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

#include "Common/Modules/IDevice.h"

using namespace Ignite;

extern std::unique_ptr<IDevice> _PUiVirtualEngine;

namespace ui
{
	////////////////////////////////////////////////
	//   Class: Ignite Pattern row
	////////////////////////////////////////////////

	IgnitePatternRow::IgnitePatternRow(int SerialNumber, mt::Ignite::patternData& Data, IgnitePattern* patternPtr) : data(Data)
	{
		_pPatternParentPtr = patternPtr;
		srNo.makeVisible(this);
		name.makeVisibleAndAddListner(this);
		name.setEditable(false, true, false);
		serialNumber = String(SerialNumber + 1);
		name.setText(String(serialNumber) + ": " + data.enginePatternData.patternName, juce::dontSendNotification);
		name.setJustificationType(juce::Justification::centred);
		srNo.setText(String(SerialNumber), juce::dontSendNotification);
		name.addMouseListener(this, false);
		name.setLableFont(font_11);

		patternState.makeVisible(this);
		patternState.setDisplayTitle(false);
		patternState.setJustificationType(juce::Justification::centred);
		patternState.setTextFont(font_11);

		addAndMakeVisible(direction);
		direction.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		direction.updateListOptions(mt::Ignite::directions);
		direction.setSelected(0);
		direction.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		direction.drawBorder(false);
		direction.setValueFont(font_11);

		addAndMakeVisible(numOfBars);
		numOfBars.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		numOfBars.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		numOfBars.drawBorder(false);
		numOfBars.setSelected(0);
		numOfBars.setValueFont(font_11);

		addAndMakeVisible(lastStep);
		lastStep.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		lastStep.updateListOptionsWithSize(mt::Ignite::lastSteps, 16);
		lastStep.setSelected(15);
		lastStep.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		lastStep.drawBorder(false);
		lastStep.setValueFont(font_11);

		addAndMakeVisible(timeBase);
		timeBase.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		timeBase.updateListOptions(mt::Ignite::tbvalues);
		timeBase.setSelected(3);
		timeBase.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		timeBase.drawBorder(false);
		timeBase.setValueFont(font_11);

		addAndMakeVisible(firstStep);
		firstStep.updateListOptionsWithSize(mt::Ignite::lastSteps, 16);
		firstStep.setSelected(0);
		firstStep.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		firstStep.setValueFont(font_11);

		direction.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });
		numOfBars.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });
		lastStep.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });
		firstStep.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });
		timeBase.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });

		patternRotateBtn.makeVisibleAndAddListner(this);
		patternRotateBtn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		box.items.add(FlexItem(name).withMargin(0).withFlex(1.33f));
		box.items.add(FlexItem(direction).withMargin(0).withFlex(1));
		box.items.add(FlexItem(numOfBars).withMargin(0).withFlex(1));
		box.items.add(FlexItem(timeBase).withMargin(0).withFlex(1));
		box.items.add(FlexItem(lastStep).withMargin(0).withFlex(1));
		box.items.add(FlexItem(patternRotateBtn).withMargin(0).withFlex(1));

		direction.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pPatternParentPtr->setSelected(getSerialNumber());
			auto currentDirection = (int)_pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::DIR_INDEX);
			direction.setSelected(value);

			if (currentDirection != value)
			{
				if (value != 8)
				{
					_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::DIR_INDEX, (uint8_t)value, false);
					isDirectionAtBarlevel = false;
				}
				else
				{
					isDirectionAtBarlevel = true;
					direction.setSelected(8);
				}
				//_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::DIR_INDEX, (uint8_t)value, false);
				/*if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{*/
					_pPatternParentPtr->setPatternDataUpdateStatus(true);
					_pPatternParentPtr->updatePatternEditIndication();
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				//}
			}
		};

		name.onValueChanged = [this](String value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pPatternParentPtr->setSelected(getSerialNumber());
			if (_pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::NAME) != value)
			{
				_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::NAME, value, false);
				/*if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{*/
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::UNDO, true);
					IgniteTrack::GetAppTrackInstance()->setInstrDataDirtyFlag(true);
					_pPatternParentPtr->setPatternDataUpdateStatus(true);
					updateEditIndication();
				//}
			}
		};

		name.ValidateDataOnChange = [this](String value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return KEY_PAD_DATA_VALIDATE_OK;

			String PatternName = _pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::NAME);
			_pPatternParentPtr->setSelected(getSerialNumber());

			if (PatternName != value)
			{
				//check for duplicate
				auto patternNameList = _PUiVirtualEngine->EngineGetPatternList();
				for (auto& name : patternNameList)
				{
					if (name == value)
					{
						return KEY_PAD_DATA_DUPLICATE_ERROR; // Name already present
					}
				}
			}
			return KEY_PAD_DATA_VALIDATE_OK;
		};

		numOfBars.onApplyValueChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pPatternParentPtr->setSelected(getSerialNumber());
			if ((int)_pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM) != value)
			{
				_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::BARNUM, (uint8_t)value, false);
				numOfBars.setSelected(value);
				/*if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{*/
					_pPatternParentPtr->setPatternDataUpdateStatus(true);
					_pPatternParentPtr->updatePatternEditIndication();
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				//}
				PatternStatusBar::GetPatternBarInstance()->onNumbofBarchangePattern(value);
			}
		};

		timeBase.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			
			_pPatternParentPtr->setSelected(getSerialNumber());
			timeBase.setSelected(value);
			if ((int)_pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::TIMEBASE) != value)
			{
				_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::TIMEBASE, (uint8_t)value, false);
				_pPatternParentPtr->refreshPatternUI();
				/*if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{*/
					_pPatternParentPtr->setPatternDataUpdateStatus(true);
					_pPatternParentPtr->updatePatternEditIndication();
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				//}
			}
		};

		lastStep.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pPatternParentPtr->setSelected(getSerialNumber());
			lastStep.setSelected(value);
			if ((int)_pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::LASTSTEP) != value)
			{
				_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::LASTSTEP, (int16_t)value, false);
				/*if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{*/
					_pPatternParentPtr->setPatternDataUpdateStatus(true);
					_pPatternParentPtr->updatePatternEditIndication();
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternParentPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				/*}*/
			}
		};

		firstStep.onApplyValueChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);
			if (checker.shouldBailOut())
				return;

			_pPatternParentPtr->setSelected(getSerialNumber());
			_pPatternParentPtr->rotatePattern((uint16_t)value / 16, (uint16_t)value % 16);
			/*if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{*/
				_pPatternParentPtr->setPatternDataUpdateStatus(true);
				_pPatternParentPtr->updatePatternEditIndication();
				_pPatternParentPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternParentPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			//}
		};

		direction.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		numOfBars.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		timeBase.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		lastStep.onFocusChanged = [this](bool a)
		{
			repaint();
		};
		updateLengthandOffset();
	}

	IgnitePatternRow::~IgnitePatternRow()
	{}

	void IgnitePatternRow::mouseUp(const MouseEvent& event)
	{
		if (rowIsBeingDraggedOver)
		{
			if (_pPatternParentPtr->getPatternMoveState())
			{
				_pPatternParentPtr->movePattern(event.position);
			}
			rowIsBeingDraggedOver = false;
		}
		else if (onMouseDown)
				onMouseDown(this);
	}

	void IgnitePatternRow::mouseDrag(const MouseEvent& event)
	{
		juce::DragAndDropContainer* dragC = juce::DragAndDropContainer::findParentDragContainerFor(this);
		if (dragC)
		{
			if (isHighlighted)
			{
				if (!dragC->isDragAndDropActive())
				{
					if (_pPatternParentPtr->getPatternMoveState())
						dragC->startDragging("TargetSource", this);
					rowIsBeingDraggedOver = true;
				}
			}
		}
	}

	void IgnitePatternRow::highlight(bool State)
	{
		State ? patternState.setText("Active", dontSendNotification) : patternState.setText("InActive", dontSendNotification);
		isHighlighted = State;
		repaint();
	}

	int IgnitePatternRow::getSerialNumber()
	{
		return srNo.getText().getIntValue();
	}

	void IgnitePatternRow::mouseDown(const MouseEvent& event)
	{
	}

	void IgnitePatternRow::updateEditIndication()
	{
		String patternNameString = _pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::NAME);

		patternNameString = serialNumber + ": " + patternNameString;
		if (_pPatternParentPtr->getPatternDataUpdateStatus()&& !_pPatternParentPtr->isGlobalAutosaveEnabled())
			patternNameString = patternNameString + "*";
		IgniteTrack::GetAppTrackInstance()->setPatternDataDirtyFlag(true);
		name.setText(patternNameString, juce::dontSendNotification);
	}

	void IgnitePatternRow::refreshPatternRowUI()
	{
		auto patternDataPtr = _pPatternParentPtr->getPatternData((uint8_t)_pPatternParentPtr->getSelected());
		String patternNameString = patternDataPtr->enginePatternData.patternDispName;
		patternNameString = serialNumber + ": " + patternNameString;

		name.setText(patternNameString, juce::dontSendNotification);
		if (!isDirectionAtBarlevel)
		{
			int ret = (int)_pPatternParentPtr->getPatternData(mt::Ignite::ptDataIndex::DIR_INDEX);
			if (ret >= 0)
				direction.setSelected(ret);
			else
				direction.setSelected(8);
		}
		timeBase.setSelected(patternDataPtr->enginePatternData.timeBase);
		numOfBars.setSelected(patternDataPtr->enginePatternData.numBars - 1);
		lastStep.updateListOptionsWithSize(mt::Ignite::lastSteps, (patternDataPtr->enginePatternData.numBars * 16));
		lastStep.setSelected(patternDataPtr->enginePatternData.patternLastStepId);
		updateLengthandOffset();
	}

	void IgnitePatternRow::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &patternRotateBtn)
		{
			firstStep.setSelected(0);
			firstStep.showList();
		}
	}

	void IgnitePatternRow::labelTextChanged(Label* labelThatHasChanged)
	{
		if (labelThatHasChanged == &name)
		{
			_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::NAME, name.getText(), false);
			_pPatternParentPtr->setPatternDataUpdateStatus(true);
			updateEditIndication();
		}
	}

	void IgnitePatternRow::paint(juce::Graphics& g)
	{
		auto color = ui::Theme::Instance().getColour(neutralGrey4);
		Image dropImage;
		String s;

		if (isHighlighted)
		{
			s = isMouseOver ? "pattern-list-bg-active-hover.png" : "pattern-list-bg-active.png";
			dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(s));
			g.drawImage(dropImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
		else
		{
			s = isMouseOver ? "pattern-list-bg-default-hover.png" : "pattern-list-bg-default.png";
			dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(s));
			g.drawImage(dropImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
	}

	void IgnitePatternRow::resized()
	{
		box.performLayout(getLocalBounds());
	}

	void IgnitePatternRow::setColor(int colourID, Colour colour)
	{
		if (colourID == ui::Label::backgroundColourId)
		{
			name.setBackgroundColour(colour);
		}
		else if (colourID == ui::Label::textColourId)
		{
			name.setTextColour(colour);
		}
		else if (colourID == ui::Label::outlineColourId)
		{
			name.setColour(ui::Label::outlineColourId, colour);
		}
	}

	void IgnitePatternRow::setFocus(bool hasFocus, bool activeHasFocus)
	{
		if (this != nullptr)
		{
			if (hasFocus)
				isMouseOver = true;
			else
				isMouseOver = false;
			if (activeHasFocus)
			{
				name.setBackgroundColour(juce::Colour(0x2086BF));
				patternState.setBackgroundColour(juce::Colour(0x28AAEE));
			}
		}
	};

	bool IgnitePatternRow::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		FrontPannelParam compParam;

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RSELECT:
		case FrontPannelParam::paramKey_NEXT_TIE:
			onMouseDown(this);
			break;
		case FrontPannelParam::paramKey_RDBLSELECT:
			name.editLable();
			name.PannelKeyHandler(param, KeyValue);
			break;
		case FrontPannelParam::paramRot_PADROT4:
			compParam = (KeyValue == ROTARY_LEFT)
				? (direction.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (direction.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			direction.FPKeyHandler(true, (paramId_t)compParam, KeyValue);
			break;
		case FrontPannelParam::paramRot_PADROT5:
			compParam = (KeyValue == ROTARY_LEFT)
				? (numOfBars.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (numOfBars.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			numOfBars.FPKeyHandler(true, (paramId_t)compParam, KeyValue);
			break;
		case FrontPannelParam::paramRot_PADROT6:
			compParam = (KeyValue == ROTARY_LEFT)
				? (timeBase.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (timeBase.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			timeBase.FPKeyHandler(true, (paramId_t)compParam, KeyValue);
			break;
		case FrontPannelParam::paramRot_PADROT7:
			compParam = (KeyValue == ROTARY_LEFT)
				? (lastStep.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (lastStep.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			lastStep.FPKeyHandler(true, (paramId_t)compParam, KeyValue);
			break;
		case FrontPannelParam::paramRot_PADROT8:
			compParam = (KeyValue == ROTARY_LEFT)
				? (firstStep.IsEditing() ? FrontPannelParam::paramKey_RMOVERIGHT : FrontPannelParam::paramKey_MINUS_NAV)
				: (firstStep.IsEditing() ? FrontPannelParam::paramKey_RMOVELEFT : FrontPannelParam::paramKey_PLUS_NAV);
			firstStep.FPKeyHandler(true, (paramId_t)compParam, KeyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY4:
			direction.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY5:
			numOfBars.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY6:
			timeBase.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY7:
			lastStep.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY8:
			if (!firstStep.IsEditing())
				patternRotateBtn.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
			else
				firstStep.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			if (direction.IsEditing())
				direction.FPKeyHandler(true, param, KeyValue);
			else if (numOfBars.IsEditing())
				numOfBars.FPKeyHandler(true, param, KeyValue);
			else if (timeBase.IsEditing())
				timeBase.FPKeyHandler(true, param, KeyValue);
			else if (lastStep.IsEditing())
				lastStep.FPKeyHandler(true, param, KeyValue);
			else if (firstStep.IsEditing())
				firstStep.FPKeyHandler(true, param, KeyValue);
			break;
		default:
			return false;
		}
		return true;
	}

	void IgnitePatternRow::updateLastStep(bool update_from_engine, bool is_internal)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "Update from engine : " + String((int)update_from_engine) + " is internal : " + String((int)is_internal));

		auto patternDataPtr = _pPatternParentPtr->getPatternData((uint8_t)_pPatternParentPtr->getSelected());

		auto num_bars = patternDataPtr->enginePatternData.numBars;

		if (lastStep.getSelectedIndex() != ((num_bars * 16) - 1))
		{
			lastStep.updateListOptionsWithSize(mt::Ignite::lastSteps, (num_bars * 16));
			firstStep.updateListOptionsWithSize(mt::Ignite::lastSteps, (num_bars * 16));
		}

		if (update_from_engine)
		{
			lastStep.setSelected(patternDataPtr->enginePatternData.patternLastStepId);
		}
		else
		{
			if (patternDataPtr->enginePatternData.patternLastStepId != (num_bars * 16) - 1)
				_pPatternParentPtr->setPatternData(mt::Ignite::ptDataIndex::LASTSTEP, (int16_t)((num_bars * 16) - 1), is_internal);
			lastStep.setSelected(((num_bars + 1) * 16) - 1);
		}
		firstStep.setSelected(0);
	}

	void IgnitePatternRow::enableBarEditButton(bool state)
	{
		//if (state)
		//{
		//	numOfBars.setAlpha(1.0f);
		//	numOfBars.setInterceptsMouseClicks(true, true);
		//}
		//else
		//{
		//	numOfBars.setAlpha(0.3f);
		//	numOfBars.setInterceptsMouseClicks(false, false);
		//}
	}

	void IgnitePatternRow::enableRotatePatternButton(bool state)
	{
		//patternRotateBtn.setEnabled(state);
	}

	void IgnitePatternRow::mouseMove(const MouseEvent& event)
	{
		isMouseOver = true;
		repaint();
	}

	void IgnitePatternRow::mouseExit(const MouseEvent& event)
	{
		isMouseOver = false;
		repaint();
	}

	void IgnitePatternRow::updateLengthandOffset()
	{
		switch (timeBase.getSelectedIndex())
		{
		case 0:
			lenthMinMax.min = 0;
			lenthMinMax.max= 191;
			offsetMinMax.min = -96;
			offsetMinMax.max = 95;
			break;
		case 1:
			lenthMinMax.min = 0;
			lenthMinMax.max = 95;
			offsetMinMax.min = -48;
			offsetMinMax.max = 47;
			break;
		case 2:
			lenthMinMax.min = 0;
			lenthMinMax.max = 63;
			offsetMinMax.min = -32;
			offsetMinMax.max = 31;
			break;
		case 3:
			lenthMinMax.min = 0;
			lenthMinMax.max = 47;
			offsetMinMax.min = -24;
			offsetMinMax.max = 23;
			break;
		case 4:
			lenthMinMax.min = 0;
			lenthMinMax.max = 31;
			offsetMinMax.min = -16;
			offsetMinMax.max = 15;
			break;
		case 5:
			lenthMinMax.min = 0;
			lenthMinMax.max = 23;
			offsetMinMax.min = -12;
			offsetMinMax.max = 11;
			break;
		case 6:
			lenthMinMax.min = 0;
			lenthMinMax.max = 15;
			offsetMinMax.min = -8;
			offsetMinMax.max = 7;
			break;
		case 7:
			lenthMinMax.min = 0;
			lenthMinMax.max = 11;
			offsetMinMax.min = -6;
			offsetMinMax.max = 5;
			break;
		case 8:
			lenthMinMax.min = 0;
			lenthMinMax.max = 7;
			offsetMinMax.min = -4;
			offsetMinMax.max = 3;
			break;
		case 9:
			lenthMinMax.min = 0;
			lenthMinMax.max = 5;
			offsetMinMax.min = -3;
			offsetMinMax.max = 2;
			break;
		case 10:
			lenthMinMax.min = 0;
			lenthMinMax.max = 3;
			offsetMinMax.min = -2;
			offsetMinMax.max = 1;
			break;
		default:
			break;

		}

	}

	StepPlayhead::StepPlayhead()
	{
		_pParent = IgnitePattern::getAppPatternInstance();

		setInterceptsMouseClicks(false, false);
		optPtr = IgniteControlOptions::GetAppOptInstance();

		_pParent->onPlayHeadChanged = [this](int sNo)
		{
			stepNo = sNo;
			repaint();
		};
	}

	StepPlayhead::~StepPlayhead()
	{
	}

	void StepPlayhead::paint(juce::Graphics& g)
	{
		auto b = getLocalBounds();
		float xPos;
		xPos = stepNo == 1 ? bounds.getX() : (((stepNo - 1) * ButtonWidth) + bounds.getX());

		if (_pParent->getTabIndex() == 2)
		{
			auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE) || (opMode == mt::Ignite::operatioMode::RECORD_MODE))
			{
				g.setColour(colour);
				g.drawRect(xPos, bounds.getY(), bounds.getWidth(), bounds.getHeight(), 1.0f);
			}
		}
	}
};
