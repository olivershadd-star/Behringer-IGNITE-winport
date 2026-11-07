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
	//   Class: Ignite TrackConfig
	////////////////////////////////////////////////
	IgniteTrackConfig::IgniteTrackConfig()
	{
		addAndMakeVisible(autoSaveBtn);
		autoSaveBtn.addListener(this);
		autoSaveBtn.setToggleable(true);
		autoSaveBtn.setComponentID("autoSaveComp");
		autoSaveBtn.sethoverImages("toggle-autosave-default-hover.png", "toggle-autosave-active-hover.png", "toggle-autosave-disabled.png");

		addAndMakeVisible(trackMixer);
		trackMixer.addListener(this);
		trackMixer.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		trackMixer.setToggleable(true);
		trackMixer.setComponentID("trackMixerComp");

		autoSaveBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		trackMenuBox1.items.add(FlexItem(autoSaveBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		trackMenuBox1.items.add(FlexItem(trackMixer).withMargin({ 0,8,8,0 }).withFlex(1));

		mixerComp = TrackMixer::GetTrackMixerInstance();
		addAndMakeVisible(mixerComp);
		mixerComp->setBounds(10, 0, 1004, layout::middle.getHeight() + 15);
		mixerComp->setVisible(false);

		trackOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(trackOptCtl);
		trackOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		trackOptCtl->addOptCtlListener(this);

		popupPtr = CommonPopUp::getCommonPopupInstance();
	}

	IgniteTrackConfig::~IgniteTrackConfig()
	{
	}

	void IgniteTrackConfig::paint(juce::Graphics& g)
	{
		if (trackConfigDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("Track Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Track Configuration");

	}

	void IgniteTrackConfig::resized()
	{
		trackMenuBox1.performLayout(Rectangle(xStartSongMenuBox1, yStartSongMenuBox1, (int)(widthSongMenuBox1 * 0.67), heightSongMenuBox1));
	}

	void IgniteTrackConfig::enableControlButton(IgniteControlOptions::eKey key, bool state)
	{
		trackOptCtl->enableKey(key, state);
	}

	void IgniteTrackConfig::updateData()
	{
		std::vector<IgniteParamList> trackCfgParamList;
		IgniteParamList params;

		params.param = (paramId_t)SettingsTrackCnfgParam::SettingsTrackAutoSaveParam;
		trackCfgParamList.push_back(params);

		trackCfgParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackCnfg, trackCfgParamList);
		autoSaveTrack = (bool)trackCfgParamList[0].MsgValue.get<int8_t>();
		autoSaveBtn.setToggleState(autoSaveTrack, dontSendNotification);
		autoSaveBtn.getToggleState() ? autoSaveBtn.setButtonText("Auto Save:on") : autoSaveBtn.setButtonText("Auto Save:off");
	}

	void IgniteTrackConfig::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &autoSaveBtn)
		{
			autoSaveTrack = autoSaveBtn.getToggleState();
			if (IgniteTrack::GetAppTrackInstance()->trackDataUpdated && autoSaveTrack)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramSaveSongCmd, 0);
				IgniteTrack::GetAppTrackInstance()->updateLables();
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackCnfg, (paramId_t)SettingsTrackCnfgParam::SettingsTrackAutoSaveParam, autoSaveTrack);
			trackOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			trackOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			trackConfigDataUpdated = true;
			autoSaveBtn.setButtonText(autoSaveBtn.getToggleState() ? "Auto Save:on" : "Auto Save:off");
		}
		else if (buttonThatWasClicked == &trackMixer)
		{
			mixerComp->setVisible(true);
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgInit, 0);
			mixerComp->trackMixerOptCtl->enableKey(IgniteControlOptions::DEL, false);
			if (mixerComp->trackMixerDataUpdated)
			{
				mixerComp->trackMixerOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				mixerComp->trackMixerOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			}
			else
			{
				mixerComp->trackMixerOptCtl->enableKey(IgniteControlOptions::SAVE, false);
				mixerComp->trackMixerOptCtl->enableKey(IgniteControlOptions::UNDO, false);
			}
		}
	}

	void IgniteTrackConfig::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			trackConfigDataUpdated = false;
		}
		else if (option == IgniteControlOptions::AUTOSAVEON)
		{
			isAutosave = true;
		}
		else if (option == IgniteControlOptions::AUTOSAVEOFF)
		{
			isAutosave = false;
		}

		if (this->isVisible() && !mixerComp->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				popupPtr->close();
				popupPtr->setPopUpPropories("Save ", 604, 290);
				popupPtr->setbtnsize(265, 44);
				popupPtr->setInfoText(String(" Save Track Configuration edits? "));
				popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
				popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
				popupPtr->popupType = POPUP_WITHOKCANCEL;
				popupPtr->isCloseButtonVisible(false);
				popupPtr->show();
				popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 1)
					{
						_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackCnfg, (paramId_t)SettingsTrackCnfgParam::SettingsTrackCnfgSave, 0);
						trackOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						trackOptCtl->enableKey(IgniteControlOptions::UNDO, false);
						trackConfigDataUpdated = false;
					}
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
				};
			}
			else if (option == IgniteControlOptions::TRACKVIEW)
			{
				if (IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
				{
					AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::TRACK);
					IgniteTrack::GetAppTrackInstance()->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::TRACK_WINDOW);
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (trackConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackCnfg, (paramId_t)SettingsTrackCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> trackCfgParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsTrackCnfgParam::paramUndoListCmd;
					trackCfgParamList.push_back(params);
					trackCfgParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackCnfg, trackCfgParamList);
					if (trackCfgParamList.size() == 1)
					{
						trackConfigDataUpdated = false;
						trackOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						trackOptCtl->enableKey(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	bool IgniteTrackConfig::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool handled = true;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
		{
			PannelSendKey(false, param, KeyValue);
			if (option_handler_focus == TRACKCONFIG_DETAIL)
			{
				if (mixerComp->isVisible())
					mixerComp->PannelKeyHandler(param, KeyValue);
				else
				option_handler_focus = TRACKCONFIG_OPTION;
			}
			else
			{
				option_handler_focus = TRACKCONFIG_DETAIL;
			}
			PannelSendKey(true, param, KeyValue);
			return true;
		}

		if (option_handler_focus == TRACKCONFIG_DETAIL)
		{
			if (mixerComp->isVisible())
				mixerComp->PannelKeyHandler(param, KeyValue);
			else
				handled = false;

			if (!handled)
			{
				bool setfocus = true;
				if (KeyFocusedItem == TrackMenuViewItemID::NO_FOCUS)
				{
					/*1st key after Page visible */
					KeyFocusedItem = TrackMenuViewItemID::AUTO_SAVE;

					if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param && KeyValue == 1)
					{
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
						return true;
					}
				}
				else
				{
					PannelSendKey(false, param, KeyValue); // clear last Focus
					switch ((FrontPannelParam)param)
					{
					case FrontPannelParam::paramKey_RMOVELEFT:
						KeyFocusedItem = (KeyFocusedItem + 1 >= TrackMenuViewItemID::FOCUS_MAX ? (TrackMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
						break;
					case FrontPannelParam::paramKey_RMOVERIGHT:
						KeyFocusedItem = (KeyFocusedItem - 1 <= TrackMenuViewItemID::NO_FOCUS ? (TrackMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
						break;
					case FrontPannelParam::paramKey_RETURN_NAV:
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
						break;
					}
				}
				if (setfocus)
				{
					PannelSendKey(true, param, KeyValue);
				}
			}
		}
		else
		{
			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				OptFocusedItem = (OptFocusedItem + 1 >= TrackOptionsViewItemID::OP_FOCUS_MAX ? (TrackOptionsViewItemID::OP_FOCUS_MAX) : OptFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				OptFocusedItem = (OptFocusedItem - 1 <= TrackOptionsViewItemID::OP_NO_FOCUS ? (TrackOptionsViewItemID::OP_NO_FOCUS + 1) : OptFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
				break;
			}
			PannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void IgniteTrackConfig::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		bool state = false;

		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (option_handler_focus == TRACKCONFIG_DETAIL)
		{
			switch (TrackMenuView[KeyFocusedItem])
			{
			case AUTO_SAVE:
				autoSaveBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case TRACK_MIXER:
				trackMixer.FPKeyHandler(isFocuse, param, KeyValue);
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
				state = trackOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			case OPT_SCENELIST:
				state = trackOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::TRACKVIEW, isFocuse, param, KeyValue);
				break;
			}

			if (state == false)
			{
				OptFocusedItem++;
				if (OptFocusedItem > OP_FOCUS_MAX)
					OptFocusedItem = OPT_UNDO;
				PannelSendKey(isFocuse, param, KeyValue);
			}
		}
	}

	void IgniteTrackConfig::mouseUp(const MouseEvent& event)
	{
		auto a = event.eventComponent->getComponentID();
		int NewFocusedItem = TrackMenuViewItemID::NO_FOCUS;

		if (a == "autoSaveComp")					NewFocusedItem = TrackMenuViewItemID::AUTO_SAVE;
		else if (a == "trackMixerComp")	NewFocusedItem = TrackMenuViewItemID::TRACK_MIXER;

		if (NewFocusedItem != TrackMenuViewItemID::NO_FOCUS && NewFocusedItem != KeyFocusedItem)
		{
			PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
			KeyFocusedItem = NewFocusedItem;
			PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
		}
	}
};
