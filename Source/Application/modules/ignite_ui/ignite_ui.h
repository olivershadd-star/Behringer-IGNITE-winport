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

  dependencies:       hardware, common_ui_controls, common_ui_components

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#ifndef IGNITE_UI_INCLUDE
#define IGNITE_UI_INCLUDE

// Dependent module includes.
#include <common_ui_controls/common_ui_controls.h>
#include <common_ui_components/common_ui_components.h>
#include <hardware/hardware.h>

// Module include files.
//Device Status
#include "source/settings/mt_ignite_device_status.h"
#include "source/settings/mt_ignite_playtribe_connection_status.h"

#include "source/home/mt_ignite_menu.h"
#include "source/home/mt_ignite_home.h"
#include "source/hardwareTest/mt_ignite_touchTest.h"
#include "source/common/mt_ignite_cntropt.h"
#include "source/song/mt_ignite_songConfig.h"
#include "source/common/mt_ignite_copy.h"
#include "source/settings/mt_ignite_wifi_detail.h"
#include "source/settings/mt_ignite_connectivity.h"
#include "source/settings/mt_ignite_audition.h"
#include "source/settings/mt_ignite_midi_clock.h"
#include "source/settings/mt_ignite_backup.h"
#include "source/settings/mt_ignite_transpose.h"
#include "source/settings/mt_ignite_bray.h"
#include "source/settings/mt_ignite_sculpt_config.h"
#include "source/settings/mt_ignite_midi_remote_control.h"
#include "source/settings/mt_ignite_midi_machine_control.h"
#include "source/settings/mt_ignite_loop.h"
#include "source/track/mt_ignite_track_swap.h"
#include "source/common/mt_ignite_option_editctl.h"
#include "source/common/mt_ignite_top_bar.h"
#include "source/common/mt_ignite_bottom_bar.h"
#include "source/common/mt_ignite_taptempo.h"
#include "source/common/mt_ignite_app_animatedtext.h"
#include "source/common/mt_ignite_ui_autohide_control.h"
#include "source/song/mt_ignite_songs.h"
#include "source/scene/mt_ignite_scene.h"
#include "source/song/mt_ignite_song_detail.h"
#include "source/scene/mt_ignite_scene_detail.h"
#include "source/scene/custom_scale/mt_ignite_custom_scale.h"
#include "source/scene/custom_scale/mt_ignite_custom_scale_opt.h"
#include "source/home/mt_ignite_mainmode.h"
#include "source/track/mt_ignite_track.h"
#include "source/track/mt_ignite_track_options.h"
#include "source/track/mt_ignite_track_values.h"
//bar view
#include "source/pattern/bar_view/mt_ignite_bar_view_control.h"
#include "source/pattern/bar_view/mt_ignite_bar_view_presets.h"
#include "source/pattern/bar_view/mt_ignite_bar_view.h"
#include "source/pattern/bar_view/mt_ignite_bar_insert.h"
#include "source/pattern/bar_view/mt_ignite_bar_copy.h"
//grid view
#include "source/pattern/grid_view/inc/mt_ignite_grid_control.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_data.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_parameter_view.h"
#include "source/pattern/grid_view/inc/mt_ignite_time_sig_setting.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_tool_interface.h"
//#include "source/pattern/grid_view/inc/mt_ignite_grid_move_resize_tool.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_erase_tool.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_cut_paste_tool.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_copy_paste_tool.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_select_tool.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_pencil_tool.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_component.h"
#include "source/pattern/grid_view/inc/mt_ignite_keyboard_component.h"
#include "source/pattern/grid_view/inc/mt_ignite_grid_view.h"

#include "source/pattern/step_view/mt_ignite_step.h"
#include "source/pattern/mt_ignite_pattern_list.h"
#include "source/pattern/mt_ignite_pattern.h"
#include "source/common//mt_ignite_appdnp.h"
#include "source/common/mt_ignite_app_statusbar.h"
#include "source/common/mt_ignite_ui_interface.h"
#include "source/common/mt_ignite_app_joystick.h"
#include "source/pattern/step_view/mt_ignite_step_event_list.h"
#include "source/pattern/step_view/mt_ignite_step_length.h"
#include "source/instrument/mt_ignite_inst_preset.h"
#include "source/instrument/mt_ignite_instrument.h"
#include "source/instrument/mt_ignite_instrumentopt.h"
#include "source/settings/mt_ignite_misc_settings.h"
#include "source/settings/mt_ignite_settings.h"
#include "source/track/track_grid.h"
#include "source/common/mt_ignite_bar.h"
#include "source/track/track_mixer/mt_ignite_track_mixer_view_control.h"
#include "source/track/track_mixer/mt_ignite_track_mixer_view.h"

//#include "source/calibration/hardware/i2cManager.h"
//#include "source/calibration/hardware/cvControl.h"

//Menu
#include "source/record/mt_ignite_record.h"
#include "source/record/mt_ignite_recordmodal.h"
#include "source/cvio/mt_ignite_cvio.h"
#include "source/calibration/mt_ignite_calbration.h"
#include "source/scene/mt_ignite_sceneConfig.h"
#include "source/track/mt_ignite_trackConfig.h"
#include "source/pattern/mt_ignite_patternConfig.h"
#include "source/midiConfig/mt_ignite_midiConfig.h"



//Front pannel
#include "source/FrontPannel/mt_ignite_frontpannel.h"

//Test Data
#include "source/settings/mt_ignite_test.h"

#endif // IGNITE_UI_INCLUDE
