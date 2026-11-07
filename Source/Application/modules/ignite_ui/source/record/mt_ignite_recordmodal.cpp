namespace ui
{

	////////////////////////////////////////////////
	//   Class: Ignite Record Modale
	////////////////////////////////////////////////
	IgniteRecordModale::IgniteRecordModale()
	{
		addAndMakeVisible(CreateNew);
		CreateNew.addListener(this);

		addAndMakeVisible(Cancel);
		Cancel.addListener(this);

		addAndMakeVisible(OverRide);
		OverRide.addListener(this);

		addAndMakeVisible(Audition);
		Audition.addListener(this);

		addAndMakeVisible(close);
		close.addListener(this);

		Title.makeVisible(this);
		Title.setJustificationType(Justification::centred);
	}

	IgniteRecordModale::~IgniteRecordModale()
	{

	}

	void IgniteRecordModale::paint(juce::Graphics& g)
	{
		Image Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-3.png"));
		g.drawImage(Draw, ui::Rectangle<float>{ 0, 0,604, 360}, RectanglePlacement::stretchToFit);

		g.setColour(Theme::Instance().getColour(customBlue15));
		g.fillRect(ui::Rectangle{ 0, 100, getWidth(),  1 });
		g.fillRect(ui::Rectangle{ 0, 261, getWidth(),  1 });
		

	}

	void IgniteRecordModale::resized()
	{
		Title.setBounds(0, 30, getWidth(), 50);
		Cancel.setBounds(30, 291, 544, 44);
		close.setBounds(550, 25, 25, 25);
	}

	void IgniteRecordModale::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &Cancel || buttonThatWasClicked == &close)
		{
			onSelectionChanged(0);
			Cancel.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &CreateNew)
		{
			onSelectionChanged(1);
			CreateNew.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &OverRide)
		{
			onSelectionChanged(2);
			OverRide.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &Audition)
		{
			onSelectionChanged(3);
			Audition.setToggleState(false, dontSendNotification);
		}
		CtrlPtr->isEditing = false;
	}

	void IgniteRecordModale::show(bool newrecord, bool overriderecord)
	{
		KeyFocusedItem = 0;
		Cancel.isFocused = false;
		OverRide.isFocused = false;
		CreateNew.isFocused = false;
		Audition.isFocused = false;
		OverRide.setVisible(false);
		Audition.setVisible(true);
		std::function<void(int)> CallbackOnExit;
		if (newrecord && overriderecord)
		{
			CreateNew.setBounds(30, 110, 544, 45);
			OverRide.setBounds(30, 160, 544, 45);
			Audition.setBounds(30, 210, 544, 45);
			OverRide.setVisible(true);
			overRide = true;
		}
		else if (!newrecord)
		{
			CreateNew.setBounds(30, 130, 544, 50);
			Audition.setBounds(30, 185, 544, 50);
			overRide = false;
		}
		if(CtrlPtr==nullptr)
			CtrlPtr = IgniteControlOptions::GetAppOptInstance();
		CtrlPtr->isEditing = true;
		close.toFront(true);
		ui::CommonUtils::showCustomDialog(" ", this, [this, CallbackOnExit](int r)
			{
				if (auto dw = getCurrentlyModalComponent())
					dw->exitModalState(0);
				CommonUtils::close();
				CtrlPtr->isEditing = false;
			}, juce::Rectangle <int>(0, 0, (int)604, (int)getHeight()));
		
	}

	bool IgniteRecordModale::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{

		PannelSendKey(false, param, KeyValue); // clear last Focus
		if (KeyFocusedItem == 0)
		{
			KeyFocusedItem = 1;
		}
		else
		{
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				KeyFocusedItem = (KeyFocusedItem + 1 >= RecordModalViewItemID::FOCUS_MAX ? (RecordModalViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				KeyFocusedItem = (KeyFocusedItem - 1 <= RecordModalViewItemID::NO_FOCUS ? (RecordModalViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				buttonClicked(&Cancel);
				break;
			case FrontPannelParam::paramKey_RSELECT:
				PannelSendKey(false, param, KeyValue);
				return true;
				break;
			}
		}
		PannelSendKey(true, param, KeyValue); // clear last Focus
		return true;
	}

	void IgniteRecordModale::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
		{
			switch (RecordModalView[KeyFocusedItem])
			{
			case CREATE_NEW:
				this->postCommandMessage(1);
				CreateNew.isFocused = isFocuse;
				break;
			case OVERRIDE:
				this->postCommandMessage(2);
				OverRide.isFocused = isFocuse;
				break;
			case AUDITION:
				this->postCommandMessage(3);
				Audition.isFocused = isFocuse;
				break;
			case CANCEL:
				this->postCommandMessage(4);
				Cancel.isFocused = isFocuse;
				break;
			default:
				break;
			}
			
		}
		else
		{
			switch (RecordModalView[KeyFocusedItem])
			{
			case CREATE_NEW:
				CreateNew.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case OVERRIDE:
				OverRide.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case AUDITION:
				Audition.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case CANCEL:
				Cancel.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			default:
				break;
			}
			repaint();
		}
	}

	void IgniteRecordModale::handleCommandMessage(int id)
	{
		if(id == 1)
			buttonClicked(&CreateNew);
		else if (id == 2)
			buttonClicked(&OverRide);
		else if (id == 3)
			buttonClicked(&Audition);
		else if (id == 4)
			buttonClicked(&Cancel);
	}
}
