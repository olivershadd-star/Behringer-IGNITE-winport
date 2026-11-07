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

	////////////////////////////////////////////////
	//   Class: Ignite Calibration
	////////////////////////////////////////////////
	IgniteCalibration::IgniteCalibration()
	{
		addAndMakeVisible(calibMode);
		calibMode.addListener(this);
		calibMode.setToggleable(true);
		calibMode.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		calibMode.sethoverImages("toggle-calibration-off-hover.png", "toggle-calibration-on-hover.png", "toggle-calibration-on-hover.png");

		cvPort1.makeVisibleAddListnerAndAddRadioGroup(this, 3456);
		cvPort2.makeVisibleAddListnerAndAddRadioGroup(this, 3456);
		cvPort3.makeVisibleAddListnerAndAddRadioGroup(this, 3456);
		cvPort4.makeVisibleAddListnerAndAddRadioGroup(this, 3456);
		cvPort5.makeVisibleAddListnerAndAddRadioGroup(this, 3456);
		cvPort6.makeVisibleAddListnerAndAddRadioGroup(this, 3456);
		cvPort7.makeVisibleAddListnerAndAddRadioGroup(this, 3456);
		cvPort8.makeVisibleAddListnerAndAddRadioGroup(this, 3456);

		addAndMakeVisible(cvPort);
		cvPort.setFont(18.0f);
		cvPort.setTextColour(ui::Theme::Instance().getColour(neutralWhite));
		cvPort.setInterceptsMouseClicks(false, false);
		cvPort.setJustificationType(juce::Justification::centredLeft);

		addAndMakeVisible(cvAdjust);
		cvAdjust.setFont(18.0f);
		cvAdjust.setTextColour(ui::Theme::Instance().getColour(neutralWhite));
		cvAdjust.setInterceptsMouseClicks(false, false);

		addAndMakeVisible(step1);
		step1.addListener(this);
		addAndMakeVisible(step2);
		step2.addListener(this);
		addAndMakeVisible(step3);
		step3.addListener(this);
		addAndMakeVisible(step4);
		step4.addListener(this);
		addAndMakeVisible(step5);
		step5.addListener(this);
		addAndMakeVisible(step6);
		step6.addListener(this);
		addAndMakeVisible(step7);
		step7.addListener(this);
		addAndMakeVisible(step8);
		step8.addListener(this);
		addAndMakeVisible(step9);
		step9.addListener(this);
		addAndMakeVisible(step10);
		step10.addListener(this);

		addAndMakeVisible(minusOffset);
		minusOffset.addListener(this);
		addAndMakeVisible(plusOffset);
		plusOffset.addListener(this);
		addAndMakeVisible(resetStep);
		resetStep.addListener(this);

		calibOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(calibOptCtl);
		calibOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		calibOptCtl->addOptCtlListener(this);
		popupPtr = CommonPopUp::getCommonPopupInstance();
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();

		cvPort1.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort2.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort3.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort4.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort5.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort6.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort7.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cvPort8.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		step1.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step2.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step3.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step4.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step5.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step6.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step7.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step8.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step9.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		step10.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		minusOffset.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		plusOffset.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		resetStep.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		enableBtnCtl(false);
		getAssets();
	}

	IgniteCalibration::~IgniteCalibration()
	{
	}

	void IgniteCalibration::enableControlButton(IgniteControlOptions::eKey key, bool state)
	{
		calibOptCtl->enableKey(key, state);
	}

	void IgniteCalibration::saveCalibSettings(int8_t SaveLocation)
	{
		calibOptCtl->enableKey(IgniteControlOptions::SAVE, false);
		calibDataUpdated = false;
	}

	void IgniteCalibration::getAssets()
	{
		bgContainerDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-bg-container-196x90-default.png"));
		bgContainerDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-bg-container-196x90-default-hover.png"));
		bgContainerActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-bg-container-196x90-active.png"));
		bgContainerActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-bg-container-196x90-active-hover.png"));
		bgContainerDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-bg-container-196x90-disabled.png"));
		cvPortContainer = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvaport-container.png"));

		cv1Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection1-default.png"));
		cv1DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection1-default-hover.png"));
		cv1Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection1-active.png"));
		cv1ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection1-active-hover.png"));
		cv1Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection1-disabled.png"));

		cv2Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection2-default.png"));
		cv2DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection2-default-hover.png"));
		cv2Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection2-active.png"));
		cv2ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection2-active-hover.png"));
		cv2Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection2-disabled.png"));

		cv3Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection3-default.png"));
		cv3DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection3-default-hover.png"));
		cv3Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection3-active.png"));
		cv3ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection3-active-hover.png"));
		cv3Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection3-disabled.png"));

		cv4Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection4-default.png"));
		cv4DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection4-default-hover.png"));
		cv4Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection4-active.png"));
		cv4ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection4-active-hover.png"));
		cv4Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection4-disabled.png"));

		cv5Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection5-default.png"));
		cv5DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection5-default-hover.png"));
		cv5Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection5-active.png"));
		cv5ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection5-active-hover.png"));
		cv5Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection5-disabled.png"));

		cv6Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection6-default.png"));
		cv6DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection6-default-hover.png"));
		cv6Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection6-active.png"));
		cv6ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection6-active-hover.png"));
		cv6Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection6-disabled.png"));

		cv7Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection7-default.png"));
		cv7DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection7-default-hover.png"));
		cv7Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection7-active.png"));
		cv7ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection7-active-hover.png"));
		cv7Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection7-disabled.png"));

		cv8Default = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection8-default.png"));
		cv8DefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection8-default-hover.png"));
		cv8Active = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection8-active.png"));
		cv8ActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection8-active-hover.png"));
		cv8Disabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cv-port-selection8-disabled.png"));

		cvMinusDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-minus-default.png"));
		cvMinusDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-minus-default-hover.png"));
		cvMinusActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-minus-active.png"));
		cvMinusActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-minus-active-hover.png"));
		cvMinusDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-minus-disabled.png"));

		cvPlusDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-plus-default.png"));
		cvPlusDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-plus-default-hover.png"));
		cvPlusActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-plus-active.png"));
		cvPlusActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-plus-active-hover.png"));
		cvPlusDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cvadjust-plus-disabled.png"));

		calibResetDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-reset-default.png"));
		calibResetDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-reset-default-hover.png"));
		calibResetActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-reset-active.png"));
		calibResetActiveHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-reset-active-hover.png"));
		calibResetDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("calib-reset-disabled.png"));
	}

	void IgniteCalibration::paint(juce::Graphics& g)
	{
		Image DrawImage;

		g.setColour(ui::Theme::Instance().getColour(neutralBlack));
		g.fillAll();

		MenuMode::GetMenuModeInstance()->setHeader("CV & Gate Calibration");
		MenuMode::GetMenuModeInstance()->setJustification(Justification::centred);

		g.drawImage(cvPortContainer, ui::Rectangle<float>{10, 120, 1004, 74});

		DrawImage = (cvPort1.isEnabled()) ? (cvPort1.getToggleState() ? ((cvPort1.isMouseOver() || cvPort1.isFocused) ? cv1ActiveHover : cv1Active) : ((cvPort1.isMouseOver() || cvPort1.isFocused) ? cv1DefaultHover : cv1Default)) : cv1Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{75, 135, 110, 44});

		DrawImage = (cvPort2.isEnabled()) ? (cvPort2.getToggleState() ? ((cvPort2.isMouseOver() || cvPort2.isFocused) ? cv2ActiveHover : cv2Active) : ((cvPort2.isMouseOver() || cvPort2.isFocused) ? cv2DefaultHover : cv2Default)) : cv2Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{190, 135, 110, 44});

		DrawImage = (cvPort3.isEnabled()) ? (cvPort3.getToggleState() ? ((cvPort3.isMouseOver() || cvPort3.isFocused) ? cv3ActiveHover : cv3Active) : ((cvPort3.isMouseOver() || cvPort3.isFocused) ? cv3DefaultHover : cv3Default)) : cv3Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{305, 135, 110, 44});

		DrawImage = (cvPort4.isEnabled()) ? (cvPort4.getToggleState() ? ((cvPort4.isMouseOver() || cvPort4.isFocused) ? cv4ActiveHover : cv4Active) : ((cvPort4.isMouseOver() || cvPort4.isFocused) ? cv4DefaultHover : cv4Default)) : cv4Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{420, 135, 110, 44});

		DrawImage = (cvPort5.isEnabled()) ? (cvPort5.getToggleState() ? ((cvPort5.isMouseOver() || cvPort5.isFocused) ? cv5ActiveHover : cv5Active) : ((cvPort5.isMouseOver() || cvPort5.isFocused) ? cv5DefaultHover : cv5Default)) : cv5Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{535, 135, 110, 44});

		DrawImage = (cvPort6.isEnabled()) ? (cvPort6.getToggleState() ? ((cvPort6.isMouseOver() || cvPort6.isFocused) ? cv6ActiveHover : cv6Active) : ((cvPort6.isMouseOver() || cvPort6.isFocused) ? cv6DefaultHover : cv6Default)) : cv6Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{650, 135, 110, 44});

		DrawImage = (cvPort7.isEnabled()) ? (cvPort7.getToggleState() ? ((cvPort7.isMouseOver() || cvPort7.isFocused) ? cv7ActiveHover : cv7Active) : ((cvPort7.isMouseOver() || cvPort7.isFocused) ? cv7DefaultHover : cv7Default)) : cv7Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{765, 135, 110, 44});

		DrawImage = (cvPort8.isEnabled()) ? (cvPort8.getToggleState() ? ((cvPort8.isMouseOver() || cvPort8.isFocused) ? cv8ActiveHover : cv8Active) : ((cvPort8.isMouseOver() || cvPort8.isFocused) ? cv8DefaultHover : cv8Default)) : cv8Disabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{880, 135, 110, 44});

		DrawImage = (step1.isEnabled()) ? (step1.getToggleState() ? ((step1.isMouseOver() || step1.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step1.isMouseOver() || step1.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{10, 202, 196, 90});

		DrawImage = (step2.isEnabled()) ? (step2.getToggleState() ? ((step2.isMouseOver() || step2.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step2.isMouseOver() || step2.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{212, 202, 196, 90});

		DrawImage = (step3.isEnabled()) ? (step3.getToggleState() ? ((step3.isMouseOver() || step3.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step3.isMouseOver() || step3.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{414, 202, 196, 90});

		DrawImage = (step4.isEnabled()) ? (step4.getToggleState() ? ((step4.isMouseOver() || step4.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step4.isMouseOver() || step4.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{616, 202, 196, 90});

		DrawImage = (step5.isEnabled()) ? (step5.getToggleState() ? ((step5.isMouseOver() || step5.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step5.isMouseOver() || step5.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{818, 202, 196, 90});

		DrawImage = (step6.isEnabled()) ? (step6.getToggleState() ? ((step6.isMouseOver() || step6.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step6.isMouseOver() || step6.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{10, 300, 196, 90});

		DrawImage = (step7.isEnabled()) ? (step7.getToggleState() ? ((step7.isMouseOver() || step7.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step7.isMouseOver() || step7.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{212, 300, 196, 90});

		DrawImage = (step8.isEnabled()) ? (step8.getToggleState() ? ((step8.isMouseOver() || step8.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step8.isMouseOver() || step8.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{414, 300, 196, 90});

		DrawImage = (step9.isEnabled()) ? (step9.getToggleState() ? ((step9.isMouseOver() || step9.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step9.isMouseOver() || step9.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{616, 300, 196, 90});

		DrawImage = (step10.isEnabled()) ? (step10.getToggleState() ? ((step10.isMouseOver() || step10.isFocused) ? bgContainerActiveHover : bgContainerActive) : ((step10.isMouseOver() || step10.isFocused) ? bgContainerDefaultHover : bgContainerDefault)) : bgContainerDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{818, 300, 196, 90});

		g.drawImage(cvPortContainer, ui::Rectangle<float>{10, 398, 1004, 74});

		DrawImage = (minusOffset.isEnabled()) ? (minusOffset.getToggleState() ? ((minusOffset.isMouseOver() || minusOffset.isFocused) ? cvMinusActiveHover : cvMinusActive) : ((minusOffset.isMouseOver() || minusOffset.isFocused) ? cvMinusDefaultHover : cvMinusDefault)) : cvMinusDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{268, 413, 230, 44});

		DrawImage = (plusOffset.isEnabled()) ? (plusOffset.getToggleState() ? ((plusOffset.isMouseOver() || plusOffset.isFocused) ? cvPlusActiveHover : cvPlusActive) : ((plusOffset.isMouseOver() || plusOffset.isFocused) ? cvPlusDefaultHover : cvPlusDefault)) : cvPlusDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{508, 413, 230, 44});

		DrawImage = (resetStep.isEnabled()) ? (resetStep.getToggleState() ? ((resetStep.isMouseOver() || resetStep.isFocused) ? calibResetActiveHover : calibResetActive) : ((resetStep.isMouseOver() || resetStep.isFocused) ? calibResetDefaultHover : calibResetDefault)) : calibResetDisabled;
		g.drawImage(DrawImage, ui::Rectangle<float>{764, 398, 250, 74});
	}

	void IgniteCalibration::enableBtnCtl(bool state)
	{
		cvPort1.setEnabled(state);
		cvPort2.setEnabled(state);
		cvPort3.setEnabled(state);
		cvPort4.setEnabled(state);
		cvPort5.setEnabled(state);
		cvPort6.setEnabled(state);
		cvPort7.setEnabled(state);
		cvPort8.setEnabled(state);
		step1.setEnabled(state);
		step2.setEnabled(state);
		step3.setEnabled(state);
		step4.setEnabled(state);
		step5.setEnabled(state);
		step6.setEnabled(state);
		step7.setEnabled(state);
		step8.setEnabled(state);
		step9.setEnabled(state);
		step10.setEnabled(state);
		cvPort1.setToggleState(false, dontSendNotification);
		cvPort2.setToggleState(false, dontSendNotification);
		cvPort3.setToggleState(false, dontSendNotification);
		cvPort4.setToggleState(false, dontSendNotification);
		cvPort5.setToggleState(false, dontSendNotification);
		cvPort6.setToggleState(false, dontSendNotification);
		cvPort7.setToggleState(false, dontSendNotification);
		cvPort8.setToggleState(false, dontSendNotification);
		step1.setToggleState(false, dontSendNotification);
		step2.setToggleState(false, dontSendNotification);
		step3.setToggleState(false, dontSendNotification);
		step4.setToggleState(false, dontSendNotification);
		step5.setToggleState(false, dontSendNotification);
		step6.setToggleState(false, dontSendNotification);
		step7.setToggleState(false, dontSendNotification);
		step8.setToggleState(false, dontSendNotification);
		step9.setToggleState(false, dontSendNotification);
		step10.setToggleState(false, dontSendNotification);
		cvAdjust.setEnabled(state);
		cvPort.setEnabled(state);
		minusOffset.setEnabled(false);
		plusOffset.setEnabled(false);
		resetStep.setEnabled(false);
		cvAdjust.setAlpha(0.5f);
		if (state)
		{
			cvPort.setAlpha(1.0f);
			cvPort1.setToggleState(true, dontSendNotification);
			currentCvPort = 0;
		}
		else
			cvPort.setAlpha(0.5f);
	}

	void IgniteCalibration::clearAllBtnState()
	{
		enableBtnCtl(false);
		calibMode.setToggleState(false, dontSendNotification);
		dacVoltageChanged.emit(0, 0.0f);
	}

	void IgniteCalibration::clearBtnToggleState(int btn)
	{
		if (btn != 1)
			step1.setToggleState(false, dontSendNotification);
		if (btn != 2)
			step2.setToggleState(false, dontSendNotification);
		if (btn != 3)
			step3.setToggleState(false, dontSendNotification);
		if (btn != 4)
			step4.setToggleState(false, dontSendNotification);
		if (btn != 5)
			step5.setToggleState(false, dontSendNotification);
		if (btn != 6)
			step6.setToggleState(false, dontSendNotification);
		if (btn != 7)
			step7.setToggleState(false, dontSendNotification);
		if (btn != 8)
			step8.setToggleState(false, dontSendNotification);
		if (btn != 9)
			step9.setToggleState(false, dontSendNotification);
		if (btn != 10)
			step10.setToggleState(false, dontSendNotification);

		if (step1.getToggleState() || step2.getToggleState() || step3.getToggleState() || step4.getToggleState() || step5.getToggleState() ||
			step6.getToggleState() || step7.getToggleState() || step8.getToggleState() || step9.getToggleState() || step10.getToggleState())
		{
			minusOffset.setEnabled(true);
			plusOffset.setEnabled(true);
			resetStep.setEnabled(true);
			cvAdjust.setAlpha(1.0f);
		}
		else
		{
			minusOffset.setEnabled(false);
			plusOffset.setEnabled(false);
			resetStep.setEnabled(false);
			cvAdjust.setAlpha(0.5f);
		}

		if (btn == -1)
		{
			step1.setToggleState(false, dontSendNotification);
			step2.setToggleState(false, dontSendNotification);
			step3.setToggleState(false, dontSendNotification);
			step4.setToggleState(false, dontSendNotification);
			step5.setToggleState(false, dontSendNotification);
			step6.setToggleState(false, dontSendNotification);
			step7.setToggleState(false, dontSendNotification);
			step8.setToggleState(false, dontSendNotification);
			step9.setToggleState(false, dontSendNotification);
			step10.setToggleState(false, dontSendNotification);
			dacVoltageChangedForAll.emit(0.0f);
		}
	}

	void IgniteCalibration::updateCalibDataFromEngine()
	{
		std::vector<IgniteParamList> calibParamsList;
		IgniteParamList params;

		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramFetchCalibData, true, true);

		for (auto i = 0; i < 8; i++)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramActiveCVCalibPort, i, true);

			calibParamsList.clear();
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset1;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset2;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset3;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset4;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset5;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset6;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset7;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset8;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset9;
			calibParamsList.push_back(params);
			params.param = (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset10;
			calibParamsList.push_back(params);

			calibParamsList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, calibParamsList);
			stepOffsetList[0 + (i * 10)] = calibParamsList[0].MsgValue.get< float >();
			stepOffsetList[1 + (i * 10)] = calibParamsList[1].MsgValue.get< float >();
			stepOffsetList[2 + (i * 10)] = calibParamsList[2].MsgValue.get< float >();
			stepOffsetList[3 + (i * 10)] = calibParamsList[3].MsgValue.get< float >();
			stepOffsetList[4 + (i * 10)] = calibParamsList[4].MsgValue.get< float >();
			stepOffsetList[5 + (i * 10)] = calibParamsList[5].MsgValue.get< float >();
			stepOffsetList[6 + (i * 10)] = calibParamsList[6].MsgValue.get< float >();
			stepOffsetList[7 + (i * 10)] = calibParamsList[7].MsgValue.get< float >();
			stepOffsetList[8 + (i * 10)] = calibParamsList[8].MsgValue.get< float >();
			stepOffsetList[9 + (i * 10)] = calibParamsList[9].MsgValue.get< float >();
		}
	}

	void IgniteCalibration::sendCalibDataToEngine(int step, float voltage)
	{
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramActiveCVCalibPort, currentCvPort, true);

		switch ((CalibStep)step)
		{
		case CalibStep::CV_CALIB_STEP1:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset1, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP2:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset2, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP3:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset3, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP4:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset4, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP5:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset5, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP6:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset6, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP7:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset7, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP8:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset8, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP9:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset9, voltage, true);
			break;
		case CalibStep::CV_CALIB_STEP10:
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramCVCalibOffset10, voltage, true);
			break;
		}
	}

	void IgniteCalibration::showInfoText(bool state, float voltage)
	{
		if (state)
			_pInfoWindow->setTextandShow(String(voltage) + "V enabled");
		else
			_pInfoWindow->setTextandShow(String(voltage) + "V disabled");
	}

	void IgniteCalibration::resized()
	{
		calibMode.setBounds(10, 63, 1004, 50);
		cvPort.setBounds(20, 142, 90, 30);
		cvPort1.setBounds(75, 135, 110, 44);
		cvPort2.setBounds(190, 135, 110, 44);
		cvPort3.setBounds(305, 135, 110, 44);
		cvPort4.setBounds(420, 135, 110, 44);
		cvPort5.setBounds(535, 135, 110, 44);
		cvPort6.setBounds(650, 135, 110, 44);
		cvPort7.setBounds(765, 135, 110, 44);
		cvPort8.setBounds(880, 135, 110, 44);

		step1.setBounds(10, 202, 196, 90);
		step2.setBounds(212, 202, 196, 90);
		step3.setBounds(414, 202, 196, 90);
		step4.setBounds(616, 202, 196, 90);
		step5.setBounds(818, 202, 196, 90);
		step6.setBounds(10, 300, 196, 90);
		step7.setBounds(212, 300, 196, 90);
		step8.setBounds(414, 300, 196, 90);
		step9.setBounds(616, 300, 196, 90);
		step10.setBounds(818, 300, 196, 90);
		cvAdjust.setBounds(30, 425, 117, 19);
		minusOffset.setBounds(268, 413, 230, 44);
		plusOffset.setBounds(508, 413, 230, 44);
		resetStep.setBounds(764, 398, 250, 74);
	}

	void IgniteCalibration::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &calibMode)
		{
			enableBtnCtl(calibMode.getToggleState());
			if (!calibMode.getToggleState())
				dacVoltageChanged.emit(0, 0.0f);
		}
		else if (buttonThatWasClicked == &cvPort1)
		{
			currentCvPort = 0;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &cvPort2)
		{
			currentCvPort = 1;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &cvPort3)
		{
			currentCvPort = 2;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &cvPort4)
		{
			currentCvPort = 3;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &cvPort5)
		{
			currentCvPort = 4;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &cvPort6)
		{
			currentCvPort = 5;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &cvPort7)
		{
			currentCvPort = 6;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &cvPort8)
		{
			currentCvPort = 7;
			clearBtnToggleState(-1);
		}
		else if (buttonThatWasClicked == &step1)
		{
			currentStep = 0;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step1.getToggleState() ? newValue : 0);
			clearBtnToggleState(1);
			showInfoText(step1.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step2)
		{
			currentStep = 1;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step2.getToggleState() ? newValue : 0);
			clearBtnToggleState(2);
			showInfoText(step2.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step3)
		{
			currentStep = 2;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step3.getToggleState() ? newValue : 0);
			clearBtnToggleState(3);
			showInfoText(step3.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step4)
		{
			currentStep = 3;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step4.getToggleState() ? newValue : 0);
			clearBtnToggleState(4);
			showInfoText(step4.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step5)
		{
			currentStep = 4;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step5.getToggleState() ? newValue : 0);
			clearBtnToggleState(5);
			showInfoText(step5.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step6)
		{
			currentStep = 5;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step6.getToggleState() ? newValue : 0);
			clearBtnToggleState(6);
			showInfoText(step6.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step7)
		{
			currentStep = 6;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step7.getToggleState() ? newValue : 0);
			clearBtnToggleState(7);
			showInfoText(step7.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step8)
		{
			currentStep = 7;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step8.getToggleState() ? newValue : 0);
			clearBtnToggleState(8);
			showInfoText(step8.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step9)
		{
			currentStep = 8;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step9.getToggleState() ? newValue : 0);
			clearBtnToggleState(9);
			showInfoText(step9.getToggleState(), newValue);
		}
		else if (buttonThatWasClicked == &step10)
		{
			currentStep = 9;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			dacVoltageChanged.emit(currentCvPort, step10.getToggleState() ? newValue : 0);
			clearBtnToggleState(10);
			showInfoText(step10.getToggleState(), newValue);
		}

		else if (buttonThatWasClicked == &minusOffset)
		{
			stepOffsetList.at((currentCvPort + 0) * 10 + currentStep) -= CV_CALIB_STEP_OFFSET;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			std::cout << "New Value = " << newValue << std::endl;
			dacVoltageChanged.emit(currentCvPort, newValue);
			sendCalibDataToEngine(currentStep, newValue);
			minusOffset.setToggleState(false, dontSendNotification);
			_pInfoWindow->setTextandShow(String(-5) + "mv offset");
		}
		else if (buttonThatWasClicked == &plusOffset)
		{
			stepOffsetList.at((currentCvPort + 0) * 10 + currentStep) += CV_CALIB_STEP_OFFSET;
			newValue = (currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep));
			std::cout << "New Value = " << newValue << std::endl;
			dacVoltageChanged.emit(currentCvPort, newValue);
			sendCalibDataToEngine(currentStep, newValue);
			plusOffset.setToggleState(false, dontSendNotification);
			_pInfoWindow->setTextandShow("+" + String(5) + "mv offset");
		}
		else if (buttonThatWasClicked == &resetStep)
		{
			stepOffsetList.at((currentCvPort + 0) * 10 + currentStep) = 0.0;
			newValue = currentStep + 1 + stepOffsetList.at((currentCvPort + 0) * 10 + currentStep);
			dacVoltageChanged.emit(currentCvPort, newValue);
			std::cout << "New Value = " << newValue << std::endl;
			resetStep.setToggleState(false, dontSendNotification);
			sendCalibDataToEngine(currentStep, 0.0);
			_pInfoWindow->setTextandShow("Reset to default value for current step");
		}

		enableControlButton(IgniteControlOptions::SAVE, true);
		calibDataUpdated = true;
	}

	void IgniteCalibration::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (this->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("CV & Gate Calibration", 604, 290);
					auto saveMsg = "Save New Calibration Values ?";
					popupPtr->setInfoText(String(saveMsg));
					popupPtr->addImageButton("Reset to Factory Default", "btn-factory-default-174x44-active.png", "btn-factory-default-174x44-active-hover.png", 2);
					popupPtr->addImageButton("Cancel", "btn-cancel-174x44-default.png", "btn-cancel-174x44-active-hover.png", 0);
					popupPtr->addImageButton("Save", "btn-save-174x44-default.png", "btn-save-174x44-active-hover.png", 1);
					popupPtr->popupType = POPUP_CHANGEWARNING;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
						{
							if (r == 1)
							{
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleCvioCnfg, (paramId_t)SettingsCvioCnfgParam::paramSaveCvioCalibSetting, 0);
								enableControlButton(IgniteControlOptions::SAVE, false);
								calibDataUpdated = false;
							}
							else if (r == 2)
							{

							}

							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);
						};
				}
			}
		}
	}

	void IgniteCalibration::exitCallibrationView()
	{
		if (getCalibStatus())
			_pInfoWindow->setTextandShow("Calibration Mode Disabled");
		clearAllBtnState();
		setVisible(false);
		IgniteSettings::GetAppSettingsInstance()->enableMiscCompVisibility();
	}

	bool IgniteCalibration::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
		{
			pannelSendKey(false, param, KeyValue);
			if (optionHandlerFocus == CVGATE_CONFIG_DETAIL)
			{
				optionHandlerFocus = CVGATE_CONFIG_OPTION;
			}
			else
			{
				optionHandlerFocus = CVGATE_CONFIG_DETAIL;
			}
			pannelSendKey(true, param, KeyValue);
			return true;
		}

		if (optionHandlerFocus == CVGATE_CONFIG_DETAIL)
		{
			if (keyFocusedItem == CvGateMenuViewItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				keyFocusedItem = CvGateMenuViewItemID::CALLIB_MODE;

				if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
				{
					exitCallibrationView();
					return true;
				}
			}
			else
			{
				pannelSendKey(false, param, KeyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= CvGateMenuViewItemID::FOCUS_MAX ? (CvGateMenuViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= CvGateMenuViewItemID::NO_FOCUS ? (CvGateMenuViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					exitCallibrationView();
					break;
				case FrontPannelParam::paramRot_ROW:
					if (KeyValue == ROTARY_DIRECTION_RIGHT)
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						keyFocusedItem = (keyFocusedItem + CV_GATE_ROW_ITEMS >= CvGateMenuViewItemID::FOCUS_MAX ? ((keyFocusedItem + CV_GATE_ROW_ITEMS) == (CvGateMenuViewItemID::FOCUS_MAX) ? (CvGateMenuViewItemID::FOCUS_MAX) : keyFocusedItem) : keyFocusedItem + CV_GATE_ROW_ITEMS);
						pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						keyFocusedItem = (keyFocusedItem - CV_GATE_ROW_ITEMS <= CvGateMenuViewItemID::NO_FOCUS ? (keyFocusedItem) : keyFocusedItem - CV_GATE_ROW_ITEMS);
						pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
					}
					repaint();
					setfocus = false;
					break;
				}
			}
		}
		else
		{
			pannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				optFocusedItem = (optFocusedItem + 1 >= CvGateOptionsViewItemID::OP_FOCUS_MAX ? (CvGateOptionsViewItemID::OP_FOCUS_MAX) : optFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				optFocusedItem = (optFocusedItem - 1 <= CvGateOptionsViewItemID::OP_NO_FOCUS ? (CvGateOptionsViewItemID::OP_NO_FOCUS + 1) : optFocusedItem - 1);
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

	void IgniteCalibration::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		bool state = false;

		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (optionHandlerFocus == CVGATE_CONFIG_DETAIL)
		{
			switch (CvGateMenuView[keyFocusedItem])
			{
			case CALLIB_MODE:
				calibMode.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV1:
				cvPort1.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV2:
				cvPort2.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV3:
				cvPort3.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV4:
				cvPort4.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV5:
				cvPort5.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV6:
				cvPort6.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV7:
				cvPort7.FPKeyHandler(isFocuse, param, 0);
				break;
			case CV8:
				cvPort8.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP1_1V:
				step1.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP2_2V:
				step2.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP3_3V:
				step3.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP4_4V:
				step4.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP5_5V:
				step5.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP6_6V:
				step6.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP7_7V:
				step7.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP8_8V:
				step8.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP9_9V:
				step9.FPKeyHandler(isFocuse, param, 0);
				break;
			case STEP10_10V:
				step10.FPKeyHandler(isFocuse, param, 0);
				break;
			case CVADJUST_MINUS:
				minusOffset.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case CVADJUST_PLUS:
				plusOffset.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case RESET:
				resetStep.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			default:
				break;
			}
			repaint();
		}
		else
		{
			switch (CvGateoptionsView[optFocusedItem])
			{
			case OPT_UNDO:
				state = calibOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			default:
				break;
			}

			if (state == false)
			{
				optFocusedItem++;
				if (optFocusedItem == OP_FOCUS_MAX)
					optFocusedItem = OPT_UNDO;
				pannelSendKey(isFocuse, param, KeyValue);
			}
		}
	}
};
