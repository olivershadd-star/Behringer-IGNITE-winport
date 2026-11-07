/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
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

#include <string>

namespace ui
{
	class WifiManager
	{
	public:
		WifiManager();
		~WifiManager();
		bool enableWiFi();
		bool disableWiFi();
		std::vector<mt::Ignite::WiFiNetwork> scanWiFiNetworks();
		void displayWiFiNetworks(const juce::StringArray& networks);
		bool connectToWiFi(const juce::String& ssid, const juce::String& password, int priority = 5);
		bool disconnectWiFi();
		bool isPasswordPresent(const String& ssid);
		void getWifiProperties(mt::Ignite::wifiProperties* wifiData);
		bool isWifiConnected(std::string ssid);

		static WifiManager* getWifiInterface()
		{
			static WifiManager* _wifiInterface;
			if (NULL == _wifiInterface)
			{
				_wifiInterface = new WifiManager();
			}

			return _wifiInterface;
		}

	private:
		std::string executeCommand(const std::string& command);
		void addSSID(const juce::String& ssid, const juce::String& password, int priority = 5);
		void removeSSID(const String& ssid);
		std::map<std::string, std::string> loadWifiCredentials();
		void saveWifiCredential(const std::string& ssid, const std::string& password);
		bool fileExists(const std::string& filename);
		std::string getMacAddress(const char* ifname);
		void getIPandSubnet(const char* ifname, std::string& ipAddress, std::string& subnetMask);
		std::string getGateway();
	};
}
