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
class CommonSlider : public juce::Slider
{
public:
    CommonSlider() : CommonSlider( juce::Slider::LinearBar, juce::Slider::TextBoxAbove ) {}

    CommonSlider( SliderStyle style, TextEntryBoxPosition textBoxPos ) : Slider( style, textBoxPos )
    {
     //   setLookAndFeel( CommonLooknFeel::getLnf() );
        //this->setTextBoxStyle()
    }

    void makeVisible( Component* Parent )
    {
        Parent->addAndMakeVisible( dynamic_cast<Component&>(*this) );
    }

    void makeVisibleAndAddListner( Component* Parent )
    {
        makeVisible( Parent );
        addListener( dynamic_cast<Listener*>(Parent) );
    }

    void mouseMove(const MouseEvent& event) override
    {
        if (focusState != true)
        {
            focusState = true;
            repaint();
        }
    }

    void mouseExit(const MouseEvent& event) override
    {
        if (focusState != false)
        {
            focusState = false;
            repaint();
        }
    }

    bool focusState = { false };
};
}
