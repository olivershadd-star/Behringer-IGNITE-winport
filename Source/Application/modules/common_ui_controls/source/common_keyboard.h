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

#pragma once

namespace ui
{
	class CommonKeyPad : public juce::Component, public CommonButton::Listener, public CommonLabel::Listener
	{
#define KEY_PAD_DATA_VALIDATE_OK 0
#define KEY_PAD_DATA_LIMIT_ERROR 1
#define KEY_PAD_DATA_DUPLICATE_ERROR 2

#define KEY_PAD_DATA_LIMIT_ERROR_STRING "Reached Maximum number of letters"
#define KEY_PAD_DATA_DUPLICATE_ERROR_STRING "Name already exist"

	public:

#define KEYBOARD_VIEW 45
		enum KeyboardViewItemID
		{
			NO_FOCUS = 0,
			KEY1,
			KEY2,
			KEY3,
			KEY4,
			KEY5,
			KEY6,
			KEY7,
			KEY8,
			KEY9,
			KEY10,
			KEY11,
			KEY12,
			KEY13,
			KEY14,
			KEY15,
			KEY16,
			KEY17,
			KEY18,
			KEY19,
			KEY20,
			KEY21,
			KEY22,
			KEY23,
			KEY24,
			KEY25,
			KEY26,
			KEY27,
			KEY28,
			KEY29,
			KEY30,
			KEY31,
			KEY32,
			KEY33,
			KEY34,
			KEY35,
			KEY36,
			KEY37,
			KEY38,
			KEY39,
			KEY40,
			KEY41,
			KEY42,
			KEY43,
			KEY44,
			FOCUS_MAX = KEY44
		};
		uint8_t KeyboardView[KEYBOARD_VIEW] = { NO_FOCUS,KEY1,KEY2,KEY3,KEY4,KEY5,KEY6,KEY7,KEY8,KEY9,KEY10,
			KEY11,KEY12,KEY13,KEY14,KEY15,KEY16,KEY17,KEY18,KEY19,KEY20,KEY21,KEY22,KEY23,KEY24,KEY25,KEY26,KEY27,
			KEY28,KEY29,KEY30,KEY31,KEY32,KEY33,KEY34,KEY35,KEY36,KEY37,KEY38,KEY39,KEY40,KEY41,KEY42,KEY43,KEY44 };
		int KeyFocusedItem = KeyboardViewItemID::NO_FOCUS;
		CommonWarningPopUp* warnPopupPtr = nullptr;

		std::function<void(String)> onValueChanged;
		std::function<int(String)> ValidateDataOnChange;
		explicit CommonKeyPad(const String& name);
		void setValue(String Value);
		const String getValue(void) { return lastEnteredValue; }
		void show(std::function<void(int)> CallbackOnExit);
		void labelTextChanged(Label* labelThatHasChanged);
		void setMaximumLimit(int max);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		bool isToggle;

	private:

		CommonLabel keyPadValue{ ("") };

