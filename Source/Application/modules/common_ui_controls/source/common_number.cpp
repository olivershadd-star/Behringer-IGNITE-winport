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
 //#include "../../ignite_ui/source/common/mt_ignite_cntropt.h"
namespace ui
{
	CommonNumPad::CommonNumPad(const String& Name, float min, float max, float defaultVal, float stepSize, bool isFloatSupported)
	{
		setValueBounds(min, max, defaultVal, isFloatSupported ? 0.1f : stepSize);
		setLookAndFeel(CommonLooknFeel::getLnf());
		isNumpadWithFloat = isFloatSupported;

		numPadValue.makeVisibleAndAddListner(this);
		numPadValue.setColour(juce::Slider::backgroundColourId, ui::Theme::Instance().getColour(customBlack));
		numPadValue.setColour(juce::Slider::trackColourId, ui::Theme::Instance().getColour(customBlue15));
		numPadValue.setColour(juce::Slider::textBoxOutlineColourId, ui::Theme::Instance().getColour(transparentBlack));
		numPadValue.setLookAndFeel(CustomSliderLookandFeel::getLnf());
		numPadValue.setComponentID("editSlider");

		num0.makeVisibleAndAddListner(this);
		num1.makeVisibleAndAddListner(this);
		num2.makeVisibleAndAddListner(this);
		num3.makeVisibleAndAddListner(this);
		num4.makeVisibleAndAddListner(this);
		num5.makeVisibleAndAddListner(this);
		num6.makeVisibleAndAddListner(this);
		num7.makeVisibleAndAddListner(this);
		num8.makeVisibleAndAddListner(this);
		num9.makeVisibleAndAddListner(this);
		numDelButton.makeVisibleAndAddListner(this);
		incButton.makeVisibleAndAddListner(this);
		decButton.makeVisibleAndAddListner(this);
		incSliderButton.makeVisibleAndAddListner(this);
		decSliderButton.makeVisibleAndAddListner(this);
		x2Button.makeVisibleAndAddListner(this);
		b2Button.makeVisibleAndAddListner(this);

		if (isNumpadWithFloat)
		{
			decimalButton.makeVisibleAndAddListner(this);
			decimalButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		}
		numApplyButton.makeVisibleAndAddListner(this);
		numCancelButton.makeVisibleAndAddListner(this);
		closeBtn.makeVisible(this);
		closeBtn.addListener(this);

		num1.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num2.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num3.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num4.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num5.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num6.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num7.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num8.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num9.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num0.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		numDelButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		incButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		decButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		incSliderButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		decSliderButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		x2Button.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		b2Button.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		numCancelButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		numApplyButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		decimalButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		numCancelButton.setBackgroundColour(ui::Theme::Instance().getColour(customRed3));
		numCancelButton.setColour(juce::TextEditor::focusedOutlineColourId, Theme::Instance().getColour(customRed5));
		numCancelButton.setOutlineColour(ui::Theme::Instance().getColour(customRed4));
		numApplyButton.setBackgroundColour(Theme::Instance().getColour(customOrange));
		numApplyButton.setOutlineColour(ui::Theme::Instance().getColour(customOrange5));
		numApplyButton.setColour(juce::TextEditor::focusedOutlineColourId, Theme::Instance().getColour(customOrange4));

		Title.makeVisible(this);
		Title.setText(Name, dontSendNotification);
		Title.setJustificationType(juce::Justification::centred);
		intermdiatelabel.makeVisible(this);
		intermdiatelabel.setJustificationType(juce::Justification::centred);

		ctrlRow.items.add(FlexItem(numCancelButton).withFlex(4).withMargin({ 0,5,0,0 }));
		ctrlRow.items.add(FlexItem(numApplyButton).withFlex(4).withMargin({ 0,0,0,5 }));
		this->setName(Name);
		setSize(layout::numpad.getWidth(), layout::numpad.getHeight());
		closeBtn.setBounds(548, 30, 30, 20);
		closeBtn.toFront(true);
		addMouseListener(this, true);
	}

