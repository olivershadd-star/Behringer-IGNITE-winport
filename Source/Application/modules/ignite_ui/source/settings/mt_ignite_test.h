/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY.
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
	class IgniteTest :
		public juce::Component,
		public juce::Button::Listener
	{
	public:
		IgniteTest();
		~IgniteTest() override;

		static IgniteTest* GetAppTestDataInstance()
		{
			static IgniteTest* GetAppTestDataObj;
			if (NULL == GetAppTestDataObj)
			{
				GetAppTestDataObj = new IgniteTest();
			}
			return GetAppTestDataObj;
		}

	private:
		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;
		juce::FlexBox ctlBox3;

		CommonNumber songNum{ "Number of Songs", 0, 64, 0 };
		CommonNumber sceneNum{ "Number of Scenes per Song", 0, 64, 0 };
		CommonListBox TrackNum{ "Number of Tracks", 4 };
		std::vector<juce::String> numOfTracks{ "16", "32", "48", "64" };
		CommonNumber PatternNum{ "Number of Patterns", 0, 256, 0 };
		CommonNumber barNum{ "Number of Bars in Pattern", 0, 16, 0 };
		CommonNumber instrNum{ "Number of Instruments", 0, 256, 0 };
		CommonButton createTestData{ "Create Test Data" };
		CommonButton touchTest{ "Touch Test" };
		CommonButton WipeTestData{ "Wipe All Test Data" };
		CommonToggleButton HW_Test{ "HardwareTest" };
		CommonToggleButton Mcu_FW_Test{ "Mcu FW Upgrade test" };

		String _title;
		int numOfSongs = 0;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTest)
	};
};
