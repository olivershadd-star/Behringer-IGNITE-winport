/*
* Copyright (C) Musictribe Innovation India Pvt. Ltd
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
#define PAN_MAX_THRESHOLD 128
	class TrackMixerControl : public juce::Component,
		public juce::Button::Listener
	{
	public:
		TrackMixerControl();
		~TrackMixerControl() override;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void getAssets();
	private:
		void updateRangeText();

	SIGNALS:
		sig::Signal <juce::String > controlParamChanged;
		//bool true for left nudge
		sig::Signal<bool> leftNudgeChanged;
		sig::Signal<bool> rightNudgeChanged;
		sig::Signal<bool> presetOn;

	private:
		enum e_paramValueType {
			eMIN,
			eVolume,
			ePan,
			eMAX
		};

		std::map<juce::String, e_paramValueType> s_mapStringToParamValueType =
		{
			{ "Volume",			eVolume },
			{ "Pan",			ePan },
		};

		ui::CommonButton trackBankButton{ TRANS("1/1") };
		ui::CommonButton leftRangeButton{ TRANS("<") };
		ui::CommonButton rightRangeButton{ TRANS(">") };
		ui::CommonButton leftNudgeButton{ TRANS("") };
		ui::CommonButton nudgeText;
		ui::CommonButton rightNudgeButton{ TRANS("") };
		juce::String sparamListValue = "Veolume";
		CommonImageButton volumeButton{ "Volume","btn-bottom-volume-default.png","btn-bottom-volume-active.png","btn-bottom-volume-default-hover.png"};
		CommonImageButton panButton{ "Pan","btn-bottom-pan-default.png","btn-bottom-pan-active.png","btn-bottom-pan-default-hover.png" };
		Image imageScrollBtmDefault, imageScrollBtmDefaultHover, imageScrollLftDefault, imageScrollLftDefaultHover, imageScrollRgsDefault, imageScrollRgtDefaultHover;

		int totalBars = 1;
		int rangeLow = 1;
		int rangeHigh = 16;
		int threshold = 127;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackMixerControl)
	};
}
