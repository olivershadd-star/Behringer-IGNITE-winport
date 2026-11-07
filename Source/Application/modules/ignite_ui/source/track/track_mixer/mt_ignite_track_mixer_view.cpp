//#include "mt_ignite_bar_view.h"
#define TRACK_MIXER_BUTTON_SPACE 4
#define NOTE_PORT 4
namespace ui
{
	TrackMixer::TrackMixer()
	{
		addAndMakeVisible(trackMixerControl);
		trackBankIndex = 1;

		selectedIndex.resize(64);

		popupPtr = CommonPopUp::getCommonPopupInstance();

		trackMixerControl.rightNudgeChanged.connect([this](bool nudgeRight)
			{
				auto _trackPtr = IgniteTrack::GetAppTrackInstance();
				getTrackMixerBankAndUpdate(!nudgeRight);
				_trackPtr->getNextTrackBankAndUpdate(true);
				AppMainmode::getMainModeInstance()->setFpFillAndSoloLedState();
				AppMainmode::getMainModeInstance()->setFpEditTrackLedState();
			});

		trackMixerControl.leftNudgeChanged.connect([this](bool nudgeLeft)
			{
				auto _trackPtr = IgniteTrack::GetAppTrackInstance();
				getTrackMixerBankAndUpdate(nudgeLeft);
				_trackPtr->getNextTrackBankAndUpdate(false);
				AppMainmode::getMainModeInstance()->setFpFillAndSoloLedState();
				AppMainmode::getMainModeInstance()->setFpEditTrackLedState();
			});


		trackMixerControl.controlParamChanged.connect([this](juce::String param)
			{
				updateTrackData();
				setActiveParamControl(param);
				std::fill(selectedIndex.begin(), selectedIndex.end(), 0);
			});

		rangeLow = 0;
		rangeHigh = 16;
		stepPreset.setQl(16);
		updateTrackData();

		trackMixerOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(trackMixerOptCtl);
		trackMixerOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		trackMixerOptCtl->addOptCtlListener(this);
	}

	void TrackMixer::getTrackMixerBankAndUpdate(bool direction)
	{
		auto _trackPtr = IgniteTrack::GetAppTrackInstance();
		if (_trackPtr->getTotalTrackBank() > 0)

		{
			std::fill(selectedIndex.begin(), selectedIndex.end(), true);
			if (direction)
			{
				trackBankIndex++;
				if (trackBankIndex > _trackPtr->getTotalTrackBank())
					trackBankIndex = 1;
			}
			else
			{
				trackBankIndex--;
				if (trackBankIndex <= 0)
					trackBankIndex = _trackPtr->getTotalTrackBank();
			}
			refreshTrackMixerUI();
			repaint();
		}
	}

	void TrackMixer::getSelectedTrackMixerBankAndUpdate(int trackMixerBank)
	{
		auto _trackPtr = IgniteTrack::GetAppTrackInstance();
		if (_trackPtr->getTotalTrackBank() > 0)
		{
			trackBankIndex = trackMixerBank;
			repaint();
		}
	}

	void TrackMixer::buttonClicked(juce::Button* buttonThatWasClicked)
	{
	}

