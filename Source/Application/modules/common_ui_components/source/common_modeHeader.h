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
class CommonModeHeader : public Component, public Button::Listener
{
public:
    std::function<void( bool )> onBackButtonPressed;
    std::function<void( bool )> onFullscreenButtonPressed;

    CommonModeHeader( const String& Name, const String& Image );
    void makeVisible( Component* Parent ) { Parent->addAndMakeVisible( dynamic_cast<Component&>(*this) ); }

private:
    FlexBox  box;
    CommonImageButton back{"Back", "Mode Back Button.png"};
    CommonImageButton fullscreen{"FullScreen", "Mode Hide Bar.png"};
    CommonImageButton separator{"Separator", "Separator.png"};
    CommonImageButton icon{"MenuIcon"};
    CommonLabel name{"Track Mute"};

    virtual void buttonClicked( Button* ) override;
    virtual void paint( Graphics& g ) override;
    virtual void resized() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CommonModeHeader )
};
}
