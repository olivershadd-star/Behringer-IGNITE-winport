#include <string>
#include <iostream>
#include <iterator>
#include <list>
#include "Common/Modules/IModule.h"
#include "common_defs/source/EngineDataStruct.h"
#include "Firmware/Application/Model/IgniteEngine.h"
#include "Firmware/Application/Model/SettingsManager/SettingsTrackInstrumentMixer.h"

using namespace Ignite;

SettingsTrackInstrumentMixer::SettingsTrackInstrumentMixer (IParamChangeListener* listener, IgniteEngine& model) : paramlistener (listener), engine (model),
Module ("SettingsTrackInstrumentMixer", (moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, (unsigned int)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerParamMax, listener)
{
	AddParameter<int8_t> ((int8_t)SettingsTrackInstrumentMixerParam::paramTMActiveTrack, 0, 63, 0);
	AddParameter<int8_t> ((int8_t)SettingsTrackInstrumentMixerParam::paramTMPan, 0, 127, 63);
	AddParameter<int8_t> ((int8_t)SettingsTrackInstrumentMixerParam::paramTMVolume, 0, 127, 63);
	AddParameter<int8_t> ((paramId_t)SettingsTrackInstrumentMixerParam::paramUndoCmd, 0, 1, 0);
	AddParameter<uint8_t> ((paramId_t)SettingsTrackInstrumentMixerParam::paramUndoListCmd, 0, 127, 0);
	AddParameter<int8_t> ((paramId_t)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgInit, 0, 1, 0);
	AddParameter<int8_t> ((paramId_t)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgSave, 0, 1, 0);
	AddParameter<uint8_t> ((paramId_t)SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgCancel, 0, 127, 0);
	AddParameter<int8_t>((paramId_t)SettingsTrackInstrumentMixerParam::paramSaveAll, 0, 1, 0);
	engine.updateModuleReadyStatus((moduleId_t)ModuleName::moduleSettingsTrackInstrumentMixer, true);
	// Note : no data stored in file, the mixer data belong to Instrument
	SetDefaultUndoListData ();
}
void SettingsTrackInstrumentMixer::SetDefaultUndoListData ()
{
	Instrument* instrument = nullptr;
	_DefaultUndoSettingsTrackInstrumentMixerDataList.clear ();
	if ((engine.songManager != nullptr) && (engine.songManager->activeSong != nullptr) && (engine.songManager->getActiveSong ()->getEditScene () != nullptr))
	{
		auto& trackList = engine.songManager->getActiveSong ()->getEditScene ()->_sceneData->trackList;
		for (auto& track1 : trackList)
		{
			_SettingsTrackInstrumentMixerData = { 0 };
			_SettingsTrackInstrumentMixerData.MixerTrack = track1.getTrackId ();
			instrument = track1.getTrackTxInstrument ();
			if (instrument != nullptr)
			{
				_SettingsTrackInstrumentMixerData.MixerPanValue = instrument->getTrackMixerPan ();
				_SettingsTrackInstrumentMixerData.MixerVolumeValue = instrument->getTrackMixerVolume ();
			}
			_DefaultUndoSettingsTrackInstrumentMixerDataList.push_back (_SettingsTrackInstrumentMixerData);
		}
	}
	if (!(_DefaultUndoSettingsTrackInstrumentMixerDataList.empty ()))
	{
		_SettingsTrackInstrumentMixerData = (*(_DefaultUndoSettingsTrackInstrumentMixerDataList.begin ()));
		isUndilistNeedUpdate = false;
		_UndoSettingsTrackInstrumentMixerDataList.clear ();
	}
	else
	{
		isUndilistNeedUpdate = true;
		_UndoSettingsTrackInstrumentMixerDataList.clear ();
	}
}
void SettingsTrackInstrumentMixer::SaveTrackInsrument (void)
{
	if (!(_DefaultUndoSettingsTrackInstrumentMixerDataList.empty ()))
	{
		for (auto& it : _DefaultUndoSettingsTrackInstrumentMixerDataList)
		{
			engine.instrumentManager->SaveEditTrackMixerInstrument (it.MixerTrack);
		}
	}
	_UndoSettingsTrackInstrumentMixerDataList.clear ();
	isUndilistNeedUpdate = true;
}
void SettingsTrackInstrumentMixer::RestoreDataData (bool isDefault)
{
	SettingsTrackInstrumentMixerData _TmpMixerData;

	if (isDefault)
	{
		for (auto& it : _DefaultUndoSettingsTrackInstrumentMixerDataList)
		{
			_TmpMixerData = it;
			engine.instrumentManager->setTrackMixerTrack (_TmpMixerData.MixerTrack);
			engine.instrumentManager->setTrackMixerPanValue (_TmpMixerData.MixerPanValue);
			engine.instrumentManager->setTrackMixerVolumeValue (_TmpMixerData.MixerVolumeValue);
			engine.instrumentManager->SaveEditTrackMixerInstrument (_TmpMixerData.MixerTrack);
		}
	}
	else if (!_UndoSettingsTrackInstrumentMixerDataList.empty ())
	{
		_TmpMixerData = (*(_UndoSettingsTrackInstrumentMixerDataList.begin ()));
		engine.instrumentManager->setTrackMixerTrack (_TmpMixerData.MixerTrack);
		engine.instrumentManager->setTrackMixerPanValue (_TmpMixerData.MixerPanValue);
		engine.instrumentManager->setTrackMixerVolumeValue (_TmpMixerData.MixerVolumeValue);
		_SettingsTrackInstrumentMixerData = _TmpMixerData;
		CurrentTrack = _SettingsTrackInstrumentMixerData.MixerTrack;
		_UndoSettingsTrackInstrumentMixerDataList.erase (_UndoSettingsTrackInstrumentMixerDataList.begin ());

	}
}
void SettingsTrackInstrumentMixer::SetUndoDataData (void)
{
	if (_UndoSettingsTrackInstrumentMixerDataList.size () > MAX_SETTINGS_UNDO_COUNT)
	{
		auto it = _UndoSettingsTrackInstrumentMixerDataList.end ();
		it--;
		_UndoSettingsTrackInstrumentMixerDataList.erase (it);
	}

	engine.instrumentManager->setTrackMixerTrack (CurrentTrack);
	_SettingsTrackInstrumentMixerData.MixerPanValue = engine.instrumentManager->getTrackMixerPanValue ();
	_SettingsTrackInstrumentMixerData.MixerVolumeValue = engine.instrumentManager->getTrackMixerVolumeValue ();
	_SettingsTrackInstrumentMixerData.MixerTrack = CurrentTrack;
	_UndoSettingsTrackInstrumentMixerDataList.insert (_UndoSettingsTrackInstrumentMixerDataList.begin (), _SettingsTrackInstrumentMixerData);
}
void SettingsTrackInstrumentMixer::setParamList (moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist, bool isPlayMode)
{
	for (std::vector<IgniteParamList>::iterator it = paramlist.begin(); it != paramlist.end(); ++it)
	{
		//set value for each, this calls onParameterChange
		FindParameter((*it).param)->setValue(moduleSrc, (*it).MsgValue, isPlayMode);
	}
}
std::vector<IgniteParamList> SettingsTrackInstrumentMixer::getParamList (moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist)
{
	std::vector<IgniteParamList> retParam = {};
	IgniteParamList paramData = { 0 };

	for (std::vector<IgniteParamList>::iterator it = paramlist.begin (); it != paramlist.end (); ++it)
	{
		switch ((SettingsTrackInstrumentMixerParam)(*it).param)
		{
			case SettingsTrackInstrumentMixerParam::paramUndoListCmd:
			{
				paramData = { 0 };
				paramData.param = (paramId_t)SettingsTrackInstrumentMixerParam::paramUndoListCmd;
				paramData.Count = (uint32_t)_UndoSettingsTrackInstrumentMixerDataList.size (); //set the number of params
				retParam.push_back (paramData);

				if (_UndoSettingsTrackInstrumentMixerDataList.size ())
					retParam.push_back (paramData); // intentionally added to indicate undo available
				break;
			}
			case SettingsTrackInstrumentMixerParam::paramTMActiveTrack:
				paramData = { (*it).param, engine.instrumentManager->getTrackMixerTrack (), 0, 0 };
				retParam.push_back (paramData);
				break;

			case SettingsTrackInstrumentMixerParam::paramTMPan:
				paramData = { (*it).param, engine.instrumentManager->getTrackMixerPanValue (), 0, 0 };
				retParam.push_back (paramData);
				break;

			case SettingsTrackInstrumentMixerParam::paramTMVolume:
				paramData = { (*it).param, engine.instrumentManager->getTrackMixerVolumeValue (), 0, 0 };
				retParam.push_back (paramData);
				break;
		}
	}

	return  retParam;
}
void SettingsTrackInstrumentMixer::SetCommandParam (moduleId_t moduleSrc, paramId_t param, bool isPlayMode)
{
	ParamHandler (moduleSrc, FindParameter (param), false);
}
void SettingsTrackInstrumentMixer::getParam (moduleId_t moduleSrc, paramId_t param)
{
	//this funcation not used; use get param list
}
void SettingsTrackInstrumentMixer::onParameterChange (moduleId_t moduleSrc, ParameterBase* param, bool isPlayMode)
{
	if ((SettingsTrackInstrumentMixerParam)param->GetParamID () == SettingsTrackInstrumentMixerParam::paramTMPan ||
		(SettingsTrackInstrumentMixerParam)param->GetParamID () == SettingsTrackInstrumentMixerParam::paramTMVolume)
	{
		if (!isPlayMode)
			SetUndoDataData ();
	}
	ParamHandler (moduleSrc, param, true);
}
void SettingsTrackInstrumentMixer::ParamHandler (moduleId_t moduleSrc, ParameterBase* param, bool SendNotification)
{
	if (isUndilistNeedUpdate)
	{
		SetDefaultUndoListData ();
	}
	switch ((SettingsTrackInstrumentMixerParam)param->GetParamID ())
	{
		case SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgInit:
			SetDefaultUndoListData ();
			break;
		case SettingsTrackInstrumentMixerParam::paramUndoCmd:
			RestoreDataData (false);
			break;
		case SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgCancel:
			RestoreDataData (true);
			break;
		case SettingsTrackInstrumentMixerParam::paramSaveAll:
			if (_DefaultUndoSettingsTrackInstrumentMixerDataList.empty())
				break;
			//fallthrough
		case SettingsTrackInstrumentMixerParam::paramSettingsTrackInstrumentMixerCnfgSave:
			SaveTrackInsrument ();
			break;
		case SettingsTrackInstrumentMixerParam::paramTMActiveTrack:
			CurrentTrack = param->getValue ().get<uint8_t> ();
			engine.instrumentManager->setTrackMixerTrack (CurrentTrack);
			break;
		case SettingsTrackInstrumentMixerParam::paramTMPan:
			engine.instrumentManager->setTrackMixerPanValue (param->getValue ().get<uint8_t> ());
			break;
		case SettingsTrackInstrumentMixerParam::paramTMVolume:
			engine.instrumentManager->setTrackMixerVolumeValue (param->getValue ().get<uint8_t> ());
			break;
		default:
			assert (0);
			break;
	}
	if (engine.getAutoSaveStatus())
	{
		SaveData();
	}
	if (SendNotification)
	{
		/* Send notification to the subscribed modules via engine */
		paramlistener->onParameterChanged (moduleSrc, param);
	}
}
void SettingsTrackInstrumentMixer::SaveData()
{
	if (_DefaultUndoSettingsTrackInstrumentMixerDataList.empty())
		return;
	SaveTrackInsrument();

}