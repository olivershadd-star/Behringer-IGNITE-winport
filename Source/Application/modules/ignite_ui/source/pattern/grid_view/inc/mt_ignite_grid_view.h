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
	class IgniteSongConfig;
	class FrountPannel;

	class DrumNotestView : public Component
	{
	public:
		DrumNotestView(GridComponent& gridCompView)
			: gridComponent(gridCompView)
		{}

		int getNoteViewHeight()
		{
			return (int)(gridData->noteHeight * (totalPianoKeys + 1));
		}
		void setSelectedNote(int note) { selectedNote = note; }

	private:
		int selectedNote = -1;
		GridComponent& gridComponent;
		GridData* gridData{ gridComponent.getGridData() };

		void paint(Graphics& g) override;
		void mouseUp(const MouseEvent& event) override;
	};

	class ScaleComponent : public Component
	{
	public:

		std::function<void(const MouseEvent& event)> onMouseDown;

		ScaleComponent(GridComponent& gridView);
		void gridDataChanged();
		void setSelectedSteps(bool* _pSteps) { _pStepsState = _pSteps; }
		void setCurrentBar(int newBar) { currentBar = newBar; }

	private:
		void paint(Graphics& g) override;
		void resized() override;
		void mouseDown(const MouseEvent& event);
		bool getGateStatus(int stepIndex);
		int getStepId(int stepIndex);

		float tickWidth = 0;
		float playHeadXPos = 0;
		GridComponent& gridComponent;
		int currentBar = 0;
		bool* _pStepsState = nullptr;
		mt::Ignite::patternData* patternData = nullptr;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScaleComponent)
	};

	class AppGrid : public juce::Component,
		public CommonViewport::Listener,
		public CommonSlider::Listener,
		private Timer
	{
	public:
		AppGrid();
		~AppGrid() override;

		enum GRID_FOCUS
		{
			GRID_PARAM,
			GRID_OPTIONS,
			GRID_NOTES
		};

#define GRID_DETAL_VIEW 11
		enum gridViewItemID
		{
			NO_FOCUS = 0,
			VELO,
			LEN_ST,
			LEN_TK,
			DELAY,
			LEFT,
			RIGHT,
			ZOOM_LEFT,
			ZOOM_RIGHT,
			BAR_LEFT,
			BAR_RIGHT,
			FOCUS_MAX = BAR_RIGHT
		};

		uint8_t gridDetailView[GRID_DETAL_VIEW] = { NO_FOCUS, VELO, LEN_ST, LEN_TK, DELAY, LEFT, RIGHT, ZOOM_LEFT, ZOOM_RIGHT, BAR_LEFT, BAR_RIGHT };
		int keyFocusedItem = gridViewItemID::NO_FOCUS;
		int barIndex = 0;

		std::map<juce::String, mt::Ignite::nodeDataIndex> s_mapStringToParamValueIndex =
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
			{ "Len:Tick",   maxTickLength},
			{ "Offset",          maxDelay},
		};
		bool isSliderDragging = false;
		std::vector<mt::Ignite::selectedNode> prev_value;

		static AppGrid* getGridInstance()
		{
			static AppGrid* gridInstance;
			if (NULL == gridInstance)
			{
				gridInstance = new AppGrid();
			}

			return gridInstance;
		}

		void updateSliderRange();
		void refreshScreen();
		void refreshScaleComp() { repaint(); }
		void resetGridView() { parameterControl.refreshGridctrl(); }
		void updateOnViewPositionChange(CommonViewport* _pViewport);

		GridData* getGridData() { return gridComponent.getGridData(); }
		NoteManagement& getNoteManagement() { return gridComponent.getNoteManagement(); }
		ParameterViewControl& getParameterViewControl() { return parameterControl; };
		int getGridZoomValue() { return gridComponent.getZoomPercentage(); }
		GridToolType getActiveTool() { return gridComponent.getActiveTool(); }
		bool getOptionsHandlerState() { return optionHandlerEnabled; }
		int getCenterStep() { return centerStep; }

		void setViewType(GridViewType viewType);
		void setGangMode(bool state) { gridTools.setGangMode(state); }
		bool getGangMode() { return gridTools.isGangSelected(); }
		void setUndoButtonState(bool state) { gridTools.setUndoButtonState(state); }
		void setSculptButtonState(bool state) { gridTools.setSculptButtonState(state); }
		void setCopyButtonState(bool state) { gridTools.setCopyBtnState(state); }
		void setCutButtonState(bool state) { gridTools.setCutBtnState(state); }
		void setSculptState(bool state) { gridTools.setSculptState(state); }
		void setRowEdit(int8_t state) { isRowEditing = state; }
		void setStepNoteValues(paramId_t param);
		void setStepsNoteValues(paramId_t param);
		void setGridZoomInValue(int newVal) { gridComponent.setZoomFactor(gridComponent.getZoomPercentage() + newVal); gridComponent.repaint(); }
		void setGridZoomOutValue(int newVal) { gridComponent.setZoomFactor(gridComponent.getZoomPercentage() - newVal); gridComponent.repaint(); }

		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		void moveViewPortVertically(int note, int direction);
		void moveViewPortHorizontaly(int step, float swipeDistance = 0.0f);
		void moveViewPortVertically(int note);
		void toolTypeChanged(GridToolType toolType);
		bool isSelectToolActive() { return gridComponent.selectToolIsActive(); }
		int currentStepShowing = 0;
		void showNoteRGB();
		void showSelectedNoteRGB(int noteNum);
		void resetPencilToolState();

	private:
		Component* _pNoteViewComponent = nullptr;
		DrumNotestView* drumView = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;

		CommonViewport  scaleViewport;
		GridComponent gridComponent;
		ScaleComponent scaleComp{ gridComponent };
		CommonViewport  keyboardViewport;
		juce::MidiKeyboardState keyboardState;
		ParameterView  parameterView{ gridComponent.getGridData(), gridComponent.getNoteManagement() };
		ParameterViewControl parameterControl{ parameterView };

		CommonViewport  gridViewport;
		CommonViewport  parameterViewport;
		GridViewType viewType{ GridViewType::DrumView };
		AppGridControl gridTools;
		CommonSlider levelSlider{ Slider::LinearVertical, Slider::NoTextBox };

		int8_t isRowEditing = -1;
		int selectedStep = -1;

		int16_t sliderPrevValue = 0;
		int16_t offset = 0;
		std::vector<int> values;
		bool dragging = true;
		int stepFocusedId = 0;
		uint8_t optionHandlerEnabled = GRID_NOTES;
		FrountPannel* FrountPannelRef = nullptr;
		int rMoveLeftCount = 0;
		int rMoveRightCount = 0;
		int timerStarted = false;
		int centerStep = 5;
		int MaxOffsetVar = 0;
		int MaxLengthVar = 0;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void sliderValueChanged(juce::Slider* slider) override;
		void sliderDragEnded(juce::Slider* slider) override;
		void timerCallback() override;

		void updateGridDataWithOffset(int16_t offset, bool isPlayModeData, bool isSliderDragging);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void enableDisableButton(juce::Point<float> position, int stepIndex = 0);
		bool gridBarKeyHandler(paramId_t param, uint32_t keyValue);
		bool gridRowKeyHandler(paramId_t param, uint32_t keyValue);
		void handleCommandMessage(int id);
		void updateOffsetLength();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppGrid)
	};
}//namespace mt

