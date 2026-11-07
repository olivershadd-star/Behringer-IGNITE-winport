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
CommonModeHeader::CommonModeHeader( const String& Name, const String& Image )
{
    setLookAndFeel( CommonLooknFeel::getLnf() );
    name.setName( Name );
    icon.setImage( Image );
    icon.setToggleable( false );
    separator.setToggleable( false );
    name.setColour( juce::Label::backgroundColourId, Theme::Instance().getColour( transparentBlack ) );
    name.setColour( juce::Label::textColourId, Theme::Instance().getColour(systemBlue) );

    back.makeVisibleAndAddListner( this );
    fullscreen.makeVisibleAndAddListner( this );
    icon.makeVisible( this );
    name.makeVisible( this );
    separator.makeVisible( this );

    box.items.add( FlexItem( back ).withMargin( 5 ).withFlex( 1 ) );
    box.items.add( FlexItem( icon ).withMargin( 5 ).withFlex( 1 ) );
    box.items.add( FlexItem( name ).withMargin( 5 ).withFlex( 12 ) );
    box.items.add( FlexItem( separator ).withMargin( 0 ).withFlex( 0.1f ) );
    box.items.add( FlexItem( fullscreen ).withMargin( 5 ).withFlex( 1 ) );
}

void CommonModeHeader::paint( Graphics& g )
{
    Path p;
    p.addRoundedRectangle( getLocalBounds().reduced( 10 ), 3 );
    g.setColour( Theme::Instance().getColour( neutralGrey6 ) );
    g.fillPath( p );
}

void CommonModeHeader::resized()
{
    box.performLayout( getLocalBounds().reduced( 10 ) );
};

void CommonModeHeader::buttonClicked( Button* Button )
{
    if( Button == &back )
        if( onBackButtonPressed )
            onBackButtonPressed( Button->getToggleState() );
    if( Button == &fullscreen )
        if( onFullscreenButtonPressed )
            onFullscreenButtonPressed( Button->getToggleState() );
}
};
