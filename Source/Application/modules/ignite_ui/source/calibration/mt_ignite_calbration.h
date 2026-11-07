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

#define CV_CALIB_STEP_OFFSET 0.005f

namespace ui
{
	class AppDnp;
	class IgniteControlOptions;
	class CVControl;

	class IgniteCalibration :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
		IgniteCalibration();
		~IgniteCalibration() override;
		void enableControlButton(IgniteControlOptions::eKey key, bool state);
		void enableBtnCtl(bool state);
		void updateCalibDataFromEngine();
		void clearAllBtnState();
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool getCalibStatus() { return calibMode.getToggleState(); }
		void getAssets();

		static IgniteCalibration* GetAppCalibrationInstance()
		{
			static IgniteCalibration* GetAppCalibrationObj;
			if (NULL == GetAppCalibrationObj)
			{
				GetAppCalibrationObj = new IgniteCalibration();
			}

			return GetAppCalibrationObj;
		}

	private:
#define CV_GATE_MENU_VIEW 23
#define CV_GATE_OPT_VIEW 2
#define CV_GATE_ROW_ITEMS 3

		enum CvGateMenuViewItemID
		{
			NO_FOCUS = 0,
			CALLIB_MODE, // Row 1
			CV1,
			CV2,
			CV3,
			CV4,
			CV5,
			CV6,
			CV7,
			CV8,
			STEP1_1V, // Row 2
			STEP2_2V,
			STEP3_3V,
			STEP4_4V,
			STEP5_5V,
			STEP6_6V, // Row 3
			STEP7_7V,
			STEP8_8V,
			STEP9_9V,
			STEP10_10V,
			CVADJUST_MINUS, // Row 4
			CVADJUST_PLUS,
			RESET,
			FOCUS_MAX = RESET
		};

		enum CVGATECONFIG_FOCUS
		{
			CVGATE_CONFIG_DETAIL,
			CVGATE_CONFIG_OPTION,
		};

