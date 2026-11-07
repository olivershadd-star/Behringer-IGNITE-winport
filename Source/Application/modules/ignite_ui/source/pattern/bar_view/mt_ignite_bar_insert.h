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

#pragma once
namespace ui
{
	class IgniteBarInsert : public juce::Component, public CommonButton::Listener
	{
	public:
		enum class insertCtlKey {
			INSERT,
			CANCEL,
		};

		IgniteBarInsert();
		~IgniteBarInsert() override;
		std::function<void(insertCtlKey, int)> onButtonPressed;
		void setBarIndex(int barIndex);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);

	private:
#define BAR_INSERT_OPTIONS_VIEW 4
		enum barInsertViewItemID
		{
			NO_FOCUS = 0,
			KEY_INSERT_POSITION,
			KEY_CANCEL,
			KEY_INSERT,
			FOCUS_MAX = KEY_INSERT
		};

		uint8_t barInsertView[BAR_INSERT_OPTIONS_VIEW] = { NO_FOCUS, KEY_INSERT_POSITION, KEY_CANCEL, KEY_INSERT };
		int keyFocusedItem = barInsertViewItemID::NO_FOCUS;
		int numberOfBars = 0;
		std::vector<juce::String> barNumberDefault{ "btn-num-1-default.png","btn-num-2-default.png", "btn-num-3-default.png", "btn-num-4-default.png", "btn-num-5-default.png", "btn-num-6-default.png", "btn-num-7-default.png", "btn-num-8-default.png", "btn-num-9-default.png", "btn-num-10-default.png", "btn-num-11-default.png", "btn-num-12-default.png", "btn-num-13-default.png", "btn-num-14-default.png", "btn-num-15-default.png", "btn-num-16-default.png" };
		std::vector<juce::String> barNumberDefaultHover{ "btn-num-1-default-hover.png","btn-num-2-default-hover.png", "btn-num-3-default-hover.png", "btn-num-4-default-hover.png", "btn-num-5-default-hover.png", "btn-num-6-default-hover.png", "btn-num-7-default-hover.png", "btn-num-8-default-hover.png", "btn-num-9-default-hover.png", "btn-num-10-default-hover.png", "btn-num-11-default-hover.png", "btn-num-12-default-hover.png", "btn-num-13-default-hover.png", "btn-num-14-default-hover.png", "btn-num-15-default-hover.png", "btn-num-16-default-hover.png" };
		std::vector<juce::String> barNumberActive{ "btn-num-1-active.png","btn-num-2-active.png", "btn-num-3-active.png", "btn-num-4-active.png", "btn-num-5-active.png", "btn-num-6-active.png", "btn-num-7-active.png", "btn-num-8-active.png", "btn-num-9-active.png", "btn-num-10-active.png", "btn-num-11-active.png", "btn-num-12-active.png", "btn-num-13-active.png", "btn-num-14-active.png", "btn-num-15-active.png", "btn-num-16-active.png" };
		std::vector<juce::String> barNumberActiveHover{ "btn-num-1-active-hover.png","btn-num-2-active-hover.png", "btn-num-3-active-hover.png", "btn-num-4-active-hover.png", "btn-num-5-active-hover.png", "btn-num-6-active-hover.png", "btn-num-7-active-hover.png", "btn-num-8-active-hover.png", "btn-num-9-active-hover.png", "btn-num-10-active-hover.png", "btn-num-11-active-hover.png", "btn-num-12-active-hover.png", "btn-num-13-active-hover.png", "btn-num-14-active-hover.png", "btn-num-15-active-hover.png", "btn-num-16-active-hover.png" };
		Array<CommonImageButton*> options;
		CommonLabel	insertTitle{ "Insert Bar" };
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		CommonLabel insertLabel{ "Please enter a position to insert bar" };
		CommonButton barNumberButton;
		CommonImageButton insertButton{ "Insert","btn-insert-267x44-default.png","btn-insert-267x44-default-hover.png","btn-insert-267x44-default-hover.png" };
		CommonImageButton cancelButton{ "Cancel","btn-cancel-267x44-default.png","btn-cancel-267x44-default-hover.png","btn-cancel-267x44-default-hover.png" };
		void handleCommandMessage(int id);
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteBarInsert)
	};
}