/*!
 *  @file       MIDI.hpp
 *  Project     Arduino MIDI Library
 *  @brief      MIDI Library for the Arduino - Inline implementations
 *  @author     Francois Best, lathoub
 *  @date       24/02/11
 *  @license    MIT - Copyright (c) 2015 Francois Best
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once
BEGIN_MIDI_NAMESPACE

#define RegionActiveSending

/// \brief Constructor for MidiInterface.
template <class Transport, class Settings, class Platform>
inline MidiInterface<Transport, Settings, Platform>::MidiInterface(Transport& inTransport)
    : mTransport(inTransport)
    , mInputChannel(0)
    , mRunningStatus_RX((StatusByte)MidiType::InvalidType)
    , mRunningStatus_TX((StatusByte)MidiType::InvalidType)
    , mPendingMessageExpectedLength(0)
    , mPendingMessageIndex(0)
    , mCurrentRpnNumber(0xffff)
    , mCurrentNrpnNumber(0xffff)
    , mThruActivated(true)
    , mThruFilterMode(Thru::Full)
    , mLastMessageSentTime(0)
    , mLastMessageReceivedTime(0)
    , mSenderActiveSensingPeriodicity(0)
    , mReceiverActiveSensingActivated(false)
    , mLastError(0)
{
    mSenderActiveSensingPeriodicity = Settings::SenderActiveSensingPeriodicity;
}

/*! \brief Destructor for MidiInterface.

 This is not really useful for the Arduino, as it is never called...
 */
template <class Transport, class Settings, class Platform>
inline MidiInterface<Transport, Settings, Platform>::~MidiInterface()
{
}

// -----------------------------------------------------------------------------

/*! \brief Call the begin method in the setup() function of the Arduino.

 All parameters are set to their default values:
 - Input channel set to 1 if no value is specified
 - Full thru mirroring
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::begin(Channel inChannel)
{
    // Initialise the Transport layer
    mTransport.begin();

    mInputChannel = inChannel;
    mRunningStatus_TX = (StatusByte)MidiType::InvalidType;
    mRunningStatus_RX = (StatusByte)MidiType::InvalidType;

    mPendingMessageIndex = 0;
    mPendingMessageExpectedLength = 0;

    mCurrentRpnNumber = 0xffff;
    mCurrentNrpnNumber = 0xffff;

    mLastMessageSentTime = Platform::now();

    mMessage.valid = false;
    mMessage.type = MidiType::InvalidType;
    mMessage.channel = 0;
    mMessage.data1 = 0;
    mMessage.data2 = 0;
    mMessage.length = 0;

    mThruFilterMode = Thru::Full;
    mThruActivated = false;
}

// -----------------------------------------------------------------------------
//                                 Output
// -----------------------------------------------------------------------------

/*! \addtogroup output
 @{
 */

