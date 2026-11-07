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

	class GridPencilTool : public IGridTool
	{
	public:
		GridPencilTool(NoteManagement& nMgmt, GridData& data);

	private:
		float startX, mouseX, mouseY, endX, startY, endY = 0;
		int currentNoteDrag = -1;
		int selectedNote = 0;
		int selectedStep = 0;
		NoteManagement& noteMgmt;
		GridData& gridData;

		virtual void paint(Graphics& g);
		virtual void mouseDown(const MouseEvent&) override;
		virtual void mouseDrag(const MouseEvent& event);
		virtual void mouseUp(const MouseEvent& event) override;
		virtual void mouseDoubleClick(const MouseEvent& event) override;
		void clearSelectRegion();
		bool isSelectRegionValid();
	};
}

