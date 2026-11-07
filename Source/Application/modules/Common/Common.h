 /*******************************************************************************
  The block below describes the properties of this module, and is read by
  the Projucer to automatically generate project code that uses it.
  For details about the syntax and how to create or use a module, see the
  JUCE Module Format.txt file.

  BEGIN_JUCE_MODULE_DECLARATION

   ID:                 ignite_ui
   vendor:             MusicTribe
   version:            0.1.0
   name:               MusicTribe ui
   description:        Classes aand interfaces for DAW
   website:            http://www.microbees.com/
   license:            AGPLv3

   dependencies:       juce_core,juce_gui_basics,juce_data_structures, common_defs

  END_JUCE_MODULE_DECLARATION

 *******************************************************************************/

#pragma once
#define AUDIO_COMPONENT_H_INCLUDE

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_data_structures/juce_data_structures.h>

//#include <audio_engine/audio_engine.h>
//#include <common_defs/common_defs.h>

//#include "JuceLibraryCode/BinaryData.h"
#include "Utils/MLog.h"
#include "Modules/IModule.h"
//#include "Thirdparty/log_c/src/log.h"
#include "Os/CrossPlatform/CMsgQueue.h"
#include "Modules/CSong.h"
#include "Modules/IDevice.h"
#include "Modules/IListener.h"
#include "Modules/SysexUtils.h"
#include "Modules/IMidiEndPoint.h"

#include "Os/IThread.h"
#include "Os/CrossPlatform/CThread.h"
#include "Modules/anytype.h"
#include "Modules/parameter.h"
#include "Modules/Subscriptions.h"
#include "Modules/Pattern.h"
#include "Modules/Bar.h"
#include "Modules/Step.h"
#include "Modules/Track.h"
#include "Modules/Scene.h"
#include "Modules/Instrument.h"
#include "Board/CHardwareTimer.h"
#include "Modules/ISyncListener.h"
#include "Modules/CMidiClock.h"
//#include "Modules/CMidiCV.h"
#include "Board/Simulator/CSystemTick.h"
#include "Thirdparty/MidiLib/MidiTransport.h"
#include "Modules/module.h"
