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
	class NoteManagement
	{
	public:
		void push_back()//const MTNoteData& note, bool emit = true )
		{
			notesChanged.emit();
		}

		void erase()//const MTSelected& selection, const std::vector<MTNoteData>& notes )
		{
			notesChanged.emit();
		}

		void clear()
		{
			notesCleared.emit();
			notesChanged.emit();
		}

		void editNoteVelocity()// const MTSelected& selection, const std::vector<MTNoteData>& notes, int velocity )
		{
			notesChanged.emit();
		}

	SIGNALS:
		sig::Signal<> notesChanged;
		sig::Signal<> notesCleared;
	};

	struct BarData
	{
		int totalBeats = 0;
		float barStartPos = 0;
		float widthOfBar = 0;
		int timeSigNum = 0;
		int timeSigDen = 0;
	};

	class GridData
	{
	public:
		GridData();

		void insertTimeSig(int bar, int num, int den);
		void deleteTimeSig(int bar);
		void insertBars(int newBarLength, int timSigNum, int timeSigDen);

		int findRow(float yPos) const;
		int findColumn(float xPos) const;
		float findX(int col) const;
		float findY(int row) const;

		void setZoomFactor(float horozontalFactor, float verticalFactor);
		void setQl(unsigned int ql);

		inline int getRequiredGridWidth();
		Rectangle<float> getCellRect(int row, int column) const;
		void getBarData(int bar, BarData& barData) const;
		int getZoomPercentage() { return (int)verticalZoom; }
		inline float getcellWidth() { return cellWidth; }
		void getTimeSignatureForBar(int atBar, int& num, int& den, bool& hasOnlyOneBar);
		unsigned int getQl() { return quantizationLevel; }
		inline float getYPositionFromNote(int note) const
		{
			return ((totalPianoKeys - note) * noteHeight /*- 9*/);
		}

		void getStartValues(int& startRow, int& endRow, int& startColumn, int& endColumn) const
		{
			float cellHeight = noteHeight;
			auto visibileViewPortX = visibleViewPort.getX();
			auto visibileViewPortY = visibleViewPort.getY();

			startRow = static_cast<int>(std::floor(visibileViewPortX / cellHeight));
			startColumn = static_cast<int>(std::floor(visibileViewPortX / cellWidth));
			endRow = static_cast<int>(std::ceil((visibileViewPortY + visibleViewPort.getHeight()) / cellHeight));
			endColumn = static_cast<int>(std::ceil((visibileViewPortY + visibleViewPort.getWidth()) / cellWidth));
		}

	private:
		void calculateBarWidthHeight();
		void recalculate();

	SIGNALS:
		sig::Signal<> gridChanged;

	public:
		// grid data
		Component* gridComponent = nullptr;
		int bars{ 1 };
		std::vector<int> barsRange{ 1 };
		std::vector<std::pair<int, int> > barTimeSig{ {4, 4} };

		// calculated handy values
		int   columns;
		float recommendedWidth;
		float greyWidth; //additional width needed when notes do not fit in the beats
		float tickWidth;
		float noteMarkingWidth = 0;

		// barWidth and beatWidth are 4/4 time sig refrence width
		float barWidth = 700.0f;
		float beatWidth;
		float cellWidth;
		int ticksPerQl = 1;

		bool tcOn = true;
		juce::Rectangle<int> visibleViewPort{ 0, 0, 496, 237 };

		float noteHeight = ignite_Constants::noteLineWidth;

	private:
		unsigned int quantizationLevel{ 16 };
		float horizontalZoom = 30;
		float verticalZoom = 30;
	};
}

