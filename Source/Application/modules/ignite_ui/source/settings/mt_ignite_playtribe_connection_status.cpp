
using namespace Ignite;
using namespace std;

namespace ui
{
	PlaytribeConnectionStatus::PlaytribeConnectionStatus()
	{
		auto fontHeight = 18.0f;
		Font textFont(fontHeight);

		addAndMakeVisible(disconnectBtn);
		disconnectBtn.setToggleable(false);
		disconnectBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		disconnectBtn.setEnabled(true);
		disconnectBtn.addListener(this);

		headerLable.makeVisible(this);
		headerLable.setDisplayTitle(false);
		headerLable.setEditable(false, false, false);
		headerLable.setJustificationType(Justification::centred);
		headerLable.setText("Device is in restricted mode", juce::dontSendNotification);
		headerLable.setFont(juce::Font(22.0f, juce::Font::bold));

		infoLable.makeVisible(this);
		infoLable.setDisplayTitle(false);
		infoLable.setEditable(false, false, false);
		infoLable.setJustificationType(Justification::centred);
		infoLable.setText("Wi-Fi update mode activated, Some operations are disabled.\nUse the PC app to update firmware, load & save backup, or perform a factory reset.\nClick Disconnect to regain access of disabled operations.", juce::dontSendNotification);
		infoLable.setTextFont(textFont);

		popupPtr = CommonPopUp::getCommonPopupInstance();

		setSize(1024, 600);
	}

	PlaytribeConnectionStatus::~PlaytribeConnectionStatus()
	{

	}

	void PlaytribeConnectionStatus::paint(juce::Graphics& g)
	{
		g.setColour(juce::Colours::black.withAlpha(0.65f));
		g.fillAll();
	}

	void PlaytribeConnectionStatus::resized()
	{
		auto b = getLocalBounds();
		disconnectBtn.setBounds(834, 20, 180, 44);
		headerLable.setBounds(Rectangle(10, 125, 1014, 40));
		infoLable.setBounds(Rectangle(10, 185, 1014, 75));
	}

	void PlaytribeConnectionStatus::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &disconnectBtn)
		{
			stopPlaytribeHandler();
		}
	}

	void PlaytribeConnectionStatus::timerCallback()
	{
		stopTimer();

		popupPtr->close();
		popupPtr->timerCallback();

		if (!isConnected)
		{
			popupPtr->setPopUpPropories("Connection Status", 604, 290);
			popupPtr->isCloseButtonVisible(false);
			popupPtr->setInfoText("Connection timed out, Please check your network. \n Make sure the app is launched before retrying.");
			popupPtr->setbtnsize(544, 44);
			popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_RESET;
			popupPtr->requestforReturnValueCallback();
			popupPtr->isCloseButtonVisible(false);
			popupPtr->show();
			CommonUtils::SetBlockingPopup(true);

			popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 1)
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
				};

			popupPtr->onActionReturnvalue = [this](int r)
				{
					popupPtr->close();
					if (r == 1)
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);

						stopPlaytribeHandler();
					}
				};
		}
	}

	void PlaytribeConnectionStatus::waitingForConnectionPopup()
	{
		isConnected = false; 
		popupPtr->close();
		popupPtr->showPreloader("", "Waiting For Connection... Please ensure the app is launched");
		startTimer(15000);
	}

	void PlaytribeConnectionStatus::ConnectionEstablishedPopup()
	{
		popupPtr->close();
		popupPtr->timerCallback();

		stopTimer();
		disconnectBtn.setEnabled(true);
		disconnectBtn.setAlpha(1.0f);

		popupPtr->setPopUpPropories("Connection Status", 604, 290);
		popupPtr->setInfoText("Connection Successful");
		popupPtr->setbtnsize(544, 44);
		popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
		popupPtr->popupType = POPUP_RESET;
		popupPtr->requestforReturnValueCallback();
		popupPtr->isCloseButtonVisible(false);
		popupPtr->show();

		popupPtr->onSelectionChanged = [this](int r)
			{
				if (r == 1)
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
			};

		popupPtr->onActionReturnvalue = [this](int r)
			{
				popupPtr->close();
				if (r == 1)
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
			};
	}

	void PlaytribeConnectionStatus::setConnectionState(bool state)
	{
		isConnected = true;

		// TODO : add code related to blocking the front pannel when app connected to device.
	}

	bool PlaytribeConnectionStatus::getConnectionState()
	{
		return isConnected;
	}

	void PlaytribeConnectionStatus::stopPlaytribeHandler()
	{
		setConnectionState(false);
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_stopPlayTribeWifiHandler, true, false);

		// TODO : add code related to unblocking the front pannel when app disconnected to device.
	}
}