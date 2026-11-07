#pragma once
#include "Common/Os/CrossPlatform/CMsgQueue.h"


namespace Ignite
{

	class IgniteConstants
	{
		public:
			static const uint8_t sysexMsgIdIndex = 6;
			static const uint8_t sysexStartData = 0xF0;
			static const uint8_t sysexEndData = 0xF7;
			static const uint8_t manufacturerCode1 = 0x00;
			static const uint8_t manufacturerCode2 = 0x20;
			static const uint8_t manufacturerCode3 = 0x32;

			static const uint8_t device = 0x7F;
			static const uint8_t modelNumber1 = 0x00;
			static const uint8_t modelNumber2 = 0x00;
			static const uint8_t modelNumber3 = 0x42;
			static const uint8_t internalModelNumber = 0x77;
			static const uint32_t msgQueueSize = 100; //Number of messages for PC App and Engine
			static const uint32_t msgQueueSizeUI = 500; //Number of messages for PC App and Engine
			//msgQueueSize FP: Message size for FP ~60B; which is ~120KB FP has 2(Rx/Tx); ~350KB Considaring MIDI messages
			static const uint32_t FPmsgQueueSize = 3000; //Number of messages
			static const uint32_t threadStackSize = 2048;//Thread stack size

			static const uint8_t defaultTempo = 80;
			static const uint8_t minTempo = 30;
			static const uint16_t maxTempo = 240;//TODO check ref device
	};

	enum class PacketType : uint8_t
	{
		packetSetDeviceId,
		packetStatus,
		packetGetOpMode,
		packetInternal = 0x7E,
		maxPacketType
	};

	enum class MsgType : uint8_t
	{
		msgSetParam = 0x01,
		msgSetParamList,
		msgSetCommandParam,
		msgGetParam,
		msgGetParamList,
		msgSubscribe,
		msgUnsubscribe,
		msgPublish,
		maxMsgType
	};

	struct IgniteMessage
	{
		MsgType messageType = MsgType::msgSetParam;
		uint8_t messageSize;
		uint8_t messageData[50] = { 0 };
	};

	enum class DataType
	{
		u8 = 0,
		u32,
		f32,
		string,
	};

	enum class MTDataType
	{
		BOOL,
		INT8,
		UINT8,
		INT16,
		UINT16,
		INT32,
		UINT32,
		INT64,
		UINT64,
		FLOAT32,
		STRING,
	};

} //namespace Ignite
