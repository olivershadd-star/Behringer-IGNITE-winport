/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY.
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
	//   Class: IgniteBackup
	////////////////////////////////////////////////
	IgniteBackup::IgniteBackup()
	{
		addAndMakeVisible(fullBackupBtn);
		fullBackupBtn.addListener(this);
		fullBackupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		fullBackupBtn.setToggleable(true);

		addAndMakeVisible(songBackupBtn);
		songBackupBtn.addListener(this);
		songBackupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		songBackupBtn.setToggleable(true);

		addAndMakeVisible(instrumentBackupBtn);
		instrumentBackupBtn.addListener(this);
		instrumentBackupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		instrumentBackupBtn.setToggleable(true);

		addAndMakeVisible(patternBackupBtn);
		patternBackupBtn.addListener(this);
		patternBackupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		patternBackupBtn.setToggleable(true);

		/*addAndMakeVisible(midiConfigBackupBtn);
		midiConfigBackupBtn.addListener(this);
		midiConfigBackupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		midiConfigBackupBtn.setToggleable(true);

		addAndMakeVisible(cvAndGateBackupBtn);
		cvAndGateBackupBtn.addListener(this);
		cvAndGateBackupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		cvAndGateBackupBtn.setToggleable(true);*/

		addAndMakeVisible(settingsBackupBtn);
		settingsBackupBtn.addListener(this);
		settingsBackupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		settingsBackupBtn.setToggleable(true);

		fullBackupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		songBackupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		instrumentBackupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		patternBackupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		/*midiConfigBackupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		cvAndGateBackupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());*/
		settingsBackupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		popupPtr = CommonPopUp::getCommonPopupInstance();

		ctlBox1.items.add(FlexItem(fullBackupBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(songBackupBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(patternBackupBtn).withMargin({ 0,8,8,0 }).withFlex(1));

		ctlBox2.items.add(FlexItem(instrumentBackupBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		/*ctlBox2.items.add(FlexItem(midiConfigBackupBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(cvAndGateBackupBtn).withMargin({ 0,8,8,0 }).withFlex(1));*/

		ctlBox2.items.add(FlexItem(settingsBackupBtn).withMargin({ 0,8,8,0 }).withFlex(1));
	}

	IgniteBackup::~IgniteBackup()
	{
	}

	void IgniteBackup::paint(juce::Graphics& g)
	{
		MenuMode::GetMenuModeInstance()->setHeader("Backup Save/Restore");
		g.setColour(ui::Theme::Instance().getColour((neutralBlack)));
		g.fillAll();
	}

	void IgniteBackup::encryptBackupAndSave(int item)
	{
		std::string backupName = "";
		std::string backupDir = "";
		//std::string backupInputDir = "";//TODO remove?

		switch (item)
		{
		case FULL_BACKUP:
			backupName = "Full";
			backupDir = backupInputDir + "/";
			break;
		case SONG_BACKUP:
			backupName = "Songs";
			backupDir = backupInputDir + backupName + "/";
			break;
		case PATTERN_BACKUP:
			backupName = "Patterns";
			backupDir = backupInputDir + backupName + "/";
			break;
		case INSTRUMENT_BACKUP:
			backupName = "Instruments";
			backupDir = backupInputDir + backupName + "/";
			break;
		case SETTINGS_BACKUP:
			backupName = "Settings";
			backupDir = backupInputDir + backupName + "/";
			break;
		}

		std::string backupImg = backupName;
		std::string backupTar = backupName + ".tar";
		std::string backupOutImg = outputDir + backupImg + "Backup";
		if (item == FULL_BACKUP)
			backupInputDir = rawBackupDir;
		else
			backupInputDir = rawBackupDir + backupName;

		std::string cmd = "rm -f " + backupOutImg;
		system(cmd.c_str());
		cmd = "tar -cf " + igniteDataDir + backupTar + " " + backupInputDir;
		system(cmd.c_str());
		cmd = "openssl enc -aes-256-cbc -a -salt -pbkdf2 -in " + igniteDataDir + backupTar + " -out " + backupOutImg + " -k 'MTBTMIIGNITE'";
		system(cmd.c_str());
		cmd = "rm -f " + igniteDataDir + backupTar;
		system(cmd.c_str());
	}

	void IgniteBackup::decryptBackupAndRestore(int item)
	{
		std::string backupName = "";

		switch (item)
		{
		case FULL_BACKUP:
			backupName = "Full";
			break;
		case SONG_BACKUP:
			backupName = "Songs";
			break;
		case PATTERN_BACKUP:
			backupName = "Patterns";
			break;
		case INSTRUMENT_BACKUP:
			backupName = "Instruments";
			break;
		case SETTINGS_BACKUP:
			backupName = "Settings";
			break;
		}

		std::string backupImg = backupName + "Backup";
		std::string backupTar = backupName + ".tar";
		std::string backupOutputTarFile = igniteDataDir + backupTar;
		std::string backupOutImg = outputDir + backupImg;
		std::string cmd = "openssl enc -aes-256-cbc -a -d -salt -pbkdf2 -in " + backupOutImg + " -out " + backupOutputTarFile + " -k 'MTBTMIIGNITE'";
		system(cmd.c_str());
		cmd = "tar -xf " + igniteDataDir + backupTar;
		system(cmd.c_str());
		cmd = "rm -f " + igniteDataDir + backupTar;
		system(cmd.c_str());
	}

	void IgniteBackup::backupPopup(String name)
	{
		std::vector<IgniteParamList> paramList;
		IgniteParamList params;

		params.param = (paramId_t)FrontPannelParam::paramKey_UsbGetConnectionStatus;
		paramList.push_back(params);
		paramList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramList);
		if (popupPtr->isDialogOpen.get() != true)
		{
			popupPtr->close();
			popupPtr->setPopUpPropories(name + " Backup", 604, 290);
			popupPtr->setbtnsize(137, 35);
			popupPtr->addImageButtonwithBounds("Save Backup", "btn-savebackup-default.png", "btn-savebackup-default-hover.png", "btn-savebackup-default-hover.png", 1, ui::Rectangle<int>{29, 105, 268, 50});
			popupPtr->addImageButtonwithBounds("Load Backup", "btn-loadbackup-default.png", "btn-loadbackup-default-hover.png", "btn-loadbackup-default-hover.png", 2, ui::Rectangle<int>{29, 165, 268, 50});

			if (paramList[0].MsgValue.get<std::int8_t>())
			{
				popupPtr->addImageButtonwithBounds("Save Backup to USB", "btn-saveusb-default.png", "btn-saveusb-default-hover.png", "btn-saveusb-default-hover.png", 3, ui::Rectangle<int>{307, 105, 268, 50});
				popupPtr->addImageButtonwithBounds("Load Backup from USB storage", "btn-loadusb-default.png", "btn-loadusb-default-hover.png", "btn-loadusb-default-hover.png", 4, ui::Rectangle<int>{307, 165, 268, 50});
			}
			else
			{
				popupPtr->addDisabledImageButtonwithBounds("Save Backup to USB", "btn-saveusb-disabled.png", "btn-saveusb-disabled.png", "btn-saveusb-disabled.png", 3, ui::Rectangle<int>{307, 105, 268, 50});
				popupPtr->addDisabledImageButtonwithBounds("Load Backup from USB storage", "btn-loadbackup-disabled.png", "btn-loadbackup-disabled.png", "btn-loadbackup-disabled.png", 4, ui::Rectangle<int>{307, 165, 268, 50});

			}
			popupPtr->popupType = POPUP_BACKUP;
			popupPtr->SetControlBtnLine(false);
			popupPtr->isCloseButtonVisible(true);
			popupPtr->show();
			popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 1)
					{
						this->postCommandMessage(1);
						_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamEngineCreateDataBackup, (uint8_t)KeyFocusedItem - 1, false);
						setTimeLimittoGif(1000);
					}
					else if (r == 2)
					{
						this->postCommandMessage(2); 
						_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamEngineRestoreDataBackup, (uint8_t)KeyFocusedItem - 1, false);
						setTimeLimittoGif(1000);
					}
					else if ((r == 3))
					{
						this->postCommandMessage(3);
						_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamEngineCreateDataBackup, (uint8_t)KeyFocusedItem - 1, false);
						encryptBackupAndSave(KeyFocusedItem);
						setTimeLimittoGif(1000);
					}
					else if ((r == 4))
					{
						this->postCommandMessage(4);
						decryptBackupAndRestore(KeyFocusedItem);
						_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamEngineRestoreDataBackup, (uint8_t)KeyFocusedItem - 1, false);
						setTimeLimittoGif(1000);
					}
				};
		}
	}

	void IgniteBackup::handleCommandMessage(int id)
	{
		popupPtr->close();
		if (id == 1)
			popupPtr->showPreloader("", "Saving Backup to internal memory is in Progress");
		else if (id == 2)
			popupPtr->showPreloader("", "Restoring Backup from internal memory is in Progress");
		else if (id == 3)
			popupPtr->showPreloader("", "Saveing Backup to USB Storage is in Progress");
		else if (id == 4)
			popupPtr->showPreloader("", "Restoring Backup from USB Storage is in Progress");
		else if (id == 5)
			AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
	}

	void IgniteBackup::resized()
	{
		ctlBox1.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox1, widthSongMenuBox1, heightSongMenuBox1));
		ctlBox2.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2, widthSongMenuBox1 * 2 / 3, heightSongMenuBox1));
		//ctlBox3.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2 + heightSongMenuBox1, widthSongMenuBox1 / 3, heightSongMenuBox1));
	}

	void IgniteBackup::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &fullBackupBtn)
		{
			fullBackupBtn.setToggleState(false, dontSendNotification);
			backupPopup("Full");
			KeyFocusedItem = FULL_BACKUP;
		}
		else if (buttonThatWasClicked == &songBackupBtn)
		{
			songBackupBtn.setToggleState(false, dontSendNotification);
			backupPopup("Song");
			KeyFocusedItem = SONG_BACKUP;
		}
		else if (buttonThatWasClicked == &instrumentBackupBtn)
		{
			instrumentBackupBtn.setToggleState(false, dontSendNotification);
			backupPopup("Instrument");
			KeyFocusedItem = INSTRUMENT_BACKUP;
		}
		else if (buttonThatWasClicked == &patternBackupBtn)
		{
			patternBackupBtn.setToggleState(false, dontSendNotification);
			backupPopup("Pattern");
			KeyFocusedItem = PATTERN_BACKUP;
		}
		/*else if (buttonThatWasClicked == &midiConfigBackupBtn)
		{
			midiConfigBackupBtn.setToggleState(false, dontSendNotification);
			backupPopup("MIDI Config");
			KeyFocusedItem = MIDI_CONFIG_BACKUP;
		}
		else if (buttonThatWasClicked == &cvAndGateBackupBtn)
		{
			cvAndGateBackupBtn.setToggleState(false, dontSendNotification);
			backupPopup("CV & Gate");
			KeyFocusedItem = CV_AND_GATE_BACKUP;
		}*/
		else if (buttonThatWasClicked == &settingsBackupBtn)
		{
			settingsBackupBtn.setToggleState(false, dontSendNotification);
			backupPopup("Settings");
			KeyFocusedItem = SETTINGS_BACKUP;
		}
	}

	void IgniteBackup::setTimeLimittoGif(int countLimit)
	{
		startTimer(countLimit);
	}

	void IgniteBackup::timerCallback()
	{
		stopTimer();
		popupPtr->close();

		if (popupPtr->isDialogOpen.get() != true)
		{
			if (auto dw = getCurrentlyModalComponent())
				dw->exitModalState(0);
		
			popupPtr->close();
			popupPtr->setPopUpPropories("Backup Status", 604, 290);
			popupPtr->setbtnsize(267, 44);
			popupPtr->setInfoText("Backup operation successful");
			popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_WITHOK;
			popupPtr->isCloseButtonVisible(false);
			popupPtr->show();
			popupPtr->onSelectionChanged = [this](int r)
			{
				if (r == 1)
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
			};
		}
	}

	int IgniteBackup::isEditing()
	{
		int index = 0;
		if (KeyFocusedItem == FULL_BACKUP)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = FULL_BACKUP;
			}
		}
		else if (KeyFocusedItem == SONG_BACKUP)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = SONG_BACKUP;
			}
		}
		else if (KeyFocusedItem == PATTERN_BACKUP)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = PATTERN_BACKUP;
			}
		}
		else if (KeyFocusedItem == INSTRUMENT_BACKUP)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = INSTRUMENT_BACKUP;
			}
		}
		/*else if (KeyFocusedItem == MIDI_CONFIG_BACKUP)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = MIDI_CONFIG_BACKUP;
			}
		}
		else if (KeyFocusedItem == CV_AND_GATE_BACKUP)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = CV_AND_GATE_BACKUP;
			}
		}*/
		else if (KeyFocusedItem == SETTINGS_BACKUP)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = SETTINGS_BACKUP;
			}
		}

		return index;
	}

	bool IgniteBackup::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int editItem = BackupMenuViewItemID::NO_FOCUS;

		if (param == (paramId_t)FrontPannelParam::paramKey_PowerKey_Event)
		{
			this->postCommandMessage(1);
			return true;
		}

		if (KeyFocusedItem == BackupMenuViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = BackupMenuViewItemID::FULL_BACKUP;

			if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
			{
				this->postCommandMessage(5);
				return true;
			}
		}
		else
		{
			editItem = isEditing();
			if (editItem)
			{
				if (KeyFocusedItem != editItem)
				{
					PannelSendKey(false, param, KeyValue);
					KeyFocusedItem = editItem;
				}
				setfocus = true;
			}
			else
			{
				PannelSendKey(false, param, KeyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					KeyFocusedItem = (KeyFocusedItem + 1 >= BackupMenuViewItemID::FOCUS_MAX ? (BackupMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= BackupMenuViewItemID::NO_FOCUS ? (BackupMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					this->postCommandMessage(5);
					break;
				case FrontPannelParam::paramRot_ROW:
					if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						KeyFocusedItem = (KeyFocusedItem + Backup_ROW_ITEMS >= BackupMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + Backup_ROW_ITEMS) == (BackupMenuViewItemID::FOCUS_MAX) ? (BackupMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + Backup_ROW_ITEMS);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						KeyFocusedItem = (KeyFocusedItem - Backup_ROW_ITEMS <= BackupMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - Backup_ROW_ITEMS);
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

	void IgniteBackup::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		switch (BackupMenuView[KeyFocusedItem])
		{
		case FULL_BACKUP:
			if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_RESET)
			{
				popupPtr->FPKeyHandler(true, param, KeyValue);
				return;
			}
			else
			{
				fullBackupBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
			break;
		case SONG_BACKUP:
			if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_RESET)
			{
				popupPtr->FPKeyHandler(true, param, KeyValue);
				return;
			}
			else
			{
				songBackupBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
			break;
		case PATTERN_BACKUP:
			if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_RESET)
			{
				popupPtr->FPKeyHandler(true, param, KeyValue);
				return;
			}
			else
			{
				patternBackupBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
			break;
		case INSTRUMENT_BACKUP:
			if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_RESET)
			{
				popupPtr->FPKeyHandler(true, param, KeyValue);
				return;
			}
			else
			{
				instrumentBackupBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
			break;
		/*case MIDI_CONFIG_BACKUP:
			if ((popupPtr != nullptr && popupPtr->IsEditing()) || (progressBarPtr != nullptr && progressBarPtr->isEditing()))
			{
				if (progressBarPtr != nullptr && progressBarPtr->isEditing())
				{
					progressBarPtr->FPKeyHandler(isFocuse, param, KeyValue);
				}
				else if (popupPtr != nullptr)
					popupPtr->FPKeyHandler(isFocuse, param, KeyValue);
			}
			else
			{
				midiConfigBackupBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
			break;
		case CV_AND_GATE_BACKUP:
			if ((popupPtr != nullptr && popupPtr->IsEditing()) || (progressBarPtr != nullptr && progressBarPtr->isEditing()))
			{
				if (progressBarPtr != nullptr && progressBarPtr->isEditing())
				{
					progressBarPtr->FPKeyHandler(isFocuse, param, KeyValue);
				}
				else if (popupPtr != nullptr)
					popupPtr->FPKeyHandler(isFocuse, param, KeyValue);
			}
			else
			{
				cvAndGateBackupBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
			break;*/
		case SETTINGS_BACKUP:
			if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_RESET)
			{
				popupPtr->FPKeyHandler(true, param, KeyValue);
				return;
			}
			else
			{
				settingsBackupBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
			break;
		default:
			break;
		}
		repaint();
	}
};
