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
	IgniteTrackSwap::IgniteTrackSwap()
	{
		swapTitle.makeVisible(this);
		swapTitle.setJustificationType(juce::Justification::centred);

		swapStartLabel.makeVisible(this);
		swapStartLabel.setJustificationType(juce::Justification::centred);

		swapEndLabel.makeVisible(this);
		swapEndLabel.setJustificationType(juce::Justification::centred);

		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		closeBtn.setBounds(548, 30, 30, 20);
		closeBtn.toFront(true);

		addAndMakeVisible(swapStart);
		swapStart.addListener(this);
		swapStart.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		swapStart.setToggleable(true);
		swapStart.setToggleState(true, dontSendNotification);

		addAndMakeVisible(swapEnd);
		swapEnd.addListener(this);
		swapEnd.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		swapEnd.setToggleable(true);
		swapEnd.setTextColour(ui::Theme::Instance().getColour(ui::customOrange));

		swap.makeVisibleAndAddListner(this);
		swap.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		swapBox.items.add(FlexItem(swapStart).withMargin(3).withFlex(3));
		swapBox.items.add(FlexItem(swapEnd).withMargin(3).withFlex(3));

		num0.makeVisibleAndAddListner(this);
		num1.makeVisibleAndAddListner(this);
		num2.makeVisibleAndAddListner(this);
		num3.makeVisibleAndAddListner(this);
		num4.makeVisibleAndAddListner(this);
		num5.makeVisibleAndAddListner(this);
		num6.makeVisibleAndAddListner(this);
		num7.makeVisibleAndAddListner(this);
		num8.makeVisibleAndAddListner(this);
		num9.makeVisibleAndAddListner(this);
		plus.makeVisibleAndAddListner(this);
		minus.makeVisibleAndAddListner(this);
		numDelButton.makeVisibleAndAddListner(this);
		x2Button.makeVisibleAndAddListner(this);
		b2Button.makeVisibleAndAddListner(this);
		swapButton.makeVisibleAndAddListner(this);
		cancelButton.makeVisibleAndAddListner(this);

		num1.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num2.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num3.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num4.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num5.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num6.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num7.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num8.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num9.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		num0.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		plus.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		minus.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		numDelButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		x2Button.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		b2Button.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		swapButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		cancelButton.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		warnPopupPtr = CommonWarningPopUp::getCommonWarningPopupInstance();
	}

	IgniteTrackSwap::~IgniteTrackSwap()
	{
	}

	void IgniteTrackSwap::paint(juce::Graphics& g)
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

		g.drawImage(swapStart.getToggleState() ? ((swapStart.isMouseOver() || swapStart.isFocused) ? activeHoverImage : activeImage) : ((swapStart.isMouseOver() || swapStart.isFocused) ? defaultHoverImage : defaultImage), ui::Rectangle<float>{30, 146, 240, 50}, RectanglePlacement::centred);
		g.drawImage(swapEnd.getToggleState() ? ((swapEnd.isMouseOver() || swapEnd.isFocused) ? activeHoverImage : activeImage) : ((swapEnd.isMouseOver() || swapEnd.isFocused) ? defaultHoverImage : defaultImage), ui::Rectangle<float>{ 334, 146, 240, 50 }, RectanglePlacement::centred);

		defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("ico-swap-default.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("ico-swap-hover.png"));

		g.drawImage(swap.isMouseOver() ? activeImage : defaultImage, ui::Rectangle<float>{ 290, 159, 24, 24 }, RectanglePlacement::centred);
	}

	void IgniteTrackSwap::resized()
	{
		swapTitle.setBounds(30, 10, 544, heightNumpadTitle);
		swapStartLabel.setBounds(30, 118, 240, 18);
		swapEndLabel.setBounds(334, 118, 240, 18);
		swapStart.setBounds(30, 146, 240, 50);
		swapEnd.setBounds(334, 146, 240, 50);
		swap.setBounds(290, 159, 24, 24);
		num7.setBounds(30, 226, 133, 44);
		num8.setBounds(167, 226, 133, 44);
		num9.setBounds(304, 226, 133, 44);
		numDelButton.setBounds(441, 226, 133, 44);
		num4.setBounds(30, 274, 133, 44);
		num5.setBounds(167, 274, 133, 44);
		num6.setBounds(304, 274, 133, 44);
		plus.setBounds(441, 274, 133, 44);
		num1.setBounds(30, 322, 133, 44);
		num2.setBounds(167, 322, 133, 44);
		num3.setBounds(304, 322, 133, 44);
		minus.setBounds(441, 322, 133, 44);
		num0.setBounds(30, 370, 178, 44);
		b2Button.setBounds(212, 370, 178, 44);
		x2Button.setBounds(394, 370, 178, 44);
		cancelButton.setBounds(30, 459, 267, 44);
		swapButton.setBounds(305, 459, 267, 44);
	}

	void IgniteTrackSwap::setDefaultEditTrack(int value1, int value2)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "value1: " + String(value1) + "::" + "value2: " + String(value2));
		lastEnteredValue1 = value1;
		lastEnteredValue2 = value2;
		swapStart.setButtonText((String)(value1 < 1 ? 1 : value1));
		swapEnd.setButtonText((String)(value2 < 1 ? 1 : value2));
		refreshDisplay(lastEnteredValue1, lastEnteredValue2);
	};

	void IgniteTrackSwap::buttonClicked(juce::Button* button)
	{
		swapCtlKey selectedKey = swapCtlKey::CANCEL;
		if (button == &swapStart)
		{
			swapEnd.setToggleState(!swapStart.getToggleState(), dontSendNotification);
			swapEnd.setTextColour(ui::Theme::Instance().getColour(ui::customOrange));
			isMinusPressed = false;
			isPlusPressed = false;
			return;
		}

		if (button == &swapEnd)
		{
			swapStart.setToggleState(!swapEnd.getToggleState(), dontSendNotification);
			swapStart.setTextColour(ui::Theme::Instance().getColour(ui::customOrange));
			isMinusPressed = false;
			isPlusPressed = false;
			return;
		}

		// Check if APPLY or CANCEL button pressed...
		if (button == &swapButton || button == &cancelButton || button == &closeBtn)
		{
			if(button == &swapButton)
				swapButton.setToggleState(false, dontSendNotification);
			else if (button == &cancelButton)
				cancelButton.setToggleState(false, dontSendNotification);

			if (isAnyInput && (button == &swapButton))
			{
				if ((intermidentValue1 > 0) && (intermidentValue2 > 0))
				{
					selectedKey = swapCtlKey::SWAP;
					lastEnteredValue1 = intermidentValue1;
					lastEnteredValue2 = intermidentValue2;

					if (onButtonPressed)
						onButtonPressed(selectedKey, lastEnteredValue1, lastEnteredValue2);
				}
				else
				{
					warnPopupPtr->close();
					warnPopupPtr->setWarningText("Track number must be greater than zero");
					warnPopupPtr->show();
					warnPopupPtr->onSelectionChanged = [this](int r)
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};

					return;
				}
			}
			else if (button == &cancelButton || button == &closeBtn || button == &swapButton)
			{
				if (button == &swapButton)
					selectedKey = swapCtlKey::SWAP;

				intermidentValue1 = lastEnteredValue1;
				intermidentValue2 = lastEnteredValue2;

				if (onButtonPressed)
					onButtonPressed(selectedKey, lastEnteredValue1, lastEnteredValue2);
			}
		}
		else
			isAnyInput = true;

		if (swapStart.getToggleState())
		{
			swapStartIsActive = true;
			swapEndIsActive = false;
		}
		else if (swapEnd.getToggleState())
		{
			swapEndIsActive = true;
			swapStartIsActive = false;
		}

		// Process other buttons...
		if (button == &num1)
			handleArithmetic(isPlusPressed, isMinusPressed, 1);
		else if (button == &num2)
			handleArithmetic(isPlusPressed, isMinusPressed, 2);
		else if (button == &num3)
			handleArithmetic(isPlusPressed, isMinusPressed, 3);
		else if (button == &num4)
			handleArithmetic(isPlusPressed, isMinusPressed, 4);
		else if (button == &num5)
			handleArithmetic(isPlusPressed, isMinusPressed, 5);
		else if (button == &num6)
			handleArithmetic(isPlusPressed, isMinusPressed, 6);
		else if (button == &num7)
			handleArithmetic(isPlusPressed, isMinusPressed, 7);
		else if (button == &num8)
			handleArithmetic(isPlusPressed, isMinusPressed, 8);
		else if (button == &num9)
			handleArithmetic(isPlusPressed, isMinusPressed, 9);
		else if (button == &num0)
		{
			if (!isPlusPressed && !isMinusPressed)
			{
				if (swapStartIsActive)
					intermidentValue1 = intermidentValue1 * 10;
				if (swapEndIsActive)
					intermidentValue2 = intermidentValue2 * 10;
			}
		}
		else if (button == &plus)
		{
			isPlusPressed = true;
			handleArithmetic(isPlusPressed, isMinusPressed, 1);
		}
		else if (button == &minus)
		{
			isMinusPressed = true;
			handleArithmetic(isPlusPressed, isMinusPressed, 1);
		}
		else if (button == &numDelButton)
		{
			if (swapStartIsActive)
				intermidentValue1 /= 10;
			if (swapEndIsActive)
				intermidentValue2 /= 10;

			isMinusPressed = false;
			isPlusPressed = false;
		}
		else if (button == &b2Button)
		{
			if (swapStartIsActive)
				intermidentValue1 /= 2;
			if (swapEndIsActive)
				intermidentValue2 /= 2;
			isMinusPressed = false;
			isPlusPressed = false;
		}
		else if (button == &x2Button)
		{
			if (swapStartIsActive)
				intermidentValue1 *= 2;
			if (swapEndIsActive)
				intermidentValue2 *= 2;
			isMinusPressed = false;
			isPlusPressed = false;
		}

		refreshDisplay(intermidentValue1, intermidentValue2);
	}


	void IgniteTrackSwap::handleArithmetic(bool isPlus, bool isMinus, int value)
	{
		if (isPlus)
			swapStartIsActive ? intermidentValue1 += value : intermidentValue2 += value;
		else if (isMinus)
			swapStartIsActive ? intermidentValue1 -= value : intermidentValue2 -= value;
		else
			swapStartIsActive ? intermidentValue1 = intermidentValue1 * 10 + value : intermidentValue2 = intermidentValue2 * 10 + value;

		isMinusPressed = false;
		isPlusPressed = false;
	}

	void IgniteTrackSwap::refreshDisplay(int value1, int value2)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "value1: " + String(value1) + "::" + "value2: " + String(value2));
		auto numberOfTracksIndex = (int)IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::NUM_TRACKS_INDEX);
		intermidentValue1 = value1 > (numberOfTracksIndex * 16) ? (numberOfTracksIndex * 16) : value1;
		intermidentValue2 = value2 > (numberOfTracksIndex * 16) ? (numberOfTracksIndex * 16) : value2;

		if (swapStartIsActive)
			swapStart.setButtonText((String)(intermidentValue1 < 1 ? 1 : intermidentValue1));
		if (swapEndIsActive)
			swapEnd.setButtonText((String)(intermidentValue2 < 1 ? 1 : intermidentValue2));
	}

	bool IgniteTrackSwap::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;

		if (warnPopupPtr != nullptr && warnPopupPtr->IsEditing())
			return warnPopupPtr->FPKeyHandler(true, param, KeyValue);

		if(param == (paramId_t)FrontPannelParam::paramKey_PLUS_NAV)
			return plus.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
		else if(param == (paramId_t)FrontPannelParam::paramKey_MINUS_NAV)
			return minus.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);

		if (KeyFocusedItem == TrackSwapViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = TrackSwapViewItemID::SWAP_TRACK_SOURCE;
		}
		else
		{
			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				KeyFocusedItem = (KeyFocusedItem + 1 >= TrackSwapViewItemID::FOCUS_MAX ? (TrackSwapViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				KeyFocusedItem = (KeyFocusedItem - 1 <= TrackSwapViewItemID::NO_FOCUS ? (TrackSwapViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				if (onButtonPressed)
					onButtonPressed(swapCtlKey::CANCEL, lastEnteredValue1, lastEnteredValue2);
				break;
			}
		}
		if (setfocus)
		{
			PannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void IgniteTrackSwap::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (TrackSwapView[KeyFocusedItem])
		{
		case SWAP_TRACK_SOURCE:
			swapStart.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SWAP_TRACK_DEST:
			swapEnd.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		/*case KEY_0:
			num0.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_1:
			num1.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_2:
			num2.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_3:
			num3.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_4:
			num4.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_5:
			num5.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_6:
			num6.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_7:
			num7.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_8:
			num8.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_9:
			num9.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_PLUS:
			plus.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_MINUS:
			minus.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_X2:
			x2Button.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_B2:
			b2Button.FPKeyHandler(isFocuse, param, KeyValue);
			break;*/
		case KEY_CANCEL:
			cancelButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case KEY_SWAP:
			swapButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		/*case KEY_DEL:
			numDelButton.FPKeyHandler(isFocuse, param, KeyValue);
			break;*/
		default:
			break;
		}
		repaint();
	}
}
