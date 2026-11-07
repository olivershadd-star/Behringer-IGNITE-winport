#pragma once

#include <Common/Modules/anytype.h>
#include "common_defs/source/IgniteMessage.h"
#include <cstring>

namespace Ignite {
	class Module;
	class ParameterBase {
	public:
		ParameterBase(const char* Name, paramId_t param, Module& module)
			: _paramid(param), _module(module)
		{
			// Set Name
			if (Name) {
#ifdef _WIN64
				strncpy_s(name_, Name, (sizeof(name_) - 1)); //strncpy_s making linux build fail, but strncpy gives Windows build warning TBD ?
#else
				strncpy (name_, Name, (sizeof (name_) - 1));
#endif
			}
		}
		virtual ~ParameterBase()
		{
		}
		paramId_t GetParamID() const { return _paramid; }
		Module& GetModule() const { return _module; }
		const char* GetName() const { return name_; }
		virtual MTDataType getType() const = 0;
		virtual bool setValue(moduleId_t moduleSrc, const AnyType& newval, bool isPlayMode) = 0;
		virtual AnyType getValue() const = 0;

	protected:
		paramId_t _paramid;
		Module& _module;
		char name_[40] = { '\0' };
	};
}
