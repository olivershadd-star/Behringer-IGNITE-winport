#include "../inc/mt_ignite_grid_component.h"

namespace ui
{
	GridComponent::GridComponent()
	{
		setWantsKeyboardFocus(true);
		optPtr = IgniteControlOptions::GetAppOptInstance();

		gridData.gridComponent = this;
		GridPencilTool* pencilTool = new GridPencilTool(noteMgmt, gridData);
		GridSelectTool* selectTool = new GridSelectTool(noteMgmt, gridData);
		tools.push_back(pencilTool);
		tools.push_back(selectTool);
		tools.push_back(new GridEraseTool(noteMgmt, gridData));
		tools.push_back(new GridCutPasteTool(noteMgmt, gridData));
		tools.push_back(new GridCopyPasteTool(noteMgmt, gridData));

		auto gridAddNote_ = [this]()
			{
			};

		auto gridEraseNote_ = [this]()
			{
			};

		auto gridEditNoteVelocity_ = [this]()
			{
				repaint();
			};

		gridData.gridChanged.connect([this]()
			{
				updateGridSize();
			});

		selectTool->setActive(true);
		currentTool = selectTool;
		seletionIsActive = currentTool->getType() == GridToolType::GridSelectTool ? true : false;
	}

	GridComponent::~GridComponent()
	{
		for (auto tool : tools)
		{
			delete tool;
		}
	}

