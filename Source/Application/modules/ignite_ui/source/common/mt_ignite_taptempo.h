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
	class IgniteTapTempo : public juce::Component, private Timer
	{
	public:
		std::function<void(float, bool)> onValueChanged;
		std::function<int(void)> getTapConfigValue;
		std::function<void(bool)> onFocusChanged;

		IgniteTapTempo();
		~IgniteTapTempo();
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);

		void resetTapTempoData();
		bool getFocusState() {
			return focusState;
		};
		void setFocusState(bool state) {
			focusState = state;
		};
		bool getClickState() {
			return clickstate;
		}
		void setClickState(bool state) {
			clickstate = state;
			if (onFocusChanged)
				onFocusChanged(state);
		}
	private:
		std::vector<std::chrono::time_point<std::chrono::system_clock>> currentTime;
		float totalElapsedTime = 0.0f;
		int numberOfTaps = 0;
		float averageElapsedTimePerMin = 0.0f;
		bool sendUndoForTapTempo = false;


		void paint(juce::Graphics& g) override;
		void mouseDown(const MouseEvent& event) override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		bool focusState{ false };
		bool clickstate{ false };
		void timerCallback() override;
		void updateTempoImage();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTapTempo)
	};
};