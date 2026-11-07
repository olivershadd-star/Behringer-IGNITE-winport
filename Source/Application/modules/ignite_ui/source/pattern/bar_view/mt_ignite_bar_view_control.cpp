namespace ui
{
	StepSequencerControl::StepSequencerControl()
	{
		presetsButton.makeVisibleAndAddListner(this);
		presetsButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		presetsButton.setDisableImage("btn-link99x36-preset-disabled.png");
		presetsButton.sethoverImages("btn-link99x36-preset-default-hover.png", "btn-link99x36-preset-active-hover.png", "btn-link99x36-preset-disabled-hover.png");

		gridNote.makeVisible(this);
		parameter.makeVisible(this);
		timeBaseLabel.makeVisible(this);
		direction.makeVisible(this);
		lastStep.makeVisible(this);

		addAndMakeVisible(&directionListBox);
		addAndMakeVisible(&paramValueListBox);
		addAndMakeVisible(&timeBaseValueListBox);
		addAndMakeVisible(&padListBox);
		addAndMakeVisible(&firstStepListBox);
		addAndMakeVisible(&lastStepListBox);
		directionListBox.updateListOptionsWithSize(mt::Ignite::directions, 8);
		directionListBox.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		directionListBox.setJustification(juce::Justification::right);
		directionListBox.setValueColour(Theme::Instance().getColour(customOrange));
		directionListBox.setValueFont(18);
		directionListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,widthnumOfBars,470 });
		directionListBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		directionListBox.setTextColour(Theme::Instance().getColour(customBlue4));
		firstStepListBox.updateListOptionsWithSize(mt::Ignite::lastSteps, 16, 1);
		lastStepListBox.updateListOptions(mt::Ignite::lastSteps);
		timeBaseValueListBox.updateListOptions(mt::Ignite::tbvalues);
		timeBaseValueListBox.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		timeBaseValueListBox.setJustification(juce::Justification::right);
		timeBaseValueListBox.setValueColour(Theme::Instance().getColour(customOrange));
		timeBaseValueListBox.setValueFont(18);
		timeBaseValueListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,widthnumOfBars,430 });
		timeBaseValueListBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		timeBaseValueListBox.setTextColour(Theme::Instance().getColour(customBlue4));

		padListBox.updateListOptions(mt::Ignite::midiNoteNamesSharps);
		padListBox.setSelected(48);
		padListBox.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		padListBox.setJustification(juce::Justification::right);
		padListBox.setValueColour(Theme::Instance().getColour(customOrange));
		padListBox.setValueFont(18);
		padListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,widthnumOfBars,567 });
		padListBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		padListBox.setTextColour(Theme::Instance().getColour(customBlue4));

		BarInfoButton.makeVisibleAndAddListner(this);
		BarInfoButton.showTitleAndBorder(true);

		paramValueListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,widthparamValue,heightparamValue });
		paramValueListBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		paramValueListBox.setTextColour(Theme::Instance().getColour(customBlue4));
		paramValueListBox.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		paramValueListBox.setJustification(juce::Justification::right);
		paramValueListBox.setValueColour(Theme::Instance().getColour(customOrange));
		paramValueListBox.setValueFont(17);

		firstStepListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		firstStepListBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		firstStepListBox.setTextColour(Theme::Instance().getColour(customBlue4));
		firstStepListBox.setSelected(0);

		lastStepListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		lastStepListBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		lastStepListBox.setTextColour(Theme::Instance().getColour(customBlue4));

		lastStepListBox.setSelected(15);
		lastStepListBox.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		lastStepListBox.setJustification(juce::Justification::right);
		lastStepListBox.setValueColour(Theme::Instance().getColour(customOrange));
		lastStepListBox.setValueFont(18);

		padListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });
		paramValueListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,270 });
		timeBaseValueListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,350 });
		directionListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,360 });
		lastStepListBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });

		directionListBox.onSelectionChanged = [this](int value, const juce::String&)
		{
			IgnitePattern* _pPatternPtr = IgnitePattern::getAppPatternInstance();
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			auto currentDirection = (int)_pPatternPtr->getBarData(mt::Ignite::barDataIndex::DIR_INDEX, _pPatternPtr->getCurrentBarId());
			if (currentDirection != value)
			{
				_pPatternPtr->setBarData(mt::Ignite::barDataIndex::DIR_INDEX, _pPatternPtr->getCurrentBarId(), (uint8_t)value, false);
				//directionListBox.setTitleText("Direction*");
				if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{
					_pPatternPtr->setPatternDataUpdateStatus(true);
					_pPatternPtr->updatePatternEditIndication();
					_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				}
			}
		};

		padListBox.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			IgnitePattern::getAppPatternInstance()->setActiveNode((uint8_t)value);
			//IgnitePattern::getAppPatternInstance()->setNodeData(mt::Ignite::nodeDataIndex::NOTE_NUM, (uint8_t)value, (uint8_t)value, true);
			StepSequencer::getStepSequencerInstance()->repaint();
		};

		timeBaseValueListBox.onSelectionChanged = [this](int value, const juce::String&)
		{
			IgnitePattern* _pPatternPtr = IgnitePattern::getAppPatternInstance();
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if ((int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::TIMEBASE) != value)
			{
				_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::TIMEBASE, (uint8_t)value, false);
				//timeBaseValueListBox.setTitleText("Time Base*");
				if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{
					_pPatternPtr->setPatternDataUpdateStatus(true);
					_pPatternPtr->updatePatternEditIndication();
					_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				}
				_pPatternPtr->updateTickDelayRange();
			}
		};

		firstStepListBox.onApplyValueChanged = [this](int value, const juce::String& name)
		{
			IgnitePattern* _pPatternPtr = IgnitePattern::getAppPatternInstance();
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pPatternPtr->rotatePattern((uint16_t)(value / 16), (uint16_t)(value % 16));
			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}

		};

		lastStepListBox.onSelectionChanged = [this](int value, const juce::String&)
		{
			IgnitePattern* _pPatternPtr = IgnitePattern::getAppPatternInstance();
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if ((int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::LASTSTEP) != value)
			{
				_pPatternPtr->setPatternData(mt::Ignite::ptDataIndex::LASTSTEP, (int16_t)value, false);
				//lastStepListBox.setTitleText("Last Step*");
				if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
				{
					_pPatternPtr->setPatternDataUpdateStatus(true);
					_pPatternPtr->updatePatternEditIndication();
					_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
					_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
				}
			}
		};

		/*parameterViewControl.controlParamGridChanged.connect([this](int param)
			{
				paramValueListBox.setSelected(param);
			});*/

			//connect signals
		paramValueListBox.onValueChanged = [this](juce::String value)
		{
			auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

			_pPatternPtr->setActiveParamControl(value);
			switch (s_mapStringToParamValueType[value.toStdString()])
			{
			case eVelocity:
				controlParamChanged.emit(value);
				_pPatternPtr->setThreshold(maxVelocity);
				break;

			case eLengthSteps:
				_pPatternPtr->setThreshold((((int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM) + 1) * 16) / 2);
				controlParamChanged.emit(value);
				break;

			case eLengthTick:
				_pPatternPtr->setThreshold(_pPatternPtr->getTickRange().max);
				controlParamChanged.emit(value);
				break;

			case eDelay:
				_pPatternPtr->setThreshold(((_pPatternPtr->getDelayRange().max + 1) * 2)-1);
				controlParamChanged.emit(value);
				break;
			}
			//paramValueListBox.setTitleText("Parameter*");

			if (!IgnitePatternConfig::getAppPatternConfigInstance()->isAutoSaveEnabled())
			{
				_pPatternPtr->setPatternDataUpdateStatus(true);
				_pPatternPtr->updatePatternEditIndication();
				_pPatternPtr->enableControlButton(IgniteControlOptions::SAVE, true);
				_pPatternPtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		};

		controlFlex1.items.add(FlexItem(padListBox).withMargin({ 0,4,0,0 }).withFlex(1));
		controlFlex1.items.add(FlexItem(paramValueListBox).withMargin({ 0,4,0,0 }).withFlex(1));
		controlFlex1.items.add(FlexItem(timeBaseValueListBox).withMargin({ 0,4,0,0 }).withFlex(1));
		controlFlex1.items.add(FlexItem(directionListBox).withMargin({ 0,4,0,0 }).withFlex(1));
		controlFlex1.items.add(FlexItem(lastStepListBox).withMargin({ 0,0,0,0 }).withFlex(1));

		padListBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		paramValueListBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		timeBaseValueListBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		directionListBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		lastStepListBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	StepSequencerControl::~StepSequencerControl()
	{}

	void StepSequencerControl::updateAccidentals(bool state)
	{
		state ? padListBox.updateListOptions(mt::Ignite::midiNoteNamesFlats)
			: padListBox.updateListOptions(mt::Ignite::midiNoteNamesSharps);
	}

	void StepSequencerControl::enableDisableNoteBox(bool state)
	{
		padListBox.setAlpha(state ? 1.0f : 0.3f);
		gridNote.setAlpha(state ? 1.0f : 0.3f);
		padListBox.setEditable(state);
	}

	void StepSequencerControl::setPresetButtonVisibility(bool state)
	{
		if (presetsButton.getToggleState())
			presetsButton.setToggleState(false, sendNotification);
		presetsButton.setEnabled(state);
	}

	void StepSequencerControl::updateLableText(mt::Ignite::ptDataIndex item_id, bool state)
	{
		switch (item_id)
		{
		case mt::Ignite::ptDataIndex::DIR_INDEX:
			//state ? directionListBox.setTitleText("Direction*") : directionListBox.setTitleText("Direction");
			break;
		case mt::Ignite::ptDataIndex::TIMEBASE:
			//state ? timeBaseValueListBox.setTitleText("Time Base*") : timeBaseValueListBox.setTitleText("Time Base");
			break;
		case mt::Ignite::ptDataIndex::LASTSTEP:
			//state ? lastStepListBox.setTitleText("Last Step*") : lastStepListBox.setTitleText("Last Step");
			break;
		}
	}

	void StepSequencerControl::paint(juce::Graphics& g)
	{
		auto patternPtr = IgnitePattern::getAppPatternInstance();
		paramValueListBox.setSelected(patternPtr->getActiveParamControl());
		directionListBox.setSelected((int)patternPtr->getBarData(mt::Ignite::barDataIndex::DIR_INDEX, patternPtr->getCurrentBarId()));
		timeBaseValueListBox.setSelected((int)patternPtr->getPatternData(mt::Ignite::ptDataIndex::TIMEBASE));
		//lastStepListBox.setSelected((int)patternPtr->getPatternData(mt::Ignite::ptDataIndex::LASTSTEP));
		padListBox.setSelected((int)patternPtr->getPatternData(mt::Ignite::ptDataIndex::NODE_ID));

		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-container-176x80-default.png"));
		Image activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-container-176x80-default-hover.png"));
		g.drawImage(padListBox.getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 0, 0, 176, 36 }, RectanglePlacement::centred);
		g.drawImage(paramValueListBox.getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 180, 0, 176, 36 }, RectanglePlacement::centred);
		g.drawImage(timeBaseValueListBox.getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 360, 0, 176, 36 }, RectanglePlacement::centred);
		g.drawImage(directionListBox.getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 540, 0, 176, 36 }, RectanglePlacement::centred);
		g.drawImage(lastStepListBox.getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 720, 0, 176, 36 }, RectanglePlacement::centred);
	}

	void StepSequencerControl::resized()
	{
		controlFlex1.performLayout(Rectangle(0, 0, 896, 36));
		presetsButton.setBounds(906, 0, 99, 36);
		gridNote.setBounds(8, 8, 176, 20);
		parameter.setBounds(180, 8, 176, 20);
		timeBaseLabel.setBounds(368, 8, 176, 20);
		direction.setBounds(548, 8, 176, 20);
		lastStep.setBounds(728, 8, 176, 20);
		padListBox.toFront(true);
		paramValueListBox.toFront(true);
		timeBaseValueListBox.toFront(true);
		directionListBox.toFront(true);
		lastStepListBox.toFront(true);
	}

	void StepSequencerControl::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &presetsButton)
		{
			presetOn.emit(presetsButton.getToggleState());
		}
	}

	void StepSequencerControl::updateRangeText()
	{
		juce::String rangeLabel;
		rangeLabel = rangeLabel.formatted("%d-%d", rangeLow, rangeHigh);
	}

	void StepSequencerControl::updateLastStep(bool is_internal)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

		auto num_bars = (int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::BARNUM);
		lastStepListBox.updateListOptionsWithSize(mt::Ignite::lastSteps, ((num_bars + 1) * 16));
		firstStepListBox.updateListOptionsWithSize(mt::Ignite::lastSteps, ((num_bars + 1) * 16));
		firstStepListBox.setSelected(0);
		lastStepListBox.setSelected((int)_pPatternPtr->getPatternData(mt::Ignite::ptDataIndex::LASTSTEP));
	}

	bool StepSequencerControl::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramRot_ROW:
			if ((keyValue == ROTARY_LEFT || keyValue == ROTARY_FASTLEFT || keyValue == ROTARY_SUPERFASTLEFT))
			{
				padListBox.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_MINUS_NAV, keyValue);
			}
			else if ((keyValue == ROTARY_RIGHT || keyValue == ROTARY_FASTRIGHT || keyValue == ROTARY_SUPERFASTRIGHT))
			{
				padListBox.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_PLUS_NAV, keyValue);
			}
			break;
		case FrontPannelParam::paramKey_ROTARYROW:
			if ((FrontPannelKeyStatus)keyValue == FrontPannelKeyStatus::paramKeyStatusPressed)
				paramValueListBox.FPKeyHandler(true, (paramId_t)param, keyValue);
			break;
		}
		return true;
	}

	void StepSequencerControl::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (StepSequencer::getStepSequencerInstance()->keyFocusedItem)
		{
		case StepSequencer::barViewItemID::GRID_NODE:
			padListBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case StepSequencer::barViewItemID::PARAM:
			paramValueListBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case StepSequencer::barViewItemID::TIMEBASE:
			timeBaseValueListBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case StepSequencer::barViewItemID::DIRECTION:
			directionListBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case StepSequencer::barViewItemID::LAST_STEP:
			lastStepListBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case StepSequencer::barViewItemID::PRESET:
			presetsButton.FPKeyHandler(isFocuse, param, 0);
			repaint();
			break;
		default:
			break;
		}
		repaint();
	}
}