		enum CvGateOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OP_FOCUS_MAX = OPT_UNDO
		};

		uint8_t optionHandlerFocus = CVGATE_CONFIG_DETAIL;
		uint8_t CvGateoptionsView[CV_GATE_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO };
		uint8_t CvGateMenuView[CV_GATE_MENU_VIEW] = { NO_FOCUS, CALLIB_MODE, CV1, CV2, CV3, CV4, CV5, CV6, CV7, CV8, STEP1_1V, STEP2_2V, STEP3_3V, STEP4_4V, STEP5_5V, STEP6_6V, STEP7_7V, STEP8_8V, STEP9_9V, STEP10_10V, CVADJUST_MINUS, CVADJUST_PLUS, RESET };
		int keyFocusedItem = CvGateMenuViewItemID::NO_FOCUS;
		int optFocusedItem = OPT_UNDO;

		CommonImageButton calibMode{ "Calibration Mode: Off","toggle-calibration-off.png","toggle-calibration-on.png","toggle-calibration-off-hover.png" };
		CommonToggleButton cvGenState{ "START \n CV Genration" };
		CommonToggleButton prevStep{ "Prev Step" };
		CommonToggleButton nextStep{ "Next Step" };
		CommonLabel cvPort { "Port" };
		CommonToggleButton cvPort1{ "" };
		CommonToggleButton cvPort2{ "" };
		CommonToggleButton cvPort3{ "" };
		CommonToggleButton cvPort4{ "" };
		CommonToggleButton cvPort5{ "" };
		CommonToggleButton cvPort6{ "" };
		CommonToggleButton cvPort7{ "" };
		CommonToggleButton cvPort8{ "" };

		CommonLabel cvAdjust{ "CV ADJUSTMENT" };
		CommonToggleButton minusOffset{ " " };
		CommonToggleButton plusOffset{ " " };
		CommonToggleButton resetStep{ " " };
		CommonToggleButton step1{ "STEP 1 \n  Output Voltage : 1V" };
		CommonToggleButton step2{ "STEP 2 \n  Output Voltage : 2V" };
		CommonToggleButton step3{ "STEP 3 \n  Output Voltage : 3V" };
		CommonToggleButton step4{ "STEP 4 \n  Output Voltage : 4V" };
		CommonToggleButton step5{ "STEP 5 \n  Output Voltage : 5V" };
		CommonToggleButton step6{ "STEP 6 \n  Output Voltage : 6V" };
		CommonToggleButton step7{ "STEP 7 \n  Output Voltage : 7V" };
		CommonToggleButton step8{ "STEP 8 \n  Output Voltage : 8V" };
		CommonToggleButton step9{ "STEP 9 \n  Output Voltage : 9V" };
		CommonToggleButton step10{ "STEP 10 \n  Output Voltage : 10V" };

		Image cv1Default, cv2Default, cv3Default, cv4Default, cv5Default, cv6Default, cv7Default, cv8Default,
			cv1Active, cv2Active, cv3Active, cv4Active, cv5Active, cv6Active, cv7Active, cv8Active,
			cv1Disabled, cv2Disabled, cv3Disabled, cv4Disabled, cv5Disabled, cv6Disabled, cv7Disabled, cv8Disabled,
			cv1DefaultHover, cv2DefaultHover, cv3DefaultHover, cv4DefaultHover, cv5DefaultHover, cv6DefaultHover, cv7DefaultHover, cv8DefaultHover,
			cv1ActiveHover, cv2ActiveHover, cv3ActiveHover, cv4ActiveHover, cv5ActiveHover, cv6ActiveHover, cv7ActiveHover, cv8ActiveHover,
			bgContainerDefault, bgContainerDefaultHover, bgContainerActive, bgContainerActiveHover, bgContainerDisabled,
			cvPortContainer, cvMinusDefault, cvMinusDefaultHover, cvMinusActive, cvMinusActiveHover, cvMinusDisabled,
			cvPlusDefault, cvPlusDefaultHover, cvPlusActive, cvPlusActiveHover, cvPlusDisabled,
			calibResetDefault, calibResetDefaultHover, calibResetActive, calibResetActiveHover, calibResetDisabled;

		IgniteControlOptions* calibOptCtl = nullptr;
		CommonPopUp* popupPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;
		CVControl* cvCtlComp = nullptr;
		bool calibDataUpdated = false;
		int currentStep = 0;
		float newValue = 0.0f;
		int currentCvPort = 0;

		std::unordered_map <int, float> stepOffsetList{
			{0, 0.0f},
			{1, 0.0f},
			{2, 0.0f},
			{3, 0.0f},
			{4, 0.0f},
			{5, 0.0f},
			{6, 0.0f},
			{7, 0.0f},
			{8, 0.0f},
			{9, 0.0f},
			{10, 0.0f},
			{11, 0.0f},
			{12, 0.0f},
			{13, 0.0f},
			{14, 0.0f},
			{15, 0.0f},
			{16, 0.0f},
			{17, 0.0f},
			{18, 0.0f},
			{19, 0.0f},
			{20, 0.0f},
			{21, 0.0f},
			{22, 0.0f},
			{23, 0.0f},
			{24, 0.0f},
			{25, 0.0f},
			{26, 0.0f},
			{27, 0.0f},
			{28, 0.0f},
			{29, 0.0f},
			{30, 0.0f},
			{31, 0.0f},
			{32, 0.0f},
			{33, 0.0f},
			{34, 0.0f},
			{35, 0.0f},
			{36, 0.0f},
			{37, 0.0f},
			{38, 0.0f},
			{39, 0.0f},
			{40, 0.0f},
			{41, 0.0f},
			{42, 0.0f},
			{43, 0.0f},
			{44, 0.0f},
			{45, 0.0f},
			{46, 0.0f},
			{47, 0.0f},
			{48, 0.0f},
			{49, 0.0f},
			{50, 0.0f},
			{51, 0.0f},
			{52, 0.0f},
			{53, 0.0f},
			{54, 0.0f},
			{55, 0.0f},
			{56, 0.0f},
			{57, 0.0f},
			{58, 0.0f},
			{59, 0.0f},
			{60, 0.0f},
			{61, 0.0f},
			{62, 0.0f},
			{63, 0.0f},
			{64, 0.0f},
			{65, 0.0f},
			{66, 0.0f},
			{67, 0.0f},
			{68, 0.0f},
			{69, 0.0f},
			{70, 0.0f},
			{71, 0.0f},
			{72, 0.0f},
			{73, 0.0f},
			{74, 0.0f},
			{75, 0.0f},
			{76, 0.0f},
			{77, 0.0f},
			{78, 0.0f},
			{79, 0.0f},
		};

		void exitCallibrationView();

	SIGNALS:
		sig::Signal < int, float > dacVoltageChanged;
		sig::Signal < float > dacVoltageChangedForAll;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void saveCalibSettings(int8_t SaveLocation);
		void clearBtnToggleState(int btn);
		void showInfoText(bool state, float voltage);
		void sendCalibDataToEngine(int step, float voltage);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCalibration)
	};
};