	void TrackMixer::paint(juce::Graphics& g)
	{
		if (trackMixerDataUpdated)
			MenuMode::GetMenuModeInstance()->setHeader("Tracks Instrument Mixer*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Tracks Instrument Mixer");

		if (buttonWidth == 0)
			return;

		g.fillAll(Theme::Instance().backgroundColour(5));

		//draw markings
		float markingWidth = levelRect.getHeight() / 4;
		float y = markingWidth + levelRect.getY();
		for (int i = 0; i < 1; i++)
		{
			g.drawLine(0, y, static_cast<float>(getWidth()), y);
			y += markingWidth;
		}

		// draw levels
		auto levelIndex = 0;
		bool* trackState = getTrackMixerTrackState();

		for (int i = (trackBankIndex - 1) * 16; i <= (trackBankIndex * 16) - 1; i++)
		{
			int index = i;

			selectedIndex[index - rangeLow] = true;
			auto value = getParamFromEngine(getActiveParamControl(), index);
			auto lbr = getLevelButtonRect((levelIndex++ - rangeLow) + 1);
			float unit_height = lbr.getHeight() * (1.0f / s_mapStringToParamMaxType[getActiveParamControl()]);
			float posFoVel = (float)value * unit_height; //127 is velocity of selected note
			posFoVel = lbr.getHeight() - posFoVel;
			lbr.setY(lbr.getY() + posFoVel);
			lbr.setHeight(lbr.getHeight() - posFoVel);
			g.setColour(Theme::Instance().gettrackMixerParam((int)s_mapStringToParamValueType[getActiveParamControl()], (int)((value / 127.0) * 100)));
			g.fillRoundedRectangle(lbr.toFloat(), 3.0f);

			auto center = lbr.getCentre();
			g.setColour(juce::Colours::white);
			g.drawText(juce::String(value), lbr, Justification::centred);

			if (trackState[index])
			{
				g.setColour(Theme::Instance().getColour(CommonColorID::neutralWhite));
				g.drawRect(getLevelButtonRect((index - rangeLow) + 1), 1.0f);
			}
		}

		//draw buttons
		auto btnIndex = 0;
		for (int i = ((trackBankIndex - 1) * 16) + 1; i <= (trackBankIndex * 16) + 1; i++)
		{
			if (getParamFromEngine(getActiveParamControl(), i - 2) != -1)
				g.setColour(juce::Colour(0xFF644200));
			else
				g.setColour(juce::Colour(0xFF354662));

			auto btnRect = getStepButtonRect(btnIndex++);
			g.fillRect(btnRect);
			auto center = btnRect.getCentre();

			g.setColour(juce::Colours::white);
			g.drawText("Track " + juce::String(i - 1 + rangeLow), btnRect, Justification::centred);
		}
	}

	void TrackMixer::resized()
	{
		trackMixerControl.setBounds(xStartStepControl, 432, widthStepControl + 60, heightStepCtrl);
		stepRect = ui::Rectangle<float>(xStartStepRect, 400, 966, heightStepRect);
		levelRect = ui::Rectangle<float>(xStartLevelRect, 60, 966, heightLevelRect - 30);
		calculateButtonWidth();
	}

	ui::Rectangle<float> TrackMixer::getLevelButtonRect(int index)
	{
		float xPos;
		if (index == 1)
		{
			xPos = 0;
		}
		else
		{
			xPos = levelRect.getX() + ((index - 1) * STEP_BUTTON_SPACE) + ((index - 1) * buttonWidth);
		}

		return ui::Rectangle<float>(xPos, levelRect.getY(), buttonWidth, levelRect.getHeight());
	}

	ui::Rectangle<float> TrackMixer::getStepButtonRect(int index)
	{
		float xPos;

		if (index == 1)
		{
			xPos = 0;
		}
		else
		{
			xPos = stepRect.getX() + ((index - 1) * STEP_BUTTON_SPACE) + ((index - 1) * buttonWidth);
		}

		return ui::Rectangle<float>(xPos, stepRect.getY() + 2, buttonWidth, stepButtonHeight);
	}

	void TrackMixer::mouseDrag(const MouseEvent& event)
	{
		enableDisableButton(event.position);
	}

	void TrackMixer::mouseUp(const MouseEvent& event)
	{
		lastIndex = -1;
	}

	void TrackMixer::mouseDown(const MouseEvent& event)
	{
		enableDisableButton(event.position);
	}

	void TrackMixer::updateTrackData()
	{
		repaint();
	}

	void TrackMixer::calculateButtonWidth()
	{
		int range = (rangeHigh - rangeLow);
		float effectiveWidth = stepRect.getWidth() - (2 * TRACK_MIXER_BUTTON_SPACE) - ((range - 1) * 1);
		buttonWidth = effectiveWidth / range;
		repaint();
	}

	void TrackMixer::refreshTrackMixerUI()
	{
	}

	void TrackMixer::enableDisableButton(juce::Point<float> position)
	{
		int index = static_cast<int>((position.getX() - 2) / buttonWidth);
		index = static_cast<int>((position.getX() - index - 2) / buttonWidth);

		index = index + ((trackBankIndex - 1) * 16);

		if (selected_track > -1)
		{
			resetTrackMixerTrackState();
			selected_track = -1;
		}

		if (levelRect.contains(position))
		{
			float y = position.getY();
			int velocity = static_cast<int>(std::round((s_mapStringToParamMaxType[getActiveParamControl()] * (y - levelRect.getY())) / levelRect.getHeight()));
			velocity = s_mapStringToParamMaxType[getActiveParamControl()] - velocity;

			if (velocity < 0 || velocity > s_mapStringToParamMaxType[getActiveParamControl()])
				return;

			if (getParamFromEngine(getActiveParamControl(), index) != -1)
				setParamToEngine(getActiveParamControl(), index, (int8_t)velocity);
			repaint();
		}
	}

