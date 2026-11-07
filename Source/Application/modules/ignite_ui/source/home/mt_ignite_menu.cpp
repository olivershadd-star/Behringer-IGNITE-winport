#include "mt_ignite_menu.h"
extern std::unique_ptr<IDevice> _PUiVirtualEngine;

//==============================================================================
namespace ui
{
	AppMenuOptions::AppMenuOptions(AppMenu* parentPtr)
	{
		menuPtr = parentPtr;
		menuModeptr = MenuMode::GetMenuModeInstance();
		instrumentButton.makeVisibleAndAddListner(this);
		songButton.makeVisibleAndAddListner(this);
		sceneButton.makeVisibleAndAddListner(this);
		browser.makeVisibleAndAddListner(this);

		patternButton.makeVisibleAndAddListner(this);
		trackButton.makeVisibleAndAddListner(this);
		midiConfigButton.makeVisibleAndAddListner(this);
		cvioButton.makeVisibleAndAddListner(this);

		drumButton.makeVisibleAndAddListner(this);
		calibrationButton.makeVisibleAndAddListner(this);
		recordButton.makeVisibleAndAddListner(this);
		settingsButton.makeVisibleAndAddListner(this);
		
		optionptr = AppOptions::GetOptionsInstance();

		instrumentButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		midiConfigButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		cvioButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		songButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		sceneButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		trackButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		patternButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		recordButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		settingsButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		addMouseListener(this, true);
		/*INSTRUMENT, //Row 1
			MIDI_CONFIG,
			CVIO_CONFIG,
			SONG,
			SCENE,
			TRACK,
			PATTERN, //Row 2
			RECORD, // Row 3
			SETTINGS,*/
		instrumentButton.setComponentID(String(INSTRUMENT));
		midiConfigButton.setComponentID(String(MIDI_CONFIG));
		cvioButton.setComponentID(String(CVIO_CONFIG));
		songButton.setComponentID(String(SONG));
		sceneButton.setComponentID(String(SCENE));
		trackButton.setComponentID(String(TRACK));
		patternButton.setComponentID(String(PATTERN));
		recordButton.setComponentID(String(RECORD));
		settingsButton.setComponentID(String(SETTINGS));

		instrumentButton.setDefaultOverImage( "link-instrument-active.png");
		songButton.setDefaultOverImage("link-song-active.png"); 
		sceneButton.setDefaultOverImage("link-scene-active.png");

		patternButton.setDefaultOverImage("link-pattern-active.png");
		trackButton.setDefaultOverImage("link-track-active.png"); 
		midiConfigButton.setDefaultOverImage("link-midiconfig-active.png");
		cvioButton.setDefaultOverImage("link-cvioconfig-active.png");

		drumButton.setDefaultOverImage("drumconfig-active.png");
		calibrationButton.setDefaultOverImage("calibration-active.png");
		recordButton.setDefaultOverImage("link-record-active.png");
		settingsButton.setDefaultOverImage("link-settings-active.png");
		//settingsButton{ "Settings","link-settings-default.png","link-settings-active.png","link-settings-active.png" };

		r1.items.add(FlexItem(instrumentButton).withFlex(1));
		r1.items.add(FlexItem(midiConfigButton).withFlex(1));
		r1.items.add(FlexItem(cvioButton).withFlex(1));

		r2.items.add(FlexItem(songButton).withFlex(1));
		r2.items.add(FlexItem(sceneButton).withFlex(1));
		r2.items.add(FlexItem(trackButton).withFlex(1));

		r3.items.add(FlexItem(patternButton).withFlex(1));
		r3.items.add(FlexItem(recordButton).withFlex(1));
		r3.items.add(FlexItem(settingsButton).withFlex(1));

		box.flexDirection = FlexBox::Direction::column;
		box.items.add(FlexItem(r1).withFlex(1));
		box.items.add(FlexItem(r2).withFlex(1));
		box.items.add(FlexItem(r3).withFlex(1));
		//	box.items.add(FlexItem(r4).withMargin(1).withFlex(1));
		optionptr->showOptions(false);
		menuModeptr->onBackbtnpress = [this](int btn)
		{
			changeMenuWindowState(activeBtnptr, false);
		};
	}

