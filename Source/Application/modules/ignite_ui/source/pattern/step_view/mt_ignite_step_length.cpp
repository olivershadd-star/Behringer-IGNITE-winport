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

#include "Common/Modules/IDevice.h"

extern std::unique_ptr<IDevice> _PUiVirtualEngine;

namespace ui
{
	PatternBarLengthCtl::PatternBarLengthCtl()
	{
		lengthTitle.makeVisible(this);
		lengthTitle.setJustificationType(juce::Justification::centred);

		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		closeBtn.setBounds(548, 30, 30, 20);
		closeBtn.toFront(true);

		addAndMakeVisible(ctlHold);
		ctlHold.addListener(this);
		ctlHold.setToggleState(false, sendNotification);
		ctlHold.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		ctlHold.setToggleable(true);
		ctlHold.sethoverImages("btn-hold-default-hover.png", "btn-hold-active-hover.png", "");

		addAndMakeVisible(ctlStep);
		ctlStep.addListener(this);
		ctlStep.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		ctlStep.setToggleable(true);
		ctlStep.setToggleState(true, dontSendNotification);
		ctlStep.sethoverImages("btn-step-default-hover.png", "btn-step-active-hover.png", "");

		addAndMakeVisible(stepLabel);
		stepLabel.setJustificationType(juce::Justification::centred);

		stepSlider.makeVisibleAndAddListner(this);
		stepSlider.setRange(minStepLength, maxStepLength, stepLengthStepSize);
		stepSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customBlack));
		stepSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customBlue15));
		stepSlider.setColour(juce::Slider::textBoxOutlineColourId, ui::Theme::Instance().getColour(transparentBlack));
		stepSlider.setLookAndFeel(CustomSliderLookandFeel::getLnf());

		stepIncButton.makeVisibleAndAddListner(this);
		stepIncButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		stepIncButton.setDisableImage("textbox-slider-plus-btn-disabled.png");
		stepIncButton.sethoverImages("textbox-slider-plus-btn-default-hover.png", "", "");

		stepDecButton.makeVisibleAndAddListner(this);
		stepDecButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		stepDecButton.setDisableImage("textbox-slider-minus-btn-disabled.png");
		stepDecButton.sethoverImages("textbox-slider-minus-btn-default-hover.png", "", "");

		addAndMakeVisible(tickLabel);
		tickLabel.setJustificationType(juce::Justification::centred);

		tickSlider.makeVisibleAndAddListner(this);
		tickSlider.setRange(minTickLength, maxTickLength, tickLengthStepSize);
		tickSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customBlack));
		tickSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customBlue15));
		tickSlider.setColour(juce::Slider::textBoxOutlineColourId, ui::Theme::Instance().getColour(transparentBlack));
		tickSlider.setLookAndFeel(CustomSliderLookandFeel::getLnf());

		tickIncButton.makeVisibleAndAddListner(this);
		tickIncButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		tickIncButton.setDisableImage("textbox-slider-plus-btn-disabled.png");
		tickIncButton.sethoverImages("textbox-slider-plus-btn-default-hover.png", "", "");

		tickDecButton.makeVisibleAndAddListner(this);
		tickDecButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		tickDecButton.setDisableImage("textbox-slider-minus-btn-disabled.png");
		tickDecButton.sethoverImages("textbox-slider-minus-btn-default-hover.png", "", "");

		setSize(604, 415);
	}

	PatternBarLengthCtl::~PatternBarLengthCtl()
	{
	}

	void PatternBarLengthCtl::paint(juce::Graphics& g)
	{
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-2.png"));
		g.drawImage(defaultImage, juce::Rectangle <float>{ (float)0, (float)0, 604, 478 }, RectanglePlacement::centred);
		g.setColour(ui::Theme::Instance().getColour(customGrey5));
		g.drawHorizontalLine(78, 0, 604);
		g.drawHorizontalLine(156, 0, 604);
		//g.drawHorizontalLine(376, 0, 604);
	}

	void PatternBarLengthCtl::resized()
	{
		lengthTitle.setBounds(30, 10, 544, heightNumpadTitle);
		//ctlHold.setBounds(34, 87, 271, 60);
		//ctlStep.setBounds(308, 87, 271, 60);
		stepLabel.setBounds(30, 176, 544, 18);
		tickLabel.setBounds(30, 276, 544, 18);

		stepSlider.setBounds(85, 209, 436, 50);
		stepDecButton.setBounds(32, 209, 50, 50);
		stepIncButton.setBounds(522, 209, 50, 50);

		tickSlider.setBounds(85, 309, 436, 50);
		tickDecButton.setBounds(32, 309, 50, 50);
		tickIncButton.setBounds(522, 309, 50, 50);
	}

	void PatternBarLengthCtl::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &closeBtn)
		{
			isDialogOpen = false;

			if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
				dw->exitModalState(0);
			CommonUtils::SetUtilsVisiblity(false);
		}
		else if (buttonThatWasClicked == &ctlHold)
		{
			ctlStep.setToggleState(!ctlHold.getToggleState(), dontSendNotification);
			patternLenData.isHoldEnabled = ctlHold.getToggleState();
			if (ctlHold.getToggleState() == false)
			{
				stepLabel.setTextColour(ui::Theme::Instance().getColour(neutralWhite).withAlpha((float)0.8));
				tickLabel.setTextColour(ui::Theme::Instance().getColour(neutralWhite).withAlpha((float)0.8));

				stepSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customBlack));
				stepSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customBlue15));

				tickSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customBlack));
				tickSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customBlue15));

				stepSlider.setEnabled(true);
				stepIncButton.setEnabled(true);
				stepDecButton.setEnabled(true);
				tickSlider.setEnabled(true);
				tickIncButton.setEnabled(true);
				tickDecButton.setEnabled(true);
				patternLenData.steps = stepSliderValue;
			}
			else
			{
				patternLenData.steps = lengthHoldId;
				stepLabel.setTextColour(ui::Theme::Instance().getColour(customGrey6).withAlpha((float)0.8));
				tickLabel.setTextColour(ui::Theme::Instance().getColour(customGrey6).withAlpha((float)0.8));

				stepSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customGrey7));
				stepSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customGrey8).withAlpha((float)0.8));

				tickSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customGrey7));
				tickSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customGrey8).withAlpha((float)0.8));

				stepSlider.setEnabled(false);
				stepIncButton.setEnabled(false);
				stepDecButton.setEnabled(false);
				tickSlider.setEnabled(false);
				tickIncButton.setEnabled(false);
				tickDecButton.setEnabled(false);
			}
		}
		else if (buttonThatWasClicked == &ctlStep)
		{
			ctlHold.setToggleState(!ctlStep.getToggleState(), dontSendNotification);
			patternLenData.isHoldEnabled = ctlHold.getToggleState();

			if (ctlStep.getToggleState() == true)
			{
				stepLabel.setTextColour(ui::Theme::Instance().getColour(neutralWhite).withAlpha((float)0.8));
				tickLabel.setTextColour(ui::Theme::Instance().getColour(neutralWhite).withAlpha((float)0.8));

				stepSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customBlack));
				stepSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customBlue15));

				tickSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customBlack));
				tickSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customBlue15));

				stepSlider.setEnabled(true);
				stepIncButton.setEnabled(true);
				stepDecButton.setEnabled(true);
				tickSlider.setEnabled(true);
				tickIncButton.setEnabled(true);
				tickDecButton.setEnabled(true);
				patternLenData.steps = stepSliderValue;
			}
			else
			{
				patternLenData.steps = lengthHoldId;
				stepLabel.setTextColour(ui::Theme::Instance().getColour(customGrey6).withAlpha((float)0.8));
				tickLabel.setTextColour(ui::Theme::Instance().getColour(customGrey6).withAlpha((float)0.8));

				stepSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customGrey7));
				stepSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customGrey8).withAlpha((float)0.8));

				tickSlider.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customGrey7));
				tickSlider.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customGrey8).withAlpha((float)0.8));

				stepSlider.setEnabled(false);
				stepIncButton.setEnabled(false);
				stepDecButton.setEnabled(false);
				tickSlider.setEnabled(false);
				tickIncButton.setEnabled(false);
				tickDecButton.setEnabled(false);
			}
		}
		else if (buttonThatWasClicked == &stepIncButton)
		{
			stepIncButton.setToggleState(false, dontSendNotification);
			stepSlider.setValue(stepSliderValue + stepValue);
			patternLenData.steps = stepSliderValue;
		}
		else if (buttonThatWasClicked == &stepDecButton)
		{
			stepDecButton.setToggleState(false, dontSendNotification);
			stepSlider.setValue(stepSliderValue - stepValue);
			patternLenData.steps = stepSliderValue;
		}
		else if (buttonThatWasClicked == &tickIncButton)
		{
			tickIncButton.setToggleState(false, dontSendNotification);
			tickSlider.setValue(tickSliderValue + stepValue);
			patternLenData.ticks = tickSliderValue;
		}
		else if (buttonThatWasClicked == &tickDecButton)
		{
			tickDecButton.setToggleState(false, dontSendNotification);
			tickSlider.setValue(tickSliderValue - stepValue);
			patternLenData.ticks = tickSliderValue;
		}
	}

	void PatternBarLengthCtl::setSliderValue(int steps, int ticks)
	{
		stepSlider.setValue((double)steps);
		tickSlider.setValue((double)ticks);
	}

	void PatternBarLengthCtl::sliderValueChanged(juce::Slider* sliderThatWasMoved)
	{
		if (sliderThatWasMoved == &stepSlider)
		{
			stepSliderValue = (uint8_t)stepSlider.getValue();
			patternLenData.steps = stepSliderValue;
		}
		else if (sliderThatWasMoved == &tickSlider)
		{
			tickSliderValue = (uint8_t)tickSlider.getValue();
			patternLenData.ticks = tickSliderValue;

		}
	}

	void PatternBarLengthCtl::handleCommandMessage(int id)
	{
		if (id == 1)
			buttonClicked(&closeBtn);
		else if (id == 2)
		{
			CommonUtils::SetUtilsVisiblity(false);
			CommonUtils::close();
		}
	}

	bool PatternBarLengthCtl::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		bool setfocus = true;
		bool isHandled = false;
		FrountPannelRef = FrountPannel::GetFrountPannelInstance();

		if (param == (paramId_t)FrontPannelParam::paramKey_RETURN_NAV)
			postCommandMessage(1);
		else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
			postCommandMessage(2);
		else if (param == (paramId_t)FrontPannelParam::paramKey_TRACKROTARY6)
		{
			if (FrountPannelRef->getShiftKeyStatus())
			{
				ctlHold.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
				isHandled = true;
			}
		}
		else if (param == (paramId_t)FrontPannelParam::paramKey_PLUS_NAV)
		{
			if (FrountPannelRef->getShiftKeyStatus())
				stepIncButton.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			else
				tickIncButton.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);

			isHandled = true;
		}
		else if (param == (paramId_t)FrontPannelParam::paramKey_MINUS_NAV)
		{
			if (FrountPannelRef->getShiftKeyStatus())
				stepDecButton.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);
			else
				tickDecButton.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, keyValue);

			isHandled = true;
		}

		if (!isHandled)
		{
			if (keyFocusedItem == stepLengthViewItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				keyFocusedItem = stepLengthViewItemID::KEY_STEP_DEC;
			}
			else
			{
				pannelSendKey(false, param, keyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= stepLengthViewItemID::FOCUS_MAX ? (stepLengthViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= stepLengthViewItemID::NO_FOCUS ? (stepLengthViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
					break;
				}
			}
			if (setfocus)
			{
				pannelSendKey(true, param, keyValue);
			}
		}

		return true;
	}

	void PatternBarLengthCtl::pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue)
	{
		switch (stepLengthView[keyFocusedItem])
		{
		/*case KEY_HOLD:
			ctlHold.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case KEY_STEP:
			ctlStep.FPKeyHandler(isFocuse, param, keyValue);
			break;*/
		case KEY_STEP_DEC:
			if(stepDecButton.isEnabled())
				stepDecButton.FPKeyHandler(isFocuse, param, keyValue);
			else
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
					keyFocusedItem = stepLengthViewItemID::KEY_CANCEL;

				pannelSendKey(isFocuse, param, keyValue);
			}
			break;
		case KEY_STEP_INC:
			stepIncButton.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case KEY_TICK_DEC:
			tickDecButton.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case KEY_TIC_INC:
			if(tickIncButton.isEnabled())
				tickIncButton.FPKeyHandler(isFocuse, param, keyValue);
			else
			{
				/*if (param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT)
					keyFocusedItem = stepLengthViewItemID::KEY_STEP;*/

				pannelSendKey(isFocuse, param, keyValue);
			}
			break;
		default:
			break;
		}
	}
}
