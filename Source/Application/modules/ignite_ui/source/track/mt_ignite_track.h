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
	class AppTrackOpt;
	class IgniteTrackGrid;
	class IgniteInstrument;
	class IgniteTrackValues;
	class TrackValueSelection;
	class IgniteTrackSwap;
	class IgniteRecordModale;

	class IgniteTrack :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener,
		private Timer
	{
	public:
		enum class trackScreenIndex
		{
			TRACK_WINDOW,
			OPTION_WINDOW,
			INSTR_WINDOW,
			TRACKVALUE_WINOW,
			WINOW_INVALID,
		};
		IgniteTrack();
		~IgniteTrack() override;

		bool trackCreated = false;
		bool trackDataUpdated = false;
		bool instrumentDataUpdated = true;
		bool patternDataUpdated = true;
		bool isTrackNumberChanged = false;
		bool trackSwapActive = false;
		bool bootup_state = true;
		bool isTrackMuteChanged = false;
		bool isTrackSoloChanged = false;

		TrackValueSelection* trackValueSelectPtr = nullptr;
		IgniteControlOptions* trackOptCtlPtr = nullptr;
		AppTrackOpt* _pChild = nullptr;

		void setTrackSoloDirtyFlag(bool dirty) { isTrackSoloChanged = dirty; }
		bool getTrackSoloDirtyFlag() { return isTrackSoloChanged; }
		void setTrackMuteDirtyFlag(bool dirty) { isTrackMuteChanged = dirty; }
		bool getTrackMuteDirtyFlag() { return isTrackMuteChanged; }
		void setInstrDataDirtyFlag(bool dirty) { instrumentDataUpdated = dirty; }
		bool getInstrDataDirtyFlag() { return instrumentDataUpdated; }
		void setPatternDataDirtyFlag(bool dirty) { patternDataUpdated = dirty; }
		bool getPatternDataDirtyFlag() { return patternDataUpdated; }
		void noOfTrackChaged(bool dirty) { isTrackNumberChanged = dirty; }
		bool isNumberofTrackChanged() { return isTrackNumberChanged; }
		void addTracks(mt::Ignite::sceneData& data);
		void updateNumOfTracks(mt::Ignite::sceneData& data);
		void changeTrackOptionsVisibility(trackScreenIndex index);
		trackScreenIndex getTraKVisibleTab() { return Currentindex; };
		void updateTrackData(uint8_t param, const std::string& value);
		void setTrackData(mt::Ignite::trackDataIndex item_id, int data, bool is_internal, int currentTrack = -1);
		void setTrackData(mt::Ignite::trackDataIndex item_id, String data, bool is_internal);
		var getTrackData(mt::Ignite::trackDataIndex item_id);
		bool isTrackCreated(void) { return(trackCreated); }
		void deleteCurrentTrack();
		void refreshTrackUI();
		void updateTrackDataList();
		void getNextTrackBankAndUpdate(bool direction);
		void updateSelectionInfo(void);
		void updateSelectedPattern();
		void setCurrentTrackData(int currentTrack = -1);
		void updateDataFromEngine();
		void updateCurrentTrackDataFromEngine(int index = -1);
		void enableControlButton(IgniteControlOptions::eKey key, bool state) { trackOptCtlPtr->enableKey(key, state); };
		void swapTrack(IgniteTrackSwap::swapCtlKey key, int index1, int index2);
		void updateTrackData(uint8_t param, uint8_t value);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		int getTotalTrackBank() { return numOfTrackBanks; }
		void updateLables();
		void saveTrack();
		bool isEditing();
		int getViewStatus();
		void setCurrentTrackBank(int trackBank) { currentTrackBank = trackBank; }
		void getTrackBankAndUpdate(int trackBank);
		bool isGlobalAutosaveEnabled() { return isAutosave; };
		void setActiveBarID(int barId, int stepId) { activeBarId = barId; activeStepId = stepId; }
		static IgniteTrack* GetAppTrackInstance()
		{
			static IgniteTrack* GetTrackInstance;
			if (NULL == GetTrackInstance)
			{
				GetTrackInstance = new IgniteTrack();
			}

			return GetTrackInstance;
		}

	private:
#define TRACK_VIEW 5
		enum TrackOptionsItemID
		{
			NO_FOCUS = 0,
			TRACK_BACK,
			TRACK_FWD,
			TRACK_SWAP,
			TRACK_CONFIG,
			FOCUS_MAX = TRACK_CONFIG
		};
		uint8_t TrackOptionsView[TRACK_VIEW] = { NO_FOCUS, TRACK_BACK, TRACK_FWD, TRACK_SWAP, TRACK_CONFIG };
		int KeyFocusedItem = TrackOptionsItemID::NO_FOCUS;
		bool option_handler_enabled = false;
		bool fillKeyStatus = false;

		IgniteTrackGrid* trackGridPtr = nullptr;
		AppOptCtl* trackoptCtl = nullptr;
		IgniteInstrument* instrInstance = nullptr;
		IgniteScene* scenePtr = nullptr;
		AppOptCtl* trackOptCtl = nullptr;
		IgniteTrackSwap* trackSwapComp = nullptr;
		PatternStatusBar* patternstatusbarptr = nullptr;
		trackScreenIndex Currentindex = trackScreenIndex::WINOW_INVALID;
		AppMainmode* mainmodeptr = nullptr;
		IgniteRecordModale* RecordModale = nullptr;
		mt::Ignite::trackData prevTrackData{ 0 };
		int currentTrackBank;
		int numOfTrackBanks = 1;
		int num_of_scenes = 0;
		int id = 0, pid = 0, pfid = 0;
		bool recButtonBlinkState = true;
		uint8_t timeSeconds = 0;
		uint8_t timeMinutes = 0;
		uint8_t timeHours = 0;
		bool isAutosave = false;
		int activeBarId = 1;
		int activeStepId = 1;
		int currentSceneBar = 0;
		mt::Ignite::operatioMode opMode = mt::Ignite::operatioMode::IDLE_MODE;
		bool bootupState = true;

		IgniteTrackValues* trackValuesPtr = nullptr;
		CommonPopUp* popupPtr = nullptr;
		IgniteSongConfig* SongConfig = nullptr;
		juce::FlexBox viewBox;

		CommonImageButton trackSwap{ TRANS("Track Swap"),"btn-track-swap-default.png","btn-track-swap-active.png","btn-track-swap-default-hover.png" };
		CommonImageButton backButton{ TRANS(">") ,"btn-prev-default.png","btn-prev-active.png","btn-prev-default-hover.png" };
		CommonImageButton fwdButton{ TRANS(">") ,"btn-next-default.png","btn-next-active.png","btn-next-default-hover.png" };
		CommonImageButton trackConfig{ "TrackConfig","btn-config-default.png","btn-config-active.png","btn-config-default-hover.png"};
		CommonImageButton trackView{ "Scene View","btn-song-detail-default.png","btn-song-detail-active.png","btn-song-detail-default-hover.png" };
		CommonImageButton listView{ "List View","btn-song-list-default.png","btn-song-list-active.png","btn-song-list-default-hover.png" };

		void cleanup();
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void sendRecordRequestToEngine(int state);
		void onOptCtlButtonClicked(AppOptCtl::pKey option);
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) override;
		void timerCallback() override;
		bool PannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTrack)
	};
};
