AppGridControl::AppGridControl()
{
	gangBtn.makeVisibleAndAddListner(this);
	imageButtonPencil.makeVisibleAddListnerAndAddRadioGroup(this, 7890);
	imageButtonErase.makeVisibleAddListnerAndAddRadioGroup(this, 7890);
	selectBtn.makeVisibleAddListnerAndAddRadioGroup(this, 7890);
	gangBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	gangBtn.sethoverImages("btn-gangedit-120x44-default-hover.png", "btn-gangedit-120x44-active-hover.png", "");
	imageButtonPencil.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	imageButtonPencil.sethoverImages("btn-pen-default-hover.png", "btn-pen-active-hover.png", "");
	imageButtonErase.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	imageButtonErase.sethoverImages("btn-erase-default-hover.png", "btn-erase-active-hover.png", "");
	selectBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	selectBtn.sethoverImages("btn-select-default-hover.png", "btn-select-active-hover.png", "");
	imageButtonCut.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	imageButtonCut.sethoverImages("btn-cut-default-hover.png", "btn-cut-active-hover.png", "");

	selectBtn.setToggleState(true, dontSendNotification);

	addAndMakeVisible(imageButtonCut);
	imageButtonCut.addListener(this);
	imageButtonCut.setToggleable(true);

	addAndMakeVisible(imageButtonCopy);
	imageButtonCopy.addListener(this);
	imageButtonCopy.setToggleable(true);
	imageButtonCopy.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	imageButtonCopy.sethoverImages("btn-copy-default-hover.png", "btn-copy-active-hover.png", "");
	optionUndo.makeVisibleAndAddListner(this);

	addAndMakeVisible(sculptBtn);
	sculptBtn.addListener(this);
	sculptBtn.setVisible(false);
	sculptBtn.setToggleable(true);

	optionUndo.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

	box.items.add(FlexItem(imageButtonPencil).withMargin({ 0,8,0,0 }).withFlex(1));
	box.items.add(FlexItem(imageButtonErase).withMargin({ 0,8,0,0 }).withFlex(1));
	box.items.add(FlexItem(selectBtn).withMargin({ 0,8,0,0 }).withFlex(1));
	box.items.add(FlexItem(imageButtonCut).withMargin({ 0,8,0,0 }).withFlex(1));
	box.items.add(FlexItem(imageButtonCopy).withMargin({ 0,8,0,0 }).withFlex(1));
	box.items.add(FlexItem(optionUndo).withMargin({ 0,8,0,0 }).withFlex(1));
}

AppGridControl::~AppGridControl()
{}

//==============================================================================
void AppGridControl::paint(juce::Graphics& g)
{
}

void AppGridControl::resized()
{
	box.performLayout(ui::Rectangle<float>{438, 10, 312, 44});
	gangBtn.setBounds(315, 10, 120, 44);
}

void AppGridControl::setGangMode(bool state)
{
	gangBtn.setToggleState(state, sendNotification);
}

