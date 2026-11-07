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
	class AppDnp;
	class IgniteControlOptions;

	class IgniteSongConfig :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
		IgniteSongConfig();
		~IgniteSongConfig() override;

		bool getSongConfigDataUpdateStatus() { return songConfigDataUpdated; }
		int getTapConfigValue() { return (int)tapConfig.getValue(); }
		String getInsertPosition() { return insertPosition.getSelectedValue(); }


		bool isAccidentalEnabled() { return songSettingData.accidentals; }
		bool isAutoSaveEnabled() { return songSettingData.autoSave; }
		bool isFillModeEnabled() { return songSettingData.fillModeState; }
		bool isSoloModeEnabled() { return songSettingData.soloMode; }

		void refreshSongConfig(bool isInternal);
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);

		static IgniteSongConfig* getAppSongConfigInstance()
		{
			static IgniteSongConfig* getAppSongConfigObj;
			if (NULL == getAppSongConfigObj)
			{
				getAppSongConfigObj = new IgniteSongConfig();
			}

			return getAppSongConfigObj;
		}
		IgniteControlOptions* _pSongOptCtl = nullptr;
		void getAssets();
		bool isGlobalAutosaveEnabled() { return isAutosave; };
		void isDataNeedtoEngine(bool state) { isneedtoSendEngine = state; };
	private:
		bool isneedtoSendEngine = true;
#define SONG_MENU_VIEW 7
#define SONG_OPT_VIEW 6
#define SONG_ROW_ITEMS 3
		enum songMenuViewItemID
		{
			NO_FOCUS = 0,
			AUTO_SAVE, //Row 1
			WIPE_SONGS,
			TAP_TEMPO,
			INSERT_POSITION,
			NOTE_SHARPS, // Row 3
			NOTE_FLATS,
			/*SYNC_SOURCE,
			SYNC_PORT,*/
			FOCUS_MAX = NOTE_FLATS
		};

		enum SONGCONFIG_FOCUS
		{
			SONGCONFIG_DETAIL,
			SONGCONFIG_OPTION,
		};

		enum songOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OPT_SONGLIST,
			OPT_DEFULT,
			OPT_ACTIVE_SONG,
			OP_FOCUS_MAX = OPT_ACTIVE_SONG
		};

		CommonPopUp* _pPopUpPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;

		uint8_t optionHandlerFocus = SONGCONFIG_DETAIL;
		uint8_t optionsView[SONG_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OPT_SONGLIST,OPT_DEFULT,OPT_ACTIVE_SONG,OP_FOCUS_MAX };
		uint8_t songMenuView[SONG_MENU_VIEW] = { NO_FOCUS, AUTO_SAVE, WIPE_SONGS, TAP_TEMPO, INSERT_POSITION, NOTE_SHARPS, NOTE_FLATS, /*SYNC_SOURCE, SYNC_PORT,*/ };
		int keyFocusedItem = songMenuViewItemID::NO_FOCUS;
		int optFocusedItem = OPT_UNDO;
		bool songConfigDataUpdated = false;

		CommonNumber tapConfig{ "Tap Tempo: Min Taps", 3, 5, 3 };
		CommonImageButton autoSaveBtn{ "Auto Save:off","toggle-autosave-default.png","toggle-autosave-active.png","toggle-autosave-hover.png" };
		CommonImageButton wipeSongsBtn{ "Wipe All Songs","btn-wipe-allsongs-default.png","btn-wipe-allsongs-default.png","btn-wipe-allsongs-hover.png" };
		CommonImageButton noteSharpBtn{ "Note Names as sharps","btn-notetoggle-sharps-default.png","btn-notetoggle-sharps-active.png","btn-notetoggle-sharps-default-hover.png" };
		CommonImageButton noteFlatBtn{ "Note Names as flats","btn-notetoggle-flats-default.png","btn-notetoggle-flats-active.png","btn-notetoggle-flats-default-hover.png" };
		/*CommonListBox syncSource{ "SYNC Source", 1 };
		std::vector<juce::String> syncOptions{ "INTERNAL", "SYNC-IN",  "MIDI", "USB-MIDI" };
		CommonListBox syncSourcePort{ "SYNC Port", 1 };
		std::vector<juce::String> syncMidiPorts{ "MIDI 1", "MIDI 2", "MIDI 3", "MIDI 4", "MIDI 5" };
		std::vector<juce::String> syncInvalidPorts{ "---" };
		std::vector<juce::String> syncUSBMidiPorts{ "USB:MIDI1", "USB:MIDI2", "USB:MIDI3", "USB:MIDI4", "USB:MIDI5", "USB:MIDI6", "USB:HOST" };
		*/CommonListBox insertPosition{ "Insert Position", 1 };
		Image imageActive, imageDefault, imageActiveHover, imageDefaultHover, imagedisabledImage,imageNoteToggleBg;
		bool isAutosave = false;
		juce::FlexBox songMenuBox1;

		mt::Ignite::songSettings songSettingData{ false, false, false, 0, 0 };
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void syncPortCtl(int source);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		int isEditing();
		void handlePageShift(paramId_t param, uint32_t KeyValue);
		void handleSongConfigOption(paramId_t param, uint32_t KeyValue);
		void handleKeyMovement(paramId_t param, uint32_t KeyValue, bool& setfocus);
		void handleRotaryMovement(uint32_t KeyValue);
		void handleSongConfigDetail(paramId_t param, uint32_t KeyValue, bool& setfocus, int& EditItem);
		void handleSongConfigOptionKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleSongConfigDetailKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleButtonKey(CommonImageButton& button, bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleWipeSongsKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void adjustFocus(paramId_t param);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteSongConfig)
	};
};
