// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <juce_dsp/juce_dsp.h>
#include "PatternPlayback.h"
#define FILTER_LOWEQ_INDEX 0
#define FILTER_HIGHEQ_INDEX 1
#define EQFILTER_INDEX_MAX 2
#define AUDIO_REVERB 0
#define AUDIO_CHORUS 1
#define AUDIO_EQ_H 2
#define AUDIO_EQ_L 3
#define AUDIO_FILTER 4
#define AUDIO_EFFECT_MAX 5
enum class InternalAudioCC : uint8_t { RELEASE, FILTER_CUTOFF, RESONANCE, VOLUME, REVERB, CHORUS, EQ_LOW, EQ_HIGH };
// Fields and generated method bodies come from original Track, without a
// SongManager, external ports, firmware lifecycle or front-panel knob bank.
class TrackEffects final : public Ignite::PatternAudioEffects {
public:
    void prepare(double rate) { sampleRate=rate;effectsInit(); }
    void process(float*,int) override;
    void reset() override { resetEffects();filter.reset(); }
    void setInternalAudioEffects(uint8_t,float,bool);
    void setReverbMix(float value) { value=std::clamp(value,0.0f,1.0f);theReverbParameters.width=value>0?1.0f:0.0f;theReverbParameters.wetLevel=value;theReverbParameters.dryLevel=1.0f-value; }
private:
    void resetEffects();void effectsInit();void reverbInit();void chorusInit();void eqInit();void filterInit();void gainInit();
    double sampleRate=48000;
    float masterVolume=0.8f;
    uint8_t audioEffectsOrder[AUDIO_EFFECT_MAX]{ AUDIO_REVERB,AUDIO_CHORUS,AUDIO_EQ_L,AUDIO_EQ_H,AUDIO_FILTER };
    juce::Reverb igniteReverb;
    juce::Reverb::Parameters theReverbParameters;
    juce::dsp::Chorus<float> _Chorus[1];
    bool chorusStatus[1]{false};
    juce::dsp::IIR::Filter<float> eqFilter[EQFILTER_INDEX_MAX];
    float EQcutoffFreq[EQFILTER_INDEX_MAX]{20.0f,20000.0f};
    float EQcutoffGain[EQFILTER_INDEX_MAX]{0.0001f,0.0001f};
    bool EQisEnabled[EQFILTER_INDEX_MAX]{false,false};
    juce::dsp::LadderFilter<float> filter;
    float filtercutoffFreq=20000.0f,filterResonance=0.1f;
    juce::dsp::Gain<float> trackGain;
};
