/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY
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
class AppHome;
class IgniteAnimatdText;
namespace ui
{
	class AppStatusbar : public juce::Component
	{
	public:
		CommonLabel barLabel{ "" };
		CommonLabel beatStepLabel{ "" };
		CommonLabel timeLabel{ "Time: " };
		IgniteAnimatdText textHandler;

		void paint(juce::Graphics& g) override;
		void resized() override;

		AppStatusbar();
		~AppStatusbar() override;
		void setDisplayMessage(String& data1, String& data2);
		void setTimeMessage(String& data);
		void setBarDisplayMessage(String& data);
		void setBeatStepDisplayMessage(String& data);

		static AppStatusbar* GetAppStatusBarInstance()
		{
			static AppStatusbar* GetAppSongInstance;
			if (NULL == GetAppSongInstance)
			{
				GetAppSongInstance = new AppStatusbar();
			}

			return GetAppSongInstance;
		}

	private:
		CommonLabel statusLabel1{ "StatusBar1", "Status Bar1" };
		CommonLabel statusLabel2{ "StatusBar2", "Status Bar2" };
		FlexBox box;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppStatusbar)
	};
};
//[EndFile] You can add extra defines here...
//[/EndFile]
