namespace ui
{
	CommonTrackButton::CommonTrackButton()
	{

		addAndMakeVisible(title);
		title.setJustificationType(juce::Justification::centred);

		title.addMouseListener(this, true);
		bottomlable1.addMouseListener(this, true);
		bottomlable2.addMouseListener(this, true);
		toplable.addMouseListener(this, true);
		addAndMakeVisible(bottomlable1);
		bottomlable1.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(bottomlable2);
		bottomlable2.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(toplable);
		toplable.setJustificationType(juce::Justification::centred);
		colourid = juce::Colours::dodgerblue;
		buttonOnColour = juce::Colours::dodgerblue;
		setColour(colourid);
		buttonOffColour = juce::Colours::limegreen;
		title.setFont(24.0f);
		title.setTextColour(Colour(0xFF424357));
		title.setInterceptsMouseClicks(true, false);
		bottomlable2.setInterceptsMouseClicks(true, false);
		toplable.setInterceptsMouseClicks(true, false);
		bottomlable1.setInterceptsMouseClicks(true, false);

		bottomlable2.setFont(12.0f);
		bottomlable1.setFont(12.0f);
		bottomlable2.setTextColour(Colour(0xFF424357));
		bottomlable1.setTextColour(Colour(0xFF424357));
		bottomlable1.setJustificationType(Justification::right);
		bottomlable2.setJustificationType(Justification::left);
		bottomlable1.setText("No Instrument", dontSendNotification);
		bottomlable2.setText("No Pattern", dontSendNotification);

		repaint();
	}

	void CommonTrackButton::resized()
	{
		auto bounds = getLocalBounds();
		auto totalWidth = bounds.getWidth();
		auto totalHeight = bounds.getHeight();

		auto trackLabelHeight = totalHeight * 0.2;

		Font test((float)(trackLabelHeight * 0.85f));
		auto titleWidth = test.getStringWidth(title.getText());
		title.setBounds(0, (int)(totalHeight * 0.25), (int)totalWidth, (int)(totalHeight * 0.4));
		titleWidth = test.getStringWidth(bottomlable2.getText());
		bottomlable2.setBounds(0, (int)(totalHeight * 0.7), (int)(totalWidth * 0.5), (int)(totalHeight * 0.25));
		toplable.setBounds((int)(totalWidth * 0.7), 0, (int)(totalWidth * 0.3), (int)(totalHeight * 0.2));
		titleWidth = test.getStringWidth(bottomlable1.getText());
		bottomlable1.setBounds((int)(totalWidth * 0.5), (int)(totalHeight * 0.7), (int)(totalWidth * 0.5), (int)(totalHeight * 0.25));
	}

