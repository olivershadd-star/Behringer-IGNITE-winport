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
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#endif


namespace ui
{
	class IgniteBRaySettings;
	class IgniteMidiRemoteControl;
	class IgniteBackup;
	class IgniteTransposeSettings;
	class IgniteGifPreloader;
	class IgniteDeviceStatus;
	class IgniteMiscSettings;
	class IgniteAuditionSettings;
	class IgniteConnectivity;

	class IgniteSettings :
		public juce::Component,
		public juce::Button::Listener,
		public CommonSlider::Listener,
		public IgniteControlOptions::Listener,
		private Timer
	{
	public:
#define SETTINGS_MENU_VIEW 11
#define SETTINGS_OPT_VIEW 3
#define SETTINGS_ROW_ITEMS 3
		enum SettingsMenuViewItemID
		{
			NO_FOCUS = 0,
			MIDI_CLK_CONFIG,
			//REMOTE_CONTROL,
			//MMC_CONFG,
			//MIDI_XPOSE_CONFIG,
			BRAY,
			AUDITION_CFG,
			DEVICE_STATUS,
			BACKUP,
			FACTORY_RESET,
			CONNECTVITY,
			MISC_SETTING,
			WIPE_UNASSIGNED_INSTRUMENS,
			BRIGHTNESS,
			//BRIGHTNESS_CTL,
			FOCUS_MAX = BRIGHTNESS
		};
		enum SETTING_FOCUS
		{
			SETTING_DETAIL,
			SETTING_OPTION,
		};

		enum SettingsOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OP_FOCUS_MAX = OPT_UNDO
		};

		uint8_t option_handler_focus = SETTING_DETAIL;
		uint8_t OptionsView[SETTINGS_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OP_FOCUS_MAX };
		int OptFocusedItem = OPT_UNDO;

		uint8_t SettingsMenuView[SETTINGS_MENU_VIEW] = { NO_FOCUS, MIDI_CLK_CONFIG, BRAY, AUDITION_CFG, DEVICE_STATUS, BACKUP, FACTORY_RESET, CONNECTVITY, MISC_SETTING, WIPE_UNASSIGNED_INSTRUMENS, BRIGHTNESS/*, BRIGHTNESS_CTL*/};
		int KeyFocusedItem = SettingsMenuViewItemID::NO_FOCUS;
		bool settingsDataUpdated = false;
		CommonPopUp* popupPtr = nullptr;
		CommonThreadWithProgressBar* progressBarPtr = nullptr;
		std::function<void(int Selection)> onSelectionChanged;
		bool isMiscSettingIsVisible() {	return miscBtn.isVisible();	}
		void enableMiscCompVisibility() { this->buttonClicked(&miscBtn); miscSettingComp->setVisible(true); }

		IgniteSettings();
		~IgniteSettings() override;
		void updateData();
		void enableControlButton(IgniteControlOptions::eKey key, bool state);
		void factoryResetPopup();
		bool initiateFirmwareUpdate(SwUdateSource_t mode);
		void startFactoryReset();
		int isEditing();
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void pcOpOngoingPopUpCtl(bool state);
		void changeFwStatus(bool status) { isSwUpdateGoing = status; };
		CommonInfoWindow* _pInfoWindow;
		void getAssets();
		void setWipeInstrumentsBtnState(bool state);
		static IgniteSettings* GetAppSettingsInstance()
		{
			static IgniteSettings* GetAppRSettingsObj;
			if (NULL == GetAppRSettingsObj)
			{
				GetAppRSettingsObj = new IgniteSettings();
			}

			return GetAppRSettingsObj;
		}

	private:
		typedef enum {
			IDLE,
			START,
			RUN,
			SUCCESS,
			FAILURE,
			DOWNLOAD,
			DONE,
			SUBPROCESS,
			PROGRESS,
		} RECOVERY_STATUS;


		enum preloaderOpType
		{
			FIRMWARE_OP,
			FACTORY_RESET_OP,
			MIDI_RESET_OP,
			INVALID
		};

		struct progress_msg {
			unsigned int    magic;          /* Magic Number */
			RECOVERY_STATUS status;         /* Update Status (Running, Failure) */
			unsigned int    dwl_percent;    /* % downloaded data */
			unsigned int    nsteps;         /* No. total of steps */
			unsigned int    cur_step;       /* Current step index */
			unsigned int    cur_percent;    /* % in current step */
			char            cur_image[256]; /* Name of image to be installed */
			char            hnd_name[64];   /* Name of running hanler */
			unsigned int    infolen;        /* Len of data valid in info */
			char            info[2048];     /* additional information about install */
		};

