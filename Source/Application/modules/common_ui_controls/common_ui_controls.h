/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 common_defs
  vendor:             MUSIC Tribe, MY
  version:            0.1.0
  name:               MusicTribe Common definitions
  description:        Classes and interfaces containing common definitions
  website:
  license:            AGPLv3
  author:             MUSIC Tribe

  dependencies:       juce_core, juce_gui_basics, common_defs

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#ifndef IGNITE_UI_CONTROLS_INCLUDE
#define IGNITE_UI_CONTROLS_INCLUDE

// Dependent module includes.
#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <common_defs/common_defs.h>

// Common definitions...
namespace ui
{
enum
{
    IGNITE_DIALOG_APPLY,
    IGNITE_DIALOG_CANCEL
};
}; // namespace :: ui

// Module include files.
#include "source/common_Theme.h"
#include "source/common_lookAndFeel.h"
#include "source/common_slider.h"
#include "source/common_label.h"
#include "source/common_buttons.h"
#include "source/common_number.h"
#include "source/common_canvas.h"

#include "source/common_progressbar.h"
#include "source/common_listbox.h"
#include "source/common_MultiSelectTabBarButton.h"
#include "source/common_viewport.h"
#include "source/common_popup.h"
#include "source/common_threadwithprogressbar.h"
#include "source/common_trackbutton.h"
#include "source/common_utils.h"
#include "source/common_keyboard.h"
#include "source/common_helpInfoPopup.h"
#include "source/common_rotaryslider.h"
#include "source/common_gif_preloader.h"
#include "source/BinaryData.h"
#endif