/*! \brief Send a MIDI message.
\param inMessage    The message

 This method is used when you want to send a Message that has not been constructed
 by the library, but by an external source.
 This method does *not* check against any of the constraints.
 Typically this function is use by MIDI Bridges taking MIDI messages and passing
 them thru.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::send(const MidiMessage& inMessage)
{
    if (!inMessage.valid)
        return;

    if (mTransport.beginTransmission(inMessage.type)) {
        const StatusByte status = getStatus(inMessage.type, inMessage.channel);
        mTransport.write(status);

        if (inMessage.type != MidiType::SystemExclusive) {
            if (inMessage.length > 1)
                mTransport.write(inMessage.data1);
            if (inMessage.length > 2)
                mTransport.write(inMessage.data2);
        } else {
            // sysexArray does not contain the start and end tags
            mTransport.write(MidiType::SystemExclusiveStart);

            for (size_t i = 0; i < inMessage.getSysExSize(); i++)
                mTransport.write(inMessage.sysexArray[i]);

            mTransport.write(MidiType::SystemExclusiveEnd);
        }
    }
    mTransport.endTransmission();
    UpdateLastSentTime();
}

/*! \brief Generate and send a MIDI message from the values given.
 \param inType    The message type (see type defines for reference)
 \param inData1   The first data byte.
 \param inData2   The second data byte (if the message contains only 1 data byte,
 set this one to 0).
 \param inChannel The output channel on which the message will be sent
 (values from 1 to 16). Note: you cannot send to OMNI.

 This is an internal method, use it only if you need to send raw data
 from your code, at your own risks.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::send(MidiType inType,
    DataByte inData1,
    DataByte inData2,
    Channel inChannel)
{
    if (inType <= MidiType::PitchBend) // Channel messages
    {
        // Then test if channel is valid
        if (inChannel >= MIDI_CHANNEL_OFF || inChannel == MIDI_CHANNEL_OMNI || (uint8_t)inType < 0x80) {
            return; // Don't send anything
        }
        // Protection: remove MSBs on data
        inData1 &= 0x7f;
        inData2 &= 0x7f;
        if (mSendCallback)
            mSendCallback(inType, inData1, inData2, inChannel);
        const StatusByte status = getStatus(inType, inChannel);

        if (mTransport.beginTransmission(inType)) {
            if (Settings::UseRunningStatus) {
                if (mRunningStatus_TX != status) {
                    // New message, memorise and send header
                    mRunningStatus_TX = status;
                    mTransport.write(mRunningStatus_TX);
                }
            } else {
                // Don't care about running status, send the status byte.
                mTransport.write(status);
            }

            // Then send data
            mTransport.write(inData1);
            if (inType != MidiType::ProgramChange && inType != MidiType::AfterTouchChannel) {
                mTransport.write(inData2);
            }

            mTransport.endTransmission();
            UpdateLastSentTime();
        }
    } else if (inType >= MidiType::Clock && inType <= MidiType::SystemReset) {
        sendRealTime(inType); // System Real-time and 1 byte.
    }
}

// -----------------------------------------------------------------------------

/*! \brief Send a Note On message
 \param inNoteNumber  Pitch value in the MIDI format (0 to 127).
 \param inVelocity    Note attack velocity (0 to 127). A NoteOn with 0 velocity
 is considered as a NoteOff.
 \param inChannel     The channel on which the message will be sent (1 to 16).

 Take a look at the values, names and frequencies of notes here:
 http://www.phys.unsw.edu.au/jw/notes.html
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendNoteOn(DataByte inNoteNumber,
    DataByte inVelocity,
    Channel inChannel)
{
    send(MidiType::NoteOn, inNoteNumber, inVelocity, inChannel);
}

/*! \brief Send a Note Off message
 \param inNoteNumber  Pitch value in the MIDI format (0 to 127).
 \param inVelocity    Release velocity (0 to 127).
 \param inChannel     The channel on which the message will be sent (1 to 16).

 Note: you can send NoteOn with zero velocity to make a NoteOff, this is based
 on the Running Status principle, to avoid sending status messages and thus
 sending only NoteOn data. sendNoteOff will always send a real NoteOff message.
 Take a look at the values, names and frequencies of notes here:
 http://www.phys.unsw.edu.au/jw/notes.html
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendNoteOff(DataByte inNoteNumber,
    DataByte inVelocity,
    Channel inChannel)
{
    send(MidiType::NoteOff, inNoteNumber, inVelocity, inChannel);
}

/*! \brief Send a Program Change message
 \param inProgramNumber The Program to select (0 to 127).
 \param inChannel       The channel on which the message will be sent (1 to 16).
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendProgramChange(DataByte inProgramNumber,
    Channel inChannel)
{
    send(MidiType::ProgramChange, inProgramNumber, 0, inChannel);
}

/*! \brief Send a Control Change message
 \param inControlNumber The controller number (0 to 127).
 \param inControlValue  The value for the specified controller (0 to 127).
 \param inChannel       The channel on which the message will be sent (1 to 16).
 @see MidiControlChangeNumber
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendControlChange(DataByte inControlNumber,
    DataByte inControlValue,
    Channel inChannel)
{
    send(MidiType::ControlChange, inControlNumber, inControlValue, inChannel);
}

/*! \brief Send a Polyphonic AfterTouch message (applies to a specified note)
 \param inNoteNumber  The note to apply AfterTouch to (0 to 127).
 \param inPressure    The amount of AfterTouch to apply (0 to 127).
 \param inChannel     The channel on which the message will be sent (1 to 16).
 Note: this method is deprecated and will be removed in a future revision of the
 library, @see sendAfterTouch to send polyphonic and monophonic AfterTouch messages.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendPolyPressure(DataByte inNoteNumber,
    DataByte inPressure,
    Channel inChannel)
{
    send(MidiType::AfterTouchPoly, inNoteNumber, inPressure, inChannel);
}

/*! \brief Send a MonoPhonic AfterTouch message (applies to all notes)
 \param inPressure    The amount of AfterTouch to apply to all notes.
 \param inChannel     The channel on which the message will be sent (1 to 16).
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendAfterTouch(DataByte inPressure,
    Channel inChannel)
{
    send(MidiType::AfterTouchChannel, inPressure, 0, inChannel);
}

/*! \brief Send a Polyphonic AfterTouch message (applies to a specified note)
 \param inNoteNumber  The note to apply AfterTouch to (0 to 127).
 \param inPressure    The amount of AfterTouch to apply (0 to 127).
 \param inChannel     The channel on which the message will be sent (1 to 16).
 @see Replaces sendPolyPressure (which is now deprecated).
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendAfterTouch(DataByte inNoteNumber,
    DataByte inPressure,
    Channel inChannel)
{
    send(MidiType::AfterTouchPoly, inNoteNumber, inPressure, inChannel);
}

/*! \brief Send a Pitch Bend message
 \param inChannel     The channel on which the message will be sent (1 to 16).
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendPitchBend(uint8_t inPitchValue,
    Channel inChannel)
{
    send(MidiType::PitchBend, (inPitchValue & 0x7f), (inPitchValue >> 7) & 0x7f, inChannel);
}

/*! \brief Generate and send a System Exclusive frame.
 \param inLength  The size of the array to send
 \param inArray   The byte array containing the data to send
 \param inArrayContainsBoundaries When set to 'true', 0xf0 & 0xf7 bytes
 (start & stop SysEx) will NOT be sent
 (and therefore must be included in the array).
 default value for ArrayContainsBoundaries is set to 'false' for compatibility
 with previous versions of the library.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendSysEx(unsigned inLength,
    const byte* inArray,
    bool inArrayContainsBoundaries)
{
    mTransport.sendMessage(inArray, (uint8_t)inLength, MidiType::SystemExclusiveStart);
    UpdateLastSentTime();
    if (Settings::UseRunningStatus)
        mRunningStatus_TX = (StatusByte)MidiType::InvalidType;
}

/*! \brief Send a Tune Request message.

 When a MIDI unit receives this message,
 it should tune its oscillators (if equipped with any).
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendTuneRequest()
{
    sendCommon(MidiType::TuneRequest);
}

/*! \brief Send a MIDI Time Code Quarter Frame.

 \param inTypeNibble      MTC type
 \param inValuesNibble    MTC data
 See MIDI Specification for more information.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendTimeCodeQuarterFrame(DataByte inTypeNibble,
    DataByte inValuesNibble)
{
    const byte data = byte((((inTypeNibble & 0x07) << 4) | (inValuesNibble & 0x0f)));
    sendTimeCodeQuarterFrame(data);
}

/*! \brief Send a MIDI Time Code Quarter Frame.

 See MIDI Specification for more information.
 \param inData  if you want to encode directly the nibbles in your program,
                you can send the byte here.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendTimeCodeQuarterFrame(DataByte inData)
{
    sendCommon(MidiType::TimeCodeQuarterFrame, inData);
}

/*! \brief Send a Song Position Pointer message.
 \param inBeats    The number of beats since the start of the song.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendSongPosition(unsigned inBeats)
{
    sendCommon(MidiType::SongPosition, inBeats);
}

/*! \brief Send a Song Select message */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendSongSelect(DataByte inSongNumber)
{
    sendCommon(MidiType::SongSelect, inSongNumber);
}

