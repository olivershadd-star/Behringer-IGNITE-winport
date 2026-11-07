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
	class IgniteSceneRow;
	class AppSceneView;
	class AppDnp;
	class IgniteLoopControl;

	class IgniteScene :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener,
		public juce::DragAndDropContainer
	{
	public:
		int currentTrack = 0;

		enum SCENE_FOCUS
		{
			SCENE_DETAIL,
			SCENE_LIST,
			SCENE_OPTION,
		};

		IgniteScene();
		~IgniteScene() override;

		int getSelected(void);
		var getSceneData(mt::Ignite::sceneDataIndex item_id);
		int getCurrentSceneRow() { return curretSceneRow; }
		String getSceneListData(mt::Ignite::sceneDataIndex index);
		mt::Ignite::trackData* getTrackDataRef(int currentTrack = -1);
		bool getSceneDataUpdateStatus() { return sceneDataUpdated; }
		bool getSceneMoveState() { return moveEnabled; }
		int8_t getOptionHandlerState() { return optionHandlerEnabled; }
		int setNextCurrentTrack(int selectedTrack);

		void setCurrentPlayingScene(int index);
		void setCurrentSceneRow(int value) { curretSceneRow = value; }
		void setSelected(int index);
		void setSceneDataUpdateStatus(bool state) { sceneDataUpdated = state; }
		void setSceneMoveState(bool state) { moveEnabled = state; }

		void changeSceneOptionsVisibility(bool bShouldShow);

		void setSceneData(mt::Ignite::sceneDataIndex item_id, uint8_t value, bool is_internal);
		void setSceneData(mt::Ignite::sceneDataIndex item_id, int8_t value, bool is_internal);
		void setSceneData(mt::Ignite::sceneDataIndex item_id, int value, bool is_internal);
		void setSceneData(mt::Ignite::sceneDataIndex item_id, String value, bool is_internal);
		void setSceneData(mt::Ignite::sceneDataIndex item_id, float data, bool is_internal, bool isPlayModeData = false);

		void updateSceneData(uint8_t param, const uint8_t value);
		void updateSceneData(uint8_t param, const int8_t value);
		void updateSceneData(uint8_t param, const int16_t value);
		void updateSceneData(uint8_t param, const uint32_t value);
		void updateSceneData(uint8_t param, const float value);
		void updateSceneData(uint8_t param, const std::string& value);
		void updateSceneEditIndication(bool state);
		void updateSceneList();

		void updateTracksData();

		void addScene(bool updateDefultData, String name = "");
		void deleteAllScenes();
		void refreshSceneUI();
		void enableControlButton(IgniteControlOptions::eKey key, bool state) { _pSceneOptCtl->enableKey(key, state); };
		void moveScene(juce::Point<float> position);
		void moveScene(int dest_index);
		void updateLables();
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		void setSceneRowHighLightIndex(bool isInc, int indexBy);
		void enableViewBox(bool state);
		int getViewStatus();
		void setFpSceneLedState();
		int getCurrentSceneBank() { return currentSceneBank; };
		bool isGlobalAutosaveEnabled() { return isAutosave; };
		void getAssets();
		static IgniteScene* getAppSceneInstance()
		{
			static IgniteScene* sceneInstance;
			if (NULL == sceneInstance)
			{
				sceneInstance = new IgniteScene();
			}

			return sceneInstance;
		}

		CommonPopUp* _pPopUpPtr = nullptr;
		AppSceneView* _pSceneView = nullptr;
		AppMainmode* mainmodePtr = nullptr;

	private:
#define SCENE_OPTIONS_VIEW 10
		enum OptionsViewItemID
		{
			NO_FOCUS = 0,
			SCENE_MOVE_DOWN,
			SCENE_MOVE_UP,
			SCENE_MOVE_TOP,
			SCENE_MOVE_LAST,
			SCENE_MOVE,
			/*SCENE_LOOP,*/
			SCENE_UNDO,
			SCENE_COPY,
			SCENE_CONFIG,
			FOCUS_MAX = SCENE_CONFIG
		};

		uint8_t optionsView[SCENE_OPTIONS_VIEW] = { NO_FOCUS, SCENE_MOVE_DOWN, SCENE_MOVE_UP, SCENE_MOVE_TOP, SCENE_MOVE_LAST, SCENE_MOVE, /*SCENE_LOOP,*/ SCENE_UNDO, SCENE_COPY, SCENE_CONFIG };
		int keyFocusedItem = OptionsViewItemID::NO_FOCUS;

		IgniteSong* _pSongPtr = nullptr;
		AppDnp* _pEmptySceneComp = nullptr;
		IgniteLoopControl* _pSceneLoopComp = nullptr;
		juce::OwnedArray<IgniteSceneRow>* _pRowPtr = nullptr;
		IgniteControlOptions* _pSceneOptCtl = nullptr;
		SceneStatusBar* _pSceneBarRef = nullptr;
		IgniteCopy* _pSceneCopyComp = nullptr;
		AppOptions* _pAppOptPtr = nullptr;
		bool isAutosave = false;

		juce::FlexBox viewBox;
		juce::Viewport dialogViewPort;
		bool isDialogClosed{ true };
		juce::Viewport view;
		juce::Component container;
		CommonButton addNew{ "" };
		CommonImageButton addNewInList{ "+ Add New Scene","btn-add-newscene-default.png","btn-add-newscene-active.png", "btn-add-newscene-hover.png" };
		CommonImageButton sceneView{ "Scene View","btn-song-detail-default.png","btn-song-detail-active.png","btn-song-detail-default-hover.png" };
		CommonImageButton listView{ "List View","btn-song-list-default.png","btn-song-list-active.png","btn-song-list-default-hover.png" };

		std::vector<juce::String> sceneList{ "No Scene Selected" };
		int songIndex = -1;
		mt::Ignite::sceneData prevSceneData{ 0 };
		bool keyFocusOnRow = false;
		int sceneRowHighLightIndex = 0;
		bool addNewInListHiglited = false;
		paramId_t itemParam;
		uint32_t itemKeyValue;
		bool itemFocus = false;
		int curretSceneRow = 0;
		bool sceneDataUpdated = false;
		bool moveEnabled = false;
		uint8_t optionHandlerEnabled = SCENE_DETAIL;
		int selected{ 0 };
		int prevSelected{ 0 };
		int currentSceneBank = 0;
		Image imageAddNewInlistDefault, imageAddNewInlistActive, imageAddNewInlistHover,imageSceneDetailViewDefault, imageSceneDetailViewActive, imageSceneDetailViewHover,
			imageSceneListViewDefault, imageSceneListViewActive, imageSceneListViewHover, imageAddNewDefault, imageAddNewActive, imageAddNewHover;
		void cleanup();
		void populate(mt::Ignite::sceneData* scDataPtr, bool isScreenUpdateneeded, String name = "");
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void setDefaultSceneData(mt::Ignite::sceneData* scDataPtr, bool updateDefultData);
		void showPopup(int index);
		void setLoopControl(IgniteLoopControl::loopKey key, int loopStartIndex, int loopEndIndex);
		String getSceneName();
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) override;
		void copyScene(IgniteCopy::copyCtlKey key, String copyName);
		void deleteScene();
		void deleteCurrentScene();
		void saveScene();
		void handleCommandMessage(int id);
		bool pannelKeyOptionsHandler(paramId_t param, uint32_t keyValue);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void requestDataFromEngine(int index);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteScene)
	};

	class IgniteSceneRow :
		public juce::Component,
		public CommonLabel::Listener
	{
	public:
		IgniteSceneRow(int SerialNumber, mt::Ignite::sceneData& Data, IgniteScene* scenePtr);
		~IgniteSceneRow();
		std::function<void(IgniteSceneRow*)> onMouseDown;

		int getSongIndex(void);
		int getSerialNumber();

		void setSongIndex(int index);
		void setColor(int colourID, Colour colour);
		void setloop(bool a) { isloopEnabled = a; repaint(); };
		void SetFocus(bool hasFocus, bool hasActiveFoces);

		void updateEditIndication();

		void highlight(bool state);
		void refreshSceneRowUI();
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool isEditing() { return name.isEditing; }
		void getAssets();
	private:
		IgniteScene* _pScene = nullptr;
		mt::Ignite::sceneData& Scenedata;
		juce::FlexBox box;
		int serialNo;
		int songIndex;
		String serialNumber = "1";

		CommonSerialNumber srNo{ "1" };
		CommonKey name{ "" };
		CommonLabel sceneState{ "INACTIVE" };
		bool rowIsBeingDraggedOver = false;
		bool  isloopEnabled = false;
		Image imageSceneListActiveHover, imageSceneListActive, imageSceneListInactiveDefault, imageSceneListInactiveHover;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void labelTextChanged(Label* labelThatHasChanged) override;
		void mouseDown(const MouseEvent& event) override;
		bool isHighlighted{ false };
		void mouseUp(const MouseEvent& event) override;
		void mouseDrag(const MouseEvent& event) override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		bool isMouseOver{ false };

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteSceneRow)
	};
};
