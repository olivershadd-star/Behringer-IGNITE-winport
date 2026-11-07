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
	IgniteCopy::IgniteCopy()
	{
		addAndMakeVisible(CopyLabel);
		CopyLabel.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		CopyLabel.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(CopyName);
		CopyName.setEditable(false, true, false);
		CopyName.setDisplayBorder(false);
		CopyName.setTextColour(ui::Theme::Instance().getColour(customGrey9));
		CopyName.setJustificationType(Justification::centred);

		addAndMakeVisible(ctlApply);
		ctlApply.addListener(this);
		ctlApply.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		addAndMakeVisible(ctlCancel);
		ctlCancel.addListener(this);
		ctlCancel.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		addAndMakeVisible(closeBtn);
		closeBtn.addListener(this);

		setSize(widthCopy, heightCopy);

		CopyName.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	IgniteCopy::~IgniteCopy()
	{
	}

	void IgniteCopy::paint(juce::Graphics& g)
	{
		Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-4.png"));
		g.drawImage(dropImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
		g.setColour(ui::Theme::Instance().getColour(customGrey5));
		g.drawHorizontalLine(76, 0, 604);
		g.drawHorizontalLine(186, 0, 604);

		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-form-modal-default.png"));
		Image defaultHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("textbox-form-modal-hover.png"));

		g.drawImage((CopyName.isMouseOver() || CopyName.getFocusState()) ? defaultHoverImage : defaultImage, ui::Rectangle<float>{ 30, 106, 544, 50 }, RectanglePlacement::centred);
	}

	void IgniteCopy::setLabelText(String text)
	{
		CopyName.setText(text + " - Copy", dontSendNotification);
	}

	void IgniteCopy::resized()
	{
		CopyLabel.setBounds(10, 10, 543, 68);
		CopyName.setBounds(30, 106, 544, 50);
		closeBtn.setBounds(548, 25, 25, 25);
		ctlCancel.setBounds(30, 216, 267, 44);
		ctlApply.setBounds(307, 216, 267, 44);
	}

	void IgniteCopy::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		copyCtlKey selectedKey = copyCtlKey::CANCEL;

		if (buttonThatWasClicked == &ctlApply)
		{
			selectedKey = copyCtlKey::COPY;
			ctlApply.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &ctlCancel || buttonThatWasClicked == &closeBtn)
		{
			selectedKey = copyCtlKey::CANCEL;
			if(buttonThatWasClicked == &ctlCancel)
				ctlCancel.setToggleState(false, dontSendNotification);
		}

		if (onButtonPressed)
			onButtonPressed(selectedKey, CopyName.getText());
	}

	bool IgniteCopy::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		if (KeyFocusedItem == CopyViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = CopyViewItemID::COPY_NAME;
		}
		else if (CopyName.isEditing)
			return CopyName.PannelKeyHandler(param, KeyValue);
		else
		{
			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				KeyFocusedItem = (KeyFocusedItem + 1 >= CopyViewItemID::FOCUS_MAX ? (CopyViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				KeyFocusedItem = (KeyFocusedItem - 1 <= CopyViewItemID::NO_FOCUS ? (CopyViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				if (onButtonPressed)
					onButtonPressed(copyCtlKey::CANCEL, CopyName.getText());
				break;
			}
		}
		if (setfocus)
		{
			PannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void IgniteCopy::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (CopyView[KeyFocusedItem])
		{
		case COPY_NAME:
			if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
				this->postCommandMessage(1);
			else
				CopyName.PannelKeyHandler(param, KeyValue);
			break;
		case COPY_CANCEL:
			ctlCancel.FPKeyHandler(isFocuse, param, KeyValue);
			ctlCancel.setState((Button::ButtonState)isFocuse);
			break;
		case COPY_SAVE:
			ctlApply.FPKeyHandler(isFocuse, param, KeyValue);
			ctlApply.setState((Button::ButtonState)isFocuse);
			break;
		default:
			break;
		}
	}

	void IgniteCopy::handleCommandMessage(int id)
	{
		if (id == 1)
			CopyName.editLable();
	}
};
