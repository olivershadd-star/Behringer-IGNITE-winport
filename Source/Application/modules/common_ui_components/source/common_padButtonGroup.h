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
#define _NUM_PADS_IN_ROW (4)
#define _NUM_PADS_IN_COL (4)
#define _NUM_PADS_IN_COMPONENT (_NUM_PADS_IN_COL*_NUM_PADS_IN_ROW)

class CommonPadButtonGroupComponent : public Component, public Button::Listener
{
public:
    std::function<void( CommonPadButton* )> OnButtonClicked;

    CommonPadButtonGroupComponent();

    const String& getBank() { return bank; }
    int getBankOffset() { return bankOffset; }
    const Colour& getBorderColor( int Index );

    void setBank( const String& Bank );

    void setHeaderText( int Index, const String& Text );

    void setHeader2Text( int Index, const String& Text );

    void setRow1Text( int Index, const String& Text );

    void setBorderColor( int Index, const Colour& Col, float Thickness );

    void setBorderColor( const Colour& Col, float Thickness );

    void makeVisible( Component* Parent );

private:
    String bank{"A"};
    int bankOffset{0};
    std::unique_ptr<CommonPadButton> pads[_NUM_PADS_IN_COMPONENT];

    FlexBox box, r[_NUM_PADS_IN_ROW];

    void resized();
    virtual void buttonClicked( Button* ButtonClicked ) override;
    void onBankChanged();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CommonPadButtonGroupComponent )
};
}
