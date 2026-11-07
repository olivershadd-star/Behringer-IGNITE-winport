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

namespace ui
{
// Single PAD, in minimap view...
CommonMiniPad::CommonMiniPad() : CommonMiniPad( {}, {} )
{}
CommonMiniPad::CommonMiniPad( const juce::Colour& Normal, const juce::Colour& Highlighted )
    : normalColor( Normal ), highlightColor( Highlighted )
{}

void CommonMiniPad::highlight( bool Highlight )
{
    isHighlight = Highlight;
    repaint();
}

void CommonMiniPad::makeVisible( Component* Parent )
{
    Parent->addAndMakeVisible( dynamic_cast<Component&>(*this) );
}

void CommonMiniPad::paint( Graphics& g )
{
    juce::Path p;
    p.addRoundedRectangle( getLocalBounds(), 3 );
    g.setColour( (isHighlight ? highlightColor : normalColor) );
    g.fillPath( p );
}

// Mini Map of PAD GROUPS...
CommonPadMiniMap::CommonPadMiniMap()
    : CommonPadMiniMap( Theme::Instance().getColour( neutralGrey1 ), Theme::Instance().getColour(systemBlue) )
{};

CommonPadMiniMap::CommonPadMiniMap( const juce::Colour& Normal, const juce::Colour& Highlighted )
{
    for( int i = 0; i < NUM_BANKS; ++i )
    {
        char n[2] = {0};
        n[0] = (char)('A' + i);
        bankNames[i] = std::make_unique<CommonLabel>( &n[0] );
        bankNames[i]->makeVisible( this );
    }
    for( int i = 0; i < (NUM_BANKS * NUM_PADS_IN_BANK); ++i )
    {
        pads[i] = std::make_unique<CommonMiniPad>( Normal, Highlighted );
        pads[i]->makeVisible( this );
    }

    // Compose Layout...
    box.flexDirection = FlexBox::Direction::column;
    for( auto i = 0; i < NUM_BANKS; ++i )
    {
        b[i].flexDirection = juce::FlexBox::Direction::columnReverse;
        for( auto j = 0; j < NUM_ROWS_IN_BANK; j++ )
        {
            auto rowIndex = (i * NUM_ROWS_IN_BANK) + j;
            for( auto k = 0; k < NUM_COLS_IN_BANK; k++ )
            {
                auto padIndex = (i * NUM_PADS_IN_BANK) + (j * NUM_ROWS_IN_BANK) + k;
                r[rowIndex].items.add( juce::FlexItem( *pads[padIndex].get() ).withMargin( 2 ).withFlex( 1 ) );
            }
            b[i].items.add( FlexItem( r[rowIndex] ).withMargin( {0,2,2,2} ).withFlex( 1 ) );
        }
    }
    for( auto i = 0; i < NUM_BANKS / 2; ++i )
    {
        br[i].items.add( FlexItem( *bankNames[i * 2] ).withMargin( 2 ).withFlex( 0.5f ) );
        br[i].items.add( FlexItem( b[i * 2] ).withMargin( {2,6,2,2} ).withFlex( 3.5f ) );
        br[i].items.add( FlexItem( b[i * 2 + 1] ).withMargin( {2,2,2,6} ).withFlex( 3.5f ) );
        br[i].items.add( FlexItem( *bankNames[i * 2 + 1] ).withMargin( 2 ).withFlex( 0.5f ) );
    }

    // Overall Layout...
    box.items.add( FlexItem( br[0] ).withMargin( 5 ).withFlex( 1 ) );
    box.items.add( FlexItem( br[1] ).withMargin( 5 ).withFlex( 1 ) );
    box.items.add( FlexItem( br[2] ).withMargin( 5 ).withFlex( 1 ) );
    box.items.add( FlexItem( br[3] ).withMargin( 5 ).withFlex( 1 ) );
}

void CommonPadMiniMap::highlight( int Index, bool Highlight )
{
    if( isPositiveAndBelow( Index, (NUM_BANKS * NUM_PADS_IN_BANK) ) )
        pads[Index]->highlight( Highlight );
}

void CommonPadMiniMap::highlightAll()
{
    for( auto i = 0; i < (NUM_BANKS * NUM_PADS_IN_BANK); ++i )
        pads[i]->highlight( true );
}

void CommonPadMiniMap::clearAll()
{
    for( auto i = 0; i < (NUM_BANKS * NUM_PADS_IN_BANK); ++i )
        pads[i]->highlight( false );
}

void CommonPadMiniMap::makeVisible( Component* Parent )
{
    Parent->addAndMakeVisible( dynamic_cast<Component&>(*this) );
}

void CommonPadMiniMap::resized()
{
    box.performLayout( getLocalBounds().reduced( 5 ) );
}
};
