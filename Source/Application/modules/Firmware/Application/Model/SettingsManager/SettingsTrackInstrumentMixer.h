#pragma once
#include <stdint.h>
#include <string>
#include "module.h"
#include "Common/Modules/CSong.h"
#include "Firmware/Application/Model/ModelParams.h"

namespace Ignite
{
	class IgniteEngine;
	class SettingsTrackInstrumentMixer : public Module
	{
	public:
		SettingsTrackInstrumentMixer (IParamChangeListener* listener, IgniteEngine& model);
		SettingsTrackInstrumentMixer (const SettingsTrackInstrumentMixer&) = delete;
		SettingsTrackInstrumentMixer& operator= (const SettingsTrackInstrumentMixer&) = delete;
		SettingsTrackInstrumentMixer (SettingsTrackInstrumentMixer&&) = delete;
		SettingsTrackInstrumentMixer& operator= (SettingsTrackInstrumentMixer&&) = delete;
		~SettingsTrackInstrumentMixer () = default;

		void setParamList (moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist, bool isPlayMode)override;
		void onParameterChange (moduleId_t moduleSrc, ParameterBase* param, bool isPlayMode) override;
		void SetCommandParam (moduleId_t moduleSrc, paramId_t param, bool isPlayMode) override;
		void getParam (moduleId_t moduleSrc, paramId_t param)override;
		void ParamHandler (moduleId_t moduleSrc, ParameterBase* param, bool SendNotification);
		std::vector<IgniteParamList> getParamList (moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist)override;

	private:
		IgniteEngine& engine;
		IParamChangeListener* paramlistener;
		void SetDefaultUndoListData ();
		void SaveData();
		void RestoreDataData (bool isDefault);
		void SetUndoDataData (void);
		void SaveTrackInsrument (void);
		bool isUndilistNeedUpdate = true;
		uint8_t CurrentTrack = 0;
		SettingsTrackInstrumentMixerData _SettingsTrackInstrumentMixerData;
		std::vector<SettingsTrackInstrumentMixerData> _DefaultUndoSettingsTrackInstrumentMixerDataList;
		std::vector<SettingsTrackInstrumentMixerData> _UndoSettingsTrackInstrumentMixerDataList;
	};
}