#!/usr/bin/env python3
"""Build a traceable desktop adaptation of the original musical model."""
import hashlib,json,re,sys
from pathlib import Path
root=Path(__file__).resolve().parents[1]
out=Path(sys.argv[1]);out.mkdir(parents=True,exist_ok=True)
manifest=json.loads((root/'provenance.json').read_text())
sources={}
for name,item in manifest.items():
    data=(root/'upstream'/name).read_bytes()
    if hashlib.sha256(data).hexdigest()!=item['sha256']:
        raise SystemExit('Original source was modified: '+name)
    sources[name]=data.decode('utf-8-sig')

def declaration(text,kind,name):
    match=re.search(r'\b'+kind+r'\s+'+name+r'\b[^\{]*\{',text)
    if not match:raise RuntimeError('Missing original declaration '+name)
    pos=match.end();depth=1
    while depth:
        if text[pos]=='{':depth+=1
        if text[pos]=='}':depth-=1
        pos+=1
    return text[match.start():text.index(';',pos)+1]

params=sources['ModelParams.h'];data=sources['EngineDataStruct.h']
prelude='''// Generated from verified original IGNITE declarations. See provenance.json.
#pragma once
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cassert>
#ifndef DBG
#define DBG(...) ((void)0)
#endif
'''
for macro in ('MAX_STEPS_IN_PATTERN_BAR','MAX_NUM_OF_BARS_IN_PATTERN','MAX_NOTE','MAX_NOTE_VELOCITY','MAX_LENGTH_OF_A_NOTE_IN_STEPS'):
    found=re.search(r'^#define\s+'+macro+r'\s+[^\n]+',params,re.M)
    if not found:raise RuntimeError(macro)
    prelude+=found.group(0)+'\n'
for alias in ('TickLength_t','TickOffset_t'):
    prelude+=re.search(r'typedef\s+[^;]+\b'+alias+r'\s*;',params).group(0)+'\n'
prelude+='namespace Ignite {\n'
for kind,name in [('enum class','Note'),('enum class','TimeBase'),('struct','ClientPatternNodeData'),('struct','Aux'),('struct','ClientPatternStepData'),('enum class','PatternDirection'),('struct','ClienPatterntBarData'),('struct','ClientUsedByData'),('enum class','PatternDataUpdateReasonType'),('struct','PatternDataUpdateLocation'),('struct','ClientPatternData')]:
    prelude+=declaration(params,kind,name)+'\n'
prelude+='using StepData=ClientPatternStepData;\nusing NodeData=ClientPatternNodeData;\n'
prelude+=declaration(data,'struct','UsedByData')+'\n}\n'
(out/'MusicalTypes.h').write_text(prelude)

