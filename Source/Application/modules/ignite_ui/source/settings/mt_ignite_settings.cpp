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

using namespace Ignite;

namespace ui
{

	//FwUpgardeThread("FrontPanneIN", 1600, osPriorityHigh),

	////////////////////////////////////////////////
	//   Class: Ignite Record
	////////////////////////////////////////////////
	IgniteSettings::IgniteSettings() : FwUpgardeThread("FrontPanneIN", 1600, osPriorityHigh)
	{
		brightnesSlider.makeVisibleAndAddListner(this);
		brightnesSlider.setRange(0, 100, 25);
		brightnesSlider.setValue(80.0, dontSendNotification);
		brightnesSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
		brightnesSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 70, 50);
		brightnesSlider.setColour(Slider::ColourIds::trackColourId, Theme::Instance().getColour(customOrange));
		brightnesSlider.setColour(Slider::ColourIds::thumbColourId, Theme::Instance().getColour(neutralWhite));
		brightnesSlider.setColour(Slider::ColourIds::backgroundColourId, Colour(0xFF101226));
		brightnesSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Theme::Instance().getColour(neutralWhite));
		brightnesSlider.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour(0xFF101226));
		brightnesSlider.setComponentID("sliderComp");

		addAndMakeVisible(themeBtn);
		themeBtn.addListener(this);
		themeBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		themeBtn.showBorder(false);
		themeBtn.setVisible(false);
		themeBtn.setComponentID("themeComp");
		themeBtn.setTextColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(brightnessBtn);
		brightnessBtn.addListener(this);
		brightnessBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		brightnessBtn.showBorder(true);
		brightnessBtn.setVisible(true);
		brightnessBtn.setComponentID("brightnessComp");
		brightnessBtn.setButtonText("Display Brightness");

		addAndMakeVisible(deviceStatusBtn);
		deviceStatusBtn.addListener(this);
		deviceStatusBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		deviceStatusBtn.setToggleable(true);
		deviceStatusBtn.setComponentID("upgradeComp");

		addAndMakeVisible(factoryResetBtn);
		factoryResetBtn.addListener(this);
		factoryResetBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		factoryResetBtn.setToggleable(true);
		factoryResetBtn.setComponentID("resetComp");

		addAndMakeVisible(backupBtn);
		backupBtn.addListener(this);
		backupBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		backupBtn.setToggleable(true);
		backupBtn.setComponentID("backupComp");

		addAndMakeVisible(midiClockConfigBtn);
		midiClockConfigBtn.addListener(this);
		midiClockConfigBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		midiClockConfigBtn.setToggleable(true);
		midiClockConfigBtn.setComponentID("midiClkCfgComp");
		midiClockConfigBtn.sethoverImages("btn-midi-clock-default-hover.png", "", "");

		/*addAndMakeVisible(mmcConfigBtn);
		mmcConfigBtn.addListener(this);
		mmcConfigBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		mmcConfigBtn.setToggleable(true);
		mmcConfigBtn.setComponentID("mmcCfgComp");*/

		/*addAndMakeVisible(midiRemoteControlBtn);
		midiRemoteControlBtn.addListener(this);
		midiRemoteControlBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		midiRemoteControlBtn.setToggleable(true);
		midiRemoteControlBtn.setComponentID("rmtCtrlComp");*/

		addAndMakeVisible(bRayBtn);
		bRayBtn.addListener(this);
		bRayBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		bRayBtn.setToggleable(true);
		bRayBtn.setComponentID("brayComp");

		/*addAndMakeVisible(midiTransposeBtn);
		midiTransposeBtn.addListener(this);
		midiTransposeBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		midiTransposeBtn.setToggleable(true);
		midiTransposeBtn.setComponentID("midiXposeComp");*/

		addAndMakeVisible(auditionCfgBtn);
		auditionCfgBtn.addListener(this);
		auditionCfgBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		auditionCfgBtn.setToggleable(true);
		auditionCfgBtn.setComponentID("auditionComp");

		addAndMakeVisible(miscBtn);
		miscBtn.addListener(this);
		miscBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		miscBtn.setToggleable(true);
		miscBtn.setComponentID("miscComp");

		addAndMakeVisible(connectvityBtn);
		connectvityBtn.addListener(this);
		connectvityBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
		connectvityBtn.setToggleable(true);
		connectvityBtn.setComponentID("connectivityComp");

		addAndMakeVisible(wipeUnassignedInstrBtn);
		wipeUnassignedInstrBtn.addListener(this);
		wipeUnassignedInstrBtn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		wipeUnassignedInstrBtn.setEnabled(false);
		
		settingsOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(settingsOptCtl);
		settingsOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		settingsOptCtl->addOptCtlListener(this);

		deviceStatusBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		factoryResetBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		backupBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		themeBtn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		brightnessBtn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		bRayBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	//	midiRemoteControlBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		midiClockConfigBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		//mmcConfigBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		//midiTransposeBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		auditionCfgBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		miscBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		connectvityBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		brightnesSlider.setLookAndFeel(BrightnessSilderLnF::getLnf());
		brightnessToggle.sethoverImages("brightness-toggle-option1-hover.png", "brightness-toggle-option2-hover.png", "brightness-toggle-option1-hover.png");
		settingsBox1.items.add(FlexItem(midiClockConfigBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox1.items.add(FlexItem(bRayBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox1.items.add(FlexItem(auditionCfgBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		//settingsBox1.items.add(FlexItem(midiRemoteControlBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		//settingsBox1.items.add(FlexItem(mmcConfigBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		//settingsBox1.items.add(FlexItem(midiTransposeBtn).withMargin({ 0,8,8,0 }).withFlex(1));

		settingsBox2.items.add(FlexItem(deviceStatusBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox2.items.add(FlexItem(backupBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox2.items.add(FlexItem(factoryResetBtn).withMargin({ 0,8,8,0 }).withFlex(1));

		/*settingsBox3.items.add(FlexItem(deviceStatusBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox3.items.add(FlexItem(backupBtn).withMargin({ 0,8,8,0 }).withFlex(1));*/
		settingsBox3.items.add(FlexItem(connectvityBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox3.items.add(FlexItem(miscBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		settingsBox3.items.add(FlexItem(wipeUnassignedInstrBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		

		settingsBox.flexDirection = FlexBox::Direction::column;
		settingsBox.items.add(FlexItem(settingsBox1).withFlex(1));
		settingsBox.items.add(FlexItem(settingsBox2).withFlex(1));
		settingsBox.items.add(FlexItem(settingsBox3).withFlex(1));
		//settingsBox.items.add(FlexItem(settingsBox4).withFlex(1).withMaxWidth(675.0f));

		brayComp = IgniteBRaySettings::GetAppBrayInstance();
		addChildComponent(brayComp);
		brayComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		brayComp->setVisible(false);

		auditionComp = IgniteAuditionSettings::GetAppAuditionInstance();
		addChildComponent(auditionComp);
		auditionComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		auditionComp->setVisible(false);

		connComp = IgniteConnectivity::GetAppConnectivityInstance();
		addChildComponent(connComp);
		connComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		connComp->setVisible(false);
		
		popupPtr = CommonPopUp::getCommonPopupInstance();

		midiRemoteCtrlComp = IgniteMidiRemoteControl::GetAppMidiRemoteControlInstance();
		addChildComponent(midiRemoteCtrlComp);;
		midiRemoteCtrlComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		midiRemoteCtrlComp->setVisible(false);

		backupComp = IgniteBackup::GetAppBackupInstance();
		addChildComponent(backupComp);;
		backupComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		backupComp->setVisible(false);

		midiClkComp = IgniteMidiClkSetting::GetAppMidiClkInstance();
		addChildComponent(midiClkComp);;
		midiClkComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		midiClkComp->setVisible(false);

		transposeComp = IgniteTransposeSettings::GetAppTransposeInstance();
		addChildComponent(transposeComp);;
		transposeComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		transposeComp->setVisible(false);

		miscSettingComp = IgniteMiscSettings::GetAppSettingsInstance();
		addChildComponent(miscSettingComp);;
		miscSettingComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		miscSettingComp->setVisible(false);

		/*mmcComp = IgniteMidiMachineControl::GetAppMidiMachineControlInstance();
		addChildComponent(mmcComp);;
		mmcComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		mmcComp->setVisible(false);*/

		deviceStatusComp = IgniteDeviceStatus::GetDevStatusInstance();
		addChildComponent(deviceStatusComp);;
		deviceStatusComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		deviceStatusComp->setVisible(false);
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();

		brightnessToggle.makeVisibleAndAddListner(this);
		brightnessToggle.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		brightnessToggle.setComponentID("brightnessToggle");
		brightnessToggle.setToggleState(true, dontSendNotification);
		getAssets();
	}

	IgniteSettings::~IgniteSettings()
	{
	}
	void IgniteSettings::getAssets()
	{
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-default.png"));
		imageHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-default-hover.png"));
		imageDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-disabled.png"));
		imageActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("toggle-btn-bg-active.png"));
		imageBrigtnessKnob= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("brightnes-knob.png"));
	}

	void IgniteSettings::setWipeInstrumentsBtnState(bool state)
	{
		if (state)
			wipeUnassignedInstrBtn.setEnabled(true);
		else
			wipeUnassignedInstrBtn.setEnabled(false);
	}

	void IgniteSettings::paint(juce::Graphics& g)
	{
		if (settingsDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("Settings*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Settings");
		
		Image Draw;

		/*Draw = calibBtn.getToggleState() ? BtnActiveImage : ((calibBtn.isMouseOver() || calibBtn.isFocused) ? OverImage : defaultImage);
		g.drawImage(Draw, ui::Rectangle<float>{ 347, 340, 328, 80 });*/

		g.drawImage(imageBrigtnessKnob, ui::Rectangle<float>{ 10, 430, 1004, 40 });

		Draw = wipeUnassignedInstrBtn.isEnabled() ? ((wipeUnassignedInstrBtn.isMouseOver() || wipeUnassignedInstrBtn.isFocused) ? imageHover : imageDefault) : imageDisabled;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 250, 328, 80 });
	}

	void IgniteSettings::enableControlButton(IgniteControlOptions::eKey key, bool state)
	{
		settingsOptCtl->enableKey(key, state);
	}

	void IgniteSettings::updateData()
	{
		std::vector<IgniteParamList> SettingsGeneralCnfgParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgBrightnessParam;
		SettingsGeneralCnfgParams.push_back(params);

		SettingsGeneralCnfgParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, SettingsGeneralCnfgParams);

		brightnesSlider.setValue(SettingsGeneralCnfgParams[0].MsgValue.get<int8_t>(), dontSendNotification);
		current_screen = NO_FOCUS;

		brightnessToggle.setVisible(true);
	}

	void IgniteSettings::resized()
	{
		settingsBox.performLayout(ui::Rectangle(10, yStartSettingBox, 1012, 270));
		brightnessToggle.setBounds(ui::Rectangle(20, 437, 20, 24));
		brightnessBtn.setBounds(ui::Rectangle(40, 437, 140, 25));
		brightnesSlider.setBounds(ui::Rectangle(180, 435, 815, 30));
	}

	void IgniteSettings::sliderValueChanged(juce::Slider* sliderThatWasMoved)
	{
		if (sliderThatWasMoved == &brightnesSlider)
		{
			if (brightnessBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FPLED_Brightness, (int)brightnesSlider.getValue(), false);
			else
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_LCD_Brightness, (int)brightnesSlider.getValue(), false);

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgBrightnessParam, (int)brightnesSlider.getValue(), false);

			settingsOptCtl->enableKey(IgniteControlOptions::SAVE, true);
			settingsOptCtl->enableKey(IgniteControlOptions::UNDO, true);
			settingsDataUpdated = true;
		}
	}

	bool IgniteSettings::startFirmwareUpadate()
	{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		int connfd = -1;
		struct progress_msg msg;
		isSwUpdateGoing = true;
		deviceStatusComp->devStatusStopTimer();
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_Firmware_Update, (int)true, false);
		system("/bin/fw_setenv force_reboot yes");
		{
			int count = 100;
			int status;
			std::string line;
			while (count--)
			{
				juce::File infofile("/tmp/update_status");
				if (infofile.existsAsFile())
				{
					juce::String fileContent = infofile.loadFileAsString();
					status = fileContent.getIntValue();
				}
				else
					status = -1;

				if (status == 1)
					break;
				DBG("Awaiting completion");
				sleep(1);
			}
		}

		if (juce::File("/tmp/fwupdate/Ignite_MCU.hex").exists())
		{
			isSwUpdateGoing = true;
			DBG("IN MCU UPDATE NOW");

			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FwUpgrade, 1);
			while (isSwUpdateGoing);
			DBG("EXIT FOR MCU LOCK");
		}
		isSwUpdateGoing = false;
		DBG("Upgrade completed reboot device");
		Fw_Upgarde = true;
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_DevStatus, FW_UPDATE_COMPLETED);
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_removeFirmwarePacakge, FW_UPDATE_COMPLETED);
		popupPtr->setInfoText("Firmware upgrade successfull, Device will restart automatically in 5 seconds");
		sleep(6);
		system("reboot");
#endif
		return true;
	}

	bool IgniteSettings::initiateFirmwareUpdate(SwUdateSource_t mode)
	{
		updateSource = mode;
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_SOMFwUpdate, (int)true, false);
		FwUpgardeThreadFunctionCB = [](void* context) { static_cast<IgniteSettings*> (context)->FwUpgardeThreadFunction(); };
		FwUpgardeThread.startThread(FwUpgardeThreadFunctionCB, this);
		return true;
	}

	void IgniteSettings::FwUpgardeThreadFunction()
	{
		operationType = FIRMWARE_OP;
		if (!startFirmwareUpadate())
			setTimeLimittoGif(1000);
	}

	void IgniteSettings::pcOpOngoingPopUpCtl(bool state)
	{
		if (state)
		{
			popupPtr->close();
			popupPtr->showPreloader("", "File Transfer ongoing between Device and PC");
		}
		else
		{
			if (!isSwUpdateGoing)
			{
				DBG("Preloader closed");
				popupPtr->close();
				CommonUtils::SetUtilsVisiblity(false);
			}
		}
	}

	int IgniteSettings::connect_ipc(bool reconnect)
	{
		int fd = -1;
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		DBG("IN CONNECT_IPC ");
		struct sockaddr_un servaddr;
		fd = socket(AF_LOCAL, SOCK_STREAM, 0);
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sun_family = AF_LOCAL;
		strncpy(servaddr.sun_path, socketpath, sizeof(servaddr.sun_path) - 1);

		/*
		 * Check to get a valid socket
		 */
		if (fd < 0)
			return -1;

		do
		{
			if (connect(fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == 0)
			{
				break;
			}
			if (!reconnect)
			{
				DBG("cannot communicate with SWUpdate via " << socketpath);
				exit(1);
			}
			usleep(1000);
		} while (true);

		DBG("Connected to SWUpdate via=" << socketpath);
#endif
		return fd;
	}

	int IgniteSettings::progress_ipc_receive(int* connfd, struct progress_msg* msg)
	{
		int ret = -1;
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		ret = read(*connfd, msg, sizeof(*msg));
		DBG("ret-> " << ret);
		if (ret != sizeof(*msg))
		{
			DBG("Connection closing..\n");
			close(*connfd);
			*connfd = -1;
			return -1;
		}
#endif
		return ret;
	}
	void IgniteSettings::startFactoryReset()
	{
		this->FactoryReset = true;
		operationType = FACTORY_RESET_OP;

		popupPtr->close();
		popupPtr->showPreloader("Factory Reset", "Factory Reset in Progress");
		setTimeLimittoGif(5000);

		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_DevStatus, (int)FACTORY_RESET_ONGOING, false);
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FactoryReset, (int)true, false);

	}

	void IgniteSettings::factoryResetPopup()
	{
		if (popupPtr->isDialogOpen.get() != true)
		{
			popupPtr->close();
			popupPtr->setPopUpPropories("Factory Reset", 604, 290);
			popupPtr->setbtnsize(265, 44);
			popupPtr->setInfoText("Are you sure you want to Reset into Factory Setting?");
			popupPtr->addImageButton("Cancel", "btn-secondary-cancel-267x44-default.png", "btn-secondary-cancel-267x44-default-hover.png", 2);
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
			popupPtr->onActionReturnvalue = [this](int r)
				{
					if (r == 1)
					{
						//this->FactoryReset = true;
						//operationType = FACTORY_RESET_OP;
						startFactoryReset();
					}

				};
		}
	}

	void IgniteSettings::gifPreloaderSettingPopup(String message)
	{
		settingGifcomp = new IgniteGifPreloader(604, 290);
		settingGifcomp->setProgressStatus(message);
		settingGifcomp->show();
		setTimeLimittoGif(8000);
	}

	void IgniteSettings::setProgressStatusMessage(String message)
	{
		settingGifcomp->setProgressStatus(message);
	}

	void IgniteSettings::setTimeLimittoGif(int countLimit)
	{
		startTimer(countLimit);
	}

	void IgniteSettings::timerCallback()
	{
		stopTimer();
		if (auto dw = getCurrentlyModalComponent())
			dw->exitModalState(0);

		popupPtr->close();
		if (operationType == FACTORY_RESET_OP)
		{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
			popupPtr->setPopUpPropories("Factory Reset Status", 604, 290);
			popupPtr->setInfoText("Factory Reset is success: device will reboot in 5 sec");
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_McuSleepMode, 0);
			sleep(5);
			system("fw_setenv force_reboot yes");
			system("reboot");
#endif
			popupPtr->setPopUpPropories("Factory Reset Status", 604, 290);
			popupPtr->setInfoText("Factory reset failed !!!");
		}
		else if (operationType == FIRMWARE_OP)
		{
			popupPtr->setPopUpPropories("Firmware Update Status", 604, 290);
			popupPtr->setInfoText("Firmware upgrade failed !!!");
		}
		popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
		popupPtr->popupType = POPUP_WITHOK;
		popupPtr->isCloseButtonVisible(false);
		popupPtr->show();
		popupPtr->onSelectionChanged = [this](int r)
			{
				if (r == 1)
				{
					if (this->FactoryReset)
					{
#if defined(__linux__) || defined(__linux) || defined(linux)
						system("/bin/fw_setenv force_reboot yes");
						system("reboot");
#endif
					}
					FactoryReset = false;
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
				}
			};
		
	}

	void IgniteSettings::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &themeBtn)
		{
		}
		else if (buttonThatWasClicked == &deviceStatusBtn)
		{
			brightnessToggle.setVisible(false);
			deviceStatusBtn.setToggleState(false, dontSendNotification);
			deviceStatusComp->updateSerialAndFimrwareData();
			deviceStatusComp->refreshData();
			deviceStatusComp->setVisible(true);
			current_screen = DEVICE_STATUS;
			KeyFocusedItem = DEVICE_STATUS;
		}
		else if (buttonThatWasClicked == &factoryResetBtn)
		{
			factoryResetBtn.setToggleState(false, dontSendNotification);
			factoryResetPopup();
			current_screen = FACTORY_RESET;
			KeyFocusedItem = FACTORY_RESET;
		}
		else if (buttonThatWasClicked == &backupBtn)
		{
			brightnessToggle.setVisible(false);
			backupBtn.setToggleState(false, dontSendNotification);
			backupComp->setVisible(true);
			current_screen = BACKUP;
			KeyFocusedItem = BACKUP;
		}
		else if (buttonThatWasClicked == &midiClockConfigBtn)
		{
			brightnessToggle.setVisible(false);
			midiClockConfigBtn.setToggleState(false, dontSendNotification);
			midiClkComp->updateData();
			midiClkComp->setVisible(true);
			current_screen = MIDI_CLK_CONFIG;
			KeyFocusedItem = MIDI_CLK_CONFIG;
		}
		else if (buttonThatWasClicked == &bRayBtn)
		{
			brightnessToggle.setVisible(false);
			bRayBtn.setToggleState(false, dontSendNotification);
			brayComp->setVisible(true);
			brayComp->updateData();
			if (brayComp->brayConfigDataUpdated)
			{
				brayComp->enableControlButton(IgniteControlOptions::SAVE, true);
				brayComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				brayComp->enableControlButton(IgniteControlOptions::SAVE, false);
				brayComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			current_screen = BRAY;
			KeyFocusedItem = BRAY;
		}
		/*else if (buttonThatWasClicked == &midiRemoteControlBtn)
		{
			brightnessToggle.setVisible(false);
			midiRemoteControlBtn.setToggleState(false, dontSendNotification);
			midiRemoteCtrlComp->setVisible(true);
			midiRemoteCtrlComp->updateData();

			if (midiRemoteCtrlComp->remoteControlDataUpdated)
			{
				midiRemoteCtrlComp->enableControlButton(IgniteControlOptions::SAVE, true);
				midiRemoteCtrlComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				midiRemoteCtrlComp->enableControlButton(IgniteControlOptions::SAVE, false);
				midiRemoteCtrlComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			current_screen = REMOTE_CONTROL;
			KeyFocusedItem = REMOTE_CONTROL;
		}
		else if (buttonThatWasClicked == &midiTransposeBtn)
		{
			brightnessToggle.setVisible(false);
			midiTransposeBtn.setToggleState(false, dontSendNotification);
			transposeComp->setVisible(true);
			transposeComp->updateData();

			if (transposeComp->transposeConfigDataUpdated)
			{
				transposeComp->enableControlButton(IgniteControlOptions::SAVE, true);
				transposeComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				transposeComp->enableControlButton(IgniteControlOptions::SAVE, false);
				transposeComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			current_screen = MIDI_XPOSE_CONFIG;
			KeyFocusedItem = MIDI_XPOSE_CONFIG;
		}*/

		/*else if (buttonThatWasClicked == &mmcConfigBtn)
		{
			brightnessToggle.setVisible(false);
			mmcConfigBtn.setToggleState(false, dontSendNotification);
			mmcComp->setVisible(true);
			mmcComp->updateData();

			if (mmcComp->mmcDataUpdated)
			{
				mmcComp->enableControlButton(IgniteControlOptions::SAVE, true);
				mmcComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				mmcComp->enableControlButton(IgniteControlOptions::SAVE, false);
				mmcComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			current_screen = MMC_CONFG;
			KeyFocusedItem = MMC_CONFG;
		}*/

		else if (buttonThatWasClicked == &auditionCfgBtn)
		{
			brightnessToggle.setVisible(false);
			auditionCfgBtn.setToggleState(false, dontSendNotification);
			auditionComp->setVisible(true);
			auditionComp->updateData();

			if (auditionComp->auditionConfigDataUpdated)
			{
				auditionComp->enableControlButton(IgniteControlOptions::SAVE, true);
				auditionComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				auditionComp->enableControlButton(IgniteControlOptions::SAVE, false);
				auditionComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			current_screen = AUDITION_CFG;
			KeyFocusedItem = AUDITION_CFG;
			}

		else if (buttonThatWasClicked == &miscBtn)
		{
			brightnessToggle.setVisible(false);
			miscBtn.setToggleState(false, dontSendNotification);
			miscSettingComp->setVisible(true);
			miscSettingComp->updateData();

			if (miscSettingComp->miscSettingsDataUpdated)
			{
				miscSettingComp->enableControlButton(IgniteControlOptions::SAVE, true);
				miscSettingComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				miscSettingComp->enableControlButton(IgniteControlOptions::SAVE, false);
				miscSettingComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			current_screen = MISC_SETTING;
			KeyFocusedItem = MISC_SETTING;
		}
		else if (buttonThatWasClicked == &connectvityBtn)
		{
			brightnessToggle.setVisible(false);
			connectvityBtn.setToggleState(false, dontSendNotification);
			connComp->setVisible(true);
			connComp->updateLedStatus(true);
			connComp->updateDataFromEngine();

			if (connComp->connDataUpdated)
			{
				connComp->enableControlButton(IgniteControlOptions::SAVE, true);
				connComp->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else
			{
				miscSettingComp->enableControlButton(IgniteControlOptions::SAVE, false);
				miscSettingComp->enableControlButton(IgniteControlOptions::UNDO, false);
			}
			current_screen = CONNECTVITY;
			KeyFocusedItem = CONNECTVITY;
			}
		else if (buttonThatWasClicked == &brightnessBtn)
		{
			if (brightnessBtn.getToggleState())
			{
				brightnessBtn.setButtonText("LED Brightness");
				brightnessToggle.setToggleState(false, dontSendNotification);
			}
			else
			{
				brightnessBtn.setButtonText("Display Brightness");
				brightnessToggle.setToggleState(true, dontSendNotification);
			}
		}
		else if (&brightnessToggle == buttonThatWasClicked)
		{
			if (!brightnessToggle.getToggleState())
			{
				brightnessBtn.setButtonText("LED Brightness");
				brightnessBtn.setToggleState(true, dontSendNotification);
			}
			else
			{
				brightnessBtn.setButtonText("Display Brightness");
				brightnessBtn.setToggleState(false, dontSendNotification);
			}
		}
		else if (&wipeUnassignedInstrBtn == buttonThatWasClicked)
		{
			IgniteInstruments::GetAppInstrumentsInstance()->deleteUnassignedInstruments();
		}
	}

	void IgniteSettings::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			settingsDataUpdated = false;
		}
		else if (option == IgniteControlOptions::AUTOSAVEON)
		{
			isAutosave = true;
		}
		else if (option == IgniteControlOptions::AUTOSAVEOFF)
		{
			isAutosave = false;
		}
		if (this->isVisible() && !miscSettingComp->isVisible() && !brayComp->isVisible() && !midiRemoteCtrlComp->isVisible() && 
			!midiClkComp->isVisible() && !transposeComp->isVisible() && !auditionComp->isVisible() && 
			!IgniteCalibration::GetAppCalibrationInstance()->isVisible() && !connComp->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("Save ", 604, 290);
					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String("Save Settings edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
						{
							if (r == 1)
							{
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgSave, 0);
								settingsOptCtl->enableKey(IgniteControlOptions::SAVE, false);
								settingsOptCtl->enableKey(IgniteControlOptions::UNDO, false);
								settingsDataUpdated = false;
							}
							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);
						};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (settingsDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> settingCtlParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsGeneralCnfgParam::paramUndoListCmd;
					settingCtlParamList.push_back(params);
					settingCtlParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, settingCtlParamList);
					if (settingCtlParamList.size() == 1)
					{
						settingsDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgniteSettings::isEditing()
	{
		int index = 0;

		if (KeyFocusedItem == DEVICE_STATUS)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = DEVICE_STATUS;
			}
			/*if (progressBarPtr != nullptr && progressBarPtr->isEditing())
			{
				index = FIRMWARE_UPGRDAE;
			}*/
		}
		else if (KeyFocusedItem == FACTORY_RESET)
		{
			if (popupPtr != nullptr && popupPtr->IsEditing())
			{
				index = FACTORY_RESET;
			}
		}

		return index;
	}

	bool IgniteSettings::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool handled = true;

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_FwUpgrade)
		{
			isSwUpdateGoing = KeyValue;
			DBG("MCU FIRMWARE DONE RESTART");
		}

		if (popupPtr != nullptr && popupPtr->IsEditing() && popupPtr->popupType != POPUP_RESET)
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
		{
			PannelSendKey(false, param, KeyValue);
			if (option_handler_focus == SETTING_DETAIL)
			{
				option_handler_focus = SETTING_OPTION;
			}
			else
			{
				option_handler_focus = SETTING_DETAIL;
			}
			PannelSendKey(true, param, KeyValue);
			return true;
		}

		if (FrontPannelParam::paramKey_MINUS_NAV == (FrontPannelParam)param || FrontPannelParam::paramKey_PLUS_NAV == (FrontPannelParam)param)
		{
			auto Svalue = brightnesSlider.getValue();
			auto rangevalue = brightnesSlider.getRange();
			if (FrontPannelParam::paramKey_MINUS_NAV == (FrontPannelParam)param)
			{
				if (Svalue != brightnesSlider.getMinimum())
				{
					brightnesSlider.setValue((Svalue-25),dontSendNotification);
				}
			}

			if (FrontPannelParam::paramKey_PLUS_NAV == (FrontPannelParam)param)
			{
				if (Svalue != brightnesSlider.getMaximum())
				{
					brightnesSlider.setValue((Svalue + 25), dontSendNotification);
				}
			}
				if (brightnessBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FPLED_Brightness, (int)brightnesSlider.getValue(), false);
				else
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_LCD_Brightness, (int)brightnesSlider.getValue(), false);

				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingGnrlCnfg, (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgBrightnessParam, (int)brightnesSlider.getValue(), false);

				settingsOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				settingsOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				settingsDataUpdated = true;
			return true;
		}

		if (option_handler_focus == SETTING_DETAIL)
		{
			switch (current_screen)
			{
			case BRAY:
				handled = (brayComp->PannelKeyHandler(param, KeyValue));
				break;
			/*case REMOTE_CONTROL:
				handled = (midiRemoteCtrlComp->PannelKeyHandler(param, KeyValue));
				break;*/
				/*case MMC_CONFG:
					handled = (mmcComp->PannelKeyHandler(param, KeyValue));
					break;*/
			case BACKUP:
				handled = (backupComp->PannelKeyHandler(param, KeyValue));
				break;
			case MIDI_CLK_CONFIG:
				handled = (midiClkComp->PannelKeyHandler(param, KeyValue));
				break;
			/*case MIDI_XPOSE_CONFIG:
				handled = (transposeComp->PannelKeyHandler(param, KeyValue));
				break;*/
			case DEVICE_STATUS:
				handled = (deviceStatusComp->pannelKeyHandler(param, KeyValue));
				break;
			case MISC_SETTING:
				handled = (miscSettingComp->pannelKeyHandler(param, KeyValue));
				break;
			case AUDITION_CFG:
				handled = (auditionComp->pannelKeyHandler(param, KeyValue));
				break;
			case CONNECTVITY:
				handled = (connComp->pannelKeyHandler(param, KeyValue));
				break;
			default:
				handled = false;
				break;
			}

			if (!handled)
			{
				bool setfocus = true;
				int EditItem = SettingsMenuViewItemID::NO_FOCUS;

				if (KeyFocusedItem == SettingsMenuViewItemID::NO_FOCUS)
				{
					/*1st key after Page visible */
					KeyFocusedItem = SettingsMenuViewItemID::MIDI_CLK_CONFIG;

					if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param && KeyValue == 1)
					{
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
						return true;
					}
				}
				else
				{
					EditItem = isEditing();
					if (EditItem)
					{
						if (KeyFocusedItem != EditItem)
						{
							PannelSendKey(false, param, KeyValue);
							KeyFocusedItem = EditItem;
						}
						setfocus = true;
					}
					else
					{
						PannelSendKey(false, param, KeyValue); // clear last Focus
						switch ((FrontPannelParam)param)
						{
						case FrontPannelParam::paramKey_RMOVELEFT:
							KeyFocusedItem = (KeyFocusedItem + 1 >= SettingsMenuViewItemID::FOCUS_MAX ? (SettingsMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
							break;
						case FrontPannelParam::paramKey_RMOVERIGHT:
							KeyFocusedItem = (KeyFocusedItem - 1 <= SettingsMenuViewItemID::NO_FOCUS ? (SettingsMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
							break;
						case FrontPannelParam::paramKey_RETURN_NAV:
							AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
							break;
						case FrontPannelParam::paramRot_ROW:
							if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
							{
								PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
								KeyFocusedItem = (KeyFocusedItem + SETTINGS_ROW_ITEMS >= SettingsMenuViewItemID::FOCUS_MAX ? ((KeyFocusedItem + SETTINGS_ROW_ITEMS) == (SettingsMenuViewItemID::FOCUS_MAX) ? (SettingsMenuViewItemID::FOCUS_MAX) : KeyFocusedItem) : KeyFocusedItem + SETTINGS_ROW_ITEMS);
								PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
							}
							else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
							{
								PannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
								KeyFocusedItem = (KeyFocusedItem - SETTINGS_ROW_ITEMS <= SettingsMenuViewItemID::NO_FOCUS ? (KeyFocusedItem) : KeyFocusedItem - SETTINGS_ROW_ITEMS);
								PannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
							}
							repaint();
							setfocus = false;
							break;
						}
					}
				}
				if (setfocus)
				{
					PannelSendKey(true, param, KeyValue);
				}
				handled = true;
			}
		}
		else
		{
			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				OptFocusedItem = (OptFocusedItem + 1 >= SettingsOptionsViewItemID::OP_FOCUS_MAX ? (SettingsOptionsViewItemID::OP_FOCUS_MAX) : OptFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				OptFocusedItem = (OptFocusedItem - 1 <= SettingsOptionsViewItemID::OP_NO_FOCUS ? (SettingsOptionsViewItemID::OP_NO_FOCUS + 1) : OptFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
				break;
			}
			PannelSendKey(true, param, KeyValue);
		}
		return handled;
	}

	void IgniteSettings::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (option_handler_focus == SETTING_DETAIL)
		{
			switch (SettingsMenuView[KeyFocusedItem])
			{
			case BRAY:
				bRayBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			/*case REMOTE_CONTROL:
				midiRemoteControlBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;*/
				/*case MMC_CONFG:
					mmcConfigBtn.FPKeyHandler(isFocuse, param, KeyValue);
					break;*/
			case DEVICE_STATUS:
				deviceStatusBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case FACTORY_RESET:
				if ((popupPtr != nullptr && popupPtr->IsEditing()) || FactoryReset)
				{
					popupPtr->FPKeyHandler(isFocuse, param, KeyValue);
				}
				else
				{
					factoryResetBtn.FPKeyHandler(isFocuse, param, KeyValue);
				}
				break;
			case BACKUP:
				backupBtn.FPKeyHandler(isFocuse, param, KeyValue);
				if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				{
					buttonClicked(&backupBtn);
				}
				break;
			case MIDI_CLK_CONFIG:
				midiClockConfigBtn.FPKeyHandler(isFocuse, param, KeyValue);
				if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				{
					buttonClicked(&midiClockConfigBtn);
				}
				break;
			/*case MIDI_XPOSE_CONFIG:
				midiTransposeBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;*/
			case AUDITION_CFG:
				auditionCfgBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case MISC_SETTING:
				miscBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case CONNECTVITY:
				connectvityBtn.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case BRIGHTNESS:
				brightnessBtn.FPKeyHandler(isFocuse, param, KeyValue);
				if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				{
					buttonClicked(&brightnessBtn);
				}
				break;
				/*
			case BRIGHTNESS_CTL:
				//brightnesSlider.FPKeyHandler(isFocuse, param, KeyValue);
				break;*/
			case WIPE_UNASSIGNED_INSTRUMENS:
				if (popupPtr != nullptr && popupPtr->IsEditing())
					popupPtr->FPKeyHandler(isFocuse, param, KeyValue);
				else
					wipeUnassignedInstrBtn.FPKeyHandler(isFocuse, param, KeyValue);
			default:
				break;
			}
			repaint();
		}
		else
		{
			switch (OptionsView[OptFocusedItem])
			{
			case OPT_UNDO:
				settingsOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			}
		}
	}
};