void AppGridControl::buttonClicked(juce::Button* buttonThatWasClicked)
{
	auto noHighlight = ui::Theme::Instance().highlightColour(0);
	auto highlight = ui::Theme::Instance().highlightColour(3);
	auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

	boPencilSelected = imageButtonPencil.getToggleState();
	boEraseSelected = imageButtonErase.getToggleState();
	boCutIconSelected = imageButtonCut.getToggleState();
	boCopyIconSelected = imageButtonCopy.getToggleState();
	boSelectionIconSelected = selectBtn.getToggleState();
	boGangIconSelected = gangBtn.getToggleState();


	if (buttonThatWasClicked == &imageButtonPencil)
	{
		if (boPencilSelected)
			toolSelectionChanged.emit(GridToolType::GridPencilTool);
	}
	else if (buttonThatWasClicked == &imageButtonErase)
	{
		if (boEraseSelected)
		{
			toolSelectionChanged.emit(GridToolType::GridEraseTool);
			_pPatternPtr->delNotes(0, 0, -1, -1);
		}
	}
	else if (buttonThatWasClicked == &imageButtonCut)
	{
		if (boCutIconSelected)
		{
			toolSelectionChanged.emit(GridToolType::GridCutPasteTool);
			if (boCopyIconSelected)
				imageButtonCopy.setToggleState(false, dontSendNotification);
		}
		else
			toolSelectionChanged.emit(GridToolType::GridSelectTool);
	}
	else if (buttonThatWasClicked == &imageButtonCopy)
	{
		if (boCopyIconSelected)
		{
			toolSelectionChanged.emit(GridToolType::GridCopyPasteTool);
			if (boCutIconSelected)
				imageButtonCut.setToggleState(false, dontSendNotification);
		}
		else
			toolSelectionChanged.emit(GridToolType::GridSelectTool);
	}
	else if (buttonThatWasClicked == &optionUndo)
	{
		if (optionUndo.getToggleState())
			optionUndo.setToggleState(false, dontSendNotification);
		_pPatternPtr->onOptCtlButtonClicked(IgniteControlOptions::eKey::UNDO);
	}
	else if (buttonThatWasClicked == &sculptBtn)
	{
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptButtonOnState, sculptBtn.getToggleState());
		StepSequencer::getStepSequencerInstance()->setSculptState(sculptBtn.getToggleState());
		StepSequencer::getStepSequencerInstance()->repaint();
	}
	else if (buttonThatWasClicked == &gangBtn)
	{
		_pPatternPtr->setGangMode(boGangIconSelected);
		_pPatternPtr->resetGangStepState();
		_pPatternPtr->resetGangNoteState();
		_pPatternPtr->resetNoteSelection();
		AppGrid::getGridInstance()->repaint();
	}
	else if (buttonThatWasClicked == &selectBtn)
	{
		if (boSelectionIconSelected)
			toolSelectionChanged.emit(GridToolType::GridSelectTool);
	}

	if (selectBtn.getToggleState())
	{
		imageButtonCut.setEnabled(true);
		imageButtonCopy.setEnabled(true);
	}
	else
	{
		imageButtonCut.setEnabled(false);
		imageButtonCopy.setEnabled(false);
		if (imageButtonCut.getToggleState())
			imageButtonCut.setToggleState(false, dontSendNotification);
		if (imageButtonCopy.getToggleState())
			imageButtonCopy.setToggleState(false, dontSendNotification);
	}

	boCutIconSelected = imageButtonCut.getToggleState();
	boCopyIconSelected = imageButtonCopy.getToggleState();
}

bool AppGridControl::pannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue)
{
	bool setfocus = true;

	if (gridKeyFocusedItem == gridOptionsViewItemID::GRID_NO_FOCUS)
	{
		/*1st key after Page visible */
		gridKeyFocusedItem = gridOptionsViewItemID::GRID_GANG_EDIT;
	}
	else
	{
		pannelSendKey(false, param, KeyValue); // clear last Focus
		if (!AppGrid::getGridInstance()->getOptionsHandlerState())
			return true;
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RMOVELEFT:
			gridKeyFocusedItem = (gridKeyFocusedItem + 1 >= gridOptionsViewItemID::GRID_FOCUS_MAX ? (gridOptionsViewItemID::GRID_FOCUS_MAX) : gridKeyFocusedItem + 1);
			break;
		case FrontPannelParam::paramKey_RMOVERIGHT:
			gridKeyFocusedItem = (gridKeyFocusedItem - 1 <= gridOptionsViewItemID::GRID_NO_FOCUS ? (gridOptionsViewItemID::GRID_NO_FOCUS + 1) : gridKeyFocusedItem - 1);
			break;
		}
	}
	if (setfocus)
	{
		pannelSendKey(true, param, KeyValue);
	}
	return true;
}


void AppGridControl::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
{
	switch (gridOptionsView[gridKeyFocusedItem])
	{
	case GRID_GANG_EDIT:
		gangBtn.FPKeyHandler(isFocuse, param, 0);
		break;
	case GRID_SELECT:
		selectBtn.FPKeyHandler(isFocuse, param, 0);
		break;
	case GRID_PENCIL:
		imageButtonPencil.FPKeyHandler(isFocuse, param, 0);
		break;
	case GRID_ERASE:
		imageButtonErase.FPKeyHandler(isFocuse, param, 0);
		break;
	case GRID_CUT:
		imageButtonCut.FPKeyHandler(isFocuse, param, 0);
		break;
	case GRID_COPY:
		imageButtonCopy.FPKeyHandler(isFocuse, param, 0);
		break;
	case GRID_UNDO:
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
			optionUndo.FPKeyHandler(isFocuse, param, KeyValue);
		optionUndo.setState((Button::ButtonState)isFocuse);
		break;
	default:
		break;
	}
	repaint();
}
