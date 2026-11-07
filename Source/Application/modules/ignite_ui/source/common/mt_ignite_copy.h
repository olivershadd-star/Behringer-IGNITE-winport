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
	class IgniteCopy : public juce::Component, public CommonButton::Listener
	{
	public:
		enum class copyCtlKey {
			COPY,
			CANCEL,
		};

		IgniteCopy();
		~IgniteCopy() override;
		void setLabelText(String text);
		std::function<void(copyCtlKey, String)> onButtonPressed;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);

	private:
#define COPY_VIEW 4
		enum CopyViewItemID
		{
			NO_FOCUS = 0,
			COPY_NAME,
			COPY_CANCEL,
			COPY_SAVE,
			FOCUS_MAX = COPY_SAVE
		};
		uint8_t CopyView[COPY_VIEW] = { NO_FOCUS, COPY_NAME, COPY_CANCEL, COPY_SAVE };
		int KeyFocusedItem = CopyViewItemID::NO_FOCUS;
		juce::FlexBox ctlBox;
		juce::FlexBox copyInsertBox;
		CommonLabel CopyLabel{ "Please enter name of the copy" };
		CommonKey CopyName{ " " };
		CommonImageButton closeBtn{ "close","ico-close.png" };
		CommonImageButton ctlCancel{ "ctrCancel","btn-cancel-267x44-default.png","btn-cancel-267x44-default-hover.png","btn-cancel-267x44-default-hover.png" };
		CommonImageButton ctlApply{ "ctrApply","btn-copypaste-267x44-default.png","btn-copypaste-267x44-default-hover.png","btn-copypaste-267x44-default-hover.png" };
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCopy)
	};
};