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

	class IgniteLoopControl : public juce::Component,
		public CommonButton::Listener
	{
	public:
		enum class loopKey {
			NONE,
			START,
			END,
			APPLY,
			CANCEL,
			CLEAR,
			INVALID,
		};

		IgniteLoopControl(std::vector<juce::String>* itemList);
		~IgniteLoopControl() override;

		std::function<void(loopKey, int, int)> onButtonPressed;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void setLoopStartIndex(int startIndex) { loopStartIndex = startIndex; };
		void setLoopEndIndex(int endIndex) { loopEndIndex = endIndex; };

		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int IsEditing();
		void setTitle(String s) { Title.setText(s,dontSendNotification); };
	private:
		juce::FlexBox ctlBox;
		juce::FlexBox loopBox1;
		juce::FlexBox loopBox2;
		juce::FlexBox loopBox;
		int loopStartIndex = 0;
		int loopEndIndex = 0;
		int FocusIndex = 0;

		CommonButton loopStart;
		CommonButton loopEnd;
		CommonListBox loopStartSceneBox{ "Loop Start", 1 };
		CommonListBox loopEndSceneBox{ "Loop End", 1 };

		CommonImageButton ctlApply{"Apply","btn-apply-174x44-default.png","btn-apply-174x44-active.png","btn-apply-174x44-default-hover.png"};
		CommonImageButton ctlCancel{"Cancel","btn-cancel-174x44-default.png","btn-cancel-174x44-active.png","btn-cancel-174x44-default-hover.png"};
		CommonImageButton ctlclear{"clear","btn-clearloop-174x44-default.png","btn-clearloop-174x44-active.png","btn-clearloop-174x44-default-hover.png"};
		CommonLabel Title{ " " };
		std::vector<juce::String>* loopList;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteLoopControl)
	};
}
