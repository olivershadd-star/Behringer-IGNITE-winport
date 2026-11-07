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
#include <common_ui_controls/source/common_keyboard.h>

namespace ui
{
	class AppTrackOpt;
	class IgniteCustomScale;

	class IgniteCustomScaleOpt :
		public juce::Component,
		public CommonButton::Listener
	{
	public:
#define SCENE_UDS_NO_COM_ROW 3
		IgniteCustomScaleOpt(IgniteCustomScale* iPtr);
		~IgniteCustomScaleOpt() override;


		void refreshData();
		void selectNoteValue(int index);
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);

		static IgniteCustomScaleOpt* getcustomScaleInstanceOpt(IgniteCustomScale* tPtr)
		{
			static IgniteCustomScaleOpt* instanceCustomScaleOpt;
			if (NULL == instanceCustomScaleOpt)
			{
				instanceCustomScaleOpt = new IgniteCustomScaleOpt(tPtr);
			}
			return instanceCustomScaleOpt;
		}

	private:
#define UDS_ITEMS 13
		enum udsViewItemID
		{
			NO_FOCUS = 0,
			NOTE1,
			NOTE2,
			NOTE3,
			NOTE4,
			NOTE5,
			NOTE6,
			NOTE7,
			NOTE8,
			NOTE9,
			NOTE10,
			NOTE11,
			APPLY_NOTE_VALUES,
			FOCUS_MAX = APPLY_NOTE_VALUES
		};

		int keyFocusedItem = udsViewItemID::NO_FOCUS;
		uint8_t udsViewItems[UDS_ITEMS] = { NO_FOCUS, NOTE1, NOTE2, NOTE3, NOTE4, NOTE5, NOTE6, NOTE7, NOTE8, NOTE9, NOTE10, NOTE11, APPLY_NOTE_VALUES };

		IgniteCustomScale* scalePtr = nullptr;
		juce::FlexBox InstrBox_colume1;
		juce::FlexBox InstrBox_colume2;
		juce::FlexBox InstrBox_colume3;
		juce::FlexBox InstrBox_colume4;
		CommonPopUp* ptr=nullptr;
		bool firstIndex{ true };

		CommonImageButton udsApplyBtn{ "Apply Note Values","link-apply-note-icon-default.png","link-apply-note-icon-default-hover.png","link-apply-note-icon-default-hover.png" };
		Array<CommonListBox*> listofListBox;
		std::vector<juce::String> scaleNoteValueList{ "None", "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };
		void updateNoteList();
		int isEditing();
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void updateListBoxOptions(int index, const juce::String& sValue);
		void paint(juce::Graphics& g) override;
		void resized() override;
		virtual void buttonClicked(juce::Button* buttonThatWasClicked) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCustomScaleOpt)
	};
};
