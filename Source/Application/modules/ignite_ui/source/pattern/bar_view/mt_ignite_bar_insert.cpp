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
	IgniteBarInsert::IgniteBarInsert()
	{
		insertTitle.makeVisible(this);
		insertTitle.setJustificationType(juce::Justification::centred);

		insertLabel.makeVisible(this);
		insertLabel.setJustificationType(juce::Justification::centred);

		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		closeBtn.setBounds(548, 30, 30, 20);
		closeBtn.toFront(true);

		addAndMakeVisible(barNumberButton);
		barNumberButton.addListener(this);
		barNumberButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		for (int i = 0; i < barNumberDefault.size(); i++)
		{
			auto option = new CommonImageButton{ "NUM" + String(i + 1) ,barNumberDefault[i],barNumberActive[i],barNumberDefaultHover[i]};
			option->makeVisibleAndAddListner(this);
			option->setLookAndFeel(ImageButtonLookandFeel::getLnf());
			option->sethoverImages(barNumberDefaultHover[i], barNumberActiveHover[i], "");
			options.add(option);
		}

		insertButton.makeVisibleAndAddListner(this);
		cancelButton.makeVisibleAndAddListner(this);
		insertButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		cancelButton.setLookAndFeel(ImageButtonLookandFeel::getLnf());
	}

	IgniteBarInsert::~IgniteBarInsert()
	{
	}

	void IgniteBarInsert::setBarIndex(int barIndex)
	{
		barNumberButton.setButtonText("1");
		numberOfBars = barIndex;

		for (int i = 0; i < barIndex; i++)
		{
			options[i]->setToggleState(true, dontSendNotification);
		}

		for (int i = barIndex; i < barNumberDefault.size(); i++)
		{
			options[i]->setToggleState(false, dontSendNotification);
		}
	}

	void IgniteBarInsert::paint(juce::Graphics& g)
	{
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-1.png"));
		g.drawImage(defaultImage, juce::Rectangle <float>{ (float)0, (float)0, 604, 533 }, RectanglePlacement::centred);
		g.setColour(ui::Theme::Instance().getColour(customGrey5));
		g.drawLine(0, 78, 604, 78);
		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-form-modal-default.png"));
		Image activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-form-modal-active.png"));
		g.drawImage((barNumberButton.isMouseOver() || barNumberButton.isFocused) ? activeImage : defaultImage, ui::Rectangle<float>{ 30, 146, 544, 50 }, RectanglePlacement::centred);
		g.drawLine(0, 434, 604, 434);
	}

	void IgniteBarInsert::resized()
	{
		insertTitle.setBounds(30, 10, 544, heightNumpadTitle);
		insertLabel.setBounds(30, 118, 544, 18);
		barNumberButton.setBounds(30, 146, 544, 50);
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
		insertButton.setBounds(305, 459, 267, 44);
	}

	void IgniteBarInsert::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		insertCtlKey selectedKey = insertCtlKey::CANCEL;

		for (int i = 0; i < numberOfBars; i++)
		{
			if (options[i] == buttonThatWasClicked)
			{

				barNumberButton.setButtonText(String(i + 1));
				options[i]->setToggleState(true, dontSendNotification);
				return;
			}
		}

		if (buttonThatWasClicked == &insertButton)
		{
			insertButton.setToggleState(false, dontSendNotification);
			selectedKey = insertCtlKey::INSERT;
			if (onButtonPressed)
				onButtonPressed(selectedKey, barNumberButton.getButtonText().getIntValue());
		}
		else if (buttonThatWasClicked == &cancelButton || buttonThatWasClicked == &closeBtn)
		{
			cancelButton.setToggleState(false, dontSendNotification);
			selectedKey = insertCtlKey::CANCEL;
			if (onButtonPressed)
				onButtonPressed(selectedKey, barNumberButton.getButtonText().getIntValue());
		}
		else if (buttonThatWasClicked == options[0])
		{
			barNumberButton.setButtonText("1");
			options[0]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[1])
		{
			barNumberButton.setButtonText("2");
			options[1]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[2])
		{
			barNumberButton.setButtonText("3");
			options[2]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[3])
		{
			barNumberButton.setButtonText("4");
			options[3]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[4])
		{
			barNumberButton.setButtonText("5");
			options[4]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[5])
		{
			barNumberButton.setButtonText("6");
			options[5]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[6])
		{
			barNumberButton.setButtonText("7");
			options[6]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[7])
		{
			barNumberButton.setButtonText("8");
			options[7]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[8])
		{
			barNumberButton.setButtonText("9");
			options[8]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[9])
		{
			barNumberButton.setButtonText("10");
			options[9]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[10])
		{
			barNumberButton.setButtonText("11");
			options[10]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[11])
		{
			barNumberButton.setButtonText("12");
			options[11]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[12])
		{
			barNumberButton.setButtonText("13");
			options[12]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[13])
		{
			barNumberButton.setButtonText("14");
			options[13]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[14])
		{
			barNumberButton.setButtonText("15");
			options[14]->setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == options[15])
		{
			barNumberButton.setButtonText("16");
			options[15]->setToggleState(false, dontSendNotification);
		}
	}

	bool IgniteBarInsert::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		bool setfocus = true;
		if (keyFocusedItem == barInsertViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			keyFocusedItem = barInsertViewItemID::KEY_INSERT_POSITION;
		}
		else
		{
			pannelSendKey(false, param, keyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				keyFocusedItem = (keyFocusedItem + 1 >= barInsertViewItemID::FOCUS_MAX ? (barInsertViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				keyFocusedItem = (keyFocusedItem - 1 <= barInsertViewItemID::NO_FOCUS ? (barInsertViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				if (onButtonPressed)
					onButtonPressed(insertCtlKey::CANCEL, barNumberButton.getButtonText().getIntValue());
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

	void IgniteBarInsert::pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue)
	{
		switch (barInsertView[keyFocusedItem])
		{
		case KEY_INSERT_POSITION:
			barNumberButton.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case KEY_CANCEL:
			cancelButton.FPKeyHandler(isFocuse, param, keyValue);
			break;
		case KEY_INSERT:
			insertButton.FPKeyHandler(isFocuse, param, keyValue);
			break;
		default:
			break;
		}
		repaint();
	}

	void IgniteBarInsert::handleCommandMessage(int cmdid)
	{
		buttonClicked(options[cmdid]);
	}
}
