#include "../inc/mt_ignite_grid_parameter_view.h"
namespace ui
{
	ParameterViewControl::ParameterViewControl(ParameterView& pV)
		: parameterView(pV)
	{
		veloBtn.makeVisibleAndAddListner(this);
		lenStepBtn.makeVisibleAndAddListner(this);
		lenTickBtn.makeVisibleAndAddListner(this);
		delayBtn.makeVisibleAndAddListner(this);
		plusBtn.makeVisibleAndAddListner(this);
		minusBtn.makeVisibleAndAddListner(this);
		ZoomPrctg.makeVisibleAndAddListner(this);

		veloBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		veloBtn.setToggleable(true);
		veloBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		veloBtn.sethoverImages("btn-param-velocity-default-hover.png", "btn-param-velocity-active-hover.png", "");
		veloBtn.setToggleState(true, dontSendNotification);
		lenStepBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		lenStepBtn.setToggleable(true);
		lenStepBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		lenStepBtn.sethoverImages("btn-param-lenstep-default-hover.png", "btn-param-lenstep-active-hover.png", "");
		lenTickBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		lenTickBtn.setToggleable(true);
		lenTickBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		lenTickBtn.sethoverImages("btn-param-lentick-default-hover.png", "btn-param-lentick-active-hover.png", "");
		delayBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		delayBtn.setToggleable(true);
		delayBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		delayBtn.sethoverImages("btn-param-offset-default-hover.png", "btn-param-offset-active-hover.png", "");

		leftNudgeButton.makeVisibleAndAddListner(this);
		rightNudgeButton.makeVisibleAndAddListner(this);
		rightNudgeButton.setToggleState(false, dontSendNotification);
		addAndMakeVisible(&nudgeText);
		nudgeText.setButtonText("BAR 1/1");

		nudgeText.setLookAndFeel(EmptyTextBackgroundLooknFeel::getLnf());
		leftNudgeButton.setLookAndFeel(EmptyTextBackgroundLooknFeel::getLnf());
		rightNudgeButton.setLookAndFeel(EmptyTextBackgroundLooknFeel::getLnf());
		ZoomPrctg.setLookAndFeel(EmptyTextBackgroundLooknFeel::getLnf());
		plusBtn.setLookAndFeel(EmptyTextBackgroundLooknFeel::getLnf());
		minusBtn.setLookAndFeel(EmptyTextBackgroundLooknFeel::getLnf());

		paramBox1.items.add(FlexItem(veloBtn).withMargin(FlexItem::Margin(0, 4, 0, 0)).withFlex(1));
		paramBox1.items.add(FlexItem(lenStepBtn).withMargin(FlexItem::Margin(0, 4, 0, 0)).withFlex(1));
		paramBox1.items.add(FlexItem(lenTickBtn).withMargin(FlexItem::Margin(0, 4, 0, 0)).withFlex(1));
		paramBox1.items.add(FlexItem(delayBtn).withMargin(FlexItem::Margin(0, 0, 0, 0)).withFlex(1));

		stepControlView.controlParamChanged.connect([this](juce::String param)
			{
				auto patternPtr = IgnitePattern::getAppPatternInstance();
				patternPtr->setActiveParamControl(param);
				setButtonState(s_mapStringToParamValueType[param.toStdString()] - 1);
			});
		
		joystick = mt_ignite_app_joystick::GetobjInstance();
		addChildComponent(joystick);
		joystick->setVisible(true);

		joystick->onSelectionChanged = [this](_Direction selection) {
			auto gridPtr = AppGrid::getGridInstance();
			if (_Direction::LEFT == selection)
			{
				if (gridPtr->currentStepShowing > 0)
					gridPtr->currentStepShowing -= 1;
				gridPtr->moveViewPortHorizontaly(gridPtr->currentStepShowing);
			}
			else if (_Direction::RIGHT == selection)
			{
				if (gridPtr->currentStepShowing <= 12)
					gridPtr->currentStepShowing += 1;
				gridPtr->moveViewPortHorizontaly(gridPtr->currentStepShowing);
			}
			else if (_Direction::UP == selection)
			{
				gridPtr->moveViewPortVertically(currentNoteShowing,_Direction::UP);
			}
			else if (_Direction::DOWN == selection)
			{
			 gridPtr->moveViewPortVertically(currentNoteShowing,_Direction::DOWN);
			}
		};

		getAssets();
	}
	
