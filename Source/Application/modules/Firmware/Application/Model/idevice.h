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

#include <vector>
#include <algorithm>

namespace mt{
    class IDevice{
        IDevice() = default;

        virtual juce::String open() = 0;
        virtual void close() = 0;

        virtual bool isInput() = 0;
        virtual bool isMidi() = 0;
        virtual void setEnabled( bool b ) = 0;

        bool isEnabled() const{ return enabled; };

        virtual juce::String getName() const{ return name; };
        juce::String getDeviceID() const;

    protected:
        std::atomic<bool> enabled{ false };
        juce::String type, name;
        int sampleRate{ 0 }, numInChannels{ 0 }, numOutChannels{ 0 }, bitDepth{ 0 }, blockSize{ 0 }, numActiveInChannels{ 0 }, numActiveOutChannels{ 0 };
    };
}
