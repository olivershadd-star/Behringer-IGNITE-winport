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
	//   Class: Ignite PatternConfig
	////////////////////////////////////////////////
	IgnitePatternConfig::IgnitePatternConfig()
	{
		addAndMakeVisible(autoSaveBtn);
		autoSaveBtn.addListener(this);
		autoSaveBtn.setToggleable(true);
		autoSaveBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		autoSaveBtn.sethoverImages("toggle-autosave-default-hover.png", "toggle-autosave-active-hover.png", "toggle-autosave-disabled-hover.png");
		autoSaveBtn.setComponentID("autoSaveComp");

		addAndMakeVisible(barFollowBtn);
		barFollowBtn.addListener(this);
		barFollowBtn.setToggleable(true);
		barFollowBtn.setComponentID("barFollowComp");
		barFollowBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		barFollowBtn.sethoverImages("toggle-barfollow-default-hover.png", "toggle-barfollow-active-hover.png", "toggle-barfollow-disabled-hover.png");

		addAndMakeVisible(wipePattern);
		wipePattern.addListener(this);
		wipePattern.setToggleable(true);
		wipePattern.setComponentID("wipePatternComp");
		wipePattern.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		wipePattern.setDisableImage("btn-wipe-unassinged-disabled.png");

		//addAndMakeVisible(defaultNote);
		//defaultNote.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		//defaultNote.setValueColour(Theme::Instance().getColour(customOrange));
		//const juce::Rectangle<int> fillModeBounds{ (0),(0),604,450 };
		//defaultNote.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, fillModeBounds);
		//defaultNote.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		//defaultNote.setTextColour(Theme::Instance().getColour(customBlue4));
		//defaultNote.setComponentID("defaultNoteComp");

		addAndMakeVisible(sculptBtn);
		sculptBtn.addListener(this);
		sculptBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		sculptBtn.setToggleable(true);
		sculptBtn.setComponentID("_pSculptComp");

		addAndMakeVisible(insertPosition);
		insertPosition.updateListOptions(mt::Ignite::patternInsertPosition);
		insertPosition.setSelected(0);
		insertPosition.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		insertPosition.setValueColour(Theme::Instance().getColour(customOrange));
		insertPosition.setComponentID("insertPositionComp");
		insertPosition.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });

		_pPatternOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(_pPatternOptCtl);
		_pPatternOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		_pPatternOptCtl->addOptCtlListener(this);

		_pSculptComp = IgniteSculptConfig::GetAppSculptInstance();
		addChildComponent(_pSculptComp);;
		_pSculptComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		_pSculptComp->setVisible(false);

		//defaultNote.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		sculptBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		//defaultNote.setColour(juce::TextButton::textColourOnId, Colour(0xFFFFFFFF));
		//defaultNote.setColour(juce::TextButton::textColourOffId, Colour(0xFF269CDC));

		patternMenuBox1.items.add(FlexItem(autoSaveBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		patternMenuBox1.items.add(FlexItem(barFollowBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		patternMenuBox1.items.add(FlexItem(wipePattern).withMargin({ 0,8,8,0 }).withFlex(1));
		//patternMenuBox2.items.add(FlexItem(defaultNote).withMargin({ 0,8,8,0 }).withFlex(1));
		patternMenuBox2.items.add(FlexItem(sculptBtn).withMargin({ 0,8,8,0 }).withFlex(1));

		_pPopUpPtr = CommonPopUp::getCommonPopupInstance();
		getAssets();
		insertPosition.onSelectionChanged = [this](int value, const juce::String&)
		{
			DBG("insertPosition.onSelectionChanged::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, (paramId_t)SettingsPatternCnfgParam::paramInsertPosition, (int8_t)value);
			_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			patternConfigDataUpdated = true;
		};

		insertPosition.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		/*defaultNote.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand ((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, (paramId_t)SettingsPatternCnfgParam::paramPatternDefaultNote, static_cast<int16_t>(value));
			default_note = value;
			_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			patternConfigDataUpdated = true;		};

		defaultNote.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/
	}

	IgnitePatternConfig::~IgnitePatternConfig()
	{
	}

	void IgnitePatternConfig::getAssets()
	{
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-328x80-container-default.png"));
		imageDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-328x80-container-default-hover.png"));
		imagedisabledImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-328x80-container-disabled.png"));
	}

	void IgnitePatternConfig::paint(juce::Graphics& g)
	{
		if (patternConfigDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("Pattern Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Pattern Configuration");

		if (!IgnitePattern::getAppPatternInstance()->isPatternCreated())
			wipePattern.setEnabled(false);
		else
			wipePattern.setEnabled(true);
		Image Draw;

		/*Draw = defaultNote.isEnabled() ? (defaultNote.getFocusState() ? OverImage : defaultImage) : disabledImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 160, 328, 80 });*/

		Draw = insertPosition.getFocusState() ? imageDefaultHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 160, 328, 80 });
	}

	void IgnitePatternConfig::updateData()
	{
		std::vector<IgniteParamList> patternCnfgParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsPatternCnfgParam::SettingPatternAutoSaveParam;
		patternCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsPatternCnfgParam::paramPatternBarFollow;
		patternCnfgParams.push_back(params);

		//params.param = (paramId_t)SettingsPatternCnfgParam::paramPatternDefaultNote;
		//patternCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsPatternCnfgParam::paramInsertPosition;
		patternCnfgParams.push_back(params);

		patternCnfgParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, patternCnfgParams);

		autoSavePattern = (bool)patternCnfgParams[0].MsgValue.get<int8_t>();
		autoSaveBtn.setToggleState(autoSavePattern, dontSendNotification);
		autoSaveBtn.getToggleState() ? autoSaveBtn.setButtonText("Auto Save:on") : autoSaveBtn.setButtonText("Auto Save:off");

		barFollow = (bool)patternCnfgParams[1].MsgValue.get<int8_t>();
		barFollowBtn.setToggleState(barFollow, dontSendNotification);
		barFollowBtn.getToggleState() ? barFollowBtn.setButtonText("Bar Follow:on") : barFollowBtn.setButtonText("Bar Follow:off");

		/*defaultNote.setSelected (patternCnfgParams[2].MsgValue.get<int16_t> ());
		default_note = patternCnfgParams[2].MsgValue.get<int16_t>();*/

		insertPosition.setSelected (patternCnfgParams[2].MsgValue.get<int8_t> ());
	}

	void IgnitePatternConfig::resized()
	{
		patternMenuBox1.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox1, widthSongMenuBox1, heightSongMenuBox1));
		patternMenuBox2.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2, 337, heightSongMenuBox1));
		insertPosition.setBounds(348, 160, 328, 80);
	}

	void IgnitePatternConfig::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		auto patternPtr = IgnitePattern::getAppPatternInstance();

		if (buttonThatWasClicked == &autoSaveBtn)
		{
			autoSavePattern = autoSaveBtn.getToggleState();
			if (patternPtr->getPatternDataUpdateStatus() && autoSavePattern)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::modulePattern, (paramId_t)PatternParam::paramSavePatternCmd, ((IgnitePattern::getAppPatternInstance()->getPatternData(mt::Ignite::ptDataIndex::NAME)).toString()).toStdString());
				patternPtr->updateLables();
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, (paramId_t)SettingsPatternCnfgParam::SettingPatternAutoSaveParam, autoSavePattern);
			_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			patternConfigDataUpdated = true;
		}
		else if (buttonThatWasClicked == &wipePattern)
		{
			patternPtr->deleteAllUnassignedPatterns();
			wipePattern.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &barFollowBtn)
		{
			barFollow = barFollowBtn.getToggleState();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, (paramId_t)SettingsPatternCnfgParam::paramPatternBarFollow, barFollow);
			_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			patternConfigDataUpdated = true;
		}
		else if (buttonThatWasClicked == &sculptBtn)
		{
			sculptBtn.setToggleState(false, dontSendNotification);
			_pSculptComp->setVisible(true);
			_pSculptComp->loadDataFromEngine();

			if (_pSculptComp->sculptConfigDataUpdated)
			{
				_pSculptComp->enableControlButton(IgniteControlOptions::SAVE, true);
				_pSculptComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				_pSculptComp->enableControlButton(IgniteControlOptions::SAVE, false);
				_pSculptComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			//current_screen = SCULPT_CONFIG;
			//keyFocusedItem = SCULPT_CONFIG;
		}
	}

	void IgnitePatternConfig::updateAccidentals(bool state)
	{
		//state ? defaultNote.updateListOptions(mt::Ignite::midiNoteNamesFlats) : defaultNote.updateListOptions(mt::Ignite::midiNoteNamesSharps);
	}

	void IgnitePatternConfig::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			patternConfigDataUpdated = false;
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
					_pPopUpPtr->setInfoText(String(" Save Pattern Configuration edits? "));
					_pPopUpPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					_pPopUpPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					_pPopUpPtr->popupType = POPUP_WITHOKCANCEL;
					_pPopUpPtr->isCloseButtonVisible(false);
					_pPopUpPtr->show();
					_pPopUpPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, (paramId_t)SettingsPatternCnfgParam::SettingsPatternCnfgSave, 0);
							_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, false);
							_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, false);
							patternConfigDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::PATSTEP)
			{
				IgnitePattern::getAppPatternInstance()->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
				AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::PATTERN);
			}
			else if (option == IgniteControlOptions::PATBAR)
			{
				IgnitePattern::getAppPatternInstance()->changePatternViewVisibility(IgnitePattern::PatternView::BAR);
				AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::PATTERN);
			}
			else if (option == IgniteControlOptions::PATGRID)
			{
				IgnitePattern::getAppPatternInstance()->changePatternViewVisibility(IgnitePattern::PatternView::GRID);
				AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::PATTERN);
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (patternConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, (paramId_t)SettingsSceneCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> patternCfgParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsSceneCnfgParam::paramUndoListCmd;
					patternCfgParamList.push_back(params);
					patternCfgParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsPatternCnfg, patternCfgParamList);
					if (patternCfgParamList.size() == 1)
					{
						patternConfigDataUpdated = false;
						_pPatternOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						_pPatternOptCtl->enableKey(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgnitePatternConfig::isEditing()
	{
		int index = 0;

		if (keyFocusedItem == WIPE_PATTERN)
		{
			auto patternPtr = IgnitePattern::getAppPatternInstance();

			if (patternPtr->_pPopUpPtr != nullptr && patternPtr->_pPopUpPtr->IsEditing())
			{
				return WIPE_PATTERN;
			}
		}

		//defaultNote.IsEditing() ? index = 4 : 0;
		insertPosition.IsEditing() ? index = 5 : 0;

		return index;
	}

	bool IgnitePatternConfig::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = patternMenuViewItemID::NO_FOCUS;

		if (_pPopUpPtr != nullptr && _pPopUpPtr->IsEditing())
			return _pPopUpPtr->FPKeyHandler(true, param, KeyValue);

		if (_pSculptComp->isVisible())
		{
			_pSculptComp->PannelKeyHandler(param, KeyValue);
			return true;
		}
		else
		{
			if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
			{
				pannelSendKey(false, param, KeyValue);
				if (optionHandlerFocus == PATTERNCONFIG_DETAIL)
				{
					optionHandlerFocus = PATTERNCONFIG_OPTION;
				}
				else
				{
					optionHandlerFocus = PATTERNCONFIG_DETAIL;
				}
				pannelSendKey(true, param, KeyValue);
				return true;
			}

			if (optionHandlerFocus == PATTERNCONFIG_DETAIL)
			{
				if (keyFocusedItem == patternMenuViewItemID::NO_FOCUS)
				{
					/*1st key after Page visible */
					keyFocusedItem = patternMenuViewItemID::AUTO_SAVE;

					if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
					{
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
						return true;
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
						pannelSendKey(false, param, KeyValue); // clear last Focus
						switch ((FrontPannelParam)param)
						{
						case FrontPannelParam::paramKey_RMOVELEFT:
							keyFocusedItem = (keyFocusedItem + 1 >= patternMenuViewItemID::FOCUS_MAX ? (patternMenuViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
							break;
						case FrontPannelParam::paramKey_RMOVERIGHT:
							keyFocusedItem = (keyFocusedItem - 1 <= patternMenuViewItemID::NO_FOCUS ? (patternMenuViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
							break;
						case FrontPannelParam::paramKey_RETURN_NAV:
							AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
							break;
						case FrontPannelParam::paramRot_ROW:

							if (KeyValue == ROTARY_DIRECTION_RIGHT)
							{
								pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
								keyFocusedItem = (keyFocusedItem + PATTERN_NO_COM_ROW >= patternMenuViewItemID::FOCUS_MAX ? ((keyFocusedItem + PATTERN_NO_COM_ROW) == (patternMenuViewItemID::FOCUS_MAX) ? (patternMenuViewItemID::FOCUS_MAX) : keyFocusedItem) : keyFocusedItem + PATTERN_NO_COM_ROW);
								pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
							}
							else
							{
								pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
								keyFocusedItem = (keyFocusedItem - PATTERN_NO_COM_ROW <= patternMenuViewItemID::NO_FOCUS ? (keyFocusedItem) : keyFocusedItem - PATTERN_NO_COM_ROW);
								pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
							}
							repaint();
							setfocus = false;
							break;
						}
					}
				}
			}
			else
			{
				pannelSendKey(false, param, KeyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					optFocusedItem = (optFocusedItem + 1 >= patternOptionsViewItemID::OP_FOCUS_MAX ? (patternOptionsViewItemID::OP_FOCUS_MAX) : optFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					optFocusedItem = (optFocusedItem - 1 <= patternOptionsViewItemID::OP_NO_FOCUS ? (patternOptionsViewItemID::OP_NO_FOCUS + 1) : optFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
					break;
				}
			}
			if (setfocus)
			{
				pannelSendKey(true, param, KeyValue);
			}
			return true;
		}
	}

	void IgnitePatternConfig::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		auto patternPtr = IgnitePattern::getAppPatternInstance();
		bool state = false;

		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (optionHandlerFocus == PATTERNCONFIG_DETAIL)
		{
			switch (patternMenuView[keyFocusedItem])
			{
			case AUTO_SAVE:
				autoSaveBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case BAR_FOLLOW:
				barFollowBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case WIPE_PATTERN:
				if (wipePattern.isEnabled())
				{
					if (patternPtr->_pPopUpPtr != nullptr && patternPtr->_pPopUpPtr->IsEditing())
					{
						patternPtr->_pPopUpPtr->FPKeyHandler(isFocuse, param, KeyValue);
					}
					else
					{
						wipePattern.FPKeyHandler(isFocuse, param, KeyValue);
					}
				}
				else
				{
					if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
						keyFocusedItem++;
					else
						keyFocusedItem--;

					pannelSendKey(isFocuse, param, KeyValue);
				}
				break;
				/*case DEFAULT_NOTE:
					defaultNote.FPKeyHandler(isFocuse, param, KeyValue);
					break;*/
					//case SCULPT_CONFIG:
					//	(_pSculptComp->PannelKeyHandler(param, KeyValue));
			case SCULPT_CONFIG:
				sculptBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case INSERT_POSITION:
				insertPosition.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			default:
				break;
			}
			repaint();
		}
		else
		{
			switch (optionsView[optFocusedItem])
			{
			case OPT_UNDO:
				state = _pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			case OPT_PATSTEP:
				state = _pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::PATSTEP, isFocuse, param, KeyValue);
				break;
			case OPT_PATBAR:
				state = _pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::PATBAR, isFocuse, param, KeyValue);
				break;
			case OPT_PATGRID:
				state = _pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::PATGRID, isFocuse, param, KeyValue);
				break;

			}

			if (state == false)
			{
				optFocusedItem++;
				if (optFocusedItem > OP_FOCUS_MAX)
					optFocusedItem = OPT_UNDO;
				pannelSendKey(isFocuse, param, KeyValue);
			}
		}
	}

	void IgnitePatternConfig::mouseUp(const MouseEvent& event)
	{
		auto a = event.eventComponent->getComponentID();
		int NewFocusedItem = patternMenuViewItemID::NO_FOCUS;

		if (a == "autoSaveComp")					NewFocusedItem = patternMenuViewItemID::AUTO_SAVE;
		else if (a == "wipePatternComp")				NewFocusedItem = patternMenuViewItemID::WIPE_PATTERN;
		else if (a == "barFollowComp")			NewFocusedItem = patternMenuViewItemID::BAR_FOLLOW;
		//else if (a == "defaultNoteComp")			NewFocusedItem = patternMenuViewItemID::DEFAULT_NOTE;

		if (NewFocusedItem != patternMenuViewItemID::NO_FOCUS && NewFocusedItem != keyFocusedItem)
		{
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
			keyFocusedItem = NewFocusedItem;
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
		}
	}
};
