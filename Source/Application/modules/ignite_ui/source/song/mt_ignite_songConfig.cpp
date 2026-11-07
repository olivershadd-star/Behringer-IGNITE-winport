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

using namespace Ignite;

namespace ui
{

	////////////////////////////////////////////////
	//   Class: Ignite SongConfig
	////////////////////////////////////////////////
	IgniteSongConfig::IgniteSongConfig()
	{
		addAndMakeVisible(autoSaveBtn);
		autoSaveBtn.addListener(this);
		autoSaveBtn.setToggleable(true);
		autoSaveBtn.setComponentID("autoSaveComp");
		autoSaveBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		autoSaveBtn.sethoverImages("toggle-autosave-hover.png", "toggle-autosave-active-hover.png", "toggle-autosave-disabled.png");

		addAndMakeVisible(wipeSongsBtn);
		wipeSongsBtn.addListener(this);
		wipeSongsBtn.setToggleable(true);
		wipeSongsBtn.setComponentID("wipeComp");
		wipeSongsBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		wipeSongsBtn.setDisableImage("btn-wipe-allsongs-disabled.png");

		addAndMakeVisible(noteSharpBtn);
		noteSharpBtn.addListener(this);
		noteSharpBtn.setToggleable(true);
		noteSharpBtn.setToggleState(true, dontSendNotification);
		noteSharpBtn.setComponentID("noteSharpsComp");
		noteSharpBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		noteSharpBtn.sethoverImages("btn-notetoggle-sharps-default-hover.png", "btn-notetoggle-sharps-active-hover.png", "btn-notetoggle-sharps-disabled.png");

		addAndMakeVisible(noteFlatBtn);
		noteFlatBtn.addListener(this);
		noteFlatBtn.setToggleable(true);
		noteFlatBtn.setComponentID("noteFlatsComp");
		noteFlatBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		noteFlatBtn.sethoverImages("btn-notetoggle-flats-default-hover.png", "btn-notetoggle-flats-active-hover.png", "btn-notetoggle-flats-disabled.png");

		//addAndMakeVisible(syncSource);
		//syncSource.updateListOptions(syncOptions);
		//syncSource.setSelected(0);
		//syncSource.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		//syncSource.setValueColour(Theme::Instance().getColour(customOrange));
		//syncSource.setComponentID("syncSourceComp");

		//addAndMakeVisible(syncSourcePort);
		//syncSourcePort.updateListOptions(syncInvalidPorts);
		//syncSourcePort.setSelected(0);
		//syncSourcePort.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		//syncSourcePort.setValueColour(Theme::Instance().getColour(customOrange));
		//syncSourcePort.setComponentID("syncSourcePortComp");
		//syncSourcePort.setAlpha((float)0.3);
		//syncSourcePort.setInterceptsMouseClicks(false, false);

		addAndMakeVisible(insertPosition);
		insertPosition.updateListOptions(mt::Ignite::songInsertPosition);
		insertPosition.setSelected(0);
		insertPosition.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		insertPosition.setValueColour(Theme::Instance().getColour(customOrange));
		insertPosition.setComponentID("insertPositionComp");

		/*const juce::Rectangle<int> syncSourceBounds{ (0),(0),widthfillMode,heightfillMode };
		syncSource.setDailogViewType(mt::Ignite::DailogViewType::CustomView, false, syncSourceBounds);
		syncSource.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		syncSource.setTextColour(Theme::Instance().getColour(customOrange));

		const juce::Rectangle<int> syncSourcePortBounds{ (0),(0),widthfillMode,heightfillMode };
		syncSourcePort.setDailogViewType(mt::Ignite::DailogViewType::CustomView, false, syncSourcePortBounds);
		syncSourcePort.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		syncSourcePort.setTextColour(Theme::Instance().getColour(customOrange));*/

		_pSongOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(_pSongOptCtl);
		_pSongOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		_pSongOptCtl->addOptCtlListener(this);

		addAndMakeVisible(tapConfig);
		tapConfig.setDisplayTitle(true);
		tapConfig.setJustificationType(juce::Justification::centred);
		tapConfig.setTextColour(Theme::Instance().getColour(customOrange));
		tapConfig.setComponentID("tapTempoComp");

		tapConfig.setcustombounds(true, ui::Rectangle<int>{144, 0, 50, 50}, ui::Rectangle<int>{90, 35, 150, 50});
		/*syncSource.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		syncSourcePort.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());*/

		songMenuBox1.items.add(FlexItem(autoSaveBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		songMenuBox1.items.add(FlexItem(wipeSongsBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		songMenuBox1.items.add(FlexItem(tapConfig).withMargin({ 0,8,8,0 }).withFlex(1));

		/*syncSource.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });
		syncSourcePort.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });
		*/insertPosition.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });

		_pPopUpPtr = CommonPopUp::getCommonPopupInstance();
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();
		getAssets();

		insertPosition.onSelectionChanged = [this](int value, const juce::String&)
		{
			DBG("insertPosition.onSelectionChanged::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			
			if (isneedtoSendEngine)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::settingInsertPosition, value);
				_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				songConfigDataUpdated = true;
			}
			
		};

		tapConfig.onValueChanged = [this](int value)
		{
			DBG("tapConfig.onValueChanged::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			if (isneedtoSendEngine)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::SettingSongTapTempoParam, value);
				_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				songConfigDataUpdated = true;
			}
			
		};

		/*syncSource.onSelectionChanged = [this](int value, const juce::String&)
		{
			DBG("syncSource.onSelectionChanged::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			syncPortCtl(value);
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::settingSyncSource, value);
			_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			songConfigDataUpdated = true;
		};

		syncSourcePort.onSelectionChanged = [this](int value, const juce::String&)
		{
			DBG("syncSourcePort.onSelectionChanged::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (syncSource.getSelectedIndex() == 3)
				value += (int)InstrumentPorts::usbMidiPort1;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::settingSyncSourcePort, (int8_t)value);
			_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			songConfigDataUpdated = true;
		};*/

		/*syncSource.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		tapConfig.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		insertPosition.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	IgniteSongConfig::~IgniteSongConfig()
	{
	}

	void IgniteSongConfig::refreshSongConfig(bool isInternal)
	{
		isneedtoSendEngine = isInternal;
		std::vector<IgniteParamList> SettingsSongCnfgParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsSongCnfgParam::SettingSongAutoSaveParam;
		SettingsSongCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSongCnfgParam::SettingSongNoteNameDispParam;
		SettingsSongCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSongCnfgParam::SettingSongTapTempoParam;
		SettingsSongCnfgParams.push_back(params);

		/*params.param = (paramId_t)SettingsSongCnfgParam::settingSyncSource;
		SettingsSongCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSongCnfgParam::settingSyncSourcePort;
		SettingsSongCnfgParams.push_back(params);*/

		params.param = (paramId_t)SettingsSongCnfgParam::settingInsertPosition;
		SettingsSongCnfgParams.push_back(params);

		SettingsSongCnfgParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, SettingsSongCnfgParams);

		songSettingData.autoSave = (bool)SettingsSongCnfgParams[0].MsgValue.get<int8_t>();
		autoSaveBtn.setToggleState(songSettingData.autoSave, dontSendNotification);
		noteFlatBtn.setToggleState((bool)SettingsSongCnfgParams[1].MsgValue.get<int8_t>(), sendNotification);
		noteSharpBtn.setToggleState(!(bool)SettingsSongCnfgParams[1].MsgValue.get<int8_t>(), sendNotification);
		autoSaveBtn.getToggleState() ? autoSaveBtn.setButtonText("Auto Save:on") : autoSaveBtn.setButtonText("Auto Save:off");
		tapConfig.setValue(SettingsSongCnfgParams[2].MsgValue.get<int8_t>());
		//syncSource.setSelected((int)SettingsSongCnfgParams[7].MsgValue.get<int8_t>());
		insertPosition.setSelected((int)SettingsSongCnfgParams[3].MsgValue.get<int8_t>());

		/*if (SettingsSongCnfgParams[7].MsgValue.get<int8_t>() >= 2)
			syncPortCtl(SettingsSongCnfgParams[7].MsgValue.get<int8_t>());*/
		/*if (SettingsSongCnfgParams[7].MsgValue.get<int8_t>() == 2)
			syncSourcePort.setSelected((int)SettingsSongCnfgParams[8].MsgValue.get<int8_t>());
		else if (SettingsSongCnfgParams[7].MsgValue.get<int8_t>() == 3)
			syncSourcePort.setSelected((int)SettingsSongCnfgParams[8].MsgValue.get<int8_t>() - (int)InstrumentPorts::usbMidiPort1);*/
		if (!isneedtoSendEngine)
			isneedtoSendEngine = true;
	}

