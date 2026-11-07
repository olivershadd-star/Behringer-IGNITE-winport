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
	class IGridTool : public juce::MouseListener
		, public juce::KeyListener
	{
	public:
		IGridTool() {};

		virtual void mouseMove(const MouseEvent&) override {}
		virtual void mouseEnter(const MouseEvent&) override {}
		virtual void mouseExit(const MouseEvent&) override {}
		virtual void mouseDown(const MouseEvent&) override {}
		virtual void mouseDrag(const MouseEvent&) override {}
		virtual void mouseUp(const MouseEvent&) override {}
		virtual void mouseDoubleClick(const MouseEvent&) override {}
		virtual void mouseWheelMove(const MouseEvent&,
			const MouseWheelDetails&) override
		{}
		virtual bool keyPressed(const KeyPress& /*key*/, Component* /*originatingComponent*/) { return false; }
		virtual bool keyStateChanged(bool /*isKeyDown*/, Component* /*originatingComponent*/) { return false; }
		virtual void mouseMagnify(const MouseEvent& /*event*/, float /*scaleFactor*/) override {}
		virtual void paint(Graphics& g) = 0;
		void setActive(bool newActiveState) { this->active = newActiveState; }
		bool isActive() { return active; }
		void setType(GridToolType newType) { type = newType; }
		GridToolType getType() { return type; }

	private:
		bool active = false;
		GridToolType type = GridToolType::GridSelectTool;
	};
}// namespace mt

