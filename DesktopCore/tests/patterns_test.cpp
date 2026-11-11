// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Pattern.h"
#include "PatternHost.h"
#include <iostream>
#include <stdexcept>
using namespace Ignite;
static void require(bool ok,const char* what){if(!ok)throw std::runtime_error(what);}
struct Host final : PatternHost {
    int bars=0,clears=0,saves=0;
    void patternLengthChanged(const std::string& name,int value) override {require(name=="PC pattern","Wrong pattern notification");bars=value;}
    void patternCleared(const std::string& name) override {require(name=="PC pattern","Wrong clear notification");++clears;}
    void savePatternReferences(const PatternData&) override {++saves;}
};
int main(){try {
    Host host;
    Pattern p(0,"PC pattern",0,TimeBase::Base_16,1,false,&host);
    require(p.getTotalBars()==1&&p.PatternGetStepData(0).size()==16,"Original empty pattern structure lost");
    require(p.getTicksPerStep()==12,"Original sixteenth-note timing changed");
    ClientPatternNodeData note{};note.nodeId=60;note.note=60;note.velocity=104;note.lenInTicks=6;note.offset=-2;note.onState=true;
    require(p.PatternAddNodeData(0,0,note),"Cannot add note through original API");
    auto& step=p._patternData->barList.find(0)->second._BarData->stepList.find(0)->second;
    require(step.getPattern()==&p,"Step lost its parent pattern");
    auto nodes=step.getNodeList();require(nodes.size()==1&&nodes[0].note==60&&nodes[0].velocity==104&&nodes[0].offset==-2,"Original note data was changed");
    note.nodeId=67;note.note=67;require(p.PatternAddNodeData(0,0,note),"Cannot add second chord note");
    require(step.getNodeList().size()==2,"Original polyphonic step was reduced to one note");
    require(step.validateDelay(-5)==-5&&step.validateDelay(-7)==0,"Original delay bounds changed");
    require(step.validateLengthInTicks(13)==6,"Original note-length validation changed");
    ClientPatternStepData changed=*step._stepData;changed.skipStatus=true;changed.tieStatus=true;changed.enable=false;step.SetStepData(changed);
    require(step.getStepSkip()&&step.getStepTie()&&!step.getStepGate(),"Gate/skip/tie editing not preserved");
    p.setTimeBase(TimeBase::Base_16T);require(p.getTicksPerStep()==8,"Original triplet timing changed");
    require(step.validateDelay(-4)==-4&&step.validateDelay(-5)==0,"Triplet offset bounds wrong");
    p.addBars(1);require(p.getTotalBars()==2&&host.bars==2,"Pattern length not notified through host interface");
    require(p.CopyBar(0,1),"Original bar copy failed");
    auto copy=p.PatternGetStepData(1);require(copy.size()==16,"Copied bar has wrong number of steps");
    Pattern independent(p);independent.setTimeBase(TimeBase::Base_32T);
    auto& cloned=independent._patternData->barList.find(0)->second._BarData->stepList.find(0)->second;
    require(cloned.getPattern()==&independent,"Copied pattern still points to old parent");
    require(cloned.validateDelay(-2)==-2&&cloned.validateDelay(-3)==0,"Copied step uses wrong timebase");
    Pattern assigned(1,"Assigned",0,TimeBase::Base_4,1,false,nullptr);
    {Pattern temporary(independent);assigned=temporary;}
    auto& assignedStep=assigned._patternData->barList.find(0)->second._BarData->stepList.find(0)->second;
    require(assignedStep.getPattern()==&assigned&&assignedStep.getNodeList().size()==2,"Pattern assignment retained a dead parent");
    p.clearPattern();
    // Original CopyBar rebuilds its step map; resolve the selection by ID again.
    const auto& current=p._patternData->barList.find(0)->second._BarData->stepList.find(0)->second;
    require(host.clears==1&&current.getNodeList().empty(),"Clear did not update the original model and host");
    require(cloned.getNodeList().size()==2,"Clearing a pattern changed its independent copy");
    p.savePatternUsedByList();require(host.saves==1,"Persistence port was not called");
    std::cout<<"PASS: original Pattern/Bar/Step run without JUCE, firmware services or a physical machine.\nPolyphonic notes, velocity, offsets, lengths, gates, ties, skips, triplets, bar copy, independent pattern copy and host notifications verified.\n";
}catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