		CommonImageButton keyQ{ TRANS("q"),"btn-key-q-low-default.png","btn-key-q-low-active.png","btn-key-q-low-default-hover.png" };
		CommonImageButton keyW{ TRANS("w"),"btn-key-w-low-default.png","btn-key-w-low-active.png","btn-key-w-low-default-hover.png" };
		CommonImageButton keyE{ TRANS("e"),"btn-key-e-low-default.png","btn-key-e-low-active.png","btn-key-e-low-default-hover.png" };
		CommonImageButton keyR{ TRANS("r"),"btn-key-r-low-default.png","btn-key-r-low-active.png","btn-key-r-low-default-hover.png" };
		CommonImageButton keyT{ TRANS("t"),"btn-key-t-low-default.png","btn-key-t-low-active.png","btn-key-t-low-default-hover.png" };
		CommonImageButton keyY{ TRANS("y"),"btn-key-y-low-default.png","btn-key-y-low-active.png","btn-key-y-low-default-hover.png" };
		CommonImageButton keyU{ TRANS("u"),"btn-key-u-low-default.png","btn-key-u-low-active.png","btn-key-u-low-default-hover.png" };
		CommonImageButton keyI{ TRANS("i"),"btn-key-i-low-default.png","btn-key-i-low-active.png","btn-key-i-low-default-hover.png" };
		CommonImageButton keyO{ TRANS("o"),"btn-key-o-low-default.png","btn-key-o-low-active.png","btn-key-o-low-default-hover.png" };
		CommonImageButton keyP{ TRANS("p"),"btn-key-p-low-default.png","btn-key-p-low-active.png","btn-key-p-low-default-hover.png" };
		CommonImageButton keyA{ TRANS("a"),"btn-key-a-low-default.png","btn-key-a-low-active.png","btn-key-a-low-default-hover.png" };
		CommonImageButton keyS{ TRANS("s"),"btn-key-s-low-default.png","btn-key-s-low-active.png","btn-key-s-low-default-hover.png" };
		CommonImageButton keyD{ TRANS("d"),"btn-key-d-low-default.png","btn-key-d-low-active.png","btn-key-d-low-default-hover.png" };
		CommonImageButton keyF{ TRANS("f"),"btn-key-f-low-default.png","btn-key-f-low-active.png","btn-key-f-low-default-hover.png" };
		CommonImageButton keyG{ TRANS("g"),"btn-key-g-low-default.png","btn-key-g-low-active.png","btn-key-g-low-default-hover.png" };
		CommonImageButton keyH{ TRANS("h"),"btn-key-h-low-default.png","btn-key-h-low-active.png","btn-key-h-low-default-hover.png" };
		CommonImageButton keyJ{ TRANS("j"),"btn-key-j-low-default.png","btn-key-j-low-active.png","btn-key-j-low-default-hover.png" };
		CommonImageButton keyK{ TRANS("k"),"btn-key-k-low-default.png","btn-key-k-low-active.png","btn-key-k-low-default-hover.png" };
		CommonImageButton keyL{ TRANS("l"),"btn-key-l-low-default.png","btn-key-l-low-active.png","btn-key-l-low-default-hover.png" };
		CommonImageButton keyZ{ TRANS("z"),"btn-key-z-low-default.png","btn-key-z-low-active.png","btn-key-z-low-default-hover.png" };
		CommonImageButton keyX{ TRANS("x"),"btn-key-x-low-default.png","btn-key-x-low-active.png","btn-key-x-low-default-hover.png" };
		CommonImageButton keyC{ TRANS("c"),"btn-key-c-low-default.png","btn-key-c-low-active.png","btn-key-c-low-default-hover.png" };
		CommonImageButton keyV{ TRANS("v"),"btn-key-v-low-default.png","btn-key-v-low-active.png","btn-key-v-low-default-hover.png" };
		CommonImageButton keyB{ TRANS("b"),"btn-key-b-low-default.png","btn-key-b-low-active.png","btn-key-b-low-default-hover.png" };
		CommonImageButton keyN{ TRANS("n"),"btn-key-n-low-default.png","btn-key-n-low-active.png","btn-key-n-low-default-hover.png" };
		CommonImageButton keyM{ TRANS("m"),"btn-key-m-low-default.png","btn-key-m-low-active.png","btn-key-m-low-default-hover.png" };
		CommonImageButton keyBackSpace{ TRANS(" < -"),"btn-key-symbol-default.png","btn-key-symbol-active.png","btn-key-symbol-default-hover.png"};
		CommonImageButton keyCaps{ TRANS("CapsLock"),"btn-key-capslock-default.png","btn-key-capslock-active.png","btn-key-capslock-default-hover.png" };
		CommonImageButton keySpace{ TRANS("Space"),"btn-key-space-default.png","btn-key-space-active.png","btn-key-space-default-hover.png" };
		CommonImageButton keyDone{ TRANS("Enter"),"btn-key-enter-default.png","btn-key-enter-active.png","btn-key-enter-default-hover.png" };
		CommonImageButton keyCancel{ TRANS("Cancel"),"btn-key-cancel-default.png","btn-key-cancel-active.png","btn-key-cancel-default-hover.png" };
		CommonImageButton key0{ TRANS("0"),"btn-key-0-default.png","btn-key-0-active.png","btn-key-0-default-hover.png" };
		CommonImageButton key1{ TRANS("1"),"btn-key-1-default.png","btn-key-1-active.png","btn-key-1-default-hover.png " };
		CommonImageButton key2{ TRANS("2"),"btn-key-2-default.png","btn-key-2-active.png","btn-key-2-default-hover.png" };
		CommonImageButton key3{ TRANS("3"),"btn-key-3-default.png","btn-key-3-active.png","btn-key-3-default-hover.png" };
		CommonImageButton key4{ TRANS("4"),"btn-key-4-default.png","btn-key-4-active.png","btn-key-4-default-hover.png" };
		CommonImageButton key5{ TRANS("5"),"btn-key-5-default.png","btn-key-5-active.png","btn-key-5-default-hover.png" };
		CommonImageButton key6{ TRANS("6"),"btn-key-6-default.png","btn-key-6-active.png","btn-key-6-default-hover.png" };
		CommonImageButton key7{ TRANS("7"),"btn-key-7-default.png","btn-key-7-active.png","btn-key-7-default-hover.png" };
		CommonImageButton key8{ TRANS("8"),"btn-key-8-default.png","btn-key-8-active.png","btn-key-8-default-hover.png" };
		CommonImageButton key9{ TRANS("9"),"btn-key-9-default.png","btn-key-9-active.png","btn-key-9-default-hover.png" };
		CommonImageButton keyplus{ TRANS("+"),"btn-key-plus-default.png","btn-key-plus-active.png","btn-key-plus-default-hover.png" };
		CommonImageButton keyminus{ TRANS("-"),"btn-key-minus-default.png","btn-key-minus-active.png","btn-key-minus-default-hover.png" };
		CommonImageButton keyhyphen{ TRANS("_"),"btn-key-underscore-default.png","btn-key-underscore-active.png","btn-key-underscore-default-hover.png" };