/*! \brief Send a Common message. Common messages reset the running status.

 \param inType    The available Common types are:
 TimeCodeQuarterFrame, SongPosition, SongSelect and TuneRequest.
 @see MidiType
 \param inData1   The byte that goes with the common message.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendCommon(MidiType inType, unsigned inData1)
{
    switch (inType) {
    case MidiType::TimeCodeQuarterFrame:
    case MidiType::SongPosition:
    case MidiType::SongSelect:
    case MidiType::TuneRequest:
        break;
    default:
        // Invalid Common marker
        return;
    }

    if (mTransport.beginTransmission(inType)) {
        mTransport.write((byte)inType);
        switch (inType) {
        case MidiType::TimeCodeQuarterFrame:
            mTransport.write(inData1);
            break;
        case MidiType::SongPosition:
            mTransport.write(inData1 & 0x7f);
            mTransport.write((inData1 >> 7) & 0x7f);
            break;
        case MidiType::SongSelect:
            mTransport.write(inData1 & 0x7f);
            break;
        case MidiType::TuneRequest:
            break;
        default:
            break; // LCOV_EXCL_LINE - Coverage blind spot
        }
        mTransport.endTransmission();
        UpdateLastSentTime();
    }

    if (Settings::UseRunningStatus)
        mRunningStatus_TX = (StatusByte)MidiType::InvalidType;
}

/*! \brief Send a Real Time (one byte) message.

 \param inType    The available Real Time types are:
 Start, Stop, Continue, Clock, ActiveSensing and SystemReset.
 @see MidiType
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::sendRealTime(MidiType inType)
{
    // Do not invalidate Running Status for real-time messages
    // as they can be interleaved within any message.

    switch (inType) {
    case MidiType::Clock:
    case MidiType::Start:
    case MidiType::Stop:
    case MidiType::Continue:
    case MidiType::ActiveSensing:
    case MidiType::SystemReset:
        if (mTransport.beginTransmission(inType)) {
            mTransport.write((byte)inType);
            mTransport.endTransmission();
            UpdateLastSentTime();
        }
        break;
    default:
        // Invalid Real Time marker
        break;
    }
}

/*! \brief Start a Registered Parameter Number frame.
 \param inNumber The 14-bit number of the RPN you want to select.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::beginRpn(unsigned inNumber,
    Channel inChannel)
{
    if (mCurrentRpnNumber != inNumber) {
        const byte numMsb = 0x7f & (inNumber >> 7);
        const byte numLsb = 0x7f & inNumber;
        sendControlChange(RPNLSB, numLsb, inChannel);
        sendControlChange(RPNMSB, numMsb, inChannel);
        mCurrentRpnNumber = inNumber;
    }
}

/*! \brief Send a 14-bit value for the currently selected RPN number.
 \param inValue  The 14-bit value of the selected RPN.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendRpnValue(unsigned inValue,
    Channel inChannel)
{
    ;
    const byte valMsb = 0x7f & (inValue >> 7);
    const byte valLsb = 0x7f & inValue;
    sendControlChange(DataEntryMSB, valMsb, inChannel);
    sendControlChange(DataEntryLSB, valLsb, inChannel);
}

/*! \brief Send separate MSB/LSB values for the currently selected RPN number.
 \param inMsb The MSB part of the value to send. Meaning depends on RPN number.
 \param inLsb The LSB part of the value to send. Meaning depends on RPN number.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendRpnValue(byte inMsb,
    byte inLsb,
    Channel inChannel)
{
    sendControlChange(DataEntryMSB, inMsb, inChannel);
    sendControlChange(DataEntryLSB, inLsb, inChannel);
}

/* \brief Increment the value of the currently selected RPN number by the specified amount.
 \param inAmount The amount to add to the currently selected RPN value.
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendRpnIncrement(byte inAmount,
    Channel inChannel)
{
    sendControlChange(DataIncrement, inAmount, inChannel);
}

/* \brief Decrement the value of the currently selected RPN number by the specified amount.
 \param inAmount The amount to subtract to the currently selected RPN value.
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendRpnDecrement(byte inAmount,
    Channel inChannel)
{
    sendControlChange(DataDecrement, inAmount, inChannel);
}

/*! \brief Terminate an RPN frame.
This will send a Null Function to deselect the currently selected RPN.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::endRpn(Channel inChannel)
{
    sendControlChange(RPNLSB, 0x7f, inChannel);
    sendControlChange(RPNMSB, 0x7f, inChannel);
    mCurrentRpnNumber = 0xffff;
}

/*! \brief Start a Non-Registered Parameter Number frame.
 \param inNumber The 14-bit number of the NRPN you want to select.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::beginNrpn(unsigned inNumber,
    Channel inChannel)
{
    if (mCurrentNrpnNumber != inNumber) {
        const byte numMsb = 0x7f & (inNumber >> 7);
        const byte numLsb = 0x7f & inNumber;
        sendControlChange(NRPNLSB, numLsb, inChannel);
        sendControlChange(NRPNMSB, numMsb, inChannel);
        mCurrentNrpnNumber = inNumber;
    }
}

/*! \brief Send a 14-bit value for the currently selected NRPN number.
 \param inValue  The 14-bit value of the selected NRPN.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendNrpnValue(unsigned inValue,
    Channel inChannel)
{
    ;
    const byte valMsb = 0x7f & (inValue >> 7);
    const byte valLsb = 0x7f & inValue;
    sendControlChange(DataEntryMSB, valMsb, inChannel);
    sendControlChange(DataEntryLSB, valLsb, inChannel);
}

/*! \brief Send separate MSB/LSB values for the currently selected NRPN number.
 \param inMsb The MSB part of the value to send. Meaning depends on NRPN number.
 \param inLsb The LSB part of the value to send. Meaning depends on NRPN number.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendNrpnValue(byte inMsb,
    byte inLsb,
    Channel inChannel)
{
    sendControlChange(DataEntryMSB, inMsb, inChannel);
    sendControlChange(DataEntryLSB, inLsb, inChannel);
}

/* \brief Increment the value of the currently selected NRPN number by the specified amount.
 \param inAmount The amount to add to the currently selected NRPN value.
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendNrpnIncrement(byte inAmount,
    Channel inChannel)
{
    sendControlChange(DataIncrement, inAmount, inChannel);
}

/* \brief Decrement the value of the currently selected NRPN number by the specified amount.
 \param inAmount The amount to subtract to the currently selected NRPN value.
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::sendNrpnDecrement(byte inAmount,
    Channel inChannel)
{
    sendControlChange(DataDecrement, inAmount, inChannel);
}

/*! \brief Terminate an NRPN frame.
This will send a Null Function to deselect the currently selected NRPN.
 \param inChannel The channel on which the message will be sent (1 to 16).
*/
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::endNrpn(Channel inChannel)
{
    sendControlChange(NRPNLSB, 0x7f, inChannel);
    sendControlChange(NRPNMSB, 0x7f, inChannel);
    mCurrentNrpnNumber = 0xffff;
}

