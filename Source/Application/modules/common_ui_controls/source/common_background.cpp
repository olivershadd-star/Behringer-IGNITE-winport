/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "common_background.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CommonBackground::CommonBackground()
{
    setPaintingIsUnclipped(true);
    setInterceptsMouseClicks(false, false);
}

CommonBackground::~CommonBackground()
{}

//==============================================================================
void CommonBackground::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xd7000000));
}

void CommonBackground::resized()
{}

//[EndFile] You can add extra defines here...
//[/EndFile]
