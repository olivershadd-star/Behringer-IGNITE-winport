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
class AppHome;
namespace ui
{
	class IgnitePatternRow :
		public juce::Component,
		public CommonLabel::Listener,
		public CommonButton::Listener
	{
	public:

		IgnitePatternRow(int SerialNumber, mt::Ignite::patternData& Data, IgnitePattern* patternPtr);
		~IgnitePatternRow();

		std::function<void(IgnitePatternRow*)> onMouseDown;

		void highlight(bool state);
		int getSerialNumber();
		void refreshPatternRowUI();
		void updateEditIndication();
		void setColor(int colourID, Colour colour);
		void setFocus(bool hasFocus, bool hasActiveFoces);
		bool pannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool isEditing() { return name.isEditing; }
		void updateLastStep(bool update_from_engine, bool is_internal = false);
		void setLastSelectedStep(int selectedStepId) { lastStep.setSelected(selectedStepId); }
		void enableBarEditButton(bool state);
		void enableRotatePatternButton(bool state);
		void updateLengthandOffset();
		VariableMinMax getLengthRange() {return lenthMinMax;}
		VariableMinMax getOffsetRange() { return offsetMinMax; }
		int getLastStepIndex() { return lastStep.getSelectedIndex(); }
	private:
		IgnitePattern* _pPatternParentPtr = nullptr;
		juce::FlexBox box;
		mt::Ignite::patternData& data;

		CommonListBox lastStep{ "Last Step", 4 };
		CommonListBox direction{ "Direction", 2 };
		CommonListBox numOfBars{ "Number of Bars", {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"}, 0, 4 };
		CommonListBox firstStep{ "Change First Step", 4 };
		CommonListBox timeBase{ "Time Base", 4 };
		CommonButton patternRotateBtn{ "Rotate" };
		VariableMinMax lenthMinMax;
		VariableMinMax offsetMinMax;

		CommonSerialNumber srNo{ "1" };
		CommonKey name{ "" };
		CommonLabel trackNum{ "TRACK NUM", "1" }, fill{ "FILL", "abcdef" }, instrument{ "INSTRUMENT", "SYNTH 1" }, trackname{ "TRACK", "abcdef" };
		CommonImageButton options{ "Options", "Edit.png" };
		CommonLabel patternState{ "INACTIVE" };

		String serialNumber = "1";
		bool rowIsBeingDraggedOver = false;
		bool isHighlighted{ false };
		bool isDirectionAtBarlevel = false;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void mouseDown(const MouseEvent& event) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void labelTextChanged(Label* labelThatHasChanged) override;
		void mouseUp(const MouseEvent& event) override;
		void mouseDrag(const MouseEvent& event) override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		bool isMouseOver{ false };

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgnitePatternRow)
	};

	///////////////////////////////////////////////////////////////////////
	// Pattern step Playhead
	///////////////////////////////////////////////////////////////////////
	class StepPlayhead : public juce::Component
	{
	public:
		StepPlayhead();
		~StepPlayhead();

		void SetViewBounds(ui::Rectangle<float> b)
		{
			bounds = b;
			ButtonWidth = b.getWidth();
		};
		void setViewColour(juce::Colour c)
		{
			colour = c;
		}
		static StepPlayhead* getPlayHeadInstance()
		{
			static StepPlayhead* getInstance;
			if (NULL == getInstance)
			{
				getInstance = new StepPlayhead();
			}

			return getInstance;
		}
	private:
		IgnitePattern* _pParent = nullptr;
		IgniteControlOptions* optPtr = nullptr;

		int stepNo = 0;
		float ButtonWidth = 0;
		ui::Rectangle<float> bounds;
		juce::Colour colour;

		virtual void paint(juce::Graphics& g) override;
		virtual void resized() override {};

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StepPlayhead)
	};
};
