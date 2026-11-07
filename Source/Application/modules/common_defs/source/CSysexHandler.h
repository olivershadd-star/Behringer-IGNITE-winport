#pragma once
/*#include "KMessageQueue.h" */#include "Common/Os/CrossPlatform/CMsgQueue.h"
#include "IgniteMessage.h"
#include "SysexDefs.h"
#include "Socket.h"
#include "Version.h"
#include "Common/Os/CrossPlatform/CThread.h"
#include <functional>

namespace Ignite {
	using callback = std::function<void(uint8_t*, uint8_t)>;
	using parser = std::function<void(uint8_t*, uint8_t, callback)>;

	class CSysexHandler {
	public:
		CSysexHandler();
		void handleSysexMessage(uint8_t* array, uint8_t length, callback cb, parser internal, parser external);
		void sendSysex(const MsgType& type, PacketType pkt_type, uint8_t modId, uint8_t functionId, uint8_t* value, const uint8_t& len);
		void createSysexMessage(PacketType pkt_type, uint8_t* array, uint8_t length);

		WSASession Session;
		UDPSocket Sock;
		unsigned short Port = 8888;
		std::string IP = "127.0.0.1";
	private:
		inline bool isValidSysex(uint8_t* data, uint8_t length);
		bool isInternalSysex(uint8_t* data);
		void engineThreadFunc(void);
		void startEngine(void);

		std::thread t1;
		CThread _engineThread;
		uint8_t _sysexPkt[128] = { 0 };
		CMsgQueue<IgniteMessage> _msgqueue;
	};

} // namespace Ignite
