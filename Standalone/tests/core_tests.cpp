// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../src/core/AudioCore.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace ignite;
static void require(bool value,const char* message){if(!value)throw std::runtime_error(message);}
static std::vector<float> render(AudioCore& core,int frames) {
    std::vector<float> result;result.reserve(static_cast<size_t>(frames)*2);
    const int sizes[]={1,64,127,256,960,511};int block=0;
    while(frames>0) {
        const auto n=std::min(frames,sizes[(block++)%6]);
        std::vector<float> left(static_cast<size_t>(n)+2,12345),right(left);
        core.render(left.data()+1,right.data()+1,n);
        require(left.front()==12345&&left.back()==12345&&right.front()==12345&&right.back()==12345,"Callback wrote outside its output buffer");
        for(int i=1;i<=n;++i){require(std::isfinite(left[static_cast<size_t>(i)])&&std::isfinite(right[static_cast<size_t>(i)]),"Non-finite audio");result.push_back(left[static_cast<size_t>(i)]);result.push_back(right[static_cast<size_t>(i)]);}
        frames-=n;
    }
    return result;
}
static double energy(const std::vector<float>& samples){double e=0;for(auto v:samples)e+=static_cast<double>(v)*v;return e;}
static void wav(const char* file,const std::vector<float>& samples,int rate) {
    std::ofstream out(file,std::ios::binary);
    auto put=[&](uint32_t v,int count){for(int i=0;i<count;++i)out.put(static_cast<char>((v>>(8*i))&255));};
    const auto size=static_cast<uint32_t>(samples.size()*2);
    out.write("RIFF",4);put(size+36,4);out.write("WAVEfmt ",8);put(16,4);put(1,2);put(2,2);put(static_cast<uint32_t>(rate),4);put(static_cast<uint32_t>(rate*4),4);put(4,2);put(16,2);out.write("data",4);put(size,4);
    for(float f:samples)put(static_cast<uint16_t>(static_cast<int16_t>(std::clamp(f,-1.f,1.f)*32767)),2);
}
int main(int argc,char** argv) {
    try {
        require(argc>=2,"Pass SoundFont path");
        AudioCore core;require(core.loadSoundFont(std::filesystem::u8path(argv[1])),"SoundFont failed to load");
        require(core.hasPreset(0,0)&&core.hasPreset(128,0),"Piano or drum kit missing");
        std::cout<<"Available internal instruments: "<<core.presets().size()<<'\n';
        for(int rate:{44100,48000,96000}) {
            core.prepare(rate);
            for(int t=0;t<trackCount;++t) {
                const auto p=makeEmpty();require(core.setPattern(p)&&core.audition(t,p.tracks[static_cast<size_t>(t)].note),"Command rejected");
                const auto audio=render(core,rate/2);
                require(energy(audio)>.001,"An instrument or drum produced silence");
                core.stop();render(core,rate/4);
            }
            core.setPattern(makeDemo());core.play();
            const auto before=core.stepsPlayed();const auto audio=render(core,rate*4);
            require(core.stepsPlayed()-before==32,"Sample clock drifted over two bars");
            require(energy(audio)>1,"Sequencer demo was silent");
            core.stop();render(core,rate/4);require(energy(render(core,rate/4))<.000001,"Stop left hanging notes");
            require(core.playhead()==-1,"Stop did not reset playhead");
            std::cout<<rate<<" Hz: all 6 instruments audible, variable buffers safe, 32 steps exact, stop silent\n";
            if(rate==48000&&argc>2)wav(argv[2],audio,rate);
        }
        auto p=makeEmpty();core.prepare(48000);core.setPattern(p);core.audition(4,60);const auto piano=render(core,12000);
        core.stop();render(core,12000);p.tracks[4].program=80;core.setPattern(p);core.audition(4,60);const auto lead=render(core,12000);
        double difference=0;for(size_t i=0;i<piano.size();++i)difference+=std::abs(piano[i]-lead[i]);require(difference>1,"Changing instrument did not change the rendered sound");
        core.prepare(44100);render(core,64);require(core.programForTrack(4)==80,"Device rate change lost the selected instrument");
        core.stop();render(core,12000);
        for(int i=0;i<500;++i)core.noteOn(4,60,.8f);
        render(core,4096);core.stop();render(core,24000);require(energy(render(core,12000))<.000001,"Queue overload left hanging notes");
        std::cout<<"PASS: program changes affect audio, device reopen retains sound, overload can stop safely\n";
    } catch(const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
