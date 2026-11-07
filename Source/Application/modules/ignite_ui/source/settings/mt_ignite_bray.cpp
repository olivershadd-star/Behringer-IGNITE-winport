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
	//   Class: IgniteBRaySettings
	////////////////////////////////////////////////
	IgniteBRaySettings::IgniteBRaySettings()
	{
		addAndMakeVisible(brayLable);
		brayLable.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		brayLable.setJustificationType(juce::Justification::centredLeft);

		addAndMakeVisible(controlLable);
		controlLable.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		controlLable.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(controlBtn);
		controlBtn.addListener(this);
		controlBtn.setToggleable(true);
		controlBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		controlBtn.sethoverImages("btn-bray-off-hover.png", "btn-bray-on-hover.png", "btn-bray-on-hover.png");

		addAndMakeVisible(ccBtn);
		ccBtn.addListener(this);
		ccBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		ccBtn.setToggleable(true);
		ccBtn.setDisableImage("toggle-cccontrol-disabled.png");
		ccBtn.sethoverImages("toggle-cccontrol-default-hover.png", "toggle-cccontrol-active-hover.png", "");

		addAndMakeVisible(afterTouchBtn);
		afterTouchBtn.addListener(this);
		afterTouchBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		afterTouchBtn.setToggleable(true);
		afterTouchBtn.setDisableImage("toggle-aftertouch-disabled.png");
		afterTouchBtn.sethoverImages("toggle-aftertouch-default-hover.png", "toggle-aftertouch-active-hover.png", "");

		addAndMakeVisible(pitchBendBtn);
		pitchBendBtn.addListener(this);
		pitchBendBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		pitchBendBtn.setToggleable(true);
		pitchBendBtn.setDisableImage("toggle-pitch-disabled.png");
		pitchBendBtn.sethoverImages("toggle-pitch-default-hover.png", "toggle-pitch-active-hover.png", "");

		addAndMakeVisible(veloCtlBtn);
		veloCtlBtn.addListener(this);
		veloCtlBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		veloCtlBtn.setToggleable(true);
		veloCtlBtn.setDisableImage("toggle-velocontrol-disabled.png");
		veloCtlBtn.sethoverImages("toggle-velocontrol-default-hover.png", "toggle-velocontrol-active-hover.png", "");

		ccBtn.setEnabled(false);
		afterTouchBtn.setEnabled(false);
		pitchBendBtn.setEnabled(false);
		veloCtlBtn.setEnabled(false);
		controlLable.setAlpha(0.4f);

		brayOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(brayOptCtl);
		brayOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		brayOptCtl->addOptCtlListener(this);

		addAndMakeVisible(ccList);
		ccList.setValueColour(Theme::Instance().getColour(customOrange));
		ccList.setComponentID("CCComp");
		ccList.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		ccList.setVisible(false);

		ccBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		afterTouchBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		pitchBendBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		veloCtlBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		ctlBox1.items.add(FlexItem(controlBtn).withMargin(0).withFlex(1));

		setSize(getWidth(), getHeight());

		popupPtr = CommonPopUp::getCommonPopupInstance();
		getAssets();
		ccList.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		ccList.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramBrayCcNum, value);
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			brayConfigDataUpdated = true;
		};
	}

	IgniteBRaySettings::~IgniteBRaySettings()
	{
	}

	void IgniteBRaySettings::getAssets()
	{
			imageControlDefault= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("assigned-control-bg-default.png"));
			imageCCcontrolDefault= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-cccontrol-default.png"));
			imageCCcontrolHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-cccontrol-default-hover.png"));
	}

	void IgniteBRaySettings::paint(juce::Graphics& g)
	{
		Image Draw;
		String Imagename;

		if (brayConfigDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("B-Ray Control and Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("B-Ray Control and Configuration");

		g.setColour(ui::Theme::Instance().getColour(neutralBlack));
		g.fillAll();

		g.drawImage(imageControlDefault, ui::Rectangle<float>{ 348, 64, 666, 162  });

		if (ccList.isVisible())
		{
			Draw = ccList.getFocusState() ? imageCCcontrolHover : imageCCcontrolDefault;
			g.drawImage(Draw, ui::Rectangle<float>{ 348, 236, 328, 80 });
		}
	}

	void IgniteBRaySettings::updateData()
	{
		std::vector<IgniteParamList> brayParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsBRayCnfgParam::paramBrayPowerStatus;
		brayParams.push_back(params);
		params.param = (paramId_t)SettingsBRayCnfgParam::paramBrayControlledParam;
		brayParams.push_back(params);
		params.param = (paramId_t)SettingsBRayCnfgParam::paramBrayCcNum;
		brayParams.push_back(params);

		brayParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, brayParams);
		controlBtn.setToggleState(brayParams[0].MsgValue.get< int8_t >(), dontSendNotification);
		controlBtn.getToggleState() ? controlBtn.setButtonText("B-Ray Control:on") : controlBtn.setButtonText("B-Ray Control:off");
		ccList.setSelected(brayParams[2].MsgValue.get< int8_t >());
		ccList.setVisible(false);

		if (brayParams[0].MsgValue.get< int8_t >())
		{
			ccBtn.setToggleState(false, dontSendNotification);
			afterTouchBtn.setToggleState(false, dontSendNotification);
			pitchBendBtn.setToggleState(false, dontSendNotification);
			veloCtlBtn.setToggleState(false, dontSendNotification);
			controlLable.setAlpha(1.0f);
			ccBtn.setEnabled(true);
			afterTouchBtn.setEnabled(true);
			pitchBendBtn.setEnabled(true);
			veloCtlBtn.setEnabled(true);

			int value = brayParams[1].MsgValue.get< int8_t >();
			switch (value)
			{
			case (int)BRayControllSetting::ccControl:
				ccBtn.setToggleState(true, dontSendNotification);
				ccList.setVisible(true);
				break;
			case (int)BRayControllSetting::afterTouchControl:
				afterTouchBtn.setToggleState(true, dontSendNotification);
				break;
			case (int)BRayControllSetting::pitchBendControl:
				pitchBendBtn.setToggleState(true, dontSendNotification);
				break;
			case (int)BRayControllSetting::velocityControl:
				veloCtlBtn.setToggleState(true, dontSendNotification);
				break;
			}
		}
		else
		{
			ccBtn.setEnabled(false);
			afterTouchBtn.setEnabled(false);
			pitchBendBtn.setEnabled(false);
			veloCtlBtn.setEnabled(false);
			controlLable.setAlpha(0.4f);
		}
	}

	void IgniteBRaySettings::resized()
	{
		ctlBox1.performLayout(ui::Rectangle{ 10, 64, 328,112 });
		controlLable.setBounds(348, 66, 666, 30);
		ccList.setBounds(348, 236, 328, 80);
		ccBtn.setBounds(357, 110, 320, 50);
		pitchBendBtn.setBounds(687, 110, 320, 50);
		afterTouchBtn.setBounds(357, 170, 320, 50);
		veloCtlBtn.setBounds(687, 170, 320, 50);
	}

	void IgniteBRaySettings::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		enableControlButton(IgniteControlOptions::SAVE, false);
		enableControlButton(IgniteControlOptions::UNDO, false);
		brayConfigDataUpdated = false;

		if (buttonThatWasClicked == &controlBtn)
		{
			KeyFocusedItem = BrayMenuViewItemID::BRAY_CTL;
			if (controlBtn.getToggleState())
			{
				controlBtn.setButtonText("B-Ray Control:On");
				ccBtn.setEnabled(true);
				afterTouchBtn.setEnabled(true);
				pitchBendBtn.setEnabled(true);
				veloCtlBtn.setEnabled(true);
				controlLable.setAlpha(1.0f);
				if (ccBtn.getToggleState())
					ccList.setVisible(true);
				else
					ccList.setVisible(false);
			}
			else
			{
				controlBtn.setButtonText("B-Ray Control:Off");
				ccBtn.setEnabled(false);
				afterTouchBtn.setEnabled(false);
				pitchBendBtn.setEnabled(false);
				veloCtlBtn.setEnabled(false);
				controlLable.setAlpha(0.4f);
				ccList.setVisible(false);
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramBrayPowerStatus, controlBtn.getToggleState());
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_BRAY, (controlBtn.getToggleState() ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF));
		}
		else if (buttonThatWasClicked == &ccBtn)
		{
			KeyFocusedItem = BrayMenuViewItemID::CC_CTL;
			if (controlBtn.getToggleState())
			{
				afterTouchBtn.setToggleState(false, dontSendNotification);
				pitchBendBtn.setToggleState(false, dontSendNotification);
				veloCtlBtn.setToggleState(false, dontSendNotification);
				ccList.setVisible(true);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramBrayControlledParam, (uint8_t)BRayControllSetting::ccControl * ccBtn.getToggleState());
			}
			brayConfigDataUpdated = true;
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
		}
		else if (buttonThatWasClicked == &afterTouchBtn)
		{
			KeyFocusedItem = BrayMenuViewItemID::AFTTOUCH_CTL;
			if (controlBtn.getToggleState())
			{
				ccBtn.setToggleState(false, dontSendNotification);
				pitchBendBtn.setToggleState(false, dontSendNotification);
				veloCtlBtn.setToggleState(false, dontSendNotification);
				ccList.setVisible(false);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramBrayControlledParam, (uint8_t)BRayControllSetting::afterTouchControl * afterTouchBtn.getToggleState());
			}
			brayConfigDataUpdated = true;
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
		}
		else if (buttonThatWasClicked == &pitchBendBtn)
		{
			KeyFocusedItem = BrayMenuViewItemID::PITCHBEND_CTL;
			if (controlBtn.getToggleState())
			{
				afterTouchBtn.setToggleState(false, dontSendNotification);
				ccBtn.setToggleState(false, dontSendNotification);
				veloCtlBtn.setToggleState(false, dontSendNotification);
				ccList.setVisible(false);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramBrayControlledParam, (uint8_t)BRayControllSetting::pitchBendControl * pitchBendBtn.getToggleState());
			}
			brayConfigDataUpdated = true;
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
		}
		else if (buttonThatWasClicked == &veloCtlBtn)
		{
			KeyFocusedItem = BrayMenuViewItemID::PITCHBEND_CTL;
			if (controlBtn.getToggleState())
			{
				afterTouchBtn.setToggleState(false, dontSendNotification);
				pitchBendBtn.setToggleState(false, dontSendNotification);
				ccBtn.setToggleState(false, dontSendNotification);
				ccList.setVisible(false);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramBrayControlledParam, (uint8_t)BRayControllSetting::velocityControl * veloCtlBtn.getToggleState());
			}
			brayConfigDataUpdated = true;
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
		}

	}

	void IgniteBRaySettings::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			brayConfigDataUpdated = false;
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
					popupPtr->setInfoText(String("Save B-Ray Configuration edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramBRayCnfgSave, 0);
							enableControlButton(IgniteControlOptions::SAVE, false);
							enableControlButton(IgniteControlOptions::UNDO, false);
							brayConfigDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (brayConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, (paramId_t)SettingsBRayCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> brayParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsBRayCnfgParam::paramUndoListCmd;
					brayParamList.push_back(params);
					brayParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsBRayCnfg, brayParamList);
					if (brayParamList.size() == 1)
					{
						brayConfigDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	void IgniteBRaySettings::handleCommandMessage(int id)
	{
		if(id==1)
			AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
	}

	bool IgniteBRaySettings::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = BrayMenuViewItemID::NO_FOCUS;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if (KeyFocusedItem == BrayMenuViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = BrayMenuViewItemID::BRAY_CTL;

			if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
			{
				this->postCommandMessage(1);
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
					PannelSendKey(false, param, KeyValue);
					KeyFocusedItem = EditItem;
				}
				setfocus = true;
			}
			else
			{
				PannelSendKey(false, param, KeyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					KeyFocusedItem = (KeyFocusedItem + 1 >= BrayMenuViewItemID::FOCUS_MAX ? (BrayMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= BrayMenuViewItemID::NO_FOCUS ? (BrayMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					this->postCommandMessage(1);
					break;
				case FrontPannelParam::paramRot_ROW:
					if (KeyValue == ROTARY_RIGHT)
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						KeyFocusedItem = (KeyFocusedItem + BRAY_ROW_ITEMS >= BrayMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + BRAY_ROW_ITEMS) == (BrayMenuViewItemID::FOCUS_MAX) ? (BrayMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + BRAY_ROW_ITEMS);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else if (KeyValue == ROTARY_LEFT)
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						KeyFocusedItem = (KeyFocusedItem - BRAY_ROW_ITEMS <= BrayMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - BRAY_ROW_ITEMS);
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

	void IgniteBRaySettings::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		switch (BrayMenuView[KeyFocusedItem])
		{
		case BRAY_CTL:
			controlBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case CC_CTL:
			ccBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case PITCHBEND_CTL:
			pitchBendBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case AFTTOUCH_CTL:
			afterTouchBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case VELOCITY_CTL:
			veloCtlBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case CC_LIST:
			ccList.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
		repaint();
	}

	int IgniteBRaySettings::isEditing()
	{
		int index = 0;
		ccList.IsEditing() ? index = 6 : 0;
		return index;

	}
};
