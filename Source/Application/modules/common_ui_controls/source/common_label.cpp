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
	//////////////////////
	/// COMMON Label
	//////////////////////
	CommonLabel::CommonLabel(const String& Name)
		: CommonLabel(Name, Name, false, false)
	{
		auto theme = Theme::Instance();
		textColourId = theme.getColour(neutralWhite);
		titleColourId = theme.getColour(neutralWhite);
		backgroundColourId = findColour(Label::backgroundColourId);
	}

	CommonLabel::CommonLabel(const String& Name, const String& Text, bool ShowTitle, bool ShowBorder)
		: juce::Label(Name, Text), showTitle(ShowTitle), showBorder(ShowBorder)
	{
		auto theme = Theme::Instance();
		setName(Name);
		setJustificationType(juce::Justification::centredLeft);
		setEditable(false, false, false);
		setLookAndFeel(CommonLooknFeel::getLnf());
		textColourId = theme.getColour(neutralWhite);
		titleColourId = theme.getColour(neutralWhite);
		backgroundColourId = findColour(Label::backgroundColourId);
	}

	void CommonLabel::makeVisible(Component* Parent)
	{
		Parent->addAndMakeVisible(dynamic_cast<Component&>(*this));
	}

	void CommonLabel::makeVisibleAndAddListner(Component* Parent)
	{
		makeVisible(Parent);
		addListener(dynamic_cast<Listener*>(Parent));
	}

	void CommonLabel::setDisplayBorder(bool Show) { showBorder = Show; resized(); }
	void CommonLabel::setDisplayTitle(bool Show) { showTitle = Show; resized(); }
	void CommonLabel::setDisplayDropDown(bool Show) { showDrop = Show; resized(); }
	void CommonLabel::setDisplayTitleAndBorder(bool Show) { showTitle = Show; showBorder = Show;  resized(); }
	void CommonLabel::setBackgroundColour(Colour newColour)
	{
		backgroundColourId = newColour;
		repaint();
	}
	void CommonLabel::setTextColour(Colour newColour)
	{
		textColourId = newColour;
		repaint();
	}

	void CommonLabel::setTitleColour(Colour newColour)
	{
		titleColourId = newColour;
		repaint();
	}

	void CommonLabel::setTextFont(Font newFont)
	{
		fontSize = newFont;
		repaint();
	}

	void CommonLabel::setTitle(String newName)
	{
		setName(newName);
		repaint();
	}

	void CommonLabel::paint(Graphics& g)
	{
		auto b = getLocalBounds();
		auto theme = Theme::Instance();

		Path p;
		p.addRoundedRectangle(b, 5.0f, 5.0f);
		if (showBorder)
		{
			g.setColour(findColour(Label::outlineColourId));
			g.strokePath(p, PathStrokeType(2.0f));
		}
		g.setColour(backgroundColourId);
		g.fillPath(p);

		b.removeFromLeft(5);
		b.removeFromRight(5);
		// Draw Title text.
		if (showTitle)
		{
			auto height = b.getHeight();
			auto bTitle = b.removeFromBottom((int)(0.25 * height));

			bTitle.removeFromTop(3); // Leave some margin at the top...
			// Draw title.
			g.setColour(titleColourId);
			g.setFont(jmin(16.0f, (0.8f * bTitle.getHeight())));

			if(!custombounds)
				g.drawFittedText(getName(), ui::Rectangle{ b.getX(),b.getY()+62,bTitle.getWidth(),bTitle.getHeight()}, getJustificationType(), 1);
			else
				g.drawFittedText(getName(),  TitleBonds, getJustificationType(), 1);
		}
		// Draw drop down icon.
		if (showDrop)
		{
			auto bDrop = b.removeFromRight(10);
			// Draw dropdown arrow.
			Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("Dropdown.png"));
			g.setColour(Theme::Instance().getColour(neutralGrey9));
			g.drawImage(dropImage, bDrop.toFloat(), { RectanglePlacement::Flags::centred }, true);
		}
		// Draw Label text.
		g.setColour(textColourId);
		if (fontSize == NULL)
			g.setFont(jmin(30.0f, (0.7f * b.getHeight())));
		else
			g.setFont(fontSize);
		if (!custombounds) //this bounds will be used when devloper not assigned any custom bounds 
		{
			g.drawFittedText(getText(), b, getJustificationType(), 1);
		}
		else
			g.drawFittedText(getText(), valueBonds, getJustificationType(), 1);
	}

	void CommonLabel::resized()
	{
		auto b = getLocalBounds();
		if (showTitle)
			b.removeFromTop((int)(0.35 * b.getHeight()));
		
	}

	void CommonLabel::editorShown(TextEditor* Editor)
	{
		if (showTitle)
			Editor->setBoundsRelative(0, 0.3f, 1.0f, 0.7f);
		else
			Editor->setBounds(getLocalBounds());
	}

	void CommonLabel::setcustombounds(bool state, Rectangle<int> a, Rectangle<int> b)
	{
		custombounds = state;
		valueBonds = a;
		TitleBonds = b;
	}

	void CommonLabel::mouseMove(const MouseEvent& event)
	{
		if (focusState != true)
		{
			focusState = true;
			if (onFocusChanged)
				onFocusChanged(true);

		}
	}

	void CommonLabel::mouseExit(const MouseEvent& event)
	{
		if (focusState != false)
		{
			focusState = false;
			if (onFocusChanged)
				onFocusChanged(false);
		}
	}

	void CommonLabel::setFocus(bool s)
	{
		if (focusState != s)
		{
			focusState = s;
			if (onFocusChanged)
				onFocusChanged(s);
		}
	}
	//////////////////////
	/// COMMON Name Label
	//////////////////////
	CommonNameLabel::CommonNameLabel(const String& Name) : CommonNameLabel(Name, Name) {}
	CommonNameLabel::CommonNameLabel(const String& Name, const String& Text) : CommonLabel(Name, Text)
	{
		setEditable(true);
		setColour(juce::Label::backgroundColourId, juce::Colour(ui::color::neutral::grey1));
		setColour(juce::Label::textColourId, juce::Colour(ui::color::system::blue));
		setColour(juce::Label::outlineColourId, juce::Colour(ui::color::system::blue));
	}

	CommonSerialNumber::CommonSerialNumber() : CommonSerialNumber("", "") {}
	CommonSerialNumber::CommonSerialNumber(const String& Name) : CommonSerialNumber(Name, Name) {}
	CommonSerialNumber::CommonSerialNumber(const String& Name, const String& Text) : CommonLabel(Name, Text)
	{
		setJustificationType(juce::Justification::centred);
		setEditable(false);
		setInterceptsMouseClicks(false, false);
	}

	//////////////////////
	/// KICK Serial Number Label
	//////////////////////
	void CommonSerialNumber::paint(Graphics& g)
	{
		auto b = getLocalBounds();
		auto bt = b;
		auto br = bt.removeFromBottom((b.getHeight() / 2));

		{
			Path p;
			p.addRoundedRectangle((float)bt.getX(), (float)bt.getY(), (float)bt.getWidth(), (float)bt.getHeight(), 5.0f, 5.0f, true, false, false, false);
			g.setColour(juce::Colour(ui::color::system::blue));
			g.fillPath(p);
		}
		{
			Path p;
			p.addRoundedRectangle((float)br.getX(), (float)br.getY(), (float)br.getWidth(), (float)br.getHeight(), 5.0f, 5.0f, false, false, true, false);
			g.setColour(juce::Colour(ui::color::system::blue).withAlpha((uint8)93));
			g.fillPath(p);
		}
		g.setColour(juce::Colours::white);
		g.setFont((0.64f * bt.getHeight()));
		g.drawText(getText(), bt, getJustificationType());
	}
}
