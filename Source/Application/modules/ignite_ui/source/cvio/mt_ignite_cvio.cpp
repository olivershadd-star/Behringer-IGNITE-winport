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
	//   Class: Ignite CVIO Config
	////////////////////////////////////////////////
	IgniteCvio::IgniteCvio()
	{
		cvObject = IgniteCvConfig::GetAppCvInstance();
		addChildComponent(cvObject);
		cvObject->setBounds(10, 66, 1004, 400);
		cvObject->setVisible(false);

		gateObject = IgniteGateConfig::GetAppGateInstance();
		addChildComponent(gateObject);
		gateObject->setBounds(10, 132, 1004, 600);
		gateObject->setVisible(false);

		cvioOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(cvioOptCtl);
		cvioOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		cvioOptCtl->addOptCtlListener(this);
		cvbtn.makeVisibleAndAddListner(this);
		gatebtn.makeVisibleAndAddListner(this);
		cvbtn.setBounds(10, 66, 500, 56);
		gatebtn.setBounds(515, 66, 500, 56);
		cvbtn.setToggleState(true, sendNotification);
		cvbtn.sethoverImages("btn-cvoutput-default-hover.png", "btn-cvoutput-active-hover.png", "");
		gatebtn.sethoverImages("btn-gateport-default-hover.png", "btn-gateport-active-hover.png", "");
		gatebtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		cvbtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		popupPtr = CommonPopUp::getCommonPopupInstance();
		AppOptions::GetOptionsInstance()->changebtnstate(ui::IgniteControlOptions::CV_SONG, true);
	}

	IgniteCvio::~IgniteCvio()
	{
	}

	void IgniteCvio::paint(juce::Graphics& g)
	{
		if (cvioConfigDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("CV and Gate Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("CV and Gate Configuration");
	}

	void IgniteCvio::resized()
	{
		MenuMode::GetMenuModeInstance()->setJustification(Justification::centred);
	}

	void IgniteCvio::setDefaultOutputPort()
	{
		cvObject->updateCvOutputPort();
		gateObject->updateGateOutputPort();
	}

	void  IgniteCvio::refreshUI()
	{
		/*(AppOptions::GetOptionsInstance()->getBtnState(IgniteControlOptions::CV_SONG)) ?
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::SettingDataLocation, 1) :
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::SettingDataLocation, 0);*/
		cvObject->updateCvData();
		gateObject->updateGateData();
		for (int i = 0; i < 8; i++)
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + i), fpLEDPattern::EN_RGB_LED_LBLUE);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam((uint8_t)(FrontPannelParam::paramKey_ROTARYROW)), fpLEDPattern::EN_LED_PATT_ON);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam((uint8_t)(FrontPannelParam::paramKey_ROTARYBAR)), fpLEDPattern::EN_LED_PATT_ON);
	}

	void IgniteCvio::enableControlButton(IgniteControlOptions::eKey key, bool state)
	{
		cvioOptCtl->enableKey(key, state);
	}


	void IgniteCvio::saveCvConfigSettings(int8_t SaveLocation)
	{
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramActiveCVPort, active_port);
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramSaveCvioSetting, SaveLocation);
		cvioOptCtl->enableKey(IgniteControlOptions::SAVE, false);
		cvioOptCtl->enableKey(IgniteControlOptions::UNDO, false);
		cvioConfigDataUpdated = false;
	}

	void IgniteCvio::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			cvioConfigDataUpdated = false;
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
					auto saveMsg = "";
					(AppOptions::GetOptionsInstance()->getBtnState(IgniteControlOptions::CV_SONG)) ? (saveMsg = "Save Active Song Config edits ?") :
						(saveMsg = "Save Deafult Config edits ?");
					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String(saveMsg));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
						{
							if (r == 1)
							{
								(AppOptions::GetOptionsInstance()->getBtnState(IgniteControlOptions::CV_SONG)) ? saveCvConfigSettings(1) : saveCvConfigSettings(0);
							}
							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);
							(AppOptions::GetOptionsInstance()->getBtnState(IgniteControlOptions::CV_SONG)) ?
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::SettingDataLocation, 1) :
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::SettingDataLocation, 0);
						};
				}
			}

			else if (option == IgniteControlOptions::UNDO)
			{
				if (cvioConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> cvParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsCvioCnfgParam::paramUndoListCmd;
					cvParamList.push_back(params);
					cvParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, cvParamList);
					if (cvParamList.size() == 1)
					{
						cvioConfigDataUpdated = false;
						cvioOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						cvioOptCtl->enableKey(IgniteControlOptions::UNDO, false);
					}
					refreshUI();

				}
			}
			else if (option == IgniteControlOptions::CV_GLOBAL)
			{
				AppOptions::GetOptionsInstance()->changebtnstate(ui::IgniteControlOptions::CV_SONG, false);
				saveCvConfigSettings(1);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::SettingDataLocation, 0);
				refreshUI();
			}
			else if (option == IgniteControlOptions::CV_SONG)
			{
				AppOptions::GetOptionsInstance()->changebtnstate(ui::IgniteControlOptions::CV_GLOBAL, false);
				saveCvConfigSettings(0);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::SettingDataLocation, 1);
				refreshUI();
			}
		}
	}

	void IgniteCvio::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &cvbtn)
		{
			if (cvbtn.getToggleState())
			{
				gatebtn.setToggleState(false, dontSendNotification);
				gateObject->setVisible(false);
				cvObject->setVisible(true);
			}
		}
		else if (buttonThatWasClicked == &gatebtn)
		{
			if (gatebtn.getToggleState())
			{
				cvbtn.setToggleState(false, dontSendNotification);
				gateObject->setVisible(true);
				cvObject->setVisible(false);
			}
		}
	}

	bool IgniteCvio::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_RELEASE || (FrontPannelParam)param == FrontPannelParam::paramKey_FILTER || (FrontPannelParam)param == FrontPannelParam::paramKey_RESONANCE
			|| (FrontPannelParam)param == FrontPannelParam::paramKey_VOLUME || (FrontPannelParam)param == FrontPannelParam::paramKey_REVERBE || (FrontPannelParam)param == FrontPannelParam::paramKey_CHORUS)
		{
			cvObject->PannelKeyHandler(param, KeyValue);
			return true;
		}

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
		{
			PannelSendKey(false, param, KeyValue);

			if (option_handler_focus == CVIO_DETAIL)
			{
				if (cvbtn.getToggleState())
				{
					cvObject->PannelSendKey(false, param, KeyValue);
				}
				else if (gatebtn.getToggleState())
				{
					gateObject->PannelSendKey(false, param, KeyValue);
				}
				option_handler_focus = CVIO_OPTION;
			}
			else
			{
				if (cvbtn.getToggleState())
				{
					cvObject->PannelSendKey(true, param, KeyValue);
				}
				else if (gatebtn.getToggleState())
				{
					gateObject->PannelSendKey(true, param, KeyValue);
				}

				option_handler_focus = CVIO_DETAIL;
			}
			PannelSendKey(true, param, KeyValue);
			return true;
		}

		if (option_handler_focus == CVIO_DETAIL)
		{
			if (KeyFocusedItem == CVIOItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				KeyFocusedItem = CVIOItemID::CV_PORT;
			}
			else
			{
				if (cvbtn.getToggleState())
				{
					cvObject->PannelKeyHandler(param, KeyValue);
					if (cvObject->KeyFocusedItem == 0 && (FrontPannelParam)param == FrontPannelParam::paramKey_RMOVERIGHT)
					{
						cvObject->PannelSendKey(false, param, KeyValue);
						KeyFocusedItem--;
						PannelSendKey(true, param, KeyValue);
					}
					return true;
				}
				else if (gatebtn.getToggleState())
				{
					gateObject->PannelKeyHandler(param, KeyValue);
					if (gateObject->KeyFocusedItem == 0 && (FrontPannelParam)param == FrontPannelParam::paramKey_RMOVERIGHT)
					{
						gateObject->PannelSendKey(false, param, KeyValue);
						KeyFocusedItem--;
						PannelSendKey(true, param, KeyValue);
					}
					return true;
				}

			}

			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				KeyFocusedItem = (KeyFocusedItem + 1 >= CVIOItemID::FOCUS_MAX ? (CVIOItemID::FOCUS_MAX) : KeyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				KeyFocusedItem = (KeyFocusedItem - 1 <= CVIOItemID::NO_FOCUS ? (CVIOItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
				break;
			}
		}
		else
		{
			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				OptFocusedItem = (OptFocusedItem + 1 >= MIDIOptionsViewItemID::OP_FOCUS_MAX ? (MIDIOptionsViewItemID::OP_FOCUS_MAX) : OptFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				OptFocusedItem = (OptFocusedItem - 1 <= MIDIOptionsViewItemID::OP_NO_FOCUS ? (MIDIOptionsViewItemID::OP_NO_FOCUS + 1) : OptFocusedItem - 1);
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
		return true;
	}


	void IgniteCvio::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		bool state = false;
		if (option_handler_focus == CVIO_DETAIL)
		{
			switch (CVIO_Config[KeyFocusedItem])
			{
			case CV_PORT:
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					cvbtn.setToggleState(true, sendNotification);
				else
					cvbtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case GATE_PORT:
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					gatebtn.setToggleState(true, sendNotification);
				else
					gatebtn.FPKeyHandler(isFocuse, param, 0);
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
			case OP_UNDO:
				state = cvioOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			case OP_DEFULT:
				state = cvioOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::CV_GLOBAL, isFocuse, param, KeyValue);
				break;
			case OP_ACTIVE_SONG:
				state = cvioOptCtl->PannelKeyHandler(ui::IgniteControlOptions::CV_SONG, isFocuse, param, KeyValue);
				break;
			}
			if (state == false)
			{
				OptFocusedItem++;
				if (OptFocusedItem == OP_FOCUS_MAX)
					OptFocusedItem = OP_UNDO;
				PannelSendKey(isFocuse, param, KeyValue);
			}
		}
	}

	IgniteCvConfigContainer::IgniteCvConfigContainer()
		:containerOffset(0)
	{

	}

	IgniteCvConfigContainer::~IgniteCvConfigContainer()
	{

	}

	void IgniteCvConfigContainer::addChildComp(juce::Component* pComp)
	{
		addAndMakeVisible(pComp);
		compList.add(pComp);

	}

	void IgniteCvConfigContainer::setOffset(int offset)
	{
		containerOffset = offset;
		resized();
	}

	void IgniteCvConfigContainer::resized()
	{
		if (compList.size() < 5)
		{
			return;
		}
		const int kiGap = 10;
		int iX = kiGap;

		const int kiCompWidth = 194;
		const int kiCompHeight = 80;
		containerOffset = juce::jlimit(0, 378, containerOffset);
		const int kiStartIndex = juce::jlimit(0, 3, containerOffset / 122);
		for (auto i = 0; i < compList.size(); ++i)
		{
			compList[i]->setBounds(iX + containerOffset, 0, 0, 0);
		}
		for (auto i = 0; i < 5; ++i)
		{
			compList[kiStartIndex + i]->setBounds(iX + containerOffset, 0, kiCompWidth, kiCompHeight);
			iX += kiCompWidth + 4;
		}
	}

	////////////////////////////////////////////////
	//   Class: Ignite CV Config
	////////////////////////////////////////////////
	IgniteCvConfig::IgniteCvConfig()
	{
		cvConfigLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		cvConfigLable.setJustificationType(juce::Justification::centredLeft);
		cvConfigLable.setEditable(false, false, false);
		cvConfigLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		cvConfigLable.setColour(juce::Label::outlineColourId, Colours::white);
		cvConfigLable.makeVisible(this);

		/*addAndMakeVisible(moveLeft);
		moveLeft.addListener(this);
		moveLeft.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		addAndMakeVisible(moveRight);
		moveRight.addListener(this);
		moveRight.setLookAndFeel(ImageButtonLookandFeel::getLnf());*/

		addAndMakeVisible(cvPort1);
		cvPort1.addListener(this);

		addAndMakeVisible(cvPort2);
		cvPort2.addListener(this);

		addAndMakeVisible(cvPort3);
		cvPort3.addListener(this);

		addAndMakeVisible(cvPort4);
		cvPort4.addListener(this);

		addAndMakeVisible(cvPort5);
		cvPort5.addListener(this);

		addAndMakeVisible(cvPort6);
		cvPort6.addListener(this);

		addAndMakeVisible(cvPort7);
		cvPort7.addListener(this);

		addAndMakeVisible(cvPort8);
		cvPort8.addListener(this);

		/*cvChannel.setDisplayTitle(true);
		cvChannel.setJustificationType(juce::Justification::centred);*/

		cvNote.setDisplayTitle(true);
		cvNote.setJustificationType(juce::Justification::centred);

		//cvCCList.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		cvNoteRangeStart.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		cvNoteRangeEnd.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);

		cvVelocity.setDisplayTitle(true);
		cvVelocity.setJustificationType(juce::Justification::centred);

		cvCCCtrl.setDisplayTitle(true);
		cvCCCtrl.setJustificationType(juce::Justification::centred);

		cvPitchBend.setDisplayTitle(true);
		cvPitchBend.setJustificationType(juce::Justification::centred);

		cvLaw.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);

		//cvSlide.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);

		/*slideTime.setDisplayTitle(true);
		slideTime.setJustificationType(juce::Justification::centred);*/

		//cvGate.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		CVNoteSelection.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);

		cvOutput.setDisplayTitle(true);
		cvOutput.setJustificationType(juce::Justification::centred);

		//cvChannel.drawBorder(true);
		cvLaw.drawBorder(true);
		//cvGate.drawBorder(true);
		//cvCCList.drawBorder(true);
		//cvSlide.drawBorder(true);
		//slideTime.drawBorder(true);
		cvNoteRangeStart.drawBorder(true);
		cvNoteRangeEnd.drawBorder(true);
		CVNoteSelection.drawBorder(true);
		cvOutput.drawBorder(true);

		addAndMakeVisible(viewport);
		viewport.setViewedComponent(&Container, true);
		viewport.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::never);
		viewport.addListener(this);

		for (int i = 0; i < NO_OF_ENVOLOPE_SLIDER; i++)
		{
			String a;
			slider[i].setTitle("------");
			addAndMakeVisible(slider[i]);
			slider[i].showTitleAndValue(true, Slider::TextBoxBelow, Justification::centred);
			slider[i].setDisplayProportions(.6f, .2f, .2f);
			slider[i].addMouseListener(this, true);
			slider[i].addListener(this);
			rotarySlider.items.add(FlexItem(slider[i]).withMargin(1).withFlex(1));
			slider[i].setLookAndFeel(CommonRotaryCv_gate::getLnf());
			slider[i].setValueColour(ui::Theme::Instance().getColour(neutralWhite));
			slider[i].setTitleColour(ui::Theme::Instance().getColour(neutralWhite));
			slider[i].setKnobTitle(a.charToString('A' + i), true);
			slider[i].setRange(0, 100, 0);
			slider[i].setNumDecimalPlacesToDisplay(0);
			slider[i].setAlpha(0.5f);

		}

		slider[0].setTitle("Attack");
		slider[1].setTitle("Decay");
		slider[2].setTitle("Sustain");
		slider[3].setTitle("Release");
		slider[4].setTitle("Depth");
		//slider[5].setTitle("Velocity");

		showEnvolopSliders(false);

		cvConfigPort.items.add(FlexItem(cvPort1).withMargin({ 0,5,0,0 }).withFlex(1));
		cvConfigPort.items.add(FlexItem(cvPort2).withMargin({ 0,5,0,0 }).withFlex(1));
		cvConfigPort.items.add(FlexItem(cvPort3).withMargin({ 0,5,0,0 }).withFlex(1));
		cvConfigPort.items.add(FlexItem(cvPort4).withMargin({ 0,5,0,0 }).withFlex(1));
		cvConfigPort.items.add(FlexItem(cvPort5).withMargin({ 0,5,0,0 }).withFlex(1));
		cvConfigPort.items.add(FlexItem(cvPort6).withMargin({ 0,5,0,0 }).withFlex(1));
		cvConfigPort.items.add(FlexItem(cvPort7).withMargin({ 0,5,0,0 }).withFlex(1));
		cvConfigPort.items.add(FlexItem(cvPort8).withMargin({ 0,5,0,0 }).withFlex(1));

		//Container.addChildComp(&cvChannel);
		Container.addChildComp(&cvLaw);
		//Container.addChildComp(&cvGate);
		//Container.addChildComp(&cvCCList);
		//Container.addChildComp(&cvSlide);
		//Container.addChildComp(&slideTime);
		Container.addChildComp(&cvNoteRangeStart);
		Container.addChildComp(&cvNoteRangeEnd);
		Container.addChildComp(&CVNoteSelection);
		Container.addChildComp(&cvOutput);

		cvPort1.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort2.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort3.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort4.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort5.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort6.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort7.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort8.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		//cvChannel.setTextColour(Theme::Instance().getColour(customOrange));
		cvLaw.setValueColour(Theme::Instance().getColour(customOrange));
		//cvGate.setValueColour(Theme::Instance().getColour(customOrange));
		//cvCCList.setValueColour(Theme::Instance().getColour(customOrange));
		//cvSlide.setValueColour(Theme::Instance().getColour(customOrange));
		//slideTime.setTextColour(Theme::Instance().getColour(customOrange));
		cvNoteRangeStart.setValueColour(Theme::Instance().getColour(customOrange));
		cvNoteRangeEnd.setValueColour(Theme::Instance().getColour(customOrange));
		cvNote.setTextColour(Theme::Instance().getColour(customOrange));
		cvVelocity.setTextColour(Theme::Instance().getColour(customOrange));
		cvCCCtrl.setTextColour(Theme::Instance().getColour(customOrange));
		cvPitchBend.setTextColour(Theme::Instance().getColour(customOrange));
		CVNoteSelection.setValueColour(Theme::Instance().getColour(customOrange));
		cvOutput.setTextColour(Theme::Instance().getColour(customOrange));

		//cvCCList.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		cvNoteRangeStart.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		cvNoteRangeEnd.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		cvLaw.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,320 });
		//cvSlide.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,320 });
		//cvGate.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,290 });
		CVNoteSelection.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,320 });
		cvNoteRangeEnd.setEditable(false);
		cvNoteRangeEnd.setEnabled(false);
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramActiveCVPort, 0);
		getAssets();
		/*moveLeft.onClick = [this]()
		{
			moveLeft.setToggleState(false, dontSendNotification);
			moveViewPortHorizontaly(MoveDirection::MOVE_LEFT);
		};

		moveRight.onClick = [this]()
		{
			moveRight.setToggleState(false, dontSendNotification);
			moveViewPortHorizontaly(MoveDirection::MOVE_RIGHT);
		};*/

		cvLaw.onSelectionChanged = [this](int value, const juce::String&)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVLaw, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
				if (value == 2)
				{
					showEnvolopSliders(true);
				}
				else
				{
					showEnvolopSliders(false);
				}
			};

		CVNoteSelection.onSelectionChanged = [this](int value, const juce::String&)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCvNoteType, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		/*cvGate.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVGateType, value);
			cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
			cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
			cvioComp->cvioConfigDataUpdated = true;
		};*/

		/*cvCCList.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCcNum, value);
			cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
			cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
			cvioComp->cvioConfigDataUpdated = true;
		};*/

		/*cvSlide.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVSlideType, value);
			cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
			cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
			cvioComp->cvioConfigDataUpdated = true;
		};*/

		cvNoteRangeStart.onSelectionChanged = [this](int value, const juce::String&)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				//CVControl::getCVInterface()->setBaseNote(value);
				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVNoteRangeStart, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
				updateCvNoteEnd(value);
			};

		/*cvNoteRangeEnd.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVNoteRangeEnd, value);
			cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
			cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
			cvioComp->cvioConfigDataUpdated = true;
		};*/

		/*cvChannel.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVChannelNumber, value);
			cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
			cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
			cvioComp->cvioConfigDataUpdated = true;
		};*/

		cvNote.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				updateValuesRange();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVNotePercent, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		cvVelocity.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				updateValuesRange();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVVelocityPercent, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		cvCCCtrl.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				updateValuesRange();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCcPercent, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		cvPitchBend.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVPitchBend, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		/*slideTime.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVSlideTime, value);
			cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
			cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
			cvioComp->cvioConfigDataUpdated = true;
		};*/

		cvOutput.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				updateCvNoteEnd(cvNoteRangeStart.getSelectedIndex());
				//CVControl::getCVInterface()->setMaxCVOutput(value);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVVoltage, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		//cvChannel.setcustombounds(true, ui::Rectangle<int>{48, 3, 35, 60}, ui::Rectangle<int>{40, 35, 50, 50});
		//slideTime.setcustombounds(true, ui::Rectangle<int>{46, 3, 35, 60}, ui::Rectangle<int>{48, 35, 30, 50});
		cvOutput.setcustombounds(true, ui::Rectangle<int>{46, 3, 35, 60}, ui::Rectangle<int>{35, 35, 80, 50});
		cvLaw.setInterceptsMouseClicks(false, false);//we not supporting in beta release
		/*cvChannel.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		cvLaw.onFocusChanged = [this](bool a)
			{
				repaint();
			};

		/*cvGate.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		/*cvCCList.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		/*cvSlide.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		/*slideTime.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		cvNoteRangeStart.onFocusChanged = [this](bool a)
			{
				repaint();
			};

		/*cvNoteRangeEnd.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		cvNote.onFocusChanged = [this](bool a)
			{
				repaint();
			};

		cvVelocity.onFocusChanged = [this](bool a)
			{
				repaint();
			};
		cvCCCtrl.onFocusChanged = [this](bool a)
			{
				repaint();
			};
		cvPitchBend.onFocusChanged = [this](bool a)
			{
				repaint();
			};
		CVNoteSelection.onFocusChanged = [this](bool a)
			{
				repaint();
			};
		cvOutput.onFocusChanged = [this](bool a)
			{
				repaint();
			};
	}

	IgniteCvConfig::~IgniteCvConfig()
	{
	}

	void IgniteCvConfig::updateCvNoteEnd(int baseNote)
	{
		int endNote = (int)(baseNote + (cvOutput.getValue() * 12));

		if (endNote > 127)
			endNote = 127;

		cvNoteRangeEnd.setSelected(endNote);
	}

	void IgniteCvConfig::moveViewPortHorizontaly(int direction)
	{
		auto currentXPos = viewport.getViewPositionX();
		auto newXPos = currentXPos;
		auto offsetXPos = 122 + 4;
		if (direction == MoveDirection::MOVE_LEFT)
		{
			newXPos -= offsetXPos;
			newXPos = juce::jmax<int>(0, newXPos);
		}
		else if (direction == MoveDirection::MOVE_RIGHT)
		{
			newXPos += offsetXPos;
			newXPos = juce::jmin<int>(Container.getWidth() - viewport.getWidth(), newXPos);
		}

		viewport.setViewPosition((int)newXPos, viewport.getY());
		Container.setOffset(newXPos);
	}

	void IgniteCvConfig::updateValuesRange()
	{
		auto valueDelta = 100 - (cvVelocity.getValue() + cvCCCtrl.getValue() + cvNote.getValue());

		cvNote.setAlpha(1.0f);
		cvVelocity.setInterceptsMouseClicks(true, false);
		cvVelocity.setAlpha(1.0f);
		cvCCCtrl.setInterceptsMouseClicks(true, false);
		cvCCCtrl.setAlpha(1.0f);

		if (!cvNote.getValue() && (valueDelta <= 0))
		{
			cvNote.setInterceptsMouseClicks(false, false);
			cvNote.setAlpha(0.5f);
		}
		else
			cvNote.setValueBounds(0, cvNote.getValue() + valueDelta, cvNote.getValue(), 1);

		if (!cvVelocity.getValue() && (valueDelta <= 0))
		{
			cvVelocity.setInterceptsMouseClicks(false, false);
			cvVelocity.setAlpha(0.5f);
		}
		else
			cvVelocity.setValueBounds(0, cvVelocity.getValue() + valueDelta, cvVelocity.getValue(), 1);

		if (!cvCCCtrl.getValue() && (valueDelta <= 0))
		{
			cvCCCtrl.setInterceptsMouseClicks(false, false);
			cvCCCtrl.setAlpha(0.5f);
		}
		else
			cvCCCtrl.setValueBounds(0, cvCCCtrl.getValue() + valueDelta, cvCCCtrl.getValue(), 1);
	}

	void IgniteCvConfig::updateAccidentals(bool state)
	{
		if (state)
		{
			cvNoteRangeStart.updateListOptions(mt::Ignite::midiNoteNamesFlats);
			cvNoteRangeEnd.updateListOptions(mt::Ignite::midiNoteNamesFlats);
		}
		else
		{
			cvNoteRangeStart.updateListOptions(mt::Ignite::midiNoteNamesSharps);
			cvNoteRangeEnd.updateListOptions(mt::Ignite::midiNoteNamesSharps);
		}
	}

	void IgniteCvConfig::updateCvData()
	{
		std::vector<IgniteParamList> cvParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVLaw;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVGateType;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCcNum;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVSlideType;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVNoteRangeStart;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVNoteRangeEnd;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVChannelNumber;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVNotePercent;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVVelocityPercent;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCcPercent;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVPitchBend;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVSlideTime;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCVVoltage;
		cvParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramCvNoteType;
		cvParams.push_back(params);
		cvParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, cvParams);

		for (auto& param_id : cvParams)
		{
			switch (param_id.param)
			{
			case (paramId_t)SettingsCvioCnfgParam::paramCVLaw:
				cvLaw.setSelected(param_id.MsgValue.get< int8_t >());
				(param_id.MsgValue.get< int8_t >() == 2) ? showEnvolopSliders(true) : showEnvolopSliders(false);
				break;
				/*case (paramId_t)SettingsCvioCnfgParam::paramCVGateType:
					cvGate.setSelected(param_id.MsgValue.get< int8_t >());
					break;*/
					/*case (paramId_t)SettingsCvioCnfgParam::paramCVCcNum:
						cvCCList.setSelected(param_id.MsgValue.get< int8_t >());
						break;*/
						/*case (paramId_t)SettingsCvioCnfgParam::paramCVSlideType:
							cvSlide.setSelected(param_id.MsgValue.get< int8_t >());
							break;*/
			case (paramId_t)SettingsCvioCnfgParam::paramCVNoteRangeStart:
				cvNoteRangeStart.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			/*case (paramId_t)SettingsCvioCnfgParam::paramCVNoteRangeEnd:
				cvNoteRangeEnd.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsCvioCnfgParam::paramCVNotePercent:
				cvNote.setText(String(param_id.MsgValue.get< int8_t >()), dontSendNotification);
				cvNote.setValue(param_id.MsgValue.get< int8_t >());
				break;*/
			case (paramId_t)SettingsCvioCnfgParam::paramCVVelocityPercent:
				cvVelocity.setText(String(param_id.MsgValue.get< int8_t >()), dontSendNotification);
				cvVelocity.setValue(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsCvioCnfgParam::paramCVCcPercent:
				cvCCCtrl.setText(String(param_id.MsgValue.get< int8_t >()), dontSendNotification);
				cvCCCtrl.setValue(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsCvioCnfgParam::paramCVPitchBend:
				cvPitchBend.setText(String(param_id.MsgValue.get< int16_t >()), dontSendNotification);
				break;
				/*case (paramId_t)SettingsCvioCnfgParam::paramCVSlideTime:
					slideTime.setText(String(param_id.MsgValue.get< int32_t >()), dontSendNotification);
					break;*/
			case (paramId_t)SettingsCvioCnfgParam::paramCVVoltage:
				cvOutput.setText(String(param_id.MsgValue.get< int8_t >()), dontSendNotification);
				break;
			case (paramId_t)SettingsCvioCnfgParam::paramCvNoteType:
				CVNoteSelection.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			}
		}
		updateValuesRange();
		for (int i = 0; i < NO_OF_ENVOLOPE_SLIDER; i++)
		{
			slider[i].setValue(getSiderData((EnvlopType)i), dontSendNotification);
		}
		updateCvNoteEnd(cvNoteRangeStart.getSelectedIndex());
	}
	void IgniteCvConfig::getAssets()
	{
		imageGateportBg = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("gateport-bg-container.png"));
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-default.png"));
		imageDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-default-hover.png"));
		imageActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-active.png"));
		imageActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-active-hover.png"));
	}

	void IgniteCvConfig::paint(juce::Graphics& g)
	{
		g.drawImage(imageGateportBg, ui::Rectangle<float>{0, 64, 1004, 74});
		Image Draw;

		Draw = (cvPort1.getToggleState() ? ((cvPort1.isMouseOver() || cvPort1.isFocused) ? imageActiveHover : imageActive) : ((cvPort1.isMouseOver() || cvPort1.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{215, 79, 94, 44});

		Draw = (cvPort2.getToggleState() ? ((cvPort2.isMouseOver() || cvPort2.isFocused) ? imageActiveHover : imageActive) : ((cvPort2.isMouseOver() || cvPort2.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{314, 79, 94, 44});

		Draw = (cvPort3.getToggleState() ? ((cvPort3.isMouseOver() || cvPort3.isFocused) ? imageActiveHover : imageActive) : ((cvPort3.isMouseOver() || cvPort3.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{413, 79, 94, 44});

		Draw = (cvPort4.getToggleState() ? ((cvPort4.isMouseOver() || cvPort4.isFocused) ? imageActiveHover : imageActive) : ((cvPort4.isMouseOver() || cvPort4.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{512, 79, 94, 44});

		Draw = (cvPort5.getToggleState() ? ((cvPort5.isMouseOver() || cvPort5.isFocused) ? imageActiveHover : imageActive) : ((cvPort5.isMouseOver() || cvPort5.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{611, 79, 94, 44});

		Draw = (cvPort6.getToggleState() ? ((cvPort6.isMouseOver() || cvPort6.isFocused) ? imageActiveHover : imageActive) : ((cvPort6.isMouseOver() || cvPort6.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{710, 79, 94, 44});

		Draw = (cvPort7.getToggleState() ? ((cvPort7.isMouseOver() || cvPort7.isFocused) ? imageActiveHover : imageActive) : ((cvPort7.isMouseOver() || cvPort7.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{809, 79, 94, 44});

		Draw = (cvPort8.getToggleState() ? ((cvPort8.isMouseOver() || cvPort8.isFocused) ? imageActiveHover : imageActive) : ((cvPort8.isMouseOver() || cvPort8.isFocused) ? imageDefaultHover : imageDefault));
		g.drawImage(Draw, ui::Rectangle<float>{908, 79, 94, 44});

	}

	void IgniteCvConfig::resized()
	{
		cvConfigLable.setBounds(0, 79, 200, 44);
		cvConfigPort.performLayout(ui::Rectangle<float>{215, 79, 792, 44});
		Container.setSize(1024, 80);
		viewport.setBounds(0, 146, 1024, 80);
		/*moveLeft.setBounds(0, 146, 50, 80);
		moveRight.setBounds(954, 146, 50, 80);*/

		rotarySlider.performLayout(ui::Rectangle<float>{0, 230, 1004, 170});
	}

	void IgniteCvConfig::updateCvOutputPort()
	{
		cvPort1.setToggleState(true, dontSendNotification);
	}

	void IgniteCvConfig::setCvPortButtonToggleState(int portNumber)
	{
		cvPort1.setToggleState(false, dontSendNotification);
		cvPort2.setToggleState(false, dontSendNotification);
		cvPort3.setToggleState(false, dontSendNotification);
		cvPort4.setToggleState(false, dontSendNotification);
		cvPort5.setToggleState(false, dontSendNotification);
		cvPort6.setToggleState(false, dontSendNotification);
		cvPort7.setToggleState(false, dontSendNotification);
		cvPort8.setToggleState(false, dontSendNotification);

		switch (portNumber)
		{
		case 1:
			cvPort1.setToggleState(true, dontSendNotification);
			break;
		case 2:
			cvPort2.setToggleState(true, dontSendNotification);
			break;
		case 3:
			cvPort3.setToggleState(true, dontSendNotification);
			break;
		case 4:
			cvPort4.setToggleState(true, dontSendNotification);
			break;
		case 5:
			cvPort5.setToggleState(true, dontSendNotification);
			break;
		case 6:
			cvPort6.setToggleState(true, dontSendNotification);
			break;
		case 7:
			cvPort7.setToggleState(true, dontSendNotification);
			break;
		case 8:
			cvPort8.setToggleState(true, dontSendNotification);
			break;
		}
	}

	void IgniteCvConfig::updateCvUI(uint8_t selectedPort)
	{
		setCvPortButtonToggleState(selectedPort);
		IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramActiveCVPort, selectedPort - 1);
		cvioComp->setActivePort(selectedPort - 1);
		updateCvData();
	}

	void IgniteCvConfig::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &cvPort1)
		{
			updateCvUI(1);
		}
		else if (buttonThatWasClicked == &cvPort2)
		{
			updateCvUI(2);
		}
		else if (buttonThatWasClicked == &cvPort3)
		{
			updateCvUI(3);
		}
		else if (buttonThatWasClicked == &cvPort4)
		{
			updateCvUI(4);
		}
		else if (buttonThatWasClicked == &cvPort5)
		{
			updateCvUI(5);
		}
		else if (buttonThatWasClicked == &cvPort6)
		{
			updateCvUI(6);
		}
		else if (buttonThatWasClicked == &cvPort7)
		{
			updateCvUI(7);
		}
		else if (buttonThatWasClicked == &cvPort8)
		{
			updateCvUI(8);
		}
	}

	void IgniteCvConfig::showEnvolopSliders(bool state)
	{
		for (int i = 0; i < NO_OF_ENVOLOPE_SLIDER; i++)
		{
			slider[i].setEnabled(state);
			state ? slider[i].setAlpha(1.0f) : slider[i].setAlpha(0.0f);
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam((int)(FrontPannelParam::paramKey_TRACKROTARY1)+(i + 1)), state ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF);
		}

	}

	void IgniteCvConfig::updateSliderData(EnvlopType index, int8_t data, bool play_mode)
	{
		switch (index)
		{
		case ui::IgniteCvConfig::ATTACK:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramEnvAttack, data, play_mode);
			break;
		case ui::IgniteCvConfig::DECAY:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramEnvDecay, data, play_mode);
			break;
		case ui::IgniteCvConfig::SUSTAIN:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramEnvSustain, data, play_mode);
			break;
		case ui::IgniteCvConfig::RELEASE:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramEnvRelease, data, play_mode);
			break;
		case ui::IgniteCvConfig::AMOUNT:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramEnvAmount, data, play_mode);
			break;
			/*case ui::IgniteCvConfig::VELOCITY:
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramEnvVelocity, data, play_mode);
				break;*/
		default:
			break;
		}
	}

	int8_t IgniteCvConfig::getSiderData(EnvlopType index)
	{
		std::vector<IgniteParamList> cvParams;
		IgniteParamList params;

		switch (index)
		{
		case ui::IgniteCvConfig::ATTACK:
			params.param = (paramId_t)SettingsCvioCnfgParam::paramEnvAttack;
			break;
		case ui::IgniteCvConfig::DECAY:
			params.param = (paramId_t)SettingsCvioCnfgParam::paramEnvDecay;
			break;
		case ui::IgniteCvConfig::SUSTAIN:
			params.param = (paramId_t)SettingsCvioCnfgParam::paramEnvSustain;
			break;
		case ui::IgniteCvConfig::RELEASE:
			params.param = (paramId_t)SettingsCvioCnfgParam::paramEnvRelease;
			break;
		case ui::IgniteCvConfig::AMOUNT:
			params.param = (paramId_t)SettingsCvioCnfgParam::paramEnvAmount;
			break;
		case ui::IgniteCvConfig::VELOCITY:
			params.param = (paramId_t)SettingsCvioCnfgParam::paramEnvVelocity;
			break;
		default:
			break;
		}

		cvParams.push_back(params);
		cvParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, cvParams);
		return cvParams[0].MsgValue.get< int8_t >();
	}

	void IgniteCvConfig::onRotaryValueChange(common_rotaryslider* ptr, double Value)
	{
		updateSliderData((EnvlopType)getKnobIndex(ptr->getKnob()), (int8_t)roundToInt(Value), true);
		IgniteControlOptions::GetAppOptInstance()->enableKey(IgniteControlOptions::SAVE, true);
		IgniteControlOptions::GetAppOptInstance()->enableKey(IgniteControlOptions::UNDO, true);
		IgniteCvio::GetAppCvioInstance()->cvioConfigDataUpdated = true;
	}

	void IgniteCvConfig::onRotaryDragEnd(common_rotaryslider* ptr, double Value)
	{
		updateSliderData((EnvlopType)getKnobIndex(ptr->getKnob()), (int8_t)roundToInt(Value), false);
		IgniteControlOptions::GetAppOptInstance()->enableKey(IgniteControlOptions::SAVE, true);
		IgniteControlOptions::GetAppOptInstance()->enableKey(IgniteControlOptions::UNDO, true);
		IgniteCvio::GetAppCvioInstance()->cvioConfigDataUpdated = true;
	}

	int IgniteCvConfig::getKnobIndex(String knob)
	{
		juce_wchar a = knob[0];
		for (int i = 0; i < MAX_TRACK_VALUE; i++)
			if (a == (juce_wchar)('A' + i))
				return i;
		return 0;
	}

	int IgniteCvConfig::isEditing()
	{
		/*if (cvChannel.IsEditing())
			return CV_CHANNEL_FOCUSE;
		else */if (cvLaw.IsEditing())
			return CVLAW_CHANNEL_FOCUSE;
		/*else if (cvGate.IsEditing())
			return CVGATE_FOCUSE;*/
			/*else if (cvCCList.IsEditing())
				return CVCCLIST_FOCUSE;*/
				/*else if (cvSlide.IsEditing())
					return CVSLIDE_FOCUSE;*/
					/*else if (slideTime.IsEditing())
						return SLIDETIME_FOCUSE;*/
		else if (cvNoteRangeStart.IsEditing())
			return CVNOTERANGESTART_FOCUSE;
		else if (cvNoteRangeEnd.IsEditing())
			return CVNOTERANGEEND_FOCUSE;
		else if (cvOutput.IsEditing())
			return CVOUTPUT_FOCUSE;
		/*else if (moveLeft.isFocused)
			return CV_LEFT_FOCUSE;*/
		else if (CVNoteSelection.IsEditing())
			return CVNOTESELECTION_FOCUSE;
		/*else if (moveRight.isFocused)
			return CV_RIGHT_FOCUSE;*/
		else
			return false;
	}

	void IgniteCvConfig::updateOnViewPositionChange(ui::CommonViewport* pViewport)
	{
		repaint();
	}

	bool IgniteCvConfig::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = CVConfigItemID::NO_FOCUS;
		auto ptrCvio = IgniteCvio::GetAppCvioInstance();

		if (KeyFocusedItem == CVConfigItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = CVConfigItemID::CV_PORT1;
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
				case FrontPannelParam::paramRot_PADROT2:
				case FrontPannelParam::paramRot_PADROT3:
				case FrontPannelParam::paramRot_PADROT4:
				case FrontPannelParam::paramRot_PADROT5:
				case FrontPannelParam::paramRot_PADROT6:
				case FrontPannelParam::paramRot_PADROT7:
					if (KeyValue == ROTARY_DIRECTION_LEFT || KeyValue == ROTARY_DIRECTION_RIGHT)
					{
						int i;
						i = (param - (paramId_t)FrontPannelParam::paramRot_PADROT2);
						if (slider[i].getAlpha() == 1.0f)
							slider[i].FPKeyHandler(true, param, KeyValue);
						setfocus = false;
					}
					break;
				case FrontPannelParam::paramKey_TRACKSEL1:
				case FrontPannelParam::paramKey_TRACKSEL2:
				case FrontPannelParam::paramKey_TRACKSEL3:
				case FrontPannelParam::paramKey_TRACKSEL4:
				case FrontPannelParam::paramKey_TRACKSEL5:
				case FrontPannelParam::paramKey_TRACKSEL6:
				case FrontPannelParam::paramKey_TRACKSEL7:
				case FrontPannelParam::paramKey_TRACKSEL8:
					if ((KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
					{
						KeyFocusedItem = CV_PORT1 + (param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1);
						PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
						setfocus = false;
					}
					break;
				case FrontPannelParam::paramKey_ROTARYROW:
					if ((KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
					{
						if (ptrCvio->cvbtn.getToggleState())
							ptrCvio->gatebtn.setToggleState(true, NotificationType::sendNotification);
						else
							ptrCvio->cvbtn.setToggleState(true, NotificationType::sendNotification);
					}
					break;
				case FrontPannelParam::paramRot_BAR:
					/*if (KeyFocusedItem >= CVConfigItemID::CV_LEFT && KeyFocusedItem <= CVConfigItemID::CV_OUTPUT)
					{
						if (KeyValue == ROTARY_DIRECTION_RIGHT)
							KeyFocusedItem = (KeyFocusedItem + 1 >= CVConfigItemID::FOCUS_MAX ? (CVConfigItemID::FOCUS_MAX) : KeyFocusedItem + 1);
						else
							KeyFocusedItem = (KeyFocusedItem - 1 <= CVConfigItemID::CV_PORT8 ? (CVConfigItemID::CV_LEFT) : KeyFocusedItem - 1);
					}
					else
					{
						KeyFocusedItem = CVConfigItemID::CV_LEFT;
					}
					break;*/
				case FrontPannelParam::paramKey_RMOVELEFT:
					KeyFocusedItem = (KeyFocusedItem + 1 >= CVConfigItemID::FOCUS_MAX ? (CVConfigItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= CVConfigItemID::NO_FOCUS ? (CVConfigItemID::NO_FOCUS) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
					break;

				}
			}
		}
		if (slider[0].isEnabled())
		{
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RELEASE:
				slider[0].FPKeyHandler(true, param, KeyValue);
				current_slider = 0;
				break;
			case FrontPannelParam::paramKey_FILTER:
				slider[1].FPKeyHandler(true, param, KeyValue);
				current_slider = 1;
				break;
			case FrontPannelParam::paramKey_RESONANCE:
				slider[2].FPKeyHandler(true, param, KeyValue);
				current_slider = 2;
				break;
			case FrontPannelParam::paramKey_VOLUME:
				slider[3].FPKeyHandler(true, param, KeyValue);
				current_slider = 3;
				break;
			case FrontPannelParam::paramKey_REVERBE:
				current_slider = 4;
				slider[4].FPKeyHandler(true, param, KeyValue);
				break;
			case FrontPannelParam::paramKey_CHORUS:
				current_slider = 5;
				slider[5].FPKeyHandler(true, param, KeyValue);
				break;
				/*case FrontPannelParam::paramKey_EQHI:
					current_slider = 6;
					slider[6].FPKeyHandler(true, param, KeyValue);
					break;*/
			}
		}

		if (setfocus)
		{
			PannelSendKey(true, param, KeyValue);
		}
		return true;
	}


	void IgniteCvConfig::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (CV_Config[KeyFocusedItem])
		{
		case CV_PORT1:
			cvPort1.FPKeyHandler(isFocuse, param, 0);
			break;
		case CV_PORT2:
			cvPort2.FPKeyHandler(isFocuse, param, 0);
			break;
		case CV_PORT3:
			cvPort3.FPKeyHandler(isFocuse, param, 0);
			break;
		case CV_PORT4:
			cvPort4.FPKeyHandler(isFocuse, param, 0);
			break;
		case CV_PORT5:
			cvPort5.FPKeyHandler(isFocuse, param, 0);
			break;
		case CV_PORT6:
			cvPort6.FPKeyHandler(isFocuse, param, 0);
			break;
		case CV_PORT7:
			cvPort7.FPKeyHandler(isFocuse, param, 0);
			break;
		case CV_PORT8:
			cvPort8.FPKeyHandler(isFocuse, param, 0);
			break;
			/*case CV_LEFT:
				moveLeft.FPKeyHandler(isFocuse, param, KeyValue);
				break;*/
				/*case CV_CHANNEL:
					cvChannel.FPKeyHandler(isFocuse, param, KeyValue);
					break;*/
		case CV_LAW:
			cvLaw.FPKeyHandler(isFocuse, param, KeyValue);
			break;
			/*case CV_GATE:
				cvGate.FPKeyHandler(isFocuse, param, KeyValue);
				break;*/
				/*case CV_CC:
					cvCCList.FPKeyHandler(isFocuse, param, KeyValue);
					break;*/
					/*case CV_SLIDE:
						cvSlide.FPKeyHandler(isFocuse, param, KeyValue);
						break;*/
						/*case CV_TIME:
							slideTime.FPKeyHandler(isFocuse, param, KeyValue);
							break;*/
		case CV_NOTE_START:
			cvNoteRangeStart.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case CV_NOTE_END:
			cvNoteRangeEnd.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case CV_NOTE_SELECTION:
			CVNoteSelection.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case CV_OUTPUT:
			cvOutput.FPKeyHandler(isFocuse, param, KeyValue);
			break;
			/*case CV_RIGHT:
				moveRight.FPKeyHandler(isFocuse, param, KeyValue);
				break;*/
		default:
			break;
		}
		repaint();
	}

	////////////////////////////////////////////////
	//   Class: Ignite Gate Config
	////////////////////////////////////////////////
	IgniteGateConfig::IgniteGateConfig()
	{
		GateConfigLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		GateConfigLable.setJustificationType(juce::Justification::centredLeft);
		GateConfigLable.setEditable(false, false, false);
		GateConfigLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		GateConfigLable.setColour(juce::Label::outlineColourId, Colours::white);
		GateConfigLable.makeVisible(this);

		addAndMakeVisible(gatePort1);
		gatePort1.addListener(this);

		addAndMakeVisible(gatePort2);
		gatePort2.addListener(this);

		addAndMakeVisible(gatePort3);
		gatePort3.addListener(this);

		addAndMakeVisible(gatePort4);
		gatePort4.addListener(this);

		addAndMakeVisible(gatePort5);
		gatePort5.addListener(this);

		addAndMakeVisible(gatePort6);
		gatePort6.addListener(this);

		addAndMakeVisible(gatePort7);
		gatePort7.addListener(this);

		addAndMakeVisible(gatePort8);
		gatePort8.addListener(this);

		/*addAndMakeVisible(gateChannel);
		gateChannel.setDisplayTitle(true);
		gateChannel.setJustificationType(juce::Justification::centred);*/

		addAndMakeVisible(gateType);
		gateType.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);

		addAndMakeVisible(gateOutput);
		gateOutput.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);

		addAndMakeVisible(gateMode);
		gateMode.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		gateMode.drawBorder(true);
		gateMode.setValueColour(Theme::Instance().getColour(customOrange));
		gateMode.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,320 });

		//gateChannel.setcustombounds(true, ui::Rectangle<int>{63, 3, 35, 60}, ui::Rectangle<int>{55, 35, 50, 50});
		gateType.setcustombounds(true, ui::Rectangle<int>{20, 4, 135, 60}, ui::Rectangle<int>{33, 51, 90, 20});
		gateOutput.setcustombounds(true, ui::Rectangle<int>{20, 4, 135, 60}, ui::Rectangle<int>{33, 51, 90, 20});

		gatePort1.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		gatePort2.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		gatePort3.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		gatePort4.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		gatePort5.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		gatePort6.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		gatePort7.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		gatePort8.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		gateType.setValueColour(Theme::Instance().getColour(customOrange));
		gateOutput.setValueColour(Theme::Instance().getColour(customOrange));
		//gateChannel.setTextColour(Theme::Instance().getColour(customOrange));

		gateConfigPort.items.add(FlexItem(gatePort1).withMargin({ 0,5,0,0 }).withFlex(1));
		gateConfigPort.items.add(FlexItem(gatePort2).withMargin({ 0,5,0,0 }).withFlex(1));
		gateConfigPort.items.add(FlexItem(gatePort3).withMargin({ 0,5,0,0 }).withFlex(1));
		gateConfigPort.items.add(FlexItem(gatePort4).withMargin({ 0,5,0,0 }).withFlex(1));
		gateConfigPort.items.add(FlexItem(gatePort5).withMargin({ 0,5,0,0 }).withFlex(1));
		gateConfigPort.items.add(FlexItem(gatePort6).withMargin({ 0,5,0,0 }).withFlex(1));
		gateConfigPort.items.add(FlexItem(gatePort7).withMargin({ 0,5,0,0 }).withFlex(1));
		gateConfigPort.items.add(FlexItem(gatePort8).withMargin({ 0,5,0,0 }).withFlex(1));

		gateType.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,280 });
		gateOutput.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,280 });

		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramActiveGatePort, 0);
		getAssets();
		/*gateChannel.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramGateChannelNum, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};*/

		gateType.onSelectionChanged = [this](int value, const juce::String&)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramGateType, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		gateOutput.onSelectionChanged = [this](int value, const juce::String&)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramGateOutput, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		gateMode.onSelectionChanged = [this](int value, const juce::String&)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				IgniteCvio* cvioComp = IgniteCvio::GetAppCvioInstance();
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramGateMode, value);
				cvioComp->enableControlButton(IgniteControlOptions::SAVE, true);
				cvioComp->enableControlButton(IgniteControlOptions::UNDO, true);
				cvioComp->cvioConfigDataUpdated = true;
			};

		/*gateChannel.onFocusChanged = [this](bool a)
			{
				repaint();
			};*/

		gateType.onFocusChanged = [this](bool a)
			{
				repaint();
			};

		gateOutput.onFocusChanged = [this](bool a)
			{
				repaint();
			};

		gateMode.onFocusChanged = [this](bool a)
			{
				repaint();
			};
	}

	IgniteGateConfig::~IgniteGateConfig()
	{
	}

	void IgniteGateConfig::updateGateData()
	{
		std::vector<IgniteParamList> gateParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsCvioCnfgParam::paramGateChannelNum;
		gateParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramGateType;
		gateParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramGateMode;
		gateParams.push_back(params);
		params.param = (paramId_t)SettingsCvioCnfgParam::paramGateOutput;
		gateParams.push_back(params);
		gateParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, gateParams);


		for (auto& param_id : gateParams)
		{
			switch (param_id.param)
			{
			/*case (paramId_t)SettingsCvioCnfgParam::paramGateChannelNum:
				gateChannel.setText(String(param_id.MsgValue.get< int8_t >()), dontSendNotification);
				break;*/
			case (paramId_t)SettingsCvioCnfgParam::paramGateType:
				gateType.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsCvioCnfgParam::paramGateMode:
				gateMode.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsCvioCnfgParam::paramGateOutput:
				gateOutput.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			}
		}
	}

	void IgniteGateConfig::getAssets()
	{
		imageGateportBg = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("gateport-bg-container.png"));
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-modallink-122x80-default.png"));
		imageDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-modallink-122x80-default-hover.png"));

		imageGateDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-default.png"));
		imageGateDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-default-hover.png"));
		imageGateActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-active.png"));
		imageGateActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("port-selection-active-hover.png"));

	
	}

	void IgniteGateConfig::paint(juce::Graphics& g)
	{

		g.drawImage(imageGateportBg, ui::Rectangle<float>{0, 0, 1004, 74});
		
		Image Draw;
		//Draw = gateChannel.getFocusState() ? imageDefaultHover : imageDefault;
		//g.drawImage(Draw, ui::Rectangle<float>{0, 84, 159, 80});
		Draw = gateMode.getFocusState() ? imageDefaultHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{0, 84, 159, 80});
		Draw = gateType.getFocusState() ? imageDefaultHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{169, 84, 159, 80});
		Draw = gateOutput.getFocusState() ? imageDefaultHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{338, 84, 159, 80});

		Draw = (gatePort1.getToggleState() ? ((gatePort1.isMouseOver() || gatePort1.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort1.isMouseOver() || gatePort1.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{215, 15, 94, 44});

		Draw = (gatePort2.getToggleState() ? ((gatePort2.isMouseOver() || gatePort2.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort2.isMouseOver() || gatePort2.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{314, 15, 94, 44});

		Draw = (gatePort3.getToggleState() ? ((gatePort3.isMouseOver() || gatePort3.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort3.isMouseOver() || gatePort3.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{413, 15, 94, 44});

		Draw = (gatePort4.getToggleState() ? ((gatePort4.isMouseOver() || gatePort4.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort4.isMouseOver() || gatePort4.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{512, 15, 94, 44});

		Draw = (gatePort5.getToggleState() ? ((gatePort5.isMouseOver() || gatePort5.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort5.isMouseOver() || gatePort5.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{611, 15, 94, 44});

		Draw = (gatePort6.getToggleState() ? ((gatePort6.isMouseOver() || gatePort6.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort6.isMouseOver() || gatePort6.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{710, 15, 94, 44});

		Draw = (gatePort7.getToggleState() ? ((gatePort7.isMouseOver() || gatePort7.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort7.isMouseOver() || gatePort7.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{809, 15, 94, 44});

		Draw = (gatePort8.getToggleState() ? ((gatePort8.isMouseOver() || gatePort8.isFocused) ? imageGateActiveHover : imageGateActive) : ((gatePort8.isMouseOver() || gatePort8.isFocused) ? imageGateDefaultHover : imageGateDefault));
		g.drawImage(Draw, ui::Rectangle<float>{908, 15, 94, 44});

	}

	void IgniteGateConfig::resized()
	{
		GateConfigLable.setBounds(0, 15, 1004, 44);
		gateConfigPort.performLayout(ui::Rectangle<float>{215, 15, 792, 44});
		//gateChannel.setBounds(0, 84, 159, 80);
		gateMode.setBounds(0, 84, 159, 80);
		gateType.setBounds(169, 84, 159, 80);
		gateOutput.setBounds(338, 84, 159, 80);
	}

	void IgniteGateConfig::updateGateOutputPort()
	{
		gatePort1.setToggleState(true, dontSendNotification);
	}

	void IgniteGateConfig::setGatePortButtonToggleState(int portNumber)
	{
		gatePort1.setToggleState(false, dontSendNotification);
		gatePort2.setToggleState(false, dontSendNotification);
		gatePort3.setToggleState(false, dontSendNotification);
		gatePort4.setToggleState(false, dontSendNotification);
		gatePort5.setToggleState(false, dontSendNotification);
		gatePort6.setToggleState(false, dontSendNotification);
		gatePort7.setToggleState(false, dontSendNotification);
		gatePort8.setToggleState(false, dontSendNotification);

		switch (portNumber)
		{
		case 1:
			gatePort1.setToggleState(true, dontSendNotification);
			break;
		case 2:
			gatePort2.setToggleState(true, dontSendNotification);
			break;
		case 3:
			gatePort3.setToggleState(true, dontSendNotification);
			break;
		case 4:
			gatePort4.setToggleState(true, dontSendNotification);
			break;
		case 5:
			gatePort5.setToggleState(true, dontSendNotification);
			break;
		case 6:
			gatePort6.setToggleState(true, dontSendNotification);
			break;
		case 7:
			gatePort7.setToggleState(true, dontSendNotification);
			break;
		case 8:
			gatePort8.setToggleState(true, dontSendNotification);
			break;
		}
	}

	void IgniteGateConfig::updateGateUI(uint8_t selectedPort)
	{
		setGatePortButtonToggleState(selectedPort);
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramActiveGatePort, selectedPort - 1);
		updateGateData();
	}

	void IgniteGateConfig::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &gatePort1)
		{
			updateGateUI(1);
		}
		else if (buttonThatWasClicked == &gatePort2)
		{
			updateGateUI(2);
		}
		else if (buttonThatWasClicked == &gatePort3)
		{
			updateGateUI(3);
		}
		else if (buttonThatWasClicked == &gatePort4)
		{
			updateGateUI(4);
		}
		else if (buttonThatWasClicked == &gatePort5)
		{
			updateGateUI(5);
		}
		else if (buttonThatWasClicked == &gatePort6)
		{
			updateGateUI(6);
		}
		else if (buttonThatWasClicked == &gatePort7)
		{
			updateGateUI(7);
		}
		else if (buttonThatWasClicked == &gatePort8)
		{
			updateGateUI(8);
		}
	}

	int IgniteGateConfig::isEditing()
	{
		int index = 0;

		//gateChannel.IsEditing() ? index = 9 : 0;
		gateMode.IsEditing() ? index = 9 : 0;
		gateType.IsEditing() ? index = 10 : 0;
		gateOutput.IsEditing() ? index = 11 : 0;

		return index;
	}

	bool IgniteGateConfig::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = GateConfigItemID::NO_FOCUS;
		auto ptrCvio = IgniteCvio::GetAppCvioInstance();

		if (KeyFocusedItem == GateConfigItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			//KeyFocusedItem = GateConfigItemID::GATE_PORT1;
			KeyFocusedItem = GateConfigItemID::GATE_MODE;
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
				case FrontPannelParam::paramKey_TRACKSEL1:
				case FrontPannelParam::paramKey_TRACKSEL2:
				case FrontPannelParam::paramKey_TRACKSEL3:
				case FrontPannelParam::paramKey_TRACKSEL4:
				case FrontPannelParam::paramKey_TRACKSEL5:
				case FrontPannelParam::paramKey_TRACKSEL6:
				case FrontPannelParam::paramKey_TRACKSEL7:
				case FrontPannelParam::paramKey_TRACKSEL8:
					break;
				case FrontPannelParam::paramKey_ROTARYROW:
					if ((KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
					{
						if (ptrCvio->cvbtn.getToggleState())
							ptrCvio->gatebtn.setToggleState(true, NotificationType::sendNotification);
						else
							ptrCvio->cvbtn.setToggleState(true, NotificationType::sendNotification);
					}
					break;
				case FrontPannelParam::paramRot_BAR:
					if (KeyFocusedItem >= GateConfigItemID::GATE_MODE && KeyFocusedItem <= GateConfigItemID::FOCUS_MAX)
					{
						if (KeyValue == ROTARY_DIRECTION_LEFT)
							KeyFocusedItem = (KeyFocusedItem + 1 >= GateConfigItemID::FOCUS_MAX ? (GateConfigItemID::FOCUS_MAX) : KeyFocusedItem + 1);
						else
							KeyFocusedItem = (KeyFocusedItem - 1 <= GateConfigItemID::GATE_PORT8 ? (GateConfigItemID::GATE_MODE) : KeyFocusedItem - 1);
					}
					else
					{
						KeyFocusedItem = GateConfigItemID::GATE_MODE;
					}
					break;
				case FrontPannelParam::paramKey_RMOVELEFT:
					KeyFocusedItem = (KeyFocusedItem + 1 >= GateConfigItemID::FOCUS_MAX ? (GateConfigItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= GateConfigItemID::NO_FOCUS ? (GateConfigItemID::NO_FOCUS) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
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


	void IgniteGateConfig::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (Gate_Config[KeyFocusedItem])
		{
		case GATE_PORT1:
			gatePort1.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE_PORT2:
			gatePort2.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE_PORT3:
			gatePort3.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE_PORT4:
			gatePort4.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE_PORT5:
			gatePort5.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE_PORT6:
			gatePort6.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE_PORT7:
			gatePort7.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE_PORT8:
			gatePort8.FPKeyHandler(isFocuse, param, 0);
			break;
		/*case GATE_CHANNEL:
			gateChannel.FPKeyHandler(isFocuse, param, KeyValue);
			break;*/
		case GATE_TYPE:
			gateType.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case GATE_MODE:
			gateMode.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case GATE_OUTPUT:
			gateOutput.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
		repaint();
	}
};