/*! @} */ // End of doc group MIDI Output

// -----------------------------------------------------------------------------

template <class Transport, class Settings, class Platform>
StatusByte MidiInterface<Transport, Settings, Platform>::getStatus(MidiType inType,
    Channel inChannel) const
{
    return StatusByte(((byte)inType | ((inChannel - 1) & 0x0f)));
}

// -----------------------------------------------------------------------------
//                                  Input
// -----------------------------------------------------------------------------

/*! \addtogroup input
 @{
*/

/*! \brief Read messages from the serial port using the main input channel.

 \return True if a valid message has been stored in the structure, false if not.
 A valid message is a message that matches the input channel. \n\n
 If the Thru is enabled and the message matches the filter,
 it is sent back on the MIDI output.
 @see see setInputChannel()
 */
template <class Transport, class Settings, class Platform>
inline bool MidiInterface<Transport, Settings, Platform>::read()
{
    return read(mInputChannel);
}

/*! \brief Read messages on a specified channel.
 */
template <class Transport, class Settings, class Platform>
inline bool MidiInterface<Transport, Settings, Platform>::read(Channel inChannel)
{
#ifndef RegionActiveSending
    // Active Sensing. This message is intended to be sent
    // repeatedly to tell the receiver that a connection is alive. Use
    // of this message is optional. When initially received, the
    // receiver will expect to receive another Active Sensing
    // message each 300ms (max), and if it does not then it will
    // assume that the connection has been terminated. At
    // termination, the receiver will turn off all voices and return to
    // normal (non- active sensing) operation.
    if (Settings::UseSenderActiveSensing && (mSenderActiveSensingPeriodicity > 0) && (Platform::now() - mLastMessageSentTime) > mSenderActiveSensingPeriodicity) {
        sendActiveSensing();
        mLastMessageSentTime = Platform::now();
    }

    if (Settings::UseReceiverActiveSensing && mReceiverActiveSensingActivated && (mLastMessageReceivedTime + ActiveSensingTimeout < Platform::now())) {
        mReceiverActiveSensingActivated = false;

        mLastError |= 1UL << ErrorActiveSensingTimeout; // set the ErrorActiveSensingTimeout bit
        if (mErrorCallback)
            mErrorCallback(mLastError, _context);
    }
#endif

    if (inChannel >= MIDI_CHANNEL_OFF)
        return false; // MIDI Input disabled.

    if (!parse())
        return false;

#ifndef RegionActiveSending

    if (Settings::UseReceiverActiveSensing && mMessage.type == MidiType::ActiveSensing) {
        // When an ActiveSensing message is received, the time keeping is activated.
        // When a timeout occurs, an error message is send and time keeping ends.
        mReceiverActiveSensingActivated = true;

        // is ErrorActiveSensingTimeout bit in mLastError on
        if (mLastError & (1 << (ErrorActiveSensingTimeout - 1))) {
            mLastError &= ~(1UL << ErrorActiveSensingTimeout); // clear the ErrorActiveSensingTimeout bit
            if (mErrorCallback)
                mErrorCallback(mLastError, _context);
        }
    }

    // Keep the time of the last received message, so we can check for the timeout
    if (Settings::UseReceiverActiveSensing && mReceiverActiveSensingActivated)
        mLastMessageReceivedTime = Platform::now();

#endif

    handleNullVelocityNoteOnAsNoteOff();

    const bool channelMatch = inputFilter(inChannel);
    if (channelMatch)
        launchCallback();

    thruFilter(inChannel);

    return channelMatch;
}

// -----------------------------------------------------------------------------

