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
	class IgniteStep;
	class PatternBarLengthCtl;

	class IgniteStepNoteList : public juce::Component,
		public CommonButton::Listener
	{
	public:
		IgniteStepNoteList(int SerialNumber, ClientPatternStepData& StepData, IgnitePattern* patternPtr, IgniteStep* stepPtr);
		~IgniteStepNoteList();

		std::function<void(IgniteStepNoteList*)> onMouseDown;
		void highlight(bool state);
		int getSerialNumber();
		void refreshStepNoteListRowUI(ClientPatternNodeData noteData);
		void updateAccidentals(bool state);
		int getCurrentNoteNumber();
		void setFocus(bool hasFocus, bool hasActiveFoces);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);

	private:
		IgnitePattern* _pPatternPtr = nullptr;
		PatternBarLengthCtl* _pPatternBarLengthComp = nullptr;
		IgniteStep* _pStepPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;

		CommonListBox noteListBox{ "Note", 4 };
		CommonNumber velocomp{ "Velocity", minVelocity, maxVelocity, defVelocity };
		CommonNumber delaycomp{ "Offset", -16, 15, 0 };
		CommonButton noteLen{ "Length" };
		CommonNameLabel lengthValue{ "" };

		CommonSerialNumber srNo{ "1" };
		juce::Viewport view;
		juce::Component container;
		String step;
		String tick;

		ClientPatternStepData& data;
		juce::Viewport dialogViewPort;

		bool isHighlighted{ false };
		bool isFocused = { false };
		bool isMouseOver = { false };
		int currentNode = 0;
		int currentRow = 0;

		void updateLengthData();
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;

		void mouseUp(const MouseEvent& event) override;

		void mouseMove(const MouseEvent& event) override
		{
			if (!isFocused)
			{
				isFocused = isMouseOver = true;
				repaint();
			}
		};
		void mouseExit(const MouseEvent& event) override
		{
			isFocused = isMouseOver = false;
			repaint();
		};
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteStepNoteList);
	};

	class IgniteStepEventList : public juce::Component,
		public CommonButton::Listener
	{
	public:
		IgniteStepEventList(int SerialNumber, ClientPatternStepData& StepData, IgnitePattern* patternPtr, IgniteStep* stepPtr);
		~IgniteStepEventList();

		std::function<void(IgniteStepEventList*)> onMouseDown;
		void highlight(bool state);
		int getSerialNumber();
		void refreshStepEventListRowUI(Aux data);
		int getCurrentEventNumber();
		void setFocus(bool hasFocus, bool hasActiveFoces);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);

	private:
		IgnitePattern* _pPatternPtr = nullptr;
		IgniteStep* _pStepPtr = nullptr;

		CommonImageButton eventState{ "AUXENABLE","aux-toggle-noborder-off.png","aux-toggle-noborder-on.png","aux-toggle-noborder-off-hover.png" };

		CommonListBox eventList{ "EVENT",  {mt::Ignite::eventList}, 0, 1 };
		CommonListBox ccList{ "CC",  {mt::Ignite::midiccVal}, 0, 4 };
		CommonListBox noteList{ "CC",  {mt::Ignite::midiNoteNamesSharps}, 0, 4 };
		CommonNumber midiCCVal{ "CC VALUE", minMidi, maxMidi, defMidi };
		CommonNumber offsetComp{ "Offset", 0, 31, 0 };
		CommonNumber dataAComp{ "", 0, 127, 0 };
		CommonSerialNumber srNo{ "1" };

		juce::Viewport view;
		juce::Component container;

		bool isHighlighted{ false };
		bool isFocused = { false };
		bool isMouseOver{ false };
		ClientPatternStepData& data;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void mouseUp(const MouseEvent& event) override;
		void handleCommandMessage(int id);

		void mouseMove(const MouseEvent& event) override
		{
			isFocused = isMouseOver = true;
			repaint();
		};
		void mouseExit(const MouseEvent& event) override
		{
			isFocused = isMouseOver = false;
			repaint();
		};

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteStepEventList);
	};
};
