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

#ifdef IGNITE_UI_CONTROLS_INCLUDE
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
#error "Incorrect use of JUCE cpp file"
#endif

 // Module include files...
#include "common_ui_controls.h"

// Module source files...
#include "source/common_Theme.cpp"
#include "source/common_lookAndFeel.cpp"
#include "source/common_buttons.cpp"
#include "source/common_label.cpp"
#include "source/common_number.cpp"
#include "source/common_listbox.cpp"
#include "source/common_MultiSelectTabBarButton.cpp"
#include "source/common_viewport.cpp"
#include "source/common_progressbar.cpp"
#include "source/common_popup.cpp"
#include "source/common_threadwithprogressbar.cpp"
#include "source/common_keyboard.cpp"
#include "source/common_rotaryslider.cpp"
#include "source/common_trackbutton.cpp"
#include "source/common_utils.cpp"
#include "source/common_helpInfoPopup.cpp"
#include "source/common_gif_preloader.cpp"
#include "source/BinaryData.cpp"