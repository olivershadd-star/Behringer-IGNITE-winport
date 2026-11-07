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
	class IgniteBRaySettings :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define BRAY_MENU_VIEW 7
#define BRAY_ROW_ITEMS 3
		enum BrayMenuViewItemID
		{
			NO_FOCUS = 0,
			BRAY_CTL, //Row 1
			CC_CTL,
			PITCHBEND_CTL,
			AFTTOUCH_CTL,
			VELOCITY_CTL,
			CC_LIST,
			FOCUS_MAX = CC_LIST
		};
		uint8_t BrayMenuView[BRAY_MENU_VIEW] = { NO_FOCUS, BRAY_CTL, CC_CTL, PITCHBEND_CTL, AFTTOUCH_CTL, VELOCITY_CTL, CC_LIST };
		int KeyFocusedItem = BrayMenuViewItemID::NO_FOCUS;

		IgniteBRaySettings();
		~IgniteBRaySettings() override;

		bool brayConfigDataUpdated = false;
		IgniteControlOptions* brayOptCtl = nullptr;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void enableBray() { buttonClicked(&controlBtn); }
		void updateData();
		void enableControlButton(IgniteControlOptions::eKey key, bool state)
		{
			brayOptCtl->enableKey(key, state);
		}
		void getAssets();

		static IgniteBRaySettings* GetAppBrayInstance()
		{
			static IgniteBRaySettings* GetAppBrayObj;
			if (NULL == GetAppBrayObj)
			{
				GetAppBrayObj = new IgniteBRaySettings();
			}

			return GetAppBrayObj;
		}

	private:
		CommonLabel brayLable{ "B-RAY Control" };
		CommonLabel controlLable{ "Assigned Control" };

		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;

		CommonImageButton controlBtn{ "B-Ray:Off","btn-bray-off-default.png","btn-bray-on-default.png","btn-bray-off-hover.png"};
		CommonImageButton ccBtn{ "CC-Control","toggle-cccontrol-default.png","toggle-cccontrol-active.png","toggle-cccontrol-default-hover.png" };
		CommonImageButton afterTouchBtn{ "AfterTouchControl","toggle-aftertouch-default.png","toggle-aftertouch-active.png","toggle-aftertouch-default-hover.png" };
		CommonImageButton pitchBendBtn{ "PitchBendControl","toggle-pitch-default.png","toggle-pitch-active.png","toggle-pitch-default-hover.png" };
		CommonImageButton veloCtlBtn{ "VelocityControl","toggle-velocontrol-default.png","toggle-velocontrol-active.png","toggle-velocontrol-default-hover.png" };
		CommonListBox ccList{ "CCListControl",  {mt::Ignite::midiccVal}, 0, 4 };
		Image imageControlDefault, imageCCcontrolDefault, imageCCcontrolHover;
		CommonPopUp* popupPtr = nullptr;
		bool isAutosave = false;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		int isEditing();
		void handleCommandMessage(int id);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteBRaySettings)
	};
};
