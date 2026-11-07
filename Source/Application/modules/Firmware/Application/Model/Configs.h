#pragma once
#include <stdint.h>
namespace Ignite {
enum class Config : uint8_t {
    bootloaderByte = 0,
    versionByte1,
    versionByte2,
    versionByte3,
    versionByte4,
    versionByte5,
    versionByte6,
    /*
    Reserved Bytes for Future Use
    */
    BeginReservedBytesStart,
    BeginReservedBytesEnd = 10,
    notused,
    /*
     * The Hold button can be configured to send a MIDI CC message,
     * toggle Hold/Chord modes on/off, or do both.
     * (see HOLD_SWITCH_FUNCTION_X constants)
     */
    holdFunction,
    /*
     * You can determine whether you want the Hold button to behave in one
     * of two ways:
     *  - As a momentary switch, which maintains its maximum value only
     *    while you are holding it down, or
     *  - As a latching switch, which stays on (or off) until you press
     *    it a second time.
     *  (see HOLD_SWITCH_MODE_X constants)
     */
    holdSwitchMode,
    /*
     * You can determine whether you want your sustain pedal to behave in one
     * of two ways:
     *  - As a momentary footswitch, which maintains its maximum value
     *    only while your foot is on the pedal, or
     *  - As a latching footswitch, which stays on (or off) until you press
     *    it a second time
     *  (see SUSTAIN_PEDAL_MODE_X constants)
     */
    sustainPedalMode,
    /*
     * Your pedal can send a MIDI CC message, toggle Hold/Chord modes on/off,
     * or it can do both. Your choice.
     * (see SUSTAIN_PEDAL_FUNCTION_X constants)
     */
    sustainPedalFunction,
    /*
     * Ordinarily a sustain pedal sends a value of 0 when it is off.
     * But if you set the pedal to a different MIDI CC number you could
     * use as another modulation source.
     * This would set the minimum value that would be transmitted when
     * the pedal was off, and it could be something other than zero
     */
    sustainMsgLow,
    /*
     * Ordinarily a sustain pedal sends a value of 127 when it is on.
     * But if you set the pedal to a different MIDI CC number you could
     * use as another modulation source.
     * This would set the maximum value that would be transmitted when
     * the pedal was on, and it could be something other than 127.
     */
    sustainMsgHigh,
    /*
     * Ordinarily a sustain pedal is assigned to MIDI CC #64.
     * But this parameter allows you to set it to a different MIDI CC number
     * so you can use it as another modulation source
     */
    sustainMsgCC,
    /*
     * Ordinarily a mod wheel is assigned to MIDI CC #1.
     * But this parameter allows you to set it to a different MIDI CC number
     * so you can use it as an alternate modulation source.
     */
    modStripCCNumber,
    // Record button CC Number
    recordBtnCCNumber,
    // Stop button CC Number
    stopBtnCCNumber,
    // Play buttonCC Number
    playButtonCCNumber,
    /*
     * This determines whether the Sustain Pedal will send its messages
     * down a fixed MIDI Channel at all times or change MIDI Channels
     * when the keyboard does
     */
    sustainMsgChannel,
    // Stop button midi channel
    stopBtnMidiChannel,
    // Record button midi channel
    recordBtnMidiChannel,
    // Play button midi channel
    playButtonMidiChannel,

    /*
     * This parameter allows you to perform MIDI-to-CV conversion when the
     * Sequencer and Arpeggiator are stopped. The selected value is the MIDI
     * channel that will be allowed to control an external device through
     * the CV/Gate/Mod connectors.
     */
    midiInputChannel,
    /*
     * This determines whether the Mod strip will send its messages down
     * a fixed MIDI Channel at all times or change MIDI Channels when
     * the keyboard does.
     */
    modStripMidiChannel,
    /*
     * This determines whether the Pitch strip will send its messages down
     * a fixed MIDI Channel at all times or change MIDI Channels when
     * the keyboard does.
     */
    pitchBendMidiChannel,

