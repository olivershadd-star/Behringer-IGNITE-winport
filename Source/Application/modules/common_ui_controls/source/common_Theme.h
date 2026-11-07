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

#ifndef THEME_H
#define THEME_H

namespace ui
{
using namespace juce;
enum CommonColorID
{
    // Transparent Black.
    transparentBlack = 0x0F00000,
    transparentWhite,

    // System Colours
    systemRed = 0x1000001,
    systemBlue,
    systemYellow,
    systemGreen,
    systemOrange,

    // Neutral Colours
    neutralBlack = 0x2000001,
    neutralGrey1,
    neutralGrey2,
    neutralGrey3,
    neutralGrey4,
    neutralGrey5,
    neutralGrey6,
    neutralGrey7,
    neutralGrey8,
    neutralGrey9,
    neutralWhite,

    // Custom Colours...
    customYellow1 = 0x3000001,
    customYellow2,
    customYellow3,
    customBlue1,
    customBlue2,
    customBlue3,
    customBlue4,
    customBlue5,
    customBlue6,
    customBlue7,
    customBlue8,
    customBlue9,
    customBlue10,
    customBlue11,
    customBlue12,
    customBlue13,
    customGreen1,
    customGreen2,
    customGreen3,
    customDarkGreen1,
    customDarkGreen2,
    customDarkGreen3,
    customPink1,
    customPink2,
    customPink3,
    customPeach1,
    customPeach2,
    customPeach3,
    customOrange1,
    customOrange2,
    customOrange3,
    customEerieBlack,
    customRed,
    customRed1,
    customRed2,
    customRed3,
    customRed4,
    customRed5,
    customdblue,
    customOrange,
    customOrange4,
    customOrange5,
    customOrange6,
    customOrange7,
    customBlue14,
    customBlue15,
    customBlue16,
    customBlue17,
    customBlue18,
    customBlue19,
    customBlue20,
    customBlue21,
    customWhite,
    customOrange8,
    customOrange9,
    customGrey1,
    customGrey2,
    customGrey3,
    customGrey4,
    customBlack,
    customGrey5,
    customGrey6,
    customGrey7,
    customGrey8,
    customGrey9
};

namespace color
{
namespace transparent
{
constexpr uint32 black{0x00000000};
constexpr uint32 white{0x00ffffff};
}
namespace system
{
constexpr uint32 red{0xffFE001A};
constexpr uint32 blue{0xff00AAEE};
constexpr uint32 yellow{0xffFF9300};
constexpr uint32 orange{0xffFFA500};
constexpr uint32 green{0xff1DFF00};
}
namespace neutral
{
constexpr uint32 black{0xff000000};
constexpr uint32 grey1{0xff151515};
constexpr uint32 grey2{0xff1E1E1E};
constexpr uint32 grey3{0xff2A2A2A};
constexpr uint32 grey4{0xff2D2D2D};
constexpr uint32 grey5{0xff343434};
constexpr uint32 grey6{0xff424242};
constexpr uint32 grey7{0xff656565};
constexpr uint32 grey8{0xff707070};
constexpr uint32 grey9{0xffB2B2B2};
constexpr uint32 white{0xffFFFFFF};
}
namespace custom
{
constexpr uint32 yellow1{0xffF5AE0D};
constexpr uint32 yellow2{0xff8C6914};
constexpr uint32 yellow3{0xff5F4A18};

constexpr uint32 blue1{0xff2D66E8};
constexpr uint32 blue2{0xff254386};
constexpr uint32 blue3{0xff22345B};
constexpr uint32 blue4{0xff238FCB};
constexpr uint32 blue5{0xff18496F};
constexpr uint32 blue6{0xff1F80B7};
constexpr uint32 blue7{0xff216096};
constexpr uint32 blue8{0xff191526};
constexpr uint32 blue9{0xff1B557E};
constexpr uint32 blue10{0xff15304E};
constexpr uint32 blue11{0xff1B557E}; 
constexpr uint32 blue12{0xff1F73A6};
constexpr uint32 blue13{0xFF28AAEE};
constexpr uint32 green1{0xff0FE389};
constexpr uint32 green2{0xff158454};
constexpr uint32 green3{0xff195A3E};

constexpr uint32 dgreen1{0xff12AC3B};
constexpr uint32 dgreen2{0xff0D7629};
constexpr uint32 dgreen3{0xff0A571E};

constexpr uint32 pink1{0xffEB00FF};
constexpr uint32 pink2{0xff870F92};
constexpr uint32 pink3{0xff5C1562};

constexpr uint32 skin1{0xffEAA58B};
constexpr uint32 skin2{0xff876456};
constexpr uint32 skin3{0xff5C473F};

constexpr uint32 orange1{0xffFFA700};
constexpr uint32 orange2{0xff92640F};
constexpr uint32 orange3{0xff7A5511};
constexpr uint32 orange4{ 0xFFFFDF91 };
constexpr uint32 orange5{ 0xFFFFB608 };
constexpr uint32 orange6{ 0xFFD18900 };
constexpr uint32 orange7{ 0xFFFFA208 };

constexpr uint32 eerieBlack{0xff101226};
constexpr uint32 red1{ 0xff101226 };
constexpr uint32 red2{ 0xff580D1B };
constexpr uint32 red3{ 0xff6F131D };
constexpr uint32 red4{ 0xFF90161F }; 
constexpr uint32 red5{ 0xFFE31625 }; 
constexpr uint32 red6{ 0xFFF76D79 };
constexpr uint32 dblue{0xFF040414};
constexpr uint32 orange{ 0xFFFFB608 }; 
constexpr uint32 Cblue13{ 0xFF0E1927 }; 
constexpr uint32 Cblue14{ 0xFF283B5F }; 
constexpr uint32 Cblue15{ 0xFF162033 }; 
constexpr uint32 Cblue16{ 0xFF28AAEE }; 
constexpr uint32 Cblue18{ 0xFF282E4B };
constexpr uint32 Cblue19{ 0xFF354662 };
constexpr uint32 Cblue20{ 0xFF2D3643 };
constexpr uint32 Cblue21{ 0xFF4C5E7B };
constexpr uint32 Cwhite{ 0xFF6B869A };
constexpr uint32 Corange8{ 0xFF6B869A };
constexpr uint32 Corange9{ 0xFF644200 };
constexpr uint32 Cgrey1{ 0xFF3B3F57 };
constexpr uint32 Cgrey2{ 0xFFB5BAC4 };
constexpr uint32 Cgrey3{ 0xFF354662 };
constexpr uint32 Cgrey4{ 0xFF354662 };
constexpr uint32 Cblack{ 0xFF0B121C };
constexpr uint32 Cgrey5{ 0xFF3A4165 };
constexpr uint32 Cgrey6{ 0xFF58618D };
constexpr uint32 Cgrey7{ 0xFF0E112B };
constexpr uint32 Cgrey8{ 0xFF181D38 };
constexpr uint32 Cgrey9{ 0xFFA3E0FF };
}
}

class Theme
{
public:
    Theme();

