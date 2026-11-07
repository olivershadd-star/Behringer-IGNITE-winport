#pragma once
#include <stdint.h>
namespace Ignite
{
	class ISyncListener
	{
	public:
		virtual ~ISyncListener () { }
		virtual void tick (uint16_t tick)
		{
		}
		virtual void onStart (uint16_t tick)
		{
		}
		virtual void onStop (uint16_t tick)
		{
		}
		virtual void onPause (uint16_t tick)
		{
		}
		TimeBase _timebase;
	};
}
