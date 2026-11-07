#pragma once
#include <stdint.h>
#include "anytype.h"
#include "Common/Modules/IListener.h"

namespace Ignite
{
	class IDevice
	{
	public:
		virtual ~IDevice ()
		{
		}

		virtual void addListener (IListener* listener) = 0;
		virtual bool isIDeviceReady (void) = 0;

		virtual void setParam (moduleId_t moduleSrc, moduleId_t moduleDst, paramId_t param, const AnyType value, bool isPlayMode = false) = 0;
		virtual void setParam (moduleId_t moduleSrc, moduleId_t moduleDst, std::vector<IgniteParamList> paramlist, bool isPlayMode = false) = 0;
		virtual void SetCommandParam (moduleId_t moduleSrc, moduleId_t moduleDst, paramId_t param, bool isPlayMode = false) = 0;
		virtual bool SetCommand (moduleId_t moduleSrc, moduleId_t moduleDst, paramId_t param, AnyType value, bool isPlayMode = false) = 0;

		virtual std::vector<IgniteParamList> getParam (moduleId_t moduleSrc, moduleId_t moduleDst, std::vector<IgniteParamList> paramlist) = 0;
		virtual void getParam (moduleId_t moduleSrc, moduleId_t moduleDst, paramId_t param) = 0;

		virtual void subscribe (moduleId_t module, paramId_t param, IListener* src) = 0;
		virtual void unsubscribe (moduleId_t module, paramId_t param, IListener* src) = 0;
		virtual bool SaveAllData() = 0;

		//Pattern interface 
		
		virtual std::list<std::string> EngineGetPatternList (bool isDisplayName = false) = 0;
		virtual ClientPatternData EngineGetPatternData (std::string patternName) = 0;
		virtual std::list<ClienPatterntBarData>  EngineGetBarData (std::string patternName) = 0;
		virtual std::list<ClientPatternStepData> EngineGetStepData (std::string patternName, uint16_t BarId) = 0;
		virtual std::list<PatternDataUpdateReasonType> EnginePatternGetUndoList(void) = 0;

		virtual bool EngineSetPatternData (moduleId_t moduleSrc, std::string patternName, ClientPatternData patternData, bool addToUndoList = false, PatternDataUpdateReasonType UpdateReasonType = PatternDataUpdateReasonType::PatternDataUpdateReason_PATTERNDATA) = 0;
		//virtual bool EngineSetPatternData (moduleId_t moduleSrc, std::string patternName, ClientPatternData& patternData, PatternDataUpdateLocation location, bool addToUndoList = false, PatternDataUpdateReasonType UpdateReasonType = PatternDataUpdateReasonType::PatternDataUpdateReason_PATTERNDATA) = 0;

		virtual bool EngineSetBarData (moduleId_t moduleSrc, std::string patternName, uint16_t BarId, ClienPatterntBarData barData) = 0;
		virtual bool EngineSetStepData (moduleId_t moduleSrc, std::string patternName, uint16_t BarId, uint16_t stepId, ClientPatternStepData stepData) = 0;

		virtual bool  EngineCopyPatternBar (std::string patternName, uint16_t srcBarId, uint16_t destBarId) = 0;
		virtual bool  EngineAddPatternBar (std::string patternName, bool CopyAndCreate, uint16_t FromBarId, uint16_t NumBarToAdd = 1) = 0;
		virtual bool  EngineRemovePatternBar (std::string patternName, uint16_t BarId, uint16_t NumBarToRemove = 0) = 0;
		virtual bool  EngineInsertPatternStep (std::string patternName, uint16_t BarId, uint8_t stepCount, uint8_t InsertAt, std::vector<ClientPatternStepData> ToStepDataList) = 0;
		virtual bool  EngineAddNodeData (std::string patternName, uint16_t BarId, uint16_t stepId, ClientPatternNodeData nodeData) = 0;
		virtual bool  EngineDelNodeData (std::string patternName, uint16_t BarId, uint16_t stepId, uint16_t nodeId) = 0;
		virtual bool  EngineAddNodeData (std::string patternName, uint16_t BarId, std::map<ClientPatternNodeData, std::list<uint8_t>> stepMap) = 0;
		virtual bool  EnginecopyPattern (std::string SrcpatternName, std::string DstpatternName) = 0;
		virtual bool  EngineInsertPatternBar (std::string patternName, uint16_t InsertPosition) = 0;
		virtual bool PatternMngrPatternRotate(std::string patternName, uint16_t BarID, uint16_t StepID) = 0;
		//Pattern interface END
	};
}
