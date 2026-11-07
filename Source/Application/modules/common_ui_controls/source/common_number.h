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

#pragma once

namespace ui
{
	class CommonNumPad : public juce::Component,
		public CommonButton::Listener,
		public CommonSlider::Listener
	{
	public:

		std::function<void(int)> onValueChanged;
		std::function<void(float)> onFloatValueChanged;
		std::function<void(int)> onPlayTimeValueChanged;
		std::function<void(float)> onPlayTimeFloatValueChanged;

		explicit CommonNumPad(const String& Name, float min, float max, float defaultVal, float stepSize = 1, bool isFloatSupported = false);

		void setValueBounds(float min, float max, float defaultVal, float stepSize = 0.1);
		void setRange(float min, float max, float stepSize);
		void setValue(float Value);
		const float getValue(void) { return lastEnteredValue; }
		void setTitleText(String name);
		void setNumDecimalPlacesToDisplay(int value) { numPadValue.setNumDecimalPlacesToDisplay(value); }

		void show(std::function<void(int)> CallbackOnExit);
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id) override;

	private:
		CommonSlider numPadValue;
		CommonLabel	Title{ "" };
		CommonButton num1{ TRANS("1") };
		CommonButton num2{ TRANS("2") };
		CommonButton num3{ TRANS("3") };
		CommonButton num4{ TRANS("4") };
		CommonButton num5{ TRANS("5") };
		CommonButton num6{ TRANS("6") };
		CommonButton num7{ TRANS("7") };
		CommonButton num8{ TRANS("8") };
		CommonButton num9{ TRANS("9") };
		CommonButton num0{ TRANS("0") };
		CommonButton sign{ TRANS("+/-") };
		CommonButton numDelButton{ TRANS("<-") };
		CommonButton incButton{ TRANS("+") };
		CommonButton decButton{ TRANS("-") };
		CommonButton x2Button{ TRANS("x2") };
		CommonButton b2Button{ TRANS("/2") };
		CommonButton decimalButton{ TRANS(".") };
		CommonButton numApplyButton{ TRANS("Apply") };
		CommonButton numCancelButton{ TRANS("Cancel") };
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		CommonImageButton incSliderButton{ "SLIDERINC","textbox-slider-plus-btn-default.png","textbox-slider-plus-btn-default-hover.png","textbox-slider-plus-btn-default-hover.png" };
		CommonImageButton decSliderButton{ "SLIDERDEC","textbox-slider-minus-btn-default.png","textbox-slider-minus-btn-default-hover.png","textbox-slider-minus-btn-default-hover.png" };
		CommonLabel intermdiatelabel{ "" };
		FlexBox valRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox topRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox midTRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox midBRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox bottomRow{ FlexBox::Direction::row , FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox ctrlRow{ FlexBox::Direction::row , FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };

		FlexBox numpad{ FlexBox::Direction::column, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox ctrlBox{ FlexBox::Direction::column, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox outerBox{ FlexBox::Direction::column, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		float minValue;
		float maxValue;
		float stepValue{ 1.0 };
		float lastEnteredValue;
		float intermidentValue;
		bool floatingdis = 0;
		bool isdotpreset = 0;
		bool isAnyInput{ false };
		bool isdecimalPressed = false;
		bool isPlusPressed = false;
		bool isMinusPressed = false;
		bool isNumpadWithFloat = false;
		bool isNumPadinEditMode = false;
		bool isDeletePressed = false;
		float middlelabelValue = 0;
		void handleArithmetic(bool isDecimal, bool isPlus, bool isMinus, int value);
		float validateValue(float value);
		void refreshDisplay(float value);
		void buttonClicked(juce::Button* button) override;
		void sliderValueChanged(Slider* slider) override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonNumPad);
	};

	class CommonNumber : public CommonLabel
	{
	public:
		enum ConnectedEdgeFlags
		{
			ConnectedOnLeft = 1,
			ConnectedOnRight = 2,
			ConnectedOnTop = 4,
			ConnectedOnBottom = 8,
			NoConnected = 16,
			NoLayout
		};
		std::function<void(int)> onValueChanged;
		std::function<void(float)> onFloatValueChanged;
		std::function<void(int)> onPlayTimeValueChanged;
		std::function<void(float)> onPlayTimeFloatValueChanged;
		std::function<void(bool)> onFocusChanged;
		std::function<void(bool)> onDailogTrigger;

		explicit CommonNumber(const String& Name, float Min, float Max, float Default, bool isFloatSupported = false, float StepSize = 1) :
			CommonLabel(Name, String(Default)),
			numPad(std::make_unique<ui::CommonNumPad>(Name, Min, Max, Default, StepSize, isFloatSupported))
		{
			isNumpadWithFloat = isFloatSupported;
			minValue = Min;
			maxValue = Max;
			addMouseListener(this, true);
			numPad->onValueChanged = [this](int value)
			{
				setText(String(value), juce::dontSendNotification);
				if (onValueChanged)
					onValueChanged(value);
			};
			numPad->onValueChanged = [this](int value)
			{
				setText(String(value), juce::dontSendNotification);
				if (onValueChanged)
					onValueChanged(value);
			};
			numPad->onPlayTimeValueChanged = [this](int value)
			{
				setText(String(value), juce::dontSendNotification);
				if (!isEditing)
				{
					if (onValueChanged)
						onValueChanged(value);
				}
				else if (onPlayTimeValueChanged)
					onPlayTimeValueChanged(value);
			};
			numPad->onPlayTimeFloatValueChanged = [this](float value)
			{
				setText(String(value), juce::dontSendNotification);
				if (!isEditing)
				{
					if (onFloatValueChanged)
						onFloatValueChanged(value);
				}
				else if (onPlayTimeFloatValueChanged)
					onPlayTimeFloatValueChanged(value);
			};
			numPad->onFloatValueChanged = [this](float value)
			{
				setText(String(value), juce::dontSendNotification);
				if (onFloatValueChanged)
					onFloatValueChanged(value);
			};
			title = Name;

			normalImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-modallink-122x80-default.png"));
			overImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-modallink-122x80-default-hover.png"));
		}

		void setRange(float Min, float Max, float StepSize = 1.0)
		{
			numPad->setRange(Min, Max, StepSize);
		}
		void setValueBounds(float Min, float Max, float Default, float StepSize = 1.0)
		{
			numPad->setValueBounds(Min, Max, Default, StepSize);
			setText(String(Default), juce::dontSendNotification);
		}
		void setValue(float value)
		{
			numPad->setValue(value);
			setText(String(value), juce::dontSendNotification);
		}
		float getValue()
		{
			return numPad->getValue();
		}
		float validateValue(float value)
		{
			return jmin<float>(jmax<float>(value, minValue), maxValue);
		}
		void setTitleText(String name)
		{
			title = name;
			numPad->setTitleText(name);
			repaint();
		}
		void handleCommandMessage(int id) override;
		void setNumDecimalPlacesToDisplay(int value) { numPad->setNumDecimalPlacesToDisplay(value); }
		void setLayoutType(int edgetype) { if (layoutType != edgetype) layoutType = edgetype; };
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		bool IsEditing() { return isEditing; }
		void setFocus(bool s);
		bool getFocusState() {
			return focusState;
		};
		void setEditable(bool s) {
			isEditable = s;
		};

		void setJustification(Justification j)
		{
			setJustificationType(j);
		}
		void ShowNumPad()
		{
			if (!isEditing)
			{
				isEditing = true;
				numPad->setValue(getText().getFloatValue());
				numPad->show([this](int r) { isEditing = false; if(onDailogTrigger)onDailogTrigger(false); });
				if (onDailogTrigger)
					onDailogTrigger(true);
			}
		}

		void drawBorder(bool bDraw) { bShouldDraw = bDraw; }
	private:
		bool isEditing{ false };
		std::unique_ptr<ui::CommonNumPad> numPad;
		void paint(juce::Graphics& g);
		int layoutType{ 0 };

		void mouseDown(const MouseEvent&) override
		{
			if (isEditable)
			{
				ShowNumPad();
				if (onDailogTrigger)
					onDailogTrigger(true);
			}
		}
		void mouseDoubleClick(const juce::MouseEvent& e) override
		{
			if (isEditable)
				ShowNumPad();
		}
		
		void resized() override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		bool focusState{ 0 };
		bool isEditable{ true };
		String title;

		Image normalImage;
		Image overImage;
		bool bShouldDraw = false;

		float minValue;
		float maxValue;
		bool isNumpadWithFloat = false;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonNumber);
	};
};
