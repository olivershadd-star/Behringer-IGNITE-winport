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

namespace ui
{

	////////////////////////////////////////////////
	//   Class: Ignite Step
	////////////////////////////////////////////////
	IgniteStep::IgniteStep(IgnitePattern* patternPtr, ClientPatternStepData& Data) : sData(Data)
	{
		_pPatternPtr = patternPtr;

		addNewNoteInList.makeVisibleAndAddListner(this);
		addNewNoteInList.setColour(juce::TextButton::buttonColourId, Theme::Instance().getColour(neutralGrey1));
		addNewNoteInList.setToggleable(false);
		addNewNoteInList.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		addNewNoteInList.setVisible(true);

		addNewEventInList.makeVisibleAndAddListner(this);
		addNewEventInList.setColour(juce::TextButton::buttonColourId, Theme::Instance().getColour(neutralGrey1));
		addNewEventInList.setToggleable(false);
		addNewEventInList.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		addNewEventInList.setVisible(true);

		addNewNoteEmpty.makeVisibleAndAddListner(this);
		addNewNoteEmpty.setColour(juce::TextButton::buttonColourId, Theme::Instance().getColour(neutralGrey1));
		addNewNoteEmpty.setToggleable(false);
		addNewNoteEmpty.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		addNewNoteEmpty.setVisible(false);
		addNewNoteEmpty.setBounds(0, 234, widthSongList, 44);

		addAndMakeVisible(view);
		addAndMakeVisible(container);

		_pStepOptCtl = IgniteControlOptions::GetAppOptInstance();
		_pStepOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		_pStepOptCtl->addOptCtlListener(this);

		helpInfoButtonA.makeVisibleAndAddListner(this);
		helpInfoButtonA.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		helpInfoButtonA.toFront(true);

		helpInfoButtonB.makeVisibleAndAddListner(this);
		helpInfoButtonB.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		helpInfoButtonB.toFront(true);

		view.setViewedComponent(&container, true);
		view.setBounds(0, 234, 1024, 200);
		view.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::all);
		view.setScrollBarThickness(15);
		view.setScrollBarsShown(true, false, true, false);
		container.setVisible(true);
		view.setVisible(true);

		noteLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		noteLable.setJustificationType(juce::Justification::centred);
		noteLable.setEditable(false, false, false);
		noteLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		noteLable.setColour(juce::Label::outlineColourId, Colours::white);
		noteLable.makeVisible(this);

		veloLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		veloLable.setJustificationType(juce::Justification::centred);
		veloLable.setEditable(false, false, false);
		veloLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		veloLable.setColour(juce::Label::outlineColourId, Colours::white);
		veloLable.makeVisible(this);

		offsetLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		offsetLable.setJustificationType(juce::Justification::centred);
		offsetLable.setEditable(false, false, false);
		offsetLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		offsetLable.setColour(juce::Label::outlineColourId, Colours::white);
		offsetLable.makeVisible(this);

		lenLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		lenLable.setJustificationType(juce::Justification::centred);
		lenLable.setEditable(false, false, false);
		lenLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		lenLable.setColour(juce::Label::outlineColourId, Colours::white);
		lenLable.makeVisible(this);

		emptyLable1.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		emptyLable1.setJustificationType(juce::Justification::centred);
		emptyLable1.setEditable(false, false, false);
		emptyLable1.setTextColour(Colours::grey);
		emptyLable1.makeVisible(this);

		emptyLable2.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		emptyLable2.setJustificationType(juce::Justification::centred);
		emptyLable2.setEditable(false, false, false);
		emptyLable2.setTextColour(Colours::grey);
		emptyLable2.makeVisible(this);

		emptyLable3.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		emptyLable3.setJustificationType(juce::Justification::centred);
		emptyLable3.setEditable(false, false, false);
		emptyLable3.setTextColour(Colours::grey);
		emptyLable3.makeVisible(this);

		emptyLable4.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		emptyLable4.setJustificationType(juce::Justification::centred);
		emptyLable4.setEditable(false, false, false);
		emptyLable4.setTextColour(Colours::grey);
		emptyLable4.makeVisible(this);

		prevBarButton.makeVisibleAndAddListner(this);
		nextBarButton.makeVisibleAndAddListner(this);
		addAndMakeVisible(&barButton);

		prevStepButton.makeVisibleAndAddListner(this);
		nextStepButton.makeVisibleAndAddListner(this);
		addAndMakeVisible(&stepButton);

		gateButton.makeVisibleAndAddListner(this);
		gateButton.setClickingTogglesState(false);
		gateButton.setToggleable(true);
		gateButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		gateButton.sethoverImages("pattern-selection-step-default-hover.png", "pattern-selection-step-active-hover.png", "");

