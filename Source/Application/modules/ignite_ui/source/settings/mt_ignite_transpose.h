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
	class IgniteTransposeSettings :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define XPOSE_MENU_VIEW 6
#define XPOSE_ROW_ITEMS 3
		enum XposeMenuViewItemID
		{
			NO_FOCUS = 0,
			XPOSE_CTL,
			LATCH_MODE,
			XPOSE_PORT,
			XPOSE_CHANNEL,
			CENTER_PITCH,
			FOCUS_MAX = CENTER_PITCH
		};
		uint8_t XposeMenuView[XPOSE_MENU_VIEW] = { NO_FOCUS, XPOSE_CTL, LATCH_MODE, XPOSE_PORT, XPOSE_CHANNEL, CENTER_PITCH };
		int KeyFocusedItem = XposeMenuViewItemID::NO_FOCUS;

		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();
		IgniteTransposeSettings();
		~IgniteTransposeSettings() override;

		bool transposeConfigDataUpdated = false;
		IgniteControlOptions* transposeOptCtl = nullptr;

		void updateData();
		void enableControlButton(IgniteControlOptions::eKey key, bool state)
		{
			transposeOptCtl->enableKey(key, state);
		}
		void getAssets();

		static IgniteTransposeSettings* GetAppTransposeInstance()
		{
			static IgniteTransposeSettings* GetAppTransposeObj;
			if (NULL == GetAppTransposeObj)
			{
				GetAppTransposeObj = new IgniteTransposeSettings();
			}

			return GetAppTransposeObj;
		}

	private:
		juce::FlexBox ctlBox2;
		bool isAutosave = false;
		CommonImageButton controlBtn{ "MIDI Xpose","btn-toggle-midi-xpose-default.png","btn-toggle-midi-xpose-active.png","btn-toggle-midi-xpose-default-hover.png" };
		CommonImageButton latchBtn{ "LATCH Mode","btn-latch-mode-default.png","btn-latch-mode-active.png","btn-latch-mode-default-hover.png" };
		CommonListBox midiPorts{ "Port", mt::Ignite::midiPortList, 0, 3 };
		CommonNumber midiChannel{ "Channel", 1, 16, 1 };
		CommonNumber centerPitch{ "Center-Pitch", 0, 127, 1 };
		CommonPopUp* popupPtr = nullptr;
		Image imageDefault, imageHover;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void controlButtonState(bool state);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTransposeSettings)
	};
};
