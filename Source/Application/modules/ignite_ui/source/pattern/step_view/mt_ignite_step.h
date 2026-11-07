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
	class IgnitePattern;
	class IgniteStepNoteList;
	class IgniteStepEventList;

	class IgniteStep :
		public juce::Component,
		public juce::Button::Listener,
		public CommonLabel::Listener,
		public IgniteControlOptions::Listener
	{
	public:
		CommonImageButton tieButton{ "TIE","pattern-selection-tie-default.png","pattern-selection-tie-active.png","pattern-selection-tie-default-hover.png" };
		CommonImageButton xposeDefeatButton{ "XPOSEDEFEAT","pattern-selection-transposedefeat-default.png","pattern-selection-transposedefeat-active.png","pattern-selection-transposedefeat-default-hover.png" };
		CommonImageButton skipButton{ "SKIP","pattern-selection-skip-default.png","pattern-selection-skip-active.png","pattern-selection-skip-default-hover.png" };
		CommonImageButton gateButton{ "GATE","pattern-selection-step-default.png","pattern-selection-step-active.png","pattern-selection-step-default-hover.png" };

		IgniteStep(IgnitePattern* ptr, ClientPatternStepData& data);
		~IgniteStep() override;

		void updateStepData();
		void updateAccidentals(ClientPatternStepData* stepData, bool state);
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void setActiveNoteRow(int row, bool force_update);
		void setActiveEventRow(int row, bool force_update);
		void setActiveNote(int noteNum) { activeNoteNumber = noteNum; }
		void setActiveEvent(int eventNum) { activeEventNumber = eventNum; }
		void handleDeleteEvent();
		int getPrevStepIndex() { return prevStepIndex; }
		void setPrevStepIndex(int stepIndex) { prevStepIndex = stepIndex; }
		int getEditBar() { return editBar; }
		int getEditStep() { return editStep; }
		void setEditStep(int step) { editStep = step; }
		void setEditBar(int bar) { editBar = bar; }

		static IgniteStep* getStepInstance(IgnitePattern* ptr, ClientPatternStepData& data)
		{
			static IgniteStep* getStepObj;
			if (NULL == getStepObj)
			{
				getStepObj = new IgniteStep(ptr, data);
			}
			return getStepObj;
		}

	private:
#define STEP_DETAL_VIEW 15
		enum stepViewItemID
		{
			NO_FOCUS = 0,
			BAR_LEFT, //Row 1
			BAR_RIGHT,
			STEP_LEFT,
			STEP_RIGHT,
			TIE,
			XPOSE,
			SKIP,
			GATE,
			NOTE_LIST,
			EVENT_LIST,
			NOTE,
			VELO,
			DELAY,
			LEN,
			FOCUS_MAX = LEN
		};

		IgnitePattern* _pPatternPtr = nullptr;
		ClientPatternStepData& sData;
		ClientPatternStepData* currentStepData = nullptr;
		IgniteControlOptions* _pStepOptCtl = nullptr;
		FrountPannel* FrountPannelRef = nullptr;

		juce::OwnedArray<IgniteStepNoteList> stepNotelist;
		juce::OwnedArray<IgniteStepEventList> stepEventlist;

		uint8_t stepView[STEP_DETAL_VIEW] = { NO_FOCUS, BAR_LEFT, BAR_RIGHT, STEP_LEFT, STEP_RIGHT, TIE, XPOSE, SKIP, GATE, NOTE_LIST, EVENT_LIST, NOTE, VELO, DELAY, LEN };
		int keyFocusedItem = stepViewItemID::NO_FOCUS;
		int noteListFocused = -1;
		int eventListFocused = -1;
		bool addNewNoteInListHighlighted = false;
		bool addNewEventInListHighlighted = false;
		int prevStepIndex = -1;
		int editBar = 0;
		int editStep = 0;

		juce::Viewport view;
		juce::Component container;
		juce::FlexBox barLableBox;
		juce::FlexBox stepLableBox;

		CommonImageButton addNewNoteEmpty{ " Insert New Note ","pattern-step-table-bg-disabled.png","pattern-step-table-bg-disabled.png","pattern-step-table-bg-disabled.png" };
		CommonImageButton addNewNoteInList{ " Insert New Note ","btn-insert-note-default.png","btn-insert-note-default.png","btn-insert-note-hover.png" };
		CommonImageButton addNewEventInList{ " Insert New Event","btn-insert-event-default.png","btn-insert-event-default.png","btn-insert-event-hover.png" };
		CommonImageButton noteListBtn{ "NOTELIST","pattern-step-toogle-notelist-default.png","pattern-step-toogle-notelist-active.png","pattern-step-toogle-notelist-default-hover.png" };
		CommonImageButton eventListBtn{ "EVENTLIST","pattern-step-toogle-eventlist-default.png","pattern-step-toogle-eventlist-active.png","pattern-step-toogle-eventlist-default-hover.png" };

		CommonButton helpInfoButtonA;
		CommonButton helpInfoButtonB;
		CommonButton prevBarButton;
		CommonButton barButton{ "BAR 1/1" };
		CommonButton nextBarButton;
		CommonButton prevStepButton;
		CommonButton stepButton{ "STEP 1/16" };
		CommonButton nextStepButton;

		CommonButton addNoteBtn{ "Insert" };

		CommonNameLabel noteLable{ "NOTE" };
		CommonNameLabel veloLable{ "VELOCITY" };
		CommonNameLabel offsetLable{ "OFFSET" };
		CommonNameLabel lenLable{ "LENGTH" };

		CommonNameLabel emptyLable1{ "--" };
		CommonNameLabel emptyLable2{ "--" };
		CommonNameLabel emptyLable3{ "--" };
		CommonNameLabel emptyLable4{ "--" };
		CommonNameLabel emptyLable5{ "--" };

		uint8_t activeNoteRow = 0;
		int activeEventRow = 0;
		int activeNoteNumber = 0;
		int activeEventNumber = 0;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void labelTextChanged(Label* labelThatHasChanged) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) {};// override;
		void enableControlButton(IgniteControlOptions::eKey key, bool state) { _pStepOptCtl->enableKey(key, state); };

		int isEditing();
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void setListBtnText(bool state);
		void handleCommandMessage(int id);
		void handleNoteList(paramId_t param, uint32_t keyValue);
		void handleEventList(paramId_t param, uint32_t keyValue);
		void getNextStepAndUpdate(bool direction);
		void getNextBarAndUpdate(bool direction);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteStep)
	};
};
