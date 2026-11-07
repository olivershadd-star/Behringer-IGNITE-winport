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
#define NUM_COLS_IN_BANK (4)
#define NUM_ROWS_IN_BANK (4)
#define NUM_PADS_IN_BANK (NUM_COLS_IN_BANK*NUM_ROWS_IN_BANK)
#define NUM_BANKS (8)

class CommonMiniPad : public Component
{
public:
    CommonMiniPad();
    CommonMiniPad( const juce::Colour& Normal, const juce::Colour& Highlighted );

    void highlight( bool Highlight );
    void makeVisible( Component* Parent );

private:
    bool isHighlight{false};
    juce::Colour normalColor, highlightColor;

    virtual void paint( Graphics& g ) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CommonMiniPad )
};

class CommonPadMiniMap : public Component
{
public:
    CommonPadMiniMap();
    CommonPadMiniMap( const juce::Colour& Normal, const juce::Colour& Highlighted );

    void highlight( int Index, bool Highlight );
    void highlightAll();
    void clearAll();

    void makeVisible( Component* Parent );

private:
    std::unique_ptr<CommonLabel> bankNames[NUM_BANKS];
    std::unique_ptr<CommonMiniPad> pads[NUM_BANKS * NUM_PADS_IN_BANK];
    juce::FlexBox box, b[NUM_BANKS], r[(NUM_ROWS_IN_BANK * NUM_BANKS)], br[4];

    //virtual void paint( Graphics& g ) override
    //{
    //    g.fillAll( (isHighlight ? highlight : normal) );
    //}

    virtual void resized();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CommonPadMiniMap )
};
}