		skipButton.makeVisibleAndAddListner(this);
		skipButton.setClickingTogglesState(false);
		skipButton.setToggleable(true);
		skipButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		skipButton.sethoverImages("pattern-selection-skip-default-hover.png", "pattern-selection-skip-active-hover.png", "");

		tieButton.makeVisibleAndAddListner(this);
		tieButton.setClickingTogglesState(false);
		tieButton.setToggleable(true);
		tieButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		tieButton.sethoverImages("pattern-selection-tie-default-hover.png", "pattern-selection-tie-active-hover.png", "");

		xposeDefeatButton.makeVisibleAndAddListner(this);
		xposeDefeatButton.setClickingTogglesState(false);
		xposeDefeatButton.setToggleable(true);
		xposeDefeatButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		xposeDefeatButton.sethoverImages("pattern-selection-transposedefeat-default-hover.png", "pattern-selection-transposedefeat-active-hover.png", "");

		noteListBtn.makeVisibleAndAddListner(this);
		noteListBtn.setClickingTogglesState(false);
		noteListBtn.setToggleable(true);
		noteListBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		noteListBtn.sethoverImages("pattern-step-toogle-notelist-default-hover.png", "pattern-step-toogle-notelist-active-hover.png", "");
		noteListBtn.setToggleState(true, dontSendNotification);

		eventListBtn.makeVisibleAndAddListner(this);
		eventListBtn.setClickingTogglesState(false);
		eventListBtn.setToggleable(true);
		eventListBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		eventListBtn.sethoverImages("pattern-step-toogle-eventlist-default-hover.png", "pattern-step-toogle-eventlist-active-hover.png", "");

		prevBarButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		barButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		nextBarButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		prevStepButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		stepButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		nextStepButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		barLableBox.items.add(FlexItem(barButton).withMargin(0).withFlex(1));
		stepLableBox.items.add(FlexItem(stepButton).withMargin(0).withFlex(3));
		for (auto i = 0; i < 128; i++)
		{
			IgniteStepNoteList* row;
			row = new IgniteStepNoteList(stepNotelist.size(), sData, _pPatternPtr, this);
			stepNotelist.add(row);

			IgniteStepEventList* eventRow;
			eventRow = new IgniteStepEventList(stepEventlist.size(), sData, _pPatternPtr, this);
			stepEventlist.add(eventRow);
		}
	}

	IgniteStep::~IgniteStep()
	{
	}

	void IgniteStep::setActiveNoteRow(int index, bool force_update)
	{
		if ((activeNoteRow == index) && !force_update)
			return;

		(activeNoteRow < 0) ? activeNoteRow = 0 : activeNoteRow = (uint8_t)index;

		auto numNotes = (int)_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::NODE_COUNT, editBar, editStep);

		// Highlist selected note row.
		for (auto i = 0; i < numNotes; i++)
			stepNotelist[i]->highlight(false);

		stepNotelist[activeNoteRow]->highlight(true);
		DBG("Active note row = " + String(activeNoteRow));

	}

	void IgniteStep::setActiveEventRow(int index, bool force_update)
	{
		if ((activeEventRow == index) && !force_update)
			return;

		activeEventRow = index;

		// Highlist selected event row.
		for (auto eventIndex = 0; eventIndex < currentStepData->auxList.size(); eventIndex++)
			stepEventlist[eventIndex]->highlight(false);

		stepEventlist[activeEventRow]->highlight(true);
	}

	void IgniteStep::updateAccidentals(ClientPatternStepData* stepData, bool state)
	{
		for (auto noteIndex = 0; noteIndex < stepData->nodeList.size(); noteIndex++)
			stepNotelist[noteIndex]->updateAccidentals(state);
	}

	void IgniteStep::updateStepData()
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__));

		auto& gPatternRef = gPatterns.getReference(_pPatternPtr->getSelected());
		editBar = gPatternRef.barIndex;

		int index = 0;
		auto numNotes = (int)_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::NODE_COUNT, editBar, editStep);
		enableControlButton(IgniteControlOptions::DEL, true);

		currentStepData = _pPatternPtr->getStepData(editBar, editStep);
		String bar_lable = "BAR " + String(editBar + 1) + "/" + String((int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM) + 1);
		auto currentStepId = (editStep + 1);
		String stepLable = "STEP " + String((int)currentStepId) + "/" + String((int)_pPatternPtr->getBarData(mt::Ignite::barDataIndex::NUM_STEPS, editBar));
		bool enable = _pPatternPtr->getStepData(mt::Ignite::stepDataIndex::GATE_STATUS, editBar, editStep);

		barButton.setButtonText(bar_lable);
		stepButton.setButtonText(stepLable);
		gateButton.setToggleState(enable, dontSendNotification);
		skipButton.setToggleState((bool)_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::SKIP_STATUS, editBar, editStep), dontSendNotification);
		xposeDefeatButton.setToggleState((bool)_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::TRANSPOSE_DEFEAT_STATUS, editBar, editStep), dontSendNotification);
		tieButton.setToggleState((bool)_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::TIE_STATUS, editBar, editStep), dontSendNotification);

		container.removeAllChildren();
		container.setVisible(false);
		view.setVisible(false);

		addNewNoteInList.setVisible(false);
		addNewNoteEmpty.setVisible(false);

		int noteIndex = 0;
		int eventIndex = 0;
		if (noteListBtn.getToggleState())
		{
			addNewNoteInList.setVisible(true);
			if (numNotes)
			{
				if (emptyLable1.isVisible())
				{
					emptyLable1.setVisible(false);
					emptyLable2.setVisible(false);
					emptyLable3.setVisible(false);
					emptyLable4.setVisible(false);
				}

				for (auto& j : currentStepData->nodeList)
				{
					stepNotelist[noteIndex]->refreshStepNoteListRowUI(j.second.begin()->second);
					stepNotelist[noteIndex]->setBounds(0, ((heightSongList + 4) * index++), widthSongList, 44);

					stepNotelist[noteIndex]->onMouseDown = [this](IgniteStepNoteList* Row)
					{
						setActiveNoteRow((Row->getSerialNumber()), false);
					};
					container.addAndMakeVisible(stepNotelist[noteIndex++]);
				}
				if (activeNoteRow >= currentStepData->nodeList.size() && currentStepData->nodeList.size() > 0)
				{
					activeNoteRow = (uint8_t)currentStepData->nodeList.size() - 1;
				}
				setActiveNoteRow(activeNoteRow, true);
			}
			else
			{
				emptyLable1.setVisible(true);
				emptyLable2.setVisible(true);
				emptyLable3.setVisible(true);
				emptyLable4.setVisible(true);
				enableControlButton(IgniteControlOptions::DEL, false);
				addNewNoteEmpty.setVisible(true);
				noteIndex++;
			}
			addNewNoteInList.setBounds(0, ((heightSongList + 4) * noteIndex++), widthSongList, 44);
			container.addAndMakeVisible(addNewNoteInList);

			// Set overall view container size....
			container.setSize(widthScreen - 20, ((noteIndex + 1) * (heightSongContainer + 4)));
			container.setVisible(true);
			view.setVisible(true);
		}
		else
		{
			addNewEventInList.setVisible(true);
			if (currentStepData->auxList.size())
			{
				if (emptyLable1.isVisible())
				{
					emptyLable1.setVisible(false);
					emptyLable2.setVisible(false);
					emptyLable3.setVisible(false);
					emptyLable4.setVisible(false);
				}

				for (eventIndex = 0; eventIndex < currentStepData->auxList.size(); eventIndex++)
				{
					stepEventlist[eventIndex]->refreshStepEventListRowUI(currentStepData->auxList[eventIndex]);
					stepEventlist[eventIndex]->setBounds(0, ((heightSongList + 4) * index++), widthSongList, 44);

					stepEventlist[eventIndex]->onMouseDown = [this](IgniteStepEventList* Row)
					{
						setActiveEventRow(Row->getSerialNumber(), false);
					};
					container.addAndMakeVisible(stepEventlist[eventIndex]);
				}

				if (activeEventRow >= currentStepData->auxList.size())
				{
					activeEventRow = (int)currentStepData->auxList.size() - 1;
					activeEventNumber = currentStepData->auxList[activeEventRow].data1;
				}
				setActiveEventRow(activeEventNumber, true);
			}
			else
			{
				emptyLable1.setVisible(true);
				emptyLable2.setVisible(true);
				emptyLable3.setVisible(true);
				emptyLable4.setVisible(true);
				enableControlButton(IgniteControlOptions::DEL, false);
				addNewNoteEmpty.setVisible(true);
				eventIndex++;
			}
			addNewEventInList.setBounds(0, ((heightSongList + 4) * eventIndex++), widthSongList, 44);
			container.addAndMakeVisible(addNewEventInList);

			// Set overall view container size....
			container.setSize(widthScreen - 20, ((eventIndex + 1) * (heightSongContainer + 4)));
			container.setVisible(true);
			view.setVisible(true);
		}
	}

	void IgniteStep::getNextStepAndUpdate(bool direction)
	{
		if (direction)
		{
			if (editStep < 15)
				editStep++;
		}
		else
		{
			if (editStep > 0)
				editStep--;
		}
		DBG("EDITBAR: EDITSTEP: " + String(editBar) + ":" + String(editStep));
		updateStepData();
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)getPrevStepIndex(), fpLEDPattern::EN_LED_PATT_OFF);
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + editStep), fpLEDPattern::EN_LED_PATT_ON);
		setPrevStepIndex((paramId_t)FrontPannelParam::paramKey_TRACKROTARY1 + editStep);
	}

	void IgniteStep::getNextBarAndUpdate(bool direction)
	{
		int num_bars = _pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM);
		if (direction)
		{
			if (editBar < num_bars)
				editBar++;
		}
		else
		{
			if (editBar > 0)
				editBar--;
		}

		auto& gPatternRef = gPatterns.getReference(_pPatternPtr->getSelected());
		gPatternRef.barIndex = editBar;
		editStep = 0;
		DBG("EDITBAR: EDITSTEP: " + String(editBar) + ":" + String(editStep));
		updateStepData();
		_pPatternPtr->setFpModeLedState();
	}

	void IgniteStep::labelTextChanged(Label* labelThatHasChanged)
	{
	}

	void IgniteStep::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		auto theme = Theme::Instance();

		if (buttonThatWasClicked == &gateButton)
		{
			keyFocusedItem = stepViewItemID::GATE;
			if (gateButton.getToggleState())
				gateButton.setToggleState(false, dontSendNotification);
			else
				gateButton.setToggleState(true, dontSendNotification);

			_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::GATE_STATUS, editBar, editStep, gateButton.getToggleState(), false);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		}
		else if (buttonThatWasClicked == &skipButton)
		{
			keyFocusedItem = stepViewItemID::SKIP;
			if (skipButton.getToggleState())
				skipButton.setToggleState(false, dontSendNotification);
			else
				skipButton.setToggleState(true, dontSendNotification);

			_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::SKIP_STATUS, editBar, editStep, skipButton.getToggleState(), false);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		}
		else if (buttonThatWasClicked == &tieButton)
		{
			keyFocusedItem = stepViewItemID::TIE;
			if (tieButton.getToggleState())
				tieButton.setToggleState(false, dontSendNotification);
			else
				tieButton.setToggleState(true, dontSendNotification);

			_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::TIE_STATUS, editBar, editStep, tieButton.getToggleState(), false);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		}
		else if (buttonThatWasClicked == &xposeDefeatButton)
		{
			keyFocusedItem = stepViewItemID::XPOSE;
			if (xposeDefeatButton.getToggleState())
				xposeDefeatButton.setToggleState(false, dontSendNotification);
			else
				xposeDefeatButton.setToggleState(true, dontSendNotification);
			_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::TRANSPOSE_DEFEAT_STATUS, editBar, editStep, xposeDefeatButton.getToggleState(), false);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		}
		else if (buttonThatWasClicked == &nextStepButton)
		{
			keyFocusedItem = stepViewItemID::STEP_RIGHT;
			getNextStepAndUpdate(true);
		}
		else if (buttonThatWasClicked == &prevStepButton)
		{
			keyFocusedItem = stepViewItemID::STEP_LEFT;
			getNextStepAndUpdate(false);
		}
		else if (buttonThatWasClicked == &nextBarButton)
		{
			keyFocusedItem = stepViewItemID::BAR_RIGHT;
			getNextBarAndUpdate(true);
		}
		else if (buttonThatWasClicked == &prevBarButton)
		{
			keyFocusedItem = stepViewItemID::BAR_LEFT;
			getNextBarAndUpdate(false);
		}
		else if ((buttonThatWasClicked == &addNewNoteInList))
		{
			_pPatternPtr->addNextNote(editBar, editStep);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			_pPatternPtr->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
			addNewNoteInList.setToggleState(false, dontSendNotification);
		}
		else if ((buttonThatWasClicked == &addNewEventInList))
		{
			_pPatternPtr->addStepEvent(editBar, editStep);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			_pPatternPtr->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
			addNewEventInList.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &noteListBtn)
		{
			setListBtnText(true);
			noteListBtn.setToggleState(true, dontSendNotification);
			eventListBtn.setToggleState(false, dontSendNotification);
			_pPatternPtr->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
			resized();
		}
		else if (buttonThatWasClicked == &eventListBtn)
		{
			setListBtnText(false);
			eventListBtn.setToggleState(true, dontSendNotification);
			noteListBtn.setToggleState(false, dontSendNotification);
			_pPatternPtr->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
			resized();
		}
		else if (buttonThatWasClicked == &helpInfoButtonA)
		{
			CommonHelpInfoPopUp* ptr = new CommonHelpInfoPopUp("DATA_A", 604, 360);
			String helpInfoA = " DATA_A for Event Type \n For MIDI CC: CC Number\n For Pitch Bend : value(0 to 16383)\n For PGM CHANGE : Program Number\n For After Touch Poly Pressure : Note Number\n For After Touch Channel Pressure : Pressure(0 to 127)";
			ptr->setInfoText(helpInfoA);
			ptr->show();
		}
		else if (buttonThatWasClicked == &helpInfoButtonB)
		{
			CommonHelpInfoPopUp* ptr = new CommonHelpInfoPopUp("DATA_B", 604, 360);
			String helpInfoB = " DATA_B for Event Type \n For MIDI CC: CC Value\n For Pitch Bend: NA\n For PGM CHANGE: NA\n For After Touch Poly Pressure: Pressure (0 to 127)\n For After Touch Channel Pressure: NA";
			ptr->setInfoText(helpInfoB);
			ptr->show();
		}
	}

	void IgniteStep::setListBtnText(bool state)
	{
		if (state)
		{
			noteLable.setText("NOTE", dontSendNotification);
			veloLable.setText("VELOCITY", dontSendNotification);
			offsetLable.setText("OFFSET", dontSendNotification);
			lenLable.setText("LENGTH", dontSendNotification);
		}
		else
		{
			noteLable.setText("EVENT", dontSendNotification);
			veloLable.setText("OFFSET", dontSendNotification);
			offsetLable.setText("DATA_A", dontSendNotification);
			lenLable.setText("DATA_B", dontSendNotification);
		}
	}

	void IgniteStep::paint(juce::Graphics& g)
	{
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-steppattern-default.png"));
		Image activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-steppattern-default-hover.png"));

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-steppattern-default.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-steppattern-default-hover.png"));
		Image defaultImage1 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-left-pattern-default.png"));
		Image activeImage1 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-left-pattern-default-hover.png"));
		Image defaultImage2 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-right-pattern-default.png"));
		Image activeImage2 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-right-pattern-default-hover.png"));
		Image Draw;

		Draw = (barButton.isMouseOver() || barButton.isFocused) ? activeImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 0, 0, 498, 50 }, RectanglePlacement::centred);

		Draw = (prevBarButton.isMouseOver() || prevBarButton.isFocused) ? activeImage1 : defaultImage1;
		g.drawImage(Draw, ui::Rectangle<float>{ 0, 9, 24, 32 }, RectanglePlacement::centred);

		Draw = (nextBarButton.isMouseOver() || nextBarButton.isFocused) ? activeImage2 : defaultImage2;
		g.drawImage(Draw, ui::Rectangle<float>{ 474, 9, 24, 32 }, RectanglePlacement::centred);

		Draw = (stepButton.isMouseOver() || stepButton.isFocused) ? activeImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 506, 0, 498, 50 });

		Draw = (prevStepButton.isMouseOver() || prevStepButton.isFocused) ? activeImage1 : defaultImage1;
		g.drawImage(Draw, ui::Rectangle<float>{ 506, 9, 24, 32 });

		Draw = (nextStepButton.isMouseOver() || nextStepButton.isFocused) ? activeImage2 : defaultImage2;
		g.drawImage(Draw, ui::Rectangle<float>{ 982, 9, 24, 32 });

		if (!noteListBtn.getToggleState() && !emptyLable1.isVisible())
		{
			Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("question-circle.png"));
			Image HoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("question-circle-hover.png"));
			g.drawImage((helpInfoButtonA.isMouseOver() || helpInfoButtonA.isFocused) ? HoverImage : Draw, ui::Rectangle<float>{ 685, 199, 21, 21 }, RectanglePlacement::centred);
			g.drawImage((helpInfoButtonB.isMouseOver() || helpInfoButtonB.isFocused) ? HoverImage : Draw, ui::Rectangle<float>{ 920, 199, 21, 21 }, RectanglePlacement::centred);
		}
	}

	void IgniteStep::resized()
	{
		barLableBox.performLayout(ui::Rectangle(0, 0, 498, 50));
		prevBarButton.setBounds(0, 4, 24, 42);
		nextBarButton.setBounds(474, 4, 24, 42);
		prevBarButton.toFront(true);
		nextBarButton.toFront(true);

		stepLableBox.performLayout(ui::Rectangle{ 506, 0, 498, 50 });
		prevStepButton.setBounds(506, 4, 24, 42);
		nextStepButton.setBounds(982, 4, 24, 42);
		prevStepButton.toFront(true);
		nextStepButton.toFront(true);

		tieButton.setBounds(0, 58, 245, 70);
		xposeDefeatButton.setBounds(253, 58, 245, 70);
		skipButton.setBounds(506, 58, 245, 70);
		gateButton.setBounds(759, 58, 245, 70);

		noteListBtn.setBounds(0, 138, 500, 50);
		eventListBtn.setBounds(504, 138, 500, 50);

		if (emptyLable1.isVisible())
		{
			emptyLable1.setBounds(12, 241, 250, 30);
			emptyLable2.setBounds(262, 241, 250, 30);
			emptyLable3.setBounds(512, 241, 250, 30);
			emptyLable4.setBounds(762, 241, 250, 30);
			noteLable.setBounds(12, 195, 250, 30);
			veloLable.setBounds(262, 195, 250, 30);
			offsetLable.setBounds(512, 195, 250, 30);
			lenLable.setBounds(762, 195, 250, 30);
			helpInfoButtonA.setBounds(0, 0, 0, 0);
			helpInfoButtonB.setBounds(0, 0, 0, 0);
			noteLable.setAlpha(0.3f);
			veloLable.setAlpha(0.3f);
			offsetLable.setAlpha(0.3f);
			lenLable.setAlpha(0.3f);
		}
		else
		{
			noteLable.setAlpha(1.0f);
			veloLable.setAlpha(1.0f);
			offsetLable.setAlpha(1.0f);
			lenLable.setAlpha(1.0f);
			if (noteListBtn.getToggleState())
			{
				noteLable.setBounds(12, 195, 250, 30);
				veloLable.setBounds(262, 195, 250, 30);
				offsetLable.setBounds(512, 195, 250, 30);
				lenLable.setBounds(762, 195, 250, 30);
				helpInfoButtonA.setBounds(0, 0, 0, 0);
				helpInfoButtonB.setBounds(0, 0, 0, 0);
			}
			else
			{
				noteLable.setBounds(75, 195, 200, 30);
				veloLable.setBounds(305, 195, 250, 30);
				offsetLable.setBounds(590, 195, 100, 30);
				lenLable.setBounds(830, 195, 100, 30);
				helpInfoButtonA.setBounds(685, 199, 21, 21);
				helpInfoButtonB.setBounds(920, 199, 21, 21);
			}
		}
	}

	int IgniteStep::isEditing()
	{
		int index = 0;
		return index;
	}

	void IgniteStep::handleCommandMessage(int id)
	{
		if (id == 1)
			buttonClicked(&addNewNoteInList);
		else if (id == 2)
			buttonClicked(&addNewEventInList);
		else if (id == 3)
			setActiveNoteRow(noteListFocused, false);
		else if (id == 4)
			setActiveEventRow(eventListFocused, false);
	}

	void IgniteStep::handleNoteList(paramId_t param, uint32_t keyValue)
	{
		if (noteListBtn.getToggleState() == true)
		{
			auto numNotes = (int)_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::NODE_COUNT, editBar, editStep);
			if (noteListFocused < 0)
			{
				noteListFocused = 0;
			}
			else
			{
				if (!addNewNoteInListHighlighted)
					stepNotelist[noteListFocused]->setFocus(false, false);

				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:

					if (noteListFocused + 1 >= numNotes && addNewNoteInList.isVisible())
					{
						addNewNoteInList.setState(Button::ButtonState::buttonOver);
						noteListFocused = (numNotes - 1);
						addNewNoteInListHighlighted = true;
					}
					else
						noteListFocused = jmin<int>(jmax<int>((noteListFocused + 1), 0), (numNotes - 1));

					if ((noteListFocused) * 52 > (view.getViewArea().getHeight() - 52))
						view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() + 52);

					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					if (addNewNoteInListHighlighted)
					{
						addNewNoteInList.setState(Button::ButtonState::buttonNormal);
						addNewNoteInListHighlighted = false;
						noteListFocused = numNotes == 0 ? numNotes : (numNotes - 1);
					}
					else
						noteListFocused = jmin<int>(jmax<int>((noteListFocused - 1), 0), numNotes == 0 ? numNotes : (numNotes - 1));

					if ((noteListFocused - 1) * 52 <= (view.getViewArea().getHeight()))
						view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() - 52);

					break;

				case FrontPannelParam::paramKey_RSELECT:
					if (addNewNoteInListHighlighted)
						this->postCommandMessage(1);
					else
						this->postCommandMessage(3);
					break;
				}
				if (!addNewNoteInListHighlighted)
					stepNotelist[noteListFocused]->setFocus(true, false);
				repaint();
			}
		}
	}

	void IgniteStep::handleEventList(paramId_t param, uint32_t keyValue)
	{
		int numEvents = (int)currentStepData->auxList.size();
		if (eventListFocused < 0)
		{
			eventListFocused = 0;
		}
		else
		{
			stepEventlist[eventListFocused]->setFocus(false, false);

			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:

				if (eventListFocused + 1 >= numEvents && addNewEventInList.isVisible())
				{
					addNewEventInList.setState(Button::ButtonState::buttonOver);
					eventListFocused = (numEvents - 1);
					addNewEventInListHighlighted = true;
				}
				else
					eventListFocused = jmin<int>(jmax<int>((eventListFocused + 1), 0), (numEvents - 1));

				if ((eventListFocused) * 52 > (view.getViewArea().getHeight() - 52))
					view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() + 52);

				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				if (addNewEventInListHighlighted)
				{
					addNewEventInList.setState(Button::ButtonState::buttonNormal);
					addNewEventInListHighlighted = false;
					eventListFocused = numEvents == 0 ? numEvents : (numEvents - 1);
				}
				else
					eventListFocused = jmin<int>(jmax<int>((eventListFocused - 1), 0), numEvents == 0 ? numEvents : (numEvents - 1));

				if ((eventListFocused - 1) * 52 <= (view.getViewArea().getHeight()))
					view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() - 52);

				break;

			case FrontPannelParam::paramKey_RSELECT:
				if (addNewEventInListHighlighted)
					this->postCommandMessage(2);
				else
					this->postCommandMessage(4);
				break;
			}
			if (!addNewEventInListHighlighted)
				stepEventlist[eventListFocused]->setFocus(true, false);
			repaint();
		}
	}

	bool IgniteStep::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		bool setfocus = true;
		int EditItem = stepViewItemID::NO_FOCUS;
		bool isStepHandled = false;
		FrountPannelRef = FrountPannel::GetFrountPannelInstance();
		auto numNotes = (int)_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::NODE_COUNT, editBar, editStep);
		auto numEvents = currentStepData->auxList.size();

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramRot_ROW:
			if ((keyValue == ROTARY_LEFT || keyValue == ROTARY_FASTLEFT || keyValue == ROTARY_SUPERFASTLEFT))
			{
				if (noteListBtn.getToggleState() == true)
					handleNoteList((paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, keyValue);
				else if (eventListBtn.getToggleState() == true)
					handleEventList((paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, keyValue);
			}
			else if ((keyValue == ROTARY_RIGHT || keyValue == ROTARY_FASTRIGHT || keyValue == ROTARY_SUPERFASTRIGHT))
			{
				if (noteListBtn.getToggleState() == true)
					handleNoteList((paramId_t)FrontPannelParam::paramKey_RMOVELEFT, keyValue);
				else if (eventListBtn.getToggleState() == true)
					handleEventList((paramId_t)FrontPannelParam::paramKey_RMOVELEFT, keyValue);
			}
			isStepHandled = true;
			break;
		case FrontPannelParam::paramKey_ROTARYROW:
			if (noteListBtn.getToggleState() == true)
				handleNoteList((paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			else if (eventListBtn.getToggleState() == true)
				handleEventList((paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			isStepHandled = true;
			break;
		case FrontPannelParam::paramRot_PADROT3:
		case FrontPannelParam::paramRot_PADROT4:
		case FrontPannelParam::paramRot_PADROT5:
		case FrontPannelParam::paramRot_PADROT6:
		case FrontPannelParam::paramRot_PADROT7:
			if (noteListBtn.getToggleState() == true && numNotes != 0)
				stepNotelist[activeNoteRow]->pannelKeyHandler(param, keyValue);
			else if (eventListBtn.getToggleState() == true && numEvents != 0)
				stepEventlist[activeEventRow]->pannelKeyHandler(param, keyValue);
			isStepHandled = true;
			break;
		case FrontPannelParam::paramKey_INSERT:
			if (noteListBtn.getToggleState() == true)
				this->postCommandMessage(1);
			else if (eventListBtn.getToggleState() == true)
				this->postCommandMessage(2);
			isStepHandled = true;
			break;
		case FrontPannelParam::paramKey_DELETE:
			_pStepOptCtl->PannelKeyHandler((paramId_t)FrontPannelParam::paramKey_DELETE, keyValue);
			isStepHandled = true;
			break;
		case FrontPannelParam::paramKey_ROTARYBAR:
			if ((keyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed))
				getNextBarAndUpdate(true);
			isStepHandled = true;
			break;
		case FrontPannelParam::paramRot_BAR:
			if ((keyValue == ROTARY_LEFT || keyValue == ROTARY_FASTLEFT || keyValue == ROTARY_SUPERFASTLEFT))
				getNextStepAndUpdate(true);
			else if ((keyValue == ROTARY_RIGHT || keyValue == ROTARY_FASTRIGHT || keyValue == ROTARY_SUPERFASTRIGHT))
				getNextStepAndUpdate(false);
			isStepHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKROTARY3:
		case FrontPannelParam::paramKey_TRACKROTARY4:
		case FrontPannelParam::paramKey_TRACKROTARY5:
		case FrontPannelParam::paramKey_TRACKROTARY6:
		case FrontPannelParam::paramKey_TRACKROTARY7:
		case FrontPannelParam::paramKey_RETURN_NAV:
			if ((FrountPannelRef->getShiftKeyStatus() == true))
			{
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)prevStepIndex, fpLEDPattern::EN_LED_PATT_OFF);
				editStep = (param - (paramId_t)FrontPannelParam::paramKey_TRACKROTARY1);
				updateStepData();
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)param, fpLEDPattern::EN_LED_PATT_ON);
				prevStepIndex = param;
			}
			else
			{
				if ((noteListBtn.getToggleState() == true) && numNotes != 0)
					stepNotelist[activeNoteRow]->pannelKeyHandler(param, keyValue);
				else if (eventListBtn.getToggleState() == true && numEvents != 0)
					stepEventlist[activeEventRow]->pannelKeyHandler(param, keyValue);
			}
			isStepHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKROTARY1:
		case FrontPannelParam::paramKey_TRACKROTARY2:
		case FrontPannelParam::paramKey_TRACKROTARY8:
		case FrontPannelParam::paramKey_TRACKROTARY9:
		case FrontPannelParam::paramKey_TRACKROTARY10:
		case FrontPannelParam::paramKey_TRACKROTARY11:
		case FrontPannelParam::paramKey_TRACKROTARY12:
		case FrontPannelParam::paramKey_TRACKROTARY13:
		case FrontPannelParam::paramKey_TRACKROTARY14:
		case FrontPannelParam::paramKey_TRACKROTARY15:
		case FrontPannelParam::paramKey_TRACKROTARY16:
			if ((FrountPannelRef->getShiftKeyStatus() == true))
			{
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)prevStepIndex, fpLEDPattern::EN_LED_PATT_OFF);
				editStep = (param - (paramId_t)FrontPannelParam::paramKey_TRACKROTARY1);
				updateStepData();
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)param, fpLEDPattern::EN_LED_PATT_ON);
				prevStepIndex = param;
				isStepHandled = true;
			}
			break;
		}
		if (isStepHandled)
			return true;

		if (keyFocusedItem == stepViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			keyFocusedItem = stepViewItemID::BAR_LEFT;
		}
		else
		{
			EditItem = isEditing();
			if (EditItem)
			{
				if (keyFocusedItem != EditItem)
				{
					pannelSendKey(false, param, keyValue);
					keyFocusedItem = EditItem;
				}
				setfocus = true;
			}
			else
			{
				pannelSendKey(false, param, keyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= stepViewItemID::FOCUS_MAX ? (stepViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= stepViewItemID::NO_FOCUS ? (stepViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
					break;
				}
			}
		}
		if (setfocus)
		{
			pannelSendKey(true, param, keyValue);
		}
		return true;
	}

	void IgniteStep::pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue)
	{
		switch (stepView[keyFocusedItem])
		{
		case BAR_LEFT:
			prevBarButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case BAR_RIGHT:
			nextBarButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case STEP_LEFT:
			prevStepButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case STEP_RIGHT:
			nextStepButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case GATE:
			gateButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case SKIP:
			skipButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case XPOSE:
			xposeDefeatButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case TIE:
			tieButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case NOTE_LIST:
			noteListBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case EVENT_LIST:
			eventListBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		default:
			break;
		}
		repaint();
	}

	void IgniteStep::handleDeleteEvent()
	{
		if (isVisible())
		{
			if (noteListBtn.getToggleState())
			{
				_pPatternPtr->delNote(editBar, editStep, stepNotelist[activeNoteRow]->getCurrentNoteNumber(), true);
			}
			else
			{
				_pPatternPtr->delStepEvent(activeEventRow, editBar, editStep);
			}
			_pPatternPtr->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
		}
	}
};
