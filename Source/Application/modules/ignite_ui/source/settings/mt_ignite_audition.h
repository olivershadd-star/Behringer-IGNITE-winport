/*
 * Copyright (c) - 2024 - MUSIC Tribe, MY.
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
	class IgniteAuditionSettings :
		public juce::Component,
		public IgniteControlOptions::Listener
	{
	public:
#define AUD_MENU_VIEW 18
#define AUD_ROW_ITEMS 4
#define AUD_OPT_VIEW 3
		enum AuditionViewItemID
		{
			NO_FOCUS = 0,
			PORT_1_PRESET,
			PORT_2_PRESET,
			PORT_3_PRESET,
			PORT_4_PRESET,
			PORT_5_PRESET,
			PORT_6_PRESET,
			PORT_7_PRESET,
			PORT_8_PRESET,
			PORT_9_PRESET,
			PORT_10_PRESET,
			PORT_11_PRESET,
			PORT_12_PRESET,
			PORT_13_PRESET,
			PORT_14_PRESET,
			PORT_15_PRESET,
			PORT_16_PRESET,
			PORT_17_PRESET,
			FOCUS_MAX = PORT_17_PRESET
		};
		enum AUD_FOCUS
		{
			AUD_DETAIL,
			AUD_OPTION,
		};

		enum AudOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OP_FOCUS_MAX = OPT_UNDO
		};

		uint8_t option_handler_focus = AUD_DETAIL;
		uint8_t OptionsView[AUD_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OP_FOCUS_MAX };
		int OptFocusedItem = OPT_UNDO;
		uint8_t AudMenuView[AUD_MENU_VIEW] = { NO_FOCUS, PORT_1_PRESET, PORT_2_PRESET, PORT_3_PRESET, PORT_4_PRESET,
		PORT_5_PRESET , PORT_6_PRESET , PORT_7_PRESET , PORT_8_PRESET , PORT_9_PRESET , PORT_10_PRESET , PORT_11_PRESET, PORT_12_PRESET, 
		PORT_13_PRESET, PORT_14_PRESET, PORT_15_PRESET, PORT_16_PRESET, PORT_17_PRESET };
		int KeyFocusedItem = AuditionViewItemID::NO_FOCUS;

		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();
		IgniteAuditionSettings();
		~IgniteAuditionSettings() override;
		void updateUSBMidiName();

		bool auditionConfigDataUpdated = false;
		IgniteControlOptions* auditionOptCtl = nullptr;

		void updateData();
		void enableControlButton(IgniteControlOptions::eKey key, bool state)
		{
			auditionOptCtl->enableKey(key, state);
		}

		static IgniteAuditionSettings* GetAppAuditionInstance()
		{
			static IgniteAuditionSettings* GetAppAuditionObj;
			if (NULL == GetAppAuditionObj)
			{
				GetAppAuditionObj = new IgniteAuditionSettings();
			}

			return GetAppAuditionObj;
		}

	private:
		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;
		juce::FlexBox ctlBox3;
		juce::FlexBox ctlBox4;

		std::vector<CommonListBox*> midiPresets;
		CommonPopUp* popupPtr = nullptr;
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-bg-bray-toggle-default.png"));
		Image OverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-bg-bray-toggle-default-hover.png"));

		bool isAutosave = false;
		int numberOfUSBHost = 0;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void setUsbHostVisibility();
		void handleCommandMessage(int id);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteAuditionSettings)
	};
};