// Private method: MIDI parser
template <class Transport, class Settings, class Platform>
bool MidiInterface<Transport, Settings, Platform>::parse()
{
    if (mTransport.available() == 0)
        return false; // No data available.

    // clear the ErrorParse bit
    mLastError &= ~(1UL << ErrorParse);

    // Parsing algorithm:
    // Get a byte from the serial buffer.
    // If there is no pending message to be recomposed, start a new one.
    //  - Find type and channel (if pertinent)
    //  - Look for other bytes in buffer, call parser recursively,
    //    until the message is assembled or the buffer is empty.
    // Else, add the extracted byte to the pending message, and check validity.
    // When the message is done, store it.

    const byte extracted = mTransport.read();

    // Ignore Undefined
    if (extracted == (DataByte)MidiType::Undefined_FD)
        return (Settings::Use1ByteParsing) ? false : parse();

    if (mPendingMessageIndex == 0) {
        // Start a new pending message
        mPendingMessage[0] = extracted;

        // // Check for running status first
        // if (isChannelMessage(getTypeFromStatusByte(mRunningStatus_RX))) {
        //     // Only these types allow Running Status

        //     // If the status byte is not received, prepend it
        //     // to the pending message
        //     if (extracted < 0x80) {
        //         mPendingMessage[0] = mRunningStatus_RX;
        //         mPendingMessage[1] = extracted;
        //         mPendingMessageIndex = 1;
        //     }
        //     // Else: well, we received another status byte,
        //     // so the running status does not apply here.
        //     // It will be updated upon completion of this message.
        // }

        const MidiType pendingType = getTypeFromStatusByte(mPendingMessage[0]);

        switch (pendingType) {
        // 1 byte messages
        case MidiType::Start:
        case MidiType::Continue:
        case MidiType::Stop:
        case MidiType::Clock:
        case MidiType::Tick:
        case MidiType::ActiveSensing:
        case MidiType::SystemReset:
        case MidiType::TuneRequest:
            // Handle the message type directly here.
            mMessage.type = pendingType;
            mMessage.channel = 0;
            mMessage.data1 = 0;
            mMessage.data2 = 0;
            mMessage.valid = true;

            // Do not reset all input attributes, Running Status must remain unchanged.
            // We still need to reset these
            mPendingMessageIndex = 0;
            mPendingMessageExpectedLength = 0;

            return true;
            break;

        // 2 bytes messages
        case MidiType::ProgramChange:
        case MidiType::AfterTouchChannel:
        case MidiType::TimeCodeQuarterFrame:
        case MidiType::SongSelect:
            mPendingMessageExpectedLength = 2;
            break;

        // 3 bytes messages
        case MidiType::NoteOn:
        case MidiType::NoteOff:
        case MidiType::ControlChange:
        case MidiType::PitchBend:
        case MidiType::AfterTouchPoly:
        case MidiType::SongPosition:
            mPendingMessageExpectedLength = 3;
            break;

        case MidiType::SystemExclusiveStart:
        case MidiType::SystemExclusiveEnd:
            // The message can be any length
            // between 3 and MidiMessage::sSysExMaxSize bytes
            mPendingMessageExpectedLength = MidiMessage::sSysExMaxSize;
            mRunningStatus_RX = (StatusByte)MidiType::InvalidType;
            mMessage.sysexArray[0] = (DataByte)pendingType;
            break;

        case MidiType::InvalidType:
        default:
            // This is obviously wrong. Let's get the hell out'a here.
            mLastError |= 1UL << ErrorParse; // set the ErrorParse bit
            if (mErrorCallback)
                mErrorCallback(mLastError, _context); // LCOV_EXCL_LINE

            resetInput();
            return false;
            break;
        }

        if (mPendingMessageIndex >= (mPendingMessageExpectedLength - 1)) {
            // Reception complete
            mMessage.type = pendingType;
            mMessage.channel = getChannelFromStatusByte(mPendingMessage[0]);
            mMessage.data1 = mPendingMessage[1];
            mMessage.data2 = 0; // Completed new message has 1 data byte
            mMessage.length = 1;

            mPendingMessageIndex = 0;
            mPendingMessageExpectedLength = 0;
            mMessage.valid = true;

            return true;
        } else {
            // Waiting for more data
            mPendingMessageIndex++;
        }

        return (Settings::Use1ByteParsing) ? false : parse();
    } else {
        // First, test if this is a status byte
        if (extracted >= 0x80) {
            // Reception of status bytes in the middle of an uncompleted message
            // are allowed only for interleaved Real Time message or EOX
            switch ((MidiType)extracted) {
            case MidiType::Clock:
            case MidiType::Start:
            case MidiType::Tick:
            case MidiType::Continue:
            case MidiType::Stop:
            case MidiType::ActiveSensing:
            case MidiType::SystemReset:

                // Here we will have to extract the one-byte message,
                // pass it to the structure for being read outside
                // the MIDI class, and recompose the message it was
                // interleaved into. Oh, and without killing the running status..
                // This is done by leaving the pending message as is,
                // it will be completed on next calls.

                mMessage.type = (MidiType)extracted;
                mMessage.data1 = 0;
                mMessage.data2 = 0;
                mMessage.channel = 0;
                mMessage.length = 1;
                mMessage.valid = true;

                return true;

                // Exclusive
            case MidiType::SystemExclusiveStart:
            case MidiType::SystemExclusiveEnd:
                if ((mMessage.sysexArray[0] == (DataByte)MidiType::SystemExclusiveStart)
                    || (mMessage.sysexArray[0] == (DataByte)MidiType::SystemExclusiveEnd)) {
                    // Store the last byte (EOX)
                    mMessage.sysexArray[mPendingMessageIndex++] = extracted;
                    mMessage.type = MidiType::SystemExclusive;

                    // Get length
                    mMessage.data1 = mPendingMessageIndex & 0xff; // LSB
                    mMessage.data2 = byte(mPendingMessageIndex >> 8); // MSB
                    mMessage.channel = 0;
                    mMessage.length = mPendingMessageIndex;
                    mMessage.valid = true;

                    resetInput();

                    return true;
                } else {
                    // Well well well.. error.
                    mLastError |= 1UL << ErrorParse; // set the error bits
                    if (mErrorCallback)
                        mErrorCallback(mLastError, _context); // LCOV_EXCL_LINE

                    resetInput();
                    return false;
                }

            default:
                break; // LCOV_EXCL_LINE - Coverage blind spot
            }
        }

        // Add extracted data byte to pending message
        if (mPendingMessage[0] == (DataByte)MidiType::SystemExclusiveStart)
            mMessage.sysexArray[mPendingMessageIndex] = extracted;
        else
            mPendingMessage[mPendingMessageIndex] = extracted;

        // Now we are going to check if we have reached the end of the message
        if (mPendingMessageIndex >= (mPendingMessageExpectedLength - 1)) {
            // SysEx larger than the allocated buffer size,
            // Split SysEx like so:
            //   first:  0xF0 .... 0xF0
            //   midlle: 0xF7 .... 0xF0
            //   last:   0xF7 .... 0xF7
            if (mPendingMessage[0] == (DataByte)MidiType::SystemExclusiveStart) {
                // auto lastByte = mMessage.sysexArray[Settings::SysExMaxSize - 1];
                // mMessage.sysexArray[Settings::SysExMaxSize - 1] = (DataByte)MidiType::SystemExclusiveStart;
                // mMessage.type = MidiType::SystemExclusive;

                // // Get length
                // mMessage.data1 = Settings::SysExMaxSize & 0xff; // LSB
                // mMessage.data2 = byte(Settings::SysExMaxSize >> 8); // MSB
                // mMessage.channel = 0;
                // mMessage.length = Settings::SysExMaxSize;
                // mMessage.valid = true;

                // No need to check against the inputChannel,
                // SysEx ignores input channel
                //launchCallback();

                resetInput();

                return false;
            }

            mMessage.type = getTypeFromStatusByte(mPendingMessage[0]);

            if (isChannelMessage(mMessage.type))
                mMessage.channel = getChannelFromStatusByte(mPendingMessage[0]);
            else
                mMessage.channel = 0;

            mMessage.data1 = mPendingMessage[1];
            // Save data2 only if applicable
            mMessage.data2 = mPendingMessageExpectedLength == 3 ? mPendingMessage[2] : 0;

            // Reset local variables
            mPendingMessageIndex = 0;
            mPendingMessageExpectedLength = 0;

            mMessage.valid = true;

            // Activate running status (if enabled for the received type)
            switch (mMessage.type) {
            case MidiType::NoteOff:
            case MidiType::NoteOn:
            case MidiType::AfterTouchPoly:
            case MidiType::ControlChange:
            case MidiType::ProgramChange:
            case MidiType::AfterTouchChannel:
            case MidiType::PitchBend:
                // Running status enabled: store it from received message
                mRunningStatus_RX = mPendingMessage[0];
                break;

            default:
                // No running status
                mRunningStatus_RX = (StatusByte)MidiType::InvalidType;
                break;
            }
            return true;
        } else {
            // Then update the index of the pending message.
            mPendingMessageIndex++;

            return (Settings::Use1ByteParsing) ? false : parse();
        }
    }
}

