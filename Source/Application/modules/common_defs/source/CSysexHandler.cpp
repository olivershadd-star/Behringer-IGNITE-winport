#ifdef WINDOWS_PLATFORM
#include "CSysexHandler.h"
#endif

using namespace Ignite;
using namespace std;

/*!
 *  Constructor.
 */
CSysexHandler::CSysexHandler() :_msgqueue(IgniteConstants::msgQueueSize), _sysexPkt{}, _engineThread("engine", 1600, osPriorityHigh)
{
	_sysexPkt[0] = IgniteConstants::sysexStartData;
	_sysexPkt[1] = IgniteConstants::manufacturerCode1;
	_sysexPkt[2] = IgniteConstants::manufacturerCode2;
	_sysexPkt[3] = IgniteConstants::manufacturerCode3;
	_sysexPkt[4] = IgniteConstants::modelNumber1;
	_sysexPkt[5] = IgniteConstants::modelNumber2;
	_sysexPkt[6] = IgniteConstants::modelNumber3;
	_sysexPkt[7] = IgniteConstants::device;
	startEngine();
}

void CSysexHandler::engineThreadFunc(void)
{
	IgniteMessage msg;
	while (true) {
		if (!_msgqueue.isEmpty())
		{
			_msgqueue.get(msg, TimeOut::kWaitForever);
			Sock.SendMidiMessages(IP, Port, (const char*)&msg, sizeof(msg));
		}
	}
}

void CSysexHandler::startEngine(void)
{
	auto enginethreadcb = [](void* context) {
		static_cast<CSysexHandler*>(context)->engineThreadFunc();
	};
	_engineThread.startThread(enginethreadcb, this);
}

void CSysexHandler::handleSysexMessage(uint8_t* array, uint8_t length, callback cb, parser internal, parser external)
{
	if (isValidSysex(array, length))
		isInternalSysex(array) ? internal(_sysexPkt, length, cb) : external(_sysexPkt, length, cb);
}

bool CSysexHandler::isInternalSysex(uint8_t* data)
{
	return (data[8] == (uint8_t)PacketType::packetInternal) ? true : false;
}

bool CSysexHandler::isValidSysex(uint8_t* data, uint8_t length)
{
	return (length > 8) && (data[1] == IgniteConstants::manufacturerCode1)
		&& (data[2] == IgniteConstants::manufacturerCode2) && (data[3] == IgniteConstants::manufacturerCode3)
		&& (data[4] == IgniteConstants::modelNumber1) && (data[5] == IgniteConstants::modelNumber2)
		&& (data[6] == IgniteConstants::modelNumber3) && (data[7] == IgniteConstants::device);
}

void CSysexHandler::createSysexMessage(PacketType pkt_type, uint8_t* data, uint8_t length)
{
	int i;

	if (length < 128) {
		for (i = 9; i < length; i++)
		{
			_sysexPkt[i] = data[i];
		}
		_sysexPkt[8] = (uint8_t)pkt_type;
		_sysexPkt[i] = IgniteConstants::sysexEndData;
	}
}

void CSysexHandler::sendSysex(const MsgType& type, PacketType pkt_type, uint8_t modId, uint8_t functionId, uint8_t* data, const uint8_t& len)
{
	IgniteMessage msg;

	createSysexMessage(pkt_type, data, len);
	msg.messageType = type;
	msg.messageSize = len;

	for (int i = 1; i <= len; i++)
	{
		msg.messageData[i] = _sysexPkt[i];
	}
	_msgqueue.put(msg, TimeOut::kNoWait);
}
