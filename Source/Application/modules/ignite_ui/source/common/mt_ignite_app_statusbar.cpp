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
AppStatusbar::AppStatusbar()
{
	/*barLabel.makeVisible(this);
	barLabel.setDisplayTitle(false);
	barLabel.setFont(juce::Font(font_16, juce::Font::plain).withTypefaceStyle("Regular"));
	barLabel.setJustificationType(juce::Justification::centred);
	barLabel.setText("Bar:Beat:Step::00:", dontSendNotification);

	beatStepLabel.makeVisible(this);
	beatStepLabel.setDisplayTitle(false);
	beatStepLabel.setFont(juce::Font(font_16, juce::Font::plain).withTypefaceStyle("Regular"));
	beatStepLabel.setJustificationType(juce::Justification::centred);
	beatStepLabel.setText("00:00", dontSendNotification);



	timeLabel.makeVisible(this);
	timeLabel.setDisplayTitle(false);
	timeLabel.setFont(juce::Font(font_11, juce::Font::plain).withTypefaceStyle("Regular"));
	timeLabel.setJustificationType(juce::Justification::centred);
	timeLabel.setText("Time: 00:00:00", dontSendNotification);
	textHandler.setInterceptsMouseClicks(false, true);*/
	statusLabel1.makeVisible(this);
	statusLabel1.setDisplayTitle(false);
	statusLabel1.setFont(juce::Font(font_16, juce::Font::plain).withTypefaceStyle("Regular"));
	statusLabel1.setJustificationType(juce::Justification::centredLeft);
	statusLabel1.setVisible(true);

	statusLabel2.makeVisible(this);
	statusLabel2.setDisplayTitle(false);
	statusLabel2.setFont(juce::Font(font_16, juce::Font::plain).withTypefaceStyle("Regular"));
	statusLabel2.setJustificationType(juce::Justification::centredRight);
	statusLabel2.setVisible(true);

	//addAndMakeVisible(textHandler);
	//textHandler.setScrollingBounds(ui::Rectangle<int>{0, 2, 1024, 22},15.0f);
}

AppStatusbar::~AppStatusbar()
{}

//==============================================================================
void AppStatusbar::paint(juce::Graphics& g)
{

	juce::Rectangle <float>a{ (float)0,(float)0,(float)layout::statusBar.getWidth() ,(float)layout::statusBar.getHeight() };
	Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("status-bar-bg.png"));
	g.drawImage(dropImage, a, RectanglePlacement::centred);

}

void AppStatusbar::resized()
{
	statusLabel1.setBounds(0, 2, 512, 22);
	statusLabel2.setBounds(513, 2, 511, 22);
	//textHandler.setBounds(ui::Rectangle<int>{0, 2, 1024, 22});
	
	/*barLabel.setBounds(700, 2, 180, 22);
	beatStepLabel.setBounds(831, 2, 80, 22);
	timeLabel.setBounds(890, 2, 150, 22);*/
}

void AppStatusbar::setBarDisplayMessage(String& data)
{
	barLabel.makeVisible(this);
	barLabel.setText(data, dontSendNotification);
}

void AppStatusbar::setBeatStepDisplayMessage(String& data)
{
	beatStepLabel.makeVisible(this);
	beatStepLabel.setText(data, dontSendNotification);
}

void AppStatusbar::setDisplayMessage(String& data1, String& data2)
{
	statusLabel1.setText(data1, dontSendNotification);
	statusLabel2.setText(data2, dontSendNotification);
	//textHandler.setAnimatedText(data);
	
}

void AppStatusbar::setTimeMessage(String& data)
{
	timeLabel.makeVisible(this);
	timeLabel.setText(data, dontSendNotification);
}
