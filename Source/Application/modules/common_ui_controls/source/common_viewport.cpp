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
	//////////////////////
	/// Common ViewPort
	//////////////////////

	CommonViewport::CommonViewport()
	{
		setScrollOnDragMode(Viewport::ScrollOnDragMode::all);
		setScrollBarsShown(true, false);
	}

	void CommonViewport::addListener(Listener* listener)
	{
		listeners.add(listener);
	}

	void CommonViewport::removeListener(Listener* listener)
	{
		listeners.remove(listener);
	}
	void CommonViewport::visibleAreaChanged(const Rectangle<int>& /*newVisibleArea*/)
	{
		Component::BailOutChecker checker(this);

		if (checker.shouldBailOut())
			return;

		listeners.callChecked(checker, [this](Listener& l) { l.updateOnViewPositionChange(this); });
	}
}
