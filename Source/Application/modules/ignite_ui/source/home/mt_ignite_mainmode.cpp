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

using namespace ignite_Constants;
namespace ui
{
	AppMainmode::AppMainmode()
	{
		appSongComp = IgniteSong::getAppSongInstance();
		appSceneComp = IgniteScene::getAppSceneInstance();
		appTrackComp = IgniteTrack::GetAppTrackInstance();
		appPatternComp = IgnitePattern::getAppPatternInstance();
		componentMenu = AppMenu::GetAppMenuInstance();
		optionComp = AppOptions::GetOptionsInstance();
		optCntPtr = IgniteControlOptions::GetAppOptInstance();
		hidesliders = CommonAutoHideSlider::GetHideSliderInstance();
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();
		cvCtlComp = CVControl::getCVInterface();
		wifiComp = WifiManager::getWifiInterface();

		addChildComponent(optCntPtr);
		optCntPtr->setInterceptsMouseClicks(true, true);
		optCntPtr->setVisible(true);

		tabData = { {"MENU", false, 0, {CommonPadButton::PadButtonType::withMenuTab}},
					{"SONG", false, 2, {CommonPadButton::PadButtonType::withSongMultiTab, CommonPadButton::PadButtonType::withPatternMultiTab}},
					{"SCENE", false, 0, {CommonPadButton::PadButtonType::withMenuTab}},
					{"TRACK", false, 0, {CommonPadButton::PadButtonType::withMenuTab}},
					{"PATTERN", true, 3, {CommonPadButton::PadButtonType::withPatternMultiTab, CommonPadButton::PadButtonType::withPatternMultiTab, CommonPadButton::PadButtonType::withPatternMultiTab}}
		};
		addChildComponent(appSongComp);
		addChildComponent(appSceneComp);
		addChildComponent(appTrackComp);
		addChildComponent(appPatternComp);
		addChildComponent(componentMenu);
		addChildComponent(optionComp);
		addChildComponent(hidesliders);
		addChildComponent(_pInfoWindow);

		menu.makeVisibleAndAddListner(this);
		Song.makeVisibleAndAddListner(this);
		Scene.makeVisibleAndAddListner(this);
		Track.makeVisibleAndAddListner(this);
		Pattern.makeVisibleAndAddListner(this);

		menu.setToggleState(true, dontSendNotification);

		appSongComp->setVisible(true);
		optCntPtr->setVisible(true);
		optionComp->setVisible(true);
		enableTab(mt::Ignite::tabs::SCENE, false);
		enableTab(mt::Ignite::tabs::TRACK, false);
		changeTabVisibility(mt::Ignite::tabs::MENU, true);
		appPatternComp->refreshStatusbar();
		appPatternComp->refreshPatternUI();

		trackSwapComp = IgniteTrackSwap::GetTrackSwapInstance();
		addChildComponent(trackSwapComp);
		trackSwapComp->setBounds(210, 20, 604, 533);
		trackSwapComp->setVisible(false);

		RecordModale = IgniteRecordModale::GetAppRecordInstance();
		addChildComponent(RecordModale);

		RecordModale->setVisible(false);
		menu.setLookAndFeel(EmptyBackgroundLooknFeel().getLnf());
		Scene.setLookAndFeel(EmptyBackgroundLooknFeel().getLnf());
		Song.setLookAndFeel(EmptyBackgroundLooknFeel().getLnf());
		Track.setLookAndFeel(EmptyBackgroundLooknFeel().getLnf());
		Pattern.setLookAndFeel(EmptyBackgroundLooknFeel().getLnf());
		hidesliders->SetVisible(false);
		hidesliders->setInterceptsMouseClicks(false, true);
		getAssets();
		trackSwapComp->onButtonPressed = [this](IgniteTrackSwap::swapCtlKey key, int index1, int index2)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			appTrackComp->swapTrack(key, index1 - 1, index2 - 1);
		};

		barInsertComp = new IgniteBarInsert();
		addChildComponent(barInsertComp);
		barInsertComp->setBounds(210, 20, 604, 533);
		barInsertComp->setVisible(false);

