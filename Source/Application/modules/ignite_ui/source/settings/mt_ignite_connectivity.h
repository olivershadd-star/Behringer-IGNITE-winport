/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY.
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

#pragma once

namespace ui
{
	class IgniteControlOptions;
	class IgniteWiFiRow;
	class WifiManager;
	class IgniteWifiDetail;

	enum WIFI_STATE
	{
		WIFI_POWER_OFF,
		WIFI_POWER_ON,
		WIFI_SCANNING,
		WIFI_CONNECTING,
		WIFI_DISCONNECTED,
	};

	class WifiScan : public juce::Thread
	{
	public:
		WifiScan() : juce::Thread("WifiScanThread")
		{
		}
		WifiScan(std::function<void(std::vector<mt::Ignite::WiFiNetwork>)> onScanComplete)
			: juce::Thread("WifiScanThread"), onScanComplete(onScanComplete)
		{
		}
		void run() override;

	private:
		std::function<void(std::vector<mt::Ignite::WiFiNetwork>)> onScanComplete;
	};

	class WifiConnect : public juce::Thread
	{
	public:
		WifiConnect() : juce::Thread("WifiConnectThread")
		{
		}
		WifiConnect(std::function<void(bool)> onConnectComplete)
			: juce::Thread("WifiConnectThread"), onConnectComplete(onConnectComplete)
		{
		}
		void run() override;
		void setSsidAndPassword(String ssid, String password) { wifi_ssid = ssid; wifi_password = password; }

	private:
		std::function<void(bool)> onConnectComplete;
		WIFI_STATE currentState = WIFI_POWER_OFF;
		String wifi_ssid;
		String wifi_password;
	};

	class IgniteConnectivity :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener,
		public juce::Label::Listener,
		private Timer
	{
	public:
		IgniteConnectivity();
		~IgniteConnectivity() override;
		void enableControlButton(IgniteControlOptions::eKey key, bool state);
		void updateDataFromEngine();
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void refreshWiFiUI(bool force_refresh);
		void connectWifi(String password);
		void setSelected(int index) { selected = index; }
		bool isSecureNetwork();
		void updateLedStatus(bool state);
		bool connDataUpdated = false;

		WIFI_STATE getWifiConnectionState() { return currentState; };

		static IgniteConnectivity* GetAppConnectivityInstance()
		{
			static IgniteConnectivity* GetAppConnectivityObj;
			if (NULL == GetAppConnectivityObj)
			{
				GetAppConnectivityObj = new IgniteConnectivity();
			}

			return GetAppConnectivityObj;
		}

	private:
#define CONN_MENU_VIEW 15
#define CONN_OPT_VIEW 2
#define CONN_ROW_ITEMS 3

		enum ConnMenuViewItemID
		{
			NO_FOCUS = 0,
			WIFI_ENABLE,
			WIFI_SCAN,
			FOCUS_MAX = WIFI_SCAN,
		};

		enum CONNCONFIG_FOCUS
		{
			CONN_CONFIG_DETAIL,
			CONN_CONFIG_OPTION,
		};

		enum ConnOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OP_FOCUS_MAX = OPT_UNDO
		};

		uint8_t optionHandlerFocus = CONN_CONFIG_DETAIL;
		uint8_t ConnoptionsView[CONN_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO };
		uint8_t ConnMenuView[CONN_MENU_VIEW] = { NO_FOCUS, WIFI_ENABLE, WIFI_SCAN };
		int keyFocusedItem = ConnMenuViewItemID::NO_FOCUS;
		int optFocusedItem = OPT_UNDO;

		CommonImageButton wifiMode{ "WiFi: Off","toggle-wifi-off.png","toggle-wifi-on.png","toggle-wifi-off-hover.png" };
		CommonImageButton networkLable{ "Networks","networks.png","networks.png","networks.png" };
		CommonImageButton topBorder{ "","row-top-border.png","row-top-border.png","row-top-border.png" };
		CommonImageButton scanBtn{ "Scan Networks","btn-wifi-search-default.png","btn-wifi-search-default.png","btn-wifi-search-default-hover.png" };

		IgniteControlOptions* connOptCtl = nullptr;
		CommonPopUp* popupPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;
		WifiManager* wifiComp = nullptr;


