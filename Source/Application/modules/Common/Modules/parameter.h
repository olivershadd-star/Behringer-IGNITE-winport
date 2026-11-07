#pragma once
#include <cstring>
#include <Common/Modules/anytype.h>
#include "common_defs/source/IgniteMessage.h"
#include <Common/Modules/parameterbase.h>

namespace Ignite
{
	class Module;
	template <typename T>
	class Parameter : public ParameterBase {
	public:
		Parameter (const char* Name, paramId_t param, Module& module)
			: ParameterBase (Name, param, module)
		{
		}
		~Parameter () = default;

		void Init (T Min, T Max, T Default = (T)0)
		{
			_min = Min;
			_max = Max;
			_default = Default;
			setValue (_default);
		}

		MTDataType getType () const override
		{
			return model::GetType (_value);
		}

		bool setValue (const T& newValue)
		{
			T changedValue = newValue;
			if (model::GetType (_value) != MTDataType::STRING)
			{
				if (newValue > _max)
				{
					changedValue = _max;
				}
				else if (newValue < _min)
				{
					changedValue = _min;
				}
			}

			_value = changedValue;
			return true;
		}

		bool setValue (moduleId_t moduleSrc, const AnyType& newval, bool isPlayMode) override
		{
			if (setValue (newval.get<T> ()))
			{
				return true;
			}
			return false;
		}

		operator const T ()
		{
			return getValue ();
		}

		virtual T getValue ()
		{
			return _value;
		}

		AnyType getValue () const override
		{
			return _value;
		}

	private:
		T _value;
		T _min, _max, _default;
	};
}
