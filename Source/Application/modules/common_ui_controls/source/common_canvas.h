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
class CommonCanvas : public juce::Component
{
public:
    CommonCanvas()
    {
        setLookAndFeel( CommonLooknFeel::getLnf() );
    }

    void makeVisible( Component* Parent )
    {
        Parent->addAndMakeVisible( dynamic_cast<Component&>(*this) );
    }

    void paint( Graphics& g ) override
    {
        g.setColour( getBackgroundColour() );
        g.fillAll();
    }

    const juce::Colour getBackgroundColour() { return Theme::Instance().getColour( neutralBlack ); }
    const juce::Colour getForegroundColour() { return Theme::Instance().getColour( neutralWhite ); }
    const juce::Colour getSelectionColour() { return Theme::Instance().getColour( systemBlue ); }
};
}
