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
	//   Class: IgniteMidiMachineControl
	////////////////////////////////////////////////
	IgniteMidiMachineControl::IgniteMidiMachineControl()
	{
		addAndMakeVisible(midiRxPort);
		midiRxPort.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		midiRxPort.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(midiTxPort);
		midiTxPort.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		midiTxPort.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(midiRxChannel);
		midiRxChannel.setDisplayTitle(true);
		midiRxChannel.setJustificationType(juce::Justification::centred);
		midiRxChannel.setTextColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(mmcRxAll);
		mmcRxAll.addListener(this);
		mmcRxAll.setToggleable(true);
		mmcRxAll.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mmcRxAll.setDisableImage("btn-mmc-all-disabled.png");
		mmcRxAll.sethoverImages("btn-mmc-all-default-hover.png", "btn-mmc-all-active-hover.png", "");

		addAndMakeVisible(mmcTxBtn);
		mmcTxBtn.addListener(this);
		mmcTxBtn.setToggleable(true);
		mmcTxBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mmcTxBtn.sethoverImages("toggle-mmc-send-off-hover.png", "toggle-mmc-send-on-hover.png", "toggle-mmc-send-off-disabled.png");

		addAndMakeVisible(mmcRxBtn);
		mmcRxBtn.addListener(this);
		mmcRxBtn.setToggleable(true);
		mmcRxBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mmcRxBtn.sethoverImages("toggle-mmc-receive-off-hover.png","toggle-mmc-receive-on-hover.png","toggle-mmc-receive-on-hover.png");

		midiRxChannel.setAlpha(0.2f);
		midiRxPort.setAlpha(0.2f);
		midiTxPort.setAlpha(0.2f);
		midiRxChannel.setInterceptsMouseClicks(false, false);
		midiRxPort.setInterceptsMouseClicks(false, false);
		midiTxPort.setInterceptsMouseClicks(false, false);
		mmcRxAll.setEnabled(false);

		popupPtr = CommonPopUp::getCommonPopupInstance();

		mmcOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(mmcOptCtl);
		mmcOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		mmcOptCtl->addOptCtlListener(this);

		ctlBox1.items.add(FlexItem(mmcRxBtn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(midiRxPort).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(midiRxChannel).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(mmcRxAll).withMargin({ 0,0,0,0 }).withFlex(1));

		ctlBox2.items.add(FlexItem(mmcTxBtn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(midiTxPort).withMargin({ 0,0,0,0 }).withFlex(1));

		setSize(getWidth(), getHeight());

		midiRxChannel.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));
		midiRxPort.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		midiTxPort.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,49,604,450 });

		midiRxChannel.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg, (paramId_t)SettingsMidiMachineControlCnfgParam::paramMidiMachineControlDeviceId, value);
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			mmcDataUpdated = true;
		};

		midiRxPort.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg, (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlInputPort, value);
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			mmcDataUpdated = true;
		};

		midiTxPort.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg , (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlOutputPort, value);
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			mmcDataUpdated = true;
		};

		midiRxPort.onFocusChanged = [this](bool state)
		{
			repaint();
		};

		midiRxChannel.onFocusChanged = [this](bool state)
		{
			repaint();
		};
		midiTxPort.onFocusChanged = [this](bool state)
		{
			repaint();
		};
	}

	IgniteMidiMachineControl::~IgniteMidiMachineControl()
	{
	}

	void IgniteMidiMachineControl::paint(juce::Graphics& g)
	{
		Image Draw;
		String imageName;
		if (mmcDataUpdated)
			MenuMode::GetMenuModeInstance()->setHeader("MIDI Machine Control Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("MIDI Machine Control Configuration");

		g.setColour(ui::Theme::Instance().getColour((neutralBlack)));
		g.fillAll();

		imageName = midiRxPort.getFocusState() ? "toggle-btn-bg-245x80-default-hover.png" : "toggle-btn-bg-245x80-default.png";
		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(imageName));
		g.drawImage(Draw, ui::Rectangle<float>{ 263, 70, 245, 80  });

		imageName = midiRxChannel.getFocusState() ? "toggle-btn-bg-245x80-default-hover.png" : "toggle-btn-bg-245x80-default.png";
		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(imageName));
		g.drawImage(Draw, ui::Rectangle<float>{ 516, 70, 245, 80  });

		imageName = midiTxPort.getFocusState() ? "toggle-btn-bg-245x80-default-hover.png" : "toggle-btn-bg-245x80-default.png";
		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(imageName));
		g.drawImage(Draw, ui::Rectangle<float>{ 263, 158, 245, 80  });
	}

	void IgniteMidiMachineControl::updateData()
	{
		std::vector<IgniteParamList> midiMachCntlParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlReceiveStatus;
		midiMachCntlParams.push_back(params);
		params.param = (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlSendStatus;
		midiMachCntlParams.push_back(params);
		params.param = (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlInputPort;
		midiMachCntlParams.push_back(params);
		params.param = (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlOutputPort;
		midiMachCntlParams.push_back(params);
		params.param = (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlDeviceId;
		midiMachCntlParams.push_back(params);
		params.param = (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlDeviceIdAll;
		midiMachCntlParams.push_back(params);

		midiMachCntlParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg , midiMachCntlParams);

		for (auto& param_id : midiMachCntlParams)
		{
			switch (param_id.param)
			{
			case (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlReceiveStatus:
				mmcRxBtn.setToggleState((bool)param_id.MsgValue.get< int8_t >(), dontSendNotification);
				break;
			case (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlSendStatus:
				mmcTxBtn.setToggleState((bool)param_id.MsgValue.get< int8_t >(), dontSendNotification);
				break;
			case (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlInputPort:
				midiRxPort.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlOutputPort:
				midiTxPort.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsMidiMachineControlCnfgParam::paramMidiMachineControlDeviceId:
				midiRxChannel.setText(String(param_id.MsgValue.get< int8_t >()), dontSendNotification);
				break;
			case (paramId_t)SettingsMidiMachineControlCnfgParam::paramMidiMachineControlDeviceIdAll:
				mmcRxAll.setToggleState((bool)param_id.MsgValue.get< int8_t >(), dontSendNotification);
				break;
			}
		}

		if (mmcRxBtn.getToggleState())
		{
			midiRxChannel.setAlpha(1.0f);
			midiRxPort.setAlpha(1.0f);
			midiRxChannel.setInterceptsMouseClicks(true, true);
			midiRxPort.setInterceptsMouseClicks(true, true);
			mmcRxAll.setEnabled(true);
			if (mmcRxAll.getToggleState())
			{
				midiRxChannel.setAlpha(0.2f);
				midiRxChannel.setInterceptsMouseClicks(false, false);
			}
			else
			{
				midiRxChannel.setAlpha(1.0f);
				midiRxChannel.setInterceptsMouseClicks(true, true);
			}
		}
		else
		{
			midiRxPort.setAlpha(0.2f);
			midiRxPort.setInterceptsMouseClicks(false, false);
			mmcRxAll.setEnabled(false);
			midiRxChannel.setAlpha(0.2f);
			midiRxChannel.setInterceptsMouseClicks(false, false);
		}

		if (mmcTxBtn.getToggleState())
		{
			midiTxPort.setAlpha(1.0f);
			midiTxPort.setInterceptsMouseClicks(true, true);
		}
		else
		{
			midiTxPort.setAlpha(0.2f);
			midiTxPort.setInterceptsMouseClicks(false, false);
		}
	}

	void IgniteMidiMachineControl::resized()
	{
		ctlBox1.performLayout(ui::Rectangle{ 10, 70, 1004, 80 });
		ctlBox2.performLayout(ui::Rectangle{ 10, 158, 498, 80 });
	}

	void IgniteMidiMachineControl::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &mmcTxBtn)
		{
			if (mmcTxBtn.getToggleState())
			{
				midiTxPort.setAlpha(1.0f);
				midiTxPort.setInterceptsMouseClicks(true, true);
			}
			else
			{
				midiTxPort.setAlpha(0.2f);
				midiTxPort.setInterceptsMouseClicks(false, false);
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg , (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlSendStatus, mmcTxBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &mmcRxBtn)
		{
			if (mmcRxBtn.getToggleState())
			{
				midiRxChannel.setAlpha(1.0f);
				midiRxPort.setAlpha(1.0f);
				midiRxChannel.setInterceptsMouseClicks(true, true);
				midiRxPort.setInterceptsMouseClicks(true, true);
				mmcRxAll.setEnabled(true);
			}
			else
			{
				midiRxChannel.setAlpha(0.2f);
				midiRxPort.setAlpha(0.2f);
				midiRxChannel.setInterceptsMouseClicks(false, false);
				midiRxPort.setInterceptsMouseClicks(false, false);
				mmcRxAll.setEnabled(false);
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg , (paramId_t)SettingsMidiMachineControlCnfgParam ::paramMidiMachineControlReceiveStatus, mmcRxBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &mmcRxAll)
		{
			if (mmcRxAll.getToggleState())
			{
				midiRxChannel.setAlpha(0.2f);
				midiRxChannel.setInterceptsMouseClicks(false, false);
			}
			else
			{
				midiRxChannel.setAlpha(1.0f);
				midiRxChannel.setInterceptsMouseClicks(true, true);
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg, (paramId_t)SettingsMidiMachineControlCnfgParam::paramMidiMachineControlDeviceIdAll, mmcRxAll.getToggleState());
		}

		enableControlButton(IgniteControlOptions::SAVE, true);
		enableControlButton(IgniteControlOptions::UNDO, true);
		mmcDataUpdated = true;
	}

	void IgniteMidiMachineControl::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (this->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("Save ", 604, 290);
					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String("Save MIDI Machine Control edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg, (paramId_t)SettingsMidiMachineControlCnfgParam::SettingMidiMachineControlCnfgSave, 0);
							enableControlButton(IgniteControlOptions::SAVE, false);
							enableControlButton(IgniteControlOptions::UNDO, false);
							mmcDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (mmcDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg , (paramId_t)SettingsMidiMachineControlCnfgParam ::paramUndoCmd, 0);

					std::vector<IgniteParamList> midiMachineCtlParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsMidiMachineControlCnfgParam ::paramUndoListCmd;
					midiMachineCtlParamList.push_back(params);
					midiMachineCtlParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiMachineControlCnfg , midiMachineCtlParamList);
					if (midiMachineCtlParamList.size() == 1)
					{
						mmcDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgniteMidiMachineControl::isEditing()
	{
		int index = 0;

		midiRxPort.IsEditing() ? index = 2 : 0;
		midiRxChannel.IsEditing() ? index = 3 : 0;
		midiTxPort.IsEditing() ? index = 6 : 0;
		return index;
	}

	bool IgniteMidiMachineControl::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int editItem = MMCMenuViewItemID::NO_FOCUS;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if (KeyFocusedItem == MMCMenuViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = MMCMenuViewItemID::MMC_TX_CTRL;
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
					KeyFocusedItem = (KeyFocusedItem + 1 >= MMCMenuViewItemID::FOCUS_MAX ? (MMCMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= MMCMenuViewItemID::NO_FOCUS ? (MMCMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
					break;
				case FrontPannelParam::paramRot_ROW:
					if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						KeyFocusedItem = (KeyFocusedItem + MMC_ROW_ITEMS >= MMCMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + MMC_ROW_ITEMS) == (MMCMenuViewItemID::FOCUS_MAX) ? (MMCMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + MMC_ROW_ITEMS);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						KeyFocusedItem = (KeyFocusedItem - MMC_ROW_ITEMS <= MMCMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - MMC_ROW_ITEMS);
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

	void IgniteMidiMachineControl::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		switch (MMCMenuView[KeyFocusedItem])
		{
		case MMC_TX_CTRL:
			mmcTxBtn.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case MMC_RX_CTRL:
			mmcRxBtn.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case MMC_MIDI_RX_DEVID:
			if (midiRxChannel.getAlpha() == 1.0f)
				midiRxChannel.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case MMC_MIDI_RX_PORT:
			if (midiRxPort.getAlpha() == 1.0f)
				midiRxPort.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case MMC_MIDI_RX_DEVALL:
			mmcRxAll.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case MMC_MIDI_TX_PORT:
			if (midiTxPort.getAlpha() == 1.0f)
				midiTxPort.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
		repaint();
	}
};