	void CommonNumPad::setRange(float min, float max, float stepSize)
	{
		minValue = min;
		maxValue = max;
		stepValue = stepSize;

		if (minValue > 0)
			sign.setEnabled(false);

		numPadValue.setRange((float)minValue, (float)maxValue, (float)stepValue);
		numPadValue.setNumDecimalPlacesToDisplay(0);
	}

	void CommonNumPad::setValueBounds(float min, float max, float defaultVal, float stepSize)
	{
		setRange(min, max, stepSize);
		setValue(defaultVal);
	}

	void CommonNumPad::setValue(float Value)
	{
		lastEnteredValue = validateValue(Value);
		refreshDisplay(lastEnteredValue);
	};

	void CommonNumPad::setTitleText(String name)
	{
		Title.setText(name, dontSendNotification);
	};

	float CommonNumPad::validateValue(float value)
	{
		return jmin<float>(jmax<float>(value, minValue), maxValue);
	}

	void CommonNumPad::refreshDisplay(float value)
	{
		intermidentValue = validateValue(value);
		numPadValue.setValue((double)intermidentValue, dontSendNotification);

		if (isNumpadWithFloat)
		{
			if (onPlayTimeFloatValueChanged)
				onPlayTimeFloatValueChanged(intermidentValue);
		}
		else
		{
			if (onPlayTimeValueChanged)
				onPlayTimeValueChanged((int)intermidentValue);
		}
	}