// Private method, see midi_Settings.h for documentation
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::handleNullVelocityNoteOnAsNoteOff()
{
    if (Settings::HandleNullVelocityNoteOnAsNoteOff && getType() == MidiType::NoteOn && getData2() == 0) {
        mMessage.type = MidiType::NoteOff;
    }
}

// Private method: check if the received message is on the listened channel
template <class Transport, class Settings, class Platform>
inline bool MidiInterface<Transport, Settings, Platform>::inputFilter(Channel inChannel)
{
    // This method handles recognition of channel
    // (to know if the message is destinated to the Arduino)

    // First, check if the received message is Channel
    if (mMessage.type >= MidiType::NoteOff && mMessage.type <= MidiType::PitchBend) {
        // Then we need to know if we listen to it
        if ((mMessage.channel == inChannel) || (inChannel == MIDI_CHANNEL_OMNI)) {
            return true;
        } else {
            // We don't listen to this channel
            return false;
        }
    } else {
        // System messages are always received
        return true;
    }
}

// Private method: reset input attributes
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::resetInput()
{
    mPendingMessageIndex = 0;
    mPendingMessageExpectedLength = 0;
    mRunningStatus_RX = (StatusByte)MidiType::InvalidType;
}

template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::flushSysex()
{
    resetInput();
}
// -----------------------------------------------------------------------------

/*! \brief Get the last received message's type

 Returns an enumerated type. @see MidiType
 */
template <class Transport, class Settings, class Platform>
inline MidiType MidiInterface<Transport, Settings, Platform>::getType() const
{
    return mMessage.type;
}

/*! \brief Get the channel of the message stored in the structure.

 \return Channel range is 1 to 16.
 For non-channel messages, this will return 0.
 */
template <class Transport, class Settings, class Platform>
inline Channel MidiInterface<Transport, Settings, Platform>::getChannel() const
{
    return mMessage.channel;
}

/*! \brief Get the first data byte of the last received message. */
template <class Transport, class Settings, class Platform>
inline DataByte MidiInterface<Transport, Settings, Platform>::getData1() const
{
    return mMessage.data1;
}

/*! \brief Get the second data byte of the last received message. */
template <class Transport, class Settings, class Platform>
inline DataByte MidiInterface<Transport, Settings, Platform>::getData2() const
{
    return mMessage.data2;
}

/*! \brief Get the System Exclusive byte array.

 @see getSysExArrayLength to get the array's length in bytes.
 */
template <class Transport, class Settings, class Platform>
inline const byte* MidiInterface<Transport, Settings, Platform>::getSysExArray() const
{
    return mMessage.sysexArray;
}

/*! \brief Get the length of the System Exclusive array.

 It is coded using data1 as LSB and data2 as MSB.
 \return The array's length, in bytes.
 */
template <class Transport, class Settings, class Platform>
inline unsigned MidiInterface<Transport, Settings, Platform>::getSysExArrayLength() const
{
    return mMessage.getSysExSize();
}

/*! \brief Check if a valid message is stored in the structure. */
template <class Transport, class Settings, class Platform>
inline bool MidiInterface<Transport, Settings, Platform>::check() const
{
    return mMessage.valid;
}

// -----------------------------------------------------------------------------

template <class Transport, class Settings, class Platform>
inline Channel MidiInterface<Transport, Settings, Platform>::getInputChannel() const
{
    return mInputChannel;
}

