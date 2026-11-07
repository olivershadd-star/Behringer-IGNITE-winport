set(LIBRARY midi)
project(${LIBRARY})

add_library(${LIBRARY} STATIC
    midi_Namespace.h
    midi_Defs.h
    midi_Message.h
    midi_Platform.h
    midi_Settings.h
    MIDI.cpp
    MIDI.hpp
    MIDI.h
    MidiTransport.cpp
    MidiTransport.h
)