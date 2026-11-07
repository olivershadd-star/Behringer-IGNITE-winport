/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
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

	template<int blurShift, bool enhanceContrast = false>
	static inline void blurImage(juce::Image& img)
	{
		if (!img.isValid() || !img.getWidth() || !img.getHeight()) return;
		img = img.convertedToFormat(juce::Image::ARGB);
		juce::Image::BitmapData bm(img, 0, 0, img.getWidth(), img.getHeight(), juce::Image::BitmapData::readWrite);
		int                     h = img.getHeight();
		int                     w = img.getWidth();

		auto pxBlur = [](int p, int& s, int blrShift, bool enhContrast = false) -> int {
			int px = p << 16;
			s += (px - s) >> blrShift;
			if (enhContrast)
			{
				px = s >> 8;
				px = ((((98304 - px) >> 7) * px >> 16) * px >> 16); // sine clamp
				return juce::jlimit(0, 255, px);
			}
			return s >> 16;
		};

		for (int y = 0; y < h; y++)
		{
			for (int c = 0; c < 4; c++)
			{
				uint8_t* p = bm.getLinePointer(y) + c;
				int      s = p[0] << 16;
				for (int x = 0; x < w; x++, p += 4)
					p[0] = (uint8_t)pxBlur(int(p[0]), s, blurShift);

				p -= 4;
				for (int x = 0; x < w; x++, p -= 4)
					p[0] = (uint8_t)pxBlur(int(p[0]), s, blurShift);
			}
		}

		for (int x = 0; x < w; x++)
		{
			for (int c = 0; c < 4; c++)
			{
				uint8_t* p = bm.getPixelPointer(x, 0) + c;
				int      incr = int(bm.getPixelPointer(x, 1) - bm.getPixelPointer(x, 0));
				int      s = p[0] << 16;
				for (int y = 0; y < h; y++, p += incr)
					p[0] = (uint8_t)pxBlur(int(p[0]), s, blurShift);

				p -= incr;
				for (int y = 0; y < h; y++, p -= incr)
					p[0] = (uint8_t)pxBlur(int(p[0]), s, blurShift, enhanceContrast);
			}
		}
	} // blurImage
	CommonKeyPad::CommonKeyPad(const String& Name)
	{
		isToggle = false;
		maxLimit = 30;

		setLookAndFeel(CommonLooknFeel::getLnf());

		keyPadValue.makeVisible(this);
		keyPadValue.setEditable(false);
		keyPadValue.addListener(this);
		keyPadValue.setJustificationType(juce::Justification::centred);
		keyPadValue.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemGreen).withAlpha((float)0.4));
		keyPadValue.setBackgroundColour(ui::Theme::Instance().getColour(ui::neutralWhite));
		keyPadValue.setTextColour(ui::Theme::Instance().getColour(ui::neutralBlack));

		keyQ.makeVisibleAndAddListner(this);
		keyQ.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyW.makeVisibleAndAddListner(this);
		keyW.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyE.makeVisibleAndAddListner(this);
		keyE.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyR.makeVisibleAndAddListner(this);
		keyR.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyT.makeVisibleAndAddListner(this);
		keyT.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyY.makeVisibleAndAddListner(this);
		keyY.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyU.makeVisibleAndAddListner(this);
		keyU.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyI.makeVisibleAndAddListner(this);
		keyI.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyO.makeVisibleAndAddListner(this);
		keyO.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyP.makeVisibleAndAddListner(this);
		keyP.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyA.makeVisibleAndAddListner(this);
		keyA.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyS.makeVisibleAndAddListner(this);
		keyS.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyD.makeVisibleAndAddListner(this);
		keyD.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyF.makeVisibleAndAddListner(this);
		keyF.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyG.makeVisibleAndAddListner(this);
		keyG.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyH.makeVisibleAndAddListner(this);
		keyH.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyJ.makeVisibleAndAddListner(this);
		keyJ.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyK.makeVisibleAndAddListner(this);
		keyK.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyL.makeVisibleAndAddListner(this);
		keyL.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyZ.makeVisibleAndAddListner(this);
		keyZ.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyX.makeVisibleAndAddListner(this);
		keyX.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyC.makeVisibleAndAddListner(this);
		keyC.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyV.makeVisibleAndAddListner(this);
		keyV.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyB.makeVisibleAndAddListner(this);
		keyB.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyN.makeVisibleAndAddListner(this);
		keyN.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyM.makeVisibleAndAddListner(this);
		keyM.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyBackSpace.makeVisibleAndAddListner(this);
		keyBackSpace.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyCaps.makeVisibleAndAddListner(this);
		keyCaps.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keySpace.makeVisibleAndAddListner(this);
		keySpace.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyDone.makeVisibleAndAddListner(this);
		keyDone.setColour(ui::Label::textColourId, ui::Theme::Instance().getColour(ui::transparentWhite));
		key0.makeVisibleAndAddListner(this);
		key0.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key1.makeVisibleAndAddListner(this);
		key1.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key2.makeVisibleAndAddListner(this);
		key2.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key3.makeVisibleAndAddListner(this);
		key3.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key4.makeVisibleAndAddListner(this);
		key4.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key5.makeVisibleAndAddListner(this);
		key5.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key6.makeVisibleAndAddListner(this);
		key6.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key7.makeVisibleAndAddListner(this);
		key7.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key8.makeVisibleAndAddListner(this);
		key8.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		key9.makeVisibleAndAddListner(this);
		key9.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyplus.makeVisibleAndAddListner(this);
		keyplus.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyminus.makeVisibleAndAddListner(this);
		keyminus.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyhyphen.makeVisibleAndAddListner(this);
		keyhyphen.setColour(juce::TextButton::buttonColourId, ui::Theme::Instance().getColour(ui::systemBlue).withAlpha((float)0.4));
		keyCancel.makeVisibleAndAddListner(this);

		valRow.items.add(FlexItem(keyPadValue).withFlex(1));
		topNumRow.items.add(FlexItem(key1).withFlex(2));
		topNumRow.items.add(FlexItem(key2).withFlex(2));
		topNumRow.items.add(FlexItem(key3).withFlex(2));
		topNumRow.items.add(FlexItem(key4).withFlex(2));
		topNumRow.items.add(FlexItem(key5).withFlex(2));
		topNumRow.items.add(FlexItem(key6).withFlex(2));
		topNumRow.items.add(FlexItem(key7).withFlex(2));
		topNumRow.items.add(FlexItem(key8).withFlex(2));
		topNumRow.items.add(FlexItem(key9).withFlex(2));
		topNumRow.items.add(FlexItem(key0).withFlex(2));
		topNumRow.items.add(FlexItem(keyplus).withFlex(2));
		topNumRow.items.add(FlexItem(keyminus).withFlex(2));
		topNumRow.items.add(FlexItem(keyhyphen).withFlex(2));

		topRow.items.add(FlexItem(keyQ).withFlex(2));
		topRow.items.add(FlexItem(keyW).withFlex(2));
		topRow.items.add(FlexItem(keyE).withFlex(2));
		topRow.items.add(FlexItem(keyR).withFlex(2));
		topRow.items.add(FlexItem(keyT).withFlex(2));
		topRow.items.add(FlexItem(keyY).withFlex(2));
		topRow.items.add(FlexItem(keyU).withFlex(2));
		topRow.items.add(FlexItem(keyI).withFlex(2));
		topRow.items.add(FlexItem(keyO).withFlex(2));
		topRow.items.add(FlexItem(keyP).withFlex(2));
		topRow.items.add(FlexItem(keyBackSpace).withFlex(3.8f));

		midTRow.items.add(FlexItem(keyCaps).withFlex(4));
		midTRow.items.add(FlexItem(keyA).withFlex(2));
		midTRow.items.add(FlexItem(keyS).withFlex(2));
		midTRow.items.add(FlexItem(keyD).withFlex(2));
		midTRow.items.add(FlexItem(keyF).withFlex(2));
		midTRow.items.add(FlexItem(keyG).withFlex(2));
		midTRow.items.add(FlexItem(keyH).withFlex(2));
		midTRow.items.add(FlexItem(keyJ).withFlex(2));
		midTRow.items.add(FlexItem(keyK).withFlex(2));
		midTRow.items.add(FlexItem(keyL).withFlex(2));
		midTRow.items.add(FlexItem(keyDone).withFlex(3.8f));

		bottomRow.items.add(FlexItem(keyCancel).withFlex(3.6f));
		bottomRow.items.add(FlexItem(keyZ).withFlex(2));
		bottomRow.items.add(FlexItem(keyX).withFlex(2));
		bottomRow.items.add(FlexItem(keyC).withFlex(2));
		bottomRow.items.add(FlexItem(keyV).withFlex(2));
		bottomRow.items.add(FlexItem(keyB).withFlex(2));
		bottomRow.items.add(FlexItem(keyN).withFlex(2));
		bottomRow.items.add(FlexItem(keyM).withFlex(2));
		bottomRow.items.add(FlexItem(keySpace).withFlex(6.2f));

		//keypad.items.add(FlexItem(valRow).withFlex(1).withMargin({ 2.0 }).withMaxHeight(60.0f));
		keypad.items.add(FlexItem(topNumRow).withFlex(1));
		keypad.items.add(FlexItem(topRow).withFlex(1));
		keypad.items.add(FlexItem(midTRow).withFlex(1));
		keypad.items.add(FlexItem(bottomRow).withFlex(1));
		keyQ.setToggleable(true);
		this->setName(Name);
		setSize(layout::numpad.getWidth(), layout::numpad.getHeight());
		keyCaps.setToggleState(false, sendNotification);
	}

	void CommonKeyPad::show(std::function<void(int)> CallbackOnExit)
	{
		if (auto w = juce::TopLevelWindow::getActiveTopLevelWindow())
			image = w->createComponentSnapshot(ui::Rectangle<int>{0, 0, 1024, 600}, true);
		ui::blurImage<2>(image);
		DialogWindow::LaunchOptions options;
		options.content.setNonOwned(this);
		options.content->setSize(layout::screen.getWidth(), layout::screen.getHeight());
		options.dialogTitle = this->getName();
		options.dialogBackgroundColour = Theme::Instance().getColour(transparentBlack);
		options.escapeKeyTriggersCloseButton = true;
		options.useNativeTitleBar = false;
		options.resizable = false;

		juce::Component::SafePointer<juce::DialogWindow> dialogWindow{ options.launchAsync() };
		dialogWindow->setDraggable(true);
		dialogWindow->setLookAndFeel(CommonLooknFeel::getLnf());
		dialogWindow->setTitleBarTextCentred(false);
		dialogWindow->setTitleBarHeight(0);

		ModalComponentManager::getInstance()->attachCallback(dialogWindow, ModalCallbackFunction::create([CallbackOnExit, dialogWindow](int R)
			{
				CallbackOnExit(R);
				delete dialogWindow;
			}));
		//ui::CommonUtils::showDialog(this->getName(), this, CallbackOnExit, layout::keypad.getWidth(), layout::keypad.getHeight());
		
	}

	void CommonKeyPad::setValue(String value)
	{
		// Remove '*' characters if present
		String inputValue = value.contains("*") ? value.removeCharacters("*") : value;

		int colonIndex = inputValue.indexOfChar(':'); // Find the position of ':' and Remove the character before ':' and ':'
		if (colonIndex > 0) {
			inputValue = inputValue.substring(0, colonIndex - 1) + inputValue.substring(colonIndex + 1);
		}
		inputValue = inputValue.trim(); // remove  space from leading and trailing

		keyPadValue.setText(inputValue, dontSendNotification);
	}

	void CommonKeyPad::paint(juce::Graphics& g)
	{
		if (this->isVisible())
			g.drawImageAt(image, 0, 0);
		g.setColour(Theme::Instance().getKeyBoardColour(1,0));
		g.fillRect(ui::Rectangle<float>(0, 300, 1024, 290));
		g.setColour(Theme::Instance().getKeyBoardColour(2, 0));
		g.fillRect(ui::Rectangle<float>(0, 300, 1024, 1));
	};

	void CommonKeyPad::resized()
	{
		keypad.performLayout(ui::Rectangle<float>(157, 310.0f, 710, 200));
		valRow.performLayout(ui::Rectangle<float>(157, 230.0f, 710, 60));
	};

	void CommonKeyPad::setMaximumLimit(int max)
	{
		maxLimit = max;
	}

	void CommonKeyPad::buttonClicked(juce::Button* button)
	{
		// Check if Enter button pressed...
		if (button == &keyDone)
		{
			int dataOk = KEY_PAD_DATA_VALIDATE_OK;

			if (isAnyInput && (button == &keyDone))
			{
				if (ValidateDataOnChange)
				{
					dataOk = ValidateDataOnChange(lastEnteredValue);
					if (dataOk != KEY_PAD_DATA_VALIDATE_OK)
					{
						String string = "Error";
						if (dataOk == KEY_PAD_DATA_DUPLICATE_ERROR)
							string = KEY_PAD_DATA_DUPLICATE_ERROR_STRING;
						else if (dataOk == KEY_PAD_DATA_LIMIT_ERROR)
							string = KEY_PAD_DATA_LIMIT_ERROR_STRING;

						warnPopupPtr = new CommonWarningPopUp(string);
						warnPopupPtr->show();
						warnPopupPtr->onSelectionChanged = [this](int r)
						{
							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);
						};
					}
				}

				if (onValueChanged && (dataOk == KEY_PAD_DATA_VALIDATE_OK))
				{
					lastEnteredValue = lastEnteredValue.trim(); // remove space from leading and trailing
					onValueChanged(lastEnteredValue);
				}
			}
			if (dataOk == KEY_PAD_DATA_VALIDATE_OK)
			{
				// Exit this dialog box.
				if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
					(button == &keyDone) ? dw->exitModalState(IGNITE_DIALOG_APPLY) : dw->exitModalState(IGNITE_DIALOG_CANCEL);
			}
		}

		if (keyPadValue.getText().length() <= maxLimit)
		{
			isAnyInput = true;

			if (button == &keyQ)
			{
				if (keyQ.getToggleState())
					keyQ.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyQ.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyW)
			{
				if (keyW.getToggleState())
					keyW.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyW.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyE)
			{
				if (keyE.getToggleState())
					keyE.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyE.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyR)
			{
				if (keyR.getToggleState())
					keyR.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyR.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyT)
			{
				if (keyT.getToggleState())
					keyT.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyT.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyY)
			{
				if (keyY.getToggleState())
					keyY.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyY.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyU)
			{
				if (keyU.getToggleState())
					keyU.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyU.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyI)
			{
				if (keyI.getToggleState())
					keyI.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyI.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyO)
			{
				if (keyO.getToggleState())
					keyO.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyO.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyP)
			{
				if (keyP.getToggleState())
					keyP.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyP.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyA)
			{
				if (keyA.getToggleState())
					keyA.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyA.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyS)
			{
				if (keyS.getToggleState())
					keyS.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyS.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyD)
			{
				if (keyD.getToggleState())
					keyD.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyD.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyF)
			{
				if (keyF.getToggleState())
					keyF.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyF.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyG)
			{
				if (keyG.getToggleState())
					keyG.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyG.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyH)
			{
				if (keyH.getToggleState())
					keyH.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyH.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyJ)
			{
				if (keyJ.getToggleState())
					keyJ.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyJ.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyK)
			{
				if (keyK.getToggleState())
					keyK.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyK.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyL)
			{
				if (keyL.getToggleState())
					keyL.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyL.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyZ)
			{
				if (keyZ.getToggleState())
					keyZ.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyZ.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyX)
			{
				if (keyX.getToggleState())
					keyX.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyX.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyC)
			{
				if (keyC.getToggleState())
					keyC.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyC.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyV)
			{
				if (keyV.getToggleState())
					keyV.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyV.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyB)
			{
				if (keyB.getToggleState())
					keyB.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyB.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyN)
			{
				if (keyN.getToggleState())
					keyN.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyN.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyM)
			{
				if (keyM.getToggleState())
					keyM.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyM.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key1)
			{
				if (key1.getToggleState())
					key1.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key1.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key2)
			{
				if (key2.getToggleState())
					key2.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key2.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key3)
			{
				if (key3.getToggleState())
					key3.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key3.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key4)
			{
				if (key4.getToggleState())
					key4.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key4.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key5)
			{
				if (key5.getToggleState())
					key5.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key5.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key6)
			{
				if (key6.getToggleState())
					key6.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key6.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key7)
			{
				if (key7.getToggleState())
					key7.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key7.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key8)
			{
				if (key8.getToggleState())
					key8.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key8.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key9)
			{
				if (key9.getToggleState())
					key9.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key9.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &key0)
			{
				if (key0.getToggleState())
					key0.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + key0.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyplus)
			{
				if (keyplus.getToggleState())
					keyplus.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyplus.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyminus)
			{
				if (keyminus.getToggleState())
					keyminus.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyminus.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keyhyphen)
			{
				if (keyhyphen.getToggleState())
					keyhyphen.setToggleState(false, dontSendNotification);
				keyPadValue.setText(keyPadValue.getText() + keyhyphen.getButtonText(), juce::dontSendNotification);
			}
			else if (button == &keySpace)
			{
				if (keySpace.getToggleState())
					keySpace.setToggleState(false, dontSendNotification);
				//Spacebar handling
				if (keyPadValue.getText().isNotEmpty())
				{
					keyPadValue.setText(keyPadValue.getText() + " ", juce::dontSendNotification);
				}
			}
		}
		else
		{
			//TODO : Removed the pop-up as it creating crash

			//if (button != &keyCaps && button != &keyBackSpace && button != &keyCancel && button != &keyDone)
			//{
			//	warnPopupPtr = new CommonWarningPopUp("Reached Maximum number of letters");
			//	warnPopupPtr->show();
			//	warnPopupPtr->onSelectionChanged = [this](int r)
			//	{
			//		if (auto dw = getCurrentlyModalComponent())
			//			dw->exitModalState(0);
			//	};
			//}
		}

		if (button == &keyCaps)
		{
			toggleKeys();
		}
		else if (button == &keyBackSpace)
		{
			if (keyBackSpace.getToggleState())
				keyBackSpace.setToggleState(false, dontSendNotification);
			if (keyPadValue.getText().isNotEmpty())
			{
				std::string tmpVal = keyPadValue.getText().toStdString();
				tmpVal.erase(tmpVal.length() - 1);
				keyPadValue.setText(String(tmpVal), juce::dontSendNotification);
			}
		}
		else if (button == &keyCancel)
		{
			if (keyCancel.getToggleState())
				keyCancel.setToggleState(false, dontSendNotification);
			if (auto dw = getCurrentlyModalComponent())
				dw->exitModalState(0);
		}

		lastEnteredValue = keyPadValue.getText();
	};

	void CommonKeyPad::labelTextChanged(Label* labelThatHasChanged) {}

	void CommonKeyPad::toggleKeys()
	{
		if (isToggle == true)
		{
			keyQ.setButtonText(keyQ.getButtonText().toLowerCase());
			keyW.setButtonText(keyW.getButtonText().toLowerCase());
			keyE.setButtonText(keyE.getButtonText().toLowerCase());
			keyR.setButtonText(keyR.getButtonText().toLowerCase());
			keyT.setButtonText(keyT.getButtonText().toLowerCase());
			keyY.setButtonText(keyY.getButtonText().toLowerCase());
			keyU.setButtonText(keyU.getButtonText().toLowerCase());
			keyI.setButtonText(keyI.getButtonText().toLowerCase());
			keyO.setButtonText(keyO.getButtonText().toLowerCase());
			keyP.setButtonText(keyP.getButtonText().toLowerCase());
			keyA.setButtonText(keyA.getButtonText().toLowerCase());
			keyS.setButtonText(keyS.getButtonText().toLowerCase());
			keyD.setButtonText(keyD.getButtonText().toLowerCase());
			keyF.setButtonText(keyF.getButtonText().toLowerCase());
			keyG.setButtonText(keyG.getButtonText().toLowerCase());
			keyH.setButtonText(keyH.getButtonText().toLowerCase());
			keyJ.setButtonText(keyJ.getButtonText().toLowerCase());
			keyK.setButtonText(keyK.getButtonText().toLowerCase());
			keyL.setButtonText(keyL.getButtonText().toLowerCase());
			keyZ.setButtonText(keyZ.getButtonText().toLowerCase());
			keyX.setButtonText(keyX.getButtonText().toLowerCase());
			keyC.setButtonText(keyC.getButtonText().toLowerCase());
			keyV.setButtonText(keyV.getButtonText().toLowerCase());
			keyB.setButtonText(keyB.getButtonText().toLowerCase());
			keyN.setButtonText(keyN.getButtonText().toLowerCase());
			keyM.setButtonText(keyM.getButtonText().toLowerCase());
			keyQ.setImage("btn-key-q-low-default.png", "btn-key-q-low-active.png", "btn-key-q-low-default-hover.png");
			keyW.setImage("btn-key-w-low-default.png", "btn-key-w-low-active.png", "btn-key-w-low-default-hover.png");
			keyE.setImage("btn-key-e-low-default.png", "btn-key-e-low-active.png", "btn-key-e-low-default-hover.png");
			keyR.setImage("btn-key-r-low-default.png", "btn-key-r-low-active.png", "btn-key-r-low-default-hover.png");
			keyT.setImage("btn-key-t-low-default.png", "btn-key-t-low-active.png", "btn-key-t-low-default-hover.png");
			keyY.setImage("btn-key-y-low-default.png", "btn-key-y-low-active.png", "btn-key-y-low-default-hover.png");
			keyU.setImage("btn-key-u-low-default.png", "btn-key-u-low-active.png", "btn-key-u-low-default-hover.png");
			keyI.setImage("btn-key-i-low-default.png", "btn-key-i-low-active.png", "btn-key-i-low-default-hover.png");
			keyO.setImage("btn-key-o-low-default.png", "btn-key-o-low-active.png", "btn-key-o-low-default-hover.png");
			keyP.setImage("btn-key-p-low-default.png", "btn-key-p-low-active.png", "btn-key-p-low-default-hover.png");
			keyA.setImage("btn-key-a-low-default.png", "btn-key-a-low-active.png", "btn-key-a-low-default-hover.png");
			keyS.setImage("btn-key-s-low-default.png", "btn-key-s-low-active.png", "btn-key-s-low-default-hover.png");
			keyD.setImage("btn-key-d-low-default.png", "btn-key-d-low-active.png", "btn-key-d-low-default-hover.png");
			keyF.setImage("btn-key-f-low-default.png", "btn-key-f-low-active.png", "btn-key-f-low-default-hover.png");
			keyG.setImage("btn-key-g-low-default.png", "btn-key-g-low-active.png", "btn-key-g-low-default-hover.png");
			keyH.setImage("btn-key-h-low-default.png", "btn-key-h-low-active.png", "btn-key-h-low-default-hover.png");
			keyJ.setImage("btn-key-j-low-default.png", "btn-key-j-low-active.png", "btn-key-j-low-default-hover.png");
			keyK.setImage("btn-key-k-low-default.png", "btn-key-k-low-active.png", "btn-key-k-low-default-hover.png");
			keyL.setImage("btn-key-l-low-default.png", "btn-key-l-low-active.png", "btn-key-l-low-default-hover.png");
			keyZ.setImage("btn-key-z-low-default.png", "btn-key-z-low-active.png", "btn-key-z-low-default-hover.png");
			keyX.setImage("btn-key-x-low-default.png", "btn-key-x-low-active.png", "btn-key-x-low-default-hover.png");
			keyC.setImage("btn-key-c-low-default.png", "btn-key-c-low-active.png", "btn-key-c-low-default-hover.png");
			keyV.setImage("btn-key-v-low-default.png", "btn-key-v-low-active.png", "btn-key-v-low-default-hover.png");
			keyB.setImage("btn-key-b-low-default.png", "btn-key-b-low-active.png", "btn-key-b-low-default-hover.png");
			keyN.setImage("btn-key-n-low-default.png", "btn-key-n-low-active.png", "btn-key-n-low-default-hover.png");
			keyM.setImage("btn-key-m-low-default.png", "btn-key-m-low-active.png", "btn-key-m-low-default-hover.png");
			isToggle = false;
		}
		else
		{
			keyQ.setButtonText(keyQ.getButtonText().toUpperCase());
			keyW.setButtonText(keyW.getButtonText().toUpperCase());
			keyE.setButtonText(keyE.getButtonText().toUpperCase());
			keyR.setButtonText(keyR.getButtonText().toUpperCase());
			keyT.setButtonText(keyT.getButtonText().toUpperCase());
			keyY.setButtonText(keyY.getButtonText().toUpperCase());
			keyU.setButtonText(keyU.getButtonText().toUpperCase());
			keyI.setButtonText(keyI.getButtonText().toUpperCase());
			keyO.setButtonText(keyO.getButtonText().toUpperCase());
			keyP.setButtonText(keyP.getButtonText().toUpperCase());
			keyA.setButtonText(keyA.getButtonText().toUpperCase());
			keyS.setButtonText(keyS.getButtonText().toUpperCase());
			keyD.setButtonText(keyD.getButtonText().toUpperCase());
			keyF.setButtonText(keyF.getButtonText().toUpperCase());
			keyG.setButtonText(keyG.getButtonText().toUpperCase());
			keyH.setButtonText(keyH.getButtonText().toUpperCase());
			keyJ.setButtonText(keyJ.getButtonText().toUpperCase());
			keyK.setButtonText(keyK.getButtonText().toUpperCase());
			keyL.setButtonText(keyL.getButtonText().toUpperCase());
			keyZ.setButtonText(keyZ.getButtonText().toUpperCase());
			keyX.setButtonText(keyX.getButtonText().toUpperCase());
			keyC.setButtonText(keyC.getButtonText().toUpperCase());
			keyV.setButtonText(keyV.getButtonText().toUpperCase());
			keyB.setButtonText(keyB.getButtonText().toUpperCase());
			keyN.setButtonText(keyN.getButtonText().toUpperCase());
			keyM.setButtonText(keyM.getButtonText().toUpperCase());
			keyQ.setImage("btn-key-q-default.png", "btn-key-q-active.png","btn-key-q-default-hover.png");
			keyW.setImage("btn-key-w-default.png", "btn-key-w-active.png","btn-key-w-default-hover.png");
			keyE.setImage("btn-key-e-default.png", "btn-key-e-active.png","btn-key-e-default-hover.png");
			keyR.setImage("btn-key-r-default.png", "btn-key-r-active.png","btn-key-r-default-hover.png");
			keyT.setImage("btn-key-t-default.png", "btn-key-t-active.png","btn-key-t-default-hover.png");
			keyY.setImage("btn-key-y-default.png", "btn-key-y-active.png","btn-key-y-default-hover.png");
			keyU.setImage("btn-key-u-default.png", "btn-key-u-active.png","btn-key-u-default-hover.png");
			keyI.setImage("btn-key-i-default.png", "btn-key-i-active.png","btn-key-i-default-hover.png");
			keyO.setImage("btn-key-o-default.png", "btn-key-o-active.png","btn-key-o-default-hover.png");
			keyP.setImage("btn-key-p-default.png", "btn-key-p-active.png","btn-key-p-default-hover.png");
			keyA.setImage("btn-key-a-default.png", "btn-key-a-active.png","btn-key-a-default-hover.png");
			keyS.setImage("btn-key-s-default.png", "btn-key-s-active.png","btn-key-s-default-hover.png");
			keyD.setImage("btn-key-d-default.png", "btn-key-d-active.png","btn-key-d-default-hover.png");
			keyF.setImage("btn-key-f-default.png", "btn-key-f-active.png","btn-key-f-default-hover.png");
			keyG.setImage("btn-key-g-default.png", "btn-key-g-active.png","btn-key-g-default-hover.png");
			keyH.setImage("btn-key-h-default.png", "btn-key-h-active.png","btn-key-h-default-hover.png");
			keyJ.setImage("btn-key-j-default.png", "btn-key-j-active.png","btn-key-j-default-hover.png");
			keyK.setImage("btn-key-k-default.png", "btn-key-k-active.png","btn-key-k-default-hover.png");
			keyL.setImage("btn-key-l-default.png", "btn-key-l-active.png","btn-key-l-default-hover.png");
			keyZ.setImage("btn-key-z-default.png", "btn-key-z-active.png","btn-key-z-default-hover.png");
			keyX.setImage("btn-key-x-default.png", "btn-key-x-active.png","btn-key-x-default-hover.png");
			keyC.setImage("btn-key-c-default.png", "btn-key-c-active.png","btn-key-c-default-hover.png");
			keyV.setImage("btn-key-v-default.png", "btn-key-v-active.png","btn-key-v-default-hover.png");
			keyB.setImage("btn-key-b-default.png", "btn-key-b-active.png","btn-key-b-default-hover.png");
			keyN.setImage("btn-key-n-default.png", "btn-key-n-active.png","btn-key-n-default-hover.png");
			keyM.setImage("btn-key-m-default.png", "btn-key-m-active.png","btn-key-m-default-hover.png");
			isToggle = true;
		}
	}

	bool CommonKey::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;

		if (keyPad->warnPopupPtr != nullptr && keyPad->warnPopupPtr->IsEditing())
			return keyPad->warnPopupPtr->FPKeyHandler(true, param, KeyValue);

		if (keyPad->KeyFocusedItem == keyPad->KeyboardViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			keyPad->KeyFocusedItem = keyPad->KeyboardViewItemID::KEY1;
		}
		else
		{
			keyPad->PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				keyPad->KeyFocusedItem = (keyPad->KeyFocusedItem + 1 >= keyPad->KeyboardViewItemID::FOCUS_MAX ? (keyPad->KeyboardViewItemID::FOCUS_MAX) : keyPad->KeyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				keyPad->KeyFocusedItem = (keyPad->KeyFocusedItem - 1 <= keyPad->KeyboardViewItemID::NO_FOCUS ? (keyPad->KeyboardViewItemID::NO_FOCUS + 1) : keyPad->KeyFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				if (auto dw = getCurrentlyModalComponent())
					dw->exitModalState(0);
				break;
			}
		}
		if (setfocus)
		{
			keyPad->PannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void CommonKeyPad::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (KeyboardView[KeyFocusedItem])
		{
		case KEY1:
			key1.FPKeyHandler(isFocuse, param, 0);
			isFocuse ? key1.setState(Button::ButtonState::buttonOver) : key1.setState(Button::ButtonState::buttonNormal);
			break;
		case KEY2:
			isFocuse ? key2.setState(Button::ButtonState::buttonOver) : key2.setState(Button::ButtonState::buttonNormal);
			key2.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY3:
			isFocuse ? key3.setState(Button::ButtonState::buttonOver) : key3.setState(Button::ButtonState::buttonNormal);
			key3.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY4:
			isFocuse ? key4.setState(Button::ButtonState::buttonOver) : key4.setState(Button::ButtonState::buttonNormal);
			key4.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY5:
			isFocuse ? key5.setState(Button::ButtonState::buttonOver) : key5.setState(Button::ButtonState::buttonNormal);
			key5.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY6:
			isFocuse ? key6.setState(Button::ButtonState::buttonOver) : key6.setState(Button::ButtonState::buttonNormal);
			key6.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY7:
			isFocuse ? key7.setState(Button::ButtonState::buttonOver) : key7.setState(Button::ButtonState::buttonNormal);
			key7.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY8:
			isFocuse ? key8.setState(Button::ButtonState::buttonOver) : key8.setState(Button::ButtonState::buttonNormal);
			key8.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY9:
			isFocuse ? key9.setState(Button::ButtonState::buttonOver) : key9.setState(Button::ButtonState::buttonNormal);
			key9.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY10:
			isFocuse ? key0.setState(Button::ButtonState::buttonOver) : key0.setState(Button::ButtonState::buttonNormal);
			key0.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY11:
			isFocuse ? keyplus.setState(Button::ButtonState::buttonOver) : keyplus.setState(Button::ButtonState::buttonNormal);
			keyplus.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY12:
			isFocuse ? keyminus.setState(Button::ButtonState::buttonOver) : keyminus.setState(Button::ButtonState::buttonNormal);
			keyminus.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY13:
			isFocuse ? keyhyphen.setState(Button::ButtonState::buttonOver) : keyhyphen.setState(Button::ButtonState::buttonNormal);
			keyhyphen.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY14:
			isFocuse ? keyQ.setState(Button::ButtonState::buttonOver) : keyQ.setState(Button::ButtonState::buttonNormal);
			keyQ.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY15:
			isFocuse ? keyW.setState(Button::ButtonState::buttonOver) : keyW.setState(Button::ButtonState::buttonNormal);
			keyW.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY16:
			isFocuse ? keyE.setState(Button::ButtonState::buttonOver) : keyE.setState(Button::ButtonState::buttonNormal);
			keyE.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY17:
			isFocuse ? keyR.setState(Button::ButtonState::buttonOver) : keyR.setState(Button::ButtonState::buttonNormal);
			keyR.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY18:
			isFocuse ? keyT.setState(Button::ButtonState::buttonOver) : keyT.setState(Button::ButtonState::buttonNormal);
			keyT.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY19:
			isFocuse ? keyY.setState(Button::ButtonState::buttonOver) : keyY.setState(Button::ButtonState::buttonNormal);
			keyY.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY20:
			isFocuse ? keyU.setState(Button::ButtonState::buttonOver) : keyU.setState(Button::ButtonState::buttonNormal);
			keyU.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY21:
			isFocuse ? keyI.setState(Button::ButtonState::buttonOver) : keyI.setState(Button::ButtonState::buttonNormal);
			keyI.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY22:
			isFocuse ? keyO.setState(Button::ButtonState::buttonOver) : keyO.setState(Button::ButtonState::buttonNormal);
			keyO.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY23:
			isFocuse ? keyP.setState(Button::ButtonState::buttonOver) : keyP.setState(Button::ButtonState::buttonNormal);
			keyP.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY24:
			isFocuse ? keyBackSpace.setState(Button::ButtonState::buttonOver) : keyBackSpace.setState(Button::ButtonState::buttonNormal);
			keyBackSpace.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY25:
			isFocuse ? keyCaps.setState(Button::ButtonState::buttonOver) : keyCaps.setState(Button::ButtonState::buttonNormal);
			keyCaps.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY26:
			isFocuse ? keyA.setState(Button::ButtonState::buttonOver) : keyA.setState(Button::ButtonState::buttonNormal);
			keyA.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY27:
			isFocuse ? keyS.setState(Button::ButtonState::buttonOver) : keyS.setState(Button::ButtonState::buttonNormal);
			keyS.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY28:
			isFocuse ? keyD.setState(Button::ButtonState::buttonOver) : keyD.setState(Button::ButtonState::buttonNormal);
			keyD.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY29:
			isFocuse ? keyF.setState(Button::ButtonState::buttonOver) : keyF.setState(Button::ButtonState::buttonNormal);
			keyF.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY30:
			isFocuse ? keyG.setState(Button::ButtonState::buttonOver) : keyG.setState(Button::ButtonState::buttonNormal);
			keyG.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY31:
			isFocuse ? keyH.setState(Button::ButtonState::buttonOver) : keyH.setState(Button::ButtonState::buttonNormal);
			keyH.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY32:
			isFocuse ? keyJ.setState(Button::ButtonState::buttonOver) : keyJ.setState(Button::ButtonState::buttonNormal);
			keyJ.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY33:
			isFocuse ? keyK.setState(Button::ButtonState::buttonOver) : keyK.setState(Button::ButtonState::buttonNormal);
			keyK.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY34:
			isFocuse ? keyL.setState(Button::ButtonState::buttonOver) : keyL.setState(Button::ButtonState::buttonNormal);
			keyL.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY35:
			isFocuse ? keyDone.setState(Button::ButtonState::buttonOver) : keyDone.setState(Button::ButtonState::buttonNormal);
			keyDone.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY36:
			isFocuse ? keyCancel.setState(Button::ButtonState::buttonOver) : keyCancel.setState(Button::ButtonState::buttonNormal);
			keyCancel.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY37:
			isFocuse ? keyZ.setState(Button::ButtonState::buttonOver) : keyZ.setState(Button::ButtonState::buttonNormal);
			keyZ.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY38:
			isFocuse ? keyX.setState(Button::ButtonState::buttonOver) : keyX.setState(Button::ButtonState::buttonNormal);
			keyX.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY39:
			isFocuse ? keyC.setState(Button::ButtonState::buttonOver) : keyC.setState(Button::ButtonState::buttonNormal);
			keyC.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY40:
			isFocuse ? keyV.setState(Button::ButtonState::buttonOver) : keyV.setState(Button::ButtonState::buttonNormal);
			keyV.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY41:
			isFocuse ? keyB.setState(Button::ButtonState::buttonOver) : keyB.setState(Button::ButtonState::buttonNormal);
			keyB.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY42:
			isFocuse ? keyN.setState(Button::ButtonState::buttonOver) : keyN.setState(Button::ButtonState::buttonNormal);
			keyN.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY43:
			isFocuse ? keyM.setState(Button::ButtonState::buttonOver) : keyM.setState(Button::ButtonState::buttonNormal);
			keyM.FPKeyHandler(isFocuse, param, 0);
			break;
		case KEY44:
			isFocuse ? keySpace.setState(Button::ButtonState::buttonOver) : keySpace.setState(Button::ButtonState::buttonNormal);
			keySpace.FPKeyHandler(isFocuse, param, 0);
			break;
		default:
			break;
		}
	}

};
