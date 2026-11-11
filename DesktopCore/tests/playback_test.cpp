// SPDX-License-Identifier: AGPL-3.0-or-later
#include "PatternPlayback.h"
#include "Pattern.h"
#include "SequenceManager.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
using namespace Ignite;
static void require(bool ok,const char* why){if(!ok)throw std::runtime_error(why);}
struct Host final : SequenceHost {
    Pattern* p=nullptr;
    Pattern* findPattern(const std::string& name) override{return p&&p->getName()==name?p:nullptr;}
};
static void word(std::ostream& out,uint32_t value,int bytes){for(int i=0;i<bytes;++i)out.put(static_cast<char>((value>>(8*i))&255));}
static void wav(const char* path,const std::vector<float>& l,const std::vector<float>& r,int rate){
    std::ofstream out(path,std::ios::binary);require(bool(out),"Cannot write audio evidence");
    out.write("RIFF",4);word(out,36+static_cast<uint32_t>(l.size()*4),4);out.write("WAVEfmt ",8);word(out,16,4);word(out,1,2);word(out,2,2);
    word(out,rate,4);word(out,rate*4,4);word(out,4,2);word(out,16,2);out.write("data",4);word(out,static_cast<uint32_t>(l.size()*4),4);
    for(size_t i=0;i<l.size();++i)for(float sample:{l[i],r[i]})word(out,static_cast<uint16_t>(static_cast<int16_t>(std::clamp(sample,-1.0f,1.0f)*32767)),2);
}
static double energy(const std::vector<float>& samples,size_t first,size_t end){double result=0;for(size_t i=first;i<end;++i){require(std::isfinite(samples[i]),"Non-finite audio sample");result+=samples[i]*samples[i];}return result/(end-first);}
int main(int argc,char** argv){try {
    require(argc==3,"Usage: original_playback_test bank.sf2 evidence.wav");
    std::ifstream in(argv[1],std::ios::binary);require(bool(in),"Missing internal instrument bank");
    std::vector<char> bytes((std::istreambuf_iterator<char>(in)),{});
    Pattern p(0,"Audio",0,TimeBase::Base_16,1,false,nullptr);
    ClientPatternNodeData n{};n.nodeId=60;n.note=60;n.velocity=100;n.lenInTicks=6;n.offset=2;n.onState=true;
    require(p.PatternAddNodeData(0,2,n),"Cannot edit original model for playback");
    Host host;host.p=&p;SequenceManager sequence(host);sequence.updateTrackPattern(&p);
    const auto plan=compilePatternPlayback(sequence,p);
    require(plan.ticks==192&&plan.notes.size()==2&&plan.notes[0].tick==26&&plan.notes[1].tick==32,"Original events not preserved in PCM schedule");
    PatternPlayback audio;require(!audio.play(),"Play accepted missing instruments");
    require(!audio.loadBank(nullptr,0)&&audio.loadBank(bytes.data(),bytes.size()),"Instrument bank failed to load");
    require(audio.presets().size()>128,"Melodic and drum presets missing");
    require(!audio.setPreset(999,999),"Invalid preset accepted");
    std::vector<float> evidenceL,evidenceR;
    for(int rate:{44100,48000,96000}){
        audio.prepare(rate);require(audio.setPreset(0,0),"Piano preset missing");audio.setPattern(plan,120);require(audio.play(),"Play failed");
        std::vector<float> l(rate*4),r(l.size());const auto before=audio.noteOns();
        // Deliberately irregular blocks: the musical clock follows samples,
        // not UI timer frequency or buffer length.
        size_t offset=0;const int blocks[]={31,127,512,73,1024};int block=0;
        while(offset<l.size()){int count=std::min(static_cast<size_t>(blocks[block++%5]),l.size()-offset);audio.render(l.data()+offset,r.data()+offset,count);offset+=count;}
        require(audio.noteOns()-before==2,"Loop note count depends on sample rate or block size");
        const auto onset=static_cast<size_t>(std::ceil(rate*60.0/120/48*26));
        require(energy(l,0,onset)==0&&energy(l,onset,onset+rate/10)>1e-7,"Original offset did not become audible at the expected sample");
        audio.stop();require(audio.playStep()==-1,"Stop left the play cursor active");audio.render(l.data(),r.data(),1000);require(energy(l,0,1000)==0,"Stop left sounding notes");
        if(rate==48000){evidenceL=std::move(l);evidenceR=std::move(r);}
    }
    // Same original events through an internal drum kit, without external MIDI.
    p.clearPattern();n.nodeId=36;n.note=36;n.offset=0;p.PatternAddNodeData(0,0,n);
    sequence.updateSequence(PatternChangeParameter::addRemoveNote,0,p.getName());
    audio.prepare(48000);require(audio.setPreset(128,0),"Internal drum kit missing");audio.setPattern(compilePatternPlayback(sequence,p),120);audio.play();
    std::vector<float> drumL(48000),drumR(48000);audio.render(drumL.data(),drumR.data(),48000);
    require(energy(drumL,0,12000)>1e-7,"Internal kick is silent");
    // An anticipation remains in the immutable plan and wraps into the prior
    // cycle; unsupported firmware Track features must not disappear silently.
    p.clearPattern();n.nodeId=60;n.note=60;n.offset=-2;n.lenInTicks=6;p.PatternAddNodeData(0,0,n);
    sequence.updateSequence(PatternChangeParameter::addRemoveNote,0,p.getName());
    const auto early=compilePatternPlayback(sequence,p);
    require(early.notes.size()==2&&early.notes[0].tick==4&&!early.notes[0].on&&early.notes[1].tick==190&&early.notes[1].on,"Negative offset was silently lost");
    p._patternData->barList.find(0)->second._BarData->barRepeatCount=1;
    bool refused=false;try {compilePatternPlayback(sequence,p);}catch(const std::invalid_argument&){refused=true;}
    require(refused,"Track-only bar repeats were silently ignored");
    // The evidence contains a four-second piano pattern followed by a kick.
    evidenceL.insert(evidenceL.end(),drumL.begin(),drumL.end());evidenceR.insert(evidenceR.end(),drumR.begin(),drumR.end());wav(argv[2],evidenceL,evidenceR,48000);
    std::cout<<"PASS: original Pattern -> SequenceManager -> original TSF -> PCM.\nPiano/drum bank, 44.1/48/96 kHz, irregular buffers, sample offset, loop count and immediate Stop verified.\n";
}catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
