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

const char* MCU_SYNCPIN_UNEXPORT = "echo 86 > /sys/class/gpio/unexport";
const char* MCU_SYNCPIN_EXPORT = "echo 86 > /sys/class/gpio/export";
const char* MCU_SYNCPIN_DIR_SET = "echo out > /sys/class/gpio/gpio86/direction";
const char* MCU_SYNCPIN_VAL_HIGH = "echo 1 > /sys/class/gpio/gpio86/value";
const char* MCU_SYNCPIN_VAL_LOW = "echo 0 > /sys/class/gpio/gpio86/value";
const char* MCU_RESETPIN_EXPORT = "echo 07 > /sys/class/gpio/export";
const char* MCU_RESETPIN_DIR_SET = "echo out > /sys/class/gpio/gpio7/direction";
const char* MCU_RESETPIN_VAL_HIGH = "echo 1 > /sys/class/gpio/gpio7/value";
const char* MCU_RESETPIN_VAL_LOW = "echo 0 > /sys/class/gpio/gpio7/value";
const char* MCU_RESETPIN_UNEXPORT = "echo 07 > /sys/class/gpio/unexport";

namespace ui
{
	AppHome& getAppHome()
	{

		AppHome* AppHome = AppHome::GetAppHomeInstance();
		return *AppHome;
	}

	AppHome::AppHome() :
		topBar(std::make_unique<IgniteTopBar>())
	{
#ifdef FP_UART_LINUX
		std::system(MCU_RESETPIN_EXPORT);
		std::system(MCU_RESETPIN_DIR_SET);
		std::system(MCU_RESETPIN_VAL_HIGH);
		std::system(MCU_RESETPIN_VAL_LOW);
	
		std::system(MCU_SYNCPIN_EXPORT);
		std::system(MCU_SYNCPIN_DIR_SET);
		std::system(MCU_SYNCPIN_VAL_HIGH);
#endif
		mainMode = AppMainmode::getMainModeInstance();
		statusBar = AppStatusbar::GetAppStatusBarInstance();
		barComp1 = SceneStatusBar::GetSceneBarInstance();
		barComp2 = PatternStatusBar::GetPatternBarInstance();

		addChildComponent(mainMode);
		addChildComponent(topBar.get());
		addChildComponent(statusBar);
		statusBar->setInterceptsMouseClicks(false, false);
		addChildComponent(barComp1);
		addChildComponent(barComp2);
		barComp1->setInterceptsMouseClicks(false, false);
		barComp2->setInterceptsMouseClicks(false, false);

		setSize(layout::screen.getWidth(), layout::screen.getHeight());
		mainMode->setBounds(layout::mainmode);
		statusBar->setBounds(layout::statusBar);
		barComp1->setBounds(layout::songBar2);
		barComp2->setBounds(layout::songBar1);
		mainMode->addMouseListener(this, true);
		show(screen::APP_MAIN_MODE, true);
		IgniteSong::getAppSongInstance()->updateDataFromEngine();
		//mainMode->startUsbHandler();

		playtribeConnStatusComp = PlaytribeConnectionStatus::GetPlaytribeConnectionStatusInstance();
		addChildComponent(playtribeConnStatusComp);
		playtribeConnStatusComp->setBounds(0, 0, 1024, 600);
		playtribeConnStatusComp->setVisible(false);

#if ENABLE_HARDWARE_TEST
		touchTestComp = new TouchscreenTestComponent;
		addChildComponent(touchTestComp);
		touchTestComp->setBounds(0, 0, layout::screen.getWidth(), layout::screen.getHeight());
		touchTestComp->setVisible(false);
#endif
#ifdef FP_UART_LINUX
		std::system(MCU_SYNCPIN_VAL_LOW);
#endif
	}

	AppHome::~AppHome()
	{}

	void AppHome::enableTouchTest(bool state)
	{
#if ENABLE_HARDWARE_TEST
		touchTestComp->resized();
		touchTestComp->setVisible(state);
#endif
	}

	void AppHome::show(ui::screen Screen, bool state)
	{
		hideAll();
		switch (Screen)
		{
		case screen::APP_MAIN_MODE:
			mainMode->setVisible(state);
			statusBar->setVisible(true);
			barComp1->setVisible(true);
			barComp2->setVisible(true);
			break;
		case screen::BAR:
			statusBar->setVisible(true);
			barComp1->setVisible(true);
			barComp2->setVisible(true);
			break;
		default: break;
		};
		// Always show top and bottom bar...
		topBar->setVisible(true);
	}

	void AppHome::hideAll()
	{
		barComp1->setVisible(false);
		barComp2->setVisible(false);
		statusBar->setVisible(false);
		mainMode->setVisible(false);
	}

	void AppHome::paint(juce::Graphics& g)
	{
		g.fillAll(Theme::Instance().getColour(neutralBlack));
	}

	void AppHome::resized()
	{

	}

	void AppHome::mouseUp(const MouseEvent& event)
	{
		auto a = event.eventComponent->getComponentID();
		if (a != "opt")
		{
			//AppOptions::GetOptionsInstance()->showOptions(false);
//			IgniteControlOptions::GetAppOptInstance()->changeoptionBtnStatus(false);
		}

	}
};
