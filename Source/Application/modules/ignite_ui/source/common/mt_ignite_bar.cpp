/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY
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

using namespace ui;
SceneStatusBar::SceneStatusBar()
{
	songBarLabel.makeVisible(this);
	songBarLabel.setDisplayTitle(false);
	songBarLabel.setFont(juce::Font(font_11, juce::Font::plain).withTypefaceStyle("Regular"));
	songBarLabel.setJustificationType(juce::Justification::centred);
	songBarLabel.setText("", dontSendNotification);
}

SceneStatusBar::~SceneStatusBar()
{}

//==============================================================================
void SceneStatusBar::paint(juce::Graphics& g)
{
	float widthofBar=0;
	float xStart = 0;
	juce::Rectangle <float>a{ (float)0,(float)0,(float)layout::songBar1.getWidth(),(float)layout::songBar1.getHeight() };
	Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scene-dur-bar.png"));
	g.drawImage(dropImage, a, RectanglePlacement::centred);
	if (barLength != 0)
	{
		widthofBar = ((float)1024 / (float)barLength);
		for (int i = 0; i < barLength; i++)
		{

			if ((loopStart <= i) && (i <= loopEnd))
			{
				g.setColour(Colour(0xFFB14444));
				g.fillRect((float)xStart, (float)0, (float)1, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFF4B91A2));
				g.fillRect((float)xStart + 1, (float)0, (float)widthofBar - 2, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFFB14444));
				g.fillRect((float)xStart + widthofBar - 1, (float)0, (float)1, (float)layout::songBar1.getHeight());

			}
			else
			{
				g.setColour(Colour(0xFF334375));
				g.fillRect((float)xStart, (float)0, (float)1, (float)layout::songBar1.getHeight()); 
				g.setColour(Colour(0xFF1E2745));
				g.fillRect((float)xStart+1, (float)0, (float)widthofBar -2, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFF334375));
				g.fillRect((float)xStart+ widthofBar-1, (float)0, (float)1, (float)layout::songBar1.getHeight());
			}

			if (activeBar == i + 1)
			{
				g.setColour(Colour(0xFF65B1C4));
				g.fillRect((float)xStart, (float)0, (float)1, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFF6BD0E8));
				g.fillRect((float)xStart + 1, (float)0, (float)widthofBar - 2, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFF65B1C4));
				g.fillRect((float)xStart + widthofBar - 1, (float)0, (float)1, (float)layout::songBar1.getHeight());
			}
			xStart = xStart + widthofBar ;
		}
	}
}

void SceneStatusBar::resized()
{
	songBarLabel.setBounds(getLocalBounds());
}

void SceneStatusBar::setDisplayMessage(String& data)
{
	songBarLabel.setText(data, dontSendNotification);
}

void SceneStatusBar::onNumofBarchangedinScene(int nobar)
{
	barLength = nobar;
	repaint();
}
PatternStatusBar::PatternStatusBar()
{
	songBarLabel.makeVisible(this);
	songBarLabel.setDisplayTitle(false);
	songBarLabel.setFont(juce::Font(font_11, juce::Font::plain).withTypefaceStyle("Regular"));
	songBarLabel.setJustificationType(juce::Justification::centred);
	songBarLabel.setText("", dontSendNotification);
}

PatternStatusBar::~PatternStatusBar()
{}

//==============================================================================
void PatternStatusBar::paint(juce::Graphics& g)
{
	//juce::Rectangle <float>a{ (float)0,(float)0,(float)layout::songBar1.getWidth(),(float)layout::songBar1.getHeight() };
	//Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("scene-dur-bar.png"));
	//g.drawImage(dropImage, a, RectanglePlacement::centred);
	g.setColour(Colour(0xFFffADAD).withBrightness(0.5f));
	g.fillAll();
	if (patternBarLength != 0)
	{
		float xStart = 0;
		float widthofBar = ((float)1024 / (float)patternBarLength);
		for (int i = 0; i < patternBarLength; i++)
		{
			if((loopStart <=i ) && ( i<= loopEnd))
			{
				g.setColour(Colour(0xFFB14444));
				g.fillRect((float)xStart, (float)0, (float)2.5, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFF7C3A3A));
				g.fillRect((float)xStart + 2, (float)0, (float)widthofBar - 4, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFFB14444));
				g.fillRect((float)xStart + widthofBar - 2, (float)0, (float)2.5, (float)layout::songBar1.getHeight());

			}
			else
			{
				g.setColour(Colour(0xFF334375));
				g.fillRect((float)xStart, (float)0, (float)1, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFF1E2745));
				g.fillRect((float)xStart + 1, (float)0, (float)widthofBar - 2, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFF334375));
				g.fillRect((float)xStart + widthofBar - 1, (float)0, (float)1, (float)layout::songBar1.getHeight());
			}

			if (activeBar == i + 1)
			{
				g.setColour(Colour(0xFFffADAD));
				g.fillRect((float)xStart, (float)0, (float)2.5, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFFFF6666));
				g.fillRect((float)xStart + 2, (float)0, (float)widthofBar - 4, (float)layout::songBar1.getHeight());
				g.setColour(Colour(0xFFffADAD));
				g.fillRect((float)xStart + widthofBar - 2, (float)0, (float)2.5, (float)layout::songBar1.getHeight());
			}
			xStart = xStart + widthofBar;
		}
	}
}

void PatternStatusBar::resized()
{
	songBarLabel.setBounds(getLocalBounds());
}

void PatternStatusBar::setDisplayMessage(String& data)
{
	songBarLabel.setText(data, dontSendNotification);
}
