#pragma once
namespace Ignite {
	// Compatible with CMSIS OS, Other OS Implementations can interpret differently
	// TODO Check, Use Linux prio?
	enum ThreadPriority {
		osPriorityNone = 0, ///< No priority (not initialized).
		osPriorityLow = 8, ///< Priority: low
		osPriorityBelowNormal = 16, ///< Priority: below normal
		osPriorityNormal = 24, ///< Priority: normal
		osPriorityAboveNormal = 32, ///< Priority: above normal
		osPriorityHigh = 40, ///< Priority: high
		osPriorityRealtime = 48, ///< Priority: realtime
		osPriorityISR = 56, ///< Reserved for ISR deferred thread.
		osPriorityReserved = 0x7FFFFFFF ///< Prevents enum down-size compiler optimization.
	};
	using ThreadFunction = void(*)(void*);

} // namespace Ignite

