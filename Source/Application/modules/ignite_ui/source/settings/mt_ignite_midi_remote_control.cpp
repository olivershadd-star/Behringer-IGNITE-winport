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
	//   Class: IgniteMidiRemoteControl
	////////////////////////////////////////////////
	IgniteMidiRemoteControl::IgniteMidiRemoteControl()
	{
		addAndMakeVisible(pgmChangeMsgLable);
		pgmChangeMsgLable.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		pgmChangeMsgLable.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(midiPort);
		midiPort.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		midiPort.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(midiChannel);
		midiChannel.setDisplayTitle(true);
		midiChannel.setJustificationType(juce::Justification::centred);
		midiChannel.setTextColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(controlBtn);
		controlBtn.addListener(this);
		controlBtn.setToggleable(true);
		controlBtn.sethoverImages("btn-remote-control-default-hover.png", "btn-remote-control-active-hover.png", "");

		addAndMakeVisible(sceneChangeBtn);
		sceneChangeBtn.addListener(this);
		sceneChangeBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		sceneChangeBtn.setToggleable(true);
		sceneChangeBtn.setDisableImage("toggle-scenechange-disabled.png");
		sceneChangeBtn.sethoverImages("toggle-scenechange-default-hover.png", "toggle-scenechange-active-hover.png", "");

		sceneChangeBtn.setEnabled(false);
		pgmChangeMsgLable.setAlpha(0.2f);
		midiChannel.setAlpha(0.2f);
		midiPort.setAlpha(0.2f);
		midiChannel.setInterceptsMouseClicks(false, false);
		midiPort.setInterceptsMouseClicks(false, false);

		remoteControlOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(remoteControlOptCtl);
		remoteControlOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		remoteControlOptCtl->addOptCtlListener(this);

		pgmChangeMsgLable.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		controlBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		sceneChangeBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		ctlBox1.items.add(FlexItem(controlBtn).withMargin(0).withFlex(1));
		ctlBox1.items.add(FlexItem(midiPort).withMargin(0).withFlex(1));
		ctlBox1.items.add(FlexItem(midiChannel).withMargin(0).withFlex(1));

		ctlBox2.items.add(FlexItem(pgmChangeMsgLable).withMargin(10).withFlex(1));
		ctlBox3.items.add(FlexItem(sceneChangeBtn).withMargin(0).withFlex(1));

		setSize(getWidth(), getHeight());

		midiChannel.setcustombounds(true, ui::Rectangle(0, 15, 328, 34), ui::Rectangle(0, 49, 328, 20));
		midiPort.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		
		popupPtr = CommonPopUp::getCommonPopupInstance(); 
		getAssets();
		midiChannel.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlMidiChannel, value);
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			remoteControlDataUpdated = true;
		};

		midiPort.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlMidiPort, value);
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			remoteControlDataUpdated = true;
		};

		midiPort.onFocusChanged = [this](bool state)
		{
			repaint();
		};

		midiChannel.onFocusChanged = [this](bool state)
		{
			repaint();
		};
	}

	IgniteMidiRemoteControl::~IgniteMidiRemoteControl()
	{
	}

	void IgniteMidiRemoteControl::getAssets()
	{
		imageMidiBgDefault=juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-default.png"));
		imageMidiBgHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-default-hover.png"));
		imageCntBg= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("assigned-control-bg-default.png"));
	}

	void IgniteMidiRemoteControl::paint(juce::Graphics& g)
	{
		Image Draw;
		String imageName;
		if (remoteControlDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("MIDI Input Remote Control Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("MIDI Input Remote Control Configuration");

		g.setColour(ui::Theme::Instance().getColour((neutralBlack)));
		g.fillAll();

		Draw = midiPort.getFocusState() ? imageMidiBgHover : imageMidiBgDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 64, 328, 80  });

		Draw = midiChannel.getFocusState() ?  imageMidiBgHover : imageMidiBgDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 64, 328, 80  });

		g.drawImage(imageCntBg, ui::Rectangle<float>{ 348, 154, 666, 112  });
	}

	void IgniteMidiRemoteControl::updateData()
	{
		std::vector<IgniteParamList> midiRmtCntlParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlStatus;
		midiRmtCntlParams.push_back(params);
		params.param = (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlLatchParam;
		midiRmtCntlParams.push_back(params);
		params.param = (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlMidiPort;
		midiRmtCntlParams.push_back(params);
		params.param = (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlMidiChannel;
		midiRmtCntlParams.push_back(params);
		params.param = (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlSceneChangeParam;
		midiRmtCntlParams.push_back(params);
		params.param = (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlFontChangeParam;
		midiRmtCntlParams.push_back(params);

		midiRmtCntlParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, midiRmtCntlParams);

		for (auto& param_id : midiRmtCntlParams)
		{
			switch (param_id.param)
			{
			case (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlStatus:
				controlBtn.setToggleState((bool)param_id.MsgValue.get< int8_t >(), dontSendNotification);
				break;
			case (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlMidiPort:
				midiPort.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlMidiChannel:
				midiChannel.setText(String(param_id.MsgValue.get< int8_t >()), dontSendNotification);
				break;
			case (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlSceneChangeParam:
				sceneChangeBtn.setToggleState((bool)param_id.MsgValue.get< int8_t >(), dontSendNotification);
				break;
			}
		}

		if (controlBtn.getToggleState())
		{
			sceneChangeBtn.setEnabled(true);
			pgmChangeMsgLable.setAlpha(1.0f);
			midiChannel.setAlpha(1.0f);
			midiPort.setAlpha(1.0f);
			midiChannel.setInterceptsMouseClicks(true, true);
			midiPort.setInterceptsMouseClicks(true, true);


		}
		else
		{
			sceneChangeBtn.setEnabled(false);
			pgmChangeMsgLable.setAlpha(0.2f);
			midiChannel.setAlpha(0.2f);
			midiPort.setAlpha(0.2f);
			midiChannel.setInterceptsMouseClicks(false, false);
			midiPort.setInterceptsMouseClicks(false, false);
		}
	}

	void IgniteMidiRemoteControl::resized()
	{
		ctlBox1.performLayout(ui::Rectangle{ 10, 64, 1004,80 });
		ctlBox2.performLayout(ui::Rectangle{ 348, 154, 666, 50 });
		ctlBox3.performLayout(ui::Rectangle{ 508, 206, 320, 50 });
	}

	void IgniteMidiRemoteControl::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &controlBtn)
		{
			if (controlBtn.getToggleState())
			{
				sceneChangeBtn.setEnabled(true);
				pgmChangeMsgLable.setAlpha(1.0f);
				midiChannel.setAlpha(1.0f);
				midiPort.setAlpha(1.0f);
				midiChannel.setInterceptsMouseClicks(true, true);
				midiPort.setInterceptsMouseClicks(true, true);
			}
			else
			{
				sceneChangeBtn.setEnabled(false);
				pgmChangeMsgLable.setAlpha(0.2f);
				midiChannel.setAlpha(0.2f);
				midiPort.setAlpha(0.2f);
				midiChannel.setInterceptsMouseClicks(false, false);
				midiPort.setInterceptsMouseClicks(false, false);
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlStatus, controlBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &sceneChangeBtn)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, (paramId_t)SettingsRemoteControlCnfgParam::SettingsRemoteControlSceneChangeParam, sceneChangeBtn.getToggleState());
		}
		enableControlButton(IgniteControlOptions::SAVE, true);
		enableControlButton(IgniteControlOptions::UNDO, true);
		remoteControlDataUpdated = true;
	}

	void IgniteMidiRemoteControl::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			remoteControlDataUpdated = false;
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
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("Save ", 604, 290);

					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String("Save MIDI Input Remote Control edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, (paramId_t)SettingsRemoteControlCnfgParam::SettingRemoteControlCnfgSave, 0);
							enableControlButton(IgniteControlOptions::SAVE, false);
							enableControlButton(IgniteControlOptions::UNDO, false);
							remoteControlDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (remoteControlDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, (paramId_t)SettingsRemoteControlCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> midiRemoteCtlParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsRemoteControlCnfgParam::paramUndoListCmd;
					midiRemoteCtlParamList.push_back(params);
					midiRemoteCtlParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRemoteControlCnfg, midiRemoteCtlParamList);
					if (midiRemoteCtlParamList.size() == 1)
					{
						remoteControlDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgniteMidiRemoteControl::isEditing()
	{
		int index = 0;

		midiPort.IsEditing() ? index = 2 : 0;
		midiChannel.IsEditing() ? index = 3 : 0;

		return index;
	}

	bool IgniteMidiRemoteControl::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int editItem = RmtCtrlMenuViewItemID::NO_FOCUS;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if (KeyFocusedItem == RmtCtrlMenuViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = RmtCtrlMenuViewItemID::RMT_CTRL;
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
					KeyFocusedItem = (KeyFocusedItem + 1 >= RmtCtrlMenuViewItemID::FOCUS_MAX ? (RmtCtrlMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= RmtCtrlMenuViewItemID::NO_FOCUS ? (RmtCtrlMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
					break;
				case FrontPannelParam::paramRot_ROW:
					if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						KeyFocusedItem = (KeyFocusedItem + RMT_CTRL_ROW_ITEMS >= RmtCtrlMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + RMT_CTRL_ROW_ITEMS) == (RmtCtrlMenuViewItemID::FOCUS_MAX) ? (RmtCtrlMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + RMT_CTRL_ROW_ITEMS);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						KeyFocusedItem = (KeyFocusedItem - RMT_CTRL_ROW_ITEMS <= RmtCtrlMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - RMT_CTRL_ROW_ITEMS);
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

	void IgniteMidiRemoteControl::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		switch (RmtCtrlMenuView[KeyFocusedItem])
		{
		case RMT_CTRL:
			controlBtn.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case RMT_MIDI_CHANNEL:
			if (midiChannel.getAlpha() == 1.0f)
				midiChannel.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case RMT_MIDI_PORT:
			if (midiChannel.getAlpha() == 1.0f)
				midiPort.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case RMT_SCENE_CHANGE:
			if (sceneChangeBtn.isEnabled())
			{
				sceneChangeBtn.FPKeyHandler(isFocuse, param, KeyValue);
				if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse && controlBtn.getToggleState())
				{
					buttonClicked(&sceneChangeBtn);
				}
			}
			break;
		default:
			break;
		}
		repaint();
	}
};
