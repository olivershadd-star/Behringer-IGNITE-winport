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

	IgniteBarCopy::IgniteBarCopy()
	{
		copyTitle.makeVisible(this);
		copyTitle.setJustificationType(juce::Justification::centred);

		CopyFromLabel.makeVisible(this);
		CopyFromLabel.setJustificationType(juce::Justification::centred);

		CopyToLabel.makeVisible(this);
		CopyToLabel.setJustificationType(juce::Justification::centred);

		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		closeBtn.setBounds(548, 30, 30, 20);
		closeBtn.toFront(true);

		addAndMakeVisible(sourceBarNumber);
		sourceBarNumber.addListener(this);
		sourceBarNumber.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		sourceBarNumber.setToggleable(true);
		sourceBarNumber.setToggleState(true, dontSendNotification);

		addAndMakeVisible(destinationBarNumber);
		destinationBarNumber.addListener(this);
		destinationBarNumber.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		destinationBarNumber.setToggleable(true);

		copy.makeVisibleAndAddListner(this);
		copy.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		for (int i = 0; i < barNumberDefault.size(); i++)
		{
			auto option = new CommonImageButton{ "NUM" + String(i + 1) ,barNumberDefault[i],barNumberActive[i],barNumberDefaultHover[i]};
			option->makeVisibleAndAddListner(this);
			option->setLookAndFeel(ImageButtonLookandFeel::getLnf());
			option->setDisableImage(barNumberDisabled[i]);
			option->sethoverImages(barNumberDefaultHover[i], barNumberActiveHover[i], barNumberDisabledHover[i]);
			options.add(option);
		}

		copyButton.makeVisibleAndAddListner(this);
		copyButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		cancelButton.makeVisibleAndAddListner(this);
		cancelButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	}

	IgniteBarCopy::~IgniteBarCopy()
	{
	}

	void IgniteBarCopy::setMaxBarIndex(int maxBarNumber)
	{
		sourceBarNumber.setButtonText("1");
		destinationBarNumber.setButtonText("1");
		if (sourceBarNumber.getToggleState())
		{
			refreshNumpad(maxBarNumber, ui::Theme::Instance().getColour(ui::customOrange), false);
			destinationBarNumber.setTextColour(ui::Theme::Instance().getColour(ui::customOrange));
		}
		else
		{
			refreshNumpad(maxBarNumber, Theme::Instance().getColour(neutralWhite), true);
			sourceBarNumber.setTextColour(ui::Theme::Instance().getColour(ui::customOrange));
		}
		numberOfBars = maxBarNumber;
	}

	void IgniteBarCopy::refreshNumpad(int barIndex, Colour textColour, bool isEnable)
	{
		for (int i = 0; i < barIndex; i++)
		{
			options[i]->setEnabled(true);
			options[i]->setToggleState(true, dontSendNotification);
		}

		for (int i = barIndex; i < barNumberDefault.size(); i++)
		{
			options[i]->setEnabled(isEnable);
			options[i]->setToggleState(false, dontSendNotification);
		}
	}

	void IgniteBarCopy::paint(juce::Graphics& g)
	{
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-1.png"));
		g.drawImage(defaultImage, juce::Rectangle <float>{ (float)0, (float)0, 604, 533 }, RectanglePlacement::centred);
		g.setColour(ui::Theme::Instance().getColour(customGrey5));
		g.drawLine(0, 78, 604, 78);
		g.drawLine(0, 434, 604, 434);

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-input-default.png"));
		Image defaultHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-input-default-hover.png"));
		Image activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-input-active.png"));
		Image activeHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-input-active-hover.png"));

		g.drawImage(sourceBarNumber.getToggleState() ? ((sourceBarNumber.isMouseOver() || sourceBarNumber.isFocused) ? activeHoverImage : activeImage) : ((sourceBarNumber.isMouseOver() || sourceBarNumber.isFocused) ? defaultHoverImage : defaultImage), ui::Rectangle<float>{30, 146, 240, 50}, RectanglePlacement::centred);
		g.drawImage(destinationBarNumber.getToggleState() ? ((destinationBarNumber.isMouseOver() || destinationBarNumber.isFocused) ? activeHoverImage : activeImage) : ((destinationBarNumber.isMouseOver() || destinationBarNumber.isFocused) ? defaultHoverImage : defaultImage), ui::Rectangle<float>{ 334, 146, 240, 50 }, RectanglePlacement::centred);

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("ico-swap-default.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("ico-swap-hover.png"));

		g.drawImage(copy.isMouseOver() ? activeImage : defaultImage, ui::Rectangle<float>{ 290, 159, 24, 24 }, RectanglePlacement::centred);
	}

	void IgniteBarCopy::resized()
	{
		copyTitle.setBounds(30, 10, 544, heightNumpadTitle);
		CopyFromLabel.setBounds(30, 118, 240, 18);
		CopyToLabel.setBounds(334, 118, 240, 18);
		sourceBarNumber.setBounds(30, 146, 240, 50);
		destinationBarNumber.setBounds(334, 146, 240, 50);
		copy.setBounds(290, 159, 24, 24);
		(*options[0]).setBounds(30, 226, 133, 44);
		(*options[1]).setBounds(167, 226, 133, 44);
		(*options[2]).setBounds(304, 226, 133, 44);
		(*options[3]).setBounds(441, 226, 133, 44);
		(*options[4]).setBounds(30, 274, 133, 44);
		(*options[5]).setBounds(167, 274, 133, 44);
		(*options[6]).setBounds(304, 274, 133, 44);
		(*options[7]).setBounds(441, 274, 133, 44);
		(*options[8]).setBounds(30, 322, 133, 44);
		(*options[9]).setBounds(167, 322, 133, 44);
		(*options[10]).setBounds(304, 322, 133, 44);
		(*options[11]).setBounds(441, 322, 133, 44);
		(*options[12]).setBounds(30, 370, 133, 44);
		(*options[13]).setBounds(167, 370, 133, 44);
		(*options[14]).setBounds(304, 370, 133, 44);
		(*options[15]).setBounds(441, 370, 133, 44);
		cancelButton.setBounds(30, 459, 267, 44);
		copyButton.setBounds(305, 459, 267, 44);
	}

	void IgniteBarCopy::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		copyBarCtlKey selectedKey = copyBarCtlKey::CANCEL;

		for (int i = 0; i < numberOfBars; i++)
		{
			if (options[i] == buttonThatWasClicked)
			{
				if (sourceBarNumber.getToggleState())
					sourceBarNumber.setButtonText(String(i + 1));
				if (destinationBarNumber.getToggleState())
					destinationBarNumber.setButtonText(String(i + 1));
				options[i]->setToggleState(true, dontSendNotification);
				return;
			}
		}

		if (buttonThatWasClicked == &sourceBarNumber)
		{
			destinationBarNumber.setToggleState(!sourceBarNumber.getToggleState(), dontSendNotification);
			destinationBarNumber.setTextColour(ui::Theme::Instance().getColour(ui::customOrange));
			refreshNumpad(numberOfBars, ui::Theme::Instance().getColour(ui::customOrange), false);
			return;
		}

		if (buttonThatWasClicked == &destinationBarNumber)
		{
			sourceBarNumber.setToggleState(!destinationBarNumber.getToggleState(), dontSendNotification);
			sourceBarNumber.setTextColour(ui::Theme::Instance().getColour(ui::customOrange));
			refreshNumpad(numberOfBars, Theme::Instance().getColour(neutralWhite), true);
			return;
		}

		if (buttonThatWasClicked == &copyButton || buttonThatWasClicked == &cancelButton || buttonThatWasClicked == &closeBtn)
		{
			if (buttonThatWasClicked == &copyButton)
			{
				copyButton.setToggleState(false, dontSendNotification);
				selectedKey = copyBarCtlKey::COPY;
				if (onButtonPressed)
					onButtonPressed(selectedKey, sourceBarNumber.getButtonText().getIntValue(), destinationBarNumber.getButtonText().getIntValue());
			}
			else if (buttonThatWasClicked == &cancelButton || buttonThatWasClicked == &closeBtn)
			{
				cancelButton.setToggleState(false, dontSendNotification);
				selectedKey = copyBarCtlKey::CANCEL;
				if (onButtonPressed)
					onButtonPressed(selectedKey, sourceBarNumber.getButtonText().getIntValue(), destinationBarNumber.getButtonText().getIntValue());
			}
		}
		else
		{
			if (sourceBarNumber.getToggleState())
			{
				sourceBarNumberIsActive = true;
				destinationBarNumberIsActive = false;
			}

			if (destinationBarNumber.getToggleState())
			{
				destinationBarNumberIsActive = true;
				sourceBarNumberIsActive = false;
			}

			if (buttonThatWasClicked == options[0])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("1");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("1");
				options[0]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[1])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("2");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("2");
				options[1]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[2])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("3");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("3");
				options[2]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[3])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("4");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("4");
				options[3]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[4])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("5");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("5");
				options[4]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[5])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("6");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("6");
				options[5]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[6])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("7");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("7");
				options[6]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[7])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("8");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("8");
				options[7]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[8])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("9");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("9");
				options[8]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[9])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("10");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("10");
				options[9]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[10])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("11");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("11");
				options[10]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[11])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("12");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("12");
				options[11]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[12])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("13");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("13");
				options[12]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[13])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("14");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("14");
				options[13]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[14])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("15");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("15");
				options[14]->setToggleState(false, dontSendNotification);
			}
			else if (buttonThatWasClicked == options[15])
			{
				if (sourceBarNumberIsActive)
					sourceBarNumber.setButtonText("16");
				if (destinationBarNumberIsActive)
					destinationBarNumber.setButtonText("16");
				options[15]->setToggleState(false, dontSendNotification);
			}
		}
	}

	bool IgniteBarCopy::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		bool setfocus = true;
		if (keyFocusedItem == barCopyViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			keyFocusedItem = barCopyViewItemID::BAR_COPY_SOURCE;
		}
		else
		{
			pannelSendKey(false, param, keyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				keyFocusedItem = (keyFocusedItem + 1 >= barCopyViewItemID::FOCUS_MAX ? (barCopyViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				keyFocusedItem = (keyFocusedItem - 1 <= barCopyViewItemID::NO_FOCUS ? (barCopyViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				if (onButtonPressed)
					onButtonPressed(copyBarCtlKey::CANCEL, sourceBarNumber.getButtonText().getIntValue(), destinationBarNumber.getButtonText().getIntValue());
				break;
			case FrontPannelParam::paramKey_TRACKSEL1:
			case FrontPannelParam::paramKey_TRACKSEL2:
			case FrontPannelParam::paramKey_TRACKSEL3:
			case FrontPannelParam::paramKey_TRACKSEL4:
			case FrontPannelParam::paramKey_TRACKSEL5:
			case FrontPannelParam::paramKey_TRACKSEL6:
			case FrontPannelParam::paramKey_TRACKSEL7:
			case FrontPannelParam::paramKey_TRACKSEL8:
			case FrontPannelParam::paramKey_TRACKSEL9:
			case FrontPannelParam::paramKey_TRACKSEL10:
			case FrontPannelParam::paramKey_TRACKSEL11:
			case FrontPannelParam::paramKey_TRACKSEL12:
			case FrontPannelParam::paramKey_TRACKSEL13:
			case FrontPannelParam::paramKey_TRACKSEL14:
			case FrontPannelParam::paramKey_TRACKSEL15:
			case FrontPannelParam::paramKey_TRACKSEL16:
				this->postCommandMessage(param - (paramId_t)FrontPannelParam::paramKey_TRACKSEL1);
				break;
			}
		}
		if (setfocus)
		{
			pannelSendKey(true, param, keyValue);
		}
		return true;
	}

	void IgniteBarCopy::pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue)
	{
		switch (barCopyView[keyFocusedItem])
		{
		case BAR_COPY_SOURCE:
			sourceBarNumber.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case BAR_COPY_DEST:
			destinationBarNumber.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case KEY_CANCEL:
			cancelButton.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case KEY_SWAP:
			copyButton.FPKeyHandler(isFocuse, param, keyValue);
			break;
		default:
			break;
		}
		repaint();
	}

	void IgniteBarCopy::handleCommandMessage(int cmdid)
	{
		buttonClicked(options[cmdid]);
	}
}
