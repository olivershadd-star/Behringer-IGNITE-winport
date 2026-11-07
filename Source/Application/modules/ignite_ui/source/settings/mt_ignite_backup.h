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
	class IgniteGifPreloader;
	class IgniteBackup :
		public juce::Component,
		public juce::Button::Listener,
		private Timer
	{
	public:
#define Backup_MENU_VIEW 8
#define Backup_ROW_ITEMS 3
		enum BackupMenuViewItemID
		{
			NO_FOCUS = 0,
			FULL_BACKUP,
			SONG_BACKUP,
			PATTERN_BACKUP,
			INSTRUMENT_BACKUP,
			//MIDI_CONFIG_BACKUP,
			//CV_AND_GATE_BACKUP,
			SETTINGS_BACKUP,
			FOCUS_MAX = SETTINGS_BACKUP
		};
		uint8_t BackupMenuView[Backup_MENU_VIEW] = { NO_FOCUS, FULL_BACKUP, SONG_BACKUP, PATTERN_BACKUP, INSTRUMENT_BACKUP, /*MIDI_CONFIG_BACKUP, CV_AND_GATE_BACKUP,*/ SETTINGS_BACKUP };
		int KeyFocusedItem = BackupMenuViewItemID::NO_FOCUS;

		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();
		IgniteBackup();
		~IgniteBackup() override;
		static IgniteBackup* GetAppBackupInstance()
		{
			static IgniteBackup* GetAppBackupObj;
			if (NULL == GetAppBackupObj)
			{
				GetAppBackupObj = new IgniteBackup();
			}

			return GetAppBackupObj;
		}

	private:
		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;
		juce::FlexBox ctlBox3;

		CommonImageButton fullBackupBtn{ "Full Backup Save/Restore","selection-fullbackup-default.png","selection-fullbackup-default-hover.png","selection-fullbackup-default-hover.png" };
		CommonImageButton songBackupBtn{ "Song Backup Save/Restore","selection-songbackup-default.png","selection-songbackup-default-hover.png","selection-songbackup-default-hover.png" };
		CommonImageButton instrumentBackupBtn{ "Instrument Backup Save/Restore","selection-instbackup-default.png","selection-instbackup-default-hover.png","selection-instbackup-default-hover.png" };
		//CommonImageButton midiConfigBackupBtn{ "MIDI Config Backup Save/Restore","selection-midibackup-default.png","selection-midibackup-default-hover.png","selection-midibackup-default-hover.png" };
		CommonImageButton patternBackupBtn{ "Pattern Backup Save/Restore","selection-patternbackup-default.png","selection-patternbackup-default-hover.png","selection-patternbackup-default-hover.png" };
		CommonImageButton settingsBackupBtn{ "Settings Backup Save/Restore","selection-settingsbackup-default.png","selection-settingsbackup-default-hover.png","selection-settingsbackup-default-hover.png" };
		//CommonImageButton cvAndGateBackupBtn{ "CV & Gate Backup Save/Restore","selection-cvgatebackup-default.png","selection-cvgatebackup-default-hover.png","selection-cvgatebackup-default-hover.png" };

		String progressMessage;
		CommonPopUp* popupPtr = nullptr;
		CommonPopUp* optPopupPtr = nullptr;
		IgniteGifPreloader* backUpgifcomp = nullptr;

		std::string igniteDataDir = "/data/ignite/Ignite_Files/";
		std::string backupInputDir = "Ignite_folder_backup/";
		std::string rawBackupDir = "/data/ignite/Ignite_Files/Ignite_folder_backup/";
		std::string outputDir = "/mnt/flash/";

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void backupPopup(String name);
		void setTimeLimittoGif(int countLimit);
		void timerCallback();
		void encryptBackupAndSave(int item);
		void decryptBackupAndRestore(int item);
		void handleCommandMessage(int id);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteBackup)
	};
};
