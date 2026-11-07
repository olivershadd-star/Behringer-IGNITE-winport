/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY.
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

#pragma once

namespace ui
{
	class IgniteTopBar :
		public juce::Component,
		public ui::CommonToggleButton::Listener
	{
	public:
		IgniteTopBar();
		~IgniteTopBar();

	private:
		juce::FlexBox topBarBox;
		ui::CommonToggleButton song{ "SONG" }, scene{ "SCENE" }, track{ "TRACK" }, pattern{ "PATTERN"
		};
		ui::CommonLabel bbs{ "BAR:BEAT:STEP","001:01:01" };
		ui::CommonImageButton menuButton{ TRANS("Menu"), "Menu.png", "Menu.png" };
		ui::CommonImageButton settings{ "SETTIGNS", "Settings.png", "Settings1.png" };
		ui::CommonImageButton mainModeButton{ "MAINMODE", "Mainmode_Normal.png", "Mainmode_Pressed.png" };
		ui::CommonToggleButton listview{ "LIST VIEW" };
		ui::CommonToggleButton barview{ "BAR VIEW" };
		ui::CommonToggleButton gridview{ "GRID VIEW" };
		ui::CommonImageButton igniteSaveButton{ "SAVE", "Save.png", "Save.png" };
		ui::CommonImageButton igniteBrowseButton{ "BROWSE", "Browse.png", "Browse.png" };
		ui::CommonImageButton ignitePlayButton{ "PLAY", "Play_Pressed.png", "Pause_Pressed.png" };
		ui::CommonImageButton gridButton{ TRANS("Grid"), "Grid.png", "Grid1.png" };
		ui::CommonImageButton barButton{ TRANS("Bar"), "Step Sequencer.png", "Step Sequencer1.png" };
		ui::CommonImageButton listButton{ TRANS("List"), "List.png", "List1.png" };

		virtual void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void paint(juce::Graphics& g) override;
		void resized() override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTopBar)
	};
};
