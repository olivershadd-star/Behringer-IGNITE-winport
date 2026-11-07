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
class CommonLabel : public juce::Label
{
public:
    std::function<void(bool)> onFocusChanged;
    explicit CommonLabel( const String& Name );
    explicit CommonLabel( const String& Name, const String& Text, bool ShowTitle = false, bool ShowBorder = false );

    void makeVisible( Component* Parent );
    void makeVisibleAndAddListner( Component* Parent );

    void setDisplayBorder( bool Show );
    void setDisplayTitle(bool Show);
    void setDisplayDropDown( bool Show );
    void setDisplayTitleAndBorder( bool Show );
    void setBackgroundColour(Colour newColour);
    void setTextColour(Colour);
    void setTextFont(Font);
    void setTitle(String newName);
    void setTitleColour(Colour newColour);
    virtual void paint(Graphics& g) override;
    void setcustombounds(bool state, Rectangle<int> a, Rectangle<int> b);
    bool getFocusState() { return focusState; };
private:
    bool focusState = 0;
    bool showTitle{ false };
    bool showBorder{false};
    bool showDrop{false};
    Colour textColourId;
    Colour titleColourId;
    Colour backgroundColourId;
    Font fontSize=NULL;
    bool custombounds = false;
    Rectangle<int> valueBonds={0,0,0,0};
    Rectangle<int> TitleBonds = { 0,0,0,0 };
    virtual void resized() override;
    virtual void editorShown( TextEditor* Editor ) override;
    //void mouseUp( const MouseEvent& ) override;
    void mouseMove(const MouseEvent& event) override;
    void mouseExit(const MouseEvent& event) override;
    void setFocus(bool s);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CommonLabel );
};

class CommonNameLabel : public CommonLabel
{
public:
    explicit CommonNameLabel( const String& Name );
    explicit CommonNameLabel( const String& Name, const String& Text );

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CommonNameLabel );
};

class CommonSerialNumber : public CommonLabel
{
public:
    explicit CommonSerialNumber();
    explicit CommonSerialNumber( const String& Name );
    explicit CommonSerialNumber( const String& Name, const String& Text );

private:
    void paint( Graphics& g ) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CommonSerialNumber );
};
}