	void ParameterViewControl::setButtonState(int btn_index)
	{
		veloBtn.setToggleState(false, dontSendNotification);
		lenStepBtn.setToggleState(false, dontSendNotification);
		lenTickBtn.setToggleState(false, dontSendNotification);
		delayBtn.setToggleState(false, dontSendNotification);
		switch (btn_index)
		{
		case 0:
			veloBtn.setToggleState(true, dontSendNotification);
			break;	
		case 1:
			lenStepBtn.setToggleState(true, dontSendNotification);
			break;
		case 2:
			lenTickBtn.setToggleState(true, dontSendNotification);
			break;
		case 3:
			delayBtn.setToggleState(true, dontSendNotification);
			break;
		}
	}

	void ParameterViewControl::buttonClicked(Button* button)
	{
		auto patternPtr = IgnitePattern::getAppPatternInstance();
		auto gridPtr = AppGrid::getGridInstance();

		if (button == &rightNudgeButton)
		{
			gridPtr->keyFocusedItem = gridPtr->gridViewItemID::RIGHT;
			rightNudgeButton.setToggleState(false, dontSendNotification);
			patternPtr->getNextBarAndUpdate(true);
			refreshGridctrl();
		}
		else if (button == &leftNudgeButton)
		{
			gridPtr->keyFocusedItem = gridPtr->gridViewItemID::LEFT;
			leftNudgeButton.setToggleState(false, dontSendNotification);
			patternPtr->getNextBarAndUpdate(false);
			refreshGridctrl();
		}
		else if (button == &veloBtn)
		{
			gridPtr->keyFocusedItem = gridPtr->gridViewItemID::VELO;
			setButtonState(0);
			patternPtr->setActiveParamControl("Velocity");
			controlParamGridChanged.emit(eVelocity);
			patternPtr->setThreshold(maxVelocity + 1);
			AppGrid::getGridInstance()->updateSliderRange();
		}
		else if (button == &lenStepBtn)
		{
			gridPtr->keyFocusedItem = gridPtr->gridViewItemID::LEN_ST;
			setButtonState(1);
			patternPtr->setActiveParamControl("Len:Steps");
			controlParamGridChanged.emit(eLengthSteps);
			patternPtr->setThreshold(maxStepLength + 1);
			AppGrid::getGridInstance()->updateSliderRange();
		}
		else if (button == &lenTickBtn)
		{
			gridPtr->keyFocusedItem = gridPtr->gridViewItemID::LEN_TK;
			setButtonState(2);
			patternPtr->setActiveParamControl("Len:Tick");
			controlParamGridChanged.emit(eLengthTick);
			patternPtr->setThreshold(patternPtr->getTickRange().max + 1);
			AppGrid::getGridInstance()->updateSliderRange();
		}
		else if (button == &delayBtn)
		{
			gridPtr->keyFocusedItem = gridPtr->gridViewItemID::DELAY;
			setButtonState(3);
			patternPtr->setActiveParamControl("Offset");
			controlParamGridChanged.emit(eDelay);
			patternPtr->setThreshold(((patternPtr->getDelayRange().max+1)*2) - 1);
			AppGrid::getGridInstance()->updateSliderRange();
		}

		AppGrid::getGridInstance()->repaint();

		if(button == &veloBtn || button == &lenStepBtn || button == &lenTickBtn || button == &delayBtn)
			AppGrid::getGridInstance()->showNoteRGB();
	}

	void ParameterViewControl::getAssets()
	{
		scrollOptionDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-patternbar-default.png"));
		scrollOptionHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-patternbar-default-hover.png"));
		zoomPlusDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("pattern-zoom-plus-default.png"));

		zoomPlusHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("pattern-zoom-plus-default-hover.png"));
		zoomMinusDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("pattern-zoom-minus-default.png"));
		zoomMinusHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("pattern-zoom-minus-default-hover.png"));
		scrollLeftDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-patternbar-left-default.png"));

		scrollLeftHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-patternbar-left-default-hover.png"));
		scrollRghtDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-patternbar-right-default.png"));
		scrollRghtHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-patternbar-right-default-hover.png"));
	}

	void ParameterViewControl::paint(Graphics& g)
	{
		Image draImage;
		g.drawImage(draImage, ui::Rectangle<float>{ 518, 3, 147, 36 }, RectanglePlacement::centred);
		g.drawImage(draImage, ui::Rectangle<float>{ 633, 3, 147, 36 }, RectanglePlacement::centred);

		draImage = (ZoomPrctg.isMouseOver() || ZoomPrctg.isFocused) ? scrollOptionHover : scrollOptionDefault;
		g.drawImage(draImage, ui::Rectangle<float>{ 516, 3, 147, 36 }, RectanglePlacement::centred);

		draImage = (plusBtn.isMouseOver() || plusBtn.isFocused) ? zoomPlusHover : zoomPlusDefault;
		g.drawImage(draImage, ui::Rectangle<float>{ 637, 5, 30, 32 }, RectanglePlacement::centred);

		draImage = (minusBtn.isMouseOver() || minusBtn.isFocused) ? zoomMinusHover : zoomMinusDefault;
		g.drawImage(draImage, ui::Rectangle<float>{ 517, 5, 30, 32 }, RectanglePlacement::centred);

		draImage = (nudgeText.isMouseOver() || nudgeText.isFocused) ? scrollOptionHover : scrollOptionDefault;
		g.drawImage(draImage, ui::Rectangle<float>{ 687, 3, 147, 36 }, RectanglePlacement::centred);

		draImage = (leftNudgeButton.isMouseOver() || leftNudgeButton.isFocused) ? scrollLeftHover : ((leftNudgeButton.getToggleState() ? scrollLeftHover : scrollLeftDefault));
		g.drawImage(draImage, ui::Rectangle<float>{ 689, 5, 30, 32 }, RectanglePlacement::centred);

		draImage = (rightNudgeButton.isMouseOver() || rightNudgeButton.isFocused) ? scrollRghtHover : ((rightNudgeButton.getToggleState() ? scrollRghtHover : scrollRghtDefault));
		g.drawImage(draImage, ui::Rectangle<float>{ 802, 5, 30, 32 }, RectanglePlacement::centred);
	}
	void ParameterViewControl::refreshGridctrl()
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		auto _pAppGridInstance = AppGrid::getGridInstance();

		String bar_lable = "BAR " + String((int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BAR_ID) + 1) + "/" + String((int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM) + 1);
		nudgeText.setButtonText(bar_lable);
		(_pAppGridInstance->getGridZoomValue() == 5) ? ZoomPrctg.setButtonText(String(0) + " % ") :
			ZoomPrctg.setButtonText(String(_pAppGridInstance->getGridZoomValue()) + " % ");
		_pAppGridInstance->refreshScaleComp();
	}

	void ParameterViewControl::resized()
	{
		paramBox1.performLayout(Rectangle(xStartParam, yStartGridControlFlex, 492, 36));

		ZoomPrctg.setBounds(516, 3, 147, 36);
		plusBtn.setBounds(637, 5, 30, 32);
		minusBtn.setBounds(517, 5, 30, 32);
		plusBtn.toFront(true);
		minusBtn.toFront(true);

		nudgeText.setBounds(687, 3, 147, 36);
		leftNudgeButton.setBounds(689, 5, 30, 32);
		leftNudgeButton.toFront(true);
		rightNudgeButton.setBounds(802, 5, 30, 32);
		rightNudgeButton.toFront(true);

		joystick->setBounds(965, 0, 48, 48);
	}

	void ParameterViewControl::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (AppGrid::getGridInstance()->AppGrid::gridDetailView[AppGrid::getGridInstance()->AppGrid::keyFocusedItem])
		{
		case AppGrid::gridViewItemID::VELO:
			veloBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case AppGrid::gridViewItemID::LEN_ST:
			lenStepBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case AppGrid::gridViewItemID::LEN_TK:
			lenTickBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case AppGrid::gridViewItemID::DELAY:
			delayBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case AppGrid::gridViewItemID::ZOOM_LEFT:
			plusBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case AppGrid::gridViewItemID::ZOOM_RIGHT:
			minusBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case AppGrid::gridViewItemID::BAR_LEFT:
			leftNudgeButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case AppGrid::gridViewItemID::BAR_RIGHT:
			rightNudgeButton.FPKeyHandler(isFocuse, param, 0);
			break;
		default:
			break;
		}
		if ((param == (uint8_t)FrontPannelParam::paramKey_ROTARYROW) && (FrountPannel::GetFrountPannelInstance()->getShiftKeyStatus() == 1) && KeyValue == 1)
		{
			buttonClicked(&leftNudgeButton);
			//rightNudgeChanged.emit(rightNudgeButton.getToggleState());
		}
		else if ((param == (uint8_t)FrontPannelParam::paramKey_ROTARYROW) && KeyValue == 1)
		{
			buttonClicked(&rightNudgeButton);
			//leftNudgeButton.emit(rightNudgeButton.getToggleState());
		}
		repaint();
	}
	ParameterView::ParameterView(GridData* gData, NoteManagement& noteManagement)
		: gridData(gData), noteMgmt(noteManagement)
	{
		noteMgmt.notesChanged.connect([this]() { repaint(); });
	}

	int ParameterView::getStepId(int stepIndex)
	{
		if (stepIndex >= 16)
			return (stepIndex - (patternData->barIndex * 16));
		else
			return stepIndex;
	}

	var ParameterView::getParamFromEngine(mt::Ignite::nodeDataIndex param, int step_index, int nodeId)
	{
		auto tmp1 = patternData->stepIndex;
		auto tmp2 = patternData->nodeIndex;
		var value = -1;
		auto patternPtr = IgnitePattern::getAppPatternInstance();
		patternData->stepIndex = getStepId(step_index);
		if (nodeId >= 0)
			patternData->nodeIndex = nodeId;

		if (patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.count((const unsigned char)patternData->nodeIndex))
		{
			switch (param)
			{
			case mt::Ignite::nodeDataIndex::DELAY:
				value = patternData->enginePatternData.BarDataList.at((const unsigned char)patternData->barIndex).StepDataList.at((const unsigned char)patternData->stepIndex).nodeList.at((const unsigned char)patternData->nodeIndex).begin()->second.offset + ((patternPtr->getDelayRange().max + 1));
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
		return value;
	}

	bool ParameterView::isNotePreset(int stepNum, int noteNum)
	{
		if (patternData->barIndex >= patternData->enginePatternData.BarDataList.size())
			return false;

		return patternData->enginePatternData.BarDataList.at(static_cast<unsigned char>(patternData->barIndex)).StepDataList.at(static_cast<unsigned short>(stepNum)).nodeList.find(static_cast<uint8_t>(noteNum))
			!= patternData->enginePatternData.BarDataList.at(static_cast<unsigned char>(patternData->barIndex)).StepDataList.at(static_cast<unsigned char>(stepNum)).nodeList.end();
	}

	void ParameterView::paint(Graphics& g)
	{
		IgnitePattern* _pPatternPtr = IgnitePattern::getAppPatternInstance();
		patternData = _pPatternPtr->getPatternData((uint8_t)_pPatternPtr->getSelected());
		int viewHeight = getHeight();
		juce::String sParam = _pPatternPtr->getActiveParamControl();
		auto nodeDataIndex = s_mapStringToParamValueIndex[sParam];
		auto paramMaxValue = s_mapStringToParamMaxType[sParam];
		auto cellHeight = viewHeight - 0.5f;
		auto themeInstance = Theme::Instance();
		auto cellWidth = gridData->cellWidth;

		g.fillAll(Colour(0xFFFFFFF));

		if (cellWidth > minimumCellWidthToDraw)
		{
			int startRow, startColumn, endRow, endColumn = 0;
			gridData->getStartValues(startRow, endRow, startColumn, endColumn);
			g.setColour(themeInstance.outlineColour(5));

			for (int j = startColumn; j <= endColumn; j++)
			{
				Rectangle<float> cellRect(cellWidth * j, 0, cellWidth, static_cast<float>(getHeight()));
				g.drawRect(cellRect, 0.5f);
			}
		}

		const float heightFactor = viewHeight * (1.0f / paramMaxValue);

		for (int step = 0; step < 16; step++) {
			float x1 = gridData->findX(step) - 0.5f;
			for (int note = 0; note < 128; note++) {
				if (isNotePreset(step, note))
				{
					int param = getParamFromEngine(nodeDataIndex, step, note);
					g.setColour(Theme::Instance().getNoteColourForParam((int)nodeDataIndex, param));
					float posFoVel = viewHeight - (param * heightFactor);
					Rectangle<float> selRect(x1, posFoVel, cellWidth, cellHeight);
					g.drawRect(selRect);
					g.fillRect(selRect);
				}
			}
		}
	}

	int ParameterView::getRecommendedtHeight()
	{
		return 80;
	}

	void ParameterView::mouseDrag(const MouseEvent& event)
	{
		IgnitePattern* _pPatternPtr = IgnitePattern::getAppPatternInstance();
		juce::String param = _pPatternPtr->getActiveParamControl();
		int paramMaxValue = s_mapStringToParamMaxType[param];

		float x = event.position.getX();
		float y = event.position.getY();

		int selected_step = gridData->findColumn(x);
		int velocity = static_cast<int>(std::round((paramMaxValue * y) / getHeight()));

		velocity = paramMaxValue - velocity;

		if (velocity < 0 || velocity > paramMaxValue)
			return;

		_pPatternPtr->parameterViewDrag(selected_step, velocity, s_mapStringToParamValueIndex[param]);
	}

	void ParameterView::updateOffsetLength()
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

		s_mapStringToParamMaxType.at("Offset") = ((_pPatternPtr->getDelayRange().max + 1) * 2) - 1;
		s_mapStringToParamMaxType.at("Len:Tick") = (_pPatternPtr->getTickRange().max);
		MaxOffsetVar = s_mapStringToParamMaxType["Offset"];
		MaxLengthVar = s_mapStringToParamMaxType["Len:Tick"];
	}
}