/*! \brief Set the value for the input MIDI channel
 \param inChannel the channel value. Valid values are 1 to 16, MIDI_CHANNEL_OMNI
 if you want to listen to all channels, and MIDI_CHANNEL_OFF to disable input.
 */
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::setInputChannel(Channel inChannel)
{
    mInputChannel = inChannel;
}

// -----------------------------------------------------------------------------

/*! \brief Extract an enumerated MIDI type from a status byte.

 This is a utility static method, used internally,
 made public so you can handle MidiTypes more easily.
 */
template <class Transport, class Settings, class Platform>
MidiType MidiInterface<Transport, Settings, Platform>::getTypeFromStatusByte(byte inStatus)
{
    if ((inStatus < 0x80) || (inStatus == (byte)MidiType::Undefined_F4) || (inStatus == (byte)MidiType::Undefined_F5) || (inStatus == (byte)MidiType::Undefined_FD))
        return MidiType::InvalidType; // Data bytes and undefined.

    if (inStatus < 0xf0)
        // Channel message, remove channel nibble.
        return MidiType(inStatus & 0xf0);

    return MidiType(inStatus);
}

/*! \brief Returns channel in the range 1-16
 */
template <class Transport, class Settings, class Platform>
inline Channel MidiInterface<Transport, Settings, Platform>::getChannelFromStatusByte(byte inStatus)
{
    return Channel((inStatus & 0x0f) + 1);
}

template <class Transport, class Settings, class Platform>
bool MidiInterface<Transport, Settings, Platform>::isChannelMessage(MidiType inType)
{
    return (inType == MidiType::NoteOff || inType == MidiType::NoteOn || inType == MidiType::ControlChange || inType == MidiType::AfterTouchPoly || inType == MidiType::AfterTouchChannel || inType == MidiType::PitchBend || inType == MidiType::ProgramChange);
}

// -----------------------------------------------------------------------------

/*! \brief Detach an external function from the given type.

 Use this method to cancel the effects of setHandle********.
 \param inType        The type of message to unbind.
 When a message of this type is received, no function will be called.
 */
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::disconnectCallbackFromType(MidiType inType)
{
    switch (inType) {
    case MidiType::NoteOff:
        mNoteOffCallback = nullptr;
        break;
    case MidiType::NoteOn:
        mNoteOnCallback = nullptr;
        break;
    case MidiType::AfterTouchPoly:
        mAfterTouchPolyCallback = nullptr;
        break;
    case MidiType::ControlChange:
        mControlChangeCallback = nullptr;
        break;
    case MidiType::ProgramChange:
        mProgramChangeCallback = nullptr;
        break;
    case MidiType::AfterTouchChannel:
        mAfterTouchChannelCallback = nullptr;
        break;
    case MidiType::PitchBend:
        mPitchBendCallback = nullptr;
        break;
    case MidiType::SystemExclusive:
        mSystemExclusiveCallback = nullptr;
        break;
    case MidiType::TimeCodeQuarterFrame:
        mTimeCodeQuarterFrameCallback = nullptr;
        break;
    case MidiType::SongPosition:
        mSongPositionCallback = nullptr;
        break;
    case MidiType::SongSelect:
        mSongSelectCallback = nullptr;
        break;
    case MidiType::TuneRequest:
        mTuneRequestCallback = nullptr;
        break;
    case MidiType::Clock:
        mClockCallback = nullptr;
        break;
    case MidiType::Start:
        mStartCallback = nullptr;
        break;
    case MidiType::Tick:
        mTickCallback = nullptr;
        break;
    case MidiType::Continue:
        mContinueCallback = nullptr;
        break;
    case MidiType::Stop:
        mStopCallback = nullptr;
        break;
    case MidiType::ActiveSensing:
        mActiveSensingCallback = nullptr;
        break;
    case MidiType::SystemReset:
        mSystemResetCallback = nullptr;
        break;
    default:
        break;
    }
}

/*! @} */ // End of doc group MIDI Callbacks