		barInsertComp->onButtonPressed = [this](IgniteBarInsert::insertCtlKey key, int barNumber)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			appPatternComp->insertBar(key, barNumber - 1);
		};

		patternBarCopyComp = new IgniteBarCopy();
		addChildComponent(patternBarCopyComp);
		patternBarCopyComp->setBounds(210, 20, 604, 533);
		patternBarCopyComp->setVisible(false);

		patternBarCopyComp->onButtonPressed = [this](IgniteBarCopy::copyBarCtlKey key, int fromBarId, int toBarId)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			appPatternComp->copyPatternBar(key, fromBarId - 1, toBarId - 1);
		};
		popupPtr = CommonPopUp::getCommonPopupInstance();

		_pInfoWindow->setVisible(false);
	}

	AppMainmode::~AppMainmode() {}

	void AppMainmode::paint(juce::Graphics& g)
	{

		Image Draw = menu.getToggleState() ? (menu.isFocused || menu.isMouseOver() ? imageMenuActivehover : imageMenuActive) : (menu.isFocused || menu.isMouseOver() ? imageMenuDefaulthover : imageMenuDefault);
		g.drawImage(Draw, ui::Rectangle<float>{12, 0, 110, 76}, RectanglePlacement::centred);

		if (appSongComp->isVisible())
		{
			if (appSongComp->getViewStatus())
				Draw = Song.getToggleState() ? (Song.isFocused || Song.isMouseOver() ? imageSongActivehover : imageSongActive) : (Song.isFocused || Song.isMouseOver() ? imageSongDefaulthover : imageSongDefault);
			else
				Draw = Song.getToggleState() ? (Song.isFocused || Song.isMouseOver() ? imageSong2Activehover : imageSong2Active) : (Song.isFocused || Song.isMouseOver() ? imageSongDefaulthover : imageSongDefault);
		}
		else
		{
			Draw = Song.isFocused || Song.isMouseOver() ? imageSongDefaulthover : imageSongDefault;
		}
		g.drawImage(Draw, ui::Rectangle<float>{127, 0, 110, 76}, RectanglePlacement::centred);

		if (Scene.isEnabled())
		{
			if (appSceneComp->getViewStatus())
				Draw = Scene.getToggleState() ? Scene.isFocused || Scene.isMouseOver() ? imageSceneActivehover : imageSceneActive : Scene.isFocused || Scene.isMouseOver() ? imageSceneDefaulthover : imageSceneDefault;
			else
				Draw = Scene.getToggleState() ? Scene.isFocused || Scene.isMouseOver() ? imageScene2Activehover : imageScene2Active : Scene.isFocused || Scene.isMouseOver() ? imageSceneDefaulthover : imageSceneDefault;
		}
		else
			Draw = Scene.isFocused || Scene.isMouseOver() ? imageSceneDisabledhover : imageSceneDisabled;
		g.drawImage(Draw, ui::Rectangle<float>{242, 0, 110, 76}, RectanglePlacement::centred);

		if (Track.isEnabled())
			if (appTrackComp->getViewStatus())
				Draw = Track.getToggleState() ? Track.isFocused || Track.isMouseOver() ? imageTrackActivehover : imageTrackActive : Track.isFocused || Track.isMouseOver() ? imageTrackDefaulthover : imageTrackDefault;
			else
				Draw = Track.getToggleState() ? Track.isFocused || Track.isMouseOver() ? imageTrack2Activehover : imageTrack2Active : Track.isFocused || Track.isMouseOver() ? imageTrackDefaulthover : imageTrackDefault;
		else
			Draw = Track.isFocused || Track.isMouseOver() ? imageTrackDisabledhover : imageTrackDisabled;
		g.drawImage(Draw, ui::Rectangle<float>{357, 0, 110, 76}, RectanglePlacement::centred);

		if (appPatternComp->isVisible())
		{
			if (appPatternComp->getTabIndex() == 1)
				Draw = Pattern.isFocused || Pattern.isMouseOver() ? imagePatternActive2hover : imagePatternActive2;
			else if (appPatternComp->getTabIndex() == 2)
				Draw = Pattern.isFocused || Pattern.isMouseOver() ? imagePatternActive3hover : imagePatternActive3;
			else if (appPatternComp->getTabIndex() == 3)
				Draw = Pattern.isFocused || Pattern.isMouseOver() ? imagePatternActive4hover : imagePatternActive4;
			else
				Draw = Pattern.isFocused || Pattern.isMouseOver() ? imagePatternActivehover : imagePatternActive;
		}
		else
		{
			Draw = Pattern.isFocused || Pattern.isMouseOver() ? imagePatternDefaulthover : imagePatternDefault;
		}

		g.drawImage(Draw, ui::Rectangle<float>{472, 0, 110, 76}, RectanglePlacement::centred);
	}

	void AppMainmode::getAssets()
	{
		imageMenuActivehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-menu-active-hover.png"));
		imageMenuActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-menu-active.png"));
		imageMenuDefaulthover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-menu-default-hover.png"));
		imageMenuDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-menu-default.png"));

		imageSongActivehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-song-active-hover.png"));
		imageSongActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-song-active.png"));
		imageSongDefaulthover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-song-default-hover.png"));
		imageSongDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-song-default.png"));

		imageSong2Activehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-song-active2-hover.png"));
		imageSong2Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-song-active2.png"));

		imageSceneActivehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-active-hover.png"));
		imageSceneActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-active.png"));
		imageSceneDefaulthover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-default-hover.png"));
		imageSceneDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-default.png"));

		imageScene2Activehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-active2-hover.png"));
		imageScene2Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-active2.png"));

		imageSceneDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-disabled.png"));
		imageSceneDisabledhover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-scene-disabled-hover.png"));

		imageTrackActivehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-active-hover.png"));
		imageTrackActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-active.png"));
		imageTrackDefaulthover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-default-hover.png"));
		imageTrackDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-default.png"));

		imageTrack2Activehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-active2-hover.png"));
		imageTrack2Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-active2.png"));

		imageTrackDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-default-1.png"));
		imageTrackDisabledhover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-tracks-default-hover-1.png"));

		imagePatternDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-default.png"));
		imagePatternDefaulthover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-default-hover.png"));

		imagePatternActivehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active-hover.png"));
		imagePatternActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active.png"));

		imagePatternActive2hover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active2-hover.png"));
		imagePatternActive2 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active2.png"));

		imagePatternActive3hover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active3-hover.png"));
		imagePatternActive3 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active3.png"));

		imagePatternActive4hover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active4-hover.png"));
		imagePatternActive4 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("topnav-pattern-active4.png"));
	}


	void AppMainmode::changeTabVisibility(mt::Ignite::tabs tab_index, bool enable)
	{
		int sceneView = -1;
		componentMenu->changeMenuOptionsVisibilty(ui::AppMenu::MENU_WINDOWS::DISABLE_ALL_WINDOW);

		if (tab_index == mt::Ignite::tabs::TRACK)
		{
			if (!appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
				return;
		}
		if (tab_index == mt::Ignite::tabs::SCENE)
		{
			if (!appSongComp->isSongCreated())
				return;
		}
		paramId_t paramId = 0;
		appSongComp->setVisible(false);
		appSceneComp->setVisible(false);
		appTrackComp->setVisible(false);
		appPatternComp->setVisible(false);
		componentMenu->setVisible(false);
		optCntPtr->enableKey(IgniteControlOptions::ALL, false);
		IgniteDeviceStatus::GetDevStatusInstance()->devStatusStopTimer();
		resetLedsOnTabChange();
		resetPatternStepModes();
		resetPatternModes();
		if (tab_index != mt::Ignite::tabs::PATTERN)
		{
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FILL_X, fillKeyStatus ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF);
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_SOLO_SKIP, soloKeyStatus ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF);
		}

		switch (tab_index)
		{
		case mt::Ignite::tabs::MENU:
			paramId = (paramId_t)FrontPannelParam::paramKey_MENU;
			componentMenu->setVisible(true);
			componentMenu->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
			if (IgniteInstruments::GetAppInstrumentsInstance()->isVisible())
			{
				IgniteInstruments::GetAppInstrumentsInstance()->refreshInstrumentsUI();
			}
			optionComp->taboptionChanges(mt::Ignite::tabs::MENU, 0);
			MenuMode::GetMenuModeInstance()->setJustification(Justification::centred);
			if (appSongComp->isSongCreated())
			{
				setFpFillAndSoloLedState();
				setFpEditTrackLedState();
			}
			break;
		case mt::Ignite::tabs::SONG:
			paramId = (paramId_t)FrontPannelParam::paramKey_SONG;
			appSongComp->setVisible(true);
			appSongComp->refreshSongUI(true);
			changeTabState(mt::Ignite::tabs::SONG);
			if (!appSongComp->getViewStatus())
				appSongComp->setFpSongLedState();
			else
			{
				setFpFillAndSoloLedState();
				setFpEditTrackLedState();
			}
			break;
		case mt::Ignite::tabs::SCENE:
			paramId = (paramId_t)FrontPannelParam::paramKey_SCENE;
			appSceneComp->setVisible(true);
			Scene.setToggleState(true, dontSendNotification);

			Song.setToggleState(false, dontSendNotification);
			menu.setToggleState(false, dontSendNotification);
			changeTabState(mt::Ignite::tabs::SCENE);
			sceneView = appSceneComp->getViewStatus();
			appSceneComp->changeSceneOptionsVisibility(sceneView);
			if (!sceneView)
				appSceneComp->setFpSceneLedState();
			else
			{
				setFpFillAndSoloLedState();
				setFpEditTrackLedState();
			}
			break;
		case mt::Ignite::tabs::TRACK:
			paramId = (paramId_t)FrontPannelParam::paramKey_TRACK;
			appTrackComp->setVisible(true);
			appSceneComp->updateTracksData();
			IgniteTrack::GetAppTrackInstance()->refreshTrackUI();

			if (appTrackComp->getViewStatus())
				IgniteTrack::GetAppTrackInstance()->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::OPTION_WINDOW);
			optionComp->taboptionChanges(mt::Ignite::tabs::TRACK, appTrackComp->getViewStatus());
			setFpFillAndSoloLedState();
			setFpEditTrackLedState();
			break;
		case mt::Ignite::tabs::PATTERN:
			paramId = (paramId_t)FrontPannelParam::paramKey_PATTERN;
			appPatternComp->setVisible(true);
			changeTabState(mt::Ignite::tabs::PATTERN);
			IgnitePattern::getAppPatternInstance()->refreshPatternUI();
			if (appPatternComp->getTabIndex() == 1)
				appPatternComp->setFpRotaryLedState();

			if (appPatternComp->getTabIndex() != -1)
			{
				if (!appPatternComp->getTabIndex() && appPatternComp->isPatternCreated() && appPatternComp->isInitCompleted())
				{
					appPatternComp->setFpPatternLedState();
					for (int rot = 0; rot < LISTVIEW_MAPPED_COMP; rot++)
					{
						_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY3 + rot), fpLEDPattern::EN_LED_PATT_Blink5_Off);
					}
				}
				else
				{
					appPatternComp->setPatternStepModes();
				}
			}
			break;
		}
		if (paramId)
		{
			clearAllTabKeyLed();// Clear all Led
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)paramId, fpLEDPattern::EN_LED_PATT_ON);
		}
		active_tab = tab_index;
	}

	void AppMainmode::resetLedsOnTabChange()
	{
		std::vector<IgniteParamList> paramlist = {};
		IgniteParamList paramData;
		paramData.MsgValue = fpLEDPattern::EN_LED_PATT_OFF;
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL1; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL2; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL3; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL4; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL5; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL6; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL7; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL8; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL9; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL10; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL11; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL12; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL13; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL14; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL15; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL16; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY1; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY2; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY3; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY4; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY5; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY6; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY7; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY8; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY9; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY10; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY11; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY12; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY13; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY14; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY15; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKROTARY16; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP1; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP2; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP3; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP4; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP5; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP6; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP7; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP8; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP9; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP10; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP11; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP12; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP13; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP14; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP15; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP16; paramlist.push_back(paramData);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramlist);

	}

	void AppMainmode::resetPadLedsOnViewChange()
	{
		std::vector<IgniteParamList> paramlist = {};
		IgniteParamList paramData;
		paramData.MsgValue = fpLEDPattern::EN_LED_PATT_OFF;
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP1; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP2; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP3; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP4; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP5; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP6; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP7; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP8; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP9; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP10; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP11; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP12; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP13; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP14; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP15; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::param_RGB_DISP16; paramlist.push_back(paramData);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramlist);
	}

	void AppMainmode::resetTrackSelLeds()
	{
		std::vector<IgniteParamList> paramlist = {};
		IgniteParamList paramData;
		paramData.MsgValue = fpLEDPattern::EN_LED_PATT_OFF;
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL1; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL2; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL3; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL4; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL5; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL6; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL7; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL8; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL9; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL10; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL11; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL12; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL13; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL14; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL15; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACKSEL16; paramlist.push_back(paramData);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramlist);
	}

	void AppMainmode::resetRotaryLedsOnViewChange()
	{
		for (auto rotary = 0; rotary < 16; rotary++)
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + rotary), fpLEDPattern::EN_LED_PATT_OFF);
	}

	void AppMainmode::startUsbHandler()
	{
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_startPlayTribeUsbHandler, true, false);

	}

	void  AppMainmode::enableTab(mt::Ignite::tabs tab_index, bool state)
	{
		switch (tab_index)
		{
		case mt::Ignite::tabs::MENU:
			menu.setEnabled(state);
			break;
		case mt::Ignite::tabs::SONG:
			Song.setEnabled(state);
			break;
		case mt::Ignite::tabs::SCENE:
			Scene.setEnabled(state);
			break;
		case mt::Ignite::tabs::TRACK:
			Track.setEnabled(state);
			break;
		case mt::Ignite::tabs::PATTERN:
			Pattern.setEnabled(state);
			break;
		}
	}
	void AppMainmode::handleCommandMessage(int id)
	{
		if (id == 10)
		{
			int currentTrackBank = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
			_pInfoWindow->setTextandShow("Current Track Bank : " + String(currentTrackBank + 1));
		}
		else if (id == 11)
		{
			if (appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
				IgniteRecordModale::GetAppRecordInstance()->onSelectionChanged(3);
		}
		mt::Ignite::tabs tab_index = (mt::Ignite::tabs)id;

		switch (tab_index)
		{
		case mt::Ignite::tabs::MENU:
			buttonClicked(&menu);
			break;
		case mt::Ignite::tabs::SONG:
			buttonClicked(&Song);
			break;
		case mt::Ignite::tabs::SCENE:
			if (Scene.isEnabled())
			{
				buttonClicked(&Scene);
				if (active_tab == mt::Ignite::tabs::SCENE)
					//Switch between Row view and Detail view
					appSceneComp->pannelKeyHandler((paramId_t)FrontPannelParam::paramKey_SCENE, 0);
			}
			break;
		case mt::Ignite::tabs::TRACK:
			if (Track.isEnabled())
				buttonClicked(&Track);
			break;
		case mt::Ignite::tabs::PATTERN:
			buttonClicked(&Pattern);
			break;
		case mt::Ignite::tabs::POWER_OFF:
		{
			if (popupPtr->isDialogOpen.get() != true)
			{
				popupPtr->close();
				popupPtr->setPopUpPropories("Power Control", 604, 290);
				popupPtr->addImageButtonwithBounds("Cancel", "off-btn-cancel-default.png", "off-btn-cancel-hover.png", "off-btn-cancel-hover.png", 1, ui::Rectangle<int>{42, 90, 160, 170});
				popupPtr->addImageButtonwithBounds("Power Off", "off-btn-poweroff-default.png", "off-btn-poweroff-hover.png", "off-btn-poweroff-hover.png", 2, ui::Rectangle<int>{222, 90, 160, 170});
				popupPtr->addImageButtonwithBounds("Restart", "off-btn-restart-default.png", "off-btn-restart-hover.png", "off-btn-restart-hover.png", 3, ui::Rectangle<int>{402, 90, 160, 170});
				popupPtr->popupType = POPUP_POWERCTL;
				popupPtr->SetControlBtnLine(false);
				popupPtr->setAutohide(true, 10000);
				popupPtr->isCloseButtonVisible(false);
				popupPtr->show();
				popupPtr->onSelectionChanged = [this](int r)
				{
					if ((r == 2) || (r == 3))
					{
						auto opMode = optCntPtr->getOperationMode();
						if (opMode == mt::Ignite::operatioMode::PLAY_MODE)
							_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramStopSongCmd, fpLEDPattern::EN_LED_PATT_OFF);
						else if (opMode == mt::Ignite::operatioMode::RECORD_MODE)
							_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramStopRecordCmd, fpLEDPattern::EN_LED_PATT_OFF);
						else if (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE)
						{
							_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramStopSongCmd, fpLEDPattern::EN_LED_PATT_OFF);
							_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramStopRecordCmd, fpLEDPattern::EN_LED_PATT_OFF);
						}
						if (r == 2)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_McuSleepMode, 1);
							DBG("Systems Poweroff Initiated");
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
							sleep(1);
#endif
							system("fw_setenv force_reboot no");
						}
						else
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_McuSleepMode, 0);
							DBG("Systems Reboot Initiated");
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
							sleep(1);
