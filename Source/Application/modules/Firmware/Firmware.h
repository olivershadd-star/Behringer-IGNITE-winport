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

   dependencies:       juce_core,juce_gui_basics,juce_data_structures, common_defs, juce_audio_devices

  END_JUCE_MODULE_DECLARATION

 *******************************************************************************/

#pragma once
#define AUDIO_COMPONENT_H_INCLUDE

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <hardware/hardware.h>

//#include <audio_engine/audio_engine.h>
//#include <common_defs/common_defs.h>

//#include "JuceLibraryCode/BinaryData.h"
#include "Application/Model/IgniteEngine.h"
#include "Application/Model/ModelParams.h"
#include "Application/Model/SongManager.h"
#include "Application/Model/PatternManager.h"
#include "Application/Model/InstrumentManager.h"
#include "Application/Model/Configs.h"
#include "Application/Model/SysexDefs.h"
#include "Application/Model/SettingsManager/SettingsTransposeControlCnfg.h"
#include "Application/Model/tsf.h"
#include "Application/Model/SequenceManager.h"
