namespace  ui
{
Theme::Theme()
{
    // Tranaparent Colours
    colorPalette[transparentBlack] = color::transparent::black;
    colorPalette[transparentWhite] = color::transparent::white;
    // System Colours
    colorPalette[systemRed] = color::system::red;
    colorPalette[systemBlue] = color::system::blue;
    colorPalette[systemYellow] = color::system::yellow;
    colorPalette[systemGreen] = color::system::green;
    colorPalette[systemOrange] = color::system::orange;
    // Neutral Colours
    colorPalette[neutralBlack] = color::neutral::black;
    colorPalette[neutralGrey1] = color::neutral::grey1;
    colorPalette[neutralGrey2] = color::neutral::grey2;
    colorPalette[neutralGrey3] = color::neutral::grey3;
    colorPalette[neutralGrey4] = color::neutral::grey4;
    colorPalette[neutralGrey5] = color::neutral::grey5;
    colorPalette[neutralGrey6] = color::neutral::grey6;
    colorPalette[neutralGrey7] = color::neutral::grey7;
    colorPalette[neutralGrey8] = color::neutral::grey8;
    colorPalette[neutralGrey9] = color::neutral::grey9;
    colorPalette[neutralWhite] = color::neutral::white;
    // Custom Colours...
    colorPalette[customYellow1] = color::custom::yellow1;
    colorPalette[customYellow2] = color::custom::yellow2;
    colorPalette[customYellow3] = color::custom::yellow3;
    colorPalette[customBlue1] = color::custom::blue1;
    colorPalette[customBlue2] = color::custom::blue2;
    colorPalette[customBlue3] = color::custom::blue3;
    colorPalette[customBlue4] = color::custom::blue4;
    colorPalette[customBlue5] = color::custom::blue5;
    colorPalette[customBlue6] = color::custom::blue6;
    colorPalette[customBlue7] = color::custom::blue7;
    colorPalette[customBlue8] = color::custom::blue8;
    colorPalette[customBlue9] = color::custom::blue9;
    colorPalette[customBlue10] = color::custom::blue10;
    colorPalette[customBlue11] = color::custom::blue11;
    colorPalette[customBlue12] = color::custom::blue12;
    colorPalette[customBlue13] = color::custom::blue13;
    colorPalette[customGreen1] = color::custom::green1;
    colorPalette[customGreen2] = color::custom::green2;
    colorPalette[customGreen3] = color::custom::green3;
    colorPalette[customDarkGreen1] = color::custom::dgreen1;
    colorPalette[customDarkGreen2] = color::custom::dgreen2;
    colorPalette[customDarkGreen3] = color::custom::dgreen3;
    colorPalette[customPink1] = color::custom::pink1;
    colorPalette[customPink2] = color::custom::pink2;
    colorPalette[customPink3] = color::custom::pink3;
    colorPalette[customPeach1] = color::custom::skin1;
    colorPalette[customPeach2] = color::custom::skin2;
    colorPalette[customPeach3] = color::custom::skin3;
    colorPalette[customOrange1] = color::custom::orange1;
    colorPalette[customOrange2] = color::custom::orange2;
    colorPalette[customOrange3] = color::custom::orange3;
    colorPalette[customOrange4] = color::custom::orange4;
    colorPalette[customOrange5] = color::custom::orange5;
    colorPalette[customOrange6] = color::custom::orange6;
    colorPalette[customOrange7] = color::custom::orange7;
    colorPalette[customEerieBlack] = color::custom::eerieBlack;
    colorPalette[customRed1] = color::custom::red2;
    colorPalette[customRed2] = color::custom::red3;
    colorPalette[customRed3] = color::custom::red4;
    colorPalette[customRed4] = color::custom::red5;
    colorPalette[customRed5] = color::custom::red6;
    colorPalette[customdblue] = color::custom::dblue;
    colorPalette[customOrange] = color::custom::orange;
    colorPalette[customBlue14] = color::custom::Cblue13;
    colorPalette[customBlue15] = color::custom::Cblue14;
    colorPalette[customBlue16] = color::custom::Cblue15;
    colorPalette[customBlue17] = color::custom::Cblue16;
    colorPalette[customBlue18] = color::custom::Cblue18;
    colorPalette[customBlue19] = color::custom::Cblue19;
    colorPalette[customBlue20] = color::custom::Cblue20;
    colorPalette[customBlue21] = color::custom::Cblue21;
    colorPalette[customWhite] = color::custom::Cwhite;
    colorPalette[customGrey1] = color::custom::Cgrey1;
    colorPalette[customGrey2] = color::custom::Cgrey2;
    colorPalette[customGrey3] = color::custom::Cgrey3;
    colorPalette[customOrange8] = color::custom::Corange8;
    colorPalette[customOrange9] = color::custom::Corange9;
    colorPalette[customGrey4] = color::custom::Cgrey4;
    colorPalette[customBlack] = color::custom::Cblack;
    colorPalette[customGrey5] = color::custom::Cgrey5;
    colorPalette[customGrey6] = color::custom::Cgrey6;
    colorPalette[customGrey7] = color::custom::Cgrey7;
    colorPalette[customGrey8] = color::custom::Cgrey8;
    colorPalette[customGrey9] = color::custom::Cgrey9;
}

juce::Colour Theme::getColour( CommonColorID Id )
{
    auto it = colorPalette.find( Id );
    if( it != colorPalette.end() )
        return juce::Colour( it->second );
    return juce::Colours::transparentBlack;
}

Colour ui::Theme::titleColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(systemBlue);
    break; case 2: return getColour(neutralWhite);
    }
}

