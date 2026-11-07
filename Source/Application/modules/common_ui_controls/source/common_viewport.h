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
class CommonViewport : public Viewport
{
public:
    CommonViewport();

    class Listener
    {
    public:
        virtual ~Listener() = default;

        /** Called when a clicked on the this track. */
        virtual void updateOnViewPositionChange(CommonViewport* pViewport) = 0;
    };

    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    
    void visibleAreaChanged(const Rectangle<int>& newVisibleArea) override;

private:
    ListenerList<Listener> listeners;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonViewport)
};
}
