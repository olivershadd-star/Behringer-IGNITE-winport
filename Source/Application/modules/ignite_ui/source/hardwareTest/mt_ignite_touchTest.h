/*
 * Copyright (c) - 2024 - MUSIC Tribe, MY.
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
	class TouchscreenTestComponent : public juce::Component
	{
	public:
		TouchscreenTestComponent()
		{
			setInterceptsMouseClicks(true, true); // Ensure touch events are handled
		}

		void resized() override
		{
			cellWidth = getWidth() / gridColumns;
			cellHeight = getHeight() / gridRows;

			// Initialize grid state for each cell
			gridState.clear();
			cellColors.clear();
			for (int i = 0; i < gridRows * gridColumns; ++i)
			{
				gridState.add(false); // Each cell starts as untouched
				cellColors.add(juce::Colour::fromHSV(float(i) / (gridRows * gridColumns), 0.8f, 0.8f, 1.0f)); // Unique color for each cell
			}

			// Set up colors for the color bar test at the top
			colorTestColors = { juce::Colours::red, juce::Colours::green, juce::Colours::blue,
								juce::Colours::cyan, juce::Colours::magenta, juce::Colours::yellow, juce::Colours::white };
			colorBlockWidth = getWidth() / colorTestColors.size();
		}

		void paint(juce::Graphics& g) override
		{
			g.fillAll(juce::Colours::black); // Background color

			// Draw color blocks at the top of the screen
			for (int i = 0; i < colorTestColors.size(); ++i)
			{
				g.setColour(colorTestColors[i]);
				g.fillRect(i * colorBlockWidth, 0, colorBlockWidth, colorBarHeight);
			}

			// Draw the touchscreen grid cells
			for (int row = 0; row < gridRows; ++row)
			{
				for (int col = 0; col < gridColumns; ++col)
				{
					int index = row * gridColumns + col;
					auto color = gridState[index] ? cellColors[index] : juce::Colours::grey;
					g.setColour(color);
					juce::Rectangle<int> cellArea(col * cellWidth, colorBarHeight + row * cellHeight, cellWidth, cellHeight);
					g.fillRect(cellArea);
					g.setColour(juce::Colours::black);
					g.drawRect(cellArea);
				}
			}

			if (isTestPassed())
			{
				this->setVisible(false);
				AppHome::GetAppHomeInstance()->show(screen::APP_MAIN_MODE, true);
			}
		}

		void mouseDown(const juce::MouseEvent& event) override
		{
			updateTouchState(event.getPosition());
			repaint();
		}

		void mouseDrag(const juce::MouseEvent& event) override
		{
			updateTouchState(event.getPosition());
			repaint();
		}

	private:
		const int gridRows = 10;           // Number of rows in the grid
		const int gridColumns = 8;         // Number of columns in the grid
		int cellWidth = 0, cellHeight = 0;

		int colorBarHeight = 0;            // Height of the color test bar at the top
		int colorBlockWidth = 0;           // Width of each color block in the test bar
		juce::Array<juce::Colour> colorTestColors; // Colors for the color test blocks

		juce::Array<bool> gridState;       // Tracks if each cell has been touched
		juce::Array<juce::Colour> cellColors; // Unique color for each cell in the grid

		bool isTestPassed() const
		{
			return !gridState.contains(false); // Test passed if no cell is untouched
		}

		void updateTouchState(const juce::Point<int>& point)
		{
			// Determine which cell was touched, ignoring the color test bar area
			if (point.y < colorBarHeight) return; // Ignore touch on the color bar

			int col = point.x / cellWidth;
			int row = (point.y - colorBarHeight) / cellHeight;
			int index = row * gridColumns + col;

			// Mark cell as touched if within bounds
			if (index >= 0 && index < gridState.size())
			{
				gridState.set(index, true);
			}
		}

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TouchscreenTestComponent)
	};
};