	void TrackMixer::setParamToEngine(juce::String param, int index, int8_t data)
	{
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramTMActiveTrack, index);

		if (param == "Volume")
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramTMVolume, data);
		else
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramTMPan, data);

		trackMixerOptCtl->enableKey(IgniteControlOptions::SAVE, true);
		trackMixerOptCtl->enableKey(IgniteControlOptions::UNDO, true);
		trackMixerDataUpdated = true;
	}


	int8_t TrackMixer::getParamFromEngine(juce::String param, int index)
	{
		std::vector<IgniteParamList> trackMixerParams;
		IgniteParamList paramsList;

		trackMixerParams.clear();

		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramTMActiveTrack, index);

		if (param == "Volume")
		{
			paramsList.param = (paramId_t)SettingsTrackInstrumentMixerParam::paramTMVolume;
			trackMixerParams.push_back(paramsList);
			trackMixerParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, trackMixerParams);
			return trackMixerParams[0].MsgValue.get< std::int8_t >();
		}
		else
		{
			paramsList.param = (paramId_t)SettingsTrackInstrumentMixerParam::paramTMPan;
			trackMixerParams.push_back(paramsList);
			trackMixerParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, trackMixerParams);
			return trackMixerParams[0].MsgValue.get< std::int8_t >();
		}
	}

	bool TrackMixer::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool* trackState = getTrackMixerTrackState();
		bool setfocus = true;
		bool handled = false;

		if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_WIPEDATA)
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if (param == (paramId_t)FrontPannelParam::paramRot_BAR)
		{
			if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
			{
				KeyFocusedItem = TrackMixerViewItemID::LEFT_NUDGE;
				trackMixerControl.leftNudgeChanged.emit(true);
			}
			else if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
			{
				KeyFocusedItem = TrackMixerViewItemID::RIGHT_NUDGE;
				trackMixerControl.rightNudgeChanged.emit(true);
			}
			return true;
		}

		if (param == (paramId_t)FrontPannelParam::paramKey_ROTARYROW)
		{
			if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusReleased)
				return true;

			if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusPressed)
			{
				if (getActiveParamControl() == "Volume")
				{
					KeyFocusedItem = TrackMixerViewItemID::PAN_PARAM;
					trackMixerControl.PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, 0);
				}
				else if (getActiveParamControl() == "Pan")
				{
					KeyFocusedItem = TrackMixerViewItemID::VOLUME_PARAM;
					trackMixerControl.PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, 0);
				}
				return true;
			}
		}

		switch ((FrontPannelParam)param)
		{
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
			selected_track = ((trackBankIndex - 1) * 16) + (param - (paramId_t)FrontPannelParam::paramRot_PADROT1);
			handled = setSelectedTrackMixerValue(param, KeyValue, selected_track);
			break;
		default:
			break;
		}

		if (!handled)
		{
			if ((option_handler_enabled == TRACKMIXER_TRACKS))
			{
				return TrackKeyHandler(param, KeyValue);
			}
			if (option_handler_enabled == TRACKMIXER_OPTIONS && param != (paramId_t)FrontPannelParam::paramKey_PAGESHIFT && (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT ||
				param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_RSELECT || param == (paramId_t)FrontPannelParam::paramKey_RETURN_NAV))
			{
				PannelKeyOptionsHandler(param, KeyValue);
			}
			else
			{
				if (KeyFocusedItem == TrackMixerViewItemID::NO_FOCUS)
				{
					/*1st key after Page visible */
					KeyFocusedItem = TrackMixerViewItemID::VOLUME_PARAM;

					if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
					{
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::TRACK_WINDOW);
						return true;
					}
				}
				else
				{
					PannelSendKey(false, param, KeyValue); // clear last Focus
					switch ((FrontPannelParam)param)
					{
					case FrontPannelParam::paramKey_RMOVELEFT:
						KeyFocusedItem = (KeyFocusedItem + 1 >= TrackMixerViewItemID::FOCUS_MAX ? (TrackMixerViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
						break;
					case FrontPannelParam::paramKey_RMOVERIGHT:
						KeyFocusedItem = (KeyFocusedItem - 1 <= TrackMixerViewItemID::NO_FOCUS ? (TrackMixerViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
						break;
					case FrontPannelParam::paramKey_RETURN_NAV:
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::TRACK_WINDOW);
						break;

					case FrontPannelParam::paramKey_PAGESHIFT:
						if (option_handler_enabled == TRACKMIXER_PARAM)
						{
							option_handler_enabled = TRACKMIXER_OPTIONS;
						}
						else if (option_handler_enabled == TRACKMIXER_OPTIONS)
						{
							option_handler_enabled = TRACKMIXER_PARAM;
						}
						else if (option_handler_enabled == TRACKMIXER_TRACKS)
						{
							resetTrackMixerTrackState();
							option_handler_enabled = TRACKMIXER_PARAM;
						}
						PannelKeyOptionsHandler(param, KeyValue);
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
						KeyFocusedItem = TrackMixerViewItemID::NO_FOCUS;
						option_handler_enabled = TRACKMIXER_TRACKS;
						selected_track = param - 31;
						trackState[param - 31] = true;
						setfocus = false;
						break;
					}
					if (option_handler_enabled != TRACKMIXER_PARAM)
						return true;
				}
				if (setfocus)
				{
					PannelSendKey(true, param, KeyValue);
				}
			}
		}

		return true;
	}

	bool TrackMixer::TrackKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool* trackState = getTrackMixerTrackState();

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_PAGESHIFT:
			option_handler_enabled = TRACKMIXER_PARAM;
			resetTrackMixerTrackState();
			PannelSendKey(false, param, KeyValue);
			KeyFocusedItem = VOLUME_PARAM;
			PannelSendKey(true, param, KeyValue);
			break;
		case FrontPannelParam::paramKey_RMOVELEFT:
		case FrontPannelParam::paramKey_RMOVERIGHT:
		case FrontPannelParam::paramKey_RSELECT:
			setTrackMixerValues(param, selected_track);
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
			KeyFocusedItem = TrackMixerViewItemID::NO_FOCUS;
			selected_track = param - 31;
			resetTrackMixerTrackState();
			trackState[param - 31] = true;
			break;
		}
		repaint();
		return true;
	}

	bool TrackMixer::setSelectedTrackMixerValue(paramId_t param, uint32_t KeyValue, int index)
	{
		int threshold = s_mapStringToParamMaxType[getActiveParamControl()];
		int value = getParamFromEngine(getActiveParamControl(), index);

		if (value != -1)
		{
			if (((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT)) && (value < threshold))
				setParamToEngine(getActiveParamControl(), index, (int8_t)(int)getParamFromEngine(getActiveParamControl(), index) + 1);
			else if (((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT)) && (value > 0))
				setParamToEngine(getActiveParamControl(), index, (int8_t)(int)getParamFromEngine(getActiveParamControl(), index) - 1);
		}

		repaint();
		return true;
	}

	void TrackMixer::setTrackMixerValues(paramId_t param, int index)
	{
		if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT) || (param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT))
		{
			if (getParamFromEngine(getActiveParamControl(), index) != -1)
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
					setParamToEngine(getActiveParamControl(), index, (int8_t)(int)getParamFromEngine(getActiveParamControl(), index) + 1);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT)
					setParamToEngine(getActiveParamControl(), index, (int8_t)(int)getParamFromEngine(getActiveParamControl(), index) - 1);
			}
		}
	}

	void TrackMixer::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		switch (TrackMixerViewItems[KeyFocusedItem])
		{
		case VOLUME_PARAM:
		case PAN_PARAM:
		case LEFT_NUDGE:
		case RIGHT_NUDGE:
			trackMixerControl.PannelSendKey(isFocuse, param, 0);
			break;
		default:
			break;
		}
		repaint();
	}

	int TrackMixer::isEditing()
	{
		int index = 0;

		if (OptFocusedItem == OPT_TRACKVIEW)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = OPT_TRACKVIEW;
			}
		}

		return index;
	}

	bool TrackMixer::PannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue)
	{
		bool* trackState = getTrackMixerTrackState();
		bool setfocus = true;
		int editItem = TrackMixerOptionsViewItemID::OPT_NO_FOCUS;

		if (OptFocusedItem == TrackMixerOptionsViewItemID::OPT_NO_FOCUS)
		{
			/*1st key after Page visible */
			OptFocusedItem = TrackMixerOptionsViewItemID::OPT_UNDO;
		}
		else
		{
			editItem = isEditing();
			if (editItem)
			{
				if (OptFocusedItem != editItem)
				{
					PannelSendOptionsKey(false, param, KeyValue);
					OptFocusedItem = editItem;
				}
				setfocus = true;
			}
			else
			{
				PannelSendOptionsKey(false, param, KeyValue); // clear last Focus
				if (option_handler_enabled != TRACKMIXER_OPTIONS)
					return true;
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					OptFocusedItem = (OptFocusedItem + 1 >= TrackMixerOptionsViewItemID::OPT_FOCUS_MAX ? (TrackMixerOptionsViewItemID::OPT_FOCUS_MAX) : OptFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					OptFocusedItem = (OptFocusedItem - 1 <= TrackMixerOptionsViewItemID::OPT_NO_FOCUS ? (TrackMixerOptionsViewItemID::OPT_NO_FOCUS + 1) : OptFocusedItem - 1);
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
					KeyFocusedItem = TrackMixerViewItemID::NO_FOCUS;
					option_handler_enabled = TRACKMIXER_TRACKS;
					selected_track = param - 31;
					trackState[param - 31] = true;
					setfocus = false;
					break;
				}
			}
		}
		if (setfocus)
		{
			PannelSendOptionsKey(true, param, KeyValue);
		}
		return true;
	}

	void TrackMixer::PannelSendOptionsKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (OptionsView[OptFocusedItem])
		{
		case OPT_UNDO:
			trackMixerOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
			break;
		case OPT_TRACKVIEW:
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				popupPtr->FPKeyHandler(isFocuse, param, KeyValue);
			}
			else
			{
				trackMixerOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::TRACKVIEW, isFocuse, param, KeyValue);
			}
			break;
		}
		repaint();
	}

	TrackMixer::~TrackMixer()
	{
		cleanup();
	}

	void TrackMixer::cleanup()
	{
	}

	void TrackMixer::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (this->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("Save ", 604, 290);
					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String(" Save Tracks Instrument Mixer Configuration edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgSave, 0);
							trackMixerOptCtl->enableKey(IgniteControlOptions::SAVE, false);
							trackMixerOptCtl->enableKey(IgniteControlOptions::UNDO, false);
							trackMixerDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (trackMixerDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> trackMixerCfgParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsTrackInstrumentMixerParam::paramUndoListCmd;
					trackMixerCfgParamList.push_back(params);
					trackMixerCfgParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, trackMixerCfgParamList);
					if (trackMixerCfgParamList.size() == 1)
					{
						trackMixerDataUpdated = false;
						trackMixerOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						trackMixerOptCtl->enableKey(IgniteControlOptions::UNDO, false);
					}
					repaint();
				}
			}
			else if (option == IgniteControlOptions::TRACKVIEW)
			{
				if (trackMixerDataUpdated)
				{
					if (popupPtr->isDialogOpen.get() != true)
					{
						popupPtr->close();
						popupPtr->setPopUpPropories("Save Track Instrument Mixer edits", 604, 235);
						popupPtr->setbtnsize(265, 44);
						popupPtr->setInfoText(String("Save Track Instrument Mixer edits, Edits will be lost on pressing 'No' !!!"));
						popupPtr->addImageButton("Save", "btn-deleteyes-default.png", "btn-deleteyes-active.png", 1);
						popupPtr->addImageButton("Cancel", "btn-deleteno-default.png", "btn-deleteno-active.png", 2);
						popupPtr->popupType = POPUP_WIPEDATA;
						popupPtr->isCloseButtonVisible(false);
						popupPtr->show();
						popupPtr->onSelectionChanged = [this](int r)
						{
							if (r == 1)
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgSave, 0);
							else
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (paramId_t)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgCancel, 0);
							trackMixerDataUpdated = false;

							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);

							AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::TRACK);
							IgniteTrack::GetAppTrackInstance()->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::TRACK_WINDOW);
						};
					}
				}
				else
				{
					AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::TRACK);
					IgniteTrack::GetAppTrackInstance()->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::TRACK_WINDOW);
				}
			}
		}
	}
}
