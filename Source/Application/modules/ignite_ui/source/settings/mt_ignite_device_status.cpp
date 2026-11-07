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

using namespace Ignite;
using namespace std;
using namespace std::filesystem;

#include <fstream>
#include <filesystem>

namespace ui
{

	////////////////////////////////////////////////
	//   Class: IgniteDeviceStatus
	////////////////////////////////////////////////
	IgniteDeviceStatus::IgniteDeviceStatus()
	{
		auto fontHeight = 16.0f;
		Font textFont(fontHeight);

		serialNumberLable.makeVisible(this);
		serialNumberLable.setDisplayTitle(false);
		serialNumberLable.setEditable(false, false, false);
		serialNumberLable.setJustificationType(Justification::centredLeft);
		serialNumberLable.setTextFont(textFont);
		serialNumberLable.setTextColour(juce::Colour(0xFFD18900));

		firmwareVersionLable.makeVisible(this);
		firmwareVersionLable.setDisplayTitle(false);
		firmwareVersionLable.setEditable(false, false, false);
		firmwareVersionLable.setJustificationType(Justification::centredLeft);
		firmwareVersionLable.setTextFont(textFont);
		firmwareVersionLable.setTextColour(juce::Colour(0xFFD18900));

		firmwareBuildDateLable.makeVisible(this);
		firmwareBuildDateLable.setDisplayTitle(false);
		firmwareBuildDateLable.setEditable(false, false, false);
		firmwareBuildDateLable.setJustificationType(Justification::centredLeft);
		firmwareBuildDateLable.setTextFont(textFont);
		firmwareBuildDateLable.setTextColour(juce::Colour(0xFFD18900));

		serialNumber.makeVisible(this);
		serialNumber.setDisplayTitle(false);
		serialNumber.setEditable(false, false, false);
		serialNumber.setJustificationType(Justification::centredRight);
		serialNumber.setTextFont(textFont);
		serialNumber.setTextColour(juce::Colour(0xFFD18900));

		firmwareVersion.makeVisible(this);
		firmwareVersion.setDisplayTitle(false);
		firmwareVersion.setEditable(false, false, false);
		firmwareVersion.setJustificationType(Justification::centredRight);
		firmwareVersion.setTextFont(textFont);
		firmwareVersion.setTextColour(juce::Colour(0xFFD18900));

		firmwareBuildDate.makeVisible(this);
		firmwareBuildDate.setDisplayTitle(false);
		firmwareBuildDate.setEditable(false, false, false);
		firmwareBuildDate.setJustificationType(Justification::centredRight);
		firmwareBuildDate.setTextFont(textFont);
		firmwareBuildDate.setTextColour(juce::Colour(0xFFD18900));

		ramStatus.makeVisible(this);
		ramStatus.setDisplayTitle(false);
		ramStatus.setEditable(false, false, false);
		ramStatus.setJustificationType(Justification::centred);
		ramStatus.setTextFont(textFont);
		ramStatus.setTextColour(juce::Colour(0xFFFFB608));

		intStorageStatus.makeVisible(this);
		intStorageStatus.setDisplayTitle(false);
		intStorageStatus.setEditable(false, false, false);
		intStorageStatus.setJustificationType(Justification::centred);
		intStorageStatus.setTextFont(textFont);
		intStorageStatus.setTextColour(juce::Colour(0xFFFFB608));

		usbStorageStatus.makeVisible(this);
		usbStorageStatus.setDisplayTitle(false);
		usbStorageStatus.setEditable(false, false, false);
		usbStorageStatus.setJustificationType(Justification::centred);
		usbStorageStatus.setTextFont(textFont);
		usbStorageStatus.setTextColour(juce::Colour(0xFFFFB608));

		totalRamLable.makeVisible(this);
		totalRamLable.setDisplayTitle(false);
		totalRamLable.setEditable(false, false, false);
		totalRamLable.setJustificationType(Justification::centredLeft);
		totalRamLable.setTextFont(textFont);
		totalRamLable.setFont(juce::Font(18.0f, juce::Font::bold));

		freeRamLable.makeVisible(this);
		freeRamLable.setDisplayTitle(false);
		freeRamLable.setEditable(false, false, false);
		freeRamLable.setJustificationType(Justification::centredLeft);
		freeRamLable.setTextFont(textFont);

		usedRamLable.makeVisible(this);
		usedRamLable.setDisplayTitle(false);
		usedRamLable.setEditable(false, false, false);
		usedRamLable.setJustificationType(Justification::centredLeft);
		usedRamLable.setTextFont(textFont);

		totalDiskSpaceLable.makeVisible(this);
		totalDiskSpaceLable.setDisplayTitle(false);
		totalDiskSpaceLable.setEditable(false, false, false);
		totalDiskSpaceLable.setJustificationType(Justification::centredLeft);
		totalDiskSpaceLable.setTextFont(textFont);

		systemUsedDiskSpaceLable.makeVisible(this);
		systemUsedDiskSpaceLable.setDisplayTitle(false);
		systemUsedDiskSpaceLable.setEditable(false, false, false);
		systemUsedDiskSpaceLable.setJustificationType(Justification::centredLeft);
		systemUsedDiskSpaceLable.setTextFont(textFont);

		availableUserDiskSpaceLable.makeVisible(this);
		availableUserDiskSpaceLable.setDisplayTitle(false);
		availableUserDiskSpaceLable.setEditable(false, false, false);
		availableUserDiskSpaceLable.setJustificationType(Justification::centredLeft);
		availableUserDiskSpaceLable.setTextFont(textFont);

		totalUsbDiskSpaceLable.makeVisible(this);
		totalUsbDiskSpaceLable.setDisplayTitle(false);
		totalUsbDiskSpaceLable.setEditable(false, false, false);
		totalUsbDiskSpaceLable.setJustificationType(Justification::centredLeft);
		totalUsbDiskSpaceLable.setTextFont(textFont);

		availableUsbDiskSpaceLable.makeVisible(this);
		availableUsbDiskSpaceLable.setDisplayTitle(false);
		availableUsbDiskSpaceLable.setEditable(false, false, false);
		availableUsbDiskSpaceLable.setJustificationType(Justification::centredLeft);
		availableUsbDiskSpaceLable.setTextFont(textFont);

		totalRam.makeVisible(this);
		totalRam.setDisplayTitle(false);
		totalRam.setEditable(false, false, false);
		totalRam.setJustificationType(Justification::centredRight);
		totalRam.setTextFont(textFont);
		totalRam.setFont(juce::Font(18.0f, juce::Font::bold));

		freeRam.makeVisible(this);
		freeRam.setDisplayTitle(false);
		freeRam.setEditable(false, false, false);
		freeRam.setJustificationType(Justification::centredRight);
		freeRam.setTextFont(textFont);

		usedRam.makeVisible(this);
		usedRam.setDisplayTitle(false);
		usedRam.setEditable(false, false, false);
		usedRam.setJustificationType(Justification::centredRight);
		usedRam.setTextFont(textFont);

		totalDiskSpace.makeVisible(this);
		totalDiskSpace.setDisplayTitle(false);
		totalDiskSpace.setEditable(false, false, false);
		totalDiskSpace.setJustificationType(Justification::centredRight);
		totalDiskSpace.setTextFont(textFont);

		systemUsedDiskSpace.makeVisible(this);
		systemUsedDiskSpace.setDisplayTitle(false);
		systemUsedDiskSpace.setEditable(false, false, false);
		systemUsedDiskSpace.setJustificationType(Justification::centredRight);
		systemUsedDiskSpace.setTextFont(textFont);

		availableUserDiskSpace.makeVisible(this);
		availableUserDiskSpace.setDisplayTitle(false);
		availableUserDiskSpace.setEditable(false, false, false);
		availableUserDiskSpace.setJustificationType(Justification::centredRight);
		availableUserDiskSpace.setTextFont(textFont);

		totalUsbDiskSpace.makeVisible(this);
		totalUsbDiskSpace.setDisplayTitle(false);
		totalUsbDiskSpace.setEditable(false, false, false);
		totalUsbDiskSpace.setJustificationType(Justification::centredRight);
		totalUsbDiskSpace.setTextFont(textFont);

		availableUsbDiskSpace.makeVisible(this);
		availableUsbDiskSpace.setDisplayTitle(false);
		availableUsbDiskSpace.setEditable(false, false, false);
		availableUsbDiskSpace.setJustificationType(Justification::centredRight);
		availableUsbDiskSpace.setTextFont(textFont);

		addAndMakeVisible(banner);
		banner.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		banner.setToggleable(false);
		banner.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		addAndMakeVisible(refreshBtn);
		refreshBtn.addListener(this);
		refreshBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		refreshBtn.setToggleable(true);
		refreshBtn.setComponentID("refreshCfgComp");
		refreshBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		addAndMakeVisible(fwUpdateBtn);
		fwUpdateBtn.addListener(this);
		fwUpdateBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		fwUpdateBtn.setToggleable(true);
		fwUpdateBtn.setComponentID("fwUpdateBtnComp");
		refreshBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		popupPtr = CommonPopUp::getCommonPopupInstance();
	}

