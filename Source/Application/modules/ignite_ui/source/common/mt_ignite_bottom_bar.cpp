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

namespace ui
{
	IgniteBottomBar::IgniteBottomBar()
	{
		volume.makeVisible(this);
		swing.makeVisible(this);
		tempo.makeVisible(this);
		quantize.makeVisible(this);
		loop.makeVisible(this);
		bbs.makeVisible(this);

		volume.setDisplayTitleAndBorder(true);
		swing.setDisplayTitleAndBorder(true);
		tempo.setDisplayTitleAndBorder(true);
		quantize.setDisplayTitleAndBorder(true);
		bbs.setDisplayTitleAndBorder(true);
		loop.setDisplayBorder(true);

		volume.setJustificationType(juce::Justification::centred);
		swing.setJustificationType(juce::Justification::centred);
		tempo.setJustificationType(juce::Justification::centred);
		quantize.setJustificationType(juce::Justification::centred);
		bbs.setJustificationType(juce::Justification::centred);
		loop.setJustificationType(juce::Justification::centred);

		loop.setFont(juce::Font(font_11, juce::Font::plain).withTypefaceStyle("Regular"));
		loop.setJustificationType(juce::Justification::centred);

		//	box.items.add(FlexItem(swing).withMargin(1).withFlex(1));
		//	box.items.add(FlexItem(tempo).withMargin(1).withFlex(1));
		box.items.add(FlexItem(loop).withMargin(1).withFlex(3));
		//	box.items.add(FlexItem(volume).withMargin(1).withFlex(1));
		//	box.items.add(FlexItem(bbs).withMargin(1).withFlex(2));
	}

	IgniteBottomBar::~IgniteBottomBar()
	{}

	void IgniteBottomBar::paint(juce::Graphics& g)
	{
		g.setColour(ui::Theme::Instance().getColour(neutralBlack));
		g.fillAll();
	}

	void IgniteBottomBar::resized()
	{
		box.performLayout(getLocalBounds().removeFromTop(30).removeFromBottom(30));
	}

	void IgniteBottomBar::updateOneSongData(int item_id, float value)
	{
		switch (item_id)
		{
		case (int)mt::Ignite::songsDataIndex::SWING:			swing.setText(String(value), juce::dontSendNotification); break;
		case (int)mt::Ignite::songsDataIndex::TEMPO:			tempo.setText(String(value), juce::dontSendNotification); break;
		default: break;
		}
	}

	void IgniteBottomBar::updateSongData(float dtempo, float dswing)
	{
		tempo.setText(String(dtempo), dontSendNotification);
		swing.setText(String(dswing), dontSendNotification);
	}
	///
};
