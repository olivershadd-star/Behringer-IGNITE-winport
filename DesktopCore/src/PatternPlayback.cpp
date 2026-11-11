// SPDX-License-Identifier: AGPL-3.0-or-later
#include "PatternPlayback.h"
#include "Pattern.h"
#include "SequenceManager.h"
#include <array>
#include <cmath>
#include <stdexcept>
#define TSF_IMPLEMENTATION
#include "../../Standalone/vendor/ignite/tsf.h"
namespace Ignite {
PatternPlaybackData compilePatternPlayback(SequenceManager& sequence, const Pattern& pattern) {
    PatternPlaybackData result;
    result.ticksPerStep = pattern.getTicksPerStep();
    const auto found = sequence.patternSequenceMap.find(pattern.getName());
    if (found == sequence.patternSequenceMap.end()) return result;
    if (pattern._patternData->_barLoopOn)
        throw std::invalid_argument("Bar loops require the original Track adapter");
    for (const auto& bar : pattern._patternData->barList)
        if (bar.second._BarData->barRepeatCount || bar.second._BarData->gBarSyncOn)
            throw std::invalid_argument("Bar repeats/global sync require the original Track adapter");
    // Only the frozen main event map is read. Call on the document owner after
    // updates have completed, then hand the resulting value to the PCM owner.
    for (const auto& bar : found->second.order.main) for (const auto step : bar.second) {
        const auto offsets = sequence.getStepEvents(pattern.getName(), bar.first, step);
        for (const auto& offset : offsets) for (const auto& event : offset.second) {
            if (event.type != MidiEventType::noteOn && event.type != MidiEventType::noteOff)
                throw std::invalid_argument("Aux/command events require the original Track adapter");
            result.notes.push_back({result.ticks + offset.first, event.type == MidiEventType::noteOn, event.data1, event.data2});
        }
        result.stepIds.push_back(step);
        result.ticks += result.ticksPerStep;
    }
    if (result.ticks == 0) return result;
    std::array<int, 128> balance{};
    for (const auto& event : result.notes) {
        if (event.pitch > 127) throw std::invalid_argument("Invalid original note pitch");
        balance[event.pitch] += event.on ? 1 : -1;
    }
    if (std::any_of(balance.begin(), balance.end(), [](int count) {return count != 0;}))
        throw std::invalid_argument("Unpaired original note events require the Track note-lifetime adapter");
    // Negative note offsets are anticipations in the repeating pattern. The
    // first cycle starts at tick zero; an anticipation of its first note is
    // heard at the end of the cycle, rather than silently dropped by a UI timer.
    for (auto& event : result.notes)
        event.tick = (event.tick % result.ticks + result.ticks) % result.ticks;
    std::stable_sort(result.notes.begin(), result.notes.end(), [](const auto& a, const auto& b) {
        return a.tick < b.tick || (a.tick == b.tick && !a.on && b.on);
    });
    return result;
}
PatternPlayback::PatternPlayback() = default;
PatternPlayback::~PatternPlayback() { if (synth) tsf_close(synth); }
bool PatternPlayback::loadBank(const void* bytes, size_t count) {
    if (synth || !bytes || count == 0 || count > 512u * 1024u * 1024u) return false;
    synth = tsf_load_memory(bytes, static_cast<int>(count));
    if (!synth) return false;
    for (const int bank : {0, 128}) for (int program = 0; program < 128; ++program)
        if (const auto* name = tsf_bank_get_presetname(synth, bank, program)) catalog.push_back({bank, program, name});
    prepare(rate);
    return setPreset(0, 0);
}
void PatternPlayback::prepare(double sampleRate) {
    stop();
    rate = std::clamp(sampleRate, 8000.0, 192000.0);
    if (synth) {
        // Original Track::sfInit: mono voice bus, 8 voices, zero dB and 0.9
        // channel volume; only the hardware sample rate becomes a host value.
        tsf_set_output(synth, TSF_MONO, static_cast<int>(rate), 0.0f);
        tsf_set_max_voices(synth, MAX_POLYPHONIC_NOTES);
        for(int channel=0;channel<2;++channel)tsf_channel_set_volume(synth,channel,0.9f);
    }
}
bool PatternPlayback::setPreset(int bank, int program) {
    if (!synth || tsf_get_presetindex(synth, bank, program) < 0) return false;
    for (int channel=0;channel<2;++channel) {
        tsf_channel_sounds_off_all(synth, channel);
        if (!tsf_channel_set_bank_preset(synth, channel, bank, program)) return false;
    }
    return true;
}
void PatternPlayback::setPattern(PatternPlaybackData incoming, double tempo) {
    stop();pattern = std::move(incoming);bpm = std::clamp(tempo, 40.0, 240.0);
}
bool PatternPlayback::play() {
    stop();
    playing = synth && pattern.ticks > 0;
    return playing;
}
void PatternPlayback::stop() {
    playing = false;frameInLoop = 0;nextEvent = 0;
    previewGate=previewTail=0;
    if (synth) for(int channel=0;channel<2;++channel) tsf_channel_sounds_off_all(synth, channel);
    if (effects) effects->reset();
}
bool PatternPlayback::audition(int pitch) {
    if (!synth || pitch<0 || pitch>127) return false;
    tsf_channel_sounds_off_all(synth,1);
    tsf_channel_note_on(synth,1,pitch,0.8f);
    previewGate=rate*0.25;previewTail=rate*2;
    return true;
}
int PatternPlayback::playStep() const {
    if (!playing || pattern.stepIds.empty()) return -1;
    const auto tick = static_cast<int>(frameInLoop / (rate * 60.0 / bpm / 48.0));
    const auto index = std::min(static_cast<size_t>(tick / pattern.ticksPerStep), pattern.stepIds.size()-1);
    return pattern.stepIds[index];
}
void PatternPlayback::render(float* left, float* right, int frames) {
    if (frames <= 0) return;
    std::fill_n(left, frames, 0.0f);std::fill_n(right, frames, 0.0f);
    if ((!playing && previewTail<=0) || !synth) return;
    std::array<float, 128> mono{};
    // Original Pattern has 48 musical ticks per quarter. The host sample clock
    // replaces the firmware's 96-PPQN hardware pulse source (two pulses/tick).
    const double framesPerTick = rate * 60.0 / bpm / 48.0;
    const double loopFrames = pattern.ticks * framesPerTick;
    int offset = 0;
    while (offset < frames) {
        if (playing && frameInLoop >= loopFrames) {
            frameInLoop -= loopFrames;nextEvent = 0;
        }
        while (playing && nextEvent < pattern.notes.size() && pattern.notes[nextEvent].tick * framesPerTick <= frameInLoop + 1e-9) {
            const auto& event = pattern.notes[nextEvent++];
            if (event.on) {tsf_channel_note_on(synth, 0, event.pitch, event.velocity / 127.0f);++triggered;}
            else tsf_channel_note_off(synth, 0, event.pitch);
        }
        double untilBoundary = playing ? loopFrames-frameInLoop : frames-offset;
        if (playing && nextEvent < pattern.notes.size()) untilBoundary=std::min(untilBoundary,pattern.notes[nextEvent].tick*framesPerTick-frameInLoop);
        if (previewGate>0) untilBoundary=std::min(untilBoundary,previewGate);
        const int count = std::min({128, frames-offset, std::max(1, static_cast<int>(std::ceil(untilBoundary-1e-9)))});
        tsf_render_float(synth, mono.data(), count, 0);
        if (effects) {
            effects->process(mono.data(),count);
        }
        for (int i=0;i<count;++i) left[offset+i]=right[offset+i]=mono[i];
        if(previewGate>0) {previewGate-=count;if(previewGate<=0)tsf_channel_note_off_all(synth,1);}
        previewTail=std::max(0.0,previewTail-count);
        offset += count;if(playing)frameInLoop += count;totalFrames += count;
    }
}
}