	void CommonNumPad::buttonClicked(juce::Button* button)
	{
		// Check if APPLY or CANCEL button pressed...
		if (button == &numApplyButton || button == &numCancelButton || button == &closeBtn)
		{
			if (isAnyInput && (button == &numApplyButton))
			{
				lastEnteredValue = intermidentValue;

				if (middlelabelValue != 0)
				{
					refreshDisplay(middlelabelValue);
					numPadValue.setInterceptsMouseClicks(true, true);
					intermdiatelabel.setVisible(false);
					lastEnteredValue = static_cast<float>(numPadValue.getValue());
					if (numPadValue.getValue() != middlelabelValue)
					{
						floatingdis = false;
						isdotpreset = false;
					}
					middlelabelValue = 0;
					intermdiatelabel.setText("", dontSendNotification);
					
				}
				if (isNumpadWithFloat)
				{
					if (onFloatValueChanged)
						onFloatValueChanged(lastEnteredValue);
				}
				else
				{
					if (onValueChanged)
						onValueChanged((int)lastEnteredValue);
				}
			}
			ui::CommonUtils::close();

			// Exit this dialog box.
			intermidentValue = lastEnteredValue;
			if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
			{
				(button == &numApplyButton) ? dw->exitModalState(IGNITE_DIALOG_APPLY) : dw->exitModalState(IGNITE_DIALOG_CANCEL);
				CommonUtils::SetUtilsVisiblity(false);

			}
		}
		else
			isAnyInput = true;

		// Process other buttons...
		if (button == &num1)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 1);
		else if (button == &num2)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 2);
		else if (button == &num3)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 3);
		else if (button == &num4)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 4);
		else if (button == &num5)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 5);
		else if (button == &num6)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 6);
		else if (button == &num7)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 7);
		else if (button == &num8)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 8);
		else if (button == &num9)
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 9);
		else if (button == &num0)
		{
			handleArithmetic(isdecimalPressed, isPlusPressed, isMinusPressed, 0);
		}
		else if (button == &sign)
		{
			intermidentValue *= -1;
			isdecimalPressed = false;
			isMinusPressed = false;
			isPlusPressed = false;
		}
		else if (button == &numDelButton)
		{
			intermidentValue /= 10;
			isDeletePressed = true;
			isdecimalPressed = false;
			isMinusPressed = false;
			isPlusPressed = false;
			handleArithmetic(false, false, false, -1);
		}
		else if (button == &incButton)
		{
			isPlusPressed = true;
		}
		else if (button == &decButton)
		{
			isMinusPressed = true;
		}
		else if (button == &incSliderButton)
		{
			incSliderButton.setToggleState(false, dontSendNotification);
			intermidentValue += stepValue;
			isdecimalPressed = false;
			isMinusPressed = false;
			if(!middlelabelValue)
				refreshDisplay(intermidentValue);
			else
				handleArithmetic(false, false, true, -1);
		}
		else if (button == &decSliderButton)
		{
			decSliderButton.setToggleState(false, dontSendNotification);
			intermidentValue -= stepValue;
			isdecimalPressed = false;
			isMinusPressed = false;
			isPlusPressed = false;
			if (!middlelabelValue)
				refreshDisplay(intermidentValue);
			else
				handleArithmetic(false, true, false, -1);
		}
		else if (button == &b2Button)
		{
			intermidentValue /= 2;
			isdecimalPressed = false;
			isMinusPressed = false;
			isPlusPressed = false;
		}
		else if (button == &x2Button)
		{
			intermidentValue *= 2;
			isdecimalPressed = false;
			isMinusPressed = false;
			isPlusPressed = false;
		}
		else if (button == &decimalButton)
		{
			isdecimalPressed = true;
			handleArithmetic(false, false, false, -1);
		}
	}

	void CommonNumPad::handleArithmetic(bool isDecimal, bool isPlus, bool isMinus, int value)
	{
		float mvalue = middlelabelValue;
		
		if (numPadValue.isVisible())
		{
			numPadValue.setVisible(false);
			intermdiatelabel.setVisible(true);
		}

		if (isDecimal)
		{
			if (isPlus)
				mvalue += (float)(value * 0.1f);
			else if (isMinus)
				mvalue -= (float)(value * 0.1f);
		}
		else if (isPlus)
		{
			mvalue += value;
		}
		else if (isMinus)
		{
			mvalue -= value;
		}
		else if (isdecimalPressed)
		{
			if (!isdotpreset) {
				intermdiatelabel.setText(String(middlelabelValue) + '.', dontSendNotification);
				floatingdis = true;
			}
			isdotpreset = true;
			isdecimalPressed = false;
			return;
		}
		else if (isDeletePressed)
		{
			if (floatingdis)
			{
				mvalue = (middlelabelValue - ((float)middlelabelValue - (int)middlelabelValue));
				intermdiatelabel.setText(String(mvalue) + '.', dontSendNotification);
				floatingdis = false;
				middlelabelValue = mvalue;
				return;
			}
			else if (isdotpreset)
			{
				isdotpreset = false;
				intermdiatelabel.setText(String(mvalue) , dontSendNotification);
			}
			else
				mvalue = static_cast<float>((uint16) middlelabelValue / 10);
			isDeletePressed=false;
		}
		else
		{
			if (isdotpreset)
				mvalue = static_cast<float>((middlelabelValue - ((float)middlelabelValue - (int)middlelabelValue)) + 0.1 * value);
			else
				mvalue = static_cast<float>(middlelabelValue * 10 + value);
	
		}

		if ((mvalue) <= maxValue)
		{
			middlelabelValue = mvalue;
			intermdiatelabel.setText(String(middlelabelValue) , dontSendNotification);
		}
	}
	void CommonNumPad::sliderValueChanged(Slider* slider)
	{
		if (slider == &numPadValue)
		{
			isAnyInput = true;
			intermidentValue = (float)numPadValue.getValue();
			refreshDisplay(intermidentValue);
		}
	}

	void CommonNumPad::show(std::function<void(int)> CallbackOnExit)
	{
		if (!numPadValue.isVisible())
		{
			numPadValue.setVisible(true);
			intermdiatelabel.setVisible(false);
		}
		numPadValue.toFront(true);
		middlelabelValue = 0;
		ui::CommonUtils::showCustomDialog(this->getName(), this, CallbackOnExit, juce::Rectangle <int>(0, 0, 604, 474));
	}

	void CommonNumPad::paint(juce::Graphics& g)
	{
		juce::Rectangle <float>a{ (float)0,(float)0,604 ,474 };
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-container.png"));
		g.drawImage(defaultImage, a, RectanglePlacement::centred);
		g.setColour(juce::Colour(0xFF3A4165));
		g.drawLine(0, 78, 604, 78);
		g.drawLine(0, 368, 604, 368);
#if 0
		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-slider-minus-btn-default.png"));
		Image activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-slider-minus-btn-default-hover.png"));
		Image Draw;

		Draw = (decSliderButton.isMouseOver() || decSliderButton.isFocused) ? activeImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 32, 103, 50, 50 }, RectanglePlacement::centred);

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-slider-plus-btn-default.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-slider-plus-btn-default-hover.png"));

		Draw = (incSliderButton.isMouseOver() || incSliderButton.isFocused) ? activeImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 522, 103, 50, 50 }, RectanglePlacement::centred);

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-keypad-bg-default.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-keypad-4col-hover.png"));
		g.drawImage((num7.isMouseOver() || num7.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)30, (float)160, (float)177.3,(float)44) }, RectanglePlacement::stretchToFit);
		g.drawImage((num8.isMouseOver() || num8.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)213.3, (float)160, (float)177.3, (float)44)}, RectanglePlacement::stretchToFit);
		g.drawImage((num9.isMouseOver() || num9.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)394.6, (float)160, (float)177.3, (float)44)}, RectanglePlacement::stretchToFit);
		g.drawImage((num4.isMouseOver() || num4.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)30, (float)208, (float)177.3, (float)44) //44.3}, RectanglePlacement::stretchToFit);
		g.drawImage((num5.isMouseOver() || num5.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)213.3, (float)208, (float)177.3, (float)44) }, RectanglePlacement::stretchToFit);
		g.drawImage((num6.isMouseOver() || num6.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)394.6, (float)208, (float)177.3, (float)44) }, RectanglePlacement::stretchToFit);
		g.drawImage((num1.isMouseOver() || num1.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)30, (float)256, (float)177.3, (float)44)}, RectanglePlacement::stretchToFit);
		g.drawImage((num2.isMouseOver() || num2.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{(float)213.3, (float)256, (float)177.3, (float)44) }, RectanglePlacement::stretchToFit);
		g.drawImage((num3.isMouseOver() || num3.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{(float)394.6, (float)256, (float)177.3, (float)44) }, RectanglePlacement::stretchToFit);

		if (isNumpadWithFloat)
		{
			g.drawImage((num0.isMouseOver() || num0.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)30, (float)304, (float)177.3, (float)44 });
			g.drawImage((decimalButton.isMouseOver() || decimalButton.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)213.3, (float)304, (float)177.3, (float)44 });
			g.drawImage((numDelButton.isMouseOver() || numDelButton.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)394.6, (float)304, (float)177.3, (float)44 }, RectanglePlacement::stretchToFit);
		}
		else
		{
			defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-keypad-3col-default.png"));
			activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-keypad-3col-hover.png"));
			g.drawImage((num0.isMouseOver() || num0.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)30, (float)304, (float)177.3, (float)44 });
			g.drawImage((numDelButton.isMouseOver() || numDelButton.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ (float)213.3, (float)304, (float)354.6, (float)44 }, RectanglePlacement::stretchToFit);
		}

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-dangerbg-default.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-dangerbg-active.png"));
		g.drawImage((numCancelButton.isMouseOver() || numCancelButton.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ 30, 398, 265, 44 }, RectanglePlacement::centred);

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-primarybg-active.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-primarybg-default.png"));
		g.drawImage((numApplyButton.isMouseOver() || numApplyButton.isFocused) ? activeImage : defaultImage, juce::Rectangle<float>{ 305, 398, 265, 44 }, RectanglePlacement::centred);
