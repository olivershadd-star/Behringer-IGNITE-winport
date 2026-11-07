/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY
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
using namespace ignite_Constants;
namespace ui
{
	class IgniteSong;
	class IgniteSongRow;
	class AppOptCtl;
	class IgniteMiscSettings;

	class AppSongView : public juce::Component,
		public juce::Button::Listener,
		public juce::Label::Listener,
		public juce::ModalComponentManager,
		private Timer
	{
	public:
		AppSongView(IgniteSong* ptr);
		~AppSongView() override;

		void refreshData(int SerialNumber, mt::Ignite::songData* data);
		void updateSongEditIndication();
		void updateScene(mt::Ignite::songData* data, int sceneActiveTracks, int nextSceneActiveTracks);
		void updateSceneLists(mt::Ignite::songData* songdata);
		void sceneBoxEnable(bool state) { sceneCBox.setInterceptsMouseClicks(state, state);  state ? sceneCBox.setAlpha(1.0f) : sceneCBox.setAlpha(0.5f); }
		void clearTapTempoData() { tapTempo.resetTapTempoData(); };
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void setTapTempo(float value, bool sendTempoAsPlayModeData, bool timerStart);
		void resetSongFocuse(String text);
		void getAssets();
		void updateActiveTracks();

		static AppSongView* getAppSongViewInstance(IgniteSong* ptr)
		{
			static AppSongView* instanceAppAppSongView;
			if (NULL == instanceAppAppSongView)
			{
				instanceAppAppSongView = new AppSongView(ptr);
			}
			return instanceAppAppSongView;
		}

	private:

#define SONG_DETAIL_ROW_ITEMS 3
#define SONG_DETAL_VIEW 12
#define SONG_DETAL_SWING_TO_SCENE_BUTTON_ID 1
#define SONG_DETAL_TEMPO_TO_SCENE_BUTTON_ID 2
#define SONG_DETAL_SHOW_SCENE_LIST_BUTTON_ID 3
		enum songDetailsViewItemID
		{
			NO_FOCUS = 0,
			SWING, //Row 1
			SWING_TO_SCENE,
			NUM_TRACKS,
			VIEW_TRACKS,
			TEMPO,
			TEMPO_TO_SCENE,
			SHOW_SCENE_LIST,
			CURRENT_SCENE, //Row 2
			NEXT_SCENE, // Row 3
			TAP_TEMPO,
			FOCUS_MAX = TAP_TEMPO
		};
		uint8_t songDetailsView[SONG_DETAL_VIEW] = { NO_FOCUS, SWING, SWING_TO_SCENE, NUM_TRACKS, VIEW_TRACKS, TEMPO, TEMPO_TO_SCENE, SHOW_SCENE_LIST, CURRENT_SCENE, NEXT_SCENE, TAP_TEMPO };
		int keyFocusedItem = songDetailsViewItemID::NO_FOCUS;
		int numItemsInRow = 3;
		IgniteSong* _pSong = nullptr;
		IgniteBottomBar* _pBottomBarComp = nullptr;
		IgniteSongConfig* _pSongConfigComp = nullptr;
		IgniteControlOptions* optPtr = nullptr;

		juce::FlexBox sceneBox;
		mt::Ignite::songData songData;
		TextEditor songNameText;
		IgniteTapTempo tapTempo;
		CommonKey nameLabel{ "SONG_NAME" };
		CommonImageButton showSceneList{ "View all scenes","btn-allscene-default.png","btn-allscene-active.png","btn-allscene-default-hover.png" };
		CommonImageButton swingAppliedtoScene{ "Swing to Scene","sml-btn-toggle-no-default.png","sml-btn-toggle-yes-default.png" };
		CommonImageButton tempoAppliedtoScene{ "Tempo to Scece","sml-btn-toggle-no-default.png","sml-btn-toggle-yes-default.png" };
		CommonToggleButton btnSwingAppliedtoScene{ "" };
		CommonToggleButton btnTempoAppliedtoScene{""};
		CommonNumber tempoComp{ "Tempo", minTempo, maxTempo, defTempo, true };
		CommonNumber swingComp{ "Swing", minSwing, maxSwing, defSwing };
		CommonListBox tracksComp{ "Number of Tracks", 4 };
		std::vector<juce::String> numOfTracks{ "16", "32", "48", "64" };
		CommonListBox sceneCBox{ "Current Scene", 1 };
		std::vector<juce::String> sceneList{ "No Scene" };
		CommonListBox nextCSceneBox{ "Next Scene", 1 };
		std::vector<juce::String> nextSceneList{ "No Scene" };
		CommonNumber sceneInSong{ "Scenes in Song",0,200,0 };
		CommonLabel activeTrackC{ "Current scene Active Track","No Active Track" };
		CommonLabel activeTrackN{ "Next  scene Track","No Active Track" };
		CommonLabel tempoToScene{ "Applied to Scence","Applied to Scene" };
		CommonLabel swingToScene{ "Swing Applied to Scence","Applied to Scene" };
		CommonImageButton tracklist{ "Track list","btn-alltracks-default.png","btn-alltracks-active.png","btn-alltracks-default-hover.png" };
		CommonButton cScene{ "" };
		CommonButton nScene{ "" };
		CommonButton swingHover;
		CommonButton tempoHover;
		Image imageAllSceneDefault, imageAllSceneActive, imageAllSceneDisable, imageSwingApptoSceneDefault, imageSwingApptoSceneActive,
			imageSwingApptoSceneDisable, imageTempoApptoSceneDefault, imageTempoApptoSceneActive, imageSongHeader, imageBgContainerSmallDefault, imageBgContainerSmallActive
			, imageBgContainerLowerDefault, imageBgContainerLowerHover, imageBgContainerLongDefault, imageBgContainerLongHover, imageBgContainer2ShortDefault, imageBgContainer2ShortHover,
			imageDividerHorz, imageSongTempoDefault, imageSongTempoHover, imageSongTempoClick;

		bool isSongSelected;
		bool isThereExistingSong;
		bool songSelected;
		bool _isFillMode;
		int id = 0, sId = 0, pfId = 0;

		void paint(juce::Graphics& g) override;
		void labelTextChanged(Label* labelThatHasChanged) override;
		void resized() override;
		//void mouseUp(const MouseEvent& event) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();
		void updateLableText(mt::Ignite::songsDataIndex item_id, bool state);
		String getSceneName(int index) { return sceneList[index]; }
		String getNxtSceneName(int index) { return nextSceneList[index]; }
		void timerCallback() override;
		void mouseDown(const MouseEvent& event) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppSongView)
	};
};
