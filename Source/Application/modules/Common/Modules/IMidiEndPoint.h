#pragma once
#include <functional>
namespace Ignite
{
	namespace Midi
	{
		using MidiCallback = std::function<void (uint8_t* data, uint8_t length)>;
		class IMidiEndPoint
		{
		public:
			virtual ~IMidiEndPoint () {};

			virtual void setSendCallback (MidiCallback sendcb) = 0;
			virtual void setRecvCallback (MidiCallback recvcb) = 0;

			virtual void sendPacket (uint8_t* data, uint8_t length) = 0;
			virtual void onPacketRecieved (uint8_t* data, uint8_t length) = 0;
		};
	}
}
