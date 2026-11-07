#ifdef MICROBEES_DAW_COMPONENT_H_INCLUDED
/* When you add this cpp file to your project, you mustn't include it in a file where you've
   already included any other headers - just put it inside a file on its own, possibly with your config
   flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
   header files that the compiler may be using.
*/
#error "Incorrect use of JUCE cpp file"
#endif
#include "Common.h"

//common
//#include "JuceLibraryCode/BinaryData.cpp"

//dialogs
//#include "Thirdparty/log_c/src/log.c"
#include "Modules/CSong.cpp"

#include "Os/CrossPlatform/CThread.cpp"
#include "Modules/Pattern.cpp"
#include "Modules/Bar.cpp"
#include "Modules/Step.cpp"
#include "Modules/Track.cpp"
#include "Modules/Scene.cpp"
#include "Modules/Instrument.cpp"
#include "Common/Board/Simulator/CHardwareTimer.cpp"
#include "Modules/CSoundFontEngine.cpp"
#include "Common/Board/Simulator/CSoundEngine.cpp"
#include "Modules/CMidiClock.cpp"
#include "Common/Thirdparty/MidiLib/MidiTransport.cpp"
//#include "Modules/CMidiCV.cpp"
//#include "Common/Thirdparty/TinySoundFont/chorus.c"
//#include "Common/Thirdparty/TinySoundFont/dspfunc.c"
//#include "Common/Thirdparty/TinySoundFont/minisdl_audio.c"
//#include "Common/Thirdparty/TinySoundFont/reverb.c"
