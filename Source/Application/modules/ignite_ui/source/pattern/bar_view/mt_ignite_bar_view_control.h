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
	class StepSequencerControl : public juce::Component,
		public juce::Button::Listener
	{
	public:

		StepSequencerControl();
		~StepSequencerControl() override;

		sig::Signal<bool> leftNudgeChanged;
		sig::Signal<bool> rightNudgeChanged;

		void setPresetButtonVisibility(bool state);
		void setSelectedLastStep(int stepId) { lastStepListBox.setSelected(stepId); }
		void setSelectedFirstStep(int stepId) { firstStepListBox.setSelected(stepId); }
		void setFirstStepFPHandler(bool isFocuse, paramId_t param, uint32_t keyValue) { firstStepListBox.FPKeyHandler(isFocuse, param, keyValue); }

		int getLastStepEditStatus() { return lastStepListBox.IsEditing(); }
		int getFirstStepEditStatus() { return firstStepListBox.IsEditing(); }
		int getPadListBoxEditStatus() { return padListBox.IsEditing(); }
		int getParamValueListBoxEditStatus() { return paramValueListBox.IsEditing(); }
		int getTimeBaseValueListBoxEditStatus() { return timeBaseValueListBox.IsEditing(); }
		int getDirectionListBoxEditStatus() { return directionListBox.IsEditing(); }

		void enableDisableNoteBox(bool state);
		void showFirstStepListBox() { firstStepListBox.showList(); }
		void updateAccidentals(bool state);
		void updateLableText(mt::Ignite::ptDataIndex item_id, bool state);
		void updateLastStep(bool is_internal = false);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);

	private:
		void updateRangeText();

	SIGNALS:
		//timediv, parameter, range low, range high, note, bar
		sig::Signal <juce::String > controlParamChanged;
		sig::Signal<bool> presetOn;

	private:
		enum e_paramValueType {
			eMIN,
			eVelocity,
			eLengthSteps,
			eLengthTick,
			eDelay,
			eMAX
		};
		std::map<juce::String, e_paramValueType> s_mapStringToParamValueType =
		{
			{ "Velocity",       eVelocity },
			{ "Len:Steps",  eLengthSteps },
			{ "Len:Tick",   eLengthTick},
			{ "Offset",          eDelay},

		};

		CommonLabel gridNote{ "GRID NOTE" };
		CommonLabel parameter{ "PARAMETER" };
		CommonLabel timeBaseLabel{ "TIME BASE" };
		CommonLabel direction{ "DIRECTION" };
		CommonLabel lastStep{ "LAST STEP" };

		CommonImageButton presetsButton{ "PRESET","btn-link99x36-preset-default.png","btn-link99x36-preset-active.png","btn-link99x36-preset-default-hover.png" };
		ui::CommonButton BarInfoButton{ TRANS("1/1") };
		ui::CommonButton leftRangeButton{ TRANS("<") };
		ui::CommonButton rightRangeButton{ TRANS(">") };

		ui::CommonListBox firstStepListBox{ ui::CommonListBox::BoxType::withTitleBar,"Change First Step", {""},0, 4 };
		ui::CommonListBox padListBox{ ui::CommonListBox::BoxType::withTitleBar, "Grid Note", {"C 4"}, 48, 4 };
		ui::CommonListBox paramValueListBox{ ui::CommonListBox::BoxType::withTitleBar,"Parameter", {"Velocity", "Len:Steps", "Len:Tick",  "Offset"}, 0, 2 };
		ui::CommonListBox timeBaseValueListBox{ ui::CommonListBox::BoxType::withTitleBar,"Time Base", {""},0, 4 };
		ui::CommonListBox directionListBox{ ui::CommonListBox::BoxType::withTitleBar,"Direction", {""},0, 2 };
		ui::CommonListBox lastStepListBox{ ui::CommonListBox::BoxType::withTitleBar,"Last Step", {""},0, 4 };

		juce::String sparamListValue = "Velocity";
		FlexBox controlFlex1;
		FlexBox controlFlex2;
		std::vector<juce::String> padData, barsData;

		int totalBars = 1;
		int rangeLow = 1;
		int rangeHigh = 16;
		int threshold = 127;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StepSequencerControl)
	};
}