    /*
     * This sets the keyboard MIDI Channel. It�s the same parameter found
     * on the keyboard that is set by holding Shift and pressing a key
     */
    midiCh1,
    midiCh2,
    midiCh3,
    midiCh4,
    /*
     * Midi Channel to use in Sequencer Mode when KbdPlay mode is active
     */
    kbdPlayChannel,
    /*
     * This sets the Aftertouch calibration offset
     */
    aftertouchCalibration,
    /*
     * Three aftertouch curves are provided so you can choose the one
     * that seems the most responsive to you.
     * (see AFTERTOUCH_CURVE_X constants)
     */
    aftertouchCurve,
    /*
     * Three velocity curves are available so you can choose the one
     * that best matches your playing style.
     * (see VELOCITY_CURVE_X constants)
     */
    velocityCurve,
    /*
     * This sets the type of randomness exhibited by the arpeggiator when
     * Arp Mode knob is set to "Random"
     * TODO: Unused
     */
    arpRandomMode,
    /*
     * This parameter will turn the KeyStep MIDI Output into a MIDI Thru.
     * Incoming MIDI data will be routed directly to the Output instead
     * of being used to transpose sequences, etc
     */
    midiThruEnabled,
    /*
     * Determines the device is in Sequencer Mode or Arpeggiator mode
     */
    // deviceMode,
    /*
     * Sync mode
     */
    syncSource,
    transportMode,
    /*
     * SWING is endowed with the ability to transmit or receive clocking
     * signals from a huge range of vintage devices.
     * Here�s a brief look at each setting:
     *  - 1step (Gate): Interprets the rising edge of the voltage as a
     *    Note On command and the falling edge as a Note Off.
     *    Then it will advance to the next step.
     *  - 1step (Clock): It is likely the input clock has a fixed period,
     *    so Swing interpolates between the edges of the clock signal
     *    to derive a steady tempo.
     *  - 1 Pulse (Korg): As the name implies, this is a special sync clock
     *    used by Korg devices.
     *  - 24 PPQ: the DIN sync used by Roland and other companies in
     *    their devices.
     *  - 48 PPQ: the clock signal used by Oberheim drum machines, et al.
     */
    syncClockMode,
    /*
     * When SWING is slaved to an external device via the Sync input,
     * this parameter allows you to specify how the sequencer and arpeggiator
     * will start:
     *  - On Clock: the Seq/Arp will start as soon as a clock is received
     *    on the jack tip. This mainly applies when you are using a
     *    Tip-Sleeve (TS) connector.
     *  - On Gate Start: the Seq/Arp will start when a clock signal
     *    is received on the tip of the connector and the start signal
     *    is high on the ring. This setting is ideal for when using a
     *    Tip-Ring-Sleeve (TRS) connector.
     *  (see SYNC_CLOCK_START_X constants)
     */
    syncClockStartMode,
    /*
     * This parameter sets the maximum about the Pitch CV output will
     * vary when the Pitch strip is used.
     */
    pitchBendRange,

    /*
     * The various models of vintage gear respond differently to electricity.
     * Swing works well with the most common types.
     *  - 1Volt per octave: This is the standard used on most Eurorack
     *    modules and synthesizers.
     *  - Hertz per volt: This is the technology used by Korg and older
     *    Yamaha synthesizers.
     *  (see PITCH_CV_OUTPUT_X constants)
     */
    pitchCVType,

    /*
     * This parameter determines which Swing feature will send signals
     * to the Mod CV output.
     * (see MOD_CV_SOURCE_X constants)
     */
    modCVSource,
    /*
     * Each of the three sources has a 'zero' point that translates into
     * 0 Volts. This parameter lets you specify whether the range will
     * be 0-5V, 0-6V, etc., on up to 0-12V
     * (see MOD_CV_MAX_VOLTAGE_X constants)
     */
    modCVMaxVoltage,
    /*
     * Three types of Gate signal response:
     *  - S-trig: This stands for "Short-circuit trigger", though sometimes
     *    it�s called "negative trigger" It involves keeping the voltage high and then shorting the trigger circuit
     *    whenever the note should play.
     *    This format is used by Dr. Bob�s classics, Korg and Yamaha synths,
     *    among others.
     *  - V-trig: An abbreviation for "Voltage trigger", also known as
     *    "positive trigger". This method involves keeping normally
     *    low voltage on trigger and producing a fixed positive voltage
     *    to indicate a note is on. It's favored by Roland and Sequential
     *    Circuits synths and others as well.
     *  (see GATE_CV_OUTPUT_X constants)
     */
    gateCVOutput,
    /*
     * Provides the option to set a separate reference note for both
     * Volt per Octave and Hertz per Volt formats.
     * This parameter will change from a 0V reference to a 1V reference
     * depending on which Pitch CV Output option is selected.
     */
    zeroVMidiNote,
    /*
     * Provides the option to set a separate reference note for both
     * Volt per Octave and Hertz per Volt formats.
     * This parameter will change from a 0V reference to a 1V reference
     * depending on which Pitch CV Output option is selected.
     */
    onevMidiNote,
    /*
     * Since CV connectors are always monophonic, it�s important to be able
     * to determine which note from a polyphonic sequencer track or keyboard
     * will be interpreted as the one the mono synth on the other end
     * should play.
     * (see NOTE_PRIORITY_X constants)
     */
    notePriority,
    /*
     * Use this to tell Swing which MIDI port will receive the
     * transposition request.
     * (see TRANSPOSITION_INPUT_PORT_X constants)
     */
    transpositionInputPort,
    /*
     * Instructs Swing which MIDI channel will set the transposition amount
     */
    transposeInputChannel,
    /*
     * This allows you to choose whether a sequence will be transposed
     * momentarily or latched. With either setting the transposition
     * will happen immediately; the difference is what will happen once
     * the key is released.
     * When Latch is Off the sequences will transpose back to the center
     * pitch immediately after the key is released.
     * When Latch is On the sequences will stay transposed after the key
     * is released, and continue at that transposition until another key
     * is pressed.
     * This parameter also affects the way the Swing responds to incoming
     * MIDI notes on the Transposition Input channel.
     */
    transpositionLatch,
    /*
     * The Center pitch decides which incoming note means �don�t transpose�.
     * The default value is MIDI note #60, or middle C [C3].
     * So for example, an incoming C3 won't transpose the sequence,
     * but an incoming D3 will transpose the sequence +2, etc.
     */
    transposeCenterPitch,
    // TODO: Unused
    playPauseFunction,
    /*
     * This parameter decides how quickly the KeyStep sequences will change
     * after a new sequence has been selected, and whether the new sequence
     * will start from the top or the middle somewhere.
     *  - End: KeyStep will not change sequences until the end of the
     *    current sequence.
     *  - Instant Reset: The sequence changes immediately and starts at
     *    the top of the new sequence.
     *  - Instant Continue: The sequence changes immediately but transitions
     *    at the current position into the new sequence.
     *
     *  If the two sequences are not the same length, the current position
     *  of the new sequence is calculated as if the new sequence had been
     *  played from the beginning.
     */
    nextSeqMode,