		String progressMessage;
		int current_screen = NO_FOCUS;
		const char* socketpath = "/tmp/swupdateprog";
		SwUdateSource_t updateSource = SwUdateSource_t::PC;

		CommonToggleButton brightnessBtn{ " " };
		CommonSlider brightnesSlider{ juce::Slider::LinearBarVertical, Slider::NoTextBox };
		CommonButton themeBtn{ "Themes" };
		//CommonImageButton mmcConfigBtn{ "MMC Configuration","btn-midi-control-config-default.png","btn-midi-control-config-default-hover.png","btn-midi-control-config-default-hover.png" };
		CommonImageButton midiClockConfigBtn{ "MIDI Clock Configuration","btn-midi-clock-default.png","btn-midi-clock-default-hover.png","btn-midi-clock-default-hover.png" };
		//CommonImageButton midiRemoteControlBtn{ "MIDI Input Remote Control","btn-midi-input-default.png","btn-midi-input-default-hover.png","btn-midi-input-default-hover.png" };
		//CommonImageButton midiTransposeBtn{ "MIDI Xpose Configuration","btn-midi-xpose-default.png","btn-midi-xpose-default-hover.png","btn-midi-xpose-default-hover.png" };
		CommonImageButton bRayBtn{ "B-Ray Control","btn-bray-control-default.png","btn-bray-control-default-hover.png","btn-bray-control-default-hover.png" };
		CommonImageButton deviceStatusBtn{ "Device Status","btn-device-status-default.png","btn-device-status-default-hover.png","btn-device-status-default-hover.png" };
		CommonImageButton factoryResetBtn{ "Factory Reset","btn-factory-reset-default.png","btn-factory-reset-default-hover.png","btn-factory-reset-default-hover.png" };
		CommonImageButton backupBtn{ "Backup","btn-backup-default.png","btn-backup-default-hover.png","btn-backup-default-hover.png" };
		CommonImageButton auditionCfgBtn{ "Audition Configuration","btn-audition-config-default.png","btn-audition-config-default-hover.png","btn-audition-config-default-hover.png" };
		CommonImageButton miscBtn{ "Misc","btn-misc-default.png","btn-misc-default-hover.png","btn-misc-default-hover.png" };
		CommonImageButton connectvityBtn{ "Connectivity","btn-connectivity-default.png","btn-connectivity-default-hover.png","btn-connectivity-default-hover.png" };
		CommonImageButton brightnessToggle{ "BrightnessToggle","brightness-toggle-option2.png","brightness-toggle-option1.png" };
		CommonButton wipeUnassignedInstrBtn{ "Wipe Unassigned Instruments" };

		juce::FlexBox settingsBox1;
		juce::FlexBox settingsBox2;
		juce::FlexBox settingsBox3;
		juce::FlexBox settingsBox4;
		juce::FlexBox settingsBox;

		IgniteControlOptions* settingsOptCtl = nullptr;
		IgniteBRaySettings* brayComp = nullptr;
		IgniteAuditionSettings* auditionComp = nullptr;
		IgniteMidiRemoteControl* midiRemoteCtrlComp = nullptr;
		IgniteBackup* backupComp = nullptr;
		IgniteMidiClkSetting* midiClkComp = nullptr;
		IgniteTransposeSettings* transposeComp = nullptr;
		IgniteMiscSettings* miscSettingComp = nullptr;
		//IgniteMidiMachineControl* mmcComp = nullptr;
		IgniteGifPreloader* settingGifcomp = nullptr;
		IgniteDeviceStatus* deviceStatusComp = nullptr;
		IgniteConnectivity* connComp = nullptr;
		IgniteCalibration* calibComp = nullptr;

		bool FactoryReset = false;
		bool Fw_Upgarde = false;
		int operationType = INVALID;
		volatile bool isSwUpdateGoing = false;
		Image imageDefault, imageActive, imageHover, imageBrigtnessKnob, imageDisabled;
		bool isAutosave = false;

		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
		void setTimeLimittoGif(int countLimit);
		void timerCallback();
		void gifPreloaderSettingPopup(String message);
		int progress_ipc_receive(int* connfd, struct progress_msg* msg);
		void setProgressStatusMessage(String message);
		int connect_ipc(bool reconnect);
		bool startFirmwareUpadate();
		CThread FwUpgardeThread;
		ThreadFunction FwUpgardeThreadFunctionCB;
		void FwUpgardeThreadFunction(void);
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteSettings)
	};
};
