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
	//   Class: IgniteTransposeSettings
	////////////////////////////////////////////////
	IgniteTransposeSettings::IgniteTransposeSettings()
	{
		addAndMakeVisible(controlBtn);
		controlBtn.addListener(this);
		controlBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		controlBtn.setToggleable(true);
		controlBtn.sethoverImages("btn-toggle-midi-xpose-default-hover.png", "btn-toggle-midi-xpose-active-hover.png", "");

		addAndMakeVisible(latchBtn);
		latchBtn.addListener(this);
		latchBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		latchBtn.setToggleable(true);
		latchBtn.setDisableImage("btn-latch-mode-disabled.png");
		latchBtn.sethoverImages("btn-latch-mode-default-hover.png", "btn-latch-mode-active-hover.png", "");

		addAndMakeVisible(midiPorts);
		midiPorts.setSelected(0);
		midiPorts.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		midiPorts.setValueColour(Theme::Instance().getColour(customOrange));
		midiPorts.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });

		addAndMakeVisible(midiChannel);
		midiChannel.setDisplayTitle(true);
		midiChannel.setJustificationType(juce::Justification::centred);
		midiChannel.setTextColour(Theme::Instance().getColour(customOrange));
		midiChannel.setcustombounds(true, ui::Rectangle(0, 15, 328, 34), ui::Rectangle(0, 49, 328, 20));

		addAndMakeVisible(centerPitch);
		centerPitch.setDisplayTitle(true);
		centerPitch.setJustificationType(juce::Justification::centred);
		centerPitch.setTextColour(Theme::Instance().getColour(customOrange));
		centerPitch.setcustombounds(true, ui::Rectangle(0, 15, 328, 34), ui::Rectangle(0, 49, 328, 20));

		midiPorts.setValueFont(22);
		midiPorts.setJustification(Justification::centred);
		midiPorts.setValueColour(Theme::Instance().getColour(customOrange));
		midiChannel.setTextColour(Theme::Instance().getColour(customOrange));
		centerPitch.setTextColour(Theme::Instance().getColour(customOrange));

		controlBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		latchBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		transposeOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(transposeOptCtl);
		transposeOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		transposeOptCtl->addOptCtlListener(this);

		ctlBox2.items.add(FlexItem(midiChannel).withMargin(0).withFlex(1));
		ctlBox2.items.add(FlexItem(centerPitch).withMargin(0).withFlex(1));
		popupPtr = CommonPopUp::getCommonPopupInstance();

		midiPorts.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			transposeConfigDataUpdated = true;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlMidiPort, value);
		};

		midiChannel.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			transposeConfigDataUpdated = true;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlMidiChannel, value);
		};

		centerPitch.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			transposeConfigDataUpdated = true;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlCenterPitch, value);
		};

		midiPorts.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		midiChannel.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		centerPitch.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		controlButtonState(false);
	}

	IgniteTransposeSettings::~IgniteTransposeSettings()
	{
	}

	void IgniteTransposeSettings::getAssets()
	{
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-default.png"));
		imageHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-default-hover.png"));
	}

	void IgniteTransposeSettings::paint(juce::Graphics& g)
	{
		
		Image Draw;
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-default.png"));
		imageHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-default-hover.png"));

		if (transposeConfigDataUpdated & !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("MIDI Xpose Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("MIDI Xpose Configuration");

		g.setColour(ui::Theme::Instance().getColour((neutralBlack)));
		g.fillAll();

		Draw = midiPorts.getFocusState() ? imageHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 64, 328, 80 });

		Draw = midiChannel.getFocusState() ? imageHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 154, 328, 80  });

		Draw = centerPitch.getFocusState() ? imageHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 154, 328, 80});
	}

	void IgniteTransposeSettings::updateData()
	{
		std::vector<IgniteParamList> midiXposeParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlStatus;
		midiXposeParams.push_back(params);

		params.param = (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlLatch;
		midiXposeParams.push_back(params);

		params.param = (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlMidiPort;
		midiXposeParams.push_back(params);

		params.param = (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlMidiChannel;
		midiXposeParams.push_back(params);

		params.param = (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlCenterPitch;
		midiXposeParams.push_back(params);

		midiXposeParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, midiXposeParams);

		controlBtn.setToggleState(midiXposeParams[0].MsgValue.get< int8>(), dontSendNotification);
		latchBtn.setToggleState(midiXposeParams[1].MsgValue.get< int8>(), dontSendNotification);

		midiPorts.setSelected(midiXposeParams[2].MsgValue.get< int8>());
		midiChannel.setText(String(midiXposeParams[3].MsgValue.get< int8>()), dontSendNotification);
		centerPitch.setText(String(midiXposeParams[4].MsgValue.get< int8>()), dontSendNotification);
		controlButtonState(controlBtn.getToggleState());

		if (transposeConfigDataUpdated)
		{
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
		}
		else
		{
			enableControlButton(IgniteControlOptions::SAVE, false);
			enableControlButton(IgniteControlOptions::UNDO, false);
		}
	}

	void IgniteTransposeSettings::resized()
	{
		controlBtn.setBounds(10, 64, 328, 80);
		latchBtn.setBounds(348, 64, 328, 80);
		midiPorts.setBounds(686, 64, 328, 80);
		ctlBox2.performLayout(ui::Rectangle{ 10, 154, 664, 80 });
	}

	void IgniteTransposeSettings::controlButtonState(bool state)
	{
		latchBtn.setEnabled(state);
		if (state)
		{
			midiPorts.setAlpha((float)1.0);
			midiChannel.setAlpha((float)1.0);
			centerPitch.setAlpha((float)1.0);
			midiPorts.setInterceptsMouseClicks(true, true);
			midiChannel.setInterceptsMouseClicks(true, true);
			midiChannel.setInterceptsMouseClicks(true, true);
			centerPitch.setInterceptsMouseClicks(true, true);
		}
		else
		{
			midiPorts.setAlpha((float)0.2);
			midiChannel.setAlpha((float)0.2);
			centerPitch.setAlpha((float)0.2);
			midiPorts.setInterceptsMouseClicks(false, false);
			midiChannel.setInterceptsMouseClicks(false, false);
			centerPitch.setInterceptsMouseClicks(false, false);
		}
	}

	void IgniteTransposeSettings::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &controlBtn)
		{
			if (controlBtn.getToggleState())
			{
				controlButtonState(true);
			}
			else
			{
				controlButtonState(false);
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlStatus, controlBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &latchBtn)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlLatch, latchBtn.getToggleState());
		}

		enableControlButton(IgniteControlOptions::SAVE, true);
		enableControlButton(IgniteControlOptions::UNDO, true);
		transposeConfigDataUpdated = true;
	}

	void IgniteTransposeSettings::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			transposeConfigDataUpdated = false;
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
					popupPtr->setInfoText(String("Save MIDI Xpose Configuration edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, (paramId_t)SettingsTransposeControlCnfgParam::paramTransposeControlCnfgSave, 0);
							enableControlButton(IgniteControlOptions::SAVE, false);
							enableControlButton(IgniteControlOptions::UNDO, false);
							transposeConfigDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (transposeConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, (paramId_t)SettingsTransposeControlCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> midiXposeParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsTransposeControlCnfgParam::paramUndoListCmd;
					midiXposeParamList.push_back(params);
					midiXposeParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTransposeControlCnfg, midiXposeParamList);
					if (midiXposeParamList.size() == 1)
					{
						transposeConfigDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgniteTransposeSettings::isEditing()
	{
		int index = 0;

		midiPorts.IsEditing() ? index = 3 : 0;
		midiChannel.IsEditing() ? index = 4 : 0;
		centerPitch.IsEditing() ? index = 5 : 0;

		return index;

	}

	bool IgniteTransposeSettings::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int editItem = XposeMenuViewItemID::NO_FOCUS;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if (KeyFocusedItem == XposeMenuViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = XposeMenuViewItemID::XPOSE_CTL;
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
					KeyFocusedItem = (KeyFocusedItem + 1 >= XposeMenuViewItemID::FOCUS_MAX ? (XposeMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= XposeMenuViewItemID::NO_FOCUS ? (XposeMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
					break;
				case FrontPannelParam::paramRot_ROW:
					if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						KeyFocusedItem = (KeyFocusedItem + XPOSE_ROW_ITEMS >= XposeMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + XPOSE_ROW_ITEMS) == (XposeMenuViewItemID::FOCUS_MAX) ? (XposeMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + XPOSE_ROW_ITEMS);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
					{
						PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						KeyFocusedItem = (KeyFocusedItem - XPOSE_ROW_ITEMS <= XposeMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - XPOSE_ROW_ITEMS);
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

	void IgniteTransposeSettings::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		switch (XposeMenuView[KeyFocusedItem])
		{
		case XPOSE_CTL:
			controlBtn.FPKeyHandler(isFocuse, param, KeyValue);
			/*if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
			{
				buttonClicked(&controlBtn);
			}*/
			break;
		case LATCH_MODE:
			latchBtn.FPKeyHandler(isFocuse, param, KeyValue);
			if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
			{
				buttonClicked(&latchBtn);
			}
			break;
		case XPOSE_CHANNEL:
			if (midiChannel.getAlpha() == 1.0f)
				midiChannel.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case XPOSE_PORT:
			if (midiPorts.getAlpha() == 1.0f)
				midiPorts.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case CENTER_PITCH:
			if (centerPitch.getAlpha() == 1.0f)
				centerPitch.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
		repaint();
	}
};
