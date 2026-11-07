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
CommonPadButtonGroupComponent::CommonPadButtonGroupComponent()
{
    setLookAndFeel( CommonLooknFeel::getLnf() );
    for( auto i = 0; i < _NUM_PADS_IN_COMPONENT; ++i )
    {
        pads[i] = std::make_unique<CommonPadButton>( bank + String( i + 1 ) );
        pads[i]->makeVisibleAndAddListner( this );
    }
    onBankChanged();

    box.flexDirection = FlexBox::Direction::columnReverse;
    for( auto i = 0; i < _NUM_PADS_IN_ROW; ++i )
    {
        for( auto j = 0; j < _NUM_PADS_IN_COL; ++j )
        {
            r[i].items.add( FlexItem( *pads[i * _NUM_PADS_IN_ROW + j].get() ).withFlex( 1 ).withMargin( {2.0} ) );
        }
        box.items.add( FlexItem( r[i] ).withFlex( 1 ).withMargin( {2.0} ) );
    }
}

const Colour& CommonPadButtonGroupComponent::getBorderColor( int Index )
{
    if( juce::isPositiveAndBelow( Index, _NUM_PADS_IN_COMPONENT ) )
        return pads[Index]->getBorderColor();
    return pads[0]->getBorderColor();
}

void CommonPadButtonGroupComponent::setBank( const String& Bank )
{
    if( Bank.compareIgnoreCase( "A" ) || Bank.compareIgnoreCase( "B" ) || Bank.compareIgnoreCase( "C" )
        || Bank.compareIgnoreCase( "D" ) || Bank.compareIgnoreCase( "E" ) || Bank.compareIgnoreCase( "F" ) )
    {
        bank = Bank.toUpperCase();
        onBankChanged();
    }
}

void CommonPadButtonGroupComponent::setHeaderText( int Index, const String& Text )
{
    if( juce::isPositiveAndBelow( Index, _NUM_PADS_IN_COMPONENT ) )
        pads[Index]->setHeaderText( Text );
}

void CommonPadButtonGroupComponent::setHeader2Text( int Index, const String& Text )
{
    if( juce::isPositiveAndBelow( Index, _NUM_PADS_IN_COMPONENT ) )
        pads[Index]->setHeader2Text( Text );
}

void CommonPadButtonGroupComponent::setRow1Text( int Index, const String& Text )
{
    if( juce::isPositiveAndBelow( Index, _NUM_PADS_IN_COMPONENT ) )
        pads[Index]->setRow1Text( Text );
}

void CommonPadButtonGroupComponent::setBorderColor( int Index, const Colour& Col, float Thickness )
{
    if( juce::isPositiveAndBelow( Index, _NUM_PADS_IN_COMPONENT ) )
        pads[Index]->setBorderColor( Col, Thickness );
}

void CommonPadButtonGroupComponent::setBorderColor( const Colour& Col, float Thickness )
{
    for( auto i = 0; i < _NUM_PADS_IN_COMPONENT; ++i )
        pads[i]->setBorderColor( Col, Thickness );
}

void CommonPadButtonGroupComponent::makeVisible( Component* Parent )
{
    Parent->addAndMakeVisible( dynamic_cast<Component&>(*this) );
}

void CommonPadButtonGroupComponent::resized()
{
    box.performLayout( getLocalBounds().reduced( 3 ) );
}

void CommonPadButtonGroupComponent::buttonClicked( Button* ButtonClicked )
{
    if( OnButtonClicked )
        OnButtonClicked( dynamic_cast<CommonPadButton*>(ButtonClicked) );
}

void CommonPadButtonGroupComponent::onBankChanged()
{
    bankOffset = 16 * (*bank.getCharPointer() - 'A');
    for( auto i = 0; i < _NUM_PADS_IN_COMPONENT; ++i )
    {
        auto id = bankOffset + i;
        pads[i]->setHeaderText( bank + String( i + 1 ) );
        pads[i]->setID( id );
    }
}
};
