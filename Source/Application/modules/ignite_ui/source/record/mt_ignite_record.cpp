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
	//   Class: Ignite Record
	////////////////////////////////////////////////
	IgniteRecord::IgniteRecord()
	{
		addAndMakeVisible(quantBtn);
		quantBtn.addListener(this);
		quantBtn.setToggleable(true);
		quantBtn.setComponentID("quantComp");
		quantBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		quantBtn.sethoverImages("toggle-quantization-default-hover.png","toggle-quantization-active-hover.png","toggle-quantization-disabled.png");

		/*addAndMakeVisible(mthruBtn);
		mthruBtn.addListener(this);
		mthruBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		mthruBtn.setToggleable(true);
		mthruBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mthruBtn.sethoverImages("toggle-mthru-default-hover.png", "toggle-mthru-active-hover.png", "toggle-mthru-disabled.png");

		addAndMakeVisible(ftsBtn);
		ftsBtn.addListener(this);
		ftsBtn.setToggleable(true);
		ftsBtn.setComponentID("ftsComp");
		ftsBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		ftsBtn.sethoverImages("toggle-fts-default-hover.png", "toggle-fts-active-hover.png", "toggle-fts-disabled.png");

		addAndMakeVisible(autoAddBarBtn);
		autoAddBarBtn.addListener(this);
		autoAddBarBtn.setToggleable(true);
		autoAddBarBtn.setComponentID("autoAddBarComp");
		autoAddBarBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		autoAddBarBtn.sethoverImages("toggle-addautobars-default-hover.png", "toggle-addautobars-active-hover.png", "toggle-addautobars-disabled.png");*/

		addAndMakeVisible(barOverwriteBtn);
		barOverwriteBtn.addListener(this);
		barOverwriteBtn.setToggleable(true);
		barOverwriteBtn.setComponentID("barOverwriteComp");
		barOverwriteBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		barOverwriteBtn.sethoverImages("toggle-barovewrite-default-hover.png", "toggle-barovewrite-active-hover.png", "toggle-barovewrite-disabled.png");

		maxBars.makeVisible(this);
		maxBars.setDisplayTitle(true);
		maxBars.setJustificationType(juce::Justification::centred);
		maxBars.setTextColour(Theme::Instance().getColour(customOrange));
		maxBars.setComponentID("maxBarsComp");
		maxBars.setcustombounds(true, ui::Rectangle<int>{144, 0, 50, 50}, ui::Rectangle<int>{90, 35, 150, 50});

		addAndMakeVisible(noteEvtBtn);
		noteEvtBtn.addListener(this);
		noteEvtBtn.setToggleable(true);
		noteEvtBtn.setComponentID("noteEvtComp");
		noteEvtBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		noteEvtBtn.sethoverImages("toggle-noteevents-default-hover.png", "toggle-noteevents-active-hover.png", "toggle-noteevents-disabled.png");

		addAndMakeVisible(ctrlEvtBtn);
		ctrlEvtBtn.addListener(this);
		ctrlEvtBtn.setToggleable(true);
		ctrlEvtBtn.setComponentID("ctrlEvtComp");
		ctrlEvtBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		ctrlEvtBtn.sethoverImages("toggle-midicc-default-hover.png", "toggle-midicc-active-hover.png", "toggle-midicc-disabled.png");

		addAndMakeVisible(aftEvtBtn);
		aftEvtBtn.addListener(this);
		aftEvtBtn.setToggleable(true);
		aftEvtBtn.setComponentID("aftEvtComp");
		aftEvtBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		aftEvtBtn.sethoverImages("toggle-afttouch-default-hover.png", "toggle-afttouch-active-hover.png", "toggle-afttouch-disabled.png");

		addAndMakeVisible(bendEvtBtn);
		bendEvtBtn.addListener(this);
		bendEvtBtn.setToggleable(true);
		bendEvtBtn.setComponentID("bendEvtComp");
		bendEvtBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		bendEvtBtn.sethoverImages("toggle-pitchblend-default-hover.png", "toggle-pitchblend-active-hover.png", "toggle-pitchblend-disabled.png");

		addAndMakeVisible(polypEvtBtn);
		polypEvtBtn.addListener(this);
		polypEvtBtn.setToggleable(true);
		polypEvtBtn.setComponentID("polypEvtComp");
		polypEvtBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		polypEvtBtn.sethoverImages("toggle-polyp-default-hover.png", "toggle-polyp-active-hover.png", "toggle-polyp-disabled.png");

		addAndMakeVisible(prgmEvtBtn);
		prgmEvtBtn.addListener(this);
		prgmEvtBtn.setToggleable(true);
		prgmEvtBtn.setComponentID("pgmEvtComp");
		prgmEvtBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		prgmEvtBtn.sethoverImages("toggle-pce-default-hover.png", "toggle-pce-active-hover.png", "toggle-pce-disabled.png");

		eventFilterLable.makeVisible(this);
		eventFilterLable.setDisplayTitleAndBorder(false);
		eventFilterLable.setInterceptsMouseClicks(false, false);

		recordOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(recordOptCtl);
		recordOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		recordOptCtl->addOptCtlListener(this);

		recordBox1.items.add(FlexItem(quantBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		/*recordBox1.items.add(FlexItem(mthruBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		recordBox1.items.add(FlexItem(ftsBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		recordBox2.items.add(FlexItem(autoAddBarBtn).withMargin({ 0, 8, 0, 0 }).withFlex(1));*/
		recordBox1.items.add(FlexItem(barOverwriteBtn).withMargin({ 0, 8, 8, 0 }).withFlex(1));

		filterBox1.items.add(FlexItem(noteEvtBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		filterBox1.items.add(FlexItem(ctrlEvtBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		filterBox1.items.add(FlexItem(aftEvtBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		filterBox2.items.add(FlexItem(bendEvtBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		filterBox2.items.add(FlexItem(polypEvtBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		filterBox2.items.add(FlexItem(prgmEvtBtn).withMargin({ 0,8,8,0 }).withFlex(1));

		filterBox3.flexDirection = FlexBox::Direction::column;
		filterBox3.items.add(FlexItem(filterBox1).withFlex(1));
		filterBox3.items.add(FlexItem(filterBox2).withFlex(1));

		popupPtr = CommonPopUp::getCommonPopupInstance();
		getAssets();
		maxBars.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordNumOfBarsParam, value);
			recordOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			recordOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			recordConfigDataUpdated = true;
		};
		maxBars.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	IgniteRecord::~IgniteRecord()
	{
	}

	void IgniteRecord::getAssets()
	{
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-default.png"));
		imagehover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-default-hover.png"));
		imageDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-addautobars-disabled.png"));
	}

	void IgniteRecord::paint(juce::Graphics& g)
	{
		if (recordConfigDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("Record Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Record Configuration");
		Image Draw;

		Draw = maxBars.isEnabled() ? (maxBars.getFocusState() ? imagehover : imageDefault) : imageDisabled;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 70, 328, 80 },RectanglePlacement::stretchToFit);
	}

	void IgniteRecord::resized()
	{
		recordBox1.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox1, widthSongMenuBox1 * 2 /3, heightSongMenuBox1));
		//recordBox2.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2, 664, heightSongMenuBox1));
		maxBars.setBounds(682, 70, 328, 80);
		filterBox3.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartFilterBox, widthSongMenuBox1, (int)heightSongMenuBox1 * 2));
		eventFilterLable.setBounds(Rectangle(xStartSongMenuBox1, yStartEventLable, widthEventLable, 30));
	}

	void IgniteRecord::setEventFilterValue(uint16_t value, bool state)
	{
		std::vector<IgniteParamList> recordParams;
		IgniteParamList params;

		params.param = (paramId_t)SongParam::paramRecordEventFilter;
		recordParams.push_back(params);
		recordParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, recordParams);
		state ? (value = recordParams[0].MsgValue.get<uint16_t>() | value) : (value = (recordParams[0].MsgValue.get<uint16_t>() & ~value));
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramRecordEventFilter, value);
	}

	void IgniteRecord::updateData()
	{
		std::vector<IgniteParamList> recordParamList;
		IgniteParamList params;

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordQuantizationParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordMthruParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordFTSParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordBarOverWriteParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordAutoAddBarParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordNoteEventParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordMidiCCEventParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordAfterTouchEventParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordPitchBendEventParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordPolyPEventParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordPgmChangeEventParam;
		recordParamList.push_back(params);

		params.param = (paramId_t)SettingsRecordCnfgParam::SettingRecordNumOfBarsParam;
		recordParamList.push_back(params);

		recordParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, recordParamList);

		quantBtn.setToggleState((bool)recordParamList[0].MsgValue.get<int8_t>(), dontSendNotification);
		//mthruBtn.setToggleState((bool)recordParamList[1].MsgValue.get<int8_t>(), dontSendNotification);
		//ftsBtn.setToggleState((bool)recordParamList[2].MsgValue.get<int8_t>(), dontSendNotification);
		barOverwriteBtn.setToggleState((bool)recordParamList[3].MsgValue.get<int8_t>(), dontSendNotification);
		//autoAddBarBtn.setToggleState((bool)recordParamList[4].MsgValue.get<int8_t>(), dontSendNotification);
		noteEvtBtn.setToggleState((bool)recordParamList[5].MsgValue.get<int8_t>(), dontSendNotification);
		ctrlEvtBtn.setToggleState((bool)recordParamList[6].MsgValue.get<int8_t>(), dontSendNotification);
		aftEvtBtn.setToggleState((bool)recordParamList[7].MsgValue.get<int8_t>(), dontSendNotification);
		bendEvtBtn.setToggleState((bool)recordParamList[8].MsgValue.get<int8_t>(), dontSendNotification);
		polypEvtBtn.setToggleState((bool)recordParamList[9].MsgValue.get<int8_t>(), dontSendNotification);
		prgmEvtBtn.setToggleState((bool)recordParamList[10].MsgValue.get<int8_t>(), dontSendNotification);
		maxBars.setText(String(recordParamList[11].MsgValue.get<int8_t>()), dontSendNotification);

		quantBtn.getToggleState() ? quantBtn.setButtonText("Quantization:on") : quantBtn.setButtonText("Quantization:off");
		//mthruBtn.getToggleState() ? mthruBtn.setButtonText("Mthru:on") : mthruBtn.setButtonText("Mthru:off");
		//ftsBtn.getToggleState() ? ftsBtn.setButtonText("FTS:on") : ftsBtn.setButtonText("FTS:off");
		barOverwriteBtn.getToggleState() ? barOverwriteBtn.setButtonText("Bar OverWrite:on") : barOverwriteBtn.setButtonText("Bar OverWrite:off");
		//autoAddBarBtn.getToggleState() ? autoAddBarBtn.setButtonText("Auto Add Bars:on") : autoAddBarBtn.setButtonText("Auto Add Bars:off");
		noteEvtBtn.getToggleState() ? noteEvtBtn.setButtonText("NOTE EVENTS:on") : noteEvtBtn.setButtonText("NOTE EVENTS:off");
		ctrlEvtBtn.getToggleState() ? ctrlEvtBtn.setButtonText("MIDI CC EVENTS:on") : ctrlEvtBtn.setButtonText("MIDI CC EVENTS:off");
		aftEvtBtn.getToggleState() ? aftEvtBtn.setButtonText("AFT TOUCH EVENT:on") : aftEvtBtn.setButtonText("AFT TOUCH EVENT:off");
		bendEvtBtn.getToggleState() ? bendEvtBtn.setButtonText("PITCH BEND EVEN:on") : bendEvtBtn.setButtonText("PITCH BEND EVEN:off");
		polypEvtBtn.getToggleState() ? polypEvtBtn.setButtonText("POLY-P EVENT:on") : polypEvtBtn.setButtonText("POLY-P EVENT:off");
		prgmEvtBtn.getToggleState() ? prgmEvtBtn.setButtonText("PROGRAM CHANGE EVENT:on") : prgmEvtBtn.setButtonText("PROGRAM CHANGE EVENT:off");
	}

	void IgniteRecord::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &quantBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::QUANTIZATION;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordQuantizationParam, quantBtn.getToggleState());
			quantBtn.setButtonText(quantBtn.getToggleState() ? "Quantization:On" : "Quantization:Off");
		}
		/*else if (buttonThatWasClicked == &mthruBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::MTHRU;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordMthruParam, mthruBtn.getToggleState());
			mthruBtn.setButtonText(mthruBtn.getToggleState() ? "Mthru:On" : "Mthru:Off");
		}
		else if (buttonThatWasClicked == &ftsBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::FTS;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordFTSParam, ftsBtn.getToggleState());
			ftsBtn.setButtonText(ftsBtn.getToggleState() ? "FTS:On" : "FTS:Off");
		}*/
		else if (buttonThatWasClicked == &barOverwriteBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::BAR_OVERWRITE;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordBarOverWriteParam, barOverwriteBtn.getToggleState());
			barOverwriteBtn.setButtonText(barOverwriteBtn.getToggleState() ? "Bar OverWrite:On" : "Bar OverWrite:Off");
		}
		/*else if (buttonThatWasClicked == &autoAddBarBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::AUTO_ADD_BARS;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordAutoAddBarParam, autoAddBarBtn.getToggleState());
			autoAddBarBtn.setButtonText(autoAddBarBtn.getToggleState() ? "Auto Add Bars:On" : "Auto Add Bars:Off");
		}*/
		else if (buttonThatWasClicked == &noteEvtBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::NOTE_EVENTS;
			setEventFilterValue((uint16_t)RecordEvents::Note, noteEvtBtn.getToggleState());
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordNoteEventParam, noteEvtBtn.getToggleState());
			noteEvtBtn.setButtonText(noteEvtBtn.getToggleState() ? "NOTE EVENTS:On" : "NOTE EVENTS:Off");
		}
		else if (buttonThatWasClicked == &ctrlEvtBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::CC_EVENTS;
			setEventFilterValue((uint16_t)RecordEvents::MidiCC, ctrlEvtBtn.getToggleState());
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordMidiCCEventParam, ctrlEvtBtn.getToggleState());
			ctrlEvtBtn.setButtonText(ctrlEvtBtn.getToggleState() ? "MIDI CC EVENTS:On" : "MIDI CC EVENTS:Off");
		}
		else if (buttonThatWasClicked == &aftEvtBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::AFT_TOUCH_EVENT;
			setEventFilterValue((uint16_t)RecordEvents::AfterTouchCP, aftEvtBtn.getToggleState());
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordAfterTouchEventParam, aftEvtBtn.getToggleState());
			aftEvtBtn.setButtonText(aftEvtBtn.getToggleState() ? "AFT TOUCH EVENT:On" : "AFT TOUCH EVENT:Off");
		}
		else if (buttonThatWasClicked == &bendEvtBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::PITCH_BEND_EVENT;
			setEventFilterValue((uint16_t)RecordEvents::PitchBend, bendEvtBtn.getToggleState());
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordPitchBendEventParam, bendEvtBtn.getToggleState());
			bendEvtBtn.setButtonText(bendEvtBtn.getToggleState() ? "PITCH BEND EVENT:On" : "PITCH BEND EVENT:Off");
		}
		else if (buttonThatWasClicked == &polypEvtBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::POLY_P_EVENT;
			setEventFilterValue((uint16_t)RecordEvents::AfterTouchPP, polypEvtBtn.getToggleState());
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordPolyPEventParam, polypEvtBtn.getToggleState());
			polypEvtBtn.setButtonText(polypEvtBtn.getToggleState() ? "POLY-P EVENT:On" : "POLY-P EVENT:Off");
		}
		else if (buttonThatWasClicked == &prgmEvtBtn)
		{
			KeyFocusedItem = RecordMenuViewItemID::PROGRAM_CHANGE_EVENT;
			setEventFilterValue((uint16_t)RecordEvents::ProgramChange, prgmEvtBtn.getToggleState());
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingRecordPgmChangeEventParam, prgmEvtBtn.getToggleState());
			prgmEvtBtn.setButtonText(prgmEvtBtn.getToggleState() ? "PROGRAM CHANGE EVENT:On" : "PROGRAM CHANGE EVENT:Off");
		}
		recordOptCtl->enableKey(IgniteControlOptions::SAVE, true);
		recordOptCtl->enableKey(IgniteControlOptions::UNDO, true);
		recordConfigDataUpdated = true;
	}

	void IgniteRecord::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			recordConfigDataUpdated = false;
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
					popupPtr->setInfoText(String(" Save Record Configuration edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::SettingsRecordCnfgSave, 0);
							recordOptCtl->enableKey(IgniteControlOptions::SAVE, false);
							recordOptCtl->enableKey(IgniteControlOptions::UNDO, false);
							recordConfigDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}

			else if (option == IgniteControlOptions::UNDO)
			{
				if (recordConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, (paramId_t)SettingsRecordCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> recordParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsRecordCnfgParam::paramUndoListCmd;
					recordParamList.push_back(params);
					recordParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsRecordCnfg, recordParamList);
					if (recordParamList.size() == 1)
					{
						recordConfigDataUpdated = false;
						recordOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						recordOptCtl->enableKey(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgniteRecord::isEditing()
	{
		int index = 0;
		maxBars.IsEditing() ? index = 3 : 0;
		return index;
	}

	bool IgniteRecord::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = RecordMenuViewItemID::NO_FOCUS;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
		{
			PannelSendKey(false, param, KeyValue);
			if (option_handler_focus ==RECCONFIG_DETAIL)
			{
				option_handler_focus = RECCONFIG_OPTION;
			}
			else
			{
				option_handler_focus = RECCONFIG_DETAIL;
			}
			PannelSendKey(true, param, KeyValue);
			return true;
		}

		if (option_handler_focus == RECCONFIG_DETAIL)
		{
			if (KeyFocusedItem == RecordMenuViewItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				KeyFocusedItem = RecordMenuViewItemID::QUANTIZATION;

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
						KeyFocusedItem = (KeyFocusedItem + 1 >= RecordMenuViewItemID::FOCUS_MAX ? (RecordMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
						break;
					case FrontPannelParam::paramKey_RMOVERIGHT:
						KeyFocusedItem = (KeyFocusedItem - 1 <= RecordMenuViewItemID::NO_FOCUS ? (RecordMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
						break;
					case FrontPannelParam::paramKey_RETURN_NAV:
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
						break;
					case FrontPannelParam::paramRot_ROW:
						if (KeyValue == ROTARY_DIRECTION_RIGHT)
						{
							PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
							KeyFocusedItem = (KeyFocusedItem + RECORD_ROW_ITEMS >= RecordMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + RECORD_ROW_ITEMS) == (RecordMenuViewItemID::FOCUS_MAX) ? (RecordMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + RECORD_ROW_ITEMS);
							PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						}
						else
						{
							PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
							KeyFocusedItem = (KeyFocusedItem - RECORD_ROW_ITEMS <= RecordMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - RECORD_ROW_ITEMS);
							PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
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
			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				OptFocusedItem = (OptFocusedItem + 1 >= RecOptionsViewItemID::OP_FOCUS_MAX ? (RecOptionsViewItemID::OP_FOCUS_MAX) : OptFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				OptFocusedItem = (OptFocusedItem - 1 <= RecOptionsViewItemID::OP_NO_FOCUS ? (RecOptionsViewItemID::OP_NO_FOCUS + 1) : OptFocusedItem - 1);
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

	void IgniteRecord::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (option_handler_focus == RECCONFIG_DETAIL)
		{
			switch (RecordMenuView[KeyFocusedItem])
			{
			case QUANTIZATION:
				quantBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			/*case MTHRU:
				mthruBtn.FPKeyHandler(isFocuse, param, KeyValue);
				if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				{
					buttonClicked(&mthruBtn);
				}
				break;
			case FTS:
				ftsBtn.FPKeyHandler(isFocuse, param, KeyValue);
				if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				{
					buttonClicked(&ftsBtn);
				}
				break;
			case AUTO_ADD_BARS:
				autoAddBarBtn.FPKeyHandler(isFocuse, param, KeyValue);
				if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				{
					buttonClicked(&autoAddBarBtn);
				}
				break;*/
			case BAR_OVERWRITE:
				barOverwriteBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case NUMBER_OF_BARS:
				maxBars.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case NOTE_EVENTS:
				noteEvtBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case CC_EVENTS:
				ctrlEvtBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case AFT_TOUCH_EVENT:
				aftEvtBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case PITCH_BEND_EVENT:
				bendEvtBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case POLY_P_EVENT:
				polypEvtBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case PROGRAM_CHANGE_EVENT:
				prgmEvtBtn.FPKeyHandler(isFocuse, param, 0);
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
				recordOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			}
		}
	}
};
