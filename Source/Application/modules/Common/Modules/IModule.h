#pragma once
#include "Firmware/Application/Model/ModelParams.h"
#include <stdint.h>

namespace Ignite
{
	class IModule
	{
	public:
		virtual ~IModule ()
		{
		}

		virtual void setParam (paramId_t id, const uint32_t value) = 0;
		virtual uint32_t getParam (paramId_t id) const = 0;
	};
}

