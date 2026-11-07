/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
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
	class CommonTrackButton : public juce::Component, private juce::Timer
	{
	public:
		typedef enum
		{
			Title = 0,
			LeftLabel,
			RightLabel,
			TopLable,
			All
		}Contains;

		typedef enum
		{
			OFF = 0,
			ON
		}STATE;

		CommonTrackButton();
		class Listener
		{
		public:
			virtual ~Listener() = default;
			virtual void onMouseDoubleClicked(CommonTrackButton*) = 0;
			virtual void onMouseClicked(CommonTrackButton*) = 0;

		};

		void addListener(Listener* newListener);
		void setColour(Colour);
		void removeListener(Listener* listener);
		void mouseDoubleClick(const MouseEvent& event) override;
		void mouseDown(const MouseEvent& event) override;
		void setTitle(String);
		void setlabels(String, String, String);
		void setTextFont(Contains, const Font&);
		void setTextBackgroundColour(Contains, Colour);
		void setTextOutlineColourId(Contains, Colour);
		void setTextColour(Contains, Colour);
		void setButtonOnColour(Colour);
		void setToggleState(bool state);
		bool getToggleState() { return State; };
		void setSoloState(bool state);
		void setEditState(bool state) { 
			isEditing = state; repaint(); };
		void repaintbtn() { repaint(); };
		void handleMouseDoubleClick();
		void handleMouseSingleClick();
		void setFocusState(bool state);
	private:
		CommonLabel title{ "" };
		Image defaultImage;
		Image ActiveImage;
		CommonLabel bottomlable1{ "No Pattern" };
		CommonLabel toplable{ "---" };
		CommonLabel bottomlable2{ "No Instrument" };
		Colour colourid;
		Colour buttonOnColour;
		Colour buttonOffColour;
		ListenerList<Listener> Listeners;

		bool State = STATE::OFF;
		bool NextState = STATE::ON;
		bool soloState = false;
		bool isEditing = false;
		bool focusState{ 0 };
		juce::Time lastClickTime;
		bool isSingleClickPending = false;
		const int doubleClickTimeoutMs = 400;
		const int singleClickTimeoutMs = 300;

		void timerCallback() override
		{
			stopTimer();

			if (isSingleClickPending)
			{
				Component::BailOutChecker checker(this);
				if (checker.shouldBailOut())
					return;

				isSingleClickPending = false;
				handleMouseSingleClick();

				Listeners.callChecked(checker, [this](Listener& l) {
					l.onMouseClicked(this);
					});
			}
		}

		void resized() override;
		virtual void paint(Graphics& g) override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonTrackButton)
	};
}