#endif
							system("fw_setenv force_reboot yes");
						}
						system("reboot");
					}

					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
				};
			}
		}
		break;
		case mt::Ignite::tabs::INTSOUND:

			if (boIntSoundEnabled)
			{
				boIntSoundEnabled = false;
				_pInfoWindow->setTextandShow("Internal Sound Disabled for All Instruments");
			}
			else
			{
				boIntSoundEnabled = true;
				_pInfoWindow->setTextandShow("Internal Sound Enabled for All Instruments");
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_INTERNALSOUNDS, (boIntSoundEnabled ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF));
			break;
		case mt::Ignite::tabs::BRAY:
			IgniteBRaySettings::GetAppBrayInstance()->enableBray();

			if (boBrayEnabled)
			{
				boBrayEnabled = false;
				_pInfoWindow->setTextandShow("B-Ray Control:OFF");
			}
			else
			{
				boBrayEnabled = true;
				_pInfoWindow->setTextandShow("B-Ray Control:ON");
			}
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_BRAY, (boBrayEnabled ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF));
			break;
		case mt::Ignite::tabs::USB_STOP:
			IgniteMiscSettings::GetAppSettingsInstance()->usbStopKeyPress();
			break;
		}
	}
	void AppMainmode::HandleTabKey(mt::Ignite::tabs tab_index)
	{
		if (hidesliders->isRotarysVisible())
		{
			hidesliders->SetVisible(false);
		}
		this->postCommandMessage((int)tab_index);
	}
	bool AppMainmode::PannelKeyHandler(mt::Ignite::tabs tab_index, paramId_t param, uint32_t KeyValue)
	{

		if ((KeyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusReleased) && (param != (paramId_t)FrontPannelParam::paramKey_ROTARYBAR))
			return true;

		if (tab_index == mt::Ignite::tabs::PATTERN && appPatternComp->getTabIndex() == 3)
		{
			//do nothing if in grid page and main rotary 
		}
		else if ((paramId_t)param == ((paramId_t)FrontPannelParam::paramKey_ROTARY_NAV) )
		{
			if (KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT) //TODO : need to change in MCU
				param = (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT;
			else if (KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT)
				param = (paramId_t)FrontPannelParam::paramKey_RMOVELEFT;
			KeyValue = 1;
		}

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_RELEASE || (FrontPannelParam)param == FrontPannelParam::paramKey_FILTER ||
			(FrontPannelParam)param == FrontPannelParam::paramKey_RESONANCE || (FrontPannelParam)param == FrontPannelParam::paramKey_VOLUME ||
			(FrontPannelParam)param == FrontPannelParam::paramKey_REVERBE || (FrontPannelParam)param == FrontPannelParam::paramKey_CHORUS ||
			(FrontPannelParam)param == FrontPannelParam::paramKey_EQHI || (FrontPannelParam)param == FrontPannelParam::paramKey_EQLO)
		{
			if (tab_index == mt::Ignite::tabs::TRACK && (IgniteTrack::GetAppTrackInstance()->getTraKVisibleTab() == (IgniteTrack::trackScreenIndex)3))
			{
				hidesliders->SetVisible(false);
			}
			else
			{
				std::vector<IgniteParamList> Params;
				IgniteParamList params;
				Params.clear();
				params.param = (paramId_t)SongParam::paramActiveTrackTxInstrumentAvailability;
				Params.push_back(params);
				Params = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, Params);

				if (Params[0].MsgValue.get<uint8>())
				{
					if (!hidesliders->isRotarysVisible())
						hidesliders->SetVisible(true);
					else
						hidesliders->restartTimer();
					hidesliders->PannelKeyHandler(param, KeyValue);
					return true;
				}
			}
		}
		else if (hidesliders->isRotarysVisible())
		{
			hidesliders->SetVisible(false);
		}

		bool handled = false;
		auto opMode = optCntPtr->getOperationMode();

		if (param == (paramId_t)FrontPannelParam::paramKey_PowerKey_Event)
		{
			this->postCommandMessage(5);
			return true;
		}

		else if (param == (paramId_t)FrontPannelParam::paramKey_BRAY)
		{
			if (KeyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed)
				this->postCommandMessage(6);
			return true;
		}

		else if (param == (paramId_t)FrontPannelParam::paramKey_INTERNALSOUNDS)
		{
			if (KeyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed)
				this->postCommandMessage(7);
			return true;
		}

		else if (param == (paramId_t)FrontPannelParam::paramKey_USB_STOP)
		{
			if (KeyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed)
				this->postCommandMessage(9);
			return true;
		}

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_REC && (FrountPannel::GetFrountPannelInstance()->getShiftKeyStatus()))
		{
			if (KeyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed)
			{
				optCntPtr->PannelKeyHandler(param, KeyValue);
				this->postCommandMessage(11);
				return true;
			}
		}
		else if ((FrontPannelParam)param == FrontPannelParam::paramKey_REC || (FrontPannelParam)param == FrontPannelParam::paramKey_BACKFORWARD || (FrontPannelParam)param == FrontPannelParam::paramKey_STOP || (FrontPannelParam)param == FrontPannelParam::paramKey_PLAY || (FrontPannelParam)param == FrontPannelParam::paramKey_SAVE || (FrontPannelParam)param == FrontPannelParam::paramKey_DELETE || optCntPtr->isEditing)
		{
			if (KeyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed)
			{
				if ((FrontPannelParam)param == FrontPannelParam::paramKey_DELETE && appPatternComp->getTabIndex() == 3)
				{
					if (appPatternComp->isPatternCreated() && appPatternComp->isInitCompleted())
						appPatternComp->pannelKeyHandler(param, KeyValue);
				}
				else
				{
					optCntPtr->PannelKeyHandler(param, KeyValue);
					if (appPatternComp->isVisible() && appPatternComp->isPatternCreated() && appPatternComp->isInitCompleted())
					{
						if (((FrontPannelParam)param == FrontPannelParam::paramKey_STOP) || ((FrontPannelParam)param == FrontPannelParam::paramKey_PLAY && (opMode == mt::Ignite::operatioMode::PLAY_MODE)))
						{
							if (appPatternComp->getSculptKeyStatus())
							{
								appPatternComp->setSulptKeyStatus(false);
								_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_SCULPT, (fpLEDPattern::EN_LED_PATT_OFF));
								_pInfoWindow->setTextandShow("SCULPT: OFF");
							}
						}
					}
				}

				return true;
			}
		}

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_NEXT_TIE && optCntPtr->getOperationMode() == mt::Ignite::operatioMode::PLAY_MODE)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SceneParam::paramManualPlayNextSceneCmd, (uint32_t)0);
			return true;
		}

		if (!IgniteConnectivity::GetAppConnectivityInstance()->isVisible())
		{
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_TRACKSEL1:
			case FrontPannelParam::paramKey_TRACKSEL2:
			case FrontPannelParam::paramKey_TRACKSEL3:
			case FrontPannelParam::paramKey_TRACKSEL4:
			case FrontPannelParam::paramKey_TRACKSEL5:
			case FrontPannelParam::paramKey_TRACKSEL6:
			case FrontPannelParam::paramKey_TRACKSEL7:
			case FrontPannelParam::paramKey_TRACKSEL8:
			case FrontPannelParam::paramKey_TRACKSEL9:
			case FrontPannelParam::paramKey_TRACKSEL10:
			case FrontPannelParam::paramKey_TRACKSEL11:
			case FrontPannelParam::paramKey_TRACKSEL12:
			case FrontPannelParam::paramKey_TRACKSEL13:
			case FrontPannelParam::paramKey_TRACKSEL14:
			case FrontPannelParam::paramKey_TRACKSEL15:
			case FrontPannelParam::paramKey_TRACKSEL16:
				if (FrountPannel::GetFrountPannelInstance()->getBarKeyStatus() == FrontPannelKeyStatus::paramKeyStatusOnHold)
					handled = changeTrackBank(param, KeyValue);
				else
				{
					if (soloKeyStatus == true)
						handled = handleTrackSolo(param, KeyValue);
					else
						handled = handleTrackMute(param, KeyValue);
				}
				break;
			case FrontPannelParam::paramKey_TRACKROTARY1:
			case FrontPannelParam::paramKey_TRACKROTARY2:
			case FrontPannelParam::paramKey_TRACKROTARY3:
			case FrontPannelParam::paramKey_TRACKROTARY4:
			case FrontPannelParam::paramKey_TRACKROTARY5:
			case FrontPannelParam::paramKey_TRACKROTARY6:
			case FrontPannelParam::paramKey_TRACKROTARY7:
			case FrontPannelParam::paramKey_TRACKROTARY8:
			case FrontPannelParam::paramKey_TRACKROTARY9:
			case FrontPannelParam::paramKey_TRACKROTARY10:
			case FrontPannelParam::paramKey_TRACKROTARY11:
			case FrontPannelParam::paramKey_TRACKROTARY12:
			case FrontPannelParam::paramKey_TRACKROTARY13:
			case FrontPannelParam::paramKey_TRACKROTARY14:
			case FrontPannelParam::paramKey_TRACKROTARY15:
			case FrontPannelParam::paramKey_TRACKROTARY16:
				handled = handleEditTrack(param, KeyValue);
				break;
			case FrontPannelParam::paramKey_FILL_X:
				if (active_tab != mt::Ignite::tabs::PATTERN)
				{
					handled = handleFillMode(param, KeyValue);
					componentMenu->PannelKeyHandler((paramId_t)param, KeyValue);
				}
				break;
			case FrontPannelParam::paramKey_SOLO_SKIP:
				if (active_tab != mt::Ignite::tabs::PATTERN)
				{
					handled = handleSoloMode(param, KeyValue);
					componentMenu->PannelKeyHandler((paramId_t)param, KeyValue);
				}
				break;
			case FrontPannelParam::paramKey_ROTARYBAR:
				handled = showTrackBank(param, KeyValue);
				break;
			case FrontPannelParam::paramRot_BAR:
				handled = handleTrackBank(param, KeyValue);
				break;
			}
		}
		if (optCntPtr->isSavePopUpOn && (param == (paramId_t)FrontPannelParam::paramKey_RSELECT || param == (paramId_t)FrontPannelParam::paramKey_RETURN_NAV))
		{
			optCntPtr->isSavePopUpOn = false;
		}

		if (optCntPtr->isDeletePopUpOn && (param == (paramId_t)FrontPannelParam::paramKey_RSELECT || param == (paramId_t)FrontPannelParam::paramKey_RETURN_NAV))
		{
			optCntPtr->isDeletePopUpOn = false;
		}

		if (!handled)
		{
			if (KeyValue != (uint8_t)FrontPannelKeyStatus::paramKeyStatusOnHold || (param == (paramId_t)FrontPannelParam::paramKey_ROTARYBAR) ||
				(param == (paramId_t)FrontPannelParam::paramKey_PLUS_NAV) || (param == (paramId_t)FrontPannelParam::paramKey_MINUS_NAV))
			{
				switch (tab_index)
				{
				case mt::Ignite::tabs::MENU:
					handled = componentMenu->PannelKeyHandler(param, KeyValue);
					break;
				case mt::Ignite::tabs::SONG:
					handled = appSongComp->pannelKeyHandler(param, KeyValue);
					break;
				case mt::Ignite::tabs::SCENE:
					if (Scene.isEnabled())
						handled = appSceneComp->pannelKeyHandler(param, KeyValue);
					break;
				case mt::Ignite::tabs::TRACK:
					if (Track.isEnabled())
						appTrackComp->PannelKeyHandler(param, KeyValue);
					break;
				case mt::Ignite::tabs::PATTERN:
					if (Pattern.isEnabled())
						appPatternComp->pannelKeyHandler(param, KeyValue);
					break;
				}
			}
		}

		return true;
	}

	bool AppMainmode::showTrackBank(paramId_t param, uint32_t KeyValue)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if ((active_tab != mt::Ignite::tabs::PATTERN) && (((active_tab == mt::Ignite::tabs::SONG) && appSongComp->getViewStatus()) || ((active_tab == mt::Ignite::tabs::SCENE) && appSceneComp->getViewStatus()) || active_tab == mt::Ignite::tabs::MENU || ((active_tab == mt::Ignite::tabs::TRACK))))
		{
			if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				auto trackBanks = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::NUM_TRACK_BANK_INDEX);
				auto currentTrackBank = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
				if (FrountPannel::GetFrountPannelInstance()->getKeyStatus((paramId_t)FrontPannelParam::paramKey_ROTARYBAR) == FrontPannelKeyStatus::paramKeyStatusOnHold)
				{
					this->postCommandMessage(10);
					AppMainmode::getMainModeInstance()->resetPadLedsOnViewChange();
					for (int trackBank = 0; trackBank < trackBanks; trackBank++)
					{
						if (trackBank == currentTrackBank)
							_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + trackBank), fpLEDPattern::EN_RGB_LED_GREEN);
						else
							_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + trackBank), fpLEDPattern::EN_RGB_LED_LPURPLE);
					}
				}
				else if (FrountPannel::GetFrountPannelInstance()->getKeyStatus((paramId_t)FrontPannelParam::paramKey_ROTARYBAR) == FrontPannelKeyStatus::paramKeyStatusReleased)
				{
					setFpFillAndSoloLedState();
					setFpEditTrackLedState();
				}
			}
			return true;
		}
		return false;
	}

	bool AppMainmode::changeTrackBank(paramId_t param, uint32_t KeyValue)
	{
		if ((active_tab != mt::Ignite::tabs::PATTERN) && (((active_tab == mt::Ignite::tabs::SONG) && appSongComp->getViewStatus()) || ((active_tab == mt::Ignite::tabs::SCENE) && appSceneComp->getViewStatus()) || active_tab == mt::Ignite::tabs::MENU || ((active_tab == mt::Ignite::tabs::TRACK))))
		{
			if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_TRACKSEL1:
				case FrontPannelParam::paramKey_TRACKSEL2:
				case FrontPannelParam::paramKey_TRACKSEL3:
				case FrontPannelParam::paramKey_TRACKSEL4:
					appTrackComp->getTrackBankAndUpdate((param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1));
					TrackMixer::GetTrackMixerInstance()->getSelectedTrackMixerBankAndUpdate((param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1) + 1);
					break;
				}
			}
			return true;
		}
		return false;
	}

	bool AppMainmode::handleTrackBank(paramId_t param, uint32_t KeyValue)
	{
		if ((active_tab != mt::Ignite::tabs::PATTERN) && (((active_tab == mt::Ignite::tabs::SONG) && appSongComp->getViewStatus()) || ((active_tab == mt::Ignite::tabs::SCENE) && appSceneComp->getViewStatus()) || active_tab == mt::Ignite::tabs::MENU || ((active_tab == mt::Ignite::tabs::TRACK))))
		{
			if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				auto currentTrackBank = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
				appTrackComp->setCurrentTrackBank(currentTrackBank);
				if (KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT)
				{
					appTrackComp->getNextTrackBankAndUpdate(false);
					setFpFillAndSoloLedState();
					setFpEditTrackLedState();
					TrackMixer::GetTrackMixerInstance()->getTrackMixerBankAndUpdate(false);
				}
				else if (KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT)
				{
					appTrackComp->getNextTrackBankAndUpdate(true);
					setFpFillAndSoloLedState();
					setFpEditTrackLedState();
					TrackMixer::GetTrackMixerInstance()->getTrackMixerBankAndUpdate(true);
				}
			}
			return true;
		}
		return false;
	}

	bool AppMainmode::handleTrackSolo(paramId_t param, uint32_t KeyValue)
	{
		bool trackFillStatus = false;
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		bool isValidTab = (active_tab == mt::Ignite::tabs::SONG && appSongComp->getViewStatus()) ||
			(active_tab == mt::Ignite::tabs::SCENE && appSceneComp->getViewStatus()) ||
			active_tab == mt::Ignite::tabs::MENU ||
			(active_tab == mt::Ignite::tabs::TRACK && !appTrackComp->getViewStatus());

		if (active_tab != mt::Ignite::tabs::PATTERN && isValidTab)
		{
			if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				int currentTrackBank = appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
				int currentTrack = (currentTrackBank * 16) + (param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1);
				appSceneComp->currentTrack = currentTrack;

				if (appSongComp->isTrackConfigured(currentTrack))
				{
					bool soloStatus = !trackSoloStatus[currentTrack];
					trackSoloStatus[currentTrack] = soloStatus;
					appTrackComp->setTrackData(mt::Ignite::trackDataIndex::TRACK_SOLO_MODE, soloStatus, false, currentTrack);

					auto scDataPtr = appSongComp->getSceneData(appSceneComp->getSelected());

					if (scDataPtr != nullptr)
						trackFillStatus = scDataPtr->track_data[currentTrack].fillPattern != " ";

					if(trackFillStatus)
						_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel,
						param + (paramId_t)FrontPannelParam::paramKey_EQLO, (uint8_t)(soloStatus ? fpLEDPattern::EN_RGB_LED_RED : fpLEDPattern::EN_RGB_LED_WHITE));
					else
						_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel,
						param + (paramId_t)FrontPannelParam::paramKey_EQLO, (uint8_t)(soloStatus ? fpLEDPattern::EN_RGB_LED_GREEN : fpLEDPattern::EN_LED_PATT_OFF));
					appTrackComp->setTrackSoloDirtyFlag(true);

					if (!appTrackComp->getViewStatus())
						IgniteTrack::GetAppTrackInstance()->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::TRACK_WINDOW);
					return true;
				}
			}
		}

		return false;
	}

	bool AppMainmode::handleSoloMode(paramId_t param, uint32_t KeyValue)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusReleased)
			return true;
		else if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusPressed)
		{
			if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				soloKeyStatus = !soloKeyStatus;

				if (fillKeyStatus && soloKeyStatus)
					setFpTrackFillAndSoloLedState();
				else if (fillKeyStatus)
					setFpTrackFillLedState();
				else if (soloKeyStatus)
					setFpTrackSoloLedState();
				else
					setFpTrackLedState();

				return true;
			}
		}
		return false;
	}

	void AppMainmode::setFpTrackSoloLedState()
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));
		mt::Ignite::sceneData* scDataPtr;
		bool soloStatus = false;

		if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
		{
			auto currentTrackBank = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
			scDataPtr = appSongComp->getSceneData(appSceneComp->getSelected());
			AppMainmode::getMainModeInstance()->resetPadLedsOnViewChange();

			for (auto track = (currentTrackBank * 16); track < (16 * (currentTrackBank + 1)); track++)
			{
				if (scDataPtr != nullptr)
					soloStatus = scDataPtr->track_data[track].soloMode;

				if (soloStatus)
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + (track % 16)), fpLEDPattern::EN_RGB_LED_GREEN);
				else
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + (track % 16)), fpLEDPattern::EN_LED_PATT_OFF);
			}
		}
	}

	bool AppMainmode::handleFillMode(paramId_t param, uint32_t KeyValue)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusReleased)
			return true;
		else if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusPressed)
		{
			if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				fillKeyStatus = !fillKeyStatus;

				if (soloKeyStatus && fillKeyStatus)
					setFpTrackFillAndSoloLedState();
				else if (soloKeyStatus)
					setFpTrackSoloLedState();
				else if (fillKeyStatus)
					setFpTrackFillLedState();
				else
					setFpTrackLedState();

				return true;
			}
		}
		return false;
	}

	void AppMainmode::setFpTrackFillLedState()
	{
		bool trackFillStatus = false;
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if (gSongs.isEmpty() || !appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			return;

		auto currentTrackBank = static_cast<int>(appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK));
		auto scDataPtr = appSongComp->getSceneData(appSceneComp->getSelected());

		if (scDataPtr == nullptr)
			return;

		AppMainmode::getMainModeInstance()->resetPadLedsOnViewChange();

		for (auto track = (currentTrackBank * 16); track < (16 * (currentTrackBank + 1)); track++)
		{
			if (scDataPtr != nullptr)
				trackFillStatus = scDataPtr->track_data[track].fillPattern != " ";

			if (trackFillStatus)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + (track % 16)), fpLEDPattern::EN_RGB_LED_WHITE);
			else
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + (track % 16)), fpLEDPattern::EN_LED_PATT_OFF);
		}
	}

	void AppMainmode::setFpFillAndSoloLedState()
	{
		if (getFillKeyStatus())
		{
			if (getSoloKeyStatus())
				setFpTrackFillAndSoloLedState();
			else
				setFpTrackFillLedState();
		}
		else if (getSoloKeyStatus())
			setFpTrackSoloLedState();
		else
			setFpTrackLedState();
	}

	void AppMainmode::setFpTrackFillAndSoloLedState()
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if (gSongs.isEmpty() || !appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			return;

		auto currentTrackBank = static_cast<int>(appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK));
		auto scDataPtr = appSongComp->getSceneData(appSceneComp->getSelected());

		if (scDataPtr == nullptr)
			return;

		AppMainmode::getMainModeInstance()->resetPadLedsOnViewChange();

		const int startTrack = currentTrackBank * 16;
		const int endTrack = startTrack + 16;

		for (int track = startTrack; track < endTrack; ++track)
		{
			auto paramId = static_cast<paramId_t>(static_cast<uint8_t>(FrontPannelParam::param_RGB_DISP1) + (track % 16));
			fpLEDPattern ledPattern = fpLEDPattern::EN_LED_PATT_OFF;

			if (scDataPtr->track_data[track].fillPattern != " ")
			{
				ledPattern = scDataPtr->track_data[track].soloMode ? fpLEDPattern::EN_RGB_LED_RED : fpLEDPattern::EN_RGB_LED_WHITE;
			}
			else if (scDataPtr->track_data[track].soloMode)
			{
				ledPattern = fpLEDPattern::EN_RGB_LED_GREEN;
			}

			_PUiVirtualEngine->setParam(static_cast<moduleId_t>(ModuleName::moduleUI), static_cast<moduleId_t>(ModuleName::moduleFrontPannel), paramId, ledPattern);
		}
	}

	bool AppMainmode::handleEditTrack(paramId_t param, uint32_t KeyValue)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if (gSongs.isEmpty() || !appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			return false;

		if (active_tab == mt::Ignite::tabs::PATTERN || active_tab == mt::Ignite::tabs::TRACK)
			return false;

		if (active_tab == mt::Ignite::tabs::SONG || active_tab == mt::Ignite::tabs::SCENE || active_tab == mt::Ignite::tabs::MENU)
		{
			auto currentTrackBank = static_cast<int>(appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK));

			for (int trackIndex = 0; trackIndex < 16; ++trackIndex)
			{
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + trackIndex), fpLEDPattern::EN_LED_PATT_OFF);
			}

			auto currentEditTrack = (currentTrackBank * 16) + (param - static_cast<paramId_t>(FrontPannelParam::paramKey_TRACKROTARY1));
			appSceneComp->setSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK, currentEditTrack, false);
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)param, fpLEDPattern::EN_LED_PATT_ON);
			appTrackComp->setCurrentTrackData();
			appTrackComp->updateSelectionInfo();
			return true;
		}

		return false;
	}

	void AppMainmode::setFpEditTrackLedState()
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
		{
			auto editTrack = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK);
			auto currentTrackBank = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);

			for (auto trackIndex = 0; trackIndex < 16; trackIndex++)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + trackIndex), fpLEDPattern::EN_LED_PATT_OFF);

			for (auto track = (currentTrackBank * 16); track < (16 * (currentTrackBank + 1)); track++)
			{
				if (track == editTrack)
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::paramKey_TRACKROTARY1 + (track % 16)), fpLEDPattern::EN_LED_PATT_ON);
				else
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::paramKey_TRACKROTARY1 + (track % 16)), fpLEDPattern::EN_LED_PATT_OFF);
			}
		}
	}

	bool AppMainmode::handleTrackMute(paramId_t param, uint32_t KeyValue)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		if (active_tab == mt::Ignite::tabs::PATTERN || fillKeyStatus == true)
			return false;

		bool isSongOrSceneOrMenuView = ((active_tab == mt::Ignite::tabs::SONG) && appSongComp->getViewStatus()) ||
			((active_tab == mt::Ignite::tabs::SCENE) && appSceneComp->getViewStatus()) ||
			(active_tab == mt::Ignite::tabs::MENU);

		if (!isSongOrSceneOrMenuView || gSongs.isEmpty() || !appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			return false;

		int currentTrackBank = static_cast<int>(appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK));
		auto currentTrack = (currentTrackBank * 16) + (param - static_cast<paramId_t>(FrontPannelParam::paramKey_TRACKSEL1));
		appSceneComp->currentTrack = currentTrack;

		if (!appSongComp->isTrackConfigured(currentTrack))
			return false;

		auto muteStatus = !trackMuteStatus[currentTrack];
		trackMuteStatus[currentTrack] = muteStatus;

		appTrackComp->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, muteStatus, false, currentTrack);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (param + (paramId_t)FrontPannelParam::paramKey_EQLO), (uint8_t)(muteStatus ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
		appTrackComp->setTrackMuteDirtyFlag(true);
		appSongComp->_pSongView->updateActiveTracks();

		return true;
	}


	void AppMainmode::setFpTrackLedState()
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));
		mt::Ignite::sceneData* scDataPtr;
		bool trackStatus = false;

		if (!gSongs.isEmpty() && appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
		{
			scDataPtr = appSongComp->getSceneData(appSceneComp->getSelected());
			auto currentTrackBank = (int)appSceneComp->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
			AppMainmode::getMainModeInstance()->resetPadLedsOnViewChange();

			for (auto track = (currentTrackBank * 16); track < (16 * (currentTrackBank + 1)); track++)
			{
				if (scDataPtr != nullptr)
					trackStatus = scDataPtr->track_data[track].trackState;

				if (!trackStatus)
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::param_RGB_DISP1 + (track % 16)), fpLEDPattern::EN_RGB_LED_LBLUE);
				else
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::param_RGB_DISP1 + (track % 16)), fpLEDPattern::EN_LED_PATT_OFF);
			}
		}
	}

	void AppMainmode::resized()
	{
		menu.setBounds(12, 0, 110, 76);
		Song.setBounds(127, 0, 110, 76);
		Scene.setBounds(242, 0, 110, 76);
		Track.setBounds(357, 0, 110, 76);
		Pattern.setBounds(472, 0, 110, 76);
		optCntPtr->setBounds(layout::paramsbar);
		appSongComp->setBounds((int)0, (int)heighttabBox, (int)getWidth(), (int)(getHeight()));
		appSceneComp->setBounds((int)0, (int)heighttabBox, (int)getWidth(), (int)(getHeight()));
		appTrackComp->setBounds((int)0, (int)heighttabBox, (int)getWidth(), (int)(getHeight()));
		appPatternComp->setBounds((int)0, (int)heighttabBox, (int)getWidth(), (int)(getHeight()));
		componentMenu->setBounds((int)0, (int)heighttabBox, (int)getWidth(), (int)(getHeight() + 2));
		optionComp->setBounds(212, heighttabBox, (getWidth() / 2) + 300, 64);
		RecordModale->setBounds(170, 60, 604, 360);
		hidesliders->setBounds(0, 0, 1024, 600);
		_pInfoWindow->setBounds(0, 0, 1024, 600);
	}
	void AppMainmode::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		menu.setToggleState(false, dontSendNotification);
		Song.setToggleState(false, dontSendNotification);
		Scene.setToggleState(false, dontSendNotification);
		Pattern.setToggleState(false, dontSendNotification);
		Track.setToggleState(false, dontSendNotification);
		if (buttonThatWasClicked == &menu)
		{
			if (active_tab != mt::Ignite::tabs::MENU)
			{
				changeTabVisibility(mt::Ignite::tabs::MENU, true);
			}
			menu.setToggleState(true, dontSendNotification);
		}
		else if (buttonThatWasClicked == &Song)
		{
			if (active_tab != mt::Ignite::tabs::SONG)
			{
				changeTabVisibility(mt::Ignite::tabs::SONG, true);
			}
			else
			{
				if (appSongComp->getViewStatus())
				{
					//Song.setImage("topnav-song-default.png", "topnav-song-active2.png", "topnav-song-disable.png");
					appSongComp->changeSongOptionsVisibility(false);
					if (appSongComp->isVisible())
						optionComp->taboptionChanges(mt::Ignite::tabs::SONG, 0);
				}
				else
				{
					//Song.setImage("topnav-song-default.png", "topnav-song-active.png", "topnav-song-disable.png");
					appSongComp->changeSongOptionsVisibility(true);
					if (appSongComp->isVisible())
						optionComp->taboptionChanges(mt::Ignite::tabs::SONG, 1);
				}
			}
			Song.setToggleState(true, dontSendNotification);
		}
		else if (buttonThatWasClicked == &Scene)
		{
			if (active_tab != mt::Ignite::tabs::SCENE)
				changeTabVisibility(mt::Ignite::tabs::SCENE, true);
			else
			{
				if (appSceneComp->getViewStatus())
				{
					appSceneComp->changeSceneOptionsVisibility(false);
					if (appSceneComp->isVisible())
						optionComp->taboptionChanges(mt::Ignite::tabs::SCENE, 0);
				}
				else
				{
					appSceneComp->changeSceneOptionsVisibility(true);
					if (appSceneComp->isVisible())
						optionComp->taboptionChanges(mt::Ignite::tabs::SCENE, 1);
				}
			}
			Scene.setToggleState(true, dontSendNotification);
		}
		else if (buttonThatWasClicked == &Track)
		{
			if (active_tab != mt::Ignite::tabs::TRACK)
				changeTabVisibility(mt::Ignite::tabs::TRACK, true);
			else
			{
				if (appTrackComp->getViewStatus())
				{
					appTrackComp->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::TRACK_WINDOW);
					if (appTrackComp->isVisible())
						optionComp->taboptionChanges(mt::Ignite::tabs::TRACK, 0);
				}
				else
				{
					appTrackComp->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::OPTION_WINDOW);
					if (appTrackComp->isVisible())
						optionComp->taboptionChanges(mt::Ignite::tabs::TRACK, 1);
				}
			}
			Track.setToggleState(true, dontSendNotification);
		}
		else if (buttonThatWasClicked == &Pattern)
		{
			if (active_tab != mt::Ignite::tabs::PATTERN)
			{
				changeTabVisibility(mt::Ignite::tabs::PATTERN, true);
				optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, appPatternComp->getTabIndex());
			}
			else
			{
				if (appPatternComp->getTabIndex() == 0)
				{
					appPatternComp->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
					optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, 1);
				}
				else if (appPatternComp->getTabIndex() == 1)
				{
					appPatternComp->changePatternViewVisibility(IgnitePattern::PatternView::BAR);
					optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, 2);
				}
				else if (appPatternComp->getTabIndex() == 2)
				{
					appPatternComp->changePatternViewVisibility(IgnitePattern::PatternView::GRID);
					optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, 3);
				}
				else
				{
					appPatternComp->changePatternViewVisibility(IgnitePattern::PatternView::LIST);
					optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, 0);
				}
			}
			Pattern.setToggleState(true, dontSendNotification);
		}
	}
	void AppMainmode::changeTabState(mt::Ignite::tabs opt)
	{
		switch (opt)
		{
		case mt::Ignite::tabs::MENU:

			buttonClicked(&menu);
			break;
		case mt::Ignite::tabs::SONG:
			if (!(appSongComp->getViewStatus()))
			{
				if (appSongComp->isVisible())
					optionComp->taboptionChanges(mt::Ignite::tabs::SONG, 0);
			}
			else
			{
				if (appSongComp->isVisible())
					optionComp->taboptionChanges(mt::Ignite::tabs::SONG, 1);
			}
			break;
		case mt::Ignite::tabs::SCENE:
			if (!(appSceneComp->getViewStatus()))
			{
				if (appSceneComp->isVisible())
					optionComp->taboptionChanges(mt::Ignite::tabs::SCENE, 0);
			}
			else
			{
				if (appSceneComp->isVisible())
					optionComp->taboptionChanges(mt::Ignite::tabs::SCENE, 1);
			}
			break;
		case mt::Ignite::tabs::TRACK:
			if (!(appTrackComp->getViewStatus()))
			{
				if (appTrackComp->isVisible())
					optionComp->taboptionChanges(mt::Ignite::tabs::TRACK, 0);
			}
			else
			{
				if (appTrackComp->isVisible())
					optionComp->taboptionChanges(mt::Ignite::tabs::TRACK, 1);
			}
			break;
		case mt::Ignite::tabs::PATTERN:
			if ((appPatternComp->getTabIndex() == 2) || (appPatternComp->getTabIndex() == 3))
			{
				optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, 2);
			}
			else if (appPatternComp->getTabIndex() == 0)
			{
				optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, 0);
			}
			else
			{
				optionComp->taboptionChanges(mt::Ignite::tabs::PATTERN, 1);
			}
			break;
		}
		repaint();
	}

	void AppMainmode::triggerTabChange(mt::Ignite::tabs t)
	{
		menu.setToggleState(false, dontSendNotification);
		Song.setToggleState(false, dontSendNotification);
		Scene.setToggleState(false, dontSendNotification);
		Track.setToggleState(false, dontSendNotification);
		Pattern.setToggleState(false, dontSendNotification);
		switch (t)
		{
		case mt::Ignite::tabs::MENU:
			buttonClicked(&menu);
			break;
		case mt::Ignite::tabs::SONG:
			buttonClicked(&Song);
			break;
		case mt::Ignite::tabs::SCENE:
			buttonClicked(&Scene);
			break;
		case mt::Ignite::tabs::TRACK:
			buttonClicked(&Track);
			break;
		case mt::Ignite::tabs::PATTERN:
			buttonClicked(&Pattern);
			break;
		default:
			break;
		}
	}

	void AppMainmode::resetPatternModes()
	{
		appPatternComp->setTieKeyStatus(false);
		appPatternComp->setTransposeKeyStatus(false);
		appPatternComp->setSkipKeyStatus(false);
		appPatternComp->resetGangStatus();
		appPatternComp->setLastKeyStatus(false);
	}

	void AppMainmode::resetPatternStepModes()
	{
		resetPadLedsOnViewChange();
		resetTrackSelLeds();
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_NEXT_TIE, fpLEDPattern::EN_LED_PATT_OFF);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FILL_X, fpLEDPattern::EN_LED_PATT_OFF);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_SOLO_SKIP, fpLEDPattern::EN_LED_PATT_OFF);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_INSERT, fpLEDPattern::EN_LED_PATT_OFF);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_GANG, fpLEDPattern::EN_LED_PATT_OFF);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_LAST, fpLEDPattern::EN_LED_PATT_OFF);
	}

	void AppMainmode::clearAllTabKeyLed()
	{
		std::vector<IgniteParamList> paramlist = {};
		IgniteParamList paramData;
		paramData.MsgValue = fpLEDPattern::EN_LED_PATT_OFF;
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_MENU; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_SONG; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_SCENE; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_TRACK; paramlist.push_back(paramData);
		paramData.param = (paramId_t)(paramId_t)FrontPannelParam::paramKey_PATTERN; paramlist.push_back(paramData);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramlist);
	}
};