    /* This parameter determines whether the sequencer will preserve
     * the velocity values of the original performance or set all recorded
     * notes to the same value.
     * (see VELOCITY_VALUE_X constants)
     */
    recordedVelocityValue,
    /*
     * This sets the velocity value for all recorded notes to the same
     * number if the Velocity parameter is set to Fixed, not �As Recorded�.
     */
    fixedVelocityValue,

    /*
     * If you�re performing live and you want to speed up the tempo
     * or slow it down without a sudden change in value, this parameter
     * will allow you to do that.
     *  - Jump: The tempo value will respond immediately when the Rate knob
     *    is turned.
     *  - Pickup: The tempo will not change until the Rate knob passes
     *    through the current value.
     */
    tempoKnobMode,
    /*
     * This lets you set your preference for how many times the Tap button
     * must be pressed before the tempo will change (2,3 or 4).
     */
    tapTempoCalculationCount,
    /*
     * This determines the start/stop behavior of the sequencer when working
     * with external clock sources
     */
    armToStart,
    /*
     * This determines how notes are "tied" together in the KeyStep sequencer
     */
    tieMode,
    octave,
    keyboardMode,
    ratchetMode,
    swing,
    gate,
    ledBrightness,
    knob1A_CC,
    knob2A_CC,
    knob3A_CC,
    knob4A_CC,
    knob1B_CC,
    knob2B_CC,
    knob3B_CC,
    knob4B_CC,
    knob1AChannel,
    knob2AChannel,
    knob3AChannel,
    knob4AChannel,
    knob1BChannel,
    knob2BChannel,
    knob3BChannel,
    knob4BChannel,
    knob1ARangeLow,
    knob2ARangeLow,
    knob3ARangeLow,
    knob4ARangeLow,
    knob1BRangeLow,
    knob2BRangeLow,
    knob3BRangeLow,
    knob4BRangeLow,
    knob1ARangeHigh,
    knob2ARangeHigh,
    knob3ARangeHigh,
    knob4ARangeHigh,
    knob1BRangeHigh,
    knob2BRangeHigh,
    knob3BRangeHigh,
    knob4BRangeHigh,
    InternalSoundOnOff,
    soundEngineVolume,
    soundFontPresetCh1,
    soundFontPresetCh2,
    soundFontPresetCh3,
    soundFontPresetCh4,
    soundFontPresetCh5,
    soundFontPresetCh6,
    soundFontPresetCh7,
    soundFontPresetCh8,
    soundFontPresetCh9,
    soundFontPresetCh10,
    soundFontPresetCh11,
    soundFontPresetCh12,
    soundFontPresetCh13,
    soundFontPresetCh14,
    soundFontPresetCh15,
    soundFontPresetCh16,
    solo,
    DrumPitch1,
    DrumPitch2,
    DrumPitch3,
    DrumPitch4,
    DrumPitch5,
    DrumPitch6,
    DrumPitch7,
    DrumPitch8,
    DrumPitch9,
    DrumPitch10,

    EndReservedBytesStart,
    EndReservedBytesEnd = 180,
    // Add any config before this
    ConfigEndSignature,
    ConfigsMax

};
};
