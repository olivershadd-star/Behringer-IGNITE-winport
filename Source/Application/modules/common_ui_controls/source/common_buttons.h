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
	class CommonButton : public TextButton
	{
	public:
		CommonButton();
		CommonButton(const String& buttonName);
		CommonButton(const String& buttonName, const String& buttonText);
		void setID(int ID);
		int getID();
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		bool isFocused = false;

		void showBorder(bool Show);
		void showTitle(bool Show);
		void showTitleAndBorder(bool Show);

		void makeVisible(Component* Parent);
		void makeVisibleAndAddListner(Component* Parent);
		void makeVisibleAndAddRadioGroup(Component* Parent, int RadioGroupId);
		void makeVisibleAddListnerAndAddRadioGroup(Component* Parent, int RadioGroupId);

		void setRadius(float XRadius, float YRadius);
		void setBackgroundColour(Colour Colour);
		void setTextColour(Colour Colour);
		void setOutlineColour(Colour Colour);
		bool IsEditing()
		{
			if (this->getToggleState())
				return true;
			return false;
		};
	protected:
		bool bShowTitle{ false };
		bool bShowBorder{ false };
		int id{ 0 };
		float xRadius{ 3.0 }, yRadius{ 3.0 };

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonButton)
	};

	class CommonToggleButton : public CommonButton
	{
	public:
		CommonToggleButton();
		CommonToggleButton(const String& buttonName);
		CommonToggleButton(const String& buttonName, const String& buttonText);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonToggleButton)
	};

	class CommonCheckBoxButton : public ToggleButton
	{
	public:
		explicit CommonCheckBoxButton(const String& buttonName, const String& buttonText = "");

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonCheckBoxButton)
	};

	class CommonImageButton : public ImageButton
	{
	public:
		/*
		void buttonClicked( Button* buttonThatWasClicked )
		{
			isOn = !isOn;
			setToggleState( isOn, NotificationType::dontSendNotification );
		}*/

		CommonImageButton(const String& buttonName);
		CommonImageButton(const String& buttonName, const String& NormalImage, const String& DownImage = "", const String& HoverImage = "");

		void setImage(Image NormalImage, Image DownImage = {}, Image HoverImage = {});
		void setImage(const String& NormalImage, const String& DownImage = "", const String& HoverImage = "");

		void setOverlayColours(const juce::Colour& Down, const juce::Colour& Normal = Theme::Instance().highlightColour(0), const juce::Colour& Hover = Theme::Instance().highlightColour(1).withAlpha(0.2f));
		void setBackgroundColour(const juce::Colour& Color);

		void makeVisible(Component* Parent);
		void makeVisibleAndAddListner(Component* Parent);
		void makeVisibleAndAddRadioGroup(Component* Parent, int RadioGroupId);
		void makeVisibleAddListnerAndAddRadioGroup(Component* Parent, int RadioGroupId);
		void setDisableImage(const String& image);
		void setDisabled(bool state) { isDisabled = state; };
		Image getDisabledImage() { return disabledImage; };
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		bool isFocused = false;
		void sethoverImages(const String& defaultHover, const String& ActiveHover, const String& DisbledHover);
		void sethoverImages(Image defaultHover, Image ActiveHover, Image DisbledHover);
		Image gethoverImages(int);
		void setDefaultOverImage(const String& defaultHover) { DefHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(defaultHover)); };
	private:
		juce::Colour backgroundColour{ Theme::Instance().highlightColour(0) };
		bool isOn = false;
		Image nI, dI, hI, disabledImage,DefHoverImage,ActHoverImage,DisabledhoverImage;
		bool isDisabled{ false };
		void setImage_(const Image& NI, const Image& DI, const Image& HI, const Colour& NC, const Colour& DC, const Colour& HC);

		void paintButton(Graphics& g, bool asHighlighed, bool asDown) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonImageButton)
	};

	class CommonColorButton : public CommonToggleButton
	{
	public:
		explicit CommonColorButton(const Colour& onColor = Theme::Instance().highlightColour(1));
		explicit CommonColorButton(const Colour& onColor, const Colour& offColor);

		void setColor(const Colour& Col);
		void setColor(const Colour& onColor, const Colour& offColor);

		const Colour& getColor();
		const Colour& getOffColor();

	private:
		Colour onCol, offCol;

		virtual void paint(Graphics& g) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonColorButton)
	};

	class CommonPadButton : public CommonButton
	{
	public:
		enum class PadButtonType
		{
			with1Row,
			with2Rows,
			withSlider,
			with1RowNSlider,
			with2RowsNSlider,
			withMenuTab,
			withSongMultiTab,
			withPatternMultiTab,
		};

		CommonPadButton();
		CommonPadButton(const String& buttonName);
		CommonPadButton(const String& buttonName, PadButtonType Type);

		// Text components...
		void setHeaderText(const String& Text);
		void setHeader2Text(const String& Text);
		void setRow1Text(const String& Text);
		void setRow2Text(const String& Text);

		// Slider component...
		void setSliderRange(double Min, double Max, double StepSize = 0.0);
		void setSliderValue(double Value);

		void setBorderColor(const Colour& Col, float Thickness = 1.0f);

		const String& getHeaderText() { return lhdr1.getText(); }
		const String& getHeader2Text() { return lhdr2.getText(); }
		const String& getRow1Text() { return lrow1.getText(); }
		const String& getRow2Text() { return lrow2.getText(); }
		double getSliderValue() { return slider.getValue(); }
		const Colour& getBorderColor() { return border; }

	private:
		float borderThickness{ 1.0f };
		PadButtonType type;
		CommonLabel lhdr1{ "" }, lhdr2{ "" }, lrow1{ "" }, lrow2{ "" };

		CommonSlider slider;
		juce::Colour border{ Theme::Instance().getColour(customBlue1) };

		FlexBox rt, box;

		virtual void paint(Graphics& g) override;
		virtual void resized();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonPadButton)
	};
}
