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
	class IgniteMidiClkOutSetting;

	class IgniteMidiClkSetting :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define MIDICLK_MENU_VIEW 24
#define CLKBTN_RADIO_GROUP_ID 1357
		enum MidiClkMenuViewItemID
		{
			NO_FOCUS = 0,
			CLOCK_INPUT,
			CLOCK_OUTPUT,
			CLOCK_INTMODE,
			CLOCK_EXTMODE,
			MIDI_PORT1,
			MIDI_PORT2,
			MIDI_PORT3,
			MIDI_PORT4,
			MIDI_PORT5,
			MIDI_USBPORT1,
			MIDI_USBPORT2,
			MIDI_USBPORT3,
			MIDI_USBPORT4,
			MIDI_USBPORT5,
			MIDI_USBPORT6,
			MIDI_USB_HOSTPORT1,
			MIDI_USB_HOSTPORT2,
			MIDI_USB_HOSTPORT3,
			MIDI_USB_HOSTPORT4,
			MIDI_USB_HOSTPORT5,
			MIDI_SYNCPORT,
			MIDI_SYNCRATE,
			MIDI_SYNC_START,
			FOCUS_MAX = MIDI_SYNC_START
		};
		uint8_t BackupMenuView[MIDICLK_MENU_VIEW] = { NO_FOCUS, CLOCK_INPUT, CLOCK_OUTPUT, CLOCK_INTMODE, CLOCK_EXTMODE, 
			MIDI_PORT1, MIDI_PORT2,	MIDI_PORT3, MIDI_PORT4, MIDI_PORT5, 
			MIDI_USBPORT1, MIDI_USBPORT2, MIDI_USBPORT3, MIDI_USBPORT4, MIDI_USBPORT5, MIDI_USBPORT6, 
			MIDI_USB_HOSTPORT1, MIDI_USB_HOSTPORT2, MIDI_USB_HOSTPORT3, MIDI_USB_HOSTPORT4, MIDI_USB_HOSTPORT5,
			MIDI_SYNCPORT, MIDI_SYNCRATE, MIDI_SYNC_START };
		int KeyFocusedItem = MidiClkMenuViewItemID::NO_FOCUS;

		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();
		IgniteMidiClkSetting();
		~IgniteMidiClkSetting() override;

		bool clkConfigDataUpdated = false;
		IgniteControlOptions* midiClkOptCtl = nullptr;

		void updateData();
		void setEditIndication();
		void enableControlButton(IgniteControlOptions::eKey key, bool state)
		{
			midiClkOptCtl->enableKey(key, state);
		}

		static IgniteMidiClkSetting* GetAppMidiClkInstance()
		{
			static IgniteMidiClkSetting* GetAppMidiClkObj;
			if (NULL == GetAppMidiClkObj)
			{
				GetAppMidiClkObj = new IgniteMidiClkSetting();
			}

			return GetAppMidiClkObj;
		}
		void getAssets();
	private:
		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;
		juce::FlexBox ctlBox3;

		CommonNameLabel modeLable{ "Mode" };
		CommonNameLabel midiPortLable{ "MIDI" };
		CommonNameLabel usbPortLable{ "USB" };
		CommonNameLabel usbHPortLable{ "HUSB" };
		CommonNameLabel syncPortLable{ "Sync" };
		CommonNameLabel clkRateLable{ "Rate:" };
		CommonNameLabel startLable{ "Start:" };

		CommonImageButton intModeBtn{ "Internal Clock","clockmode-internal-default.png","clockmode-internal-active.png","clockmode-internal-default-hover.png" };
		CommonImageButton extModeBtn{ "External Clock","clockmode-external-default.png","clockmode-external-active.png","clockmode-external-default-hover.png" };
		CommonImageButton mport1Btn{ "MIDI Port 1","clocksetting-number-1-default.png","clocksetting-number-1-active.png","clocksetting-number-1-hover.png" };
		CommonImageButton mport2Btn{ "MIDI Port 2","clocksetting-number-3-default.png","clocksetting-number-2-active.png","clocksetting-number-2-hover.png" };
		CommonImageButton mport3Btn{ "MIDI Port 3","clocksetting-number-3-default-1.png","clocksetting-number-3-active.png","clocksetting-number-3-hover.png" };
		CommonImageButton mport4Btn{ "MIDI Port 4","clocksetting-number-4-default.png","clocksetting-number-4-active.png","clocksetting-number-4-hover.png" };
		CommonImageButton mport5Btn{ "MIDI Port 5","clocksetting-number-5-default.png","clocksetting-number-5-active.png","clocksetting-number-5-hover.png" };
		CommonImageButton uport1Btn{ "USB Port 1","clocksetting-number-1-default.png","clocksetting-number-1-active.png","clocksetting-number-1-hover.png" };
		CommonImageButton uport2Btn{ "USB Port 2","clocksetting-number-3-default.png","clocksetting-number-2-active.png","clocksetting-number-2-hover.png" };
		CommonImageButton uport3Btn{ "USB Port 3","clocksetting-number-3-default-1.png","clocksetting-number-3-active.png","clocksetting-number-3-hover.png" };
		CommonImageButton uport4Btn{ "USB Port 4","clocksetting-number-4-default.png","clocksetting-number-4-active.png","clocksetting-number-4-hover.png" };
		CommonImageButton uport5Btn{ "USB Port 5","clocksetting-number-5-default.png","clocksetting-number-5-active.png","clocksetting-number-5-hover.png" };
		CommonImageButton uport6Btn{ "USB Port 6","clocksetting-number-6-default.png","clocksetting-number-6-active.png","clocksetting-number-6-hover.png" };
		CommonImageButton sportBtn{ "Sync Port","clock-in-default.png","clock-in-active.png","clock-in-hover.png" };
		CommonImageButton sOutportBtn{ "Sync Out Port","clock-out-default.png","clock-out-active.png","clock-out-hover.png" };
		CommonImageButton intBtn{ "Sync Port","clock-in-default.png","clock-in-active.png","clock-in-hover.png" };
		CommonImageButton clockInbtn{ "Clock In","btn-clockin-settings-default.png","btn-clockin-settings-active.png","btn-clockin-settings-default-hover.png" };
		CommonImageButton clockOutbtn{ "Clock Out","btn-clockout-settings-default.png","btn-clockout-settings-active.png","btn-clockout-settings-default-hover.png" };
		CommonButton uhport1Btn{ "USB HOST1" };
		CommonButton uhport2Btn{ "USB HOST2" };
		CommonButton uhport3Btn{ "USB HOST3" };
		CommonButton uhport4Btn{ "USB HOST4" };
		CommonButton uhport5Btn{ "USB HOST5" };
		CommonListBox syncClk{ "Clock Rate",  {"1 PP16", "1 PP8", "1 PPQ", "1 PP2Q", "1 PP4Q", "2 PPQ", "24 PPQ", "48 PPQ"}, 0, 2 };
		CommonListBox syncOutClk{ "Clock Out Rate",  {"1 PP16", "1 PP8", "1 PPQ", "1 PP2Q", "1 PP4Q", "2 PPQ", "24 PPQ", "48 PPQ"}, 0, 2 };
		CommonListBox syncTrigger{ "START",  {"ON CLOCK", "ON GATE"}, 0, 1 };

		Image clkBgdefaultImage, clkRatedefaultImage, clkRatehoverImage, husbDeafultImage, husbDeafultHoverImage, husbActiveImage, husbActiveHoverImage;
		CommonPopUp* popupPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;

		bool isClockInputMode = true;
		bool isIntClockMode = true;
		bool isAutosave = false;	
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) override;
		void changeVisibility();
		void autoSaveData();
		void updatePortSelection(int port, bool state);
		void setUsbHostVisibility();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteMidiClkSetting)
	};
};