Colour ui::Theme::textColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(neutralGrey9);
    break; case 2: return getColour(neutralWhite);
    break; case 3: return getColour(systemYellow);
    break; case 4: return getColour(systemBlue);
    }
}

Colour ui::Theme::backgroundColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(neutralGrey4);
    break; case 0: return getColour(neutralGrey6);
    break; case 2: return getColour(neutralGrey3);
    break; case 3: return getColour(neutralGrey2);
    break; case 4: return getColour(neutralGrey1);
    break; case 5: return getColour(neutralBlack);
    break; case 6: return getColour(systemYellow);
    break; case 7: return getColour(neutralGrey7);
    break; case 8: return getColour(neutralGrey9);
    break; case 9: return getColour(transparentBlack);
    break; case 10: return getColour(systemBlue);
    break; case 11: return getColour(neutralWhite);
    }
}

juce::Colour Theme::foregroundColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(neutralGrey9);
    break; case 2: return getColour(systemYellow);
    break; case 3: return getColour(neutralWhite);
    break; case 4: return getColour(neutralGrey8);
    break; case 5: return getColour(neutralGrey7);
    }
}

juce::Colour Theme::selectionColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(systemBlue);
    break; case 2: return getColour(systemRed);
    break; case 3: return getColour(systemGreen);
    }
}

juce::Colour Theme::outlineColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(systemBlue);
    break; case 2: return getColour(neutralGrey9);
    break; case 3: return getColour(neutralGrey8);
    break; case 4: return getColour(neutralGrey2);
    break; case 5: return getColour(neutralGrey1);
    break; case 6: return getColour(systemYellow);
    break; case 7: return getColour(neutralWhite);
    break; case 8: return getColour(systemGreen);
    break; case 9: return getColour(neutralBlack);
    }
}

juce::Colour Theme::highlightColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(systemBlue);
    break; case 0: return getColour(transparentBlack);
    break; case 2: return getColour(neutralWhite);
    break; case 3: return getColour(systemBlue);
    break; case 4: return getColour(systemRed);
    break; case 5: return getColour(systemGreen);
    break; case 6: return getColour(systemYellow);
    }
}

juce::Colour Theme::waveformColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(neutralGrey9);
    break; case 2: return getColour(systemYellow);
    break; case 3: return getColour(systemBlue);
    }
}

juce::Colour Theme::multiSelectTabActiveColour()
{
    return getColour(systemBlue);
}

juce::Colour Theme::multiSelectTabInActiveColour()
{
    return getColour(neutralGrey6);
}

juce::Colour Theme::meterColour(int ID)
{
    switch (ID)
    {
    default: case 1: return getColour(systemGreen);
    break; case 2: return getColour(systemYellow);
    break; case 3: return getColour(systemRed);
    break; case 5: return getColour(customOrange3);
    }
}

juce::Colour Theme::getNoteColourForVelocity( int velocity )
{
    return getColour(systemBlue).withAlpha( (uint8)(20 + 1.8 * velocity) );
}

juce::Colour Theme::getNoteColourForParam(int param, int value)
{
    switch (param) 
    {
    default: case 3: return juce::Colour(0xFF00923F).withAlpha((uint8)(20 + 1.8 * (value * 1.3)));//steps
    break; case 5:return juce::Colour(0xFF00CEFF).withAlpha((uint8)(20 + 1.8 * (value * 4)));//delay
    break; case 4:return juce::Colour(0xFFEDCE54).withAlpha((uint8)(20 + 1.8 * (value * 4)));//tick
    break; case 2:return juce::Colour(0xFFC2392D).withAlpha((uint8)(20 + 1.8 * value));//velo
    break; case 1:return juce::Colour(0x00ffffff).withAlpha((uint8)(20 + 1.8 * value));//velo
    }
}

juce::LookAndFeel_V4::ColourScheme Theme::getColourScheme()
{
    return {
        color::neutral::grey4, color::neutral::grey1, color::neutral::grey9,     // WindowBackgroud, WidgetBackground, MenuBackground
        (0x24000000 | color::system::yellow), (0xc8000000 | color::transparent::white), color::neutral::grey9,     // Outline, DefaultText, DefaultFill
        color::neutral::white, color::neutral::grey7, color::neutral::black      // HighlightedText, HighlightedFill, MenuText
    };
}

juce::Colour Theme::gettrackMixerParam(int param, int value)
{
    switch (param)
    {
    default: case 3: return juce::Colour(0xFFFFB608).withAlpha((uint8)(20 + 1.8 * (value * 1.3)));//steps
    break; case 2:return juce::Colour(0xFFFF6666).withAlpha((uint8)(20 + 1.8 * value));//velo
    }
}

juce::Colour Theme::getKeyBoardColour(int param, int value)
{
    switch (param)
    {
    case 1: return juce::Colour(0xFF101226);
        break;
    case 2:return juce::Colour(0xFF4D507A);
        break;
    }
    return juce::Colour(0xFF101226);
}



} // namespace :: ui
