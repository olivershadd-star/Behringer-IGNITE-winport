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

	class IgniteTrackSwap : public juce::Component,
		public CommonButton::Listener
	{
	public:
		enum class swapCtlKey {
			SWAP,
			CANCEL,
		};

		IgniteTrackSwap();
		~IgniteTrackSwap() override;

		static IgniteTrackSwap* GetTrackSwapInstance()
		{
			static IgniteTrackSwap* GetSwapInstance;
			if (NULL == GetSwapInstance)
			{
				GetSwapInstance = new IgniteTrackSwap();
			}

			return GetSwapInstance;
		}

		std::function<void(swapCtlKey, int, int)> onButtonPressed;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void setDefaultEditTrack(int value1, int value2);
		void refreshDisplay(int value1, int value2);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);

	private:
#define TRACK_SWAP_OPTIONS_VIEW 20
		enum TrackSwapViewItemID
		{
			NO_FOCUS = 0,
			SWAP_TRACK_SOURCE,
			SWAP_TRACK_DEST,
			KEY_7,
			KEY_8,
			KEY_9,
			KEY_DEL,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_PLUS,
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_MINUS,
			KEY_0,
			KEY_B2,
			KEY_X2,
			KEY_CANCEL,
			KEY_SWAP,
			FOCUS_MAX = KEY_SWAP
		};

		uint8_t TrackSwapView[TRACK_SWAP_OPTIONS_VIEW] = { NO_FOCUS, SWAP_TRACK_SOURCE, SWAP_TRACK_DEST, /*KEY_7, KEY_8, KEY_9, KEY_DEL, KEY_4, KEY_5, KEY_6, KEY_PLUS, KEY_1, KEY_2, KEY_3, KEY_MINUS, KEY_0, KEY_B2, KEY_X2,*/ KEY_CANCEL, KEY_SWAP };
		int KeyFocusedItem = TrackSwapViewItemID::NO_FOCUS;
		CommonWarningPopUp* warnPopupPtr = nullptr;

		juce::FlexBox swapBox;

		CommonToggleButton swapStart;
		CommonToggleButton swapEnd;
		CommonButton swap;
		CommonLabel	swapTitle{ "Track Swap Value" };
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		CommonLabel swapStartLabel{"Swap Track"};
		CommonLabel swapEndLabel{ "With Track" };
		CommonButton num1{ TRANS("1") };
		CommonButton num2{ TRANS("2") };
		CommonButton num3{ TRANS("3") };
		CommonButton num4{ TRANS("4") };
		CommonButton num5{ TRANS("5") };
		CommonButton num6{ TRANS("6") };
		CommonButton num7{ TRANS("7") };
		CommonButton num8{ TRANS("8") };
		CommonButton num9{ TRANS("9") };
		CommonButton num0{ TRANS("0") };
		CommonButton plus{ TRANS("+") };
		CommonButton minus{ TRANS("-") };
		CommonButton numDelButton{ TRANS("<-") };
		CommonButton x2Button{ TRANS("x2") };
		CommonButton b2Button{ TRANS("/2") };
		CommonImageButton swapButton{ "Swap","btn-swap-267x44-default.png","btn-swap-267x44-default-hover.png","btn-swap-267x44-default-hover.png" };
		CommonImageButton cancelButton{ "Cancel","btn-cancel-267x44-default.png","btn-cancel-267x44-default-hover.png","btn-cancel-267x44-default-hover.png" };

		int stepValue{ 1 };
		int lastEnteredValue1;
		int lastEnteredValue2;
		int intermidentValue1;
		int intermidentValue2;
		bool isdecimalPressed = false;
		bool isPlusPressed = false;
		bool isMinusPressed = false;
		bool isAnyInput{ false };
		bool swapStartIsActive{ false };
		bool swapEndIsActive{ false };
		void handleArithmetic(bool isPlus, bool isMinus, int value);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTrackSwap)
	};
}