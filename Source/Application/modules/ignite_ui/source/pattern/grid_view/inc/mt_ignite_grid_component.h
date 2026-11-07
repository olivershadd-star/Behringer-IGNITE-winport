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
	class GridComponent : public juce::Component
	{
	public:
		GridComponent();
		~GridComponent();

		void setQuantizationLevel(int qL);
		void setPosition(int bar, int beat, int tick);
		void setBarBeatAndTimeSignature(int bars, int num, int den);
		void setZoomFactor(double zoomValue);
		void setGridViewType(GridViewType newGridViewType) { viewType = newGridViewType; }

		int getZoomPercentage() { return gridData.getZoomPercentage(); }
		int getMinimumWidth() { return minimumWidth; }
		GridData* getGridData() { return &gridData; }
		GridToolType getActiveTool() { return currentTool->getType(); }
		NoteManagement& getNoteManagement() { return noteMgmt; }

		void noteSelectionChanged(int note);
		void toolTypeChanged(GridToolType toolType);
		void updateVisibleViewportRegion(const Rectangle<int>& viewportRegion);
		void refreshGrid(bool sliderState, std::vector<mt::Ignite::selectedNode>* values);
		bool selectToolIsActive() { return seletionIsActive; }
		bool pencilToolIsActive() { return pencilIsActive; }
		void refreshGridData();
		void updateOffsetLength();

	private:
		//caluclate row column start values depending on the visible are
		void updateGridSize();
		void updateNotesFromTrack();

	private:
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
			{ "Len:Tick",   MaxOffsetVar},
			{ "Offset",          MaxLengthVar},
		};

		//to convert to multi dimensional array for faster lookup
		NoteManagement noteMgmt;
		GridData gridData;
		std::list<IGridTool*> tools;
		std::vector<mt::Ignite::selectedNode>* noteValues;
		IGridTool* currentTool;
		GridViewType viewType;
		IgniteControlOptions* optPtr = nullptr;
		IgnitePattern* _pPatternComp = nullptr;
		mt::Ignite::patternData* patternData = nullptr;
		bool* _pStepsState;

		int noteHighLightRow = -1;
		int stepHighLightCol = -1;
		int minimumWidth = 0;
		int currentBar = 0;
		int currentBeat = 0;
		int currentTick = 0;
		bool seletionIsActive = false;
		bool pencilIsActive = false;
		bool sliderDragging = false;
		int barNum, stepThreshold, barId, activeStepIndex;
		uint8_t currentPattern = 0;
		int totalKeys;
		float cellHeight;
		float cellWidth;
		float outlineThickness;
		float highlightThickness;
		mt::Ignite::operatioMode opMode = mt::Ignite::operatioMode::IDLE_MODE;
		bool playMode = false;
		bool recordMode = false;
		int MaxOffsetVar = 0;
		int MaxLengthVar = 0;

		juce::String currentControl;
		juce::Colour noteColour100, noteColour30, outlineColour5, outlineColour6, outlineColour8, backgroundColour5, backgroundColour9
			,selectionColour1, selectionColour3, nodeTextColour, noteColourIntensity;

		void resized() override;
		void paint(juce::Graphics& g) override;
		virtual void mouseUp(const MouseEvent& event) override;
		virtual void mouseMove(const MouseEvent& event) override;
		virtual void mouseDrag(const MouseEvent& event) override;
		virtual void mouseDown(const MouseEvent& event) override;
		virtual void mouseDoubleClick(const MouseEvent& event) override;
		int getNoteValue(int step, int note);
		void insertTimeSig(int bar, int num, int den);
		void deleteTimeSig(int bar);
		void drawUI(juce::Graphics& g);
		var getParamFromEngine(mt::Ignite::nodeDataIndex, int step_index, int note_indes);
		bool getGateStatus(int stepIndex);
		int getStepId(int stepIndex);
		bool isNotePreset(int step, int note);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridComponent)
	};
}//namespace ui

