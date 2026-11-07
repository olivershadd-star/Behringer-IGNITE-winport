#pragma once
#include <stdint.h>
#include <string>
#include "Firmware/Application/Model/ModelParams.h"
#define MIDI_HANDLE_STATE_IDLE		0
#define MIDI_HANDLE_STATE_RECIVE	1
#define MIDI_HANDLE_STATE_SYSEX_IGNORE	2

//#define MIDI_NOTE_OFF_MSG_ID			0x80	// NOTE_OFF
//#define MIDI_NOTE_ON_MSG_ID				0x90 	// NOTE_ON
//#define MIDI_AFTERTOUCH_MSG_ID			0xA0	// AFTERTOUCH
//#define MIDI_CC_MSG_ID					0xB0	// CC msg Identifier Bx, Continuous controller
//#define MIDI_CONTROLL_MSG_ID			0xC0	// Patch/Control change
//#define MIDI_CHANNEL_PRESure_MSG_ID		0xD0	// Channel Pressure
//#define MIDI_PITCH_BEND_MSG_ID			0xE0	// PITCH_BEND
//#define MIDI_SYSEX_MSG_ID				0xF0	// SysEx msg Identifier
//
//#define MIDI_SYM_COMMON_MSG_TIMING_CLOCK		0xF8 // Single byte
//#define MIDI_SYM_COMMON_MSG_START_SEQUENCE		0xFA
//#define MIDI_SYM_COMMON_MSG_CONTINUE_SEQUENCE	0xFB
//#define MIDI_SYM_COMMON_MSG_STOP_SEQUENCE		0xFC
//#define MIDI_SYM_COMMON_MSG_ACTIVE_SENSING		0xFE
//#define MIDI_SYM_COMMON_MSG_SYSTEM_RESET		0xFF

#define 	MIDI_HANDLE_STATE_IDLE   0
#define 	MIDI_HANDLE_STATE_RECIVE 1
#define 	MIDI_HANDLE_STATE_SYSEX_IGNORE 2

#define 	MIDI_NOTE_OFF_MSG_ID	0x80
#define 	MIDI_NOTE_ON_MSG_ID		0x90
#define 	MIDI_AFTERTOUCH_MSG_ID  0xA0
#define 	MIDI_PITCH_BEND_MSG_ID  0xE0
#define 	MIDI_CC_MSG_ID			0xB0
#define 	MIDI_CONTROLL_MSG_ID	0xC0
#define 	MIDI_CHANNEL_PRESSURE_MSG_ID		0xD0
#define 	MIDI_SYM_COMMON_MSG					0xF0//sysex or CC msg filter start with 0xF
#define 	MIDI_SYSEX_MSG_ID_START				0xF0
#define 	MIDI_SYSEX_MSG_ID_END				0xF7
#define 	MIDI_SYM_COMMON_MSG_TIMING_CLOCK	0xF8
#define 	MIDI_SYM_COMMON_MSG_START_SEQUENCE  0xFA
#define 	MIDI_SYM_COMMON_MSG_CONTINUE_SEQUENCE	0xFB
#define 	MIDI_SYM_COMMON_MSG_STOP_SEQUENCE		0xFC
#define 	MIDI_SYM_COMMON_MSG_ACTIVE_SENSING		0xFE
#define 	MIDI_SYM_COMMON_MSG_SYSTEM_RESET		0xFF


#define MIDI_PACKET_MSG_SIZE_TYPE_1 1
#define MIDI_PACKET_MSG_SIZE_TYPE_2 2
#define MIDI_PACKET_MSG_SIZE_TYPE_3 3

#define MIDI_MSG_OK		0
#define MIDI_MSG_IGNORE 1
#define MIDI_MSG_SYSTEM 2
#define MIDI_MSG_ERROR	3
namespace Ignite
{
	class FrontPannelUtility
	{
	public:
		explicit FrontPannelUtility (FrontPannelManager* FrontPanneMgr);
		FrontPannelUtility (const FrontPannelUtility&);
		FrontPannelUtility& operator= (const FrontPannelUtility&) = default;
		~FrontPannelUtility () = default;

		bool SysMessageHandlerFromMCU (SysMessage Message);
		void MidiClockDetect(uint8_t PortId);
	private:
		FrontPannelManager* FrontPanneMgr;

		std::vector<std::chrono::time_point<std::chrono::system_clock>> MidiClkRecivedTime;
		float totalElapsedTime = 0.0f;
		int numberOfTaps = 0;
		bool _MidiClockDetectLock = false;
		uint8_t MidiRxClkPortId = IGNITE_CLK_PORT_MAX+1;
		uint8_t MidiMCUPortStatus1 = 0, MidiMCUPortStatus2 = 0, MidiMCUPortStatus3 = 0, MidiMCUPortStatus4 = 0, MidiMCUPortStatus5 = 0;
		uint8_t MCUPortRxWaitNum1 = 0, MCUPortRxWaitNum2 = 0, MCUPortRxWaitNum3 = 0, MCUPortRxWaitNum4 = 0, MCUPortRxWaitNum5 = 0;
		std::vector <uint8_t> MidiMCUPortData1, MidiMCUPortData2, MidiMCUPortData3, MidiMCUPortData4, MidiMCUPortData5;

		bool SystemMessageHandlerFromMCU (SysMessage Message);

		void handleReceiveState(std::vector<uint8_t>& Tmp, uint8_t& TmpMCUPortRxWaitNum, uint8_t& TmpMidiMCUPortStatus, const String& portname, bool& Proceed);
		void handleIdleState(std::vector<uint8_t>& Tmp, uint8_t& TmpMCUPortRxWaitNum, uint8_t& TmpMidiMCUPortStatus, uint8_t IgniteMapPortID, const String& portname);
		void handleSysExIgnore(std::vector<uint8_t>& Tmp, uint8_t& TmpMidiMCUPortStatus, uint8_t IgniteMapPortID);
		bool MidiMessageHandlerFromMCU(SysMessage& Message);

		bool KeyMessageHandlerFromMCU (SysMessage Message);
		bool LedMessageHandlerFromMCU (SysMessage Message);
		bool EncoderMessageHandlerFromMCU (SysMessage Message);
		bool GateCvMessageHandlerFromMCU (SysMessage Message);
		void SetMcuLedMapping ();
		uint8 isValidMidiMsgToRecive(uint8 data);
	};
}
