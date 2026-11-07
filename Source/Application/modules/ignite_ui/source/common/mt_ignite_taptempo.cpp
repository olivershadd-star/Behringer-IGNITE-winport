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

#define TIMEOUT_THRESHOLD_MILLISECOND 3000
#define TIMER_TIMEOUT_UPDATE_TEMPO_MILLISECOND 2000
#define TIMER_TIMEOUT_UPDATE_IMAGE_MILLISECOND 50
//#define TEMPO_CALCULATION_LAST_N_STEPS
#define TEMPO_CALCULATION_EACH_N_STEPS
#define SEND_TEMPO_AS_PLAY_MODE_TIMER
//#define SEND_TEMPO_AS_EDIT_MODE_UNDO

namespace ui
{
	IgniteTapTempo::IgniteTapTempo()
	{
		setName("TapTempo");
		setComponentID("TapTempo");
	}

	IgniteTapTempo::~IgniteTapTempo() {	}

	void IgniteTapTempo::resetTapTempoData()
	{
		numberOfTaps = 0;
		totalElapsedTime = 0;
		currentTime.clear();
	}

	void IgniteTapTempo::mouseDown(const MouseEvent& event)
	{
#if defined TEMPO_CALCULATION_EACH_N_STEPS
		if (numberOfTaps > 1)
#elif defined TEMPO_CALCULATION_LAST_N_STEPS
		if (numberOfTaps)
#endif
		{
			if ((float)std::chrono::duration_cast<std::chrono::milliseconds>
				((std::chrono::system_clock::now()) - (currentTime.back())).count() > TIMEOUT_THRESHOLD_MILLISECOND)
			{
				numberOfTaps = 0;
				totalElapsedTime = 0.0f;
				currentTime.clear();
#if defined SEND_TEMPO_AS_EDIT_MODE_UNDO
				sendUndoForTapTempo = false;
#endif
			}
		}

		currentTime.push_back(std::chrono::system_clock::now());
		numberOfTaps++;
		setClickState(true);

#if defined SEND_TEMPO_AS_PLAY_MODE_TIMER
		Timer::callAfterDelay(TIMER_TIMEOUT_UPDATE_IMAGE_MILLISECOND, [this] { updateTempoImage(); });
		startTimer(TIMER_TIMEOUT_UPDATE_TEMPO_MILLISECOND);
#elif defined SEND_TEMPO_AS_EDIT_MODE_UNDO
		startTimer(TIMER_TIMEOUT_UPDATE_IMAGE_MILLISECOND);
#endif
		if (numberOfTaps >= getTapConfigValue())
		{
			totalElapsedTime = 0.0f;
			for (auto ct = currentTime.begin(); ct != currentTime.end(); ++ct)
			{
				auto ctnext = ct + 1;
				if (ctnext != currentTime.end())
				{
					totalElapsedTime = totalElapsedTime + (float)std::chrono::duration_cast<std::chrono::milliseconds>(*ctnext - *ct).count();
				}
			}

			if (totalElapsedTime > 0.0f)
			{
				auto averageElapsedTime = totalElapsedTime / (currentTime.size() - 1);
				if (averageElapsedTime > 0.0f)
				{
					averageElapsedTimePerMin = ((1000.0f / averageElapsedTime) * 60.0f);
					averageElapsedTimePerMin = averageElapsedTimePerMin < minTempo ? minTempo : averageElapsedTimePerMin;
					averageElapsedTimePerMin = averageElapsedTimePerMin > maxTempo ? maxTempo : averageElapsedTimePerMin;
#if defined SEND_TEMPO_AS_PLAY_MODE_TIMER
					/* Send tempo value as play mode data */
					DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "Tempo value as play mode data : " + String(averageElapsedTimePerMin));
					if (onValueChanged)
						onValueChanged((float)averageElapsedTimePerMin, true);
#elif defined SEND_TEMPO_AS_EDIT_MODE_UNDO
					if (onValueChanged)
						onValueChanged((float)averageElapsedTimePerMin, sendUndoForTapTempo);
					sendUndoForTapTempo = true;
#endif
				}
			}
#if defined TEMPO_CALCULATION_LAST_N_STEPS
			currentTime.erase(currentTime.begin());
			numberOfTaps--;
#elif defined TEMPO_CALCULATION_EACH_N_STEPS
			numberOfTaps = 0;
			totalElapsedTime = 0.0f;
			currentTime.clear();
#endif
		}
	}

	void IgniteTapTempo::paint(juce::Graphics& g)
	{
	}

	void IgniteTapTempo::mouseMove(const MouseEvent& event)
	{
#if PHY_MOUSE_OVER
		if (focusState != true)
		{
			focusState = true;
			if (onFocusChanged)
				onFocusChanged(true);
		}
#endif
	}

	void IgniteTapTempo::mouseExit(const MouseEvent& event)
	{
#if PHY_MOUSE_OVER
		if (focusState != false)
		{
			focusState = false;
			if (onFocusChanged)
				onFocusChanged(false);
		}
#endif
	}

	void IgniteTapTempo::timerCallback()
	{
#if defined SEND_TEMPO_AS_PLAY_MODE_TIMER
		averageElapsedTimePerMin = averageElapsedTimePerMin < minTempo ? minTempo : averageElapsedTimePerMin;
		averageElapsedTimePerMin = averageElapsedTimePerMin > maxTempo ? maxTempo : averageElapsedTimePerMin;
		/* Send tempo value as edit mode data */
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "Tempo value as edit mode data : " + String(averageElapsedTimePerMin));
		if (onValueChanged)
			onValueChanged((float)averageElapsedTimePerMin, false);
#elif defined SEND_TEMPO_AS_EDIT_MODE_UNDO
		setClickState(false);
#endif
		stopTimer();
	}

	void IgniteTapTempo::updateTempoImage()
	{
		setClickState(false);
	}

	bool IgniteTapTempo::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		focusState = isFocuse;
		if (isFocuse == true)
		{
			if (onFocusChanged)
				onFocusChanged(true);
		}
		return true;
	}
};
