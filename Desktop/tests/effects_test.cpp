// SPDX-License-Identifier: AGPL-3.0-or-later
#include "TrackEffects.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
static void require(bool ok,const char* why){if(!ok)throw std::runtime_error(why);}
int main(){try {
    TrackEffects dry,filtered;dry.prepare(48000);filtered.prepare(48000);
    filtered.setInternalAudioEffects(static_cast<uint8_t>(InternalAudioCC::FILTER_CUTOFF),500,false);
    filtered.setInternalAudioEffects(static_cast<uint8_t>(InternalAudioCC::RESONANCE),30,false);
    double dryEnergy=0,filterEnergy=0;
    for(int block=0;block<100;++block){float a[128],b[128];for(int i=0;i<128;++i)a[i]=b[i]=0.2f*std::sin(2*3.141592653589793*8000*(block*128+i)/48000);
        dry.process(a,128);filtered.process(b,128);for(int i=0;i<128;++i){require(std::isfinite(a[i])&&std::isfinite(b[i]),"Non-finite original filter output");if(block>10){dryEnergy+=a[i]*a[i];filterEnergy+=b[i]*b[i];}}}
    require(dryEnergy>0.01&&filterEnergy<dryEnergy*0.5,"Original low-pass filter did not attenuate high frequencies");
    filtered.setReverbMix(0.4f);filtered.setInternalAudioEffects(static_cast<uint8_t>(InternalAudioCC::CHORUS),1,false);
    for(int block=0;block<500;++block){float data[128]{};if(block==0)data[0]=0.5f;filtered.process(data,128);for(float value:data)require(std::isfinite(value)&&std::abs(value)<=0.981f,"Original effects produced invalid PCM");}
    filtered.reset();float silence[128]{};filtered.process(silence,128);for(float value:silence)require(std::abs(value)<1e-6,"Stop/reset retained an effect tail");
    std::cout<<"PASS: original Track filter attenuation, reverb/chorus finite PCM and reset.\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
