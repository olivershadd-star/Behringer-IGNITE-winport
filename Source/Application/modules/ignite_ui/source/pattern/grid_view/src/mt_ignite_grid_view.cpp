/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY
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
	constexpr int threshold1_local(127);

	AppGrid::AppGrid()
	{
		// initialize grid
		setViewType(viewType);
		scaleComp.setSize(1200, 15);
		addAndMakeVisible(scaleViewport);
		scaleViewport.setViewedComponent(&scaleComp);
		scaleViewport.setScrollBarsShown(false, false, false, false);
		scaleViewport.addListener(this);
		addAndMakeVisible(&gridTools);
		gridComponent.setSize(scaleComp.getWidth(), _pNoteViewComponent->getHeight());
		addAndMakeVisible(&gridViewport);
		gridViewport.setViewedComponent(&gridComponent, false);
		gridViewport.addListener(this);
		gridViewport.setScrollBarsShown(false, false, true, true);
		gridViewport.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::never);

		addAndMakeVisible(&parameterControl);
		parameterView.setSize(1200, 0);// parameterViewport.getScrollBarThickness() + 1);
		parameterView.setMinimizeHeight(0);
		addAndMakeVisible(parameterViewport);
		parameterViewport.setViewedComponent(&parameterView, false);
		parameterViewport.setScrollBarsShown(false, false, true, true);
		parameterViewport.addListener(this);

		levelSlider.makeVisibleAndAddListner(this);
		levelSlider.setRange(0, threshold1_local);
		levelSlider.setVisible(true);
		levelSlider.setRange(-64, 64);
		levelSlider.setColour(Slider::ColourIds::textBoxOutlineColourId, Theme::Instance().getColour(transparentBlack));
		levelSlider.setColour(Slider::backgroundColourId, Theme::Instance().getColour(neutralBlack));
		levelSlider.setColour(Slider::trackColourId, Theme::Instance().getColour(neutralBlack));
		levelSlider.setLookAndFeel(BarSilderLnF::getLnf());
		scaleComp.setSize(gridComponent.getWidth(), scaleComp.getHeight());

		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();

		// sig slots
		gridComponent.getGridData()->gridChanged.connect([this]() {
			if (viewType == GridViewType::DrumView)
			{
				drumView->setSize(60, drumView->getNoteViewHeight());
			}
			else
			{
				ui::KeyboardComponent* keyboard = static_cast<ui::KeyboardComponent*>(_pNoteViewComponent);
				keyboard->setKeyWidth(gridComponent.getGridData()->noteHeight);
				keyboard->setSize(60, static_cast<int>(keyboard->getTotalKeyboardWidth()) + 9);
			}
			scaleComp.setSize(gridComponent.getWidth(), scaleComp.getHeight());
			parameterView.setSize(gridComponent.getWidth(), parameterView.getHeight());
			}
		);

		gridTools.toolSelectionChanged.connect(&gridComponent, &GridComponent::toolTypeChanged);
		parameterControl.plusBtn.onClick = [this]()
		{
			auto gridData = getGridData();
			auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
			centerStep = static_cast<int>(gridData->visibleViewPort.getWidth() / (gridData->cellWidth * 2.0f));

			keyFocusedItem = gridViewItemID::ZOOM_LEFT;
			gridComponent.setZoomFactor(gridComponent.getZoomPercentage() + 5);
			parameterControl.setZoomLable(gridComponent.getZoomPercentage());
			moveViewPortVertically(_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID));
			moveViewPortHorizontaly(_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::STEP_ID));
		};
		parameterControl.minusBtn.onClick = [this]()
		{
			auto gridData = getGridData();
			auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
			centerStep = static_cast<int>(gridData->visibleViewPort.getWidth() / (gridData->cellWidth * 2.0f));

			keyFocusedItem = gridViewItemID::ZOOM_RIGHT;
			gridComponent.setZoomFactor(gridComponent.getZoomPercentage() - 5);
			(gridComponent.getZoomPercentage() == 5) ? parameterControl.setZoomLable(0) :
				parameterControl.setZoomLable(gridComponent.getZoomPercentage());
			moveViewPortVertically(_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID));
			moveViewPortHorizontaly(_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::STEP_ID));
		};
		scaleComp.onMouseDown = [this](const MouseEvent& event)
		{
			enableDisableButton(event.position);
		};
	}

	AppGrid::~AppGrid()
	{
	}


	void AppGrid::enableDisableButton(juce::Point<float> position, int stepIndex)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		auto index = 0;
		auto gangMode = _pPatternPtr->getGangMode();
		
		if (position.getX() != -1)
			index = gridComponent.getGridData()->findColumn(position.getX());
		else
			index = stepIndex;
		
		auto gangStepState = _pPatternPtr->getGangStepState(index);

		if ((IgniteControlOptions::GetAppOptInstance()->getOperationMode() == mt::Ignite::operatioMode::PLAY_REC_MODE))
		{
			auto& gPatternRef = gPatterns.getReference(_pPatternPtr->getSelected());
			if (index != gPatternRef.stepIndex)
			{
				_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::STEP_ID, (uint8_t)index, false);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::modulePattern, (paramId_t)(uint8_t)PatternParam::ParamSelectedStep, _pPatternPtr->getCurrentBarId() << 4 | index, true);
				gridComponent.repaint();
				return;
			}

		}

		if (gridComponent.pencilToolIsActive())
		{
			if (!_pPatternPtr->getStepData(mt::Ignite::stepDataIndex::GATE_STATUS, -1, index))
				_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::GATE_STATUS, -1, index, true, false);
			else
				_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::GATE_STATUS, -1, index, (uint8_t)false, false);
		}
		else
		{
			if (!gangMode && !gangStepState)
				_pPatternPtr->resetGangStepState();
			if (!gangMode)
				_pPatternPtr->resetNoteSelection();

			_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::STEP_ID, (uint8_t)index, false);
			_pPatternPtr->resetGangNoteState();
			(gangStepState) ? _pPatternPtr->setGangStep(index, false) : _pPatternPtr->setGangStep(index, true);
			(gangStepState) ? _pPatternPtr->setNotesForSelectedStep(index, true) : _pPatternPtr->setNotesForSelectedStep(index, false);
			(gangStepState) ? isRowEditing = 0 : isRowEditing = -1;
			moveViewPortHorizontaly(stepIndex);
			gridComponent.repaint();
		}

		scaleComp.setSelectedSteps(_pPatternPtr->getGangStepsState());
		scaleComp.repaint();
	}

	//==============================================================================
	void AppGrid::paint(juce::Graphics& g)
	{
	}

	void AppGrid::updateGridDataWithOffset(int16_t data_offset, bool isPlayModeData, bool sliderState)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		auto _pSelectedNodes = _pPatternPtr->getSelectedNodes();
		auto currentControl = _pPatternPtr->getActiveParamControl();
		isSliderDragging = sliderState;
		auto index = 0;

		if (_pSelectedNodes->size())
		{
			for (auto& node : *_pSelectedNodes)
			{
				mt::Ignite::selectedNode modifiableNode = node;
				bool addDataToList = false;//added this to fix crash from FP, may need to check with HW FP keys and test

				if (values.size() <= index)
					addDataToList = true;

				if ((isSliderDragging && dragging) || addDataToList)
					values.push_back(0);

				modifiableNode.value = values[index] = (int16_t)(int)_pPatternPtr->getDataForSelectedNode(s_mapStringToParamValueIndex[currentControl], node.step, node.note) + data_offset;
				if (sliderState && dragging)
					modifiableNode.value = (int16_t)(int)_pPatternPtr->getDataForSelectedNode(s_mapStringToParamValueIndex[currentControl], node.step, node.note);

				if ((isSliderDragging && dragging) || addDataToList)
					prev_value.push_back(modifiableNode);

				index++;
			}

			if (sliderState)
			{
				for (auto i = 0; i < _pSelectedNodes->size(); i++)
					prev_value[i].value = prev_value[i].value + data_offset;

				dragging = false;
			}
			else
				dragging = true;

			if (!sliderState)
			{
				for (auto it = _pSelectedNodes->begin(); it != _pSelectedNodes->end() && index < prev_value.size(); ++it, ++index)
				{
					mt::Ignite::selectedNode modifiableNode = *it;
					modifiableNode.value = values[index] = prev_value[index].value;
				}
			}
			
			auto SelectedVector = _pPatternPtr->getSelectedNodesVec();
			for (auto i = 0; i < _pSelectedNodes->size(); i++)
			{
				SelectedVector->at(i).value = prev_value[i].value;
			}

			_pPatternPtr->setSelectedNotesValue(s_mapStringToParamValueIndex[currentControl], !isPlayModeData);
			gridComponent.refreshGrid(sliderState, &prev_value);
		}
	}

	void AppGrid::sliderValueChanged(juce::Slider* slider)
	{
		if (slider == &levelSlider)
		{
			offset = (int16_t)slider->getValue() - sliderPrevValue;
			sliderPrevValue = (int16_t)slider->getValue();
			updateGridDataWithOffset(offset, false, true);
		}
	}

	void AppGrid::sliderDragEnded(juce::Slider* slider)
	{
		if (slider == &levelSlider)
		{
			offset = (int16_t)slider->getValue() - sliderPrevValue;
			sliderPrevValue = (int16_t)slider->getValue();
			updateGridDataWithOffset(offset, true, false);
			sliderPrevValue = offset = 0;
			levelSlider.setValue(0.0, dontSendNotification);
			values.clear();
			prev_value.clear();
		}
	}

	void AppGrid::updateSliderRange()
	{
		float range;
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		auto currentControl = _pPatternPtr->getActiveParamControl();
		updateOffsetLength();
		if (currentControl == "Len:Steps")
			range = (((float)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM) + 1) * 16) / 2;
		else
			range = (float)(s_mapStringToParamMaxType[currentControl] + 1) / 2;
		
		levelSlider.setRange(-range, range);
		StepSequencer::getStepSequencerInstance()->updateSliderRange();
	}

	void AppGrid::resized()
	{
		const int kiTotalWidth = getWidth();
		const int kiTotalHeight = getHeight();
		const int kiKeyboardWidth = 60;
		int iX = 0;
		int iY = layout::gridCtrlbar.getHeight();
		const int kiBorderSize = 2;
		//const int kiScrollBarThickness = gridViewport.getScrollBarThickness();

		iX = kiKeyboardWidth;
		int parameterViewHeight = parameterView.getHeight();
		int parameterControlHeight = 50;// parameterControl.getRecommendedHeight();

		const int kiGridViewPortWidth = kiTotalWidth - iX - kiBorderSize - 68;

		const int kiGridViewPortHeight = kiTotalHeight - iY - kiBorderSize - parameterViewHeight - parameterControlHeight - 13;

		auto vertialScrollBarThickness = 8;// gridComponent.getHeight() > kiGridViewPortHeight ? kiScrollBarThickness : 0;
		gridTools.setBounds(iX + 210, 0, layout::gridCtrlbar.getWidth(), layout::gridCtrlbar.getHeight() - vertialScrollBarThickness);
		gridViewport.setBounds(iX, iY - vertialScrollBarThickness + 13, kiGridViewPortWidth, kiGridViewPortHeight);
		parameterViewport.setBounds(0, 478, 962, parameterViewHeight + 20);
		parameterControl.setBounds(0, 430, 1024, parameterControl.getRecommendedHeight() + 23);
		iX = 0;

		//const int kiScaleViewPortWidth = kiTotalWidth - kiKeyboardWidth - kiBorderSize;
		scaleViewport.setBounds(iX + 60, ui::layout::gridCtrlbar.getHeight() - 10, kiGridViewPortWidth, getHeight());

		keyboardViewport.setBounds(iX, iY - vertialScrollBarThickness + 13, kiKeyboardWidth, kiGridViewPortHeight);
		gridViewport.getVerticalScrollBar().scrollToBottom();
		levelSlider.setBounds(970, 74, 39, 346);
	}

	void AppGrid::updateOnViewPositionChange(ui::CommonViewport* pViewport)
	{
		if (pViewport == &gridViewport)
		{
			keyboardViewport.setViewPosition(0, gridViewport.getViewPositionY());
		}
		else if (pViewport == &parameterViewport)
		{
			gridViewport.setViewPosition(parameterViewport.getViewPositionX(), gridViewport.getViewPositionY());
		}
		else if (pViewport == &keyboardViewport)
		{
			gridViewport.setViewPosition(0, keyboardViewport.getViewPositionY());
		}
		gridComponent.updateVisibleViewportRegion(gridViewport.getViewArea());
	}

	void  AppGrid::refreshScreen()
	{
		if (this->isVisible())
		{
			auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
			gridComponent.refreshGridData();
			parameterControl.refreshGridctrl();
			scaleComp.setCurrentBar((int)IgnitePattern::getAppPatternInstance()->getPatternData(mt::Ignite::ptDataIndex::BAR_ID));
			moveViewPortVertically(_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID));
			if (isVisible())
			{
				showNoteRGB();
			}
			updateOffsetLength();
		}
	}

	void AppGrid::toolTypeChanged(GridToolType toolType)
	{
		gridComponent.toolTypeChanged(toolType);
	}

	void AppGrid::moveViewPortHorizontaly(int step, float swipeDistance)
	{
		auto gridData = getGridData();
		if (swipeDistance > 0.0f)
		{
			if (std::abs(swipeDistance) < 10.0f)
				step = 0;
			else
				step = static_cast<int>(swipeDistance / gridData->cellWidth);
		}

		if (step >= centerStep || step == 0)
		{
			int totalWidth = static_cast<int>(gridData->cellWidth * 16 - gridData->visibleViewPort.getWidth());
			int width = static_cast<int>(gridData->cellWidth * (step - centerStep));

			if (width > totalWidth)
			{
				width = (totalWidth < 0) ? 0 : totalWidth;
				currentStepShowing = static_cast<int>(totalWidth / gridData->cellWidth);
			}

			int viewY = static_cast<int>(gridData->visibleViewPort.getY());
			gridViewport.setViewPosition(width, viewY);
			scaleViewport.setViewPosition(width, viewY);

			gridViewport.visibilityChanged();
			scaleViewport.visibilityChanged();
			gridComponent.repaint();
		}
	}

	void AppGrid::moveViewPortVertically(int note, int direction)
	{
		auto gridData = getGridData();
		int currentY = gridViewport.getViewPositionY();
		int offsetY = static_cast<int>(gridData->noteHeight * 6);
		int newY = currentY;

		if (direction == _Direction::UP)
		{
			newY = juce::jmax(0, currentY - offsetY);
		}
		else if (direction == _Direction::DOWN)
		{
			newY = juce::jmin(static_cast<int>(gridData->noteHeight * 128), currentY + offsetY);
		}

		int viewX = static_cast<int>(gridData->visibleViewPort.getX());
		gridViewport.setViewPosition(viewX, newY);
		keyboardViewport.setViewPosition(viewX, newY);

		gridViewport.visibilityChanged();
		keyboardViewport.visibilityChanged();
		gridComponent.repaint();
	}

	void AppGrid::setViewType(GridViewType newType)
	{
		if (_pNoteViewComponent != nullptr)
		{
			removeChildComponent(_pNoteViewComponent);
			delete _pNoteViewComponent;
		}

		if (viewType == GridViewType::MidiView)
		{
			ui::KeyboardComponent* keyComp = new ui::KeyboardComponent(keyboardState, ui::KeyboardComponent::Orientation::verticalKeyboardFacingRight);
			addAndMakeVisible(keyComp);

			keyComp->setLowestVisibleKey(0);
			keyComp->setBlackNoteWidthProportion(1);
			auto minimumWidth = 60;
			auto viewportAvailableWidth = keyboardViewport.getMaximumVisibleWidth() - keyboardViewport.getScrollBarThickness();
			keyComp->setSize(jmax(minimumWidth, viewportAvailableWidth), static_cast<int>(keyComp->getTotalKeyboardWidth() + 9));
			_pNoteViewComponent = keyComp;
			keyComp->noteSelectionChanged = [this](int note)
			{
				moveViewPortVertically(note);
				gridComponent.noteSelectionChanged(note);
				scaleComp.repaint();
			};
		}
		else
		{
			drumView = new DrumNotestView(gridComponent);
			addAndMakeVisible(drumView);
			drumView->setSize(60, drumView->getNoteViewHeight());
			_pNoteViewComponent = drumView;
		}

		gridComponent.setGridViewType(newType);
		keyboardViewport.setViewedComponent(_pNoteViewComponent);
		addAndMakeVisible(keyboardViewport);
		keyboardViewport.addListener(this);
		keyboardViewport.setScrollBarsShown(false, false);
		gridViewport.setScrollBarsShown(false, false);
		keyboardViewport.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::all);
		scaleViewport.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::never);
	}

	void AppGrid::setStepNoteValues(paramId_t param)
	{
		isRowEditing = 0;
		if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
			levelSlider.setValue(levelSlider.getValue() + 1, sendNotification);
		else
			levelSlider.setValue(levelSlider.getValue() - 1, sendNotification);
	}

	void AppGrid::timerCallback()
	{
		offset = (int8_t)levelSlider.getValue() - sliderPrevValue;
		sliderPrevValue = (int8_t)levelSlider.getValue();
		updateGridDataWithOffset(offset, true, false);
		sliderPrevValue = offset = 0;
		levelSlider.setValue(0.0, dontSendNotification);
		values.clear();
		prev_value.clear();
		rMoveLeftCount = 0;
		rMoveRightCount = 0;
		timerStarted = false;
		stopTimer();
	}

	void AppGrid::setStepsNoteValues(paramId_t param)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
		{
			levelSlider.setValue(levelSlider.getValue() + 1, sendNotification);
			rMoveLeftCount = rMoveLeftCount + 1;
			if (rMoveLeftCount > 0)
			{
				if (timerStarted)
				{
					stopTimer();
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
				}
				else
				{
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
					timerStarted = true;
				}
			}
		}
		else
		{
			levelSlider.setValue(levelSlider.getValue() - 1, sendNotification);
			rMoveRightCount = rMoveRightCount + 1;
			if (rMoveRightCount > 0)
			{
				if (timerStarted)
				{
					stopTimer();
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
				}
				else
				{
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
					timerStarted = true;
				}
			}
		}
	}

	void AppGrid::handleCommandMessage(int id)
	{
		if (id == 1)
		{
			if (getGangMode())
				_pInfoWindow->setTextandShow("GANG: ON");
			else
				_pInfoWindow->setTextandShow("GANG: OFF");
		}
	}

	void AppGrid::updateOffsetLength()
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

		s_mapStringToParamMaxType.at("Offset") = ((_pPatternPtr->getDelayRange().max + 1) * 2) - 1;
		s_mapStringToParamMaxType.at("Len:Tick") = (_pPatternPtr->getTickRange().max);
		MaxOffsetVar = s_mapStringToParamMaxType["Offset"];
		MaxLengthVar = s_mapStringToParamMaxType["Len:Tick"];
		parameterView.updateOffsetLength();
	}

	bool AppGrid::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		int currentNode = (int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID);
		barIndex = IgnitePattern::getAppPatternInstance()->getCurrentBarId();
		FrountPannelRef = FrountPannel::GetFrountPannelInstance();
		auto gangMode = _pPatternPtr->getGangMode();

		if ((paramId_t)FrontPannelParam::paramKey_PLUS_NAV == param)
		{
			parameterControl.plusBtn.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, 0);
			return true;
		}
		else if ((paramId_t)FrontPannelParam::paramKey_MINUS_NAV == param)
		{
			parameterControl.minusBtn.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, 0);
			return true;
		}
		else if ((paramId_t)FrontPannelParam::paramKey_DELETE == param && keyValue == (paramId_t)FrontPannelKeyStatus::paramKeyStatusPressed)
		{
			if (_pPatternPtr->selectedNotesInGrid.size() != 0)
				gridTools.imageButtonErase.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, 0);
			return true;
		}

		if ((paramId_t)FrontPannelParam::paramKey_INSERT == param && (keyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
		{
			if (!gridTools.isPencilSelected())
			{
				_pPatternPtr->setInsertKeyStatus(true);
				gridTools.setPensePencilSelected(true);
				gridTools.setSelectTool(false);
				gridComponent.toolTypeChanged(GridToolType::GridPencilTool);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam((int)(FrontPannelParam::paramKey_INSERT)), fpLEDPattern::EN_LED_PATT_ON);
				showNoteRGB();
			}
			else
			{
				_pPatternPtr->setInsertKeyStatus(false);
				_pPatternPtr->setFpStepLedState();
				gridTools.setSelectTool(true);
				gridTools.setPensePencilSelected(false);
				gridComponent.toolTypeChanged(GridToolType::GridSelectTool);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam((int)(FrontPannelParam::paramKey_INSERT)), fpLEDPattern::EN_LED_PATT_OFF);
			}
		}
		if ((paramId_t)FrontPannelParam::paramKey_ROTARYBAR == param && keyValue == (paramId_t)FrontPannelKeyStatus::paramKeyStatusPressed)
		{
			if (!gridTools.isPencilSelected())
			{
				if (gangMode)
					_pPatternPtr->setNotesForSelectedStep(selectedStep, true);
				showSelectedNoteRGB(currentNode);
				gridComponent.repaint();
			}
			else
			{
				if (gangMode)
				{
					_pPatternPtr->addNotes(selectedStep, selectedStep, 0, 127);
					_pPatternPtr->setPatternEditIndication(true);
					repaint();
				}
			}
		}
		if ((paramId_t)FrontPannelParam::paramKey_ROTARYROW == param && keyValue== (paramId_t)FrontPannelKeyStatus::paramKeyStatusPressed)
		{
			if (!gridTools.isPencilSelected())
			{
				if (gangMode)
				{
					_pPatternPtr->setSelectedNoteForAllSteps(currentNode);
					showSelectedNoteRGB(currentNode);
					gridComponent.repaint();
				}
			}
			else
			{
				if (gangMode)
				{
					_pPatternPtr->addNotes(0, 15, currentNode, currentNode);
					_pPatternPtr->setPatternEditIndication(true);
					repaint();
				}
			}

		}
		
		if ((paramId_t)FrontPannelParam::paramKey_GANG == param && (keyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
		{
			if (gridTools.isGangSelected())
			{
				for (const auto& node : _pPatternPtr->selectedNotesInGrid)
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + node.step), fpLEDPattern::EN_LED_PATT_OFF);
				setGangMode(false);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam((int)(FrontPannelParam::paramKey_GANG)), fpLEDPattern::EN_LED_PATT_OFF);
			}
			else
			{
				setGangMode(true);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam((int)(FrontPannelParam::paramKey_GANG)), fpLEDPattern::EN_LED_PATT_ON);
				gridComponent.noteSelectionChanged(currentNode);
				showSelectedNoteRGB(currentNode);
			}
			this->postCommandMessage(1);
		}

		//needed for future 
		/*if ((paramId_t)FrontPannelParam::paramKey_ROTARYROW == param && ((keyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed) || (keyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusOnHold)))
		{
			if (keyFocusedItem == gridViewItemID::DELAY)
				keyFocusedItem = gridViewItemID::VELO;
			else
				keyFocusedItem = (keyFocusedItem + 1);
			parameterControl.pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
		}*/

		if ((paramId_t)FrontPannelParam::paramKey_PAGESHIFT == param && (keyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
		{
			if (optionHandlerEnabled == GRID_PARAM)
			{
				optionHandlerEnabled = GRID_OPTIONS;
			}
			else if (optionHandlerEnabled == GRID_OPTIONS)
			{
				optionHandlerEnabled = GRID_NOTES;
			}
			else if (optionHandlerEnabled == GRID_NOTES)
			{
				optionHandlerEnabled = GRID_PARAM;
			}
		}

		if ((paramId_t)FrontPannelParam::paramRot_ROW == param)
		{
			if ((keyValue == ROTARY_DIRECTION_RIGHT) && (currentNode > 0))
				currentNode -= 1;
			else if ((keyValue == ROTARY_DIRECTION_LEFT) && (currentNode < 127))
				currentNode += 1;

			moveViewPortVertically(currentNode);
			gridComponent.noteSelectionChanged(currentNode);

			if (isSelectToolActive() && (_pPatternPtr->selectedNotesInGrid.size() > 0) && (FrountPannel::GetFrountPannelInstance()->getShiftKeyStatus() == true))
			{
				_pPatternPtr->notesMove(true, (keyValue == ROTARY_DIRECTION_LEFT) ? false : true);
				
				gridComponent.repaint();
			}

			showSelectedNoteRGB(currentNode);
			drumView->setSelectedNote(currentNode);
			if(_pPatternPtr->getInsertKeyStatus() == true)
				showNoteRGB();
			drumView->repaint();
			return true;
		}

		if ((paramId_t)FrontPannelParam::paramRot_BAR == param)
		{
			if ((keyValue == ROTARY_DIRECTION_LEFT) && (selectedStep > 0))
				selectedStep -= 1;
			else if ((keyValue == ROTARY_DIRECTION_RIGHT) && (selectedStep < 15))
				selectedStep += 1;

			if (isSelectToolActive() && (_pPatternPtr->selectedNotesInGrid.size() > 0) && (FrountPannel::GetFrountPannelInstance()->getShiftKeyStatus() == true))
			{
				_pPatternPtr->notesMove(false, (keyValue == ROTARY_DIRECTION_LEFT) ? false : true);
				
				showNoteRGB();
			}
	
			repaint();
			_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::STEP_ID, (uint8_t)selectedStep, false);
			scaleComp.setSelectedSteps(_pPatternPtr->getGangStepsState());
			moveViewPortHorizontaly(selectedStep);
			showSelectedNoteRGB(currentNode);
			gridComponent.repaint();
			return true;
		}

		if (optionHandlerEnabled == GRID_NOTES && param!=(paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
		{
			return gridRowKeyHandler(param, keyValue);
		}

		if (optionHandlerEnabled == GRID_OPTIONS && param != (paramId_t)FrontPannelParam::paramKey_PAGESHIFT && (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT ||
			param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_RSELECT))
		{
			gridTools.pannelKeyOptionsHandler(param, keyValue);
		}
		else
		{
			bool setfocus = true;
			if (keyFocusedItem == gridViewItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				keyFocusedItem = gridViewItemID::VELO;
			}
			else
			{
				pannelSendKey(false, param, keyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= gridViewItemID::FOCUS_MAX ? (gridViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= gridViewItemID::NO_FOCUS ? (gridViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
					break;
				}

				if (setfocus)
				{
					pannelSendKey(true, param, keyValue);
				}
			}
			return true;
		}
		return false;
	}

	bool AppGrid::gridRowKeyHandler(paramId_t param, uint32_t keyValue)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		int currentNode = (int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID);
		bool isStepSelectionHandled = false;
		auto currentControl = _pPatternPtr->getActiveParamControl();

		barIndex = IgnitePattern::getAppPatternInstance()->getCurrentBarId();
		
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RMOVELEFT:
		case FrontPannelParam::paramKey_RMOVERIGHT:
		case FrontPannelParam::paramKey_RSELECT:
			setStepsNoteValues(param);
			break;
		case FrontPannelParam::paramKey_TRACKROTARY1:
		case FrontPannelParam::paramKey_TRACKROTARY2:
		case FrontPannelParam::paramKey_TRACKROTARY3:
		case FrontPannelParam::paramKey_TRACKROTARY4:
		case FrontPannelParam::paramKey_TRACKROTARY5:
		case FrontPannelParam::paramKey_TRACKROTARY6:
		case FrontPannelParam::paramKey_TRACKROTARY7:
		case FrontPannelParam::paramKey_TRACKROTARY8:
		case FrontPannelParam::paramKey_TRACKROTARY9:
		case FrontPannelParam::paramKey_TRACKROTARY10:
		case FrontPannelParam::paramKey_TRACKROTARY11:
		case FrontPannelParam::paramKey_TRACKROTARY12:
		case FrontPannelParam::paramKey_TRACKROTARY13:
		case FrontPannelParam::paramKey_TRACKROTARY14:
		case FrontPannelParam::paramKey_TRACKROTARY15:
		case FrontPannelParam::paramKey_TRACKROTARY16:
			if ((keyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
			{
				selectedStep = (param - (paramId_t)FrontPannelParam::paramKey_TRACKROTARY1);
				if (!gridTools.isGangSelected())
				{
					_pPatternPtr->resetNoteSelection();
					_pPatternPtr->setPatternEditIndication(true);
					showSelectedNoteRGB(currentNode);
					
				}
				if (_pPatternPtr->isNotePresent(selectedStep, currentNode))
				{
					_pPatternPtr->setSelectedNote(selectedStep, currentNode);
					moveViewPortHorizontaly(selectedStep);
					_pPatternPtr->resetGangStepState();
					_pPatternPtr->resetGangNoteState();
					_pPatternPtr->setPasteCompletionState(false);
					_pPatternPtr->setPatternEditIndication(true);
					showSelectedNoteRGB(currentNode);
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + selectedStep), fpLEDPattern::EN_LED_PATT_ON);
					gridComponent.repaint();
				}
				
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
		case FrontPannelParam::paramKey_TRACKSEL9:
		case FrontPannelParam::paramKey_TRACKSEL10:
		case FrontPannelParam::paramKey_TRACKSEL11:
		case FrontPannelParam::paramKey_TRACKSEL12:
		case FrontPannelParam::paramKey_TRACKSEL13:
		case FrontPannelParam::paramKey_TRACKSEL14:
		case FrontPannelParam::paramKey_TRACKSEL15:
		case FrontPannelParam::paramKey_TRACKSEL16:
			selectedStep = (param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1);
			if ((keyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusPressed))
			{

				if ((IgniteControlOptions::GetAppOptInstance()->getOperationMode() == mt::Ignite::operatioMode::PLAY_REC_MODE))
				{
					auto& gPatternRef = gPatterns.getReference(_pPatternPtr->getSelected());
					if (selectedStep != gPatternRef.stepIndex)
					{
						_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::STEP_ID, (uint8_t)selectedStep, false);
						_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::modulePattern, (paramId_t)(uint8_t)PatternParam::ParamSelectedStep, _pPatternPtr->getCurrentBarId() << 4 | selectedStep, true);
						gridComponent.repaint();
						return true;
					}

				}
				if (FrountPannel::GetFrountPannelInstance()->getBarKeyStatus() == FrontPannelKeyStatus::paramKeyStatusOnHold)
				{
					_pPatternPtr->getSelectedBarAndUpdate(param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1);
				}
				else
				{
					if (gridTools.isPencilSelected())
					{
						selectedStep = (param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1);
						if (_pPatternPtr->isNotePresent(selectedStep, currentNode))
							_pPatternPtr->delNote(-1, selectedStep, currentNode);
						else
						{
							_pPatternPtr->addNotes((param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1), (param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1), currentNode, currentNode);
						}
						_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::STEP_ID, (uint8_t)selectedStep, true);
						_pPatternPtr->setPatternEditIndication(true);
						moveViewPortHorizontaly(selectedStep);
						repaint();
					}
					else
					{
						selectedStep = (param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1) + barIndex * 16;
						auto stepGateStatus = _pPatternPtr->getStepData(mt::Ignite::stepDataIndex::GATE_STATUS, -1, selectedStep);
						moveViewPortHorizontaly(selectedStep);
						_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::STEP_ID, (uint8_t)selectedStep, false);
						scaleComp.setSelectedSteps(_pPatternPtr->getGangStepsState());

						if (!stepGateStatus)
							_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::GATE_STATUS, -1, selectedStep, true, false);
						else
							_pPatternPtr->setStepData(mt::Ignite::stepDataIndex::GATE_STATUS, -1, selectedStep, (uint8_t)false, false);


						gridComponent.repaint();
						repaint();
						_pPatternPtr->setFpStepLedState();
					}
				}
			}
			break;
		case FrontPannelParam::paramRot_PADROT1:
		case FrontPannelParam::paramRot_PADROT2:
		case FrontPannelParam::paramRot_PADROT3:
		case FrontPannelParam::paramRot_PADROT4:
		case FrontPannelParam::paramRot_PADROT5:
		case FrontPannelParam::paramRot_PADROT6:
		case FrontPannelParam::paramRot_PADROT7:
		case FrontPannelParam::paramRot_PADROT8:
		case FrontPannelParam::paramRot_PADROT9:
		case FrontPannelParam::paramRot_PADROT10:
		case FrontPannelParam::paramRot_PADROT11:
		case FrontPannelParam::paramRot_PADROT12:
		case FrontPannelParam::paramRot_PADROT13:
		case FrontPannelParam::paramRot_PADROT14:
		case FrontPannelParam::paramRot_PADROT15:
		case FrontPannelParam::paramRot_PADROT16:
			selectedStep = (param - (paramId_t)FrontPannelParam::paramRot_PADROT1);
			if (_pPatternPtr->isNotePresent(selectedStep, currentNode))
			{
				auto& gPatternRef = gPatterns.getReference(_pPatternPtr->getSelected());
				auto lenThreshold = (gPatternRef.enginePatternData.numBars * 16) - 1;
				int value=_pPatternPtr->getDataForSelectedNode(s_mapStringToParamValueIndex[currentControl], selectedStep, currentNode);
				//keyValue == ROTARY_DIRECTION_LEFT ? value-- : value++;

				if (keyValue == ROTARY_DIRECTION_LEFT)
					value--;
				else  if (keyValue == ROTARY_DIRECTION_RIGHT)
					value++;
				else if (keyValue == ROTARY_FASTLEFT)
					value -= ROTARY_FASTJUMP;
				else if (keyValue == ROTARY_FASTRIGHT)
					value += ROTARY_FASTJUMP;
				else if (keyValue == ROTARY_SUPERFASTLEFT)
					value -= ROTARY_SUPERFASTJUMP;
				else if (keyValue == ROTARY_SUPERFASTRIGHT)
					value += ROTARY_SUPERFASTJUMP;

					switch (s_mapStringToParamValueIndex[currentControl])
					{
					case mt::Ignite::nodeDataIndex::VELO:
						if (value > 127)	value = 127;
						if (value < 0)		value = 0;
						gPatternRef.enginePatternData.BarDataList.at((const unsigned char)gPatternRef.barIndex).StepDataList.at((const unsigned char)selectedStep).nodeList.at((const unsigned char)currentNode).begin()->second.velocity = (uint8_t)value;
						break;
					case mt::Ignite::nodeDataIndex::DELAY:
						//if (value - 16 > 15)	value = 31;
						//if (value - 16 <= -16)	value = 0;
						if (value - (_pPatternPtr->getDelayRange().max + 1) > _pPatternPtr->getDelayRange().max)	value = ((_pPatternPtr->getDelayRange().max + 1) * 2) - 1;
						if (value - (_pPatternPtr->getDelayRange().max + 1) <= _pPatternPtr->getDelayRange().min)	value = 0;
						gPatternRef.enginePatternData.BarDataList.at((const unsigned char)gPatternRef.barIndex).StepDataList.at((const unsigned char)selectedStep).nodeList.at((const unsigned char)currentNode).begin()->second.offset = (TickOffset_t)value - (_pPatternPtr->getDelayRange().max + 1);
						break;
					case mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP:
						if (value > lenThreshold)	value = lenThreshold;
						if (value <= 0)	value = 0;
						gPatternRef.enginePatternData.BarDataList.at((const unsigned char)gPatternRef.barIndex).StepDataList.at((const unsigned char)selectedStep).nodeList.at((const unsigned char)currentNode).begin()->second.lenInSteps = (uint8_t)value;
						break;
					case mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK:
						if (value >= _pPatternPtr->getTickRange().max)	value = _pPatternPtr->getTickRange().max;
						if (value <= 0)	value = 0;
						gPatternRef.enginePatternData.BarDataList.at((const unsigned char)gPatternRef.barIndex).StepDataList.at((const unsigned char)selectedStep).nodeList.at((const unsigned char)currentNode).begin()->second.lenInTicks = (TickLength_t)value;
						break;
					}
					_PUiVirtualEngine->EngineSetPatternData((moduleId_t)ModuleName::moduleUI, gPatternRef.enginePatternData.patternName, gPatternRef.enginePatternData, false, PatternDataUpdateReasonType::PatternDataUpdateReason_NodeData);
					_pPatternPtr->setPatternEditIndication(true);
					moveViewPortHorizontaly(selectedStep);
					repaint();
					break;
			}
		}
		if (isStepSelectionHandled)
		{
			keyFocusedItem = gridViewItemID::NO_FOCUS;
			moveViewPortHorizontaly(selectedStep);
			enableDisableButton(juce::Point<float>(-1, -1), selectedStep);
			pannelSendKey(true, param, keyValue);
		}

		return true;
	}

	bool AppGrid::gridBarKeyHandler(paramId_t param, uint32_t keyValue)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		int currentNode = (int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID);
		bool isStepSelectionHandled = false;


		barIndex = IgnitePattern::getAppPatternInstance()->getCurrentBarId();

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_PAGESHIFT:
			optionHandlerEnabled = GRID_PARAM;
			_pPatternPtr->resetGangStepState();
			pannelSendKey(false, param, keyValue);
			keyFocusedItem = gridViewItemID::VELO;
			pannelSendKey(true, param, keyValue);
			break;
		case FrontPannelParam::paramKey_RMOVELEFT:
		case FrontPannelParam::paramKey_RMOVERIGHT:
		case FrontPannelParam::paramKey_RSELECT:
			setStepsNoteValues(param);
			break;
		case FrontPannelParam::paramKey_TRACKSEL1:
			selectedStep = barIndex * 16;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL2:
			selectedStep = (barIndex * 16) + 1;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL3:
			selectedStep = (barIndex * 16) + 2;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL4:
			selectedStep = (barIndex * 16) + 3;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL5:
			selectedStep = (barIndex * 16) + 4;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL6:
			selectedStep = (barIndex * 16) + 5;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL7:
			selectedStep = (barIndex * 16) + 6;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL8:
			selectedStep = (barIndex * 16) + 7;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL9:
			selectedStep = (barIndex * 16) + 8;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL10:
			selectedStep = (barIndex * 16) + 9;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL11:
			selectedStep = (barIndex * 16) + 10;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL12:
			selectedStep = (barIndex * 16) + 11;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL13:
			selectedStep = (barIndex * 16) + 12;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL14:
			selectedStep = (barIndex * 16) + 13;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL15:
			selectedStep = (barIndex * 16) + 14;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramKey_TRACKSEL16:
			selectedStep = (barIndex * 16) + 15;
			isStepSelectionHandled = true;
			break;
		case FrontPannelParam::paramRot_ROW:
			isRowEditing = true;
			keyFocusedItem = gridViewItemID::NO_FOCUS;

			if (isSelectToolActive() && (_pPatternPtr->selectedNotesInGrid.size() > 0))
			{
				_pPatternPtr->notesMove(false, (keyValue == ROTARY_DIRECTION_LEFT) ? false : true);
				gridComponent.repaint();
			}
			else
			{
				if ((keyValue == ROTARY_DIRECTION_LEFT) && (currentNode > 0))
					currentNode -= 1;
				else if ((keyValue == ROTARY_DIRECTION_RIGHT) && (currentNode < 127))
					currentNode += 1;

				moveViewPortVertically(currentNode);
				gridComponent.noteSelectionChanged(currentNode);
				showNoteRGB();
			}
			drumView->setSelectedNote(currentNode);
			drumView->repaint();
			break;
		case FrontPannelParam::paramRot_BAR:
			if (isSelectToolActive() && (_pPatternPtr->selectedNotesInGrid.size() > 0))
			{
				_pPatternPtr->notesMove(false, (keyValue == ROTARY_DIRECTION_LEFT) ? false : true);
				gridComponent.repaint();
			}
			else
			{
				if ((keyValue == ROTARY_DIRECTION_LEFT) && (selectedStep > 0))
					selectedStep -= 1;

				else if ((keyValue == ROTARY_DIRECTION_RIGHT) && (selectedStep < 15))
					selectedStep += 1;

				moveViewPortHorizontaly(selectedStep);
				enableDisableButton(juce::Point<float>(-1, -1), selectedStep);
			}
			break;
		case FrontPannelParam::paramKey_ROTARYROW:
			if (keyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed)
			if ((FrountPannel::GetFrountPannelInstance()->getShiftKeyStatus() == 1))
				parameterControl.buttonClicked(&parameterControl.leftNudgeButton);
			else
				parameterControl.buttonClicked(&parameterControl.rightNudgeButton);
			break;
		}
		if (isStepSelectionHandled)
		{
			keyFocusedItem = gridViewItemID::NO_FOCUS;
			moveViewPortHorizontaly(selectedStep);
			enableDisableButton(juce::Point<float>(-1, -1), selectedStep);
		}
		repaint();
		return true;
	}

	void AppGrid::pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue)
	{
		switch (gridDetailView[keyFocusedItem])
		{
		case VELO:
		case LEN_ST:
		case LEN_TK:
		case DELAY:
		case LEFT:
		case RIGHT:
		case ZOOM_LEFT:
		case ZOOM_RIGHT:
		case BAR_LEFT:
		case BAR_RIGHT:
			parameterControl.pannelSendKey(isFocuse, param, 0);
			break;
		default:
			break;
		}
		repaint();
	}

	void AppGrid::resetPencilToolState()
	{
		gridTools.setPensePencilSelected(false);
		gridTools.setSelectTool(true);
		gridComponent.toolTypeChanged(GridToolType::GridSelectTool);
	}

	void AppGrid::moveViewPortVertically(int note)
	{
		GridData* gridData = getGridData();
		int _offset = (int)(gridData->visibleViewPort.getHeight() / (gridData->noteHeight * 2));
		int height = static_cast<int>(gridData->noteHeight * (127 - note - _offset));

		gridViewport.setViewPosition((int)gridData->visibleViewPort.getX(), height);
		keyboardViewport.setViewPosition((int)gridData->visibleViewPort.getX(), height);
		gridViewport.visibilityChanged();
		keyboardViewport.visibilityChanged();
	}

	void AppGrid::showNoteRGB()
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		int currentNode = (int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID);
		auto currentControl = _pPatternPtr->getActiveParamControl();

		AppMainmode::getMainModeInstance()->resetPadLedsOnViewChange();
		for (int i = 0; i < 16; i++)
			if ((_pPatternPtr->isNotePresent(i, currentNode)))
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::param_RGB_DISP1 + i), fpLEDPattern::EN_RGB_LED_WHITE);
	}

	void AppGrid::showSelectedNoteRGB(int noteNum)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		if (_pPatternPtr->selectedNotesInGrid.size() == 0)
		{
			for (int i = 0; i < 16; i++)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + i), fpLEDPattern::EN_LED_PATT_OFF);
			return;
		}
		for (int i = 0; i < 16; i++)
		{
			if (_pPatternPtr->getSelectedNote({ noteNum, i }))
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + i), fpLEDPattern::EN_LED_PATT_ON);
			else
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + i), fpLEDPattern::EN_LED_PATT_OFF);
		}
	}

	ScaleComponent::ScaleComponent(GridComponent& gridView)
		: gridComponent(gridView)
	{
		gridComponent.getGridData()->gridChanged.connect(this, &ScaleComponent::gridDataChanged);
	}

	void ScaleComponent::gridDataChanged()
	{
		repaint();
	}

	bool ScaleComponent::getGateStatus(int stepIndex)
	{
		return patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)getStepId(stepIndex)).enable;
	}


	int ScaleComponent::getStepId(int stepIndex)
	{
		if (stepIndex >= 16)
			return (stepIndex - (patternData->barIndex * 16));
		else
			return stepIndex;
	}

	void ScaleComponent::paint(Graphics& g)
	{
		auto gridData = gridComponent.getGridData();
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		patternData = _pPatternPtr->getPatternData((uint8_t)_pPatternPtr->getSelected());

		g.setFont(Font(12.0f));

		const float cellHeight = 20.0f;
		const Colour gateStatusColor = Theme::Instance().getColour(customOrange9);
		const Colour defaultColor = Theme::Instance().getColour(customGrey3);
		const Colour outlineColor = Theme::Instance().outlineColour(5);

		if (gridData->cellWidth > minimumCellWidthToDraw)
		{
			String baseLabel = "ST " + String(currentBar + 1) + ":";

			for (int j = 0; j < 16; ++j)
			{
				Rectangle<float> rectCell = gridData->getCellRect(0, j).withHeight(cellHeight);

				g.setColour(getGateStatus(j) ? gateStatusColor : defaultColor);
				g.fillRoundedRectangle(rectCell, 3.0f);

				g.setColour(outlineColor);
				g.drawRect(rectCell, 1.0f);

				g.setColour(juce::Colours::white);
				g.drawText(baseLabel + String(j + 1), rectCell, Justification::centred);
			}
		}
	}

	void ScaleComponent::resized()
	{
	}

	void ScaleComponent::mouseDown(const MouseEvent& event)
	{
		if (onMouseDown)
			onMouseDown(event);
	}

	void DrumNotestView::paint(Graphics& g)
	{
		auto* songConfigInstance = IgniteSongConfig::getAppSongConfigInstance();
		auto* themeInstance = &Theme::Instance();
		auto* patternInstance = IgnitePattern::getAppPatternInstance();

		Font f(gridData->noteHeight - 2);
		g.setFont(f);
		float y = static_cast<float>(getHeight()) - gridData->noteHeight;
		float x = static_cast<float>(getWidth());
		selectedNote = (selectedNote < 0 ? (int)patternInstance->getPatternData(mt::Ignite::ptDataIndex::NODE_ID) : selectedNote);

		auto noteNames = (songConfigInstance->isAccidentalEnabled() ? mt::Ignite::midiNoteNamesFlats : mt::Ignite::midiNoteNamesSharps);

		const Colour backgroundColour9 = themeInstance->backgroundColour(9);
		const Colour backgroundColour11 = themeInstance->backgroundColour(11);
		const Colour outlineColour7 = themeInstance->outlineColour(7);
		const Colour outlineColour9 = themeInstance->outlineColour(9);
		const Colour backgroundColour5 = themeInstance->backgroundColour(5);
		const Colour selectedNoteColour = themeInstance->backgroundColour(6).withAlpha(0.5f);

		for (int i = 0; i <= totalPianoKeys; ++i)
		{
			bool isAccidental = (i % 12 == 1 || i % 12 == 3 || i % 12 == 6 || i % 12 == 8 || i % 12 == 10);
			Rectangle<float> noteCellRect(0, y, x, gridData->noteHeight);

			if (isAccidental)
			{
				g.setColour(backgroundColour9);
				g.fillRect(noteCellRect);
				g.setColour(outlineColour7);
				g.drawText(noteNames[i], noteCellRect, Justification::centredRight);
			}
			else
			{
				g.setColour(backgroundColour11);
				g.fillRect(noteCellRect);
				g.setColour(backgroundColour5);
				g.drawText(noteNames[i], noteCellRect, Justification::centredLeft);
			}

			g.setColour(outlineColour9);
			g.drawRect(noteCellRect, 0.3f);

			if (i == selectedNote)
			{
				g.setColour(selectedNoteColour);
				g.fillRect(noteCellRect);
			}

			y -= gridData->noteHeight;
		}
	}

	void DrumNotestView::mouseUp(const MouseEvent& event)
	{
		selectedNote = (int)((float)event.position.getY() / gridData->noteHeight);
		selectedNote = totalPianoKeys - selectedNote;
		repaint();
		gridComponent.noteSelectionChanged(selectedNote);
	}
}//namespace mt

