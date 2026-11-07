/*
 * Copyright (c) - 2024 - MUSIC Tribe, MY.
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

using namespace Ignite;

namespace ui
{
	juce::Array<mt::Ignite::wifiData> gWifiNetworks;
	////////////////////////////////////////////////
	//   Class: Ignite Connectivity
	////////////////////////////////////////////////
	IgniteConnectivity::IgniteConnectivity()
	{
		addAndMakeVisible(wifiMode);
		wifiMode.addListener(this);
		wifiMode.setToggleable(true);
		wifiMode.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		wifiMode.sethoverImages("toggle-wifi-off-hover.png", "toggle-wifi-on-hover.png", "toggle-wifi-on-hover.png");

		addAndMakeVisible(scanBtn);
		scanBtn.addListener(this);
		scanBtn.setToggleable(true);
		scanBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		scanBtn.setDisableImage("btn-wifi-search-disabled.png");
		scanBtn.setEnabled(false);
		scanBtn.setAlpha(0.5f);

		addAndMakeVisible(networkLable);
		networkLable.setToggleable(false);
		networkLable.setEnabled(false);
		networkLable.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		networkLable.setAlpha(0.5f);

		addAndMakeVisible(topBorder);
		topBorder.setToggleable(false);
		topBorder.setEnabled(false);
		topBorder.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		connOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(connOptCtl);
		connOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		connOptCtl->addOptCtlListener(this);
		popupPtr = CommonPopUp::getCommonPopupInstance();
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();

		addAndMakeVisible(view);
		addAndMakeVisible(container);
		view.setViewedComponent(&container, true);
		view.setBounds(10, 169, 1004, 310);
		view.setScrollBarsShown(true, false, true, true);
		view.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::all);
		container.setVisible(false);
		view.setVisible(false);

		passwordComp.makeVisibleAndAddListner(this);
		passwordComp.setText("", juce::dontSendNotification);
		passwordComp.setLableFont(font_10);

		wifiComp = WifiManager::getWifiInterface();

		scanThread = std::make_unique<WifiScan>(
			[this](std::vector<mt::Ignite::WiFiNetwork> result) {
				std::sort(result.begin(), result.end(), [](const mt::Ignite::WiFiNetwork& a, const mt::Ignite::WiFiNetwork& b) {
					return a.signalStrength > b.signalStrength;
					});

				for (auto& iter : result)
				{
					if (!ssidExistsInNetworkList(iter.ssid))
					{
						mt::Ignite::WiFiNetwork network;
						network.ssid = iter.ssid;
						network.security = iter.security;
						network.signalStrength = iter.signalStrength;
						wifiNetworkList.push_back(network);
					}
				}
				this->postCommandMessage(1);
			});

		connectThread = std::make_unique<WifiConnect>(
			[this](bool result) {
				clearConnectedState();
				gWifiNetworks.getReference(selected).wifiConnected = result;
				this->postCommandMessage(3);
			});

		passwordComp.onValueChanged = [this](String value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			wifi_password = value;
			this->postCommandMessage(2);
		};
	}

	IgniteConnectivity::~IgniteConnectivity()
	{
	}

	mt::Ignite::wifiSigStrength getSignalStrength(int sigStrength)
	{
		if (sigStrength >= -50)
			return mt::Ignite::wifiSigStrength::STRONG_SIGNAL;
		else if (sigStrength >= -70)
			return mt::Ignite::wifiSigStrength::WEEK_SIGNAL;
		else
			return mt::Ignite::wifiSigStrength::WEEKER_SIGNAL;
	}

	bool IgniteConnectivity::ssidExistsInNetworkList(const std::string& ssid)
	{
		for (const auto& network : wifiNetworkList)
			if (network.ssid == ssid)
				return true;
		return false;
	}

	bool IgniteConnectivity::isSecureNetwork()
	{
		return gWifiNetworks.getReference(selected).isSecure;
	}

	void IgniteConnectivity::handleCommandMessage(int id)
	{
		if (id == 1)
		{
			auto lastSsiAvailable = false;
			removeWifiNetworks();
			for (auto& iter : wifiNetworkList)
			{
				addWifiNetwork(iter);
				if (lastConnectedSsid != " ")
					if (iter.ssid == lastConnectedSsid)
						lastSsiAvailable = true;
			}
			if (currentState == WIFI_SCANNING)
			{
				_pInfoWindow->setTextandShow("Wi-Fi Scan Completed");
			}
			if (list.size() > 0)
				updateLedStatus(true);
			else
				updateLedStatus(false);
			if (lastSsiAvailable)
			{
				std::cout << "last connected ssid found " << lastConnectedSsid << std::endl;
				connectWifi(lastConnectedSsid);
			}
		}
		else if (id == 2)
		{
			if (currentState == WIFI_CONNECTING)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->showPreloader("Connect to Wi-Fi ", "Connecting to Wi-Fi " + String(gWifiNetworks[selected].name));
					setTimeLimittoGif(25000);
				}
			}
			connectThread->setSsidAndPassword(gWifiNetworks[selected].name, wifi_password);
			connectThread->startThread();
		}
		else if (id == 3)
		{
			list[selected]->refreshWifiRowUI(gWifiNetworks.getReference(selected).wifiConnected);
			timerCallback();
		}
		else if (id == 4)
		{
			wifiComp->disconnectWiFi();
			clearConnectedState();
			for (auto i = 0; i < list.size(); i++)
				list[i]->refreshWifiRowUI(gWifiNetworks.getReference(selected).wifiConnected);
		}
	}

	void IgniteConnectivity::clearConnectedState()
	{
		for (auto i = 0; i < list.size(); i++)
		{
			gWifiNetworks.getReference(i).wifiConnected = false;
		}
	}

	void IgniteConnectivity::enableControlButton(IgniteControlOptions::eKey key, bool state)
	{
	}

	void IgniteConnectivity::labelTextChanged(Label* labelThatHasChanged)
	{
	}

	void IgniteConnectivity::refreshWiFiUI(bool force_refresh)
	{
		int index = 0;

		_PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramSongNameList);
		for (auto& i : list)
		{
			i->setBounds(0, (60 * index++), 990, 60);
			i->onMouseDown = [this](IgniteWiFiRow* Row)
			{
				showPopup((Row->getSerialNumber()));
			};
		}
		container.setSize(990, (index + 1) * 60);
		updateLedStatus(true);
	}

	void IgniteConnectivity::updateLedStatus(bool state)
	{
		if ((list.size() > 0) && state && (currentState != WIFI_POWER_OFF))
		{
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::paramKey_TRACKROTARY7), fpLEDPattern::EN_LED_PATT_Blink_Slow);
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::paramKey_TRACKROTARY8), fpLEDPattern::EN_LED_PATT_Blink_Slow);
		}
		else
		{
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::paramKey_TRACKROTARY7), fpLEDPattern::EN_LED_PATT_OFF);
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((int)FrontPannelParam::paramKey_TRACKROTARY8), fpLEDPattern::EN_LED_PATT_OFF);
		}
	}

	void IgniteConnectivity::populate(int index)
	{
		mt::Ignite::wifiData wifidata;
		IgniteWiFiRow* row;

		curretWifiRow++;
		wifidata = gWifiNetworks[list.size()];
		row = new IgniteWiFiRow(list.size(), wifidata, this);
		list.add(row);
		container.addAndMakeVisible(row);
		refreshWiFiUI(true);
		row->highlight(true);
	}

	void IgniteConnectivity::addWifiNetwork(mt::Ignite::WiFiNetwork network)
	{
		gWifiNetworks.add({ list.size() ,network.ssid, 0, getSignalStrength(network.signalStrength), network.security, });
		populate(0);
	}

	void IgniteConnectivity::removeWifiNetwork(int index)
	{
		container.removeChildComponent(index);
		list.remove(index);
		gWifiNetworks.removeAndReturn(index);
	}

	void IgniteConnectivity::removeWifiNetworks()
	{
		int row_index = list.size() - 1;
		while (list.size())
		{
			container.removeChildComponent(row_index);
			list.remove(row_index);
			gWifiNetworks.removeAndReturn(row_index);
			row_index--;
		}
	}

	void IgniteConnectivity::enableWifi()
	{
		currentState = WIFI_POWER_ON;
		wifiComp->enableWiFi();
		scanBtn.setEnabled(true);
		container.setVisible(true);
		view.setVisible(true);
		scanBtn.setAlpha(1.0f);
		networkLable.setAlpha(1.0f);
		scanThread->startThread();
	}

	void IgniteConnectivity::disableWifi()
	{
		currentState = WIFI_POWER_OFF;
		wifiComp->disableWiFi();
		scanBtn.setEnabled(false);
		container.setVisible(false);
		view.setVisible(false);
		scanBtn.setAlpha(0.5f);
		networkLable.setAlpha(0.5f);
		removeWifiNetworks();
		container.setSize(0, 0);
		updateLedStatus(false);
	}

	void IgniteConnectivity::connectWifi(String password)
	{
		wifi_password = password;
		currentState = WIFI_CONNECTING;
		this->postCommandMessage(2);
	}

	void IgniteConnectivity::disConnectWifi(String ssid)
	{
		currentState = WIFI_DISCONNECTED;
		std::cout << "disConnectWifi !!!!!!!!!!!!!!!!" << std::endl;
		this->postCommandMessage(4);
	}

	void IgniteConnectivity::showPopup(int index)
	{
		currentState = WIFI_CONNECTING;
		selected = index;
		passwordComp.launchKeyboard();
	}

	void IgniteConnectivity::setTimeLimittoGif(int countLimit)
	{
		startTimer(countLimit);
	}

	void IgniteConnectivity::timerCallback()
	{
		stopTimer();
		popupPtr->close();

		if (popupPtr->isDialogOpen.get() != true)
		{
			if (auto dw = getCurrentlyModalComponent())
				dw->exitModalState(0);

			popupPtr->close();
			popupPtr->setPopUpPropories("Connect to Wi-Fi", 604, 290);
			popupPtr->setbtnsize(267, 44);

			if (gWifiNetworks[selected].wifiConnected)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::paramWifiLastConnSsid, gWifiNetworks[selected].name.toStdString());
				popupPtr->setInfoText("Connected to Wi-Fi: " + String(gWifiNetworks[selected].name));
			}
			else
				popupPtr->setInfoText("Failed to connect Wi-Fi: " + String(gWifiNetworks[selected].name));

			popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_WITHOK;
			popupPtr->isCloseButtonVisible(false);
			popupPtr->show();
			popupPtr->onSelectionChanged = [this](int r)
			{
				if (r == 1)
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
			};
		}
	}
	void IgniteConnectivity::paint(juce::Graphics& g)
	{
		Image DrawImage;

		g.setColour(ui::Theme::Instance().getColour(neutralBlack));
		g.fillAll();

		MenuMode::GetMenuModeInstance()->setHeader("Wi-Fi Setting");
		MenuMode::GetMenuModeInstance()->setJustification(Justification::centred);
	}

	void IgniteConnectivity::updateDataFromEngine()
	{
		std::vector<IgniteParamList> wifiParamsList;
		IgniteParamList params;

		wifiParamsList.clear();
		params.param = (paramId_t)SettingsGeneralCnfgParam::paramWifiState;
		wifiParamsList.push_back(params);
		params.param = (paramId_t)SettingsGeneralCnfgParam::paramWifiLastConnSsid;
		wifiParamsList.push_back(params);
		wifiParamsList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, wifiParamsList);

		wifiMode.setToggleState(wifiParamsList[0].MsgValue.get< bool >(), dontSendNotification);
		lastConnectedSsid = wifiParamsList[1].MsgValue.get< std::string >();

		if (wifiMode.getToggleState())
			enableWifi();
	}

	void IgniteConnectivity::resized()
	{
		wifiMode.setBounds(10, 63, 1004, 50);
		networkLable.setBounds(10, 134, 80, 24);
		scanBtn.setBounds(834, 121, 180, 44);
		topBorder.setBounds(10, 168, 1004, 1);
	}

	void IgniteConnectivity::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &wifiMode)
		{
			wifiMode.getToggleState() ? enableWifi() : disableWifi();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::paramWifiState, wifiMode.getToggleState());
		}
		else if (buttonThatWasClicked == &scanBtn)
		{
			currentState = WIFI_SCANNING;
			_pInfoWindow->setTextandShow("Wi-Fi Scanning Started");
			scanThread->startThread();
		}

		enableControlButton(IgniteControlOptions::SAVE, true);
		connDataUpdated = true;
	}

	void IgniteConnectivity::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
	}

	bool IgniteConnectivity::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;

		if (!list.isEmpty() && ((FrontPannelParam)param == FrontPannelParam::paramRot_ROW || (FrontPannelParam)param == FrontPannelParam::paramKey_ROTARYROW
			|| (FrontPannelParam)param == FrontPannelParam::paramKey_TRACKROTARY7 || (FrontPannelParam)param == FrontPannelParam::paramKey_TRACKROTARY8))
		{
			for (auto& i : list)
				i->setFocus(false, false);

			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramRot_ROW:
				if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
				{
					wifiRowHighLightIndex = jmin<int>(jmax<int>((wifiRowHighLightIndex + 1), 0), (list.size() - 1));
					if ((wifiRowHighLightIndex) * 60 > (view.getViewArea().getHeight() - 60))
						view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() + 60);
				}
				else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
				{
					wifiRowHighLightIndex = jmin<int>(jmax<int>((wifiRowHighLightIndex - 1), 0), (list.size() - 1));

					if ((wifiRowHighLightIndex - 1) * 60 <= (view.getViewArea().getHeight()))
						view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() - 60);
				}
				break;
			case FrontPannelParam::paramKey_ROTARYROW:
				selected = wifiRowHighLightIndex;
				break;
			case FrontPannelParam::paramKey_TRACKROTARY7:
				list[wifiRowHighLightIndex]->handleCommandMessage(1);
				break;
			case FrontPannelParam::paramKey_TRACKROTARY8:
				list[wifiRowHighLightIndex]->handleCommandMessage(2);
				break;
			}
			list[wifiRowHighLightIndex]->setFocus(true, false);
			repaint();
		}
		if (optionHandlerFocus == CONN_CONFIG_DETAIL)
		{
			if (keyFocusedItem == ConnMenuViewItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				keyFocusedItem = ConnMenuViewItemID::WIFI_ENABLE;

				if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
				{
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
					return true;
				}

			}
			else
			{
				pannelSendKey(false, param, KeyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= ConnMenuViewItemID::FOCUS_MAX ? (ConnMenuViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= ConnMenuViewItemID::NO_FOCUS ? (ConnMenuViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					setVisible(false);
					updateLedStatus(false);
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
					break;
				}
			}
		}
		else
		{
			pannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				optFocusedItem = (optFocusedItem + 1 >= ConnOptionsViewItemID::OP_FOCUS_MAX ? (ConnOptionsViewItemID::OP_FOCUS_MAX) : optFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				optFocusedItem = (optFocusedItem - 1 <= ConnOptionsViewItemID::OP_NO_FOCUS ? (ConnOptionsViewItemID::OP_NO_FOCUS + 1) : optFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
				break;
			}

		}
		if (setfocus)
		{
			pannelSendKey(true, param, KeyValue);
		}

		return true;
	}

	void IgniteConnectivity::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		bool state = false;

		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (optionHandlerFocus == CONN_CONFIG_DETAIL)
		{
			switch (ConnMenuView[keyFocusedItem])
			{
			case WIFI_ENABLE:
				wifiMode.FPKeyHandler(isFocuse, param, 0);
				break;
			case WIFI_SCAN:
				scanBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			default:
				break;
			}
			repaint();
		}
		else
		{
			switch (ConnoptionsView[optFocusedItem])
			{
			case OPT_UNDO:
				state = connOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			default:
				break;
			}

			if (state == false)
			{
				optFocusedItem++;
				if (optFocusedItem == OP_FOCUS_MAX)
					optFocusedItem = OPT_UNDO;
				pannelSendKey(isFocuse, param, KeyValue);
			}
		}
	}

	////////////////////////////////////////////////
	//   Class: Ignite WiFi row
	////////////////////////////////////////////////
	IgniteWiFiRow::IgniteWiFiRow(int SerialNumber, mt::Ignite::wifiData& Data, IgniteConnectivity* WifiPtr) : wifidata(Data)
	{
		_pConn = WifiPtr;
		wifiInfoPtr = new IgniteWifiDetail(_pConn);

		name.makeVisible(this);
		name.setEditable(false, false, false);
		name.setDisplayTitle(false);
		name.setText(String(wifidata.name), juce::dontSendNotification);
		name.setLableFont(font_14);
		name.disableTitleEdit(false);
		name.setJustificationType(juce::Justification::centredLeft);

		srNo.makeVisible(this);
		srNo.setText(String(SerialNumber), juce::dontSendNotification);

		passwordComp.makeVisibleAndAddListner(this);
		passwordComp.setEditable(true, true, false);
		passwordComp.setDisplayTitle(false);
		passwordComp.setLableFont(font_10);

		addMouseListener(this, true);

		float fontSize = font_14;
		juce::Font sizeFont(fontSize);
		nameWidth = sizeFont.getStringWidth(wifidata.name) + 8;

		addAndMakeVisible(connectStateBtn);
		connectStateBtn.setToggleable(false);
		connectStateBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		connectStateBtn.setEnabled(false);

		addAndMakeVisible(connectedBtn);
		connectedBtn.setToggleable(false);
		connectedBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		connectedBtn.setEnabled(false);

		if (wifidata.isSecure)
		{
			addAndMakeVisible(secBtn);
			secBtn.setToggleable(false);
			secBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
			secBtn.setEnabled(false);
		}

		addAndMakeVisible(strenthStrongBtn);
		strenthStrongBtn.setToggleable(false);
		strenthStrongBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		strenthStrongBtn.setEnabled(false);

		addAndMakeVisible(strenthWeekBtn);
		strenthWeekBtn.setToggleable(false);
		strenthWeekBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		strenthWeekBtn.setEnabled(false);

		addAndMakeVisible(strenthWeekerBtn);
		strenthWeekerBtn.setToggleable(false);
		strenthWeekerBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		strenthWeekerBtn.setEnabled(false);

		addAndMakeVisible(connectBtn);
		connectBtn.setToggleable(false);
		connectBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		connectBtn.setEnabled(true);
		connectBtn.addListener(this);

		addAndMakeVisible(disconnectBtn);
		disconnectBtn.setToggleable(false);
		disconnectBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		disconnectBtn.setEnabled(false);
		disconnectBtn.addListener(this);

		detailBtn.makeVisibleAndAddListner(this);
		detailBtn.setToggleable(true);
		detailBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		detailBtn.setEnabled(true);

		connectedBtn.setVisible(false);
		connectStateBtn.setVisible(false);
		connectBtn.setVisible(false);
		disconnectBtn.setVisible(false);
		detailBtn.setVisible(true);

		setSignalStrength(wifidata.signalStrength);
		getAssets();

		passwordComp.onValueChanged = [this](String value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			passwordComp.setText("", dontSendNotification);
			_pConn->connectWifi(value);
		};

		passwordComp.onMouseClick = [this]()
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pConn->setSelected(getSerialNumber());
			if (!connectedBtn.isVisible())
			{
				auto isPasswordAvailable = WifiManager::getWifiInterface()->isPasswordPresent(name.getText()) || !_pConn->isSecureNetwork();
				passwordComp.keyboardCtl(!isPasswordAvailable);
				if (isPasswordAvailable)
					_pConn->connectWifi("");
			}
			else
			{
				_pConn->disConnectWifi(name.getText());
				passwordComp.keyboardCtl(false);
			}
		};
	}

	IgniteWiFiRow::~IgniteWiFiRow()
	{}

	void IgniteWiFiRow::setSignalStrength(mt::Ignite::wifiSigStrength sigStrength)
	{
		strenthStrongBtn.setVisible(false);
		strenthWeekBtn.setVisible(false);
		strenthWeekerBtn.setVisible(false);

		switch (sigStrength)
		{
		case mt::Ignite::wifiSigStrength::STRONG_SIGNAL:
			strenthStrongBtn.setVisible(true);
			break;
		case mt::Ignite::wifiSigStrength::WEEK_SIGNAL:
			strenthWeekBtn.setVisible(true);
			break;
		case mt::Ignite::wifiSigStrength::WEEKER_SIGNAL:
			strenthWeekerBtn.setVisible(true);
			break;
		default:
			strenthStrongBtn.setVisible(true);
			break;
		}
	}

	void IgniteWiFiRow::highlight(bool State)
	{
		isHighlighted = State;
		repaint();
	}

	int IgniteWiFiRow::getSerialNumber()
	{
		return srNo.getText().getIntValue();
	}

	void IgniteWiFiRow::mouseDown(const MouseEvent& event)
	{
	}

	void IgniteWiFiRow::mouseUp(const MouseEvent& event)
	{
	}

	void IgniteWiFiRow::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &detailBtn)
		{
			auto ssid = name.getText();
			wifiInfoPtr->refreshData(ssid.toStdString());
			wifiInfoPtr->setheaderText(ssid);
			dialogViewPort.setBounds(0, 0, 604, 472);
			dialogViewPort.setViewedComponent(wifiInfoPtr, false);
			CommonUtils::showCustomDialog(ssid, &dialogViewPort, [this](int r)
				{
				}, ui::Rectangle<int>{0, 0, 604, 560}, true);
		}
	}

	void IgniteWiFiRow::refreshWifiRowUI(bool state)
	{
		connectedBtn.setVisible(state);
		connectStateBtn.setVisible(state);
	}

	void IgniteWiFiRow::getAssets()
	{
		imageWifiRow1 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("list-rowcolor-1.png"));
		imageWifiRow2 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("list-rowcolor-2.png"));
		imageWifiRowHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("list-rowcolor-hover.png"));
		imageConnectDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-wifi-connect-default.png"));
		imageConnectDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-wifi-connect-default-hover.png"));
		imageDisConnectDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-wifi-disconnect-default.png"));
		imageDisConnectDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-wifi-disconnect-default-hover.png"));
		imageDetailDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-wifi-detail-default.png"));
		imageDetailDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-wifi-detail-hover.png"));

	}

	void IgniteWiFiRow::paint(juce::Graphics& g)
	{
		auto serial_number = getSerialNumber();
		g.drawImage(isMouseOver ? imageWifiRowHover : ((serial_number % 2 == 0) ? imageWifiRow1 : imageWifiRow2), getLocalBounds().toFloat(), RectanglePlacement::centred);
		(!connectedBtn.isVisible()) ? g.drawImage(imageConnectDefault, ui::Rectangle<float>{734, 18, 116, 32}) : g.drawImage(imageDisConnectDefault, ui::Rectangle<float>{734, 18, 116, 32});
		g.drawImage(imageDetailDefaultHover, ui::Rectangle<float>{870, 18, 116, 32});
	}

	void IgniteWiFiRow::resized()
	{
		connectedBtn.setBounds(15, 18, 24, 24);
		name.setBounds(39, 18, 512, 24);
		passwordComp.setBounds(734, 18, 116, 32);
		detailBtn.setBounds(870, 18, 116, 32);
		connectStateBtn.setBounds((39 + nameWidth), 21, 74, 19);
		if (wifidata.isSecure)
			secBtn.setBounds(646, 18, 24, 24);
		strenthStrongBtn.setBounds(690, 18, 24, 24);
		strenthWeekBtn.setBounds(690, 18, 24, 24);
		strenthWeekerBtn.setBounds(690, 18, 24, 24);
	}

	void IgniteWiFiRow::setFocus(bool hasFocus, bool activeHasFocus)
	{
		if (hasFocus)
			isMouseOver = true;
		else
			isMouseOver = false;
		repaint();
	};

	bool IgniteWiFiRow::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		return true;
	}

	void IgniteWiFiRow::mouseMove(const MouseEvent& event)
	{
		isMouseOver = true;
		repaint();
	}

	void IgniteWiFiRow::mouseExit(const MouseEvent& event)
	{
		isMouseOver = false;
		repaint();
	}

	void IgniteWiFiRow::handleCommandMessage(int id)
	{
		if (id == 1)
			passwordComp.onMouseClick();
		else if (id == 2)
			buttonClicked(&detailBtn);
	}

	void WifiScan::run()
	{
		std::vector<mt::Ignite::WiFiNetwork> result;
		DBG("Scan Thread has started.");

		result = WifiManager::getWifiInterface()->scanWiFiNetworks();
		if (onScanComplete != nullptr)
		{
			onScanComplete(result);
		}
		DBG("Scan Thread has exited.");
	}

	void WifiConnect::run()
	{
		bool result = false;
		DBG("Connect Thread has started.");
		std::cout << "Network: connecting to wifi SSID: " << wifi_ssid << " password: " << wifi_password << std::endl;
		result = WifiManager::getWifiInterface()->connectToWiFi(wifi_ssid, wifi_password);
		std::cout << "Result: " << result << std::endl;
		if (onConnectComplete != nullptr)
		{
			onConnectComplete(result);
		}
		DBG("Connect Thread has exited.");
	}
};
