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
	//   Class: IgniteStepNoteList
	////////////////////////////////////////////////

	IgniteStepNoteList::IgniteStepNoteList(int SerialNumber, ClientPatternStepData& stepData, IgnitePattern* patternPtr, IgniteStep* stepPtr) : data(stepData)
	{
		_pPatternPtr = patternPtr;
		_pStepPtr = stepPtr;
		srNo.makeVisible(this);
		srNo.setText(String(SerialNumber), juce::dontSendNotification);
		srNo.addMouseListener(this, false);

		addAndMakeVisible(noteListBox);
		noteListBox.updateListOptions(mt::Ignite::midiNoteNamesSharps);
		noteListBox.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		noteListBox.setValueColour(Theme::Instance().getColour(customOrange));
		noteListBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		noteListBox.setTextColour(Theme::Instance().getColour(customBlue4));
		noteListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,567 });
		noteListBox.setSelected(48);

		noteLen.makeVisibleAndAddListner(this);
		noteLen.showTitleAndBorder(false);
		noteLen.setClickingTogglesState(false);
		noteLen.setTextColour(Theme::Instance().getColour(customOrange));
		noteLen.setButtonText("");
		noteLen.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		noteLen.toFront(true);

		velocomp.makeVisible(this);
		velocomp.setDisplayTitle(false);
		velocomp.setJustificationType(juce::Justification::centred);
		velocomp.setTextColour(Theme::Instance().getColour(customOrange));
		velocomp.addMouseListener(this, false);

		delaycomp.makeVisible(this);
		delaycomp.setDisplayTitle(false);
		delaycomp.setJustificationType(juce::Justification::centred);
		delaycomp.setTextColour(Theme::Instance().getColour(customOrange));
		delaycomp.addMouseListener(this, false);

		lengthValue.makeVisible(this);
		lengthValue.setTextColour(Theme::Instance().getColour(customOrange));
		lengthValue.setEditable(false, false, false);
		lengthValue.setJustificationType(juce::Justification::centred);
		lengthValue.toBehind(&noteLen);

		_pPatternBarLengthComp = new PatternBarLengthCtl;
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();

		velocomp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pStepPtr->setActiveNote(noteListBox.getSelectedIndex());
			currentNode = noteListBox.getSelectedIndex();
			if ((int)_pPatternPtr->getNodeData(mt::Ignite::nodeDataIndex::VELO, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode) != value)
			{
				_pPatternPtr->setNodeData(mt::Ignite::nodeDataIndex::VELO, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode, (uint8_t)value, false);
				if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{
					_pPatternPtr->setPatternDataUpdateStatus(true);
					_pPatternPtr->updatePatternEditIndication();
					_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				}
			}
		};

		delaycomp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pStepPtr->setActiveNote(noteListBox.getSelectedIndex());
			currentNode = noteListBox.getSelectedIndex();
			value = value + 16;
			if ((int)_pPatternPtr->getNodeData(mt::Ignite::nodeDataIndex::DELAY, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode) != value)
			{
				_pPatternPtr->setNodeData(mt::Ignite::nodeDataIndex::DELAY, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode, (uint8_t)value, false);
				if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{
					_pPatternPtr->setPatternDataUpdateStatus(true);
					_pPatternPtr->updatePatternEditIndication();
					_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				}
			}
		};

		noteListBox.onDailogTrigger = [this](bool state)
		{
			_pStepPtr->setActiveNote(noteListBox.getSelectedIndex());
			currentNode = noteListBox.getSelectedIndex();
		};

		noteListBox.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			auto& gPatternRef = gPatterns.getReference(_pPatternPtr->getSelected());
			auto& stepDataIter = gPatternRef.enginePatternData.BarDataList.at((const unsigned char)_pStepPtr->getEditBar()).StepDataList.at((const unsigned char)_pStepPtr->getEditStep());

			if (currentNode != value)
			{
				if (stepDataIter.nodeList.count((uint8_t)value) == 0)
				{
					_pPatternPtr->delNote(_pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode);
					_pPatternPtr->addNote(_pStepPtr->getEditBar(), _pStepPtr->getEditStep(), value);
					_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::NODE_ID, (uint8_t)value, false);
					currentNode = value;
					if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
					{
						_pPatternPtr->setPatternDataUpdateStatus(true);
						_pPatternPtr->updatePatternEditIndication();
						_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
						_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
					}
				}
				else if (stepDataIter.nodeList.count((uint8_t)value) == 1)
				{
					_pInfoWindow->setTextandShow("Note already inserted");
					_pPatternPtr->delNote(_pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode);
					_pPatternPtr->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
				}
			}
		};

		velocomp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		delaycomp.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	IgniteStepNoteList::~IgniteStepNoteList()
	{}

	void IgniteStepNoteList::mouseUp(const MouseEvent& event)
	{
		if (onMouseDown)
			onMouseDown(this);
	}

	int IgniteStepNoteList::getCurrentNoteNumber()
	{
		return noteListBox.getSelectedIndex();
	}

	void IgniteStepNoteList::highlight(bool State)
	{
		isHighlighted = State;
		repaint();
	}

	int IgniteStepNoteList::getSerialNumber()
	{
		return srNo.getText().getIntValue();
	}

	void IgniteStepNoteList::updateAccidentals(bool state)
	{
		if (state)
			noteListBox.updateListOptions(mt::Ignite::midiNoteNamesFlats);
		else
			noteListBox.updateListOptions(mt::Ignite::midiNoteNamesSharps);
	}

	void IgniteStepNoteList::refreshStepNoteListRowUI(ClientPatternNodeData noteData)
	{
		int ticks = noteData.lenInTicks;
		int stepLen = noteData.lenInSteps;
		String tickData = ((ticks >= 10) ? (tick = String(ticks)) : String((tick = "0" + String(ticks))));
		String stepData = ((stepLen >= 10) ? (step = String(stepLen)) : String((step = "0" + String(stepLen))));
		String lenData = stepData + ":" + tickData;
		currentNode = noteListBox.getSelectedIndex();
		_pPatternBarLengthComp->updateTickRange(_pPatternPtr->getTickRange().min, _pPatternPtr->getTickRange().max);

		if (stepLen != lengthHoldId)
		{
			/* TODO: Fix Length popup and handling */
			lengthValue.setText(lenData, dontSendNotification);
			_pPatternBarLengthComp->setSliderValue(stepLen, ticks);
		}
		else
			lengthValue.setText("HOLD", dontSendNotification);

		delaycomp.setRange(_pPatternPtr->getDelayRange().min, _pPatternPtr->getDelayRange().max, 1);
		lengthValue.setText(String(noteData.lenInSteps)+":"+ String(noteData.lenInTicks), dontSendNotification);
		noteListBox.setSelected(noteData.note);
		velocomp.setText(String((int)noteData.velocity), dontSendNotification);
		delaycomp.setText(String((int)noteData.offset), dontSendNotification);
		_pStepPtr->setActiveNote(currentNode);
	}

	void IgniteStepNoteList::updateLengthData()
	{
		mt::Ignite::_track::patternLenInfo patternLenData(_pPatternBarLengthComp->getPatternLenData());
		currentNode = noteListBox.getSelectedIndex();

		if (patternLenData.isHoldEnabled == true)
		{
			lengthValue.setText("HOLD", dontSendNotification);
			_pPatternPtr->setNodeData(mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode, lengthHoldId, false);
		}
		else
		{
			String stepData = ((patternLenData.steps >= 10) ? (step = String(patternLenData.steps)) : String((step = "0" + String(patternLenData.steps))));
			String tickData = ((patternLenData.ticks >= 10) ? (tick = String(patternLenData.ticks)) : String((tick = "0" + String(patternLenData.ticks))));
			String lenData = stepData + ":" + tickData;
			lengthValue.setText(lenData, dontSendNotification);
			_pPatternPtr->setNodeData(mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode, patternLenData.steps, false);
			_pPatternPtr->setNodeData(mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), currentNode, patternLenData.ticks, false);
		}
		if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
		{
			_pPatternPtr->setPatternDataUpdateStatus(true);
			_pPatternPtr->updatePatternEditIndication();
			_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
			_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
		}
	}

	void IgniteStepNoteList::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		dialogViewPort.setBounds(0, 0, 604, 478);

		if (buttonThatWasClicked == &noteLen)
		{
			if (!_pPatternBarLengthComp->isDialogOpen.get())
			{
				_pPatternBarLengthComp->isDialogOpen = true;

				auto numOfBars = (int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM) + 1;

				_pStepPtr->setActiveNote(noteListBox.getSelectedIndex());
				_pPatternBarLengthComp->setLenInStepSliderRange(minStepLength, ((numOfBars * 16) - 1) > maxStepLength ? maxStepLength : ((numOfBars * 16) - 1), stepLengthStepSize);
				dialogViewPort.setViewedComponent(_pPatternBarLengthComp, false);
				CommonUtils::showCustomDialog("LENGTH", &dialogViewPort, [this](int r)
					{
						_pPatternBarLengthComp->isDialogOpen = false;

						if (r == 1)
						{
							updateLengthData();
						}
					}, ui::Rectangle<int>{0, 0, 604, 500}, true);
			}
		}
	}

	void IgniteStepNoteList::paint(juce::Graphics& g)
	{
		auto b = getLocalBounds().toFloat();
		String s;

		if (isHighlighted)
		{
			s = isMouseOver || isFocused ? "pattern-step-table-bg-active-hover.png" : "pattern-step-table-bg-active.png";
			Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(s));
			g.drawImage(dropImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
		else
		{
			s = isMouseOver || isFocused ? "pattern-step-table-bg-hover.png" : "pattern-step-table-bg-default.png";
			Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(s));
			g.drawImage(dropImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
	}

	void IgniteStepNoteList::resized()
	{
		auto bounds = getLocalBounds();
		auto startX = bounds.getX();
		auto startY = bounds.getY();
		auto hight = bounds.getHeight();

		noteListBox.setcustombounds(true, ui::Rectangle<int>{80 + 12, startY, 200, hight}, ui::Rectangle<int>{50 + 12, startY, 200, hight});
		noteListBox.setBounds(startX + 12, startY, 250, hight);
		velocomp.setBounds(startX + 260, startY, 250, hight);
		delaycomp.setBounds(startX + 510, startY, 250, hight);
		lengthValue.setBounds(startX + 760, startY, 250, hight);
		noteLen.setBounds(startX + 762, startY, 250, hight);
	}

	void IgniteStepNoteList::setFocus(bool hasFocus, bool activeHasFocus)
	{
		if (hasFocus)
			isMouseOver = true;
		else
			isMouseOver = false;

		repaint();
	};

	bool IgniteStepNoteList::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		FrontPannelParam compParam;

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramRot_PADROT3:
			_pStepPtr->setActiveNote(noteListBox.getSelectedIndex());
			currentNode = noteListBox.getSelectedIndex();

			compParam = (keyValue == ROTARY_LEFT)
				? (noteListBox.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (noteListBox.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			noteListBox.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			break;
		case FrontPannelParam::paramRot_PADROT4:
			compParam = (keyValue == ROTARY_LEFT)
				? (velocomp.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (velocomp.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			velocomp.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			break;
		case FrontPannelParam::paramRot_PADROT5:
			compParam = (keyValue == ROTARY_LEFT)
				? (delaycomp.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (delaycomp.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			delaycomp.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			break;
		case FrontPannelParam::paramRot_PADROT6:
			compParam = (keyValue == ROTARY_LEFT) ?  FrontPannelParam::paramKey_MINUS_NAV : FrontPannelParam::paramKey_PLUS_NAV;
			_pPatternBarLengthComp->pannelKeyHandler((paramId_t)compParam, keyValue);
			updateLengthData();
			break;
		case FrontPannelParam::paramKey_TRACKROTARY3:
			noteListBox.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY4:
			velocomp.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY5:
			delaycomp.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY6:
			if(!_pPatternBarLengthComp->IsEditing())
				noteLen.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			else
			{
				_pPatternBarLengthComp->pannelKeyHandler((paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
				updateLengthData();
			}
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			if (noteListBox.IsEditing())
				noteListBox.FPKeyHandler(true, param, keyValue);
			else if (velocomp.IsEditing())
				velocomp.FPKeyHandler(true, param, keyValue);
			else if (delaycomp.IsEditing())
				delaycomp.FPKeyHandler(true, param, keyValue);
			else if (_pPatternBarLengthComp->IsEditing())
				_pPatternBarLengthComp->pannelKeyHandler(param, keyValue);
			break;
		default:
			return false;
		}

		return true;
	};
	////////////////////////////////////////////////
	//   Class: IgniteStepEventList
	////////////////////////////////////////////////

	IgniteStepEventList::IgniteStepEventList(int SerialNumber, ClientPatternStepData& stepData, IgnitePattern* patternPtr, IgniteStep* stepPtr) : data(stepData)
	{
		_pPatternPtr = patternPtr;
		_pStepPtr = stepPtr;

		srNo.makeVisible(this);
		srNo.setText(String(SerialNumber), juce::dontSendNotification);
		srNo.addMouseListener(this, false);

		addAndMakeVisible(eventList);
		eventList.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		eventList.setValueColour(Theme::Instance().getColour(customOrange));
		eventList.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		eventList.setTextColour(Theme::Instance().getColour(customBlue4));
		eventList.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		eventList.setSelected(1);

		eventState.makeVisibleAndAddListner(this);
		eventState.setClickingTogglesState(false);
		eventState.setToggleable(true);
		eventState.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		eventState.sethoverImages("aux-toggle-noborder-off-hover.png", "aux-toggle-noborder-on-hover.png", "");

		offsetComp.makeVisible(this);
		offsetComp.setDisplayTitle(false);
		offsetComp.setJustificationType(juce::Justification::centred);
		offsetComp.setTextColour(Theme::Instance().getColour(customOrange));
		offsetComp.addMouseListener(this, false);

		addAndMakeVisible(ccList);
		ccList.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		ccList.setValueColour(Theme::Instance().getColour(customOrange));
		ccList.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		ccList.setTextColour(Theme::Instance().getColour(customBlue4));
		ccList.setSelected(0);
		ccList.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,567 });

		addAndMakeVisible(noteList);
		noteList.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		noteList.setValueColour(Theme::Instance().getColour(customOrange));
		noteList.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		noteList.setTextColour(Theme::Instance().getColour(customBlue4));
		noteList.setSelected(0);

		midiCCVal.makeVisible(this);
		midiCCVal.setDisplayTitle(false);
		midiCCVal.setJustificationType(juce::Justification::centred);
		midiCCVal.setTextColour(Theme::Instance().getColour(customOrange));
		midiCCVal.addMouseListener(this, false);

		dataAComp.makeVisible(this);
		dataAComp.setDisplayTitle(false);
		dataAComp.setJustificationType(juce::Justification::centred);
		dataAComp.setTextColour(Theme::Instance().getColour(customOrange));
		dataAComp.addMouseListener(this, false);

		midiCCVal.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pStepPtr->setActiveEvent(getSerialNumber());
			_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_VALUE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)value, false);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		};

		offsetComp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pStepPtr->setActiveEvent(getSerialNumber());
			_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_OFFSET, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)value, false);

			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		};

		dataAComp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (eventList.getSelectedIndex() == PITCH_BEND)
			{
				/* Extract MSB and LSB */
				auto lsb = value & 0x7F;
				auto msb = (value >> 7) & 0x7F;

				_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_TYPE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)lsb, false);
				_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_VALUE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)msb, false);
			}
			else
				_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_VALUE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)value, false);

			_pStepPtr->setActiveEvent(getSerialNumber());

			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		};

		ccList.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pStepPtr->setActiveEvent(getSerialNumber());
			int current_cc = _pPatternPtr->getStepEventData(mt::Ignite::stepEventDataIndex::EVENT_TYPE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber());
			if (current_cc != value)
			{
				_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_TYPE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)value, false);

				if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{
					_pPatternPtr->setPatternDataUpdateStatus(true);
					_pPatternPtr->updatePatternEditIndication();
					_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				}
			}
		};

		noteList.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pStepPtr->setActiveEvent(getSerialNumber());
			int current_note = _pPatternPtr->getStepEventData(mt::Ignite::stepEventDataIndex::EVENT_TYPE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber());
			if (current_note != value)
			{
				_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_TYPE, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)value, false);

				if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{
					_pPatternPtr->setPatternDataUpdateStatus(true);
					_pPatternPtr->updatePatternEditIndication();
					_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				}
			}
		};

		eventList.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pStepPtr->setActiveEvent(getSerialNumber());
			_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_NAME, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), (uint8_t)value, false);
			resized();
			_pPatternPtr->changePatternViewVisibility(IgnitePattern::PatternView::STEP);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		};

		midiCCVal.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		offsetComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		dataAComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	IgniteStepEventList::~IgniteStepEventList()
	{
	}

	int IgniteStepEventList::getCurrentEventNumber()
	{
		return ccList.getSelectedIndex();
	}

	void IgniteStepEventList::mouseUp(const MouseEvent& event)
	{
		if (onMouseDown)
			onMouseDown(this);
	}

	void IgniteStepEventList::highlight(bool State)
	{
		isHighlighted = State;
		repaint();
	}

	int IgniteStepEventList::getSerialNumber()
	{
		return srNo.getText().getIntValue();
	}

	void IgniteStepEventList::refreshStepEventListRowUI(Aux eventData)
	{
		eventState.setToggleState(eventData.enabled, dontSendNotification);
		offsetComp.setText(String(eventData.offset), dontSendNotification);
		eventList.setSelected((eventData.type / 16) - 10);

		switch (eventList.getSelectedIndex())
		{
		case 0: /* Poly Pressure */
			noteList.setSelected(eventData.data1);
			midiCCVal.setText(String(eventData.data2), dontSendNotification);
			break;
		case 1:/* MIDI CC  */
			ccList.setSelected(eventData.data1);
			midiCCVal.setText(String(eventData.data2), dontSendNotification);
			break;
		case 2:/* Program Change */
			dataAComp.setValueBounds(0, 127, eventData.data2);
			dataAComp.setText(String(eventData.data2), dontSendNotification);
			break;
		case 3:/* Channel Pressure */
			dataAComp.setValueBounds(0, 127, eventData.data2);
			dataAComp.setText(String(eventData.data2), dontSendNotification);
			break;
		case 4:/* Pitch bend */
			auto pitchBendValue = (eventData.data2 << 7) | eventData.data1; /* Combine MSB and LSB */
			dataAComp.setValueBounds(0, 16383, static_cast<float>(pitchBendValue));
			dataAComp.setText(String(pitchBendValue), dontSendNotification);
			break;
		}

	}

	void IgniteStepEventList::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &eventState)
		{
			if (eventState.getToggleState())
				eventState.setToggleState(false, dontSendNotification);
			else
				eventState.setToggleState(true, dontSendNotification);

			DBG("Serail number " + String((int)getSerialNumber()));
			_pStepPtr->setActiveEvent(getSerialNumber());
			_pPatternPtr->setStepEventData(mt::Ignite::stepEventDataIndex::EVENT_STATUS, _pStepPtr->getEditBar(), _pStepPtr->getEditStep(), getSerialNumber(), eventState.getToggleState(), false);
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		}
	}

	void IgniteStepEventList::paint(juce::Graphics& g)
	{
		auto color = ui::Theme::Instance().getColour(neutralGrey4);
		Image DrawImage;

		String s;

		if (isHighlighted)
		{
			s = isMouseOver || isFocused ? "pattern-step-table-bg-active-hover.png" : "pattern-step-table-bg-active.png";
			Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(s));
			g.drawImage(dropImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
		else
		{
			s = isMouseOver || isFocused ? "pattern-step-table-bg-hover.png" : "pattern-step-table-bg-default.png";
			Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(s));
			g.drawImage(dropImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
	}

	void IgniteStepEventList::setFocus(bool hasFocus, bool activeHasFocus)
	{
		if (hasFocus)
			isMouseOver = true;
		else
			isMouseOver = false;

		repaint();
	};

	void IgniteStepEventList::resized()
	{
		auto bounds = getLocalBounds();
		auto startX = bounds.getX();
		auto startY = bounds.getY();
		auto hight = bounds.getHeight();

		eventState.setBounds(startX, startY, 60, hight);
		eventList.setBounds(startX + 120, startY, 230, hight);
		offsetComp.setBounds(startX + 300, startY, 230, hight);

		ccList.setBounds(0, 0, 0, 0);
		midiCCVal.setBounds(0, 0, 0, 0);
		noteList.setBounds(0, 0, 0, 0);
		dataAComp.setBounds(0, 0, 0, 0);

		switch (eventList.getSelectedIndex())
		{
		case 0: /* Poly Pressure */
			noteList.setBounds(startX + 620, startY, 230, hight);
			midiCCVal.setBounds(startX + 760, startY, 230, hight);
			break;
		case 1:/* MIDI CC  */
			ccList.setBounds(startX + 600, startY, 180, hight);
			midiCCVal.setBounds(startX + 760, startY, 230, hight);
			break;
		case 2:/* Program Change */
			dataAComp.setBounds(startX + 545, startY, 180, hight);
			break;
		case 3:/* Channel Pressure */
			dataAComp.setBounds(startX + 545, startY, 180, hight);
			break;
		case 4:/* Pitch bend */
			dataAComp.setBounds(startX + 545, startY, 180, hight);
			break;
		}
	}

	void IgniteStepEventList::handleCommandMessage(int id)
	{
		if (id == 1)
			eventState.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, 0);
	}

	bool IgniteStepEventList::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		FrontPannelParam compParam;

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramRot_PADROT3:
			this->postCommandMessage(1);
			break;
		case FrontPannelParam::paramRot_PADROT4:
			compParam = (keyValue == ROTARY_LEFT)
				? (eventList.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (eventList.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			eventList.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			break;
		case FrontPannelParam::paramRot_PADROT5:
			compParam = (keyValue == ROTARY_LEFT)
				? (offsetComp.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (offsetComp.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			offsetComp.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			break;
		case FrontPannelParam::paramRot_PADROT6:
			if (eventList.getSelectedIndex() == 0)
			{
				compParam = (keyValue == ROTARY_LEFT)
					? (noteList.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
					: (noteList.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
				noteList.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			}
			else if (eventList.getSelectedIndex() == 1)
			{
				compParam = (keyValue == ROTARY_LEFT)
					? (ccList.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
					: (ccList.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
				ccList.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			}
			else if (eventList.getSelectedIndex() == 2 || eventList.getSelectedIndex() == 3 || eventList.getSelectedIndex() == 4)
			{
				compParam = (keyValue == ROTARY_LEFT)
					? (dataAComp.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
					: (dataAComp.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
				dataAComp.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			}
			break;
		case FrontPannelParam::paramRot_PADROT7:
			if (eventList.getSelectedIndex() == 0 || eventList.getSelectedIndex() == 1)
			{
				compParam = (keyValue == ROTARY_LEFT)
					? (midiCCVal.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
					: (midiCCVal.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
				midiCCVal.FPKeyHandler(true, (paramId_t)compParam, keyValue);
			}
			break;
		case FrontPannelParam::paramKey_TRACKROTARY4:
			eventList.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY5:
			offsetComp.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY6:
			if (eventList.getSelectedIndex() == 0)
				noteList.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			else if (eventList.getSelectedIndex() == 1)
				ccList.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			else if (eventList.getSelectedIndex() == 2 || eventList.getSelectedIndex() == 3 || eventList.getSelectedIndex() == 4)
				dataAComp.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY7:
			if (eventList.getSelectedIndex() == 0 || eventList.getSelectedIndex() == 1)
				midiCCVal.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			if (eventList.IsEditing())
				eventList.FPKeyHandler(true, param, keyValue);
			else if (offsetComp.IsEditing())
				offsetComp.FPKeyHandler(true, param, keyValue);
			else if (noteList.IsEditing())
				noteList.FPKeyHandler(true, param, keyValue);
			else if (ccList.IsEditing())
				ccList.FPKeyHandler(true, param, keyValue);
			else if (dataAComp.IsEditing())
				dataAComp.FPKeyHandler(true, param, keyValue);
			else if (midiCCVal.IsEditing())
				midiCCVal.FPKeyHandler(true, param, keyValue);
			break;
		default:
			return false;
		}

		return true;
	}
};