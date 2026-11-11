TinySoundFont file extracted directly from the user-provided original IGNITE archive.

Original path: `Source/Application/modules/Firmware/Application/Model/tsf.h`

Original SHA-256: `ba8311a3390204165de1c867edc623bec79282edf4c3162bde3493bf0d85357c`

The new standalone target does not link the previous Windows port, IGNITE hardware services, UART, Linux GPIO, MIDI routing, or the old interface. This first model adapts the original internal synthesizer. The original Song/Scene/Track/Pattern sequencer and JUCE effects are not ported into this target yet.

Local adaptation: convert the signed generator amount to unsigned before a left shift, preserving modulo arithmetic while removing undefined behaviour for negative SoundFont offsets.
