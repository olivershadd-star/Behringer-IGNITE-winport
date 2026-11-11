#!/usr/bin/env python3
import hashlib,json,re,sys
from pathlib import Path
root=Path(__file__).resolve().parents[1];out=Path(sys.argv[1]);out.mkdir(parents=True,exist_ok=True)
provenance=json.loads((root/'upstream/provenance.json').read_text())
fragments={}
for name,digest in provenance['fragments'].items():
    raw=(root/'upstream'/name).read_bytes()
    if hashlib.sha256(raw).hexdigest()!=digest:raise SystemExit('Original effect fragment changed: '+name)
    fragments[name]=raw.decode()
methods=fragments['Track-effect-methods.cpp.txt'].replace('Track::','TrackEffects::')
methods=methods.replace('INTERNAL_AUDIO_SAMPLE_RATE','sampleRate').replace('INTERNAL_AUDIO_20MS_BLOCK_SIZE','128')
methods=re.sub(r'^.*std::lock_guard.*\n','',methods,flags=re.M)
methods=methods.replace('_songManager->setMasterVolume(value * 0.01f);','masterVolume = value * 0.01f;')
pipeline=fragments['Track-effect-pipeline.cpp.txt'].replace('_twentyMsBuffer','mono').replace('INTERNAL_AUDIO_20MS_BLOCK_SIZE','frames')
text='''// Generated from verified original Track fragments.
#include "TrackEffects.h"
#include "tsf.h"
#define USE_INTERNAL_EFFECTS
using namespace juce;
'''+methods+'''
void TrackEffects::process(float* mono,int frames) {
    juce::AudioBuffer<float> audio(&mono,1,frames);
    juce::dsp::AudioBlock<float> block(audio);
    juce::dsp::ProcessContextReplacing<float> buffer(block);
    // Firmware updated the parameter struct without applying it to Reverb.
    // Apply it here so its existing dry/width controls operate on desktop.
    igniteReverb.setParameters(theReverbParameters);
'''+pipeline+'''
    for(int i=0;i<frames;++i) mono[i]=std::clamp(mono[i]*masterVolume,-0.98f,0.98f);
}
'''
if '_songManager' in text:raise SystemExit('Firmware dependency remains in effects')
(out/'TrackEffects.cpp').write_text(text)