	/*void IgniteSongConfig::syncPortCtl(int source)
	{
		if (source == 0 || source == 1)
		{
			syncSourcePort.updateListOptions(syncInvalidPorts);
			syncSourcePort.setSelected(0);
			syncSourcePort.setAlpha((float)0.3);
			syncSourcePort.setInterceptsMouseClicks(false, false);
		}
		else
		{
			if (source == 2)
				syncSourcePort.updateListOptions(syncMidiPorts);
			else if (source == 3)
				syncSourcePort.updateListOptions(syncUSBMidiPorts);

			syncSourcePort.setSelected(0);
			syncSourcePort.setAlpha((float)1.0);
			syncSourcePort.setInterceptsMouseClicks(true, true);
		}
	}*/
	void IgniteSongConfig::getAssets()
	{
		
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-container-328x80-default.png"));
		imageDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-container-328x80-default-hover.png"));
		imageActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-bg-active.png"));
		imageActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-bg-active-hover.png"));
		imagedisabledImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-container-328x80-disabled.png"));
		imageNoteToggleBg=juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("notename-toggle-bg.png"));
	}


	void IgniteSongConfig::paint(juce::Graphics& g)
	{
		if (songConfigDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("Song Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Song Configuration");

		MenuMode::GetMenuModeInstance()->setJustification(Justification::left);
		if (!IgniteSong::getAppSongInstance()->isSongCreated())
			wipeSongsBtn.setEnabled(false);
		else
			wipeSongsBtn.setEnabled(true);

		Image Draw;

		Draw = tapConfig.isEnabled() ? (tapConfig.getFocusState() ? imageDefaultHover : imageDefault) : imagedisabledImage;
		g.drawImage(Draw, ui::Rectangle<float>{686, 70, 328, 80});

		g.drawImage(imageNoteToggleBg, ui::Rectangle<float>{ 348, 160, 666, 80 });

		/*Draw = syncSource.isEnabled() ? (syncSource.getFocusState() ? OverImage : defaultImage) : disabledImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 340, 328, 80 });

		Draw = syncSourcePort.isEnabled() ? (syncSourcePort.getFocusState() ? OverImage : defaultImage) : disabledImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 340, 328, 80 });*/

		Draw = insertPosition.getFocusState() ? imageDefaultHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 160, 328, 80 });

		Font a((float)(18));
		g.setColour(Theme::Instance().getColour(neutralWhite));
		g.drawText("Note Names as:", ui::Rectangle{ 388, 190, 120, 18 }, Justification::left, true);

	}

	void IgniteSongConfig::resized()
	{
		songMenuBox1.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox1, widthSongMenuBox1, heightSongMenuBox1));
		noteSharpBtn.setBounds(508, 175, 242, 50);
		noteFlatBtn.setBounds(758, 175, 242, 50);
		insertPosition.setBounds(10, 160, 328, 80);
	}

	void IgniteSongConfig::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		auto songPtr = IgniteSong::getAppSongInstance();

		if (buttonThatWasClicked == &autoSaveBtn)
		{
			songSettingData.autoSave = autoSaveBtn.getToggleState();
			if ((songPtr->getSongDataUpdateStatus()) && (songSettingData.autoSave))
			{
				if(isneedtoSendEngine)
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramSaveSongCmd, 0);
				songPtr->updateLables();
			}
			if (isneedtoSendEngine)
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::SettingSongAutoSaveParam, songSettingData.autoSave);
			if (autoSaveBtn.getToggleState())
			{
				autoSaveBtn.setButtonText("Auto Save:on");
			}
			else
			{
				autoSaveBtn.setButtonText("Auto Save:off");
			}
		}
		else if (buttonThatWasClicked == &wipeSongsBtn)
		{
			songPtr->deleteAllSongs();
			wipeSongsBtn.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &noteSharpBtn)
		{
			noteFlatBtn.setToggleState(!noteSharpBtn.getToggleState(), dontSendNotification);
			songSettingData.accidentals = noteFlatBtn.getToggleState();
			TrackValueSelection::GetAppTrackValueSelectionInstance()->updateAccidentals(songSettingData.accidentals);
			IgnitePattern::getAppPatternInstance()->updateAccidentals(songSettingData.accidentals);
			IgniteCvConfig::GetAppCvInstance()->updateAccidentals(songSettingData.accidentals);
			IgnitePatternConfig::getAppPatternConfigInstance()->updateAccidentals(songSettingData.accidentals);
			if (isneedtoSendEngine)
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::SettingSongNoteNameDispParam, songSettingData.accidentals);

		}
		else if (buttonThatWasClicked == &noteFlatBtn)
		{
			noteSharpBtn.setToggleState(!noteFlatBtn.getToggleState(), dontSendNotification);
			songSettingData.accidentals = noteFlatBtn.getToggleState();
			TrackValueSelection::GetAppTrackValueSelectionInstance()->updateAccidentals(songSettingData.accidentals);
			IgnitePattern::getAppPatternInstance()->updateAccidentals(songSettingData.accidentals);
			IgniteCvConfig::GetAppCvInstance()->updateAccidentals(songSettingData.accidentals);
			IgnitePatternConfig::getAppPatternConfigInstance()->updateAccidentals(songSettingData.accidentals);
			if (isneedtoSendEngine)
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::SettingSongNoteNameDispParam, songSettingData.accidentals);
		}

		if (buttonThatWasClicked != &wipeSongsBtn)
		{
			if (isneedtoSendEngine)
			{
				_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				songConfigDataUpdated = true;
			}
			
		}

	}

	void IgniteSongConfig::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			songConfigDataUpdated = false;
		}
		else if (option == IgniteControlOptions::AUTOSAVEON)
		{
			isAutosave = true;
		}
		else if (option == IgniteControlOptions::AUTOSAVEOFF)
		{
			isAutosave = false;
		}
		if (this->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (_pPopUpPtr->isDialogOpen.get() != true)
				{
					_pPopUpPtr->close();
					_pPopUpPtr->setPopUpPropories("Save ", 604, 290);
					_pPopUpPtr->setbtnsize(265, 44);
					_pPopUpPtr->setInfoText(String(" Save Song Configuration edits ? "));
					_pPopUpPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					_pPopUpPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					_pPopUpPtr->popupType = POPUP_WITHOKCANCEL;
					_pPopUpPtr->isCloseButtonVisible(false);
					_pPopUpPtr->show();
					_pPopUpPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::SettingSongCnfgSave, 0);
							_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, false);
							_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, false);
							songConfigDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::SONGLIST)
			{
				IgniteSong::getAppSongInstance()->changeSongOptionsVisibility(false);
				AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::SONG);
			}

			else if (option == IgniteControlOptions::UNDO)
			{
				if (songConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, (paramId_t)SettingsSongCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> songCfgParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsSongCnfgParam::paramUndoListCmd;
					songCfgParamList.push_back(params);
					songCfgParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSongCnfg, songCfgParamList);
					if (songCfgParamList.size() == 1)
					{
						songConfigDataUpdated = false;
						_pSongOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						_pSongOptCtl->enableKey(IgniteControlOptions::UNDO, false);
					}
					refreshSongConfig(false);
					
				}
			}
		}
	}

	int IgniteSongConfig::isEditing()
	{
		int index = 0;
		if (keyFocusedItem == WIPE_SONGS)
		{
			auto songPtr = IgniteSong::getAppSongInstance();

			if (songPtr->_pPopUpPtr != nullptr && songPtr->_pPopUpPtr->IsEditing())
			{
				return WIPE_SONGS;
			}
		}

		tapConfig.IsEditing() ? index = 3 : 0;
		insertPosition.IsEditing() ? index = 4 : 0;
		return index;
	}


	bool IgniteSongConfig::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = songMenuViewItemID::NO_FOCUS;

		if (_pPopUpPtr != nullptr && _pPopUpPtr->IsEditing())
			return _pPopUpPtr->FPKeyHandler(true, param, KeyValue);

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
		{
			handlePageShift(param, KeyValue);
			return true;
		}

		if (optionHandlerFocus == SONGCONFIG_DETAIL)
		{
			handleSongConfigDetail(param, KeyValue, setfocus, EditItem);
		}
		else
		{
			handleSongConfigOption(param, KeyValue);
		}

		if (setfocus)
		{
			pannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void IgniteSongConfig::handlePageShift(paramId_t param, uint32_t KeyValue)
	{
		pannelSendKey(false, param, KeyValue);
		optionHandlerFocus = static_cast<uint8_t>((optionHandlerFocus == SONGCONFIG_DETAIL) ? SONGCONFIG_OPTION : SONGCONFIG_DETAIL);
		pannelSendKey(true, param, KeyValue);
	}

	void IgniteSongConfig::handleSongConfigDetail(paramId_t param, uint32_t KeyValue, bool& setfocus, int& EditItem)
	{
		if (keyFocusedItem == songMenuViewItemID::NO_FOCUS)
		{
			keyFocusedItem = songMenuViewItemID::AUTO_SAVE;
			if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
			{
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
				return;
			}
		}
		else
		{
			EditItem = isEditing();
			if (EditItem)
			{
				if (keyFocusedItem != EditItem)
				{
					pannelSendKey(false, param, KeyValue);
					keyFocusedItem = EditItem;
				}
				setfocus = true;
			}
			else
			{
				handleKeyMovement(param, KeyValue, setfocus);
			}
		}
	}

	void IgniteSongConfig::handleSongConfigOption(paramId_t param, uint32_t KeyValue)
	{
		pannelSendKey(false, param, KeyValue);
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RMOVELEFT:
			optFocusedItem = std::min(optFocusedItem + 1, (int)songOptionsViewItemID::OP_FOCUS_MAX);
			break;
		case FrontPannelParam::paramKey_RMOVERIGHT:
			optFocusedItem = std::max(optFocusedItem - 1, (int)songOptionsViewItemID::OP_NO_FOCUS + 1);
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
			break;
		}
	}

	void IgniteSongConfig::handleKeyMovement(paramId_t param, uint32_t KeyValue, bool& setfocus)
	{
		pannelSendKey(false, param, KeyValue);
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RMOVELEFT:
			keyFocusedItem = std::min(keyFocusedItem + 1, (int)songMenuViewItemID::FOCUS_MAX);
			break;
		case FrontPannelParam::paramKey_RMOVERIGHT:
			keyFocusedItem = std::max(keyFocusedItem - 1, (int)songMenuViewItemID::NO_FOCUS + 1);
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
			break;
		case FrontPannelParam::paramRot_ROW:
			handleRotaryMovement(KeyValue);
			setfocus = false;
			break;
		}
	}

	void IgniteSongConfig::handleRotaryMovement(uint32_t KeyValue)
	{
		if (KeyValue == ROTARY_DIRECTION_RIGHT)
		{
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
			keyFocusedItem = std::min(keyFocusedItem + SONG_ROW_ITEMS, (int)songMenuViewItemID::FOCUS_MAX);
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
		}
		else
		{
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
			keyFocusedItem = std::max(keyFocusedItem - SONG_ROW_ITEMS, (int)songMenuViewItemID::NO_FOCUS);
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
		}
		repaint();
	}

	void IgniteSongConfig::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased)
			return;

		if (optionHandlerFocus == SONGCONFIG_DETAIL)
		{
			handleSongConfigDetailKey(isFocuse, param, KeyValue);
		}
		else
		{
			handleSongConfigOptionKey(isFocuse, param, KeyValue);
		}
	}

	void IgniteSongConfig::handleSongConfigDetailKey(bool isFocuse, paramId_t param, uint32_t KeyValue/*, IgniteSong* songPtr*/)
	{
		switch (songMenuView[keyFocusedItem])
		{
		case AUTO_SAVE:
			handleButtonKey(autoSaveBtn, isFocuse, param, 0);
			break;
		case WIPE_SONGS:
			handleWipeSongsKey(isFocuse, param, KeyValue);
			break;
		case NOTE_FLATS:
			handleButtonKey(noteFlatBtn, isFocuse, param, 0);
			break;
		case NOTE_SHARPS:
			handleButtonKey(noteSharpBtn, isFocuse, param, 0);
			break;
		case TAP_TEMPO:
			tapConfig.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case INSERT_POSITION:
			insertPosition.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
		repaint();
	}

	void IgniteSongConfig::handleButtonKey(CommonImageButton& button, bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		button.FPKeyHandler(isFocuse, param, KeyValue);
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
		{
			buttonClicked(&button);
		}
	}

	void IgniteSongConfig::handleWipeSongsKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		auto songPtr = IgniteSong::getAppSongInstance();

		if (wipeSongsBtn.isEnabled())
		{
			if (songPtr->_pPopUpPtr != nullptr && songPtr->_pPopUpPtr->IsEditing())
			{
				songPtr->_pPopUpPtr->FPKeyHandler(isFocuse, param, KeyValue);
			}
			else
			{
				wipeSongsBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
		}
		else
		{
			adjustFocus(param);
			pannelSendKey(isFocuse, param, KeyValue);
		}
	}

	void IgniteSongConfig::adjustFocus(paramId_t param)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
			keyFocusedItem++;
		else
			keyFocusedItem--;
	}

	void IgniteSongConfig::handleSongConfigOptionKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		bool state = false;
		switch (optionsView[optFocusedItem])
		{
		case OPT_UNDO:
			state = _pSongOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
			break;
		case OPT_SONGLIST:
			state = _pSongOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::SONGLIST, isFocuse, param, KeyValue);
			break;
		case OPT_DEFULT:
			state = _pSongOptCtl->PannelKeyHandler(ui::IgniteControlOptions::SONG_SETTING_GLOBAL, isFocuse, param, KeyValue);
			break;
		case OPT_ACTIVE_SONG:
			state = _pSongOptCtl->PannelKeyHandler(ui::IgniteControlOptions::SONG_SETTING_ACTIVE, isFocuse, param, KeyValue);
			break;
		}

		if (!state)
		{
			optFocusedItem = (optFocusedItem + 1) % OP_FOCUS_MAX;
			pannelSendKey(isFocuse, param, KeyValue);
		}
	}
};
