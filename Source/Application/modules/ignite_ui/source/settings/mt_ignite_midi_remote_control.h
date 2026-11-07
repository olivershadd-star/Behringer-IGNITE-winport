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
	class IgniteMidiRemoteControl :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define RMT_CTRL_MENU_VIEW 5
#define RMT_CTRL_ROW_ITEMS 3
		enum RmtCtrlMenuViewItemID
		{
			NO_FOCUS = 0,
			RMT_CTRL, //Row 1
			RMT_MIDI_PORT,
			RMT_MIDI_CHANNEL,
			RMT_SCENE_CHANGE,
			FOCUS_MAX = RMT_SCENE_CHANGE
		};
		uint8_t RmtCtrlMenuView[RMT_CTRL_MENU_VIEW] = { NO_FOCUS, RMT_CTRL, RMT_MIDI_PORT, RMT_MIDI_CHANNEL, RMT_SCENE_CHANGE };
		int KeyFocusedItem = RmtCtrlMenuViewItemID::NO_FOCUS;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();

		IgniteMidiRemoteControl();
		~IgniteMidiRemoteControl() override;

		bool remoteControlDataUpdated = false;
		IgniteControlOptions* remoteControlOptCtl = nullptr;

		void updateData();
		void enableControlButton(IgniteControlOptions::eKey key, bool state)
		{
			remoteControlOptCtl->enableKey(key, state);
		}
		void getAssets();
		static IgniteMidiRemoteControl* GetAppMidiRemoteControlInstance()
		{
			static IgniteMidiRemoteControl* GetAppMidiRemoteControlObj;
			if (NULL == GetAppMidiRemoteControlObj)
			{
				GetAppMidiRemoteControlObj = new IgniteMidiRemoteControl();
			}

			return GetAppMidiRemoteControlObj;
		}

	private:
		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;
		juce::FlexBox ctlBox3;

		CommonImageButton controlBtn{ "Remote Control","btn-remote-control-default.png","btn-remote-control-active.png","btn-remote-control-default-hover.png" };
		CommonImageButton sceneChangeBtn{ "Scene Change","toggle-scenechange-default.png","toggle-scenechange-active.png","toggle-scenechange-default-hover.png" };
		CommonLabel pgmChangeMsgLable{ "Program Change Message Assigned Control" };

		CommonNumber midiChannel{ "MIDI Channel", 1, 16, 1 };
		CommonListBox midiPort{ "MIDI Port",  {mt::Ignite::midiPortList}, 0, 4 };
		CommonPopUp* popupPtr = nullptr;
		Image imageMidiBgDefault, imageMidiBgHover, imageCntBg;
		bool isAutosave = false;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteMidiRemoteControl)
	};
};
