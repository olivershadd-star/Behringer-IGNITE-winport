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

namespace ui
{
	//////////////////////
	/// COMMON Button
	//////////////////////
	CommonButton::CommonButton() : CommonButton("", "")
	{}
	CommonButton::CommonButton(const String& buttonName) : CommonButton(buttonName, buttonName)
	{}
	CommonButton::CommonButton(const String& buttonName, const String& buttonText) : TextButton(buttonName)
	{
		setButtonText(buttonText.length() ? buttonText : buttonName);
		setLookAndFeel(CommonLooknFeel::getLnf());
		setViewportIgnoreDragFlag(false);
	}

	void CommonButton::setID(int ID) { if (id != ID) id = ID; }
	int CommonButton::getID() { return id; }

	void CommonButton::showBorder(bool Show) { bShowBorder = Show; resized(); }
	void CommonButton::showTitle(bool Show) { bShowTitle = Show; resized(); }
	void CommonButton::showTitleAndBorder(bool Show) { bShowTitle = Show; bShowBorder = Show;  resized(); }
	void CommonButton::setRadius(float XRadius, float YRadius) { xRadius = XRadius; yRadius = YRadius; };

	void CommonButton::makeVisible(Component* Parent)
	{
		Parent->addAndMakeVisible(dynamic_cast<Component&>(*this));
	}

	void CommonButton::makeVisibleAndAddListner(Component* Parent)
	{
		makeVisible(Parent);
		addListener(dynamic_cast<Listener*>(Parent));
	}

	void CommonButton::makeVisibleAndAddRadioGroup(Component* Parent, int RadioGroupId)
	{
		makeVisible(Parent);
		setRadioGroupId(RadioGroupId, NotificationType::dontSendNotification);
	}

	void CommonButton::makeVisibleAddListnerAndAddRadioGroup(Component* Parent, int RadioGroupId)
	{
		makeVisibleAndAddListner(Parent);
		setRadioGroupId(RadioGroupId, NotificationType::dontSendNotification);
	}

	void CommonButton::setBackgroundColour(Colour Colour)
	{
		setColour(TextButton::buttonColourId, Colour);
	}

	void CommonButton::setTextColour(Colour Colour)
	{
		setColour(TextButton::textColourOffId, Colour);
	}

	void CommonButton::setOutlineColour(Colour Colour)
	{
		setColour(juce::TextEditor::outlineColourId, Colour);
	}

