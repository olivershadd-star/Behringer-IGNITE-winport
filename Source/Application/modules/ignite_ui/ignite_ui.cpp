/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
 * This file is part of IGNITE.
 *
 * IGNITE is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * IGNITE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with IGNITE. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#ifdef IGNITE_UI_INCLUDE
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
	already included any other headers - just put it inside a file on its own, possibly with your config
	flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
	header files that the compiler may be using.
 */
#error "Incorrect use of JUCE cpp file"
#endif

 //Common

 // Module include files...
#include "ignite_ui.h"

// Module source files...
#include "source/home/mt_ignite_home.cpp"
#include "source/home/mt_ignite_menu.cpp"
#include "source/common/mt_ignite_top_bar.cpp"
#include "source/common/mt_ignite_bottom_bar.cpp"
#include "source/common/mt_ignite_taptempo.cpp"
#include "source/song/mt_ignite_songs.cpp"
#include "source/song/mt_ignite_song_detail.cpp"
#include "source/scene/mt_ignite_scene.cpp"
#include "source/scene/mt_ignite_scene_detail.cpp"
#include "source/scene/custom_scale/mt_ignite_custom_scale.cpp"
#include "source/scene/custom_scale/mt_ignite_custom_scale_opt.cpp"
#include "source/home/mt_ignite_mainmode.cpp"
#include "source/track/mt_ignite_track.cpp"
#include "source/track/mt_ignite_track_options.cpp"
#include "source/track/mt_ignite_track_values.cpp"
#include "source/track/mt_ignite_track_swap.cpp"
#include "source/pattern/step_view/mt_ignite_step.cpp"
#include "source/pattern/mt_ignite_pattern_list.cpp"
#include "source/pattern/mt_ignite_pattern.cpp"
//bar view
#include "source/pattern/bar_view/mt_ignite_bar_view_control.cpp"
#include "source/pattern/bar_view/mt_ignite_bar_view_presets.cpp"
#include "source/pattern/bar_view/mt_ignite_bar_view.cpp"
#include "source/pattern/bar_view/mt_ignite_bar_insert.cpp"
#include "source/pattern/bar_view/mt_ignite_bar_copy.cpp"
//grid view
#include "source/pattern/grid_view/src/mt_ignite_grid_control.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_data.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_parameter_view.cpp"
#include "source/pattern/grid_view/src/mt_ignite_time_sig_setting.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_view.cpp"
//#include "source/pattern/grid_view/src/mt_ignite_grid_move_resize_tool.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_erase_tool.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_cut_paste_tool.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_copy_paste_tool.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_select_tool.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_component.cpp"
#include "source/pattern/grid_view/src/mt_ignite_grid_pencil_tool.cpp"
#include "source/pattern/grid_view/src/mt_ignite_keyboard_component.cpp"

#include "source/common//mt_ignite_appdnp.cpp"
#include "source/common/mt_ignite_app_statusbar.cpp"
#include "source/common/mt_ignite_option_editctl.cpp"
#include "source/common/mt_ignite_ui_interface.cpp"
#include "source/pattern/step_view/mt_ignite_step_length.cpp"
#include "source/pattern/step_view/mt_ignite_step_event_list.cpp"
#include "source/common/mt_ignite_app_joystick.cpp"
#include "source/track/track_grid.cpp"
#include "source/instrument/mt_ignite_inst_preset.cpp"
#include "source/instrument/mt_ignite_instrument.cpp"
#include "source/instrument/mt_ignite_instrumentopt.cpp"
#include "source/settings/mt_ignite_audition.cpp"
#include "source/settings/mt_ignite_midi_clock.cpp"
#include "source/settings/mt_ignite_backup.cpp"
#include "source/settings/mt_ignite_transpose.cpp"
#include "source/settings/mt_ignite_bray.cpp"
#include "source/settings/mt_ignite_sculpt_config.cpp"
#include "source/settings/mt_ignite_midi_remote_control.cpp"
#include "source/settings/mt_ignite_midi_machine_control.cpp"
#include "source/settings/mt_ignite_wifi_detail.cpp"
#include "source/settings/mt_ignite_connectivity.cpp"
#include "source/settings/mt_ignite_misc_settings.cpp"
#include "source/settings/mt_ignite_settings.cpp"
#include "source/common/mt_ignite_bar.cpp"
#include "source/common/mt_ignite_cntropt.cpp"
#include "source/common/mt_ignite_copy.cpp"
#include "source/common/mt_ignite_app_animatedtext.cpp"
#include "source/common/mt_ignite_ui_autohide_control.cpp"
#include "source/settings/mt_ignite_loop.cpp"
#include "source/track/track_mixer/mt_ignite_track_mixer_view.cpp"
#include "source/track/track_mixer/mt_ignite_track_mixer_view_control.cpp"


//#include "source/calibration/hardware/i2cManager.cpp"
//#include "source/calibration/hardware/cvControl.cpp"

// Menu
#include "source/record/mt_ignite_record.cpp"
#include "source/record/mt_ignite_recordmodal.cpp"
#include "source/cvio/mt_ignite_cvio.cpp"
#include "source/song/mt_ignite_songConfig.cpp"
#include "source/scene/mt_ignite_sceneConfig.cpp"
#include "source/track/mt_ignite_trackConfig.cpp"
#include "source/pattern/mt_ignite_patternConfig.cpp"
#include "source/midiConfig/mt_ignite_midiConfig.cpp"
#include "source/calibration/mt_ignite_calbration.cpp"

//Device Status
#include "source/settings/mt_ignite_device_status.cpp"
#include "source/settings/mt_ignite_playtribe_connection_status.cpp"


//Front pannel
#include "source/FrontPannel/mt_ignite_frontpannel.cpp"

//Test Data
#include "source/settings/mt_ignite_test.cpp"
