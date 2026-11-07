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

namespace ui
{
	IgniteWifiDetail::IgniteWifiDetail(IgniteConnectivity* iPtr)
	{
		wifiTitle.makeVisible(this);
		wifiTitle.setJustificationType(juce::Justification::centred);

		infoHeader.makeVisible(this);
		infoHeader.setJustificationType(juce::Justification::centredLeft);

		macAddressLable.makeVisible(this);
		macAddressLable.setJustificationType(juce::Justification::centredLeft);

		macAddress.makeVisible(this);
		macAddress.setJustificationType(juce::Justification::centredRight);

		ipv4AddressLable.makeVisible(this);
		ipv4AddressLable.setJustificationType(juce::Justification::centredLeft);

		ipv4Address.makeVisible(this);
		ipv4Address.setJustificationType(juce::Justification::centredRight);

		ipAddress.makeVisible(this);
		ipAddress.setJustificationType(juce::Justification::centredLeft);

		subnetMaskLable.makeVisible(this);
		subnetMaskLable.setJustificationType(juce::Justification::centredLeft);

		subnetMask.makeVisible(this);
		subnetMask.setJustificationType(juce::Justification::centredRight);

		gatewayLable.makeVisible(this);
		gatewayLable.setJustificationType(juce::Justification::centredLeft);

		gateway.makeVisible(this);
		gateway.setJustificationType(juce::Justification::centredRight);

		otherInfo.makeVisible(this);
		otherInfo.setJustificationType(juce::Justification::centredLeft);

		ipConfigLable.makeVisible(this);
		ipConfigLable.setJustificationType(juce::Justification::centredLeft);

		ipConfig.makeVisible(this);
		ipConfig.setJustificationType(juce::Justification::centredRight);

		proxyConfigLable.makeVisible(this);
		proxyConfigLable.setJustificationType(juce::Justification::centredLeft);

		proxyConfig.makeVisible(this);
		proxyConfig.setJustificationType(juce::Justification::centredRight);

		dnsConfigLable.makeVisible(this);
		dnsConfigLable.setJustificationType(juce::Justification::centredLeft);

		dnsConfig.makeVisible(this);
		dnsConfig.setJustificationType(juce::Justification::centredRight);

		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		closeBtn.setBounds(553, 30, 20, 20);
		closeBtn.toFront(true);

		getAssets();
		setSize(604, 474);
	}

	IgniteWifiDetail::~IgniteWifiDetail()
	{
	}

	void IgniteWifiDetail::getAssets()
	{
		modelContainer = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-5.png"));
	}

	void IgniteWifiDetail::paint(juce::Graphics& g)
	{
		g.drawImage(modelContainer, juce::Rectangle <float>{ (float)0, (float)0, 604, 560 }, RectanglePlacement::centred);
	}

	void IgniteWifiDetail::resized()
	{
		wifiTitle.setBounds(182, 26, 239, 34);
		infoHeader.setBounds(30, 112, 544, 26);
		macAddressLable.setBounds(30, 148, 272, 22);
		ipv4AddressLable.setBounds(30, 196, 113, 26);
		ipAddress.setBounds(30, 232, 196, 22);
		subnetMaskLable.setBounds(30, 262, 272, 22);
		gatewayLable.setBounds(30, 292, 272, 22);
		otherInfo.setBounds(30, 340, 200, 26);
		ipConfigLable.setBounds(30, 376, 200, 22);
		proxyConfigLable.setBounds(30, 406, 200, 22);
		dnsConfigLable.setBounds(30, 436, 200, 22);

		macAddress.setBounds(300, 148, 274, 22);
		ipv4Address.setBounds(300, 232, 274, 22);
		subnetMask.setBounds(300, 262, 274, 22);
		gateway.setBounds(300, 292, 274, 22);
		ipConfig.setBounds(300, 376, 274, 22);
		proxyConfig.setBounds(300, 406, 274, 22);
		dnsConfig.setBounds(300, 436, 274, 22);
	}

	void IgniteWifiDetail::refreshData(std::string ssid)
	{
		auto wifiMgr = WifiManager::getWifiInterface();
		mt::Ignite::wifiProperties wifiData =  {"-", "-", "-", "-"};
		WifiManager::getWifiInterface()->getWifiProperties(&wifiData);
		macAddress.setText(String(wifiData.macAddress), dontSendNotification);

		if (wifiMgr->isWifiConnected(ssid))
		{
			ipv4Address.setText(wifiData.ipAddress, dontSendNotification);
			subnetMask.setText(wifiData.subnetMask, dontSendNotification);
			gateway.setText(wifiData.gateway, dontSendNotification);
		}
	}

	void IgniteWifiDetail::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &closeBtn)
		{
			if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
				dw->exitModalState(0);
			CommonUtils::SetUtilsVisiblity(false);
		}
	}
}
