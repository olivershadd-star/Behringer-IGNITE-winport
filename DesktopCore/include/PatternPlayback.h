// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>
struct tsf;
namespace Ignite {
class Pattern;
class SequenceManager;
struct ScheduledNote {
    int tick = 0;
    bool on = false;
    uint8_t pitch = 0, velocity = 0;
};
// Compiled off the audio thread from the original SequenceManager event map.
// This first player supports one pattern with note events; Track/Scene controls
// and command/aux events are deliberately not represented as supported here.
struct PatternPlaybackData {
    int ticks = 0, ticksPerStep = 12;
    std::vector<ScheduledNote> notes;
    std::vector<int> stepIds;
};
PatternPlaybackData compilePatternPlayback(SequenceManager&, const Pattern&);
struct LocalPreset { int bank = 0, program = 0; std::string name; };
// Host-neutral PCM adapter. All methods have a single owner; the desktop host
// must exchange compiled snapshots at an audio block boundary, never mutate
// the original document concurrently with render(). No device/UI lives here.
class PatternPlayback {
public:
    PatternPlayback();
    ~PatternPlayback();
    PatternPlayback(const PatternPlayback&) = delete;
    PatternPlayback& operator=(const PatternPlayback&) = delete;
    bool loadBank(const void*, size_t);
    void prepare(double sampleRate);
    bool setPreset(int bank, int program);
    const std::vector<LocalPreset>& presets() const { return catalog; }
    void setPattern(PatternPlaybackData, double bpm);
    bool play();
    void stop();
    void render(float* left, float* right, int frames);
    uint64_t framesRendered() const { return totalFrames; }
    uint64_t noteOns() const { return triggered; }
    bool isPlaying() const { return playing; }
    int playStep() const;
private:
    tsf* synth = nullptr;
    std::vector<LocalPreset> catalog;
    PatternPlaybackData pattern;
    double rate = 48000, bpm = 120, frameInLoop = 0;
    size_t nextEvent = 0;
    uint64_t totalFrames = 0, triggered = 0;
    bool playing = false;
};
}