	IgniteDeviceStatus::~IgniteDeviceStatus()
	{
	}

	void IgniteDeviceStatus::updateSerialAndFimrwareData()
	{
		std::vector<IgniteParamList> paramList;
		IgniteParamList params;

		params.param = (paramId_t)FrontPannelParam::paramKey_getSerialNumber;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_getFirmwareVersion;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_getFirmwareBuildInfo;
		paramList.push_back(params);

		paramList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramList);

		serialNumber.setText(String(paramList[0].MsgValue.get<std::string>()), dontSendNotification);
		firmwareVersion.setText(String(paramList[1].MsgValue.get<std::string>()), dontSendNotification);
		firmwareBuildDate.setText(String(paramList[2].MsgValue.get<std::string>()), dontSendNotification);
	}

	void IgniteDeviceStatus::refreshData()
	{
		std::vector<IgniteParamList> paramList;
		IgniteParamList params;
		params.param = (paramId_t)FrontPannelParam::paramKey_EmmcGetTotalSize;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_EmmcGetFreeSize;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_UsbGetTotalSize;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_UsbGetFreeSize;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_RamGetTotalSize;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_RamGetFreeSize;
		paramList.push_back(params);

		paramList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramList);

		totalDiskSpace.setText(String(paramList[0].MsgValue.get<int>()) + " MB", dontSendNotification);
		availableUserDiskSpace.setText(String(paramList[1].MsgValue.get<int>()) + " MB", dontSendNotification);
		systemUsedDiskSpace.setText(String(paramList[0].MsgValue.get<int>() - paramList[1].MsgValue.get<int>()) + " MB", dontSendNotification);

		if (paramList[2].MsgValue.get<int>() > 0)
		{
			totalUsbDiskSpace.setText(String(paramList[2].MsgValue.get<int>()) + " MB", dontSendNotification);
			availableUsbDiskSpace.setText(String(paramList[3].MsgValue.get<int>()) + " MB", dontSendNotification);
		}
		else
		{
			totalUsbDiskSpace.setText("Not Connected", dontSendNotification);
			availableUsbDiskSpace.setText("Not Connected", dontSendNotification);
		}

		totalRam.setText(String(paramList[4].MsgValue.get<int>()) + " MB", dontSendNotification);
		freeRam.setText(String(paramList[5].MsgValue.get<int>()) + " MB", dontSendNotification);
		usedRam.setText(String(paramList[4].MsgValue.get<int>() - paramList[5].MsgValue.get<int>()) + " MB", dontSendNotification);

		if (!isTimerRunning())
			startTimer(1000);
	}

	void IgniteDeviceStatus::paint(juce::Graphics& g)
	{
		MenuMode::GetMenuModeInstance()->setHeader("Device Status");
		g.setColour(ui::Theme::Instance().getColour((neutralBlack)));
		g.fillAll();

		Image Draw;
		String Imagename;

		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-devicestatus-details.png"));
		g.drawImage(Draw, ui::Rectangle<float>{ 522, 70, 492, 50  });
		g.drawImage(Draw, ui::Rectangle<float>{ 522, 122, 492, 50  });
		g.drawImage(Draw, ui::Rectangle<float>{ 522, 174, 492, 50  });

		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-devicestatus-title.png"));
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 238, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 238, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 238, 328, 40  });

		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-devicestatus-content.png"));
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 282, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 326, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 370, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 282, 328, 40 });
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 326, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 370, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 282, 328, 40  });
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 326, 328, 40  });
	}

	void IgniteDeviceStatus::timerCallback()
	{
		refreshData();
	}

	void IgniteDeviceStatus::resized()
	{
		banner.setBounds(Rectangle(100, 102, 320, 90));

		serialNumberLable.setBounds(Rectangle(535, 70, 230, 50));
		firmwareVersionLable.setBounds(Rectangle(535, 122, 230, 50));
		firmwareBuildDateLable.setBounds(Rectangle(535, 174, 230, 50));

		serialNumber.setBounds(Rectangle(759, 70, 250, 50));
		firmwareVersion.setBounds(Rectangle(759, 122, 250, 50));
		firmwareBuildDate.setBounds(Rectangle(759, 174, 250, 50));

		ramStatus.setBounds(Rectangle(10, 238, 328, 40));
		intStorageStatus.setBounds(Rectangle(348, 238, 328, 40));
		usbStorageStatus.setBounds(Rectangle(686, 238, 328, 40));

		totalRamLable.setBounds(Rectangle(10, 282, 146, 40));
		freeRamLable.setBounds(Rectangle(10, 326, 146, 40));
		usedRamLable.setBounds(Rectangle(10, 370, 146, 40));

		totalRam.setBounds(Rectangle(156, 282, 182, 40));
		freeRam.setBounds(Rectangle(156, 326, 182, 40));
		usedRam.setBounds(Rectangle(156, 370, 182, 40));

		totalDiskSpaceLable.setBounds(Rectangle(348, 282, 146, 40));
		availableUserDiskSpaceLable.setBounds(Rectangle(348, 326, 146, 40));
		systemUsedDiskSpaceLable.setBounds(Rectangle(348, 370, 146, 40));

		totalDiskSpace.setBounds(Rectangle(494, 282, 182, 40));
		availableUserDiskSpace.setBounds(Rectangle(494, 326, 182, 40));
		systemUsedDiskSpace.setBounds(Rectangle(494, 370, 182, 40));

		totalUsbDiskSpaceLable.setBounds(Rectangle(686, 282, 146, 40));
		availableUsbDiskSpaceLable.setBounds(Rectangle(686, 326, 146, 40));

		totalUsbDiskSpace.setBounds(Rectangle(832, 282, 182, 40));
		availableUsbDiskSpace.setBounds(Rectangle(832, 326, 182, 40));

		refreshBtn.setBounds(Rectangle(240, 426, 267, 44));
		fwUpdateBtn.setBounds(Rectangle(517, 426, 267, 44));
	}

	FwStatus_t IgniteDeviceStatus::startFirmwareUpgrade(SwUdateSource_t mode, FwStatus_t status)
	{
		std::vector<IgniteParamList> paramList;
		IgniteParamList params;

		if (mode == SwUdateSource_t::PC)
		{
			/* Set Upgrade source as PC (PlayTribe App) */
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_Firmware_Update_Source, (int)mode, false);

			params.param = (paramId_t)FrontPannelParam::paramKey_Valid_Firmware_check;
			paramList.push_back(params);
			paramList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramList);
			status = (FwStatus_t)paramList[0].MsgValue.get<std::int8_t>();
		}

		if (status == FwStatus_t::NEW_FW)
		{
			DBG("Firmware initiated");
			if (!popupPtr->isPreloaderRunning())
			{
				popupPtr->close();
				popupPtr->showPreloader("Firmware Update", "Firmware Update in Progress");
			}
			else
				popupPtr->setInfoText("Firmware Update in Progress");
			CommonUtils::SetUtilsVisiblity(true);
			/* Decrypt Firmware package */
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_decryptFirmwareImage, (int)mode, false);

			/* Extract Firmware package */
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_ExtractFirmwareImage, (int)mode, false);

			IgniteSettings::GetAppSettingsInstance()->initiateFirmwareUpdate(mode);
		}
		return status;
	}
	bool IgniteDeviceStatus::handleFirmwareUpgrade(SwUdateSource_t mode)
	{
		popupPtr->close();
		popupPtr->showPreloader("Firmware Update", "Checking New Firmware Package");

		std::vector<IgniteParamList> paramList;
		IgniteParamList params;

		/* Set Upgrade source as Intenral */
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_Firmware_Update_Source, (int)SwUdateSource_t::INTERNAL, false);

		params.param = (paramId_t)FrontPannelParam::paramKey_Valid_Firmware_check;
		paramList.push_back(params);
		params.param = (paramId_t)FrontPannelParam::paramKey_UsbGetConnectionStatus;
		paramList.push_back(params);
		paramList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramList);
		fw_pkg_status = (FwStatus_t)paramList[0].MsgValue.get<std::int8_t>();
		auto usb_conn_status = paramList[1].MsgValue.get<std::int8_t>();
		mode = SwUdateSource_t::INTERNAL;

		if ((fw_pkg_status != FwStatus_t::NEW_FW) && (usb_conn_status))
		{
			/* Set Upgrade source as USB DISK APP */
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_Firmware_Update_Source, (int)SwUdateSource_t::USBDISK, false);

			params.param = (paramId_t)FrontPannelParam::paramKey_Valid_Firmware_check;
			paramList.push_back(params);
			paramList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, paramList);
			fw_pkg_status = (FwStatus_t)paramList[0].MsgValue.get<std::int8_t>();
			mode = SwUdateSource_t::USBDISK;
		}
		if (fw_pkg_status == FwStatus_t::NEW_FW)
		{
			DBG("New Firmware found");
			popupPtr->close();
			popupPtr->timerCallback();
			popupPtr->setPopUpPropories("Firmware Update", 604, 290);
			popupPtr->setbtnsize(265, 44);
			popupPtr->setInfoText("New Firmware version found, Press Yes to start Firmware update");
			popupPtr->addImageButton("Cancel", "btn-resetcancel-default.png", "btn-resetcancel-active.png", 2);
			popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_RESET;
			popupPtr->requestforReturnValueCallback();
			popupPtr->isCloseButtonVisible(false);
			popupPtr->show();

			popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 2)
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					}
					else
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);

					}
				};

			popupPtr->onActionReturnvalue = [this, mode](int r)
				{
					popupPtr->close();
					if (r == 1)
						startFirmwareUpgrade(mode, fw_pkg_status);
				};
		}
		else
		{
			popupPtr->close();
			popupPtr->timerCallback();
			if (popupPtr->isDialogOpen.get() != true)
			{
				popupPtr->setPopUpPropories("Status", 604, 290);
				switch (fw_pkg_status)
				{
				case FwStatus_t::INVALID_FW:
					popupPtr->setInfoText("InValid or no firmware found !!!!");
					break;
				case FwStatus_t::OLD_FW:
				case FwStatus_t::SAME_FW:
					popupPtr->setInfoText("Your software is up to date");
					break;
				case FwStatus_t::FW_NOT_PRESENT:
					popupPtr->setInfoText("No Valid Firmware found !!!! \n Please keep the firmware file in root directory of \n USB storage or flash drive and try again");
					break;
				}
				popupPtr->setbtnsize(544, 44);
				popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
				popupPtr->popupType = POPUP_WITHOK;
				popupPtr->isCloseButtonVisible(false);
				popupPtr->show();
				popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);
						}
					};
			}
		}
		return false;
	}

	void IgniteDeviceStatus::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		std::vector<IgniteParamList> paramList;
		IgniteParamList params;

		if (buttonThatWasClicked == &refreshBtn)
		{
			refreshData();
		}
		if (buttonThatWasClicked == &fwUpdateBtn)
		{
			showFirmwareUpdateSourceOptions();
			//handleFirmwareUpgrade(SwUdateSource_t::INTERNAL);
		}
	}

	bool IgniteDeviceStatus::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			popupPtr->FPKeyHandler(true, param, KeyValue);

		if (keyFocusedItem == DeviceStatusMenuViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			keyFocusedItem = DeviceStatusMenuViewItemID::REFRESH_STATUS;

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
				keyFocusedItem = (keyFocusedItem + 1 >= DeviceStatusMenuViewItemID::FOCUS_MAX ? (DeviceStatusMenuViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				keyFocusedItem = (keyFocusedItem - 1 <= DeviceStatusMenuViewItemID::NO_FOCUS ? (DeviceStatusMenuViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
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

	void IgniteDeviceStatus::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{

		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;
			
			switch (deviceStatusMenuView[keyFocusedItem])
			{
			case REFRESH_STATUS:
				refreshBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case FIRMWARE_UPGRADE:
					fwUpdateBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;

			default:
				break;
			}
			repaint();
	}

	void IgniteDeviceStatus::showFirmwareUpdateSourceOptions()
	{
		popupPtr->close();
		popupPtr->setPopUpPropories(" Supporting Firmware Update Modes", 604, 290);
		popupPtr->setbtnsize(137, 35);
		popupPtr->addButtonWithBounds("USB Drive Update", 1, ui::Rectangle<int>{29, 105, 268, 50});
		popupPtr->addButtonWithBounds("Wifi Update", 2, ui::Rectangle<int>{307, 105, 268, 50});
		popupPtr->addButtonWithBounds("USB Update", 3, ui::Rectangle<int>{29, 165, 268, 50});

		popupPtr->popupType = POPUP_WITHCLOSE;
		popupPtr->isCloseButtonVisible(true);
		popupPtr->SetControlBtnLine(false);
		popupPtr->requestforReturnValueCallback();
		popupPtr->show();

		popupPtr->onSelectionChanged = [this](int r)
			{
				if (r == 1)
				{
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
				}
				else if (r == 2)
				{
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
				}
				else if (r == 3)
				{
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
				}
			};

		popupPtr->onActionReturnvalue = [this](int r)
			{
				popupPtr->close();
				if (r == 1)
					handleUSBDriveSelection();
				else if (r == 2)
					startWifiHandler();
				else if (r == 3)
					startUsbHandler();
			};
	}

	void IgniteDeviceStatus::startUsbHandler()
	{
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_startPlayTribeUsbHandler, true, false);
	}

	void IgniteDeviceStatus::startWifiHandler()
	{
		igniteConnectivity = IgniteConnectivity::GetAppConnectivityInstance();
		if (igniteConnectivity->getWifiConnectionState() == WIFI_STATE::WIFI_CONNECTING)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_startPlayTribeWifiHandler, true, false);
		}
		else
		{
			popupPtr->close();
			popupPtr->setPopUpPropories("Wi-Fi Connection Needed", 604, 290);
			popupPtr->setbtnsize(265, 44);
			popupPtr->setInfoText("Wi-Fi is not connected, Please connect to Wi-Fi to proceed.");
			popupPtr->addButton("Cancel", 2);
			popupPtr->addButton("Connect to Wi-Fi", 1);
			popupPtr->isCloseButtonVisible(false);
			popupPtr->popupType = POPUP_WITHOKCANCEL;
			popupPtr->SetControlBtnLine(true);
			popupPtr->requestforReturnValueCallback();
			popupPtr->show();

			popupPtr->onSelectionChanged = [this](int r)
				{
					if (r == 1)
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					}
					else
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					}
				};

			popupPtr->onActionReturnvalue = [this](int r)
				{
					popupPtr->close();
					if (r == 1)
						this->postCommandMessage(1);
				};
		}
	}

	void IgniteDeviceStatus::handleUSBDriveSelection()
	{
		popupPtr->close();
		if (popupPtr->isDialogOpen.get() != true)
		{
			handleFirmwareUpgrade(SwUdateSource_t::INTERNAL);
		}
	}

	void IgniteDeviceStatus::handleCommandMessage(int id)
	{
		if (id == 1)
		{

			if (igniteConnectivity)
			{
				//igniteConnectivity->updateLedStatus(true);
				igniteConnectivity->updateDataFromEngine();
				igniteConnectivity->setVisible(true);
				igniteConnectivity->toFront(true);
			}
		}
	}
};