    static Theme& Instance()
    {
        static Theme _instance;
        return _instance;
    }

     juce::Colour getColour( CommonColorID Id );
     juce::Colour getNoteColourForVelocity( int velocity );
     juce::Colour getNoteColourForParam(int param, int value);
     juce::Colour titleColour(int ID = 1);
     juce::Colour textColour(int ID = 1);
     juce::Colour backgroundColour(int ID = 1);
     juce::Colour foregroundColour(int ID = 1);
     juce::Colour selectionColour(int ID = 1);
     juce::Colour outlineColour(int ID = 1);
     juce::Colour highlightColour(int ID = 1);
     juce::Colour waveformColour(int ID = 1);
     juce::Colour meterColour(int ID = 1);
     juce::Colour multiSelectTabActiveColour();
     juce::Colour multiSelectTabInActiveColour();
     juce::Colour gettrackMixerParam(int param, int value);
     juce::Colour getKeyBoardColour(int param, int value);
    
    static juce::File getAssetsDirectory()
    {
        auto currentFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile);
        return currentFile.getParentDirectory().getChildFile("assets");
    };
    static juce::LookAndFeel_V4::ColourScheme getColourScheme();

private:
    std::map<CommonColorID, uint32> colorPalette;
};
};
#endif // THEME_H
