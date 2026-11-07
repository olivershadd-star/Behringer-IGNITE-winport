#ifdef MICROBEES_DAW_COMPONENT_H_INCLUDED
/* When you add this cpp file to your project, you mustn't include it in a file where you've
   already included any other headers - just put it inside a file on its own, possibly with your config
   flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
   header files that the compiler may be using.
*/
#error "Incorrect use of JUCE cpp file"
#endif
#include "Firmware.h"

//common
//#include "JuceLibraryCode/BinaryData.cpp"

//dialogs
#include "Application/Model/IgniteEngine.cpp"
#include "Application/Model/SongManager.cpp"
#include "Application/Model/PatternManager.cpp"
#include "Application/Model/InstrumentManager.cpp"
#include "Application/Model/EngineFileHandler.cpp"
#include "Application/Model/TrackManager.cpp"
#include "Application/Model/SceneManager.cpp"
#include "Application/Model/FrontPannelManager.cpp"
#include "Application/Model/FrontPannelUtility.cpp"
#include "Application/Model/FrontPannelLed.cpp"
#include "Application/Model/SettingsManager/SettingsMidiCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsCvioCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsGeneralCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsSongCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsSceneCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsTrackCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsTrackInstrumentMixer.cpp"
#include "Application/Model/SettingsManager/SettingsPatternCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsRecordCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsBRayCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsRemoteControlCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsMidiMachineControlCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsSculptModeCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsUdsCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsMidiClkCnfg.cpp"
#include "Application/Model/SettingsManager/SettingsTransposeControlCnfg.cpp"
#include "Application/Model/SequenceManager.cpp"
