/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 common
  vendor:             MUSIC Tribe, MY
  version:            0.1.0
  name:               MusicTribe Common definitions
  description:        Classes and interfaces containing common definitions
  website:
  license:            AGPLv3
  dependencies:       juce_core common_defs

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#ifndef HARDWARE_H_INCLUDE
#define HARDWARE_H_INCLUDE

#include <juce_core/juce_core.h>
#include "source/i2cManager.h"
#include "source/cvControl.h"
#include "source/usbFunctionFS.h"
#include "source/PlayTribeConnectionManager.h"
#include "source/wifiManager.h"

#endif
