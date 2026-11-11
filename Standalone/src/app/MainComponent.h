// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "../core/AudioCore.h"
#include <thread>

class StepButton : public juce::TextButton {
public:
    std::function<void()> onChooseNote;
    void mouseDown(const juce::MouseEvent& e) override {if(e.mods.isPopupMenu()){if(onChooseNote)onChooseNote();}else juce::TextButton::mouseDown(e);}
};
class MainComponent final : public juce::AudioAppComponent,private juce::Timer,private juce::MidiKeyboardState::Listener {
public:
    explicit MainComponent(bool selfTest);
    ~MainComponent() override;
    void prepareToPlay(int,double) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo&) override;
    void releaseResources() override {}
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    struct Row {
        juce::TextButton select,preview,mute;
        juce::ComboBox instrument,note;
        std::array<StepButton,ignite::stepCount> steps;
    };
    void timerCallback() override;
    void handleNoteOn(juce::MidiKeyboardState*,int,int,float) override;
    void handleNoteOff(juce::MidiKeyboardState*,int,int,float) override;
    void syncControls();
    void sendPattern();
    void chooseNote(int track,int step);
    void openAudio();
    void savePattern();
    void loadPattern();
    void capture(const juce::String& file);
    void testTick();
    void testFinish(bool,const juce::String&);
    bool testClick(juce::Component&);
    ignite::AudioCore core;
    ignite::Pattern pattern=ignite::makeDemo();
    juce::LookAndFeel_V4 look;
    juce::TextButton play{"PLAY"},stop{"STOP"},demo{"Demo"},clear{"Effacer"},save{"Enregistrer"},load{"Ouvrir"},audio{"Sortie audio"};
    juce::Slider tempo,volume;
    std::array<Row,ignite::trackCount> rows;
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboard{keyboardState,juce::MidiKeyboardComponent::horizontalKeyboard};
    juce::Label status,hint;
    std::unique_ptr<juce::FileChooser> chooser;
    bool testing=false,bankLoaded=false;
    int selectedTrack=4,highlight=-1;
    std::array<int,128> keyboardOwners{};
    std::array<float,2048> monoScratch{};
    juce::String message="Demo chargee : appuyez sur PLAY.";
    std::atomic<bool> renderTest{false};
    std::thread testAudio;
    std::atomic<double> callbackEnergy{0};
    std::atomic<uint64_t> callbackFrames{0};
    std::atomic<double> deviceRate{0};
    double accumulatedEnergy=0;
    std::vector<float> recording;
    size_t recordingPosition=0;
    int testStage=0,testTicks=0,stageTicks=0,oldProgram=0;
    double checkpointEnergy=0;
    uint64_t checkpointFrames=0;
    juce::String deviceError;
};
