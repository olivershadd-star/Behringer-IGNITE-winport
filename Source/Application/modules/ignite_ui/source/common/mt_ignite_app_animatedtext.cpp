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


 //==============================================================================
namespace ui
{
	IgniteAnimatdText::IgniteAnimatdText()
	{
		TextLabel.makeVisible(this);
		TextLabel.setDisplayTitle(false);
		TextLabel.setFont(juce::Font(font_16, juce::Font::plain).withTypefaceStyle("Regular"));
		TextLabel.setJustificationType(juce::Justification::left);
	}

	void IgniteAnimatdText::timerCallback()
	{
		Font a((float)(font));
		auto l = a.getStringWidth(text);
		
		if (l > b.getWidth())
		{
			if ((scrollingbounds.getX()) != (reqWidth/2*-1))
			{
				scrollingbounds.setX(scrollingbounds.getX() - 1);
				TextLabel.setBounds(scrollingbounds);

			}
			else
			{
				scrollingbounds.setX(b.getX());
			}
		}
	}

	void IgniteAnimatdText::setScrollingBounds(ui::Rectangle<int> a,float f)
	{
		b = a;
		scrollingbounds = a;
		scrollingbounds.setX(b.getX()-(reqWidth/2));
		scrollingbounds.setWidth(reqWidth);
		font = f;
	}

	void IgniteAnimatdText::startAnimate()
	{
		startTimer(50);
	}

	void IgniteAnimatdText::paint(juce::Graphics& g)
	{

	}
	void IgniteAnimatdText::resized()
	{

	}

	void IgniteAnimatdText::setAnimatedText(String s) {
		text = s + "        ";
		Font f((float)(font));
		reqWidth = (f.getStringWidth(text)) * 2;
		TextLabel.setText(text + text, dontSendNotification);
		scrollingbounds.setWidth(reqWidth );
		if(!isTextRotating)
			scrollingbounds.setX(b.getX());
		if ((reqWidth )/2 > b.getWidth())
		{
			startAnimate();
			isTextRotating = true;
		}
		else
		{
			stopTimer();
			TextLabel.setText(s,dontSendNotification);
			TextLabel.setBounds(b);
			isTextRotating = false;
		}
	}
};