		std::vector<mt::Ignite::WiFiNetwork> wifiNetworkList;
		//StringArray wifiNetworkList;
		String wifi_password;
		CommonKey passwordComp{ "" };
		String lastConnectedSsid = "";
		juce::OwnedArray<IgniteWiFiRow> list;
		juce::Viewport view;
		juce::Component container;
		int curretWifiRow = 0;
		int count = 0;
		int selected = 0;
		int wifiRowHighLightIndex = 0;

		std::unique_ptr<WifiScan> scanThread;
		std::unique_ptr<WifiConnect> connectThread;
		WIFI_STATE currentState = WIFI_POWER_OFF;

	SIGNALS:
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void showPopup(int index);
		void enableWifi();
		void disableWifi();
		void addWifiNetwork(mt::Ignite::WiFiNetwork network);
		void removeWifiNetwork(int index);
		void removeWifiNetworks();
		//bool connectWifi(String ssid, String password);
		void disConnectWifi(String ssid);
		void populate(int index);
		void handleCommandMessage(int id);
		void labelTextChanged(Label* labelThatHasChanged);
		void setTimeLimittoGif(int countLimit);
		void timerCallback();
		void clearConnectedState();
		bool ssidExistsInNetworkList(const std::string& ssid);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteConnectivity)
	};

	class IgniteWiFiRow :
		public juce::Component,
		public juce::Button::Listener,
		public juce::Label::Listener
	{
	public:
		IgniteWiFiRow(int SerialNumber, mt::Ignite::wifiData& Data, IgniteConnectivity* _pOwnerptr);
		~IgniteWiFiRow();
		std::function<void(IgniteWiFiRow*)> onMouseDown;
		void highlight(bool state);
		int getSerialNumber();
		void refreshWifiRowUI(bool state);
		void setFocus(bool hasFocus, bool hasActiveFoces);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		bool isEditing() { return name.isEditing; }
		void getAssets();
		void setSignalStrength(mt::Ignite::wifiSigStrength sigStrength);
		void handleCommandMessage(int id);

	private:
		IgniteConnectivity* _pConn = nullptr;
		mt::Ignite::wifiData& wifidata;
		CommonSerialNumber srNo{ "1" };
		String serialNumber = "1";
		//String conntectedString = "Connected";
		IgniteWifiDetail* wifiInfoPtr = nullptr;
		juce::Viewport dialogViewPort;

		CommonKey passwordComp{ "", true };
		CommonKey name{ "" };
		CommonImageButton connectedBtn{ "","icon-connected-white.png","icon-connected-white.png","icon-connected-white.png" };
		CommonImageButton connectStateBtn{ "","connectString.png","connectString.png","connectString.png" };
		CommonImageButton secBtn{ "","icon-lock-white.png","icon-lock-white.png","icon-lock-white.png" };
		CommonImageButton strenthStrongBtn{ "","icon-wifi-strong.png","icon-wifi-strong.png","icon-wifi-strong.png" };
		CommonImageButton strenthWeekBtn{ "","icon-wifi-weak.png","icon-wifi-weak.png","icon-wifi-weak.png" };
		CommonImageButton strenthWeekerBtn{ "","icon-wifi-weaker.png","icon-wifi-weaker.png","icon-wifi-weaker.png" };
		CommonImageButton connectBtn{ "","btn-wifi-connect-default.png","btn-wifi-connect-default.png","btn-wifi-connect-default-hover.png" };
		CommonImageButton disconnectBtn{ "","btn-wifi-disconnect-default.png","btn-wifi-disconnect-default.png","btn-wifi-disconnect-default-hover.png" };
		CommonImageButton detailBtn{ "","btn-wifi-detail-default.png","btn-wifi-detail-default.png","btn-wifi-detail-hover.png" };

		int serialNo;
		int nameWidth;
		bool isHighlighted{ false };
		bool isMouseOver{ false };
		Image imageWifiRow1, imageWifiRow2, imageWifiRowHover, imageConnectDefault, imageConnectDefaultHover,
			imageDisConnectDefault, imageDisConnectDefaultHover, imageDetailDefult, imageDetailDefultHover,
			imageDetailDefault, imageDetailDefaultHover;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		void mouseUp(const MouseEvent& event) override;
		void mouseDown(const MouseEvent& event) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void labelTextChanged(Label* labelThatHasChanged)
		{}
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteWiFiRow)
	};
};
