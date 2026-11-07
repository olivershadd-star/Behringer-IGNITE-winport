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
	enum class screen
	{
		MENU,
		APP_MAIN_MODE,
		BAR,
		GRID,
		LIST,
		SETTING,

		SCREEN_MAX  // Make sure that this is at the end of enum list.
	};

	class IgniteTopBar;
	class IgniteBottomBar;
	class AppMainmode;
	class AppStatusbar;
	class AppDnp;
	class AppSettings;
	class SceneStatusBar;
	class PatternStatusBar;
	class TouchscreenTestComponent;

	class AppHome : public juce::Component
	{
	public:
		AppHome();
		~AppHome();

		void show(ui::screen Screen, bool state);
		void hideAll();
		void enableTouchTest(bool state);

		static AppHome* GetAppHomeInstance()
		{
			static AppHome* instanceAppHome;
			if (NULL == instanceAppHome)
			{
				instanceAppHome = new AppHome();
			}

			return instanceAppHome;
		}

	private:
		std::unique_ptr<IgniteTopBar> topBar;
		IgniteBottomBar* bottomBar = nullptr;
		AppMainmode* mainMode = nullptr;
		AppStatusbar* statusBar = nullptr;
		SceneStatusBar* barComp1 = nullptr;
		PatternStatusBar* barComp2 = nullptr;
#if ENABLE_HARDWARE_TEST
		TouchscreenTestComponent* touchTestComp = nullptr;
#endif
		std::unique_ptr<AppMainmode> appMainMode;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void mouseUp(const MouseEvent& event) override;

		PlaytribeConnectionStatus* playtribeConnStatusComp = nullptr;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppHome)
	};

	AppHome& getAppHome();
};