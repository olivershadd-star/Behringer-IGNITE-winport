#pragma once
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
	class CommonKey;

	class common_rotaryslider : public Component
	{
	public:
		std::function<void(double)> onValueChanged;
		std::function<void(String)> onTitleChanged;
		std::function<void(double)> onDragEnd;

		explicit common_rotaryslider(const String& Title = "", Slider::SliderStyle Style = Slider::LinearBar, Slider::TextEntryBoxPosition TextBoxPos = Slider::NoTextBox);

		void makeVisible(Component* Parent);
		void makeVisibleAndAddListner(Component* Parent);

		void showTitle(const bool Show, Justification justification = Justification::centredLeft);
		void showValue(const bool Show, Justification justification = Justification::centredLeft);
		void showTitleAndValue(const bool Show, Slider::TextEntryBoxPosition ValuePos, Justification justification = Justification::centredLeft);

		void setDisplayProportions(const float Slider, const float Value, const float Title);
		void setStringLimit(std::vector<juce::String>, int stepSize);
		void setCentered(const bool Show);

		bool isCentered() const;
		bool isDisplayingTitle() const;
		bool isDisplayingValue() const;

		double getMin() const;
		double getMax() const;
		double getValue() const;

		void setValue(double newValue, NotificationType notification);
		void setFloatValue(double newValue, NotificationType notification);
		void setRange(int newMin, int newMax, float newInt = 0);
		void setNumDecimalPlacesToDisplay(int decimalPlacesToDisplay);
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);

		void setTitle(const juce::String& t) { title.setText(t, juce::dontSendNotification); }
		void setKnobTitle(String, bool);
		Slider& getSlider() { return slider; }
		Label& getTitle() { return title; }
		Label& getVale() { return value; }
		String getKnob() { return knob.getText(); };
		void setValueColour(Colour c) {
			value.setColour(Label::textColourId, c);
		}
		void setTitleColour(Colour c) {
			title.setColour(Label::textColourId, c);
		}
		class Listener
		{
		public:
			virtual ~Listener() = default;
			virtual void onDoubleClicked(common_rotaryslider*) {};
			virtual void onbuttonClicked(common_rotaryslider*, bool value) {};
			virtual void onRotaryValueChange(common_rotaryslider*, double Value) {};
			virtual void onTitleChange(common_rotaryslider*, String s) {};
			virtual void onTitleEdit(common_rotaryslider*, String s) {};
			virtual void onRotaryDragEnd(common_rotaryslider*, double Value) {};
		};

		void addListener(Listener* newListener);
		void setValueVisible(bool Value);
		void removeListener(Listener* listener);
		bool stringRangeEnabled = false;
		void disableTitleEdit(bool state);
		void enableDisableTitleText(bool state) { knob.setVisible(state); }
		bool clickState = true;
		bool titleEditable = true;
		bool isEditing{ false };
		bool isFocused = false;
		void setEditCtl(bool state) { isEditing = state; }
		void changeDisplayName(String Name);
		void setUnit(String Unit, bool setVisble);
	private:
		Slider::TextEntryBoxPosition textBosPos{ Slider::NoTextBox };
		bool bShowTitle{ false }, bShowValue{ false }, bCentered{ false };
		Slider slider;
		Label value, knob;
		CommonKey title{ " " };
		CommonLabel name{ "" };
		bool unitVisiblity = false;
		String unit = "";
		float pTitle{ .35f }, pSlider{ .25f }, pValue{ .4f };
		ListenerList<Listener> rotaryListeners;
		void resized() override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		void mouseDoubleClick(const MouseEvent& event) override;
		std::vector<juce::String> stringValueList;
	};

	class common_rotarysliderwithtitle : public common_rotaryslider
	{
	public:
		explicit common_rotarysliderwithtitle(const String& Title, Slider::SliderStyle Style = Slider::LinearBar,
			Slider::TextEntryBoxPosition TextBoxPos = Slider::TextBoxAbove);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(common_rotarysliderwithtitle)
	};

	class commonrotary : public common_rotaryslider
	{
	public:
		explicit commonrotary(const String& Title = "");

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(commonrotary)
	};

	class CommonRotaryLookandFeel : public juce::LookAndFeel_V4
	{
	public:

		CommonRotaryLookandFeel();
		static CommonRotaryLookandFeel* getLnf()
		{
			static CommonRotaryLookandFeel commonLnf;
			return &commonLnf;
		};

	private:

		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

	};
}