adaptations={}
for name in ('Pattern.h','Pattern.cpp','Bar.h','Bar.cpp','Step.h','Step.cpp'):
    text=sources[name]
    for include in ('Common/Modules/Pattern.h','Common/Modules/Bar.h','Common/Modules/Step.h'):
        text=text.replace(include,Path(include).name)
    for include in ('common_defs/source/EngineDataStruct.h','Firmware/Application/Model/ModelParams.h'):
        text=text.replace(include,'MusicalTypes.h')
    text=re.sub(r'#include "Firmware/Application/Model/(PatternManager|IgniteEngine)\.h"\n','',text)
    text=text.replace('class IgniteEngine;','')
    text='#include "MusicalTypes.h"\n'+text
    if name=='Step.cpp':
        text='#include "Pattern.h"\n'+text
        # The original constructors forgot the parent required by delay/length validation.
        for signature in ('Step::Step (Pattern* pat, int16_t id, uint8_t note, float length, uint8_t velocity, uint8_t delay)', 'Step::Step (Pattern* pat, StepData& stepData)'):
            needle=signature+'\n{'
            if needle not in text:raise RuntimeError('Step constructor changed')
            text=text.replace(needle,needle+'\n\t_pattern = pat;')
    if name.startswith('Pattern.'):
        text='#include "PatternHost.h"\n'+text
        if name=='Pattern.cpp':text='#include "Pattern.h"\n'+text
        text=text.replace('class PatternManager;','class PatternHost;').replace('PatternManager*','PatternHost*').replace('_patternManager','_host').replace('patternMgr','host')
        text=text.replace('_host->engine.sequenceManager->updateSequence(PatternChangeParameter::numBars, numBars, _patternData->patternName);','if (_host) _host->patternLengthChanged(_patternData->patternName, numBars);')
        text=text.replace('_host->engine.sequenceManager->handlePatternClear(_patternData->patternName);','if (_host) _host->patternCleared(_patternData->patternName);')
        text=text.replace('this->_patternData->barList.insert (*i);','this->_patternData->barList.emplace(i->first, Bar(this, i->second));')
        start=text.find('void Pattern::savePatternUsedByList (void)')
        if start>=0:
            end=text.index('std::string Pattern::PatternGetDispName',start)
            text=text[:start]+'void Pattern::savePatternUsedByList (void)\n{\n\tif (_host) _host->savePatternReferences(*_patternData);\n}\n\n'+text[end:]
    # Original raw-pointer copies are retained as shared ownership, so temporary
    # Bar values no longer leak and existing alias semantics are not changed.
    for cls,member,dtype in [('Pattern','_patternData','PatternData'),('Bar','_BarData','BarData'),('Step','_stepData','StepData')]:
        text=re.sub(r'\b'+dtype+r'\*\s*'+member+r'\s*;', 'std::shared_ptr<'+dtype+'> '+member+';',text)
        text=re.sub(re.escape(member)+r'\s*=\s*new\s*\('+dtype+r'\);',member+' = std::make_shared<'+dtype+'>();',text)
    if name=='Bar.cpp':
        # Deep copies of a pattern must point their steps at the new pattern.
        text=text.replace('_BarData->stepList = Src._BarData->stepList;','for (const auto& item : Src._BarData->stepList)\n\t\t_BarData->stepList.emplace(item.first, Step(pat, *item.second._stepData));')
    if name=='Pattern.h':
        text=text.replace('Pattern& operator= (const Pattern&) = default;','Pattern& operator= (const Pattern&);')
    if name=='Pattern.cpp':
        text+='''
Pattern& Pattern::operator=(const Pattern& source)
{
    if (this == &source) return *this;
    _host = source._host;
    _patternData = std::make_shared<PatternData>(*source._patternData);
    _patternData->barList.clear();
    for (const auto& item : source._patternData->barList)
        _patternData->barList.emplace(item.first, Bar(this, item.second));
    name = source.name;
    editStepId = source.editStepId;
    playStepId = source.playStepId;
    _NumOfStepsPerBar = source._NumOfStepsPerBar;
    editStep = nullptr;
    playStep = nullptr;
    for (auto& bar : _patternData->barList) for (auto& step : bar.second._BarData->stepList) {
        if (source.editStep && step.first == source.editStep->_stepData->stepId && bar.first == source.editStep->_stepData->BarId) editStep = &step.second;
        if (source.playStep && step.first == source.playStep->_stepData->stepId && bar.first == source.playStep->_stepData->BarId) playStep = &step.second;
    }
    return *this;
}
'''
    active=re.sub(r'/\*.*?\*/|//[^\n]*','',text,flags=re.S)
    if 'engine.' in active or 'Firmware/' in active:raise RuntimeError('Hardware dependency remains in '+name)
    (out/name).write_text(text)
    adaptations[name]={'original_sha256':manifest[name]['sha256'],'adapted_sha256':hashlib.sha256(text.encode()).hexdigest()}
(out/'adaptation-manifest.json').write_text(json.dumps(adaptations,indent=2)+'\n')
print('Verified original sources; staged Pattern/Bar/Step without JUCE, firmware bootstrap or hardware.')
