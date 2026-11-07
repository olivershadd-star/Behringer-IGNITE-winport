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
namespace ui
{
	AppDnp::AppDnp()
	{
		addAndMakeVisible(labelDnp);
		labelDnp.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		labelDnp.setJustificationType(juce::Justification::centred);
		labelDnp.setEditable(false, false, false);
		labelDnp.setColour(juce::TextEditor::textColourId, juce::Colours::purple);
		labelDnp.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));
	}

	AppDnp::~AppDnp()
	{
	}

	void AppDnp::paint(juce::Graphics& g)
	{
		if (dropImage != juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("null.png")))
		{
			auto a = getLocalBounds().toFloat();
			g.drawImage(dropImage, a, RectanglePlacement::centred);
		}
		else
			g.fillAll(ui::Theme::Instance().getColour(neutralGrey2));
	}

	void AppDnp::resized()
	{
		labelDnp.setBounds(getLocalBounds());
	}

	void AppDnp::setDisplayMessage(String data)
	{
		labelDnp.setText(data, dontSendNotification);
	}
};
