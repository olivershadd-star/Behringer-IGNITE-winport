// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <array>
#include <atomic>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

struct tsf;
namespace ignite {
constexpr int trackCount = 6, stepCount = 16;
struct Step { bool enabled = false; uint8_t note = 60, velocity = 96; };
struct Track {
    int bank = 0, program = 0, note = 60;
    bool muted = false;
    std::array<Step, stepCount> steps{};
};
struct Pattern { double bpm = 120; std::array<Track, trackCount> tracks{}; };
struct Preset { int bank, program; std::string name; };
Pattern makeDemo();
Pattern makeEmpty();

// No JUCE, operating-system device, hardware, MIDI port or timer dependency.
// Message-thread producer -> bounded SPSC commands -> audio-thread consumer.
class AudioCore {
public:
    AudioCore() = default;
    ~AudioCore();
    AudioCore(const AudioCore&) = delete;
    AudioCore& operator=(const AudioCore&) = delete;
    bool loadSoundFont(const std::filesystem::path& path);
    void prepare(double sampleRate);
    bool setPattern(const Pattern&);
    bool play();
    bool stop();
    bool noteOn(int track, int note, float velocity);
    bool noteOff(int track, int note);
    bool audition(int track, int note);
    void setVolume(float value) { volume.store(value); }
    void render(float* left, float* right, int frames);
    bool ready() const { return font != nullptr; }
    bool hasPreset(int bank, int program) const;
    const std::vector<Preset>& presets() const { return catalog; }
    int playhead() const { return visibleStep.load(); }
    int programForTrack(int track) const { return visiblePrograms[static_cast<size_t>(track)].load(); }
    uint64_t stepsPlayed() const { return stepCounter.load(); }
    float peak() const { return visiblePeak.load(); }
    uint64_t droppedCommands() const { return dropped.load(); }
private:
    enum class Type { pattern, play, stop, on, off, audition };
    struct Command { Type type = Type::stop; int track = 0, note = 0; float velocity = .8f; Pattern data; };
    static constexpr unsigned queueSize = 256;
    bool push(const Command&);
    void commands();
    void applyPattern(const Pattern&);
    void silence();
    void triggerStep();
    tsf* font = nullptr;
    std::array<tsf*, trackCount> voices{};
    std::vector<Preset> catalog;
    Pattern pattern = makeDemo();
    std::array<Command, queueSize> queue{};
    std::atomic<unsigned> writeIndex{0}, readIndex{0};
    std::atomic<uint64_t> dropped{0}, stepCounter{0};
    std::atomic<bool> panic{false};
    std::atomic<int> visibleStep{-1};
    std::array<std::atomic<int>, trackCount> visiblePrograms{};
    std::atomic<float> visiblePeak{0}, volume{.7f};
    double rate = 48000, remaining = 0;
    bool playing = false;
    int nextStep = 0;
    std::array<int, trackCount> sequenceNotes{{-1,-1,-1,-1,-1,-1}};
    std::array<int, trackCount> previewNotes{{-1,-1,-1,-1,-1,-1}};
    std::array<double, trackCount> gates{}, previewGates{};
    std::array<float, 256> scratch{};
    float smoothedVolume = .7f;
};
}
