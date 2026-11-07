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
	class IgniteSongRow;
	class AppSongView;
	class IgniteSceneRow;
	class AppDnp;

	class IgniteSong :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener,
		public juce::DragAndDropContainer
	{
	public:
		IgniteSong();
		~IgniteSong() override;

		int getSelected(void);
		var getSongData(mt::Ignite::songsDataIndex itemId);
		mt::Ignite::songData* getSongDataPtr();
		int getCurrentSongRow() { return curretSongRow; }
		bool getFillMode(void);
		String getEditSceneName();
		String getCurrentSceneName();
		String getNextSceneName();
		int getActiveTracks();
		int getActiveTracksNext();
		juce::OwnedArray<ui::IgniteSceneRow>* getSceneList();
		int getViewStatus();
		mt::Ignite::sceneData* getSceneData(int sceneIndex);
		String getSongName();
		bool getSongDataUpdateStatus() { return songDataUpdated; }
		bool getSongMoveState() { return moveEnabled; }
		int8_t getOptionHandlerState() { return optionHandlerEnabled; }
		bool getGlobalSwingState() { return globalSwing; }
		bool getGlobalTempoState() { return globalTempo; }

		void setSongDataUpdateStatus(bool state) { songDataUpdated = state; }
		void setSongMoveState(bool state) { moveEnabled = state; }
		void setSelected(int index, bool force_update = false);
		void setSongData(mt::Ignite::songsDataIndex itemId, uint8_t value, bool isInternal);
		void setSongData(mt::Ignite::songsDataIndex itemId, int value, bool isInternal);
		void setSongData(mt::Ignite::songsDataIndex itemId, String value, bool isInternal);
		void setSongData(mt::Ignite::songsDataIndex itemId, float data, bool isInternal, bool isPlayModeData = false);
		void setSongData(mt::Ignite::songsDataIndex itemId, bool data, bool isInternal);
		void setCurrentSongRow(int value) { curretSongRow = value; }
		void setEditIndication(bool state);
		void setCurrentEditSceneEditTrack();
		void setGlobalSwingState(bool state) { globalSwing = state; }
		void setGlobalTempoState(bool state) { globalTempo = state; }

		void updateSongData(uint8_t param, const uint8_t value);
		void updateSongData(uint8_t param, const uint32_t value);
		void updateSongData(uint8_t param, const float value);
		void updateSongData(uint8_t param, const std::string& value);
		void updateSongGlobalTempoToScenes(float data);
		void updateSongGlobalSwingToScenes(uint8_t data);

		void changeSongOptionsVisibility(bool bShouldShow);
		bool isSongCreated(void) { return(songCreated); }
		bool isSongSetupComplete();
		bool isTrackConfigured(int trackId);
		void refreshSongUI(bool forceRefresh = false);

		void updateDataFromEngine();

		void deleteAllSongs();
		void moveSong(juce::Point<float> position);
		void moveSong(int index);
		void saveGlobalSongDataOfScenes();
		void updateLables();

		void enableControlButton(IgniteControlOptions::eKey key, bool state);
		mt::Ignite::sceneData* addSceneData(mt::Ignite::sceneData& scData);
		void addToSceneList(juce::OwnedArray<ui::IgniteSceneRow>* sceneArray);
		void removeScenesFromList();
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		void setFpSongLedState();
		bool isGlobalAutosaveEnabled() { return isAutosave; };
		void getAssets();
		CommonPopUp* _pPopUpPtr = nullptr;
		AppSongView* _pSongView = nullptr;
		AppMainmode* mainmodePtr = nullptr;

		static IgniteSong* getAppSongInstance()
		{
			static IgniteSong* appSongInstance;
			if (NULL == appSongInstance)
			{
				appSongInstance = new IgniteSong();
			}

			return appSongInstance;
		}
		
	private:
#define OPTIONS_VIEW 11
		enum optionsViewItemID
		{
			NO_FOCUS = 0,
			SONG_MOVE_DOWN,
			SONG_MOVE_UP,
			SONG_MOVE_TOP,
			SONG_MOVE_LAST,
			SONG_MOVE,
			SONG_UNDO,
			SONG_COPY,
			SONG_CONFIG,
			SONG_MIDI_CONFIG,
			SONG_CV_CONFIG,
			FOCUS_MAX = SONG_CV_CONFIG
		};

		AppDnp* _pEmptySongComp = nullptr;
		IgniteControlOptions* _pSongOptCtl = nullptr;
		IgniteCopy* _pSongCopyComp = nullptr;
		AppOptions* _pAppOptPtr = nullptr;

		juce::FlexBox box;
		juce::FlexBox viewBox;
		CommonImageButton songsView{ "Song View","btn-song-detail-default.png","btn-song-detail-active.png","btn-song-detail-default-hover.png" };
		CommonImageButton listView{ "List View","btn-song-list-default.png","btn-song-list-active.png","btn-song-list-default-hover.png" };
		CommonButton addNew{ "" };
		CommonImageButton addNewInList{ "+ Add New Song","btn-add-newsong-default.png","btn-add-newsong-active.png","btn-add-newsong-hover.png" };
		CommonLabel playTime{ "Time: " };

		mt::Ignite::songData prevSongData{ 0 };
		juce::Viewport view;
		juce::Component container;
		juce::OwnedArray<IgniteSongRow> list;

		int listFocused = -1;
		int currentScene = 0, nextScene = 0;
		int sceneActiveTracks = 0;
		int nextSceneActiveTracks = 0;
		uint8_t timeSeconds = 0;
		uint8_t timeMinutes = 0;
		uint8_t timeHours = 0;
		bool optionHandlerEnabled = false;
		bool addNewInListHiglited = false;
		paramId_t itemParam;
		uint32_t itemkeyValue;
		bool itemFocus = false;
		bool songCreated = false;
		bool songDataUpdated = false;
		bool bootupState = true;
		int curretSongRow = 0;
		bool moveEnabled = false;
		bool isAutoSaveEnbaled = false;
		bool globalSwing = false;
		bool globalTempo = false;
		int keyFocusedItem = optionsViewItemID::NO_FOCUS;
		uint8_t optionsView[OPTIONS_VIEW] = { NO_FOCUS, SONG_MOVE_DOWN, SONG_MOVE_UP, SONG_MOVE_TOP, SONG_MOVE_LAST, SONG_MOVE, SONG_UNDO, SONG_COPY, SONG_CONFIG, SONG_MIDI_CONFIG, SONG_CV_CONFIG };
		int selected{ 0 };
		int prevSelected{ -1 };
		int currentSongBank = 0;
		bool isAutosave = false;
		Image imageaAddNewInListDefault, imageaAddNewInListHover, songsDetailDefaultHover, songsDetailActiveHover, songsDetaiDisabledHover, songsListDefaultHover, songsListActiveHover, songsListDisabledHover, imageEmptyBg;
		Image imageSongDetailDefault, imageSongDetailActive, imageSongDetailHover, imageSongListDefault, imageSongListActive, imageSongListHover;
		void cleanup();
		void populate(int songIndex);
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) override;
		void setDefaultSongData();
		void updateSelectionInfo(void);
		void showPopup(int index);
		void enableViewBox(bool state);
		void copySong(IgniteCopy::copyCtlKey key, String copyName);
		void resetStatusBarPlayInfo();
		void requestDataFromEngine(int index);
		void addSong(int songIndex);
		void deleteCurrentSong();
		void deleteSong();
		void saveSong();
		void triggerButtonEvent(int index);
		void handleCommandMessage(int id);
		bool PannelKeyOptionsHandler(paramId_t param, uint32_t keyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteSong)
	};

	class IgniteSongRow :
		public juce::Component,
		public juce::Label::Listener
	{
	public:
		IgniteSongRow(int SerialNumber, mt::Ignite::songData& Data, IgniteSong* _pOwnerptr);
		~IgniteSongRow();
		std::function<void(IgniteSongRow*)> onMouseDown;
		void highlight(bool state);
		int getSerialNumber();
		void refreshSongRowUI();
		void setFocus(bool hasFocus, bool hasActiveFoces);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		bool isEditing() { return name.isEditing; }
		void getAssets();

	private:
		IgniteSong* _pSong = nullptr;
		mt::Ignite::songData& songdata;
		juce::FlexBox box;
		CommonSerialNumber srNo{ "1" };
		String serialNumber = "1";
		CommonKey name{ "" };
		CommonLabel songState{ "INACTIVE" };
		int serialNo;
		bool rowIsBeingDraggedOver = false;
		bool isHighlighted{ false };
		bool isMouseOver{ false };
		Image imageSongRowActiveHover, imageSongRowActiveDefault, imageSongRowinActiveHover, imageSongRowinActiveDefault;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		void mouseUp(const MouseEvent& event) override;
		void mouseDown(const MouseEvent& event) override;
		void mouseDrag(const MouseEvent& event) override;
		void labelTextChanged(Label* labelThatHasChanged) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteSongRow)
	};
};