	void CommonTrackButton::paint(Graphics& g)
	{
		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(focusState ? "track-container-inactive-hover.png" : "track-container-Inactive.png"));
		ActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(focusState ? "track-container-active-hover.png" : "track-container-active.png"));

		if (State == STATE::OFF && isEditing)
		{
			g.drawImage(juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("track-container-inactive-hover.png")), getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
		else if(State == STATE::OFF)
			g.drawImage(defaultImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		else
		{
			g.drawImage(ActiveImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}
		Image default_image;

		if (isEditing && State == STATE::ON)
		{
			default_image = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(focusState ? "track-container-edit-hover.png" : "track-container-edit.png"));
			g.drawImage(default_image, getLocalBounds().toFloat(), RectanglePlacement::centred);
		}

		if (soloState && State == STATE::ON)
		{
			default_image = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("track-icon-solo-active.png"));
		}
		else
		{
			default_image = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("track-icon-solo-inactive.png"));
		}

		ui::Rectangle<float> b = { getLocalBounds().removeFromTop(40).removeFromRight(50).toFloat() };
		g.drawImage(default_image, ui::Rectangle{ b.getX(),b.getY() + 15,(float)36,(float)16 }, RectanglePlacement::centred);
	}

	//Setting Button Off Colour
	void CommonTrackButton::setColour(Colour newcolourId)
	{
		colourid = newcolourId;
		buttonOffColour = newcolourId;
		repaint();
	}

	void CommonTrackButton::addListener(Listener* l) { Listeners.add(l); }
	void CommonTrackButton::removeListener(Listener* l) { Listeners.remove(l); }

	void CommonTrackButton::mouseDoubleClick(const MouseEvent& event)
	{
		Component::BailOutChecker checker(this);
		handleMouseDoubleClick();
		Listeners.callChecked(checker, [this](Listener& l) {
			l.onMouseDoubleClicked(this);
			});
	}

	void CommonTrackButton::handleMouseDoubleClick()
	{
		/*State = STATE::ON;
		NextState = 0;*/
	}

	//setting Button On Colour
	void CommonTrackButton::setButtonOnColour(Colour newcolour)
	{
		colourid = newcolour;
		buttonOnColour = newcolour;
		repaint();
	}

	void CommonTrackButton::mouseDown(const juce::MouseEvent& event)
	{
		Component::BailOutChecker checker(this);
		if (checker.shouldBailOut())
			return;

		auto currentTime = juce::Time::getCurrentTime();
		if ((currentTime - lastClickTime).inMilliseconds() <= doubleClickTimeoutMs)
		{
			stopTimer();
			isSingleClickPending = false;
			mouseDoubleClick(event);
		}
		else
		{
			lastClickTime = currentTime;
			isSingleClickPending = true;
			startTimer(singleClickTimeoutMs);
		}
	}

	void CommonTrackButton::handleMouseSingleClick()
	{
		if (NextState == STATE::ON)
		{
			State = STATE::ON;
			NextState = 0;
			bottomlable2.setTextColour(Colour(0xFFFFFFFF));
			bottomlable1.setTextColour(Colour(0xFFFFFFFF));
			title.setTextColour(Colour(0xFFFFFFFF));
		}
		else if (NextState == STATE::OFF)
		{
			State = STATE::OFF;
			NextState = 1;
			bottomlable2.setTextColour(Colour(0xFF424357));
			bottomlable1.setTextColour(Colour(0xFF424357));
			title.setTextColour(Colour(0xFF424357));

		}
		repaint();
	}

	void CommonTrackButton::setToggleState(bool state) {

		State = state;
		switch (state)
		{
		case STATE::ON:
			NextState = STATE::OFF;
			break;
		case STATE::OFF:
			NextState = STATE::ON;
			break;
		}
		repaint();
	}

	void CommonTrackButton::setTitle(String titleText)
	{
		title.setText(titleText, NotificationType::dontSendNotification);
		if (NextState == STATE::OFF)
		{
			bottomlable2.setTextColour(Colour(0xFFFFFFFF));
			bottomlable1.setTextColour(Colour(0xFFFFFFFF));
			title.setTextColour(Colour(0xFFFFFFFF));
		}
		else if (NextState == STATE::ON)
		{
			bottomlable2.setTextColour(Colour(0xFF424357));
			bottomlable1.setTextColour(Colour(0xFF424357));
			title.setTextColour(Colour(0xFF424357));
		}
		repaint();
	}

	void CommonTrackButton::setlabels(String pattern, String instrument, String mode)
	{
		bottomlable1.setText(pattern, NotificationType::dontSendNotification);
		bottomlable2.setText(instrument, NotificationType::dontSendNotification);
		toplable.setText(mode, NotificationType::dontSendNotification);
	}

	void CommonTrackButton::setSoloState(bool state)
	{
		soloState = state;
		repaint();
	}
	void CommonTrackButton::setTextFont(Contains sel, const Font& newFont)
	{
		switch (sel)
		{
		case Contains::Title:
			title.setTextFont(newFont);
			break;
		case Contains::LeftLabel:
			bottomlable1.setFont(newFont);
			break;
		case Contains::RightLabel:
			bottomlable2.setFont(newFont);
			break;
		case Contains::TopLable:
			toplable.setFont(newFont);
			break;
		case Contains::All:
			title.setFont(newFont);
			bottomlable1.setFont(newFont);
			bottomlable2.setFont(newFont);
			toplable.setFont(newFont);
			break;
		default:
			break;
		}
		resized();
	}

	void CommonTrackButton::setTextBackgroundColour(Contains sel, Colour colour)
	{
		switch (sel)
		{
		case Contains::Title:
			title.setColour(juce::Label::backgroundColourId, colour);
			break;
		case Contains::LeftLabel:
			bottomlable1.setColour(juce::Label::backgroundColourId, colour);
			break;
		case Contains::RightLabel:
			bottomlable2.setColour(juce::Label::backgroundColourId, colour);
			break;
		case Contains::TopLable:
			toplable.setColour(juce::Label::backgroundColourId, colour);
			break;
		case Contains::All:
			title.setColour(juce::Label::backgroundColourId, colour);
			bottomlable1.setColour(juce::Label::backgroundColourId, colour);
			bottomlable2.setColour(juce::Label::backgroundColourId, colour);
			toplable.setColour(juce::Label::backgroundColourId, colour);
			break;
		default:
			break;
		}
	}

	void CommonTrackButton::setTextOutlineColourId(Contains sel, Colour colour)
	{
		switch (sel)
		{
		case Contains::Title:
			title.setColour(juce::Label::outlineColourId, colour);
			break;
		case Contains::LeftLabel:
			bottomlable1.setColour(juce::Label::outlineColourId, colour);
			break;
		case Contains::RightLabel:
			bottomlable2.setColour(juce::Label::outlineColourId, colour);
			break;
		case Contains::TopLable:
			toplable.setColour(juce::Label::outlineColourId, colour);
			break;
		case Contains::All:
			title.setColour(juce::Label::outlineColourId, colour);
			bottomlable1.setColour(juce::Label::outlineColourId, colour);
			bottomlable2.setColour(juce::Label::outlineColourId, colour);
			toplable.setColour(juce::Label::outlineColourId, colour);
			break;
		default:
			break;
		}
	}

	void CommonTrackButton::setTextColour(Contains sel, Colour colour)
	{
		switch (sel)
		{
		case Contains::Title:
			title.setTextColour(colour);
			break;
		case Contains::LeftLabel:
			bottomlable1.setTextColour(colour);
			break;
		case Contains::RightLabel:
			bottomlable2.setTextColour(colour);
			break;
		case Contains::TopLable:
			toplable.setTextColour(colour);
			break;
		case Contains::All:
			title.setTextColour(colour);
			bottomlable1.setTextColour(colour);
			bottomlable2.setTextColour(colour);
			toplable.setTextColour(colour);
			break;
		default:
			break;
		}
		//repaint();
	}

	void CommonTrackButton::mouseMove(const MouseEvent& event)
	{

	}

	void CommonTrackButton::mouseExit(const MouseEvent& event)
	{

	}

	void CommonTrackButton::setFocusState(bool state)
	{
		focusState = state;
		repaint();
	}

}