	bool CommonButton::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RSELECT:
			if (isFocuse)
				this->triggerClick();
			break;
		case FrontPannelParam::paramKey_RMOVELEFT:
		case FrontPannelParam::paramKey_RMOVERIGHT:
		case FrontPannelParam::paramKey_MouseClick:
		case FrontPannelParam::paramRot_ROW:
		case FrontPannelParam::paramKey_PAGESHIFT:
			if (isFocuse)
				isFocused = true;
			else
				isFocused = false;
			break;
		}
		repaint();
		return true;
	}

	//////////////////////
	/// COMMON Toggle Button
	//////////////////////
	CommonToggleButton::CommonToggleButton() : CommonToggleButton("", "")
	{}
	CommonToggleButton::CommonToggleButton(const String& buttonName) : CommonToggleButton(buttonName, buttonName)
	{}
	CommonToggleButton::CommonToggleButton(const String& buttonName, const String& buttonText) : CommonButton(buttonName, buttonText)
	{
		setClickingTogglesState(true);
	}

	//////////////////////
	/// COMMON CheckBox Button
	//////////////////////
	CommonCheckBoxButton::CommonCheckBoxButton(const String& buttonName, const String& buttonText) : ToggleButton()
	{
		auto n = buttonText.length() ? buttonText : buttonName;
		setName(n);
		setButtonText(n);
		setLookAndFeel(CommonLooknFeel::getLnf());
	}

	//////////////////////
	/// COMMON Image Button
	//////////////////////
	CommonImageButton::CommonImageButton(const String& buttonName) :CommonImageButton(buttonName, "")
	{}
	CommonImageButton::CommonImageButton(const String& buttonName, const String& NormalImage, const String& DownImage, const String& HoverImage)
		: ImageButton(buttonName)
	{
		setName(buttonName);
		setButtonText(buttonName);
		setClickingTogglesState(true);
		setImage(NormalImage, DownImage, HoverImage);
	}

	void CommonImageButton::setImage(Image NormalImage, Image DownImage, Image HoverImage)
	{
		nI = NormalImage;
		dI = DownImage;
		hI = HoverImage;
		setImage_(nI, dI, hI, Theme::Instance().highlightColour(0), Theme::Instance().highlightColour(0), Theme::Instance().getColour(customYellow2).withAlpha(0.2f));
	}

	void CommonImageButton::setImage(const String& NormalImage, const String& DownImage, const String& HoverImage)
	{
		if (NormalImage.isNotEmpty())
			nI = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(NormalImage));
		if (DownImage.isNotEmpty())
			dI = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(DownImage));
		if (HoverImage.isNotEmpty())
			hI = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(HoverImage));
		setImage_(nI, dI, hI, Theme::Instance().highlightColour(0), Theme::Instance().highlightColour(0), Theme::Instance().getColour(customBlue12).withAlpha(0.2f));
	}

	void CommonImageButton::setImage_(const Image& NI, const Image& DI, const Image& HI, const Colour& NC, const Colour& DC, const Colour& HC)
	{
		setImages(false,   // resizeButtonNowToFitThisImage
			false,    // rescaleImagesWhenButtonSizeChanges
			true,    // preserveImageProportions
			NI,      // normalImage_
			1.000f,  // imageOpacityWhenNormal
			NC,      // overlayColourWhenNormal
			HI,      // overImage_
			1.000f,  // imageOpacityWhenOver
			HC,      // overlayColourWhenOver
			DI,      // downImage_
			1.000f,  // imageOpacityWhenDown
			DC,      // overlayColourWhenDown
			0.0f     // hitTestAlphaThreshold
		);
	}

	void CommonImageButton::setOverlayColours(const juce::Colour& Down, const juce::Colour& Normal, const juce::Colour& Hover)
	{
		setImage_(nI, dI, hI, Normal, Down, Hover);
	}

	void CommonImageButton::setBackgroundColour(const juce::Colour& Color)
	{
		backgroundColour = Color;
	}

	void CommonImageButton::makeVisible(Component* Parent)
	{
		Parent->addAndMakeVisible(dynamic_cast<Component&>(*this));
	}

	void CommonImageButton::makeVisibleAndAddListner(Component* Parent)
	{
		makeVisible(Parent);
		addListener(dynamic_cast<Button::Listener*>(Parent));
	}

	void CommonImageButton::makeVisibleAndAddRadioGroup(Component* Parent, int RadioGroupId)
	{
		makeVisible(Parent);
		setRadioGroupId(RadioGroupId, NotificationType::dontSendNotification);
	}

	void CommonImageButton::makeVisibleAddListnerAndAddRadioGroup(Component* Parent, int RadioGroupId)
	{
		makeVisibleAndAddListner(Parent);
		setRadioGroupId(RadioGroupId, NotificationType::dontSendNotification);
	}

	void CommonImageButton::paintButton(Graphics& g, bool asHighlighed, bool asDown)
	{
		g.setColour(backgroundColour);
		g.fillRect(getLocalBounds());
		ImageButton::paintButton(g, asHighlighed, asDown);
	}
	bool CommonImageButton::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RSELECT:
			if (isFocuse)
				this->triggerClick();
			break;
		case FrontPannelParam::paramKey_RMOVELEFT:
		case FrontPannelParam::paramKey_RMOVERIGHT:
		case FrontPannelParam::paramKey_MouseClick:
			if (KeyValue > 0)
			{
				if (isFocuse)
					setImage_(hI, dI, hI, Theme::Instance().highlightColour(0), Theme::Instance().highlightColour(0), Theme::Instance().getColour(customGreen1).withAlpha(0.1f));
				else
					setImage_(nI, dI, hI, Theme::Instance().highlightColour(0), Theme::Instance().highlightColour(0), Theme::Instance().getColour(customBlue12).withAlpha(0.2f));
			}
			else
				isFocused = isFocuse;
			break;
		}
		repaint();
		return true;
	}

	void CommonImageButton::setDisableImage(const String& image)
	{
		disabledImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(image));
	}

	void CommonImageButton::sethoverImages(const String& defaultHover, const String& ActiveHover, const String& DisbledHover)
	{
		DefHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(defaultHover));
		ActHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(ActiveHover));
		DisabledhoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(DisbledHover));
	}
	void CommonImageButton::sethoverImages(Image defaultHover, Image ActiveHover, Image DisbledHover)
	{
		DefHoverImage = defaultHover;
		ActHoverImage = ActiveHover;
		DisabledhoverImage = DisbledHover;
	}

	Image CommonImageButton::gethoverImages(int index)
	{
		switch (index)
		{
		case 0: return DefHoverImage;
		case 1: return ActHoverImage;
		case 2: return DisabledhoverImage;
		}
		return DisabledhoverImage;
	}
	//////////////////////
	/// COMMON Color Button
	//////////////////////
	CommonColorButton::CommonColorButton(const Colour& Color)
		: CommonColorButton(Color, Color)
	{}

	CommonColorButton::CommonColorButton(const Colour& onColor, const Colour& offColor)
		: onCol(onColor), offCol(offColor), CommonToggleButton("")
	{}

	void CommonColorButton::setColor(const Colour& Col) { onCol = Col; }
	void CommonColorButton::setColor(const Colour& onColor, const Colour& offColor) { onCol = onColor; offCol = offColor; }

	const Colour& CommonColorButton::getColor() { return onCol; }
	const Colour& CommonColorButton::getOffColor() { return offCol; }

	void CommonColorButton::paint(Graphics& g)
	{
		if (bShowBorder)
		{
			Path p;
			p.addRoundedRectangle(getLocalBounds(), xRadius, yRadius);
			g.setColour(Colour(Theme::Instance().getColour(systemYellow)));
			g.strokePath(p, PathStrokeType(2.0f));
		}
		Path p;
		p.addRoundedRectangle(getLocalBounds().reduced(5), xRadius, yRadius);
		g.setColour(getToggleState() ? onCol : offCol);
		g.fillPath(p);
	}

	//////////////////////
	/// COMMON Pad Button
	//////////////////////
	CommonPadButton::CommonPadButton() : CommonPadButton("", PadButtonType::with1Row) {}
	CommonPadButton::CommonPadButton(const String& buttonName) : CommonPadButton(buttonName, PadButtonType::with1Row) {}
	CommonPadButton::CommonPadButton(const String& buttonName, PadButtonType Type) : type(Type), CommonButton()
	{
		setLookAndFeel(CommonLooknFeel::getLnf());

		setClickingTogglesState(true);
		setMouseClickGrabsKeyboardFocus(true);
		addMouseListener(this, true);

		lhdr1.setColour(juce::Label::textColourId, Theme::Instance().getColour(systemBlue));

		lhdr1.makeVisible(this);
		lhdr2.makeVisible(this);
		lrow1.makeVisible(this);
		rt.items.add(FlexItem(lhdr1).withFlex(1.5).withMargin({ 2.0 }));
		rt.items.add(FlexItem(lhdr2).withFlex(1).withMargin({ 2.0 }));

		box.flexDirection = FlexBox::Direction::column;
		box.items.add(FlexItem(rt).withFlex(1.5).withMargin({ 2.0 }));
		box.items.add(FlexItem(lrow1).withFlex(1).withMargin({ 2.0 }));

		if (PadButtonType::with2Rows == type || PadButtonType::with2RowsNSlider == type)
		{
			lrow2.makeVisible(this);
			box.items.add(FlexItem(lrow2).withFlex(1).withMargin({ 2.0 }));
		}
		if (PadButtonType::withSlider == type || PadButtonType::with1RowNSlider == type || PadButtonType::with2RowsNSlider == type)
		{
			slider.makeVisible(this);
			box.items.add(FlexItem(slider).withFlex(1.5).withMargin({ 2.0 }));
		}

		setHeaderText(buttonName);
		setRow1Text(".");
		slider.setRange(0, 10);
		slider.setNumDecimalPlacesToDisplay(0);
	}

	// Text components...
	void CommonPadButton::setHeaderText(const String& Text) { lhdr1.setText(Text, dontSendNotification); setName(Text); }
	void CommonPadButton::setHeader2Text(const String& Text) { lhdr2.setText(Text, dontSendNotification); }
	void CommonPadButton::setRow1Text(const String& Text) { lrow1.setText(Text, dontSendNotification); }
	void CommonPadButton::setRow2Text(const String& Text) { lrow2.setText(Text, dontSendNotification); }

	// Slider component...
	void CommonPadButton::setSliderRange(double Min, double Max, double StepSize) { slider.setRange(Min, Max, StepSize); }
	void CommonPadButton::setSliderValue(double Value) { slider.setValue(Value, dontSendNotification); }
	void CommonPadButton::setBorderColor(const Colour& Col, float Thickness) { border = Col; borderThickness = Thickness;  repaint(); }

	void CommonPadButton::paint(Graphics& g)
	{
		Path p;
		float corner = 5.0f;
		p.addRoundedRectangle(getLocalBounds(), corner, corner);
		g.setColour(border);
		g.strokePath(p, PathStrokeType(borderThickness));
	}

	void CommonPadButton::resized()
	{
		box.performLayout(getLocalBounds().reduced(3));
	}
}
