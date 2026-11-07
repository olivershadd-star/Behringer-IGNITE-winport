#pragma once
#include <stdint.h>
#include <string>
#include "Firmware/Application/Model/ModelParams.h"
#include "anytype.h"

namespace Ignite
{
	class IListener
	{
	public:
		moduleId_t moduleId;
		virtual ~IListener ()
		{
		}
		virtual void publish (moduleId_t module, moduleId_t moduleSrc, paramId_t param, const AnyType& value, bool isResponse) = 0;
	};
}

