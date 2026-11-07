/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY.
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
	CommonHelpInfoPopUp::CommonHelpInfoPopUp(const juce::String& Title, int Width, int Height)
	{
		width = Width;
		height = Height;
		title.makeVisible(this);
		infoBtn.makeVisible(this);
		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		title.setJustificationType(Justification::centred);
		title.setText(Title, dontSendNotification);
		setSize(Width, Height);
	}

	CommonHelpInfoPopUp::~CommonHelpInfoPopUp()
	{
		delete dialogWindow;
	}

	void CommonHelpInfoPopUp::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &closeBtn)
		{
			if (auto dw = getCurrentlyModalComponent())
				dw->exitModalState(0);
			CommonUtils::SetUtilsVisiblity(false);
		}
	}

	void CommonHelpInfoPopUp::paint(juce::Graphics& g)
	{
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-3.png"));
		g.drawImage(defaultImage, juce::Rectangle <float>{ (float)0, (float)0, (float)getWidth(), (float)getHeight() }, RectanglePlacement::centred);
		g.setColour(ui::Theme::Instance().getColour(customGrey5));
		g.drawHorizontalLine(65, 0, 605);
	}

	void CommonHelpInfoPopUp::setInfoText(String a)
	{
		int numberOfLines = 1;
		auto fontHeight = 18.0f;
		auto theme = Theme::Instance();
		Font textFont(fontHeight);

		for (int i = 0; i < a.length(); i++)
			if (a[i] == '\n')
				numberOfLines++;

		requiredHeight = int(numberOfLines * (fontHeight + 0.8));
				
		infoLabel.setTextFont(textFont);
		infoLabel.setText(a, dontSendNotification);
		infoLabel.setColour(juce::TextEditor::outlineColourId, theme.getColour(transparentBlack));
		infoLabel.setColour(juce::TextEditor::backgroundColourId, theme.getColour(transparentBlack));
		infoLabel.setColour(juce::TextEditor::textColourId, theme.getColour(neutralWhite));

		const int border = 1;
		auto titleHeight = 65 + border;/* 65 - For Title & Horizontal line */
		availableHeightForViewPort = height - titleHeight - border;
		const int scrollBarThickness = infoViewPort.getScrollBarThickness();

		infoLabel.setSize(width - scrollBarThickness, requiredHeight);
		addAndMakeVisible(infoViewPort);
		infoViewPort.setViewedComponent(&infoLabel, true);
		resized();
	}

	void CommonHelpInfoPopUp::resized()
	{
		infoBtn.setBounds(15, 15, 41, 41);
		title.setBounds(15, 10, getWidth() - 30, 50);
		closeBtn.setBounds(getWidth() - 50, 25, 25, 25);
		infoViewPort.setBounds(0, 66, getWidth(), availableHeightForViewPort);
	}

	void CommonHelpInfoPopUp::show()
	{
		std::function<void(int)> CallbackOnExit;
		view.reset(new CommonViewport());
		CommonUtils::showCustomDialog("Copy", this, [this, CallbackOnExit](int r) {
			if (CallbackOnExit)
				CallbackOnExit(r);

			view.reset();
			}, ui::Rectangle<int>{0, 0, width, height}, false);
	}
};
