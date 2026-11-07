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
	class IgniteMidiMachineControl :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define MMC_MENU_VIEW 7
#define MMC_ROW_ITEMS 4
		enum MMCMenuViewItemID
		{
			NO_FOCUS = 0,
			MMC_RX_CTRL,
			MMC_MIDI_RX_PORT,
			MMC_MIDI_RX_DEVID,
			MMC_MIDI_RX_DEVALL,
			MMC_TX_CTRL,
			MMC_MIDI_TX_PORT,
			FOCUS_MAX = MMC_MIDI_TX_PORT
		};
		uint8_t MMCMenuView[MMC_MENU_VIEW] = { NO_FOCUS, MMC_RX_CTRL, MMC_MIDI_RX_PORT, MMC_MIDI_RX_DEVID, MMC_MIDI_RX_DEVALL, MMC_TX_CTRL, MMC_MIDI_TX_PORT };
		int KeyFocusedItem = MMCMenuViewItemID::NO_FOCUS;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();

		IgniteMidiMachineControl();
		~IgniteMidiMachineControl() override;

		bool mmcDataUpdated = false;
		IgniteControlOptions* mmcOptCtl = nullptr;

		void updateData();
		void enableControlButton(IgniteControlOptions::eKey key, bool state)
		{
			mmcOptCtl->enableKey(key, state);
		}

		static IgniteMidiMachineControl* GetAppMidiMachineControlInstance()
		{
			static IgniteMidiMachineControl* GetAppMidiMachineControlObj;
			if (NULL == GetAppMidiMachineControlObj)
			{
				GetAppMidiMachineControlObj = new IgniteMidiMachineControl();
			}

			return GetAppMidiMachineControlObj;
		}

	private:
		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;

		CommonImageButton mmcTxBtn{ "MMC Send: Off","toggle-mmc-send-off-default.png","toggle-mmc-send-on-active.png","toggle-mmc-send-off-hover.png" };
		CommonImageButton mmcRxBtn{ "MMC Receive: Off" ,"toggle-mmc-receive-off-default.png","toggle-mmc-receive-on-active.png","toggle-mmc-receive-off-hover.png" };
		CommonImageButton mmcRxAll{ "MMC Receive from All" ,"btn-mmc-all-default.png","btn-mmc-all-active.png","btn-mmc-all-default-hover.png" };

		CommonNumber midiRxChannel{ "MIDI Device Id", 0, 127, 1 };
		CommonListBox midiRxPort{ "MIDI RX Port",  {"MIDI_PORT_0","MIDI_PORT_1", "MIDI_PORT_2", "MIDI_PORT_3", "MIDI_PORT_4"}, 0, 1};
		CommonListBox midiTxPort{ "MIDI TX Port",  {"MIDI_PORT_0","MIDI_PORT_1", "MIDI_PORT_2", "MIDI_PORT_3", "MIDI_PORT_4"}, 0, 1 };

		CommonPopUp* popupPtr = nullptr;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteMidiMachineControl)
	};
};
