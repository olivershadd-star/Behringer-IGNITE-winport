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

#if( JUCE_LINUX || __linux__ )
#include <iostream>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iwlib.h>
#include <algorithm>
#include <cstring>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#endif

#define WIFI_CRED_FILE "/data/ignite/wifi_credentials.txt"
#define WIFI_CONF_FILE "/data/ignite/wpa_supplicant.conf"

namespace ui
{
	WifiManager::WifiManager()
	{
	}

	WifiManager::~WifiManager()
	{
	}

	std::string WifiManager::executeCommand(const std::string& command)
	{
		std::string result;
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		std::array<char, 128> buffer;
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
		if (!pipe) {
			throw std::runtime_error("popen() failed!");
		}
		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			result += buffer.data();
		}
#endif
		return result;
	}

	bool WifiManager::fileExists(const std::string& filename) {
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		struct stat buffer;
		return (stat(filename.c_str(), &buffer) == 0);
#endif
		return false;
	}

	std::map<std::string, std::string> WifiManager::loadWifiCredentials() {
		std::ifstream file(WIFI_CRED_FILE);
		std::map<std::string, std::string> wifiMap;
		std::string line;

		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string ssid, password;
			if (std::getline(ss, ssid, ':') && std::getline(ss, password)) {
				wifiMap[ssid] = password;
			}
		}
		return wifiMap;
	}

	void WifiManager::saveWifiCredential(const std::string& ssid, const std::string& password) {
		if (!fileExists(WIFI_CRED_FILE))
		{
			std::ofstream file(WIFI_CRED_FILE);
			file.close();
		}

		std::ofstream file(WIFI_CRED_FILE, std::ios::app);
		file << ssid << ":" << password << std::endl;
	}

	std::vector<mt::Ignite::WiFiNetwork> WifiManager::scanWiFiNetworks()
	{
		std::string currentSSID;
		bool currentSecurity = false;
		int currentSignalStrength = 0;
		std::vector<mt::Ignite::WiFiNetwork> wifiNetworks;
		StringArray scanResults;
		String command = "iwlist wlan0 scan";
		ChildProcess childProcess;

		DBG("-------------------------scanning-----------------------");
		if (childProcess.start(command))
		{
			scanResults.addLines(childProcess.readAllProcessOutput());
			childProcess.waitForProcessToFinish(10000);
		}

		for (auto line : scanResults)
		{
			if (line.contains("ESSID:"))
			{
				currentSSID = line.fromFirstOccurrenceOf("ESSID:", false, true).trim().unquoted().toStdString();
			}
			else if (line.contains("Encryption key:"))
			{
				currentSecurity = !line.contains("off");
			}
			else if (line.contains("Signal level="))
			{
				String signalStr = line.fromFirstOccurrenceOf("Signal level=", false, true).upToFirstOccurrenceOf(" dBm", false, true).trim();
				currentSignalStrength = signalStr.getIntValue();
			}

			if (!currentSSID.empty() && currentSignalStrength != 0)
			{
				mt::Ignite::WiFiNetwork network;
				network.ssid = currentSSID;
				network.security = currentSecurity;
				network.signalStrength = currentSignalStrength;

				wifiNetworks.push_back(network);

				currentSSID.clear();
				currentSecurity = false;
				currentSignalStrength = 0;
			}
		}

		for (const auto& network : wifiNetworks)
		{
			(void)network;
			DBG("SSID: " + network.ssid);
			DBG("Signal Strength: " + String(network.signalStrength));
			DBG("Security: " + (String)(network.security ? "Secured" : "Open"));
			DBG("-------------------------");
		}

		return wifiNetworks;
	}

	bool WifiManager::enableWiFi()
	{
		String command = "ip link set wlan0 up";
		String result = executeCommand(command.toStdString());

		command = "rfkill unblock wifi";
		result = executeCommand(command.toStdString());

		return result.isEmpty();
	}

	bool WifiManager::disableWiFi()
	{
		String command = "ip link set wlan0 down";
		String result = executeCommand(command.toStdString());
		return result.isEmpty();
	}

	void WifiManager::displayWiFiNetworks(const StringArray& networks)
	{
		for (const auto& network : networks)
		{
			std::cout << "Network: " << network << std::endl;
		}
	}

	bool WifiManager::connectToWiFi(const String& ssid, const String& password, int priority)
	{
		std::cout << "Network: connecting to wifi SSID: " << ssid << std::endl;
		std::map<std::string, std::string> wifiMap = loadWifiCredentials();
		std::string ssid1 = ssid.toStdString();
		String result = "";

		result.clear();
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		auto it = wifiMap.find(ssid1);
		if (it != wifiMap.end())
		{
			std::string password1 = wifiMap[ssid1];
			addSSID(ssid, String(password1), priority);
			std::cout << "SSID found in file. Using stored password." << std::endl;
		}
		else
		{
			addSSID(ssid, password, priority);
			saveWifiCredential(ssid.toStdString(), password.toStdString());
		}

		String command = "killall -9 wpa_supplicant dhclient";
		result = executeCommand(command.toStdString());
		sleep(1);
		command = "wpa_supplicant -B -i wlan0 -c /data/ignite/wpa_supplicant.conf";
		result = executeCommand(command.toStdString());
		sleep(2);
		command = "dhclient wlan0";
		result = executeCommand(command.toStdString());
#endif
		DBG("Return = " + String((int)result.isEmpty()));
		std::cout << "Return = " << (int)result.isEmpty() << std::endl;
		return isWifiConnected(ssid.toStdString());
	}

	bool WifiManager::disconnectWiFi()
	{
		String command = "killall -9 wpa_supplicant dhclient";
		String result = executeCommand(command.toStdString());
		return result.isEmpty();
	}

	void WifiManager::addSSID(const String& ssid, const String& password, int priority)
	{
		if (!fileExists(WIFI_CONF_FILE))
		{
			std::ofstream file(WIFI_CONF_FILE);
			file.close();
		}
		File configFile(WIFI_CONF_FILE);
		if (configFile.existsAsFile())
		{
			String networkConfig =
				"\nnetwork={\n"
				"    ssid=\"" + ssid + "\"\n"
				"    psk=\"" + password + "\"\n"
				"    key_mgmt=WPA-PSK  " + "\n"
				"}\n\n";

			configFile.replaceWithText(networkConfig);
		}
		else
		{
			std::cerr << "Error: wpa_supplicant.conf file not found or not accessible." << std::endl;
		}
	}

	bool WifiManager::isWifiConnected(std::string ssid)
	{
		ssid = ssid + "\n";
		std::string result;
		result.clear();

		result = executeCommand("iwgetid -r");

		if (result.compare(ssid) == 0)
		{
			std::cout << ssid << " Wi-Fi is connected.\n";
			return true;
		}
		else
		{
			std::cout << ssid << " Wi-Fi is not connected.\n";
			return false;
		}
	}

	void WifiManager::removeSSID(const juce::String& ssid)
	{
		juce::File configFile(WIFI_CONF_FILE);

		if (!configFile.existsAsFile())
		{
			std::cerr << "Error: wpa_supplicant.conf file not found or not accessible." << std::endl;
			return;
		}

		juce::String content = configFile.loadFileAsString();
		juce::String networkBlockStart = "network={\n    ssid=\"" + ssid + "\"";
		int startIndex = content.indexOf(networkBlockStart);

		if (startIndex != -1)
		{
			int endIndex = content.indexOf(startIndex, "}\n");
			if (endIndex != -1)
			{
				content = content.substring(0, startIndex) + content.substring(endIndex + 2);
				configFile.replaceWithText(content);
				std::cout << "SSID \"" << ssid << "\" removed successfully." << std::endl;
			}
		}
		else
		{
			std::cout << "SSID \"" << ssid << "\" not found." << std::endl;
		}
	}


	bool WifiManager::isPasswordPresent(const juce::String& ssid)
	{
		juce::File configFile(WIFI_CONF_FILE);

		if (!configFile.existsAsFile())
		{
			std::cerr << "Error: wpa_supplicant.conf file not found or not accessible." << std::endl;
			return false;
		}

		juce::String content = configFile.loadFileAsString();
		juce::String networkBlockStart = "network={";
		int startIndex = 0;

		while ((startIndex = content.indexOf(startIndex, networkBlockStart)) != -1)
		{
			int endIndex = content.indexOf(startIndex, "}");
			if (endIndex == -1)
			{
				std::cerr << "Error: Invalid format in wpa_supplicant.conf" << std::endl;
				return false;
			}

			juce::String networkBlock = content.substring(startIndex, endIndex + 1);
			if (networkBlock.contains("ssid=\"" + ssid + "\""))
			{
				int pskIndex = networkBlock.indexOf("psk=");
				if (pskIndex != -1)
				{
					juce::String pskLine = networkBlock.substring(pskIndex);
					juce::String pskValue = pskLine.fromFirstOccurrenceOf("psk=", false, false).trim();
					pskValue = pskValue.fromFirstOccurrenceOf("\"", false, false);
					pskValue = pskValue.upToFirstOccurrenceOf("\"", false, false);

					if (!pskValue.isEmpty())
					{
						return true;
					}
				}
			}
			startIndex = endIndex + 1;
		}
		return false;
	}

	std::string WifiManager::getMacAddress(const char* ifname)
	{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		int sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock < 0)
			return "";

		struct ifreq ifr;
		strcpy(ifr.ifr_name, ifname);
		if (ioctl(sock, SIOCGIFHWADDR, &ifr) == -1)
		{
			close(sock);
			return "";
		}

		unsigned char* mac = (unsigned char*)ifr.ifr_hwaddr.sa_data;
		close(sock);

		char macAddr[18];
		snprintf(macAddr, sizeof(macAddr), "%02x:%02x:%02x:%02x:%02x:%02x",
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		return std::string(macAddr);
#endif
		return "-";
	}

	void WifiManager::getIPandSubnet(const char* ifname, std::string& ipAddress, std::string& subnetMask)
	{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		struct ifaddrs* ifaddr, * ifa;
		if (getifaddrs(&ifaddr) == -1)
			return;

		for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
		{
			if (ifa->ifa_addr == nullptr || strcmp(ifa->ifa_name, ifname) != 0)
				continue;
			if (ifa->ifa_addr->sa_family == AF_INET)
			{
				char ip[INET_ADDRSTRLEN];
				char netmask[INET_ADDRSTRLEN];

				inet_ntop(AF_INET, &(((struct sockaddr_in*)ifa->ifa_addr)->sin_addr), ip, INET_ADDRSTRLEN);
				inet_ntop(AF_INET, &(((struct sockaddr_in*)ifa->ifa_netmask)->sin_addr), netmask, INET_ADDRSTRLEN);

				ipAddress = std::string(ip);
				subnetMask = std::string(netmask);
				break;
			}
		}
		freeifaddrs(ifaddr);
#endif
	}

	std::string WifiManager::getGateway()
	{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )

		std::ifstream routeFile("/proc/net/route");
		std::string line, iface, gateway;
		while (std::getline(routeFile, line))
		{
			std::istringstream iss(line);
			std::string destination;
			iss >> iface >> destination >> gateway;

			if (destination == "00000000")
			{
				unsigned long gw;
				sscanf(gateway.c_str(), "%lx", &gw);
				struct in_addr gateway_addr;
				gateway_addr.s_addr = gw;
				return std::string(inet_ntoa(gateway_addr));
			}
		}
#endif
		return "";
	}

	void WifiManager::getWifiProperties(mt::Ignite::wifiProperties* wifiData)
	{
		const char* ifname = "wlan0";

		wifiData->macAddress = getMacAddress(ifname);
		std::cout << "MAC Address: " << wifiData->macAddress << std::endl;

		getIPandSubnet(ifname, wifiData->ipAddress, wifiData->subnetMask);
		std::cout << "IP Address: " << wifiData->ipAddress << std::endl;
		std::cout << "Subnet Mask: " << wifiData->subnetMask << std::endl;

		wifiData->gateway = getGateway();
		std::cout << "Gateway: " << wifiData->gateway << std::endl;
	}
}