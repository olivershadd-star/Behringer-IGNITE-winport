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
	class IgniteTest;
	class IgniteGifPreloader;
	class IgniteCalibration;

	class IgniteMiscSettings :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener,
		private Timer
	{
	public:
		enum eSave {
			SAVEALL,
			AUTOSAVE
		};

#define MISC_SETTING_TEST_DATA 1
#define MISC_SETTINGS_MENU_VIEW 9
#define MISC_SETTINGS_OPT_VIEW 3
#define MISC_SETTINGS_ROW_ITEMS 3
		enum MiscSettingsMenuViewItemID
		{
			NO_FOCUS = 0,
			GLOBAL_SAVE,
			GLOBAL_AUTO_SAVE,
			MIDI_RESET,
			SAFE_STOP,
			USB_STOP,
			CV_GATE_CALLIB,
			SYSTEM_LOG,
			TEST_CFG,
			FOCUS_MAX = SYSTEM_LOG
		};
		enum MISC_SETTING_FOCUS
		{
			MISC_SETTING_DETAIL,
			MISC_SETTING_OPTION,
		};

		enum MiscSettingsOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OP_FOCUS_MAX = OPT_UNDO
		};

		uint8_t option_handler_focus = MISC_SETTING_DETAIL;
		uint8_t OptionsView[MISC_SETTINGS_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OP_FOCUS_MAX };
		int OptFocusedItem = OPT_UNDO;
		uint8_t MiscSettingsMenuView[MISC_SETTINGS_MENU_VIEW] = { NO_FOCUS, GLOBAL_SAVE, GLOBAL_AUTO_SAVE, MIDI_RESET, SAFE_STOP, USB_STOP, CV_GATE_CALLIB, SYSTEM_LOG };
		int KeyFocusedItem = MiscSettingsMenuViewItemID::NO_FOCUS;
		bool miscSettingsDataUpdated = false;
		CommonPopUp* popupPtr = nullptr;
		bool isAutosave = false;

		IgniteMiscSettings();
		~IgniteMiscSettings();
		void updateData();
		void enableControlButton(IgniteControlOptions::eKey key, bool state);
		void midiResetPopup();
		void systemLogPopup();
		int isEditing();
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void usbStopKeyPress() { buttonClicked(&usbStopBtn); }

		static IgniteMiscSettings* GetAppSettingsInstance()
		{
			static IgniteMiscSettings* GetAppMiscSettingsObj;
			if (NULL == GetAppMiscSettingsObj)
			{
				GetAppMiscSettingsObj = new IgniteMiscSettings();
			}

			return GetAppMiscSettingsObj;
		}
	private:
		int current_screen = NO_FOCUS;
		CommonToggleButton brightnessBtn{ " " };
		CommonSlider brightnesSlider{ juce::Slider::LinearBarVertical, Slider::NoTextBox };
		CommonButton themeBtn{ "Themes" };
		CommonImageButton midiResetBtn{ "MIDI Reset","btn-midi-reset-default.png","btn-midi-reset-default-hover.png","btn-midi-reset-default-hover.png" };
		CommonImageButton usbStopBtn{ "USB Stop","toggle-usbstop-off-default.png","toggle-usbstop-on-active.png","toggle-usbstop-off-hover.png" };
		CommonImageButton safeStopBtn{ "Safe Stop","toggle-safestop-off-default.png","toggle-safestop-on-active.png","toggle-safestop-on-hover-1.png" };
		CommonImageButton calibBtn{ "CV & Gate Calibration","btn-cvgate-calibration-default.png","btn-cvgate-calibration-default-hover.png","btn-cvgate-calibration-default-hover.png" };
		CommonImageButton globalSaveBtn{ "Save As Save All","toggle-saveas-default.png","toggle-saveas-active.png","toggle-saveas-hover-1.png" };
		CommonImageButton autoSaveCfgBtn{ "Auto Save All","toggle-autosave-all-default.png","toggle-autosave-all-active.png","toggle-autosave-hover-1.png" };
		CommonImageButton systemLogBtn{ "System Log","btn-systemlog-default.png","btn-systemlog-default-hover.png","btn-systemlog-default-hover.png" };

#if ENABLE_HARDWARE_TEST
		CommonButton testDataManagerBtn{ "Test Data Mgmt" };
		IgniteTest* testComp = nullptr;
#endif
		juce::FlexBox settingsBox1;
		juce::FlexBox settingsBox2;
		juce::FlexBox settingsBox;

		IgniteControlOptions* miscSettingsOptCtl = nullptr;
		bool midiReset = false;
		bool usbConnectionStatus = false;
		//int operationType = INVALID;
		IgniteCalibration* calibComp = nullptr;
		CommonInfoWindow* _pInfoWindow;

		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void setTimeLimittoGif(int countLimit);
		void timerCallback();
		void gifPreloaderSettingPopup(String message);
		IgniteControlOptions* optPtr = nullptr;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteMiscSettings)
	};


};