	void GridComponent::noteSelectionChanged(int note)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "Note : " + String(note));

		_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::NODE_ID, (uint8_t)note, false);
		noteHighLightRow = note;
		auto gangMode = _pPatternPtr->getGangMode();

		if (note >= 0)
		{
			auto gangNoteState = _pPatternPtr->getGangNoteState(note);
			if (!gangMode && !gangNoteState)
				_pPatternPtr->resetGangNoteState();
			_pPatternPtr->resetGangStepState();
			(gangNoteState) ? _pPatternPtr->setGangNote(note, false) : _pPatternPtr->setGangNote(note, true);
			(gangNoteState) ? AppGrid::getGridInstance()->setRowEdit(1) : AppGrid::getGridInstance()->setRowEdit(-1);
			if (!gangMode)
				_pPatternPtr->resetNoteSelection();

		}
		repaint();
	}

	void GridComponent::setQuantizationLevel(int qL)
	{
		gridData.setQl(qL);
	}

	void GridComponent::setPosition(int bar, int beat, int tick)
	{
		currentBar = bar;
		currentBeat = beat;
		currentTick = tick;
	}

	void GridComponent::setBarBeatAndTimeSignature(int bars, int num, int den)
	{
		gridData.insertBars(bars, num, den);
	}

	void GridComponent::updateNotesFromTrack()
	{}

	void GridComponent::refreshGridData()
	{
		_pPatternComp = IgnitePattern::getAppPatternInstance();
		currentPattern = (uint8_t)_pPatternComp->getSelected();
		patternData = _pPatternComp->getPatternData(currentPattern);
		_pStepsState = _pPatternComp->getGangStepsState();
		barNum = patternData->enginePatternData.numBars;
		stepThreshold = (barNum * 16) - 1;
		barId = patternData->barIndex + 1;
		activeStepIndex = patternData->barIndex * 16;

		if (this->isVisible())
		{
			currentControl = _pPatternComp->getActiveParamControl();
			noteColour100 = Theme::Instance().getNoteColourForParam((int)s_mapStringToParamValueType[currentControl], 100);
			noteColour30 = Theme::Instance().getNoteColourForParam((int)s_mapStringToParamValueType[currentControl], 30);
			backgroundColour5 = Theme::Instance().backgroundColour(5).withAlpha(0.2f);
			backgroundColour9 = Theme::Instance().backgroundColour(9);
			outlineColour5 = Theme::Instance().outlineColour(5);
			outlineColour6 = Theme::Instance().outlineColour(6);
			outlineColour8 = Theme::Instance().outlineColour(8);
			selectionColour1 = Theme::Instance().selectionColour(1);
			selectionColour3 = Theme::Instance().selectionColour(3);
			noteColourIntensity = noteColour100;
			nodeTextColour = Theme::Instance().getNoteColourForParam(1, 100);

			opMode = optPtr->getOperationMode();
			playMode = (opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE);
			recordMode = opMode == mt::Ignite::operatioMode::RECORD_MODE;

			// Move constants here
			totalKeys = totalPianoKeys + 1;
			cellHeight = gridData.noteHeight;
			cellWidth = gridData.cellWidth;
			outlineThickness = 0.5f;
			highlightThickness = 2.0f;
		}
		updateOffsetLength();
	}

	void GridComponent::updateOffsetLength()
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

		s_mapStringToParamMaxType.at("Offset") = ((_pPatternPtr->getDelayRange().max + 1) * 2) - 1;
		s_mapStringToParamMaxType.at("Len:Tick") = (_pPatternPtr->getTickRange().max);
		MaxOffsetVar = s_mapStringToParamMaxType["Offset"];
		MaxLengthVar = s_mapStringToParamMaxType["Len:Tick"];
	}

	void GridComponent::paint(juce::Graphics& g)
	{
		// Draw the background
		g.fillAll(Colour(0xFF282E4B));
		Font f(gridData.noteHeight - 2);
		g.setFont(f);

		if (gridData.visibleViewPort.getWidth() == 0) return;

		auto _pPtr = IgnitePattern::getAppPatternInstance();
		auto _pGridPtr = AppGrid::getGridInstance();
		noteHighLightRow = patternData->nodeIndex;
		stepHighLightCol = patternData->stepIndex;
		auto playStep = getStepId(_pPtr->getCurrentStepPlaying());

		if (gridData.cellWidth > minimumCellWidthToDraw)
		{
			int startRow, startColumn, endRow, endColumn = 0;
			gridData.getStartValues(startRow, endRow, startColumn, endColumn);
			auto highlightCurrentStep = true;

			if (playMode || recordMode)
				_pGridPtr->moveViewPortHorizontaly(playStep);

			for (int actualRow = totalPianoKeys - endRow, i = endRow; i >= startRow; i--, actualRow++)
			{
				const int pitchClass = actualRow % 12;
				const Colour cellColour = (pitchClass == 1 || pitchClass == 3 || pitchClass == 6 || pitchClass == 8 || pitchClass == 10) ? backgroundColour5 : backgroundColour9;

				for (int j = startColumn; j <= endColumn; j++)
				{
					Rectangle<float> rectCell = gridData.getCellRect(i, j);
					g.setColour(outlineColour5);
					g.drawRect(rectCell, outlineThickness);
					g.setColour(cellColour);
					g.fillRect(rectCell);

					if (i == startRow)
					{
						rectCell.setY(0);
						rectCell.setHeight(cellHeight * totalKeys);
						if (_pStepsState[j + activeStepIndex])
						{
							g.setColour(outlineColour8);
							g.drawRect(rectCell, highlightThickness);
							highlightCurrentStep = false;
						}
					}
				}
			}

			if (highlightCurrentStep)
			{
				if (playMode || recordMode)
					stepHighLightCol = playStep;
				Rectangle<float> rectCell = gridData.getCellRect(0, stepHighLightCol);
				rectCell.setY(0);
				rectCell.setHeight(cellHeight * totalKeys);
				g.setColour(outlineColour8);
				g.drawRect(rectCell, highlightThickness);
			}
		}

		Rectangle<float> rectCell1 = gridData.getCellRect(totalPianoKeys - noteHighLightRow, 0);
		rectCell1.setWidth(gridData.recommendedWidth);
		g.setColour(outlineColour6);
		g.drawRect(rectCell1, 1.0f);

		// Draw beats
		g.setColour(juce::Colours::white);
		int currBar = 1;
		float startPos = 0.0;
		for (int range : gridData.barsRange)
		{
			BarData barData;
			gridData.getBarData(range, barData);
			for (int i = currBar; i <= range; i++)
			{
				g.drawLine(startPos, 0, startPos, static_cast<float>(getHeight()), outlineThickness);
				startPos += barData.widthOfBar;
			}
			currBar = range;
		}

		// Draw note markings
		if (gridData.noteMarkingWidth > minimumBarOrBeatWidthToDraw)
		{
			const Rectangle<int>& visibleViewPort = gridData.visibleViewPort;
			int markingStartIndex = static_cast<int>(visibleViewPort.getX() / gridData.noteMarkingWidth);
			float markingStartPos = gridData.noteMarkingWidth * markingStartIndex;
			while (markingStartPos <= (visibleViewPort.getX() + visibleViewPort.getWidth()))
			{
				g.drawLine(markingStartPos, 0, markingStartPos, static_cast<float>(getHeight()), outlineThickness);
				markingStartPos += gridData.noteMarkingWidth;
			}
		}

		g.setColour(noteColour100);

		// Paint active tools
		for (auto tool : tools)
		{
			if (tool->isActive())
				tool->paint(g);
		}

		drawUI(g);
	}

	var GridComponent::getParamFromEngine(mt::Ignite::nodeDataIndex param, int step_index, int nodeId)
	{
		auto tmp1 = patternData->stepIndex;
		auto tmp2 = patternData->nodeIndex;
		var value = -1;

		patternData->stepIndex = getStepId(step_index);
		if (nodeId >= 0)
			patternData->nodeIndex = nodeId;

		if (patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.count((const unsigned char)patternData->nodeIndex))
		{
			switch (param)
			{
			case mt::Ignite::nodeDataIndex::DELAY:
				value = patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.at((const unsigned char)patternData->nodeIndex).begin()->second.offset + ((MaxOffsetVar + 1) / 2);
				break;
			case mt::Ignite::nodeDataIndex::NOTE_NUM:
				value = patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.at((const unsigned char)patternData->nodeIndex).begin()->second.note;
				break;
			case mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP:
				value = patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.at((const unsigned char)patternData->nodeIndex).begin()->second.lenInSteps;
				break;
			case mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK:
				value = patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.at((const unsigned char)patternData->nodeIndex).begin()->second.lenInTicks;
				break;
			case mt::Ignite::nodeDataIndex::VELO:
				value = patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.at((const unsigned char)patternData->nodeIndex).begin()->second.velocity;
				break;
			}
		}
		patternData->stepIndex = tmp1;
		if (nodeId >= 0)
			patternData->nodeIndex = tmp2;
		//DBG("Data" + String(value));
		return value;
	}

	int GridComponent::getStepId(int stepIndex)
	{
		if (stepIndex >= 16)
			return (stepIndex - (patternData->barIndex * 16));
		else
			return stepIndex;
	}

	bool GridComponent::getGateStatus(int stepIndex)
	{
		return patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)getStepId(stepIndex)).enable;
	}

	void GridComponent::resized()
	{
		updateGridSize();
	}

	void GridComponent::updateVisibleViewportRegion(const Rectangle<int>& viewportRegion)
	{
		gridData.visibleViewPort = viewportRegion;
	}

	void GridComponent::insertTimeSig(int bar, int num, int den)
	{
		gridData.insertTimeSig(bar, num, den);
	}

	void GridComponent::deleteTimeSig(int bar)
	{
		gridData.deleteTimeSig(bar);
	}

	void GridComponent::updateGridSize()
	{
		int gridHeight = static_cast<int>(gridData.noteHeight * (totalPianoKeys + 1));
		setSize(gridData.getRequiredGridWidth(), gridHeight);
		repaint();
	}

	void GridComponent::mouseUp(const MouseEvent& event)
	{
		for (auto tool : tools)
		{
			if (tool->isActive())
			{
				tool->mouseUp(event);
				repaint();
			}
		}
	}

	void GridComponent::mouseMove(const MouseEvent& event)
	{

		for (auto tool : tools)
		{
			if (tool->isActive())
				tool->mouseMove(event);
		}

	}

	void GridComponent::mouseDrag(const MouseEvent& event)
	{

		for (auto tool : tools)
		{
			if (tool->isActive())
			{
				tool->mouseDrag(event);
				repaint();
			}
		}

	}

	void GridComponent::mouseDown(const MouseEvent& event)
	{

		for (auto tool : tools)
		{
			if (tool->isActive())
				tool->mouseDown(event);
		}

	}

	void GridComponent::mouseDoubleClick(const MouseEvent& event)
	{

		for (auto tool : tools)
		{
			if (tool->isActive())
				tool->mouseDoubleClick(event);
		}

	}

	void GridComponent::setZoomFactor(double zoomValue)
	{
		gridData.setZoomFactor((float)zoomValue, (float)zoomValue);
		repaint();
	}

	void GridComponent::toolTypeChanged(GridToolType toolType)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		pencilIsActive = false;

		if (((toolType == GridToolType::GridCopyPasteTool || toolType == GridToolType::GridCutPasteTool || toolType == GridToolType::GridEraseTool)) && currentTool->getType() == GridToolType::GridSelectTool)
		{
			seletionIsActive = true;
		}
		else
		{
			seletionIsActive = false;
			_pPatternPtr->resetNoteSelection();
		}

		for (auto tool : tools)
		{
			if (tool->getType() == toolType)
			{
				tool->setActive(true);
				currentTool = tool;

			}
			else
			{
				tool->setActive(false);
			}
		}
		if (currentTool->getType() == GridToolType::GridSelectTool)
		{
			_pPatternPtr->resetGangStepState();
			_pPatternPtr->resetGangNoteState();
			seletionIsActive = true;
		}
		else if (currentTool->getType() == GridToolType::GridPencilTool)
			pencilIsActive = true;

		IgnitePattern::getAppPatternInstance()->resetSelectedNoteRefCount();
		repaint();
	}

	void GridComponent::refreshGrid(bool sliderState, std::vector<mt::Ignite::selectedNode>* values)
	{
		sliderDragging = sliderState;
		noteValues = values;
		repaint();
	}

	int GridComponent::getNoteValue(int step, int note)
	{
		for (auto& node : *noteValues)
		{
			if ((node.note == note) && (node.step == step))
				return node.value;
		}
		return 0;
	}
	bool GridComponent::isNotePreset(int stepNum, int noteNum)
	{
		if (patternData->barIndex >= patternData->enginePatternData.BarDataList.size())
			return false;

		return patternData->enginePatternData.BarDataList.at(static_cast<unsigned char>(patternData->barIndex)).StepDataList.at(static_cast<unsigned short>(stepNum)).nodeList.find(static_cast<uint8_t>(noteNum))
			!= patternData->enginePatternData.BarDataList.at(static_cast<unsigned char>(patternData->barIndex)).StepDataList.at(static_cast<unsigned char>(stepNum)).nodeList.end();
	}

	void GridComponent::drawUI(juce::Graphics& g)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		currentControl = _pPatternPtr->getActiveParamControl();
		auto nodeIndex = s_mapStringToParamValueType[currentControl];
		auto selectedNotes = _pPatternPtr->getSelectedNodes();
		float x1Base = gridData.cellWidth - 2;
		float yPosBase = gridData.noteHeight;

		for (int step = 0; step < 16; step++)
		{
			float x1 = gridData.findX(step) + 1;
			noteColourIntensity = (getGateStatus(step) ? noteColour100 : noteColour30);

			for (int note = 0; note < 128; note++)
			{
				int delay_val = static_cast<int>(getParamFromEngine(mt::Ignite::nodeDataIndex::DELAY, step, note));
				bool notePresent = isNotePreset(step, note);
				bool selectedNote = (selectedNotes->find({ step, note }) != selectedNotes->end());

				if (notePresent)
				{
					int param;

					if (sliderDragging)
					{
						if (selectedNote)
						{
							param = getNoteValue(step, note);
							param = std::max(param, 0);
							stepThreshold = (currentControl != "Len:Steps") ? s_mapStringToParamMaxType[currentControl] : stepThreshold;
							param = std::min(param, stepThreshold);
						}
						else
							param = getParamFromEngine(nodeIndex, step, note);
					}
					else
						param = getParamFromEngine(nodeIndex, step, note);

					g.setColour(noteColourIntensity);
					float yPos = gridData.findY(note);
					Rectangle<float> area(x1, yPos, x1Base, yPosBase);

					switch (nodeIndex)
					{
					case mt::Ignite::nodeDataIndex::VELO:
						area.setX(area.getX() + ((delay_val - ((MaxOffsetVar+1)/2)) * (area.getWidth() / MaxOffsetVar)));
						area.setY(area.getY() + yPosBase - ((yPosBase / maxVelocity) * param));
						area.setHeight((area.getHeight() * param / maxVelocity));
						g.drawRect(area);
						g.fillRect(area);
						g.setColour(nodeTextColour);
						g.drawText(juce::String(static_cast<int>(param)), area, Justification::centred);
						break;

					case mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK:
					{
						auto lenTick_val = static_cast<int>(getParamFromEngine(mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK, step, note));
						area.setX(area.getX() + ((delay_val - ((MaxOffsetVar + 1) / 2)) * (area.getWidth() / MaxOffsetVar)));
						area.setWidth(area.getWidth() * (lenTick_val) / (MaxLengthVar));
						g.drawRect(area);
						g.fillRect(area);
						g.setColour(nodeTextColour);
						auto val = getParamFromEngine(mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP, step, note);
						g.drawText(String(static_cast<int>(val)) + ":" + juce::String(static_cast<int>(param)), area, Justification::centred);
						break;
					}

					case mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP:
					{
						auto lenStep_val = static_cast<int>(getParamFromEngine(mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP, step, note));
						area.setX(area.getX() + ((delay_val - ((MaxOffsetVar+1)/2)) * (area.getWidth() / MaxOffsetVar)));

						if (lenStep_val == 0)
						{
							g.setColour(nodeTextColour);
							g.drawText(juce::String(lenStep_val), area, Justification::centredLeft);
						}
						else
						{
							area.setWidth((area.getWidth() * (lenStep_val) / stepThreshold));
							g.setColour(noteColourIntensity);
							g.drawRect(area);
							g.fillRect(area);
							g.setColour(nodeTextColour);
							auto val = getParamFromEngine(mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK, step, note);
							g.drawText(juce::String(static_cast<int>(param)) + ":" + String(static_cast<int>(val)), area, Justification::centred);
						}
						break;
					}

					case mt::Ignite::nodeDataIndex::DELAY:
						g.setColour(noteColourIntensity);
						area.setX(area.getX() + ((param - ((MaxOffsetVar + 1) / 2)) * (area.getWidth() / MaxOffsetVar)));
						g.drawRect(area);
						g.fillRect(area);
						g.setColour(selectionColour3);
						g.drawRect(area, 1.0f);
						g.setColour(nodeTextColour);
						g.drawText(juce::String(static_cast<int>(param - ((MaxOffsetVar + 1) / 2))), area, Justification::centred);
						break;

					default:
						break;
					}
				}

				if ((selectedNotes->find({ step, note }) != selectedNotes->end()))
				{
					float yPos = gridData.findY(note);
					Rectangle<float> selRect(x1, yPos, x1Base, yPosBase);
					g.setColour(selectionColour1);
					if (delay_val > -1)
						selRect.setX(selRect.getX() + ((delay_val - ((MaxOffsetVar + 1) / 2)) * (selRect.getWidth() / MaxOffsetVar)));
					g.drawRect(selRect, 1.5f);
				}
			}
		}
	}
}// namespace mt