#endif
	}

	void CommonNumPad::resized()
	{
#ifdef _MSC_VER //TODO : remove and fix below setBounds use int not float
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
		Title.setBounds(30, 10, 544, heightNumpadTitle);
		numPadValue.setBounds(xStartNumpadCmp + 55, xStartNumpadCmp + yStartNumpadCmpVal + 3, widthNumpadCmp - 108, 50);
		intermdiatelabel.setBounds(xStartNumpadCmp + 55, xStartNumpadCmp + yStartNumpadCmpVal + 3, widthNumpadCmp - 108, 50);
		decSliderButton.setBounds(32, 103, 50, 50);
		incSliderButton.setBounds(522, 103, 50, 50);
		Rectangle<int> targetArea = { xStartNumpadCmp, yStartNumpadNumbers, widthNumpadCmp,heightNumpadNumbers };
		num7.setBounds((float)30, (float)160, (float)177.3,(float) 44); //44.3
		num8.setBounds((float)213.3, (float)160, (float)177.3, (float)44);
		num9.setBounds((float)394.6, (float)160, (float)177.3, (float)44);
		num4.setBounds((float)30, (float)208, (float)177.3, (float)44); //44.3
		num5.setBounds((float)213.3, (float)208, (float)177.3, (float)44);
		num6.setBounds((float)394.6, (float)208, (float)177.3, (float)44);
		num1.setBounds((float)30, (float)256, (float)177.3, (float)44); //44.3
		num2.setBounds((float)213.3, (float)256, (float)177.3, (float)44);
		num3.setBounds((float)394.6, (float)256, (float)177.3, (float)44);
		if (isNumpadWithFloat)
		{
			num0.setBounds((float)30, (float)304, (float)177.3, (float)44); //44.3
			decimalButton.setBounds((float)213.3, (float)304, (float)177.3, (float)44);
			numDelButton.setBounds((float)394.6, (float)304, (float)177.3, (float)44);
		}
		else
		{
			num0.setBounds((float)30, (float)304, (float)177.3, (float)44);
			numDelButton.setBounds((float)213.3, (float)304, (float)354.6, (float)44);
		}

		targetArea = { xStartNumpadCmp,  yStartNumpadCtrl + 40,  widthNumpadCmp, heightNumpadCtrl };
		ctrlRow.performLayout(targetArea);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	}

	void CommonNumPad::handleCommandMessage(int id)
	{
		if(id == 1)
			buttonClicked(&decButton);
		else if (id == 2)
			buttonClicked(&incButton);
		else if (id == 3)
			buttonClicked(&numApplyButton);
		else if (id == 4)
			buttonClicked(&numCancelButton);
	}

	bool CommonNumPad::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		int value;
		bool keyHandled = true;
		int FastJumpValue = 1;
		if (KeyValue > 0)
			FastJumpValue = maxValue > 50 ? 5 : 2;

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RMOVERIGHT:
			numPadValue.setVisible(true);
			intermdiatelabel.setVisible(false);
			intermidentValue -= FastJumpValue; //Fast rotation
			isAnyInput = true;
			refreshDisplay(intermidentValue);
			break;
		case FrontPannelParam::paramKey_RMOVELEFT://Fast rotation
			numPadValue.setVisible(true);
			intermdiatelabel.setVisible(false);
			intermidentValue += FastJumpValue;
			isAnyInput = true;
			refreshDisplay(intermidentValue);
			break;
		case FrontPannelParam::paramKey_RSELECT:
			postCommandMessage(3);
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			postCommandMessage(4);
			break;
		case FrontPannelParam::paramKey_TRACKSEL1:
		case FrontPannelParam::paramKey_TRACKSEL2:
		case FrontPannelParam::paramKey_TRACKSEL3:
		case FrontPannelParam::paramKey_TRACKSEL4:
		case FrontPannelParam::paramKey_TRACKSEL5:
		case FrontPannelParam::paramKey_TRACKSEL6:
		case FrontPannelParam::paramKey_TRACKSEL7:
		case FrontPannelParam::paramKey_TRACKSEL8:
		case FrontPannelParam::paramKey_TRACKSEL9:
			value = ((paramId_t)param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1);
			handleArithmetic(false, false, false, value);
			break;
		case FrontPannelParam::paramKey_TRACKSEL10:
			handleArithmetic(false, false, false, 0);
			break;
		case FrontPannelParam::paramKey_DELETE:
			if (middlelabelValue != 0)
			{
				isDeletePressed = true;
				handleArithmetic(false, false, false, -1);
			}
			break;
		case FrontPannelParam::paramKey_TRACKSEL16:
			if (isNumpadWithFloat)
			{
				isdecimalPressed = true;
				handleArithmetic(false, false, false, -1);
			}
			break;
		default:
			keyHandled = false;
			break;
		}
		return keyHandled;
	}

	void CommonNumber::paint(juce::Graphics& g)
	{
		auto bounds = getLocalBounds();
		auto cornerSize = 6.0f;

		if (bShouldDraw)
		{
			auto ImageToDraw = getFocusState() ? overImage : normalImage;
			g.drawImage(ImageToDraw, bounds.toFloat());
		}

		g.setColour(ui::Theme::Instance().getColour(customBlue12));
		if (layoutType)
		{
			auto flatOnLeft = layoutType & ConnectedOnLeft;
			auto flatOnRight = layoutType & ConnectedOnRight;
			auto flatOnTop = layoutType & ConnectedOnTop;
			auto flatOnBottom = layoutType & ConnectedOnBottom;
			if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
			{
				Path path;
				path.addRoundedRectangle((float)bounds.getX(), (float)bounds.getY(),
					(float)bounds.getWidth(), (float)bounds.getHeight(),
					cornerSize, cornerSize,
					!(flatOnLeft || flatOnTop),
					!(flatOnRight || flatOnTop),
					!(flatOnLeft || flatOnBottom),
					!(flatOnRight || flatOnBottom));

				g.fillPath(path);

				g.setColour(ui::Theme::Instance().getColour(neutralWhite));
				g.strokePath(path, PathStrokeType(1.0f));
			}
			else
			{
				g.fillRoundedRectangle(ui::Rectangle{ (float)bounds.getX(),(float)bounds.getY(),(float)bounds.getWidth(),(float)bounds.getHeight() }, cornerSize);

				g.setColour(ui::Theme::Instance().getColour(neutralWhite));
				g.drawRoundedRectangle(ui::Rectangle{ (float)bounds.getX(),(float)bounds.getY(),(float)bounds.getWidth(),(float)bounds.getHeight() }, cornerSize, 1.0f);
			}
		}
		CommonLabel::paint(g);


	}

	void CommonNumber::resized()
	{

	}
	bool CommonNumber::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		Colour Colour;
		if (isFocuse)
			setFocus(true);
		else
			setFocus(false);

		if (!isEditing || (FrontPannelParam)param== FrontPannelParam::paramKey_MINUS_NAV|| (FrontPannelParam)param == FrontPannelParam::paramKey_PLUS_NAV)
		{
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_MouseClick:
			case FrontPannelParam::paramKey_RMOVELEFT:
			case FrontPannelParam::paramKey_RMOVERIGHT://Fallthrough
				//focus set
				break;
			case FrontPannelParam::paramKey_RSELECT:
				this->postCommandMessage(1);
				break;
			case FrontPannelParam::paramKey_MINUS_NAV:
				if(isFocuse)
					this->postCommandMessage(2);
				break;
			case FrontPannelParam::paramKey_PLUS_NAV:
				if(isFocuse)
					this->postCommandMessage(3);
				break;
			default:
				//		this->setFocus(false);
				break;
			}
		}
		else
		{
			numPad->FPKeyHandler(isFocuse, param, KeyValue);
		}
		return true;
	}

	void CommonNumber::handleCommandMessage(int id)
	{
		if (id == 1)
			ShowNumPad();
		else if (id == 2)
		{
			float stepValue = isNumpadWithFloat ? 0.1f : 1.0f;
			setValue(validateValue((getText().getFloatValue()) - stepValue));
		}
		else if (id == 3)
		{
			float stepValue = isNumpadWithFloat ? 0.1f : 1.0f;
			setValue(validateValue((getText().getFloatValue()) + stepValue));
		}
	}

	void CommonNumber::mouseMove(const MouseEvent& event)
	{
#if PHY_MOUSE_OVER
		if (focusState != true)
		{
			focusState = true;
			if (onFocusChanged)
				onFocusChanged(true);

		}
#endif
	}

	void CommonNumber::mouseExit(const MouseEvent& event)
	{
#if PHY_MOUSE_OVER
		if (focusState != false)
		{
			focusState = false;
			if (onFocusChanged)
				onFocusChanged(false);
		}
#endif
	}

	void CommonNumber::setFocus(bool s)
	{
		if (focusState != s)
		{
			focusState = s;
			if (onFocusChanged)
				onFocusChanged(s);
		}

	};
};
