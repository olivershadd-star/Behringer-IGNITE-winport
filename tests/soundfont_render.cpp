#define TSF_IMPLEMENTATION
#include "../Source/Application/modules/Firmware/Application/Model/tsf.h"
#include <cassert>
#include <initializer_list>
#include <cmath>
#include <cstdio>
int main() {
 auto* sf=tsf_load_filename("Source/Application/sf/Ignite.sf2");
 assert(sf); tsf_set_output(sf, TSF_MONO, 48000, -12);
 assert(tsf_set_max_voices(sf,8));
 float samples[960]; double energy=0;
 for(int program : {0,32,80}) {
  assert(tsf_channel_set_bank_preset(sf,0,0,program));
  tsf_channel_note_on(sf,0,60,0.8f);
  for(int b=0;b<25;++b) {tsf_render_float(sf,samples,960,0); for(float v:samples) { assert(std::isfinite(v)); energy+=v*v; }}
  tsf_channel_note_off_all(sf,0);
 }
 assert(energy>0.01); std::printf("TinySoundFont: %d presets, piano/bass/lead rendered, energy=%f\n",tsf_get_presetcount(sf),energy); tsf_close(sf);
}
