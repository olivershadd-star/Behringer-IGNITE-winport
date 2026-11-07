/*
* Copyright (C) MusicTribe Innovation India Pvt. Ltd
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
	struct TouchPoint
	{
		float startX, startY, endX, endY;
		TouchPoint() : startX(-1), startY(-1), endX(-1), endY(-1) {}
	};

	class GridSelectTool : public IGridTool
	{
	public:
		GridSelectTool(NoteManagement& gridComponent, GridData& gData);
	private:
		NoteManagement& gridComp;
		GridData& gridData;
		float startX, endX, startY, endY = 0;
		static constexpr int maxTouches = 5;
		std::array<TouchPoint, maxTouches> touchPoints;
		float initialMagnitude = 0.0f;
		float deltaX = 0.0f;
		float deltaY = 0.0f;
		static constexpr float pinchThreshold = 100.0f;

		virtual void mouseDown(const MouseEvent&) override;
		virtual void paint(Graphics& g) override;
		virtual void mouseDrag(const MouseEvent&) override;
		virtual void mouseUp(const MouseEvent&) override;
		void clearSelectRegion();
		bool isSelectRegionValid();
		int countActiveTouches();
		bool detectSwipeGesture();
		bool detectPinchGesture();
		void resetTouchPoints();
	};
}
