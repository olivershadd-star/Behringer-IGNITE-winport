/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY.
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
	class IgniteDeviceStatus :
		public juce::Component,
		private Timer,
		public juce::Button::Listener
	{
	public:
		IgniteDeviceStatus();
		~IgniteDeviceStatus() override;
		void refreshData();
		void updateSerialAndFimrwareData();

		void devStatusStartTimer(int milliseconds)
		{
			startTimer(milliseconds);
		}

		void devStatusStopTimer()
		{
			if (isTimerRunning())
				stopTimer();
		}

		static IgniteDeviceStatus* GetDevStatusInstance()
		{
			static IgniteDeviceStatus* GetDevStatusObj;
			if (NULL == GetDevStatusObj)
			{
				GetDevStatusObj = new IgniteDeviceStatus();
			}
			return GetDevStatusObj;
		}
		bool handleFirmwareUpgrade(SwUdateSource_t mode);
		FwStatus_t startFirmwareUpgrade(SwUdateSource_t mode, FwStatus_t status = FwStatus_t::INVALID_FW);
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);

	private:
#define DEVICE_STATUS_MENU_VIEW 3

		enum DeviceStatusMenuViewItemID
		{
			NO_FOCUS = 0,
			REFRESH_STATUS,
			FIRMWARE_UPGRADE,
			FOCUS_MAX = FIRMWARE_UPGRADE
		};

		uint8_t deviceStatusMenuView[DEVICE_STATUS_MENU_VIEW] = { NO_FOCUS, REFRESH_STATUS, FIRMWARE_UPGRADE };
		int keyFocusedItem = DeviceStatusMenuViewItemID::NO_FOCUS;

		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;
		juce::FlexBox ctlBox3;
		CommonPopUp* popupPtr = nullptr;
		FwStatus_t fw_pkg_status = FwStatus_t::INVALID_FW;
		//CommonLabel banner{ "Behringer \n Ignite" };

		IgniteConnectivity* igniteConnectivity = nullptr;

		CommonLabel serialNumberLable{ "Serial Number:" };
		CommonLabel firmwareVersionLable{ "Firmware Version:" };
		CommonLabel firmwareBuildDateLable{ "Firmware Build:" };

		CommonLabel serialNumber{ "" };
		CommonLabel firmwareVersion{ "" };
		CommonLabel firmwareBuildDate{ "" };

		CommonLabel ramStatus{ "Memory Status" };
		CommonLabel intStorageStatus{ "Internal Storage Status" };
		CommonLabel usbStorageStatus{ "USB Storage Status" };

		CommonLabel totalDiskSpaceLable{ "Total Space: " };
		CommonLabel systemUsedDiskSpaceLable{ "Used Space: " };
		CommonLabel availableUserDiskSpaceLable{ "Available Space: " };
		CommonLabel totalDiskSpace{ "" };
		CommonLabel systemUsedDiskSpace{ "" };
		CommonLabel availableUserDiskSpace{ "" };

		CommonLabel totalUsbDiskSpaceLable{ "Total Space: " };
		CommonLabel availableUsbDiskSpaceLable{ "Available Space: " };
		CommonLabel totalUsbDiskSpace{ "" };
		CommonLabel availableUsbDiskSpace{ "" };

		CommonLabel totalRamLable{ "Total RAM: " };
		CommonLabel freeRamLable{ "Available RAM: " };
		CommonLabel usedRamLable{ "Used RAM: " };
		CommonLabel totalRam{ "" };
		CommonLabel freeRam{ "" };
		CommonLabel usedRam{ "" };

		CommonImageButton banner{ "Banner","logo_BE_Ignite.png","logo_BE_Ignite.png","logo_BE_Ignite.png" };
		CommonImageButton refreshBtn{ "Refresh","btn-refresh-no-267x44-default.png","btn-refresh-no-267x44-default-hover.png","btn-refresh-no-267x44-default-hover.png" };
		CommonImageButton fwUpdateBtn{ "Firmware Update","btn-firmware-up-267x44-default.png","btn-firmware-up-267x44-active-hover.png","btn-firmware-up-267x44-active-hover.png" };

		void timerCallback() override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);

		void showFirmwareUpdateSourceOptions();
		void startUsbHandler();
		void startWifiHandler();
		void handleUSBDriveSelection();
		void handleCommandMessage(int id) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteDeviceStatus)
	};
};
