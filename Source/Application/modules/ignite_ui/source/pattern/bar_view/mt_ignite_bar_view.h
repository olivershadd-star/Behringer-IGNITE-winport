/*
* Copyright (C) Musictribe Innovation India Pvt. Ltd
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
	class StepPlayhead;
	class StepSequencer :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define BAR_PRESET_VIEW 6
#define BAR_DETAL_VIEW 15
#define BAR_OPTIONS_VIEW 6
		enum barViewItemID
		{
			NO_FOCUS = 0,
			GRID_NODE,
			PARAM,
			TIMEBASE,
			DIRECTION,
			LAST_STEP,
			PRESET,
			INSERT_BAR,
			GBAR_SYNC,
			XPOSE_DEFEAT,
			SCULPT,
			ROTATE_PATTERN,
			BAR_LEFT,
			BAR_RIGHT,
			BAR_REPEAT,
			FOCUS_MAX = BAR_REPEAT
		};
		enum BAR_FOCUS
		{
			BAR_PARAM,
			BAR_OPTIONS,
			BAR_STEPS,
			BAR_PRESETS
		};
		enum barOptionsViewItemID
		{
			BAR_NO_FOCUS = 0,
			BAR_GANG_EDIT,
			BAR_NOTE_EDIT,
			BAR_COPY,
			BAR_LOOP,
			BAR_UNDO,
			BAR_FOCUS_MAX = BAR_UNDO
		};
		enum barPresetViewItemID
		{
			BAR_PRESET_NO_FOCUS = 0,
			BAR_PRESET_RAMP,
			BAR_PRESET_PULSE,
			BAR_PRESET_TRIANGLE,
			BAR_PRESET_INVERSE,
			BAR_PRESET_FLIP,
			BAR_PRESET_FOCUS_MAX = BAR_PRESET_FLIP
		};

		StepSequencer();
		~StepSequencer() override;
		StepSequencerControl stepControl;

		static StepSequencer* getStepSequencerInstance()
		{
			static StepSequencer* getStepInstance;
			if (NULL == getStepInstance)
			{
				getStepInstance = new StepSequencer();
			}

			return getStepInstance;
		}

		void updateSliderRange();
		void updateAccidentals(bool state) { stepControl.updateAccidentals(state); }
		void updateLastStep(bool is_internal = false) { stepControl.updateLastStep(is_internal); };
		void updateIndication();
		void refreshBarData();

		var getParamValues(int index);
		StepSequencerControl& getStepSequencerControl() { return stepControl; };
		void getAssets();

		void setUndoButtonState(bool state) { optionUndo.setEnabled(state); }
		void setSculptState(bool state) { sculptBtn.setToggleState(state, sendNotification); }
		void setStepValues(paramId_t param, uint8_t value = 1);
		void setStepValues(paramId_t param, int index);
		void setBarStepValues(paramId_t param, uint32_t keyValue, int index);
		void setBarStepState(paramId_t param, int index);

		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		void enableBarInsertButton(bool state) { barInsert.setEnabled(state); }
		void enableBarCopyButton(bool state) { copy.setEnabled(state); }
		void enableRotatePatternButton(bool state) { patternRotateBtn.setEnabled(state); }
		void refreshBarUI();
		void setFpStepNodeLedState();
		void setFpStepGangLedState();
		void setPencilIconState(bool state);
		void setGangButtonState();

		uint8_t barDetailView[BAR_DETAL_VIEW] = { NO_FOCUS, GRID_NODE, PARAM, TIMEBASE, DIRECTION, LAST_STEP, PRESET, INSERT_BAR, GBAR_SYNC, XPOSE_DEFEAT, SCULPT, ROTATE_PATTERN, BAR_LEFT, BAR_RIGHT, BAR_REPEAT, };
		int keyFocusedItem = barViewItemID::NO_FOCUS;
		int barPresetKeyFocusedItem = barPresetViewItemID::BAR_PRESET_NO_FOCUS;
		int barKeyFocusedItem = barOptionsViewItemID::BAR_NO_FOCUS;
		void updateLegnthDelay();
		void setSulptKeyStatus(bool state) { sculptKeyStatus = state; }
		bool getSulptKeyStatus() { return sculptKeyStatus; }
	private:
		AppMainmode* _pMainmodePtr = nullptr;
		StepPlayhead* _pPlayHead = nullptr;
		FrountPannel* frontPanelPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;
		IgniteControlOptions* optPtr = nullptr;
		IgnitePattern* _pPatternComp = nullptr;
		mt::Ignite::patternData* patternData = nullptr;

		std::map<juce::String, mt::Ignite::nodeDataIndex> s_mapStringToParamValueType =
		{
			{ "Velocity",       mt::Ignite::nodeDataIndex::VELO },
			{ "Len:Steps",  mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP},
			{ "Len:Tick",   mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK},
			{ "Offset",          mt::Ignite::nodeDataIndex::DELAY},
		};

		std::map<juce::String, int> s_mapStringToParamMaxType =
		{
			{ "Velocity",       maxVelocity},
			{ "Len:Steps",  maxStepLength},
			{ "Len:Tick",   maxTickLengthVar},
			{ "Offset",       maxDelayVar},
		};

		StepPresets stepPreset;
		FlexBox barOptionFlex1;
		FlexBox barOptionFlex2;
		FlexBox barOptionFlex3;
		juce::Rectangle<float> getLevelButtonRect(int index);
		juce::Rectangle<float> getStepButtonRect(int index);
		juce::Rectangle<float> stepRect;
		juce::Rectangle<float> levelRect;
		ui::CommonButton leftNudgeButton;
		ui::CommonButton nudgeText;
		ui::CommonButton rightNudgeButton;
		CommonButton patternRotateBtn{ "" };
		CommonButton barInsert{ "" };
		CommonImageButton gbarSync{ "GBARSYNC","btn-toggle176x36-gbar-default.png","btn-toggle176x36-gbar-active.png","btn-toggle176x36-gbar-default-hover.png" };
		CommonImageButton xposeDefeat{ "XPOSEDEFEAT","btn-toggle176x36-transpose-default.png","btn-toggle176x36-transpose-active.png","btn-toggle176x36-transpose-default-hover.png" };
		CommonImageButton sculptBtn{ "SCULPT","btn-link105x36-sculpt-default.png","btn-link105x36-sculpt-active.png","btn-link105x36-sculpt-default-hover.png" };
		CommonNameLabel	barLoopCountLable{ "BAR REPEAT" };
		CommonNumber barLoopCount{ "Bar Repeat", 0, 200, 1 };
		CommonImageButton copy{ "COPY" ,"btn-copy-default.png","btn-copy-active.png","btn-copy-default-hover.png" };
		CommonImageButton loop{ "Loop", "btn-loop-default.png", "btn-loop-active.png","btn-loop-default-hover.png" };
		CommonImageButton optionUndo{ "UNDO","btn-undo-default.png","btn-undo-active.png","btn-undo-default-hover.png" };
		CommonImageButton gangBtn{ "GANG","btn-gangedit-120x44-default.png","btn-gangedit-120x44-active.png","btn-gangedit-120x44-default-hover.png" };
		CommonImageButton imageButtonPencil{ "PENCIL","btn-pen-default.png","btn-pen-active.png","btn-pen-default-hover.png" };

		Image insertDefaultImage, insertHoverImage, rotateDefaultImage, rotateHoverImage, scrollDefaultImage, scrollHoverImage,
			scrollLeftDefaultImage, scrollLeftHoverImage, scrollRightDefaultImage, scrollRightHoverImage, bgDefaultImage, bgHoverImage;

		bool isPresetsEnabled = false;
		bool isSliderDragging = false;
		bool isMouseDragEnd = false;
		bool dragging = true;
		bool sculptKeyStatus = false;
		bool isGangModeEnabled = false;
		bool* stepsState;
		int maxDelayVar = 0;
		int maxTickLengthVar = 0;
		juce::Colour noteColour, white, orange, grey3, grey2, grey4;
		juce::String currentControl;

		uint8_t barPresetView[BAR_PRESET_VIEW] = { BAR_PRESET_NO_FOCUS, BAR_PRESET_RAMP, BAR_PRESET_PULSE, BAR_PRESET_TRIANGLE, BAR_PRESET_INVERSE, BAR_PRESET_FLIP };
		uint8_t barOptionsView[BAR_OPTIONS_VIEW] = { BAR_NO_FOCUS, BAR_GANG_EDIT, BAR_NOTE_EDIT, BAR_COPY, BAR_LOOP, BAR_UNDO };
		uint8_t optionHandlerEnabled = BAR_PARAM;

		int rangeLow = 0;
		int rangeHigh = 0;
		int lastIndex = -1;
		int currentNote = 0;
		int currentBar = 1;
		int barIndex = 0;
		int startIndex = 0;
		int selectedStep = -1;
		int stepFocusedId = -1;
		int prevValue[16];
		int barNum, stepThreshold, barId, activeStepIndex;
		int noteColourIntensity;
		uint8_t currentPattern = 0;

		float markingWidth, markingY, unitHeightCache;
		float buttonWidth = 0;
		std::vector<bool> selectedIndex{ false };

		virtual void resized() override;
		void paint(juce::Graphics& g) override;
		virtual void mouseDrag(const MouseEvent& event) override;
		virtual void mouseUp(const MouseEvent& event) override;
		virtual void mouseDown(const MouseEvent& event) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) override;

		int isEditing();
		void cleanup();
		void updateBarData();
		void calculateButtonWidth();
		void enableDisableButton(juce::Point<float> position, int stepIndex = -1);
		void setParamToEngine(juce::String param, int index, int16_t data);
		var getParamFromEngine(juce::String param, int index);
		bool getGateStatus(int stepIndex);
		void updateLableText(mt::Ignite::ptDataIndex item_id, bool state);
		void handleCommandMessage(int id);
		bool pannelKeyOptionsHandler(paramId_t param, uint32_t keyValue);
		bool barKeyHandler(paramId_t param, uint32_t keyValue);
		void pannelSendOptionsKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		bool presetKeyHandler(paramId_t param, uint32_t keyValue);
		void pannelSendPresetKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		bool handleTrackSelection(paramId_t param, uint32_t KeyValue);
		bool handleGang(paramId_t param, uint32_t KeyValue);
		bool handleBar(paramId_t param, uint32_t keyValue);
		bool handleRotary(paramId_t param, uint32_t keyValue);
		bool handleInsert(paramId_t param, uint32_t KeyValue);
	};
}