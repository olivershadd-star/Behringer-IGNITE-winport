// SPDX-License-Identifier: AGPL-3.0-or-later
//
// The embedded General MIDI SoundFont (AWE32_1MB, copyright E-mu Systems) that
// used to live here cannot be redistributed and was removed from this release.
// To use SFSynth, regenerate this header from a .sf2 file you have the rights to
// (e.g. `xxd -i your.sf2`) keeping the `soundfont` / `soundfontsize` names.
#pragma once
#include <cstdint>
uint32_t            soundfontsize = 0;
const unsigned char soundfont[1]  = { 0 };
