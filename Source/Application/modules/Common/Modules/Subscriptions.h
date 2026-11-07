#pragma once
#include "Common/Modules/module.h"
#include "Common/Modules/parameter.h"
#include <algorithm>
#include <vector>
namespace Ignite {
	class Subscriptions {
	public:
		Subscriptions () = default;
		~Subscriptions () = default;
		void add (ParameterBase* param)
		{
			if (!exist (param)) {
				_paramsubs.push_back (param);
			}
		}
		void remove (ParameterBase* param)
		{
			if (!exist (param)) {
				return;
			}
			auto it = std::find (_paramsubs.begin (), _paramsubs.end (), param);
			_paramsubs.erase (it);
		}

		void add (Module* module)
		{
			if (!exist (module)) {
				_modulesubs.push_back (module);
			}
		}
		void remove (Module* module)
		{
			if (!exist (module)) {
				return;
			}
			auto it = std::find (_modulesubs.begin (), _modulesubs.end (), module);
			_modulesubs.erase (it);
		}

		bool exist (ParameterBase* param)
		{
			if (std::find (_paramsubs.begin (), _paramsubs.end (), param) != _paramsubs.end ()) {
				return true;
			}
			return false;
		}

		bool exist (Module* module)
		{
			if (std::find (_modulesubs.begin (), _modulesubs.end (), module) != _modulesubs.end ()) {
				return true;
			}
			return false;
		}

	private:
		std::vector<ParameterBase*> _paramsubs;
		std::vector<Module*> _modulesubs;
	};
};