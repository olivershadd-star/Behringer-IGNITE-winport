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

namespace ui
{
	class SceneStatusBar : public juce::Component
	{
	public:
		void paint(juce::Graphics& g) override;
		void resized() override;

		SceneStatusBar();
		~SceneStatusBar() override;
		void setDisplayMessage(String& data);
		void onNumofBarchangedinScene(int nobar);
		void SceneloopSelectedOnStatBar(int barStart, int barEnd) {
			loopStart = barStart;
			loopEnd = barEnd;
			repaint();
		}
		void setActiveSceneBar(uint8_t index) {
			activeBar = index + 1;
			repaint();
		};
		static SceneStatusBar* GetSceneBarInstance()
		{
			static SceneStatusBar* GetAppSongInstance;
			if (NULL == GetAppSongInstance)
			{
				GetAppSongInstance = new SceneStatusBar();
			}

			return GetAppSongInstance;
		}

	private:
		int barLength{ 0 };
		volatile uint8_t activeBar{ 0 };
		int loopStart{ -1 };
		int loopEnd{ -1 };
		CommonLabel songBarLabel{ "Song Bar", "Song Bar" };
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SceneStatusBar)
	};

	class PatternStatusBar : public juce::Component
	{
	public:
		void paint(juce::Graphics& g) override;
		void resized() override;

		PatternStatusBar();
		~PatternStatusBar() override;
		void setDisplayMessage(String& data);
		void onNumbofBarchangePattern(int nobar) {
			patternBarLength = (float)nobar + 1;
			repaint();
		}
		void PatternloopSelOnStatBar(int barStart, int barEnd) {
			loopStart = barStart;
			loopEnd = barEnd;
			repaint();
		}
		void setActivePatternBar(uint8_t index) {
			activeBar = index + 1;;
			repaint();
		}
		static PatternStatusBar* GetPatternBarInstance()
		{
			static PatternStatusBar* GetAppSongInstance;
			if (NULL == GetAppSongInstance)
			{
				GetAppSongInstance = new PatternStatusBar();
			}

			return GetAppSongInstance;
		}

	private:
		Image SceneActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("status-bar-bg.png"));
		CommonLabel songBarLabel{ "Song Bar", "Song Bar" };
		float patternBarLength{ 0 };
		int activeBar{ 0 };
		int loopStart{ -1 };
		int loopEnd{ -1 };
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatternStatusBar)
	};
};
//[EndFile] You can add extra defines here...
//[/EndFile]
