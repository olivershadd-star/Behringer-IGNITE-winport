/*
 * Copyright (c) - 2024 - MUSIC Tribe, MY.
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
	//   Class: Ignite Misc Setting
	////////////////////////////////////////////////
	IgniteMiscSettings::IgniteMiscSettings()
	{
		addAndMakeVisible(globalSaveBtn);
		globalSaveBtn.addListener(this);
		globalSaveBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		globalSaveBtn.setToggleable(true);
		globalSaveBtn.setComponentID("globalSaveComp");
		globalSaveBtn.sethoverImages("toggle-saveas-hover-1.png", "toggle-saveas-hover.png", "");

		addAndMakeVisible(midiResetBtn);
		midiResetBtn.addListener(this);
		midiResetBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		midiResetBtn.setToggleable(true);
		midiResetBtn.setComponentID("midiResetComp");

		addAndMakeVisible(safeStopBtn);
		safeStopBtn.addListener(this);
		safeStopBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		safeStopBtn.setToggleable(true);
		safeStopBtn.setComponentID("safeStopComp");
		safeStopBtn.sethoverImages("toggle-safestop-on-hover-1.png", "toggle-safestop-on-hover.png", "");

		addAndMakeVisible(usbStopBtn);
		usbStopBtn.addListener(this);
		usbStopBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		usbStopBtn.setToggleable(true);
		usbStopBtn.setComponentID("usbStopComp");
		usbStopBtn.sethoverImages("toggle-usbstop-off-hover.png", "toggle-usbstop-on-hover.png", "");

		addAndMakeVisible(autoSaveCfgBtn);
		autoSaveCfgBtn.addListener(this);
		autoSaveCfgBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		autoSaveCfgBtn.setToggleable(true);
		autoSaveCfgBtn.setComponentID("autoSaveComp");
		autoSaveCfgBtn.sethoverImages("toggle-autosave-hover-1.png", "toggle-autosave-all-hover.png", "");

		addAndMakeVisible(systemLogBtn);
		systemLogBtn.addListener(this);
		systemLogBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		systemLogBtn.setToggleable(true);
		systemLogBtn.setDisableImage("btn-systemlog-disabled.png");
		systemLogBtn.setComponentID("systemLogComp");

#if ENABLE_HARDWARE_TEST
		addAndMakeVisible(testDataManagerBtn);
		testDataManagerBtn.addListener(this);
		testDataManagerBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		testDataManagerBtn.setToggleable(true);
		testDataManagerBtn.showBorder(false);
		testDataManagerBtn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		testDataManagerBtn.setColour(juce::TextButton::textColourOffId, Theme::Instance().getColour(customOrange));
		testDataManagerBtn.setVisible(true);
#endif

		miscSettingsOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(miscSettingsOptCtl);
		miscSettingsOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		miscSettingsOptCtl->addOptCtlListener(this);

		addAndMakeVisible(calibBtn);
		calibBtn.addListener(this);
		calibBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		calibBtn.setToggleable(true);
		calibBtn.setComponentID("calibComp");

		calibBtn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		globalSaveBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		midiResetBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		autoSaveCfgBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		safeStopBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		usbStopBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		systemLogBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		settingsBox1.items.add(FlexItem(globalSaveBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox1.items.add(FlexItem(autoSaveCfgBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox1.items.add(FlexItem(midiResetBtn).withMargin({ 0,8,8,0 }).withFlex(1));

		settingsBox2.items.add(FlexItem(safeStopBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox2.items.add(FlexItem(usbStopBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox2.items.add(FlexItem(calibBtn).withMargin({ 0,8,8,0 }).withFlex(1));

		settingsBox.flexDirection = FlexBox::Direction::column;
		settingsBox.items.add(FlexItem(settingsBox1).withFlex(1));
		settingsBox.items.add(FlexItem(settingsBox2).withFlex(1));

		popupPtr = CommonPopUp::getCommonPopupInstance();
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();

#if ENABLE_HARDWARE_TEST
		testComp = IgniteTest::GetAppTestDataInstance();
		addChildComponent(testComp);;
		testComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		testComp->setVisible(false);
#endif
		calibComp = IgniteCalibration::GetAppCalibrationInstance();
		addChildComponent(calibComp);
		calibComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		calibComp->setVisible(false);

		optPtr = IgniteControlOptions::GetAppOptInstance();
	}

	IgniteMiscSettings::~IgniteMiscSettings()
	{
	}

	void IgniteMiscSettings::paint(juce::Graphics& g)
	{
		if (miscSettingsDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("Miscellaneous Options*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Miscellaneous Options");

		g.setColour(ui::Theme::Instance().getColour(neutralBlack));
		g.fillAll();

		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-default.png"));
		Image OverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-default-hover.png"));
		Image BtnActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-active.png"));
		Image Draw;

#if ENABLE_HARDWARE_TEST
		Draw = testDataManagerBtn.getToggleState() ? BtnActiveImage : ((testDataManagerBtn.isMouseOver() || testDataManagerBtn.isFocused) ? OverImage : defaultImage);
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 246, 328, 90 });
#endif
	}

	void IgniteMiscSettings::enableControlButton(IgniteControlOptions::eKey key, bool state)
	{
		miscSettingsOptCtl->enableKey(key, state);
	}

	void IgniteMiscSettings::updateData()
	{
		std::vector<IgniteParamList> SettingsGeneralCnfgParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgSafeStopParam;
		SettingsGeneralCnfgParams.push_back(params);

		SettingsGeneralCnfgParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, SettingsGeneralCnfgParams);

		safeStopBtn.setToggleState((bool)SettingsGeneralCnfgParams[0].MsgValue.get<int8_t>(), dontSendNotification);
		IgniteControlOptions::GetAppOptInstance()->setSafeStopStatus((bool)SettingsGeneralCnfgParams[0].MsgValue.get<int8_t>());
		current_screen = NO_FOCUS;

		SettingsGeneralCnfgParams.clear();
		params.param = (paramId_t)FrontPannelParam::paramKey_UsbGetConnectionStatus;
		SettingsGeneralCnfgParams.push_back(params);

		SettingsGeneralCnfgParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, SettingsGeneralCnfgParams);
		usbConnectionStatus = SettingsGeneralCnfgParams[0].MsgValue.get<bool>();

		if (usbConnectionStatus)
			systemLogBtn.setEnabled(true);
		else
			systemLogBtn.setEnabled(false);
	}

	void IgniteMiscSettings::resized()
	{
		settingsBox.performLayout(ui::Rectangle(10, yStartSettingBox, 1012, 180));
		systemLogBtn.setBounds(ui::Rectangle(7, 246, 333, 90));
#if ENABLE_HARDWARE_TEST
		testDataManagerBtn.setBounds(ui::Rectangle(348, 246, 328, 90));
#endif
	}

	void IgniteMiscSettings::midiResetPopup()
	{
		if (popupPtr->isDialogOpen.get() != true)
		{
			popupPtr->close();
			popupPtr->setPopUpPropories("MIDI Reset", 604, 290);
			popupPtr->setbtnsize(267, 44);
			popupPtr->setInfoText("Select Reset to reset MIDI into default setting?");
			popupPtr->addImageButton("Cancel", "btn-secondary-cancel-267x44-default.png", "btn-secondary-cancel-267x44-default-hover.png", 2);
			popupPtr->addImageButton("Reset", "btn-reset-267x44-default.png", "btn-reset-267x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_RESET;
			popupPtr->requestforReturnValueCallback();
			popupPtr->isCloseButtonVisible(false);
			popupPtr->show();

			popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 2)
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					}
					else
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);

					}
				};
			popupPtr->onActionReturnvalue = [this](int r)
				{
					if (r == 1)
					{
						midiReset = true;
						popupPtr->close();
						popupPtr->showPreloader("Midi Reset", "Midi Reset in Progress");
						setTimeLimittoGif(2000);
						popupPtr->onSelectionChanged = [this](int r)
							{

							};
					}

				};
		}
	}

	void IgniteMiscSettings::systemLogPopup()
	{
		if (popupPtr->isDialogOpen.get() != true)
		{
			popupPtr->close();
			popupPtr->setPopUpPropories("System Log", 604, 290);
			popupPtr->setbtnsize(267, 44);
			popupPtr->setInfoText("Select Yes to save log to usb flash storage ");
			popupPtr->addImageButton("Cancel", "btn-secondary-cancel-267x44-default.png", "btn-secondary-cancel-267x44-default-hover.png", 2);
			popupPtr->addImageButton("Yes", "btn-deleteyes-default.png", "btn-yes-267x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_WITHOKCANCEL;
			popupPtr->requestforReturnValueCallback();
			popupPtr->isCloseButtonVisible(false);
			popupPtr->show();

			popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 2)
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					}
					else
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					}
				};
			popupPtr->onActionReturnvalue = [this](int r)
				{
					if ((r == 1) && usbConnectionStatus)
					{
						popupPtr->close();
						popupPtr->showPreloader("System Log", "Saving log file to usb in Progress");
						setTimeLimittoGif(2000);
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
						std::string cmd = "tar -cvf /data/ignite/logs.tar /var/log/; openssl aes-256-cbc -a -salt -pbkdf2 -in /data/ignite/logs.tar -out /data/ignite/logs.img -k 'MTBTMIIGNITE'; cp -f /data/ignite/logs.img /mnt/flash/ignite_log.img; rm -f /data/ignite/logs.tar";
						system(cmd.c_str());
# endif
					}
				};
		}
	}

	void IgniteMiscSettings::setTimeLimittoGif(int countLimit)
	{
		startTimer(countLimit);
	}

	void IgniteMiscSettings::timerCallback()
	{
		stopTimer();
		if (auto dw = getCurrentlyModalComponent())
			dw->exitModalState(0);

		if (popupPtr->isDialogOpen.get() != true)
		{
			popupPtr->close();
			if (midiReset)
			{
				popupPtr->setPopUpPropories("MIDI Reset Status", 604, 290);
				popupPtr->setInfoText("MIDI reset successful");
			}
			else
			{
				popupPtr->setPopUpPropories("System Log", 604, 290);
				popupPtr->setInfoText("System log saved to usb flash storage");
			}
			popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_WITHOK;
			popupPtr->isCloseButtonVisible(false);
			popupPtr->show();
			popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 1)
					{
						midiReset = false;
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					}
				};
		}
	}

	void IgniteMiscSettings::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &themeBtn)
		{
		}
		else if (buttonThatWasClicked == &globalSaveBtn)
		{
			current_screen = GLOBAL_SAVE;
			KeyFocusedItem = GLOBAL_SAVE;
			optPtr->SaveStatusChanged(globalSaveBtn.getToggleState() ? IgniteControlOptions::SAVEALLON : IgniteControlOptions::SAVEALLOFF, globalSaveBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &autoSaveCfgBtn)
		{
			current_screen = GLOBAL_AUTO_SAVE;
			KeyFocusedItem = GLOBAL_AUTO_SAVE;
			optPtr->SaveStatusChanged(autoSaveCfgBtn.getToggleState() ? IgniteControlOptions::AUTOSAVEON : IgniteControlOptions::AUTOSAVEOFF, autoSaveCfgBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &midiResetBtn)
		{
			midiResetBtn.setToggleState(false, dontSendNotification);
			midiResetPopup();
			current_screen = MIDI_RESET;
			KeyFocusedItem = MIDI_RESET;
		}
		else if (buttonThatWasClicked == &safeStopBtn)
		{
			IgniteControlOptions::GetAppOptInstance()->setSafeStopStatus(safeStopBtn.getToggleState());
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgSafeStopParam, safeStopBtn.getToggleState());
			current_screen = SAFE_STOP;
			KeyFocusedItem = SAFE_STOP;
		}
		else if (buttonThatWasClicked == &usbStopBtn)
		{
			std::vector<IgniteParamList> paramList;
			IgniteParamList params;

			params.param = (paramId_t)FrontPannelParam::paramKey_UsbGetConnectionStatus;
			paramList.push_back(params);

			paramList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramList);

			if (paramList[0].MsgValue.get<bool>())
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_USBStop, true, false);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgUSBParam, true);
				current_screen = USB_STOP;
				KeyFocusedItem = USB_STOP;
				_pInfoWindow->setTextandShow("Safe To Remove USB device");
				usbStopBtn.repaint();
				Time::waitForMillisecondCounter(Time::getMillisecondCounter() + 1000);
			}
			else
			{
				_pInfoWindow->setTextandShow("No USB Device Connected");
			}
			usbStopBtn.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &calibBtn)
		{
			calibComp->updateCalibDataFromEngine();
			calibComp->setVisible(true);
			current_screen = CV_GATE_CALLIB;
			KeyFocusedItem = CV_GATE_CALLIB;
		}
#if ENABLE_HARDWARE_TEST
		else if (buttonThatWasClicked == &testDataManagerBtn)
		{
			testComp->setVisible(true);
		}
#endif
		else if (buttonThatWasClicked == &systemLogBtn)
		{
			systemLogBtn.setToggleState(false, dontSendNotification);
			systemLogPopup();
			current_screen = SYSTEM_LOG;
			KeyFocusedItem = SYSTEM_LOG;
		}
	}

	void IgniteMiscSettings::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			miscSettingsDataUpdated = false;
		}
		else if (option == IgniteControlOptions::AUTOSAVEON)
		{
			isAutosave = true;
		}
		else if (option == IgniteControlOptions::AUTOSAVEOFF)
		{
			isAutosave = false;
		}
		if (this->isVisible() && !calibComp->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("Save ", 604, 290);
					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String("Save Misc Settings edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
						{
							if (r == 1)
							{
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgSave, 0);
								miscSettingsOptCtl->enableKey(IgniteControlOptions::SAVE, false);
								miscSettingsOptCtl->enableKey(IgniteControlOptions::UNDO, false);
								miscSettingsDataUpdated = false;
							}
							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);
						};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (miscSettingsDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> settingCtlParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsGeneralCnfgParam::paramUndoListCmd;
					settingCtlParamList.push_back(params);
					settingCtlParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, settingCtlParamList);
					if (settingCtlParamList.size() == 1)
					{
						miscSettingsDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgniteMiscSettings::isEditing()
	{
		int index = 0;

		if (KeyFocusedItem == MIDI_RESET)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = MIDI_RESET;
			}
		}
		else if (KeyFocusedItem == SYSTEM_LOG)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = SYSTEM_LOG;
			}
		}
		return index;
	}

	bool IgniteMiscSettings::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool handled = true;

		if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_RESET)
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
		{
			pannelSendKey(false, param, KeyValue);
			if (option_handler_focus == MISC_SETTING_DETAIL)
			{
				option_handler_focus = MISC_SETTING_OPTION;
			}
			else
			{
				option_handler_focus = MISC_SETTING_DETAIL;
			}
			pannelSendKey(true, param, KeyValue);
			return true;
		}

		if (option_handler_focus == MISC_SETTING_DETAIL)
		{
			switch (current_screen)
			{
			case CV_GATE_CALLIB:
				handled = calibComp->pannelKeyHandler(param, KeyValue);
				break;
			default:
				handled = false;
				break;
			}

			if (!handled)
			{
				bool setfocus = true;
				int EditItem = MiscSettingsMenuViewItemID::NO_FOCUS;

				if (KeyFocusedItem == MiscSettingsMenuViewItemID::NO_FOCUS)
				{
					/*1st key after Page visible */
					KeyFocusedItem = MiscSettingsMenuViewItemID::GLOBAL_SAVE;

					if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
					{
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
						return true;
					}
				}
				else
				{
					EditItem = isEditing();
					if (EditItem)
					{
						if (KeyFocusedItem != EditItem)
						{
							pannelSendKey(false, param, KeyValue);
							KeyFocusedItem = EditItem;
						}
						setfocus = true;
					}
					else
					{
						pannelSendKey(false, param, KeyValue); // clear last Focus
						switch ((FrontPannelParam)param)
						{
						case FrontPannelParam::paramKey_RMOVELEFT:
							KeyFocusedItem = (KeyFocusedItem + 1 >= MiscSettingsMenuViewItemID::FOCUS_MAX ? (MiscSettingsMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
							break;
						case FrontPannelParam::paramKey_RMOVERIGHT:
							KeyFocusedItem = (KeyFocusedItem - 1 <= MiscSettingsMenuViewItemID::NO_FOCUS ? (MiscSettingsMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
							break;
						case FrontPannelParam::paramKey_RETURN_NAV:
							AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
							break;
						case FrontPannelParam::paramRot_ROW:
							if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
							{
								pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
								KeyFocusedItem = (KeyFocusedItem + SETTINGS_ROW_ITEMS >= MiscSettingsMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + SETTINGS_ROW_ITEMS) == (MiscSettingsMenuViewItemID::FOCUS_MAX) ? (MiscSettingsMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + SETTINGS_ROW_ITEMS);
								pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
							}
							else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
							{
								pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
								KeyFocusedItem = (KeyFocusedItem - SETTINGS_ROW_ITEMS <= MiscSettingsMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - SETTINGS_ROW_ITEMS);
								pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
							}
							repaint();
							setfocus = false;
							break;
						}
					}
				}
				if (setfocus)
				{
					pannelSendKey(true, param, KeyValue);
				}
				handled = true;
			}
		}
		else
		{
			pannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				OptFocusedItem = (OptFocusedItem + 1 >= MiscSettingsOptionsViewItemID::OP_FOCUS_MAX ? (MiscSettingsOptionsViewItemID::OP_FOCUS_MAX) : OptFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				OptFocusedItem = (OptFocusedItem - 1 <= MiscSettingsOptionsViewItemID::OP_NO_FOCUS ? (MiscSettingsOptionsViewItemID::OP_NO_FOCUS + 1) : OptFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
				break;
			}
			pannelSendKey(true, param, KeyValue);
		}
		return handled;
	}

	void IgniteMiscSettings::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{

		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (option_handler_focus == MISC_SETTING_DETAIL)
		{
			switch (MiscSettingsMenuView[KeyFocusedItem])
			{
			case GLOBAL_SAVE:
				globalSaveBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case GLOBAL_AUTO_SAVE:
				autoSaveCfgBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case USB_STOP:
				usbStopBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case SAFE_STOP:
				safeStopBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_RESET:
				if ((popupPtr != nullptr && popupPtr->IsEditing()) || midiReset)
				{
					popupPtr->FPKeyHandler(isFocuse, param, KeyValue);
				}
				else
				{
					midiResetBtn.FPKeyHandler(isFocuse, param, KeyValue);
				}
				break;
			case CV_GATE_CALLIB:
				calibBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case SYSTEM_LOG:
				if ((popupPtr != nullptr && popupPtr->IsEditing()))
				{
					popupPtr->FPKeyHandler(isFocuse, param, KeyValue);
				}
				else
				{
					systemLogBtn.FPKeyHandler(isFocuse, param, KeyValue);
				}
				break;
			default:
				break;
			}
			repaint();
		}
		else
		{
			switch (OptionsView[OptFocusedItem])
			{
			case OPT_UNDO:
				miscSettingsOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			}
		}
	}
};