	AppMenuOptions::~AppMenuOptions()
	{}

	//==============================================================================
	void AppMenuOptions::paint(juce::Graphics& g)
	{
		g.fillAll(Theme::Instance().getColour(neutralBlack));
	}

	void AppMenuOptions::resized()
	{
		box.performLayout(ui::Rectangle(10, 10, layout::mainmode.getWidth() - 20, widthMenuOptions));
	}

	void AppMenuOptions::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked->getToggleState())
			activeBtnptr = buttonThatWasClicked;
		if (buttonThatWasClicked == &browser)
		{
		}
		else if (buttonThatWasClicked == &instrumentButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::INSTR_WINDOW);
			if (instrumentButton.getToggleState())
				instrumentButton.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &songButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SONG_WINDOW);
			if (songButton.getToggleState())
				songButton.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &sceneButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SCENE_WINDOW);
			if (sceneButton.getToggleState())
				sceneButton.setToggleState(false, dontSendNotification);
			IgniteSceneConfig::getAppSceneConfigInstance()->updateData(true);
		}
		else if (buttonThatWasClicked == &patternButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::PATTERN_WINDOW);
			if (patternButton.getToggleState())
				patternButton.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &trackButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::TRACK_WINDOW);
			if (trackButton.getToggleState())
				trackButton.setToggleState(false, dontSendNotification);
			IgniteTrackConfig::GetAppTrackConfigInstance()->updateData();
		}
		else if (buttonThatWasClicked == &calibrationButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::CALIB_WINDOW);
			if (calibrationButton.getToggleState())
				calibrationButton.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &recordButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::RECORD_WINDOW);
			if (recordButton.getToggleState())
				recordButton.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &settingsButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			if (settingsButton.getToggleState())
				settingsButton.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &cvioButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::CVIO_WINDOW);
			if (cvioButton.getToggleState())
				cvioButton.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &midiConfigButton)
		{
			menuPtr->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MIDI_WINDOW);
			if (midiConfigButton.getToggleState())
				midiConfigButton.setToggleState(false, dontSendNotification);
		}

	}

	void AppMenuOptions::changeMenuWindowState(juce::Button* btn, bool state)
	{
		if (btn == &browser)
		{
			browser.setToggleState(state, dontSendNotification);
		}
		else if (btn == &instrumentButton)
		{
			instrumentButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &songButton)
		{
			songButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &sceneButton)
		{
			sceneButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &patternButton)
		{
			patternButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &trackButton)
		{
			trackButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &calibrationButton)
		{
			calibrationButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &recordButton)
		{
			recordButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &midiConfigButton)
		{
			midiConfigButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &cvioButton)
		{
			cvioButton.setToggleState(state, dontSendNotification);
		}
		else if (btn == &settingsButton)
		{
			settingsButton.setToggleState(state, dontSendNotification);
		}
	}

	void AppMenuOptions::mouseDown(const MouseEvent& event)
	{
		auto id=event.eventComponent->getComponentID();
		if (id >= String(INSTRUMENT) && id <= String(SETTINGS))
		{
			int a = std::stoi((id.toStdString()));
			PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_MouseClick, 1);
			KeyFocusedItem = a;
			PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_MouseClick, 1);
		}
	}

	//==============================================================================

	AppMenu::AppMenu()
	{
		menuOptions = new AppMenuOptions(this);
		addAndMakeVisible(menuOptions);

		instrInstance = IgniteInstruments::GetAppInstrumentsInstance();
		addChildComponent(instrInstance);
		instrInstance->setVisible(false);

		songInstance = IgniteSongConfig::getAppSongConfigInstance();
		addChildComponent(songInstance);
		songInstance->setVisible(false);

		sceneInstance = IgniteSceneConfig::getAppSceneConfigInstance();
		addChildComponent(sceneInstance);
		sceneInstance->setVisible(false);

		trackInstance = IgniteTrackConfig::GetAppTrackConfigInstance();
		addChildComponent(trackInstance);
		trackInstance->setVisible(false);

		patternInstance = IgnitePatternConfig::getAppPatternConfigInstance();
		addChildComponent(patternInstance);
		patternInstance->setVisible(false);

		recordInstance = IgniteRecord::GetAppRecordInstance();
		addChildComponent(recordInstance);
		recordInstance->setVisible(false);

		cvioInstance = IgniteCvio::GetAppCvioInstance();
		addChildComponent(cvioInstance);
		cvioInstance->setVisible(false);

		settingsInstance = IgniteSettings::GetAppSettingsInstance();
		addChildComponent(settingsInstance);
		settingsInstance->setVisible(false);

		midiConfigInstance = IgniteMidiConfig::GetAppMidiConfigInstance();
		addChildComponent(midiConfigInstance);
		midiConfigInstance->setVisible(false);

		calibInstance = IgniteCalibration::GetAppCalibrationInstance();
		addChildComponent(calibInstance);
		calibInstance->setVisible(false);

		menuModeInstance = MenuMode::GetMenuModeInstance();
		addChildComponent(menuModeInstance);
		menuModeInstance->setVisible(false);
		optionptr = AppOptions::GetOptionsInstance();
		menuOptCtl = IgniteControlOptions::GetAppOptInstance();

		instrInstance->updateData();
		recordInstance->updateData();
		settingsInstance->updateData();
		cvioInstance->setDefaultOutputPort();
		cvioInstance->refreshUI();
		songInstance->refreshSongConfig(false);
		sceneInstance->updateData(true);
		patternInstance->updateData();
		midiConfigInstance->refreshUI();
		trackInstance->updateData();
	}

	AppMenu::~AppMenu()
	{}

	void AppMenu::setAllMenuCompInVisible()
	{
		songInstance->setVisible(false);
		sceneInstance->setVisible(false);
		trackInstance->setVisible(false);
		TrackMixer::GetTrackMixerInstance()->setVisible(false);
		patternInstance->setVisible(false);
		recordInstance->setVisible(false);
		midiConfigInstance->setVisible(false);
		calibInstance->setVisible(false);
		cvioInstance->setVisible(false);
		settingsInstance->setVisible(false);
		IgniteBRaySettings::GetAppBrayInstance()->setVisible(false);
		IgniteAuditionSettings::GetAppAuditionInstance()->setVisible(false);
		IgniteMidiRemoteControl::GetAppMidiRemoteControlInstance()->setVisible(false);
		IgniteSculptConfig::GetAppSculptInstance()->setVisible(false);
		IgniteBackup::GetAppBackupInstance()->setVisible(false);
		IgniteMidiClkSetting::GetAppMidiClkInstance()->setVisible(false);
		instrInstance->setVisible(false);
		IgniteCustomScale::getAppCustomScaleInstance()->setVisible(false);
		IgniteTransposeSettings::GetAppTransposeInstance()->setVisible(false);
		IgniteDeviceStatus::GetDevStatusInstance()->setVisible(false);
		IgniteMiscSettings::GetAppSettingsInstance()->setVisible(false);
		IgniteConnectivity::GetAppConnectivityInstance()->setVisible(false);
		sceneInstance->setftsWindowState(false);
	}

	void AppMenu::changeMenuOptionsVisibilty(MENU_WINDOWS index)
	{
		setAllMenuCompInVisible();
		currentIndex = index;
		IgniteDeviceStatus::GetDevStatusInstance()->devStatusStopTimer();
		auto miscComp = IgniteMiscSettings::GetAppSettingsInstance();

		switch (index)
		{
		case MENU_WINDOWS::MENU_WINDOW:
			resized();
			menuOptions->toFront(true);
			menuOptions->setVisible(true);
			instrInstance->setVisible(false);
			menuModeInstance->setVisible(false);
			resized();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::MENU_WINDOW);
			menuOptCtl->enableKey(IgniteControlOptions::SAVE, false);
			menuOptCtl->enableKey(IgniteControlOptions::DEL, false);
			break;
		case MENU_WINDOWS::INSTR_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			instrInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			instrInstance->updateData();
			instrInstance->refreshInstrumentsUI();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::INSTR_WINDOW);
			if (instrInstance->instrumentsDataUpdated && !instrInstance->autoSaveState)
			{
				instrInstance->enableControlButton(IgniteControlOptions::SAVE, true);
				instrInstance->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				instrInstance->enableControlButton(IgniteControlOptions::SAVE, false);
				instrInstance->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::RECORD_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			recordInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			recordInstance->updateData();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::RECORD_WINDOW);
			recordInstance->recordOptCtl->enableKey(IgniteControlOptions::DEL, false);
			if (recordInstance->recordConfigDataUpdated)
			{
				recordInstance->recordOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				recordInstance->recordOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			}
			else
			{
				recordInstance->recordOptCtl->enableKey(IgniteControlOptions::SAVE, false);
				recordInstance->recordOptCtl->enableKey(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::SETTING_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			settingsInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			IgniteMidiRemoteControl::GetAppMidiRemoteControlInstance()->setVisible(false);
			IgniteSculptConfig::GetAppSculptInstance()->setVisible(false);
			IgniteBRaySettings::GetAppBrayInstance()->setVisible(false);
			IgniteMidiRemoteControl::GetAppMidiRemoteControlInstance()->setVisible(false);
			IgniteBackup::GetAppBackupInstance()->setVisible(false);
			IgniteMidiClkSetting::GetAppMidiClkInstance()->setVisible(false);
			IgniteTransposeSettings::GetAppTransposeInstance()->setVisible(false);
			IgniteDeviceStatus::GetDevStatusInstance()->setVisible(false);
			miscComp->setVisible(false);

			settingsInstance->updateData();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::SETTING_WINDOW);
			settingsInstance->enableControlButton(IgniteControlOptions::DEL, false);
			if (settingsInstance->settingsDataUpdated)
			{
				settingsInstance->enableControlButton(IgniteControlOptions::SAVE, true);
				settingsInstance->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				settingsInstance->enableControlButton(IgniteControlOptions::SAVE, false);
				settingsInstance->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::MISC_SETTING_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			settingsInstance->setVisible(false);
			miscComp->setVisible(true);
			menuModeInstance->setVisible(true);

			miscComp->updateData();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::MISC_SETTING_WINDOW);
			miscComp->enableControlButton(IgniteControlOptions::DEL, false);
			if (settingsInstance->settingsDataUpdated)
			{
				miscComp->enableControlButton(IgniteControlOptions::SAVE, true);
				miscComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				miscComp->enableControlButton(IgniteControlOptions::SAVE, false);
				miscComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::CVIO_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			cvioInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::CVIO_WINDOW);
			cvioInstance->enableControlButton(IgniteControlOptions::DEL, false);
			AppMainmode::getMainModeInstance()->resetPadLedsOnViewChange();
			cvioInstance->refreshUI();
			if (cvioInstance->cvioConfigDataUpdated)
			{
				cvioInstance->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioInstance->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				cvioInstance->enableControlButton(IgniteControlOptions::SAVE, false);
				cvioInstance->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::SONG_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			songInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			songInstance->isDataNeedtoEngine(false);
			songInstance->refreshSongConfig(false);
			songInstance->isDataNeedtoEngine(true);
			songInstance->repaint();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::SONG_WINDOW);
			songInstance->_pSongOptCtl->enableKey(IgniteControlOptions::DEL, false);
			if (songInstance->getSongConfigDataUpdateStatus())
			{
				songInstance->_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				songInstance->_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			}
			else
			{
				songInstance->_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, false);
				songInstance->_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::SCENE_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			sceneInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			IgniteCustomScale::getAppCustomScaleInstance()->setVisible(false);
			sceneInstance->setftsWindowState(false);
			sceneInstance->updateData(true);
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::SCENE_WINDOW);
			sceneInstance->sceneOptCtl->enableKey(IgniteControlOptions::DEL, false);
			if (sceneInstance->getSceneConfigDataUpdateState())
			{
				sceneInstance->sceneOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				sceneInstance->sceneOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			}
			else
			{
				sceneInstance->sceneOptCtl->enableKey(IgniteControlOptions::SAVE, false);
				sceneInstance->sceneOptCtl->enableKey(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::TRACK_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			trackInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			trackInstance->updateData();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::TRACK_WINDOW);
			trackInstance->trackOptCtl->enableKey(IgniteControlOptions::DEL, false);
			if (trackInstance->trackConfigDataUpdated)
			{
				trackInstance->trackOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				trackInstance->trackOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			}
			else
			{
				trackInstance->trackOptCtl->enableKey(IgniteControlOptions::SAVE, false);
				trackInstance->trackOptCtl->enableKey(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::PATTERN_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			patternInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			patternInstance->updateData();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::PATTERN_WINDOW);
			patternInstance->_pPatternOptCtl->enableKey(IgniteControlOptions::DEL, false);
			if (patternInstance->getpatternConfigDataUpdateState())
			{
				patternInstance->_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				patternInstance->_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			}
			else
			{
				patternInstance->_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, false);
				patternInstance->_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::MIDI_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			midiConfigInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			midiConfigInstance->refreshUI();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::MIDI_WINDOW);
			midiConfigInstance->enableControlButton(IgniteControlOptions::DEL, false);
			if (midiConfigInstance->midiConfigDataUpdated)
			{
				midiConfigInstance->enableControlButton(IgniteControlOptions::SAVE, true);
				midiConfigInstance->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				midiConfigInstance->enableControlButton(IgniteControlOptions::SAVE, false);
				midiConfigInstance->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			break;
		case MENU_WINDOWS::CALIB_WINDOW:
			menuOptions->toFront(false);
			menuOptions->setVisible(false);
			calibInstance->setVisible(true);
			menuModeInstance->setVisible(true);
			calibInstance->repaint();
			optionptr->taboptionChanges(mt::Ignite::tabs::MENU, (int)MENU_WINDOWS::CALIB_WINDOW);
			break;
		case MENU_WINDOWS::DISABLE_ALL_WINDOW:
			break;
		}
		menuModeInstance->repaint();

	}

	void AppMenu::resized()
	{
		songInstance->setBounds(getLocalBounds());
		sceneInstance->setBounds(getLocalBounds());
		trackInstance->setBounds(getLocalBounds());
		patternInstance->setBounds(getLocalBounds());
		instrInstance->setBounds(getLocalBounds());
		recordInstance->setBounds(getLocalBounds());
		cvioInstance->setBounds(getLocalBounds());
		calibInstance->setBounds(getLocalBounds());
		midiConfigInstance->setBounds(getLocalBounds());
		settingsInstance->setBounds(getLocalBounds());
		menuOptions->setBounds(getLocalBounds());
		menuModeInstance->setBounds(Rectangle(10, 8, layout::screen.getWidth() - 20, heightMenuInstance));
	}

	bool AppMenu::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool handled = true;

		if (((FrontPannelParam)param == FrontPannelParam::paramKey_FILL_X) || ((FrontPannelParam)param == FrontPannelParam::paramKey_SOLO_SKIP))
		{
			if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusReleased)
				return true;

			if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusPressed)
				return sceneInstance->pannelKeyHandler(param, KeyValue);
		}
		switch (currentIndex)
		{
		case MENU_WINDOWS::INSTR_WINDOW:
			handled = (instrInstance->PannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::MIDI_WINDOW:
			handled = (midiConfigInstance->PannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::CVIO_WINDOW:
			handled = (cvioInstance->PannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::SONG_WINDOW:
			handled = (songInstance->pannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::SCENE_WINDOW:
			handled = (sceneInstance->pannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::TRACK_WINDOW:
			handled = (trackInstance->PannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::PATTERN_WINDOW:
			handled = (patternInstance->pannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::RECORD_WINDOW:
			handled = (recordInstance->PannelKeyHandler(param, KeyValue));
			break;
		case MENU_WINDOWS::SETTING_WINDOW:
			handled = (settingsInstance->PannelKeyHandler(param, KeyValue));
			break;
		default:
			handled = false;
			break;
		}

		if (!handled)
			return menuOptions->PannelKeyHandler(param, KeyValue);

		return handled;
	}

	bool AppMenuOptions::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		if (KeyFocusedItem == menusViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = menusViewItemID::INSTRUMENT;
		}
		else
		{
			{
				PannelSendKey(false, param, KeyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					KeyFocusedItem = (KeyFocusedItem + 1 >= menusViewItemID::FOCUS_MAX ? (menusViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= menusViewItemID::NO_FOCUS ? (menusViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramRot_ROW:
					if (KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT)
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						KeyFocusedItem = (KeyFocusedItem + MENU_ROW_ITEMS >= menusViewItemID::FOCUS_MAX ? ((KeyFocusedItem + MENU_ROW_ITEMS) == (menusViewItemID::FOCUS_MAX) ? (menusViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + MENU_ROW_ITEMS);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else if (KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT)
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						KeyFocusedItem = (KeyFocusedItem - MENU_ROW_ITEMS <= menusViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - MENU_ROW_ITEMS);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
					}
					repaint();
					setfocus = false;
					break;
				}
			}
		}
		if (setfocus)
		{
			PannelSendKey(true, param, KeyValue);
		}
		return true;
	}


	void AppMenuOptions::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		switch (menusView[KeyFocusedItem])
		{
		case INSTRUMENT:
			instrumentButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case MIDI_CONFIG:
			midiConfigButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case CVIO_CONFIG:
			cvioButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SONG:
			songButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SCENE:
			sceneButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case TRACK:
			trackButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case PATTERN:
			patternButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case RECORD:
			recordButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SETTINGS:
			settingsButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
	}
	MenuMode::MenuMode()
	{
		back.makeVisibleAndAddListner(this);
		back.setColour(juce::TextButton::buttonColourId, Theme::Instance().getColour(neutralGrey1));
		back.setBounds(Rectangle(xStartBackBtn, yStartBackBtn, widthBackBtn, heightBackBtn));
		header.makeVisible(this);
		header.setDisplayTitle(true);
		header.setEditable(false, false, false);
		header.setJustificationType(Justification::centred);
		header.setBounds(Rectangle(10, yStartMenuHeader, 1004, heightMenuHeader));
		back.setBounds(Rectangle(xStartBackBtn, yStartBackBtn, widthBackBtn, heightBackBtn));
		back.toFront(true);
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();
	}
	MenuMode::~MenuMode()
	{
	}
	void MenuMode::paint(juce::Graphics& g)
	{
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-title.png"));
		g.drawImage(defaultImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
	}
	void MenuMode::resized()
	{
		//box.performLayout(getLocalBounds());
	}
	void MenuMode::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &back)
		{
			auto sculptComp = IgniteSculptConfig::GetAppSculptInstance();
			auto brayComp = IgniteBRaySettings::GetAppBrayInstance();
			auto midiRemoteCtrlComp = IgniteMidiRemoteControl::GetAppMidiRemoteControlInstance();
			auto backupComp = IgniteBackup::GetAppBackupInstance();
			auto midiClkComp = IgniteMidiClkSetting::GetAppMidiClkInstance();
			auto customFtsComp = IgniteCustomScale::getAppCustomScaleInstance();
			auto midiTransposeComp = IgniteTransposeSettings::GetAppTransposeInstance();
			//auto mmcComp = IgniteMidiMachineControl::GetAppMidiMachineControlInstance();
			auto deviceStatusComp = IgniteDeviceStatus::GetDevStatusInstance();
			auto miscSettingComp = IgniteMiscSettings::GetAppSettingsInstance();
			auto audComp = IgniteAuditionSettings::GetAppAuditionInstance();
			auto connComp = IgniteConnectivity::GetAppConnectivityInstance();
			auto calibComp = IgniteCalibration::GetAppCalibrationInstance();
#if ENABLE_HARDWARE_TEST
			auto testComp = IgniteTest::GetAppTestDataInstance();
#endif

			if (back.getToggleState())
				back.setToggleState(false, dontSendNotification);
			if (TrackMixer::GetTrackMixerInstance()->isVisible())
			{
				TrackMixer::GetTrackMixerInstance()->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::TRACK_WINDOW);
			}
			else if (brayComp->isVisible())
			{
				brayComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}

			else if (sculptComp->isVisible())
			{
				sculptComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::PATTERN_WINDOW);
			}
			else if (midiRemoteCtrlComp->isVisible())
			{
				midiRemoteCtrlComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}
			else if (backupComp->isVisible())
			{
				backupComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}
			else if (midiClkComp->isVisible())
			{
				midiClkComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}
			else if (customFtsComp->isVisible())
			{
				customFtsComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SCENE_WINDOW);
			}
			else if (midiTransposeComp->isVisible())
			{
				midiTransposeComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}
			/*else if (mmcComp->isVisible())
			{
				mmcComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}*/
			else if (deviceStatusComp->isVisible())
			{
				deviceStatusComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}
			else if (audComp->isVisible())
			{
				audComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}
			else if (connComp->isVisible())
			{
				connComp->updateLedStatus(false);
				connComp->setVisible(false);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
			}
			else if (miscSettingComp->isVisible())
			{
				if (calibComp->isVisible() )
				{
					if(calibComp->getCalibStatus())
						_pInfoWindow->setTextandShow("Calibration Mode Disabled");
					calibComp->clearAllBtnState();
					calibComp->setVisible(false);
					IgniteSettings::GetAppSettingsInstance()->enableMiscCompVisibility();
				}
#if ENABLE_HARDWARE_TEST
				else if (testComp->isVisible())
				{
					testComp->setVisible(false);
					IgniteSettings::GetAppSettingsInstance()->enableMiscCompVisibility();
				}
#endif
				else
				{
					miscSettingComp->setVisible(false);
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
				}
			}
			else
			{
				onBackbtnpress(0);
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
				AppOptions::GetOptionsInstance()->setView(false, false, false, false, false);
				AppOptions::GetOptionsInstance()->showOptions(false);
				MenuMode::GetMenuModeInstance()->setJustification(Justification::centred);
			}
		}
	}
	void MenuMode::labelTextChanged(Label* labelThatHasChanged)
	{

	}
	void MenuMode::setHeader(const String& name)
	{
		header.setText(name, juce::dontSendNotification);
	}
	void MenuMode::setJustification(Justification type)
	{
		header.setJustificationType(type);

		if (type == Justification::left)
		{
			header.setBounds(Rectangle(200, yStartMenuHeader, 1004, heightMenuHeader));
		}
		else
		{
			header.setBounds(Rectangle(10, yStartMenuHeader, 1004, heightMenuHeader));
			back.toFront(true);
		}
	}
};
