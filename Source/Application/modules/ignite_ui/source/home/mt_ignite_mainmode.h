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

namespace ui
{
	class IgniteSong;
	class IgniteScene;
	class IgniteTrack;
	class IgnitePattern;
	class IgniteControlOptions;
	class IgniteRecordModale;
	class IgniteBarInsert;
	class IgniteBarCopy;
	class CommonAutoHideSlider;
	class AppMenu;
	class AppOptions;
	class IgniteTrackSwap;
	class CVControl;
	class WifiManager;

	struct TabData
	{
		juce::String tabName;
		bool multiTab = false;
		int multiTabCount = 1;
		std::vector<CommonPadButton::PadButtonType> multiTabButtonTypes;
	};

	class AppMainmode : public juce::Component,
		public juce::Button::Listener
	{
	public:
		IgniteTrackSwap* trackSwapComp = nullptr;
		IgniteBarInsert* barInsertComp = nullptr;
		IgniteBarCopy* patternBarCopyComp = nullptr;

		AppMainmode();
		~AppMainmode() override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void changeTabVisibility(mt::Ignite::tabs, bool);
		static AppMainmode* getMainModeInstance()
		{
			static AppMainmode* getMainModeInstance;
			if (NULL == getMainModeInstance)
			{
				getMainModeInstance = new AppMainmode();
			}

			return getMainModeInstance;
		}
		void HandleTabKey(mt::Ignite::tabs tab_index);
		void handleCommandMessage(int id);
		bool PannelKeyHandler(mt::Ignite::tabs tab_index, paramId_t param, uint32_t KeyValue);
		void enableTab(mt::Ignite::tabs tab_index, bool enable);
		void changeTabState(mt::Ignite::tabs);
		mt::Ignite::tabs GetActiveTab()
		{
			return active_tab;
		}
		void setActiveTab(mt::Ignite::tabs t) { active_tab = t; };
		void triggerTabChange(mt::Ignite::tabs t);
		void resetPadLedsOnViewChange();
		void resetPatternStepModes();
		void resetTrackSelLeds();
		void resetPatternModes();
		void resetRotaryLedsOnViewChange();
		void setFpTrackLedState();
		void setFpEditTrackLedState();
		void setFpTrackSoloLedState();
		void setFpTrackFillLedState();
		void setFpTrackFillAndSoloLedState();
		void setFpFillAndSoloLedState();
		void setSoloKeyStatus(bool soloKeyState) { soloKeyStatus = soloKeyState; }
		bool getSoloKeyStatus() { return soloKeyStatus; }
		bool getFillKeyStatus() { return fillKeyStatus; }
		bool handleTrackSolo(paramId_t param, uint32_t KeyValue);
		void startUsbHandler();
		bool getIntSoundStatus() { return boIntSoundEnabled; }
		void getAssets();
		bool* getTrackMuteStatus() { return trackMuteStatus; }
		bool* getTrackSoloStatus() { return trackSoloStatus; }

	private:
		IgniteSong* appSongComp = nullptr;
		IgniteScene* appSceneComp = nullptr;
		IgniteTrack* appTrackComp = nullptr;
		IgnitePattern* appPatternComp = nullptr;
		IgniteControlOptions* optCntPtr = nullptr;
		IgniteRecordModale* RecordModale = nullptr;
		CommonAutoHideSlider* hidesliders = nullptr;
		AppMenu* componentMenu = nullptr;
		AppOptions* optionComp = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;
		CVControl* cvCtlComp = nullptr;
		WifiManager* wifiComp = nullptr;

		bool trackMuteStatus[64] = { false };
		bool trackSoloStatus[64] = { false };
		bool fillKeyStatus = false;
		bool soloKeyStatus = false;
		bool boMadeVisible;
		bool boIntSoundEnabled = false;
		bool boBrayEnabled = false;
		int barIndex = 0;
		std::vector<TabData> tabData;
		CommonToggleButton menu{ };
		CommonToggleButton Song{ };
		CommonToggleButton Scene{ };
		CommonToggleButton Track{  };
		CommonToggleButton Pattern{  };
		FlexBox tabBox;
		mt::Ignite::tabs active_tab = { mt::Ignite::tabs::MENU };
		CommonPopUp* popupPtr = nullptr;
		Image imageMenuActivehover, imageMenuActive, imageMenuDefaulthover, imageMenuDefault;
		Image imageSongActivehover, imageSongActive, imageSongDefaulthover, imageSongDefault, imageSong2Activehover, imageSong2Active;
		Image imageSceneActivehover, imageSceneActive, imageSceneDefaulthover, imageSceneDefault, imageScene2Activehover, imageScene2Active, imageSceneDisabled, imageSceneDisabledhover;
		Image imageTrackActivehover, imageTrackActive, imageTrackDefaulthover, imageTrackDefault, imageTrack2Activehover, imageTrack2Active, imageTrackDisabledhover, imageTrackDisabled;
		Image imagePatternDefaulthover, imagePatternDefault, imagePatternActivehover, imagePatternActive, imagePatternActive2hover, imagePatternActive2, imagePatternActive3, imagePatternActive3hover, imagePatternActive4hover, imagePatternActive4;

		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void clearAllTabKeyLed();
		void resetLedsOnTabChange();
		bool handleTrackMute(paramId_t param, uint32_t KeyValue);
		bool handleEditTrack(paramId_t param, uint32_t KeyValue);
		bool handleFillMode(paramId_t param, uint32_t KeyValue);
		bool handleSoloMode(paramId_t param, uint32_t KeyValue);
		bool handleTrackBank(paramId_t param, uint32_t KeyValue);
		bool showTrackBank(paramId_t param, uint32_t KeyValue);
		bool changeTrackBank(paramId_t param, uint32_t KeyValue);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppMainmode)
	};
};