		FlexBox valRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox topNumRow{ FlexBox::Direction::row , FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox topRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox midTRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox bottomRow{ FlexBox::Direction::row , FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox keypad{ FlexBox::Direction::column, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };

		void toggleKeys();

		String lastEnteredValue;
		bool isAnyInput{ false };
		int maxLimit;
		Image image;
		void buttonClicked(juce::Button* button) override;

		void paint(juce::Graphics& g) override;
		void resized() override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonKeyPad);
	};

	//Soft keyboard enabled label class
	class CommonKey : public CommonLabel
	{
	public:
		std::function<void(String)> onValueChanged;
		std::function<int(String)> ValidateDataOnChange;
		std::function<void(void)> onMouseClick;

		explicit CommonKey(const String& Name, bool singleClickLaunch = false) : CommonLabel(Name),
			keyPad(std::make_unique<ui::CommonKeyPad>(Name))
		{
			addMouseListener(this, true);
			mouseUpLaunch = singleClickLaunch;
			keyPad->onValueChanged = [this](String value)
			{
				setText(String(value), juce::dontSendNotification);
				if (onValueChanged)
					onValueChanged(value);
			};
			keyPad->ValidateDataOnChange = [this](String value)
			{
				if (ValidateDataOnChange)
					return(ValidateDataOnChange(value));

				return KEY_PAD_DATA_VALIDATE_OK;
			};
		}

		void setValue(int value)
		{
			setText(String(value), juce::dontSendNotification);
		}

		void editLable()
		{
			if (!isEditing)
			{
				isEditing = true;
				keyPad->setValue(getText(isEditing));
				keyPad->show([this](int r) { isEditing = false; keyPad->isToggle = false; });
			}
		}

		void setLableFont(Font newFont)
		{
			setTextFont(newFont);
		}

		void keyboardCtl(bool state) { mouseUpLaunch = state; }
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool isEditing{ false };
		void disableTitleEdit(bool state) { titleEditable = state; }
		void launchKeyboard()
		{
			keyPad->show([this](int r) { isEditing = false; keyPad->isToggle = false; });
		}
	private:
		std::unique_ptr<ui::CommonKeyPad> keyPad;
		void mouseDoubleClick(const juce::MouseEvent& e) override
		{
			if (titleEditable)
			{
				if (!isEditing)
				{
					isEditing = true;
					keyPad->setValue(getText(isEditing));
					keyPad->show([this](int r) { isEditing = false; keyPad->isToggle = false; });
				}
			}
		}

		void mouseUp(const juce::MouseEvent& e) override
		{
			if (mouseUpLaunch)
			{
				if (!isEditing)
				{
					isEditing = true;
					keyPad->setValue(getText(isEditing));
					keyPad->show([this](int r) { isEditing = false; keyPad->isToggle = false; });
				}
			}
		}

		void mouseDown(const juce::MouseEvent& e) override
		{
			if (!clickdone)
			{
				if (onMouseClick)
					onMouseClick();
				clickdone = true;
			}
			else
				clickdone = false;
		}
		bool clickdone = false;
		bool titleEditable = true;
		bool mouseUpLaunch = false;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonKey);
	};

};