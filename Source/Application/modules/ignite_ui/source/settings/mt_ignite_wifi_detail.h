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

#pragma once
namespace ui
{
	class IgniteConnectivity;
	class IgniteWifiDetail : public juce::Component,
		public CommonButton::Listener
	{
	public:
		IgniteWifiDetail(IgniteConnectivity* iPtr);
		~IgniteWifiDetail() override;
		void refreshData(std::string ssid);
		void getAssets();
		void setheaderText(String ssid) { wifiTitle.setText(ssid, dontSendNotification); }

	private:
		CommonLabel	wifiTitle{ "Wi-Fi Detail" };
		CommonLabel	infoHeader{ "Wi-Fi Information" };
		CommonLabel	macAddressLable{ "MAC Address" };
		CommonLabel	macAddress{ "-" };
		CommonLabel	ipv4AddressLable{ "IPV4 Address" };
		CommonLabel	ipv4Address{ "-" };
		CommonLabel	ipAddress{ "IP Address" };
		CommonLabel	subnetMaskLable{ "Subnet Mask" };
		CommonLabel	subnetMask{ "-" };
		CommonLabel	gatewayLable{ "Gateway" };
		CommonLabel	gateway{ "-" };
		CommonLabel	otherInfo{ "Other Information" };
		CommonLabel	ipConfigLable{ "IP Configuration" };
		CommonLabel	ipConfig{ "Automatic" };
		CommonLabel	proxyConfigLable{ "Proxy Configuration" };
		CommonLabel	proxyConfig{ "Off" };
		CommonLabel	dnsConfigLable{ "DNS Configuration" };
		CommonLabel	dnsConfig{ "Automatic" };

		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		Image modelContainer;
		void resized() override;
		void paint(juce::Graphics& g) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteWifiDetail)
	};
}
