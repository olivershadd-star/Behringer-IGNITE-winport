// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Pattern.h"
#include "SequenceManager.h"
#include <iostream>
#include <stdexcept>
using namespace Ignite;
static void require(bool ok,const char* why){if(!ok)throw std::runtime_error(why);}
struct Host final : SequenceHost {
    Pattern* pattern = nullptr;
    Pattern* findPattern(const std::string& name) override {return pattern && pattern->getName()==name ? pattern : nullptr;}
};
static void addNote(Pattern& p,int step,int pitch,int offset=0,int duration=6) {
    ClientPatternNodeData n{};n.nodeId=pitch;n.note=pitch;n.velocity=100;n.offset=offset;n.lenInTicks=duration;n.onState=true;
    require(p.PatternAddNodeData(0,step,n),"Cannot create original note");
}
static bool has(const MidiEventVector& events,MidiEventType type,int pitch){return std::any_of(events.begin(),events.end(),[&](auto e){return e.type==type&&e.data1==pitch;});}
int main(){try {
    Pattern p(0,"Sequence",0,TimeBase::Base_16,1,false,nullptr);Host host;host.pattern=&p;SequenceManager seq(host);
    addNote(p,0,60);addNote(p,0,64);addNote(p,2,67,2,5);
    seq.updateTrackPattern(&p);
    require(seq.getStepCountForFirstBar(p.getName())==16,"Original step count changed");
    auto at=[&](int step,int tick){return seq.getStepEventsAtOffset(p.getName(),0,step,tick);};
    require(has(at(0,0),MidiEventType::noteOn,60)&&has(at(0,0),MidiEventType::noteOn,64),"Chord note-on missing");
    require(has(at(0,6),MidiEventType::noteOff,60)&&has(at(0,6),MidiEventType::noteOff,64),"Chord note-off missing");
    require(has(at(2,2),MidiEventType::noteOn,67)&&has(at(2,7),MidiEventType::noteOff,67),"Offset/duration event positions changed");
    auto& steps=p._patternData->barList.find(0)->second._BarData->stepList;
    steps.find(0)->second._stepData->enable=false;
    seq.updateSequence(PatternChangeParameter::stepOnState,0,p.getName());
    require(!has(at(0,0),MidiEventType::noteOn,60),"Gated step still sends note-on");
    steps.find(0)->second._stepData->enable=true;
    steps.find(0)->second._stepData->tieStatus=true;
    seq.updateSequence(PatternChangeParameter::stepTieState,1,p.getName());
    require(!has(at(0,6),MidiEventType::noteOff,60)&&has(at(2,3),MidiEventType::noteOff,60),"Original tie semantics changed");
    steps.find(1)->second._stepData->skipStatus=true;
    seq.updateSequence(PatternChangeParameter::stepSkipState,1,p.getName());
    auto order=seq.patternSequenceMap.find(p.getName())->second.order.main.at(0);
    require(order.size()==15&&order[0]==0&&order[1]==2,"Skipped step not excluded from original playback order");
    auto& bar=p._patternData->barList.find(0)->second;
    bar._BarData->direction=PatternDirection::reverseB;
    seq.updateSequence(PatternChangeParameter::direction,0,p.getName());
    order=seq.patternSequenceMap.find(p.getName())->second.order.main.at(0);
    require(order.front()==15&&order.back()==0,"Original reverse order changed");
    for(auto& s:steps)s.second._stepData->skipStatus=true;
    seq.updateSequence(PatternChangeParameter::stepSkipState,1,p.getName());
    require(seq.getStepCountForFirstBar(p.getName())==0,"All-skipped pattern should be silent");
    steps.find(3)->second._stepData->skipStatus=false;bar._BarData->direction=PatternDirection::pendulum;
    seq.updateSequence(PatternChangeParameter::stepSkipState,0,p.getName());
    require(seq.getFirstStepOfBar(0,p.getName())==3&&seq.getStepCountForFirstBar(p.getName())==1,"Single-step pendulum is invalid");
    bar._BarData->direction=PatternDirection::alternate;
    seq.updateSequence(PatternChangeParameter::direction,0,p.getName());
    require(seq.getStepCountForFirstBar(p.getName())==2,"Original alternate direction should repeat its single step");
    require(seq.getStepEventsAtOffset("missing",0,0,0).empty(),"Unknown pattern must be silent");
    std::cout<<"PASS: original SequenceManager chord on/off, durations, gate, tie, skip, reverse, empty and singleton patterns.\n";
}catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
