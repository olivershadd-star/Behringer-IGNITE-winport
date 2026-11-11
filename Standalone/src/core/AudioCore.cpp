// SPDX-License-Identifier: AGPL-3.0-or-later
#include "AudioCore.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#define TSF_IMPLEMENTATION
#include "../../vendor/ignite/tsf.h"

namespace ignite {
Pattern makeEmpty() {
    Pattern p;
    const int notes[] = {36,38,42,41,65,77};
    const int programs[] = {0,0,0,33,0,80};
    for (int t=0;t<trackCount;++t) {
        auto& tr=p.tracks[static_cast<size_t>(t)];
        tr.bank=t<3?128:0; tr.program=programs[t]; tr.note=notes[t];
        for(auto& s:tr.steps) s.note=static_cast<uint8_t>(tr.note);
    }
    return p;
}
Pattern makeDemo() {
    auto p=makeEmpty();
    auto put=[&](int t,int s,int note,int velocity) {p.tracks[static_cast<size_t>(t)].steps[static_cast<size_t>(s)]={true,static_cast<uint8_t>(note),static_cast<uint8_t>(velocity)};};
    for(int s=0;s<16;s+=4) put(0,s,36,110);
    put(1,4,38,106); put(1,12,38,112);
    for(int s=0;s<16;s+=2) put(2,s,42,s%4==0?72:90);
    const int bassSteps[]={0,3,6,8,11,14}, bassNotes[]={41,41,44,39,39,36};
    for(int i=0;i<6;++i) put(3,bassSteps[i],bassNotes[i],100);
    const int keys[]={65,68,63,60}, lead[]={77,80,75,72};
    for(int i=0;i<4;++i) {put(4,i*4,keys[i],76);put(5,i*4+2,lead[i],62);}
    return p;
}
AudioCore::~AudioCore() {for(auto* v:voices) if(v) tsf_close(v); if(font) tsf_close(font);}
bool AudioCore::loadSoundFont(const std::filesystem::path& path) {
    if(font) return false;
    std::ifstream in(path,std::ios::binary);
    if(!in) return false;
    const std::vector<char> bytes((std::istreambuf_iterator<char>(in)),{});
    if(bytes.empty() || bytes.size()>512u*1024u*1024u) return false;
    font=tsf_load_memory(bytes.data(),static_cast<int>(bytes.size()));
    if(!font) return false;
    for(int bank:{0,128}) for(int program=0;program<128;++program)
        if(auto* name=tsf_bank_get_presetname(font,bank,program)) catalog.push_back({bank,program,name});
    for(auto& v:voices) {v=tsf_copy(font);if(!v) {
        for(auto*& copy:voices){if(copy)tsf_close(copy);copy=nullptr;}
        tsf_close(font);font=nullptr;catalog.clear();return false;
    }}
    prepare(rate);
    return true;
}
bool AudioCore::hasPreset(int bank,int program) const {return font && tsf_get_presetindex(font,bank,program)>=0;}
void AudioCore::prepare(double sampleRate) {
    rate=std::clamp(sampleRate,8000.0,192000.0);
    for(size_t t=0;t<voices.size();++t) if(auto* v=voices[t]) {
        tsf_set_output(v,TSF_STEREO_INTERLEAVED,static_cast<int>(rate),-8.0f);
        tsf_set_max_voices(v,8);
        // Allocate both internal channels before the callback starts.
        for(int ch=0;ch<2;++ch) {tsf_channel_set_bank_preset(v,ch,0,0);tsf_channel_set_volume(v,ch,.85f);}
        visiblePrograms[t].store(-1);
    }
    silence(); applyPattern(pattern);
}
bool AudioCore::push(const Command& c) {
    const auto w=writeIndex.load(std::memory_order_relaxed), next=(w+1)%queueSize;
    if(next==readIndex.load(std::memory_order_acquire)) {dropped.fetch_add(1);panic.store(true);return false;}
    queue[w]=c; writeIndex.store(next,std::memory_order_release);return true;
}
bool AudioCore::setPattern(const Pattern& p) {Command c;c.type=Type::pattern;c.data=p;return push(c);}
bool AudioCore::play() {Command c;c.type=Type::play;return push(c);}
bool AudioCore::stop() {Command c;c.type=Type::stop;return push(c);}
bool AudioCore::noteOn(int t,int n,float velocity) {if(t<0||t>=trackCount||n<0||n>127)return false;Command c;c.type=Type::on;c.track=t;c.note=n;c.velocity=std::clamp(velocity,0.f,1.f);return push(c);}
bool AudioCore::noteOff(int t,int n) {if(t<0||t>=trackCount||n<0||n>127)return false;Command c;c.type=Type::off;c.track=t;c.note=n;return push(c);}
bool AudioCore::audition(int t,int n) {if(t<0||t>=trackCount||n<0||n>127)return false;Command c;c.type=Type::audition;c.track=t;c.note=n;return push(c);}
void AudioCore::silence() {
    playing=false;nextStep=0;remaining=0;visibleStep.store(-1);
    for(auto* v:voices) if(v) for(int ch=0;ch<2;++ch) tsf_channel_sounds_off_all(v,ch);
    sequenceNotes.fill(-1);previewNotes.fill(-1);gates.fill(0);previewGates.fill(0);
}
void AudioCore::applyPattern(const Pattern& incoming) {
    pattern=incoming;pattern.bpm=std::clamp(pattern.bpm,40.0,240.0);
    for(size_t t=0;t<voices.size();++t) {
        auto& tr=pattern.tracks[t];
        if(voices[t]) {
            const auto encoded=tr.bank*128+tr.program;
            if(visiblePrograms[t].load()!=encoded || tsf_channel_get_preset_index(voices[t],0)<0)
                for(int ch=0;ch<2;++ch) {tsf_channel_sounds_off_all(voices[t],ch);tsf_channel_set_bank_preset(voices[t],ch,tr.bank,tr.program);}
            visiblePrograms[t].store(encoded);
            if(tr.muted) for(int ch=0;ch<2;++ch) tsf_channel_sounds_off_all(voices[t],ch);
        }
    }
}
void AudioCore::commands() {
    if(panic.exchange(false)) {readIndex.store(writeIndex.load(std::memory_order_acquire),std::memory_order_release);silence();return;}
    auto r=readIndex.load(std::memory_order_relaxed);
    while(r!=writeIndex.load(std::memory_order_acquire)) {
        const auto& c=queue[r];const auto t=static_cast<size_t>(c.track);
        switch(c.type) {
        case Type::pattern:applyPattern(c.data);break;
        case Type::play:silence();playing=true;break;
        case Type::stop:silence();break;
        case Type::on:if(voices[t]&&!pattern.tracks[t].muted)tsf_channel_note_on(voices[t],1,c.note,c.velocity);break;
        case Type::off:if(voices[t])tsf_channel_note_off(voices[t],1,c.note);break;
        case Type::audition:
            if(voices[t]&&!pattern.tracks[t].muted) {
                if(previewNotes[t]>=0)tsf_channel_note_off(voices[t],1,previewNotes[t]);
                tsf_channel_note_on(voices[t],1,c.note,.85f);previewNotes[t]=c.note;previewGates[t]=rate*.23;
            }break;
        }
        r=(r+1)%queueSize;readIndex.store(r,std::memory_order_release);
    }
}
void AudioCore::triggerStep() {
    visibleStep.store(nextStep);stepCounter.fetch_add(1);
    const auto duration=rate*60.0/pattern.bpm/4.0;
    for(size_t t=0;t<voices.size();++t) {
        if(sequenceNotes[t]>=0)tsf_channel_note_off(voices[t],0,sequenceNotes[t]);
        sequenceNotes[t]=-1;
        const auto& tr=pattern.tracks[t];const auto& s=tr.steps[static_cast<size_t>(nextStep)];
        if(!tr.muted&&s.enabled&&voices[t]) {
            tsf_channel_note_on(voices[t],0,s.note,static_cast<float>(s.velocity)/127.f);
            sequenceNotes[t]=s.note;gates[t]=duration*.72;
        }
    }
    nextStep=(nextStep+1)%stepCount;remaining+=duration;
}
void AudioCore::render(float* left,float* right,int frames) {
    if(frames<=0)return;
    std::fill_n(left,frames,0.f);std::fill_n(right,frames,0.f);
    commands();if(!ready())return;
    int offset=0;float peakValue=0;
    while(offset<frames) {
        if(playing&&remaining<=0)triggerStep();
        int count=std::min(128,frames-offset);
        if(playing)count=std::min(count,std::max(1,static_cast<int>(std::ceil(remaining))));
        for(size_t t=0;t<voices.size();++t) {
            if(sequenceNotes[t]>=0) {
                if(gates[t]<=0){tsf_channel_note_off(voices[t],0,sequenceNotes[t]);sequenceNotes[t]=-1;}
                else count=std::min(count,std::max(1,static_cast<int>(std::ceil(gates[t]))));
            }
            if(previewNotes[t]>=0) {
                if(previewGates[t]<=0){tsf_channel_note_off(voices[t],1,previewNotes[t]);previewNotes[t]=-1;}
                else count=std::min(count,std::max(1,static_cast<int>(std::ceil(previewGates[t]))));
            }
        }
        for(size_t t=0;t<voices.size();++t) {
            tsf_render_float(voices[t],scratch.data(),count,0);
            if(!pattern.tracks[t].muted)for(int s=0;s<count;++s){left[offset+s]+=scratch[static_cast<size_t>(s*2)];right[offset+s]+=scratch[static_cast<size_t>(s*2+1)];}
            gates[t]-=count;previewGates[t]-=count;
        }
        const auto target=std::clamp(volume.load(),0.f,1.f);
        for(int s=0;s<count;++s) {
            smoothedVolume+=(target-smoothedVolume)*.002f;
            auto& l=left[offset+s];auto& r=right[offset+s];
            l=std::clamp(l*smoothedVolume,-.98f,.98f);r=std::clamp(r*smoothedVolume,-.98f,.98f);
            peakValue=std::max(peakValue,std::max(std::abs(l),std::abs(r)));
        }
        if(playing)remaining-=count;
        offset+=count;
    }
    visiblePeak.store(peakValue);
}
}
