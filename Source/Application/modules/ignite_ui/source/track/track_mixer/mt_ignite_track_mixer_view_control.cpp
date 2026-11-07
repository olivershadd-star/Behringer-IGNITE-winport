namespace ui
{
	TrackMixerControl::TrackMixerControl()
	{
		trackBankButton.makeVisible(this);
		trackBankButton.showTitleAndBorder(true);

		leftNudgeButton.makeVisibleAndAddListner(this);
		rightNudgeButton.makeVisibleAndAddListner(this);
		addAndMakeVisible(&nudgeText);
		nudgeText.setButtonText("TRACK BANK 1/1");
		nudgeText.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		leftNudgeButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		rightNudgeButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		volumeButton.makeVisibleAndAddListner(this);
		volumeButton.setToggleable(true);
		volumeButton.setToggleState(true, dontSendNotification);
		volumeButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		volumeButton.sethoverImages("btn-bottom-volume-default-hover.png","btn-bottom-volume-active-hover.png","btn-bottom-volume-disabled.png");

		panButton.makeVisibleAndAddListner(this);
		panButton.setToggleable(true);
		panButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		panButton.sethoverImages("btn-bottom-pan-default-hover.png", "btn-bottom-pan-active-hover.png", "btn-bottom-pan-disabled.png");
		getAssets();
	}
	TrackMixerControl::~TrackMixerControl()
	{}

	void TrackMixerControl::getAssets()
	{
		imageScrollBtmDefault= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-bottom-default.png"));
		imageScrollBtmDefaultHover=juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-option-bottom-default-hover.png"));
		imageScrollLftDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-left-default.png"));
		imageScrollLftDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-left-default-hover.png"));
		imageScrollRgsDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-right-default.png"));
		imageScrollRgtDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scroll-caret-right-default-hover.png"));
	}

	void TrackMixerControl::paint(juce::Graphics& g)
	{
		auto trackMixerObj = TrackMixer::GetTrackMixerInstance();
		g.fillAll(Theme::Instance().backgroundColour(5));
		nudgeText.setButtonText("TRACK BANK " + String(trackMixerObj->trackBankIndex) + "/" + String(IgniteTrack::GetAppTrackInstance()->getTotalTrackBank()));

		Image Draw = nudgeText.isMouseOver() ? imageScrollBtmDefaultHover : imageScrollBtmDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 260, 3, 200, 36 }, RectanglePlacement::centred);

		Draw = (leftNudgeButton.isMouseOver() || leftNudgeButton.isFocused) ? imageScrollLftDefaultHover : imageScrollLftDefault;
		g.drawImage(Draw, ui::Rectangle<float>{262, 5, 24, 32}, RectanglePlacement::centred);
		
		Draw = (rightNudgeButton.isMouseOver() || rightNudgeButton.isFocused) ? imageScrollRgtDefaultHover : imageScrollRgsDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 434, 5, 24, 32 }, RectanglePlacement::centred);
	}

	void TrackMixerControl::resized()
	{
		leftNudgeButton.setBounds(262,5,24,32);
		rightNudgeButton.setBounds(434, 5, 24, 32);
		volumeButton.setBounds(0, 3, 120, 36);
		panButton.setBounds(130, 3, 120, 36);
		nudgeText.setBounds(260,3,200,36);
		leftNudgeButton.toFront(true);
		rightNudgeButton.toFront(true);
	}

	void TrackMixerControl::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		auto trackMixerPtr = TrackMixer::GetTrackMixerInstance();

		if (buttonThatWasClicked == &rightNudgeButton)
		{
			trackMixerPtr->KeyFocusedItem = trackMixerPtr->TrackMixerViewItemID::RIGHT_NUDGE;
			rightNudgeChanged.emit(rightNudgeButton.getToggleState());
		}
		else if (buttonThatWasClicked == &leftNudgeButton)
		{
			trackMixerPtr->KeyFocusedItem = trackMixerPtr->TrackMixerViewItemID::LEFT_NUDGE;
			leftNudgeChanged.emit(leftNudgeButton.getToggleState());
		}
		else if (buttonThatWasClicked == &volumeButton)
		{
			trackMixerPtr->KeyFocusedItem = trackMixerPtr->TrackMixerViewItemID::VOLUME_PARAM;
			panButton.setToggleState(!volumeButton.getToggleState(), dontSendNotification);
			trackMixerPtr->setActiveParamControl(volumeButton.getButtonText());
			controlParamChanged.emit(volumeButton.getButtonText());
			trackMixerPtr->setThreshold(maxVelocity);
		}
		else if (buttonThatWasClicked == &panButton)
		{
			trackMixerPtr->KeyFocusedItem = trackMixerPtr->TrackMixerViewItemID::PAN_PARAM;
			volumeButton.setToggleState(!panButton.getToggleState(), dontSendNotification);
			trackMixerPtr->setActiveParamControl(panButton.getButtonText());
			controlParamChanged.emit(panButton.getButtonText());
			trackMixerPtr->setThreshold((uint8_t)PAN_MAX_THRESHOLD);
		}
	}

	void TrackMixerControl::updateRangeText()
	{
		juce::String rangeLabel;
		rangeLabel = rangeLabel.formatted("%d-%d", rangeLow, rangeHigh);
	}

	void TrackMixerControl::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (TrackMixer::GetTrackMixerInstance()->KeyFocusedItem)
		{
		case TrackMixer::TrackMixerViewItemID::VOLUME_PARAM:
			volumeButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case TrackMixer::TrackMixerViewItemID::PAN_PARAM:
			panButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case TrackMixer::TrackMixerViewItemID::LEFT_NUDGE:
			leftNudgeButton.FPKeyHandler(isFocuse, param, 0);
			break;
		case TrackMixer::TrackMixerViewItemID::RIGHT_NUDGE:
			rightNudgeButton.FPKeyHandler(isFocuse, param, 0);
			break;
		}
		repaint();
	}
}