// Private - launch callback function based on received type.
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::launchCallback()
{
    if (mMessageCallback != 0)
        mMessageCallback(mMessage);

    // The order is mixed to allow frequent messages to trigger their callback faster.
    switch (mMessage.type) {
        // Notes
    case MidiType::NoteOff:
        if (mNoteOffCallback != nullptr)
            mNoteOffCallback(mMessage.channel, mMessage.data1, mMessage.data2, _context);
        break;
    case MidiType::NoteOn:
        if (mNoteOnCallback != nullptr)
            mNoteOnCallback(mMessage.channel, mMessage.data1, mMessage.data2, _context);
        break;

        // Real-time messages
    case MidiType::Clock:
        if (mClockCallback != nullptr)
            mClockCallback(_context);
        break;
    case MidiType::Start:
        if (mStartCallback != nullptr)
            mStartCallback(_context);
        break;
    case MidiType::Tick:
        if (mTickCallback != nullptr)
            mTickCallback(_context);
        break;
    case MidiType::Continue:
        if (mContinueCallback != nullptr)
            mContinueCallback(_context);
        break;
    case MidiType::Stop:
        if (mStopCallback != nullptr)
            mStopCallback(_context);
        break;
    case MidiType::ActiveSensing:
        if (mActiveSensingCallback != nullptr)
            mActiveSensingCallback(_context);
        break;

        // Continuous controllers
    case MidiType::ControlChange:
        if (mControlChangeCallback != nullptr)
            mControlChangeCallback(mMessage.channel, mMessage.data1, mMessage.data2, _context);
        break;
    case MidiType::PitchBend:
        if (mPitchBendCallback != nullptr)
            mPitchBendCallback(mMessage.channel, (int)((mMessage.data1 & 0x7f) | ((mMessage.data2 & 0x7f) << 7)) + MIDI_PITCHBEND_MIN, _context);
        break;
    case MidiType::AfterTouchPoly:
        if (mAfterTouchPolyCallback != nullptr)
            mAfterTouchPolyCallback(mMessage.channel, mMessage.data1, mMessage.data2, _context);
        break;
    case MidiType::AfterTouchChannel:
        if (mAfterTouchChannelCallback != nullptr)
            mAfterTouchChannelCallback(mMessage.channel, mMessage.data1, _context);
        break;

    case MidiType::ProgramChange:
        if (mProgramChangeCallback != nullptr)
            mProgramChangeCallback(mMessage.channel, mMessage.data1, _context);
        break;
    case MidiType::SystemExclusive:
        if (mSystemExclusiveCallback != nullptr)
            mSystemExclusiveCallback(mMessage.sysexArray, mMessage.getSysExSize(), _context);
        break;

        // Occasional messages
    case MidiType::TimeCodeQuarterFrame:
        if (mTimeCodeQuarterFrameCallback != nullptr)
            mTimeCodeQuarterFrameCallback(mMessage.data1, _context);
        break;
    case MidiType::SongPosition:
        if (mSongPositionCallback != nullptr)
            mSongPositionCallback(unsigned((mMessage.data1 & 0x7f) | ((mMessage.data2 & 0x7f) << 7)), _context);
        break;
    case MidiType::SongSelect:
        if (mSongSelectCallback != nullptr)
            mSongSelectCallback(mMessage.data1, _context);
        break;
    case MidiType::TuneRequest:
        if (mTuneRequestCallback != nullptr)
            mTuneRequestCallback(_context);
        break;

    case MidiType::SystemReset:
        if (mSystemResetCallback != nullptr)
            mSystemResetCallback(_context);
        break;

    case MidiType::InvalidType:
    default:
        break; // LCOV_EXCL_LINE - Unreacheable code, but prevents unhandled case warning.
    }
}

/*! @} */ // End of doc group MIDI Input

// -----------------------------------------------------------------------------
//                                  Thru
// -----------------------------------------------------------------------------

/*! \addtogroup thru
 @{
 */

/*! \brief Set the filter for thru mirroring
 \param inThruFilterMode a filter mode

 @see Thru::Mode
 */
template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::setThruFilterMode(Thru::Mode inThruFilterMode)
{
    mThruFilterMode = inThruFilterMode;
    mThruActivated = mThruFilterMode != Thru::Off;
}

template <class Transport, class Settings, class Platform>
inline Thru::Mode MidiInterface<Transport, Settings, Platform>::getFilterMode() const
{
    return mThruFilterMode;
}

template <class Transport, class Settings, class Platform>
inline bool MidiInterface<Transport, Settings, Platform>::getThruState() const
{
    return mThruActivated;
}

template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::turnThruOn(Thru::Mode inThruFilterMode)
{
    mThruActivated = true;
    mThruFilterMode = inThruFilterMode;
}

template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::turnThruOff()
{
    mThruActivated = false;
    mThruFilterMode = Thru::Off;
}

template <class Transport, class Settings, class Platform>
inline void MidiInterface<Transport, Settings, Platform>::UpdateLastSentTime()
{
    if (Settings::UseSenderActiveSensing && mSenderActiveSensingPeriodicity)
        mLastMessageSentTime = Platform::now();
}

/*! @} */ // End of doc group MIDI Thru

// This method is called upon reception of a message
// and takes care of Thru filtering and sending.
// - All system messages (System Exclusive, Common and Real Time) are passed
//   to output unless filter is set to Off.
// - Channel messages are passed to the output whether their channel
//   is matching the input channel and the filter setting
template <class Transport, class Settings, class Platform>
void MidiInterface<Transport, Settings, Platform>::thruFilter(Channel inChannel)
{
    // If the feature is disabled, don't do anything.
    if (!mThruActivated || (mThruFilterMode == Thru::Off))
        return;

    // First, check if the received message is Channel
    if (mMessage.type >= MidiType::NoteOff && mMessage.type <= MidiType::PitchBend) {
        const bool filter_condition = ((mMessage.channel == inChannel) || (inChannel == MIDI_CHANNEL_OMNI));

        // Now let's pass it to the output
        switch (mThruFilterMode) {
        case Thru::Full:
            send(mMessage.type,
                mMessage.data1,
                mMessage.data2,
                mMessage.channel);
            break;

        case Thru::SameChannel:
            if (filter_condition) {
                send(mMessage.type,
                    mMessage.data1,
                    mMessage.data2,
                    mMessage.channel);
            }
            break;

        case Thru::DifferentChannel:
            if (!filter_condition) {
                send(mMessage.type,
                    mMessage.data1,
                    mMessage.data2,
                    mMessage.channel);
            }
            break;

        default:
            break;
        }
    } else {
        // Send the message to the output
        switch (mMessage.type) {
            // Real Time and 1 byte
        case MidiType::Clock:
        case MidiType::Start:
        case MidiType::Stop:
        case MidiType::Continue:
        case MidiType::ActiveSensing:
        case MidiType::SystemReset:
        case MidiType::TuneRequest:
            sendRealTime(mMessage.type);
            break;

        case MidiType::SystemExclusive:
            // Send SysEx (0xf0 and 0xf7 are included in the buffer)
            sendSysEx(getSysExArrayLength(), getSysExArray(), true);
            break;

        case MidiType::SongSelect:
            sendSongSelect(mMessage.data1);
            break;

        case MidiType::SongPosition:
            sendSongPosition(mMessage.data1 | ((unsigned)mMessage.data2 << 7));
            break;

        case MidiType::TimeCodeQuarterFrame:
            sendTimeCodeQuarterFrame(mMessage.data1, mMessage.data2);
            break;

        default:
            break; // LCOV_EXCL_LINE - Unreacheable code, but prevents unhandled case warning.
        }
    }
}

END_MIDI_NAMESPACE
