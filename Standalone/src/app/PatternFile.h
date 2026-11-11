// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <juce_core/juce_core.h>
#include "../core/AudioCore.h"
juce::String encodePattern(const ignite::Pattern&);
bool decodePattern(const juce::String&,const ignite::AudioCore&,ignite::Pattern&,juce::String& error);
