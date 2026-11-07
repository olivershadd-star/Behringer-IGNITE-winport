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

	class IgniteSceneConfig :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define SONG_NO_COM_ROW 3

		CommonNumber tapConfig{ "Tap Tempo: Min Taps", 3, 5, 3 };

		IgniteSceneConfig();
		~IgniteSceneConfig() override;

		void setftsWindowState(bool state) { ftsWindowEnabled = state; }
		bool getftsWindowState() { return ftsWindowEnabled; }

		void setSceneConfigDataUpdateState(bool state) { 
			sceneConfigDataUpdated = state; }
		bool getSceneConfigDataUpdateState() { return sceneConfigDataUpdated; }
		String getSceneInsertPosition() { return insertPosition.getSelectedValue(); }

		bool isAutoSaveEnabled() { return autoSaveScene; }
		void updateData(bool isInternal);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);

		IgniteControlOptions* sceneOptCtl = nullptr;
		void getAssets();
		static IgniteSceneConfig* getAppSceneConfigInstance()
		{
			static IgniteSceneConfig* getAppSceneConfigObj;
			if (NULL == getAppSceneConfigObj)
			{
				getAppSceneConfigObj = new IgniteSceneConfig();
			}

			return getAppSceneConfigObj;
		}

	private:

#define SCENE_MENU_VIEW 7
#define SCENE_OPT_VIEW  4
		enum sceneMenuViewItemID
		{
			NO_FOCUS = 0,
			AUTO_SAVE, //Row 1
			WIPE_SCENES,
			TAP_TEMPO,
			FILL_CONFIG, //Row 2
			//FILL_MODE,
			//FILL_RELEASE,
			SOLO_MODE,
			//UDS_CONFIG, //Row 2
			INSERT_POSITION,
			FOCUS_MAX = INSERT_POSITION
		};

		enum SONGCONFIG_FOCUS
		{
			SCENECONFIG_DETAIL,
			SCENECONFIG_OPTION,
		};

		enum sceneOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OPT_SCENELIST,
			OP_FOCUS_MAX = OPT_SCENELIST
		};

		CommonImageButton autoSaveBtn{ "Auto Save:off","toggle-autosave-default.png","toggle-autosave-active.png","toggle-autosave-hover.png"};
		CommonImageButton wipeScenesBtn{ "Wipe Scenes of Current Song","btn-wipe-scene-default.png","btn-wipe-scene-default.png","btn-wipe-scene-hover.png"};
		//CommonImageButton customFtsBtn{ "User Defined Scales","btn-uds-default.png","btn-uds-default.png","btn-uds-hover.png"};
		CommonListBox insertPosition{ "Insert Position", 1 };
		CommonImageButton soloModeBtn{ "Solo Mode:off","toggle-solomode-default.png","toggle-solomode-active.png","toggle-solomode-hover.png" };
		CommonImageButton fillModeBtn{ "Fill Mode:off","toggle-fillmode-default.png","toggle-fillmode-active.png","toggle-fillmode-hover.png" };
		//CommonNameLabel fillConfigLable{ "Fill Config :" };
		//CommonListBox fillMode{ "Fill Mode", 1 };
		//std::vector<juce::String> fillModeOptions{ "Auto", "Active", "Mute", "No Fill" };
		//CommonListBox fillRelease{ "Release", 1 };
		//std::vector<juce::String> releaseOptions{ "Key", "Bar", "Scene" };

		juce::FlexBox sceneMenuBox1;
		juce::FlexBox sceneMenuBox2;
		//juce::FlexBox sceneMenuBox3;

		IgniteCustomScale* _pCustomScaleComp = nullptr;
		CommonPopUp* _pPopUpPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;

		uint8_t optionHandlerFocus = SCENECONFIG_DETAIL;
		uint8_t optionsView[SCENE_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OPT_SCENELIST,OP_FOCUS_MAX };
		uint8_t sceneMenuView[SCENE_MENU_VIEW] = { NO_FOCUS, AUTO_SAVE, WIPE_SCENES, TAP_TEMPO, FILL_CONFIG, /*FILL_MODE, FILL_RELEASE,*/ SOLO_MODE, /*UDS_CONFIG, */INSERT_POSITION };
		int keyFocusedItem = sceneMenuViewItemID::NO_FOCUS;
		bool sceneConfigDataUpdated = false;
		bool ftsWindowEnabled = false;
		bool autoSaveScene = false;
		int optFocusedItem = OPT_UNDO;
		Image imageDefault, imageDefaultHover, imageDisabled;
		bool isAutosave = false;
		bool isInternal = false;
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void mouseUp(const MouseEvent& event) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		int isEditing();
		void handleCommandMessage(int cmdId);
		bool handleCustomScaleComp(paramId_t param, uint32_t KeyValue);
		bool handlePopUp(paramId_t param, uint32_t KeyValue);
		bool handleSoloSkip(uint32_t KeyValue);
		bool handleFillX(uint32_t KeyValue);
		bool handlePageShift(paramId_t param, uint32_t KeyValue);
		bool handleDefault(paramId_t param, uint32_t KeyValue);
		bool handleDetailFocus(paramId_t param, uint32_t KeyValue);
		bool handleOptionFocus(paramId_t param, uint32_t KeyValue);
		void handleRotaryKey(paramId_t param, uint32_t KeyValue);
		void handleDetailFocus(bool isFocuse, paramId_t param, uint32_t KeyValue, IgniteScene* scenePtr);
		void handleWipeScenes(bool isFocuse, paramId_t param, uint32_t KeyValue, IgniteScene* scenePtr);
		void handleSoloMode(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleFillConfig(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void adjustFocus(paramId_t param);
		void handleOptionFocus(bool isFocuse, paramId_t param, uint32_t KeyValue);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteSceneConfig)
	};
};
