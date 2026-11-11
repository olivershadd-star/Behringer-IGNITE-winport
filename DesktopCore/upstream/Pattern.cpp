#include <stdint.h>
#include <list>
#include <string>
#include "Common/Modules/Bar.h"
#include "Common/Modules/Step.h"
#include "Firmware/Application/Model/ModelParams.h"
#include "Firmware/Application/Model/PatternManager.h"
#include "Firmware/Application/Model/IgniteEngine.h"

using namespace Ignite;
class IgniteEngine;

std::unordered_map <TimeBase, TickLength_t> timeBaseToTicksPerStep = {
	{TimeBase::Base_1,   static_cast <TickLength_t> (192)},
	{TimeBase::Base_2,   static_cast <TickLength_t> (96)},
	{TimeBase::Base_2T,  static_cast <TickLength_t> (64)},
	{TimeBase::Base_4,   static_cast <TickLength_t> (48)},
	{TimeBase::Base_4T,  static_cast <TickLength_t> (32)},
	{TimeBase::Base_8,	 static_cast <TickLength_t> (24)},
	{TimeBase::Base_8T,  static_cast <TickLength_t> (16)},
	{TimeBase::Base_16,  static_cast <TickLength_t> (12)},
	{TimeBase::Base_16T, static_cast <TickLength_t> (8)},
	{TimeBase::Base_32,  static_cast <TickLength_t> (6)},
	{TimeBase::Base_32T, static_cast <TickLength_t> (4)},
};

TickLength_t Pattern::getTicksPerStep (void) const
{
	return timeBaseToTicksPerStep[_patternData->timeBase];
}

Pattern::Pattern (int32_t id, std::string pName, uint8_t direction, TimeBase time, uint8_t bars, bool isWithData, PatternManager* patternMgr)
{
	_patternManager = patternMgr;
	_patternData = new (PatternData);
	*_patternData = { 0 };

	_patternData->numBars = bars;
	_patternData->timeBase = time;
	_patternData->patternName = pName;
	_patternData->patternDispName = pName;
	_patternData->UsedByCount = 0;
	_patternData->patternLastStepId = (bars * MAX_STEPS_IN_PATTERN_BAR) - 1;
	_patternData->id = id;
	_patternData->_barLoopOn = false;
	_patternData->_barLoopStartId = -1;
	_patternData->_barLoopEndId = -1;

	editStepId = 0;
	playStepId = 0;//start at first step, when playing
	editStep = nullptr;
	playStep = nullptr;

	for (uint16_t i = 0; i < _patternData->numBars; i++)
	{
		if (isWithData)
			_patternData->barList.emplace (i, Bar (this, i, false, 0, false, PatternDirection::forward, CreateStepWithRandomdata (_NumOfStepsPerBar, (i * _NumOfStepsPerBar))));
		else
			_patternData->barList.emplace (i, Bar (this, i, false, 0, false, PatternDirection::forward, CreateEmptyStepdata (_NumOfStepsPerBar, 0)));//TODO why step position is 0
	}

	_patternData->patternLastStepId = _patternData->numBars * _NumOfStepsPerBar;
}
Pattern::Pattern (PatternData& patternData, std::list<BarData> *barList, std::list<std::list<StepData>> *StepDataList, PatternManager* patternMgr)
{
	_patternManager = patternMgr;
	_patternData = new (PatternData);
	*_patternData = { 0 };

	_patternData->id = patternData.id;
	_patternData->numBars = patternData.numBars;
	_patternData->timeBase = patternData.timeBase;
	_patternData->patternName = patternData.patternName;
	_patternData->patternDispName = patternData.patternDispName;
	_patternData->UsedByCount = patternData.UsedByCount;
	_patternData->usedByList = patternData.usedByList;
	_patternData->patternLastStepId = patternData.patternLastStepId;
	_patternData->_barLoopEndId = patternData._barLoopEndId;
	_patternData->_barLoopOn = patternData._barLoopOn;
	_patternData->_barLoopStartId = patternData._barLoopStartId;

	editStepId = 0;
	playStepId = 0;//start at first step, when playing
	editStep = nullptr;
	playStep = nullptr;

	auto Stepit = StepDataList->begin ();
	for (auto it = barList->begin (); it != barList->end (); ++it)
	{
		_patternData->barList.emplace (it->BarId, Bar (this, it->BarId, it->barTransposeDefeat, it->barRepeatCount, it->gBarSyncOn, it->direction, *Stepit));
		++Stepit;//TODO why is bar list updation depending on StepDataList->Add info at start of function
		if (Stepit == StepDataList->end ())
		{
			break;
		}
	}
}
Pattern::Pattern (const Pattern& source)
{
	_patternManager = source._patternManager;
	_patternData = new (PatternData);
	*_patternData = { 0 };

	_patternData->id = source._patternData->id;
	_patternData->numBars = source._patternData->numBars;
	_patternData->timeBase = source._patternData->timeBase;
	_patternData->patternName = source._patternData->patternName;
	_patternData->patternDispName = source._patternData->patternDispName;
	_patternData->UsedByCount = source._patternData->UsedByCount;
	_patternData->patternLastStepId = source._patternData->patternLastStepId;
	_patternData->_barLoopEndId = source._patternData->_barLoopEndId;
	_patternData->_barLoopOn = source._patternData->_barLoopOn;
	_patternData->_barLoopStartId = source._patternData->_barLoopStartId;
	if (_patternData->UsedByCount)
		_patternData->usedByList = source._patternData->usedByList;

	this->_patternData->barList.clear ();
	for (auto i = source._patternData->barList.begin(); i != source._patternData->barList.end(); ++i)
	{
		this->_patternData->barList.insert (*i);
	}

	//set edit step
	this->editStepId = source.editStepId;
	uint16_t editBarId = this->editStepId / _NumOfStepsPerBar;
	auto editBar = this->_patternData->barList.find (editBarId);
	if (editBar != this->_patternData->barList.end())
	{
		auto it = editBar->second._BarData->stepList.find (this->editStepId);
		{
			if (it != editBar->second._BarData->stepList.end())
			{
				this->editStep = &(it->second);
			}
			else
			{
				DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "WARN : Unable to find edit step " + String (this->editStepId));
			}
		}
	}
	else
	{
		DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "WARN : Unable to find edit bar " + String (editBarId));
	}


	//set play step
	this->playStepId = source.playStepId;
	uint16_t playBarId = this->playStepId / _NumOfStepsPerBar;
	auto playBar = this->_patternData->barList.find (playBarId);
	if (playBar != this->_patternData->barList.end())
	{
		auto it = playBar->second._BarData->stepList.find (this->playStepId);
		{
			if (it != playBar->second._BarData->stepList.end())
			{
				this->playStep = &(it->second);
			}
			else
			{
				DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "WARN : Unable to find play step " + String (this->playStepId));
			}
		}
	}
	else
	{
		DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "WARN : Unable to find play bar " + String (playBarId));
	}
}
void Pattern::UpdatePattern(PatternData& patternData, std::list<BarData>* barList, std::list<std::list<StepData>>* StepDataList)
{
	// Clear existing bar list
	_patternData->barList.clear();

	_patternData->numBars = patternData.numBars;
	_patternData->timeBase = patternData.timeBase;
	_patternData->patternName = patternData.patternName;
	_patternData->patternDispName = patternData.patternDispName;
	_patternData->UsedByCount = patternData.UsedByCount;
	_patternData->usedByList = patternData.usedByList;
	_patternData->patternLastStepId = patternData.patternLastStepId;
	_patternData->_barLoopEndId = patternData._barLoopEndId;
	_patternData->_barLoopOn = patternData._barLoopOn;
	_patternData->_barLoopStartId = patternData._barLoopStartId;

	//****** No change on play/edit - this FUNCTION is mainly used for UNDO, could be called during play ****
	//editStepId, playStepId, editStep, playStep

	auto Stepit = StepDataList->begin();
	for (auto it = barList->begin(); it != barList->end(); ++it)
	{
		_patternData->barList.emplace(it->BarId, Bar(this, it->BarId, it->barTransposeDefeat, it->barRepeatCount, it->gBarSyncOn, it->direction, *Stepit));
		++Stepit;
		if (Stepit == StepDataList->end())
		{
			break;
		}
	}
}

std::list<StepData> Pattern::CreateStepWithRandomdata (uint8_t stepCount, uint16_t StartPos)
{
	std::list<StepData> StepDataList;
	for (uint16_t Id = StartPos; Id < (stepCount + StartPos); ++Id)
	{
		StepData stepData = { 0 };
		stepData.stepId = Id;
		stepData.nodeCount = 16;// Default/Max Node? : TODO
		stepData.enable = true;
		stepData.skipStatus = false;
		stepData.transposeDefeatStatus = false;
		stepData.nodeList.clear ();
		// Create random data

		for (uint16_t nodeId = 0; nodeId < stepData.nodeCount; ++nodeId)
		{
			NodeData nodeData = { 0 };
			srand ((unsigned int)time (NULL) + nodeId);
			nodeData.note = (rand () % 127);
			nodeData.velocity = 80;// (rand () % 255);
			nodeData.lenInTicks = (rand () % 15);
			nodeData.offset = (rand () % 15);
			nodeData.lenInTicks = 15;//full length by default
			stepData.nodeList[nodeData.note][nodeData.offset] = nodeData;
		}
		StepDataList.push_back (stepData);
	}
	return StepDataList;
}

std::list<StepData> Pattern::CreateEmptyStepdata (uint8_t stepCount, uint16_t StartPos)
{
	std::list<StepData> StepDataList;
	StepData stepData = { 0 };
	NodeData nodeData = { 0 };

	// Don't create nodes automatically. Let user add it.
	/*
	nodeData.note = 255; //(uint8_t)_patternManager->engine.settingsPatternCnfg->_SettingsPatternCnfgData.patternDefaultNote;
	nodeData.velocity = 38;//range 0 - 127, default set to 30% of max
	nodeData.lenInSteps = 0;//0 steps;
	nodeData.lenInTicks = 15;//full length by default
	nodeData.delay = 0;//0 - 95 ticks
	*/

	// All step gates will be disabled by default.
	// When usera adds a node, that step's gate is auto-enabled by UI
	// UI also provides ability to independently enable/disable gate
	stepData.enable = true;
	stepData.skipStatus = false;
	stepData.transposeDefeatStatus = false;

	for (uint16_t Id = StartPos; Id < (stepCount + StartPos); ++Id)
	{
		stepData.stepId = Id;
		stepData.nodeCount = 0;
		stepData.nodeList.clear ();
		//stepData.nodeList.insert ({ nodeData.note, nodeData });
		StepDataList.push_back (stepData);
	}
	return StepDataList;
}

bool Pattern::PatternGetBarDataList (ClientPatternData* clientPatternData)
{
	ClienPatterntBarData clientBarData = { 0 };

	for (auto barIt = _patternData->barList.begin (); barIt != _patternData->barList.end (); ++barIt)
	{
		clientBarData = { 0 };
		clientBarData.StepDataList.clear ();
		clientBarData.BarId = barIt->second._BarData->BarId;
		clientBarData.stepCount = barIt->second._BarData->stepCount;
		clientBarData.barRepeatCount = barIt->second._BarData->barRepeatCount;
		clientBarData.barTransposeDefeat = barIt->second._BarData->barTransposeDefeat;
		clientBarData.gBarSyncOn = barIt->second._BarData->gBarSyncOn;
		clientBarData.direction = static_cast <uint8_t> (barIt->second._BarData->direction);
		barIt->second.GetStepDataList (&clientBarData.StepDataList);
		clientPatternData->BarDataList.insert ({ static_cast<uint8_t>(clientBarData.BarId), clientBarData });
	}
	return false;
}

std::list<ClienPatterntBarData> Pattern::PatternGetBarData ()
{
	std::list<ClienPatterntBarData> clientBarDataList;
	ClienPatterntBarData clientBarData = { 0 };

	for (auto barIt = _patternData->barList.begin (); barIt != _patternData->barList.end (); ++barIt)
	{
		clientBarData = { 0 };
		clientBarData.StepDataList.clear ();
		clientBarData.BarId = barIt->second._BarData->BarId;
		clientBarData.stepCount = barIt->second._BarData->stepCount;
		clientBarData.barRepeatCount = barIt->second._BarData->barRepeatCount;
		clientBarData.barTransposeDefeat = barIt->second._BarData->barTransposeDefeat;
		clientBarData.gBarSyncOn = barIt->second._BarData->gBarSyncOn;

		std::list<ClientPatternStepData> _stepData = PatternGetStepData (barIt->second._BarData->BarId);
		uint8_t StepInBarPosition = 0;
		for (auto& StepIt : _stepData)
		{
			clientBarData.StepDataList.insert ({ StepInBarPosition, StepIt });
			StepInBarPosition++;
		}
		clientBarDataList.push_back (clientBarData);
	}
	return clientBarDataList;
}

std::list<ClientPatternStepData> Pattern::PatternGetStepData (uint16_t barId)
{
	std::list<ClientPatternStepData> ClientPatternStepDataList;

	auto bar = _patternData->barList.find (barId);
	if (bar != _patternData->barList.end())
	{
		return (bar->second.GetStepData());
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR : unable to locate requested bar");
		return (ClientPatternStepDataList);
	}
}

std::vector <StepDataUpdateStatus> Pattern::PatternSetStepData (uint16_t barId, uint16_t stepId, ClientPatternStepData stepData)
{
	std::vector <StepDataUpdateStatus> ret;

	auto bar = _patternData->barList.find (barId);
	if (bar != _patternData->barList.end())
	{
		ret = bar->second.BarSetStepData (stepData.stepId, stepData);
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR : unable to locate requested bar");
	}
	return ret;
}

bool Pattern::PatternAddNodeData (uint16_t barId, uint16_t stepId, ClientPatternNodeData nodeData)
{
	auto bar = _patternData->barList.find (barId);
	if (bar != _patternData->barList.end())
	{
		return bar->second.BarUpdateStepNodeData (stepId, nodeData);
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + " ERR : unable to locate requested bar");
		return false;
	}
}

bool Pattern::PatternAddNodeData (uint16_t barId, std::map<ClientPatternNodeData, std::list<uint8_t>> stepMap)
{
	auto bar = _patternData->barList.find (barId);
	if (bar != _patternData->barList.end())
	{
		return bar->second.BarUpdateStepNodeData (stepMap);
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR : unable to locate requested bar");
		return false;
	}
}

bool Pattern::PatternDelNodeData (uint16_t barId, uint16_t stepId, uint16_t nodeId)
{
	auto bar = _patternData->barList.find (barId);
	if (bar != _patternData->barList.end())
	{
		return bar->second.BarDelStepNodeData ( (uint8_t)stepId, nodeId);
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + " ERR : unable to locate requested bar");
		return false;
	}
}

std::map<int8_t, BarDataUpdateStatus> Pattern::PatternSetBarDataList(ClientPatternData* clientPatternData)
{
	std::map<int8_t, BarDataUpdateStatus> ret;

	for (auto barIt = _patternData->barList.begin(); barIt != _patternData->barList.end(); ++barIt)
	{
		uint8_t destBarId = barIt->second._BarData->BarId;
		if (clientPatternData->BarDataList[destBarId].BarId == destBarId)
		{
			std::map <int16_t, StepDataUpdateStatus> stepData;
			BarDataUpdateShallowStatus barOnlyData;
			BarDataUpdateStatus totalBarData;

			barOnlyData = barIt->second.SetBarData(clientPatternData->BarDataList[destBarId]);
			stepData = barIt->second.BarSetStepDataList(&(clientPatternData->BarDataList[destBarId].StepDataList));

			//only 1 bar
			totalBarData.barData = barOnlyData;
			totalBarData.stepData = stepData;

			ret.emplace( destBarId, totalBarData );
		}
	}
	return ret;
}

#if 0
std::tuple<int8_t, BarDataUpdateStatus> Pattern::PatternSetBarDataList(ClientPatternData& clientPatternData, PatternDataUpdateLocation location)
{
	std::tuple<int8_t, BarDataUpdateStatus> ret;

	auto barIter = _patternData->barList.find(location.barId);
	if (barIter != _patternData->barList.end())
	{
		std::map <int16_t, StepDataUpdateStatus> stepData;
		BarDataUpdateShallowStatus barOnlyData;
		BarDataUpdateStatus totalBarData;

		auto uiBarIter = clientPatternData.BarDataList.find(location.barId);
		if (uiBarIter != clientPatternData.BarDataList.end())
		{
			barOnlyData = barIter->second.SetBarData(uiBarIter->second);

			stepData = barIter->second.BarSetStepDataList(&(uiBarIter->second.StepDataList));

			//only 1 bar
			totalBarData.barData = barOnlyData;
			totalBarData.stepData = stepData;

			ret = std::make_tuple(location.barId, totalBarData);
		}
	}
	return ret;
}
#endif

BarDataUpdateShallowStatus Pattern::PatternSetBarData (uint16_t barId, ClienPatterntBarData barData)
{
	BarDataUpdateShallowStatus ret = { false, false, false, false };

	auto bar = _patternData->barList.find (barId);
	if (bar != _patternData->barList.end())
	{
		ret = bar->second.SetBarData (barData);
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR : unable to locate requested bar");
	}
	return ret;
}

uint16_t Pattern::AddBar (bool copyAndCreate, uint16_t fromBarId)
{
	StepData stepData = {};
	std::list<StepData> StepDataList;

	if (copyAndCreate)
	{
		auto bar = _patternData->barList.find (fromBarId);
		if (bar != _patternData->barList.end())
		{
			for (auto stepIt = bar->second._BarData->stepList.begin (); stepIt != bar->second._BarData->stepList.end (); stepIt)
			{
				stepData = *(stepIt->second._stepData);
				stepData.nodeList = stepIt->second._stepData->nodeList;
				StepDataList.push_back (stepData);
			}
			++(_patternData->numBars);
			_patternData->barList.emplace (_patternData->numBars, Bar (this, _patternData->numBars, bar->second._BarData->barTransposeDefeat, bar->second._BarData->barRepeatCount, bar->second._BarData->gBarSyncOn, bar->second._BarData->direction, StepDataList));
		}
		else
		{
			DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "ERR : Unable to locate source bar");
		}
	}
	else
	{
		_patternData->barList.emplace (_patternData->numBars, Bar (this, _patternData->numBars, false, 0, false, PatternDirection::forward, CreateEmptyStepdata (_NumOfStepsPerBar, (_patternData->numBars * _NumOfStepsPerBar))));
		_patternData->numBars++;
	}
	return _patternData->numBars;
}

int16_t Pattern::addBars (int16_t numBarsToAdd)
{
	int16_t numBars = 0;
	if (numBarsToAdd + _patternData->numBars > MAX_NUM_OF_BARS_IN_PATTERN)
	{
		numBarsToAdd = (numBarsToAdd + _patternData->numBars) - MAX_NUM_OF_BARS_IN_PATTERN;
		DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "WARN num bars to add, truncated to " + String (numBarsToAdd));
	}

	for (auto i = 0; i < numBarsToAdd; ++i)
	{
		numBars = AddBar (false, 0);//second arg has no effect
	}

	_patternData->patternLastStepId = (numBars * MAX_STEPS_IN_PATTERN_BAR) - 1;

	_patternManager->engine.sequenceManager->updateSequence(PatternChangeParameter::numBars, numBars, _patternData->patternName);

	return numBars;
}

uint16_t Pattern::insertBar (uint16_t position)
{
	if (position < _patternData->numBars)
	{
		auto barIter = _patternData->barList.find (position);

		if (barIter == _patternData->barList.end())
		{
			_patternData->barList.emplace(barIter->first, Bar(this, _patternData->numBars, false, 0, false, PatternDirection::forward, CreateEmptyStepdata(_NumOfStepsPerBar, (barIter->second._BarData->BarId * _NumOfStepsPerBar))));
		}
		else //position already occupied
		{
			auto tmpBar = barIter->second;
			auto tmpPos = barIter->first;
			auto tmpBarId = barIter->second._BarData->BarId;

			//remove current bar
			_patternData->barList.erase(barIter);

			//insert new bar
			_patternData->barList.emplace(tmpPos, Bar(this, _patternData->numBars, false, 0, false, PatternDirection::forward, CreateEmptyStepdata(_NumOfStepsPerBar, (tmpBarId * _NumOfStepsPerBar))));

			//re-add removed bar
			_patternData->barList.emplace(tmpPos, tmpBar);

		}
		_patternData->numBars++;
		reAssignSequentialIdToBars();
		reAssignSequentialIdToSteps();
	}
	else
	{
		//Limit to 16 bars max
		if (position >= MAX_NUM_OF_BARS_IN_PATTERN)
		{
			position = MAX_NUM_OF_BARS_IN_PATTERN - 1;
		}

		int numOfNewBarsToAppend = position - (_patternData->numBars - 1);

		//create new bars and append at end
		for (int count = 0; count < numOfNewBarsToAppend; ++count)
		{
			_patternData->numBars++;
			_patternData->barList.emplace (_patternData->numBars, Bar (this, _patternData->numBars, false, 0, false, PatternDirection::forward, CreateEmptyStepdata (_NumOfStepsPerBar, (_patternData->numBars * _NumOfStepsPerBar))));
		}

		reAssignSequentialIdToBars();
		reAssignSequentialIdToSteps();
	}
	return _patternData->numBars;
}

bool Pattern::RemoveBar (uint16_t barId)
{
	auto barIt = _patternData->barList.find (barId);

	if (barIt != _patternData->barList.end())
	{
		_patternData->barList.erase (barIt);
		_patternData->numBars--;
		reAssignSequentialIdToBars ();
		reAssignSequentialIdToSteps();

		return true;
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR : Unable top locate the bar to delete");
	}
	return false;
}

void Pattern::reAssignSequentialIdToBars()
{
	uint16_t _count = 0;
	std::multimap<uint16_t, Bar> newBarList;

	for (auto& barPair : _patternData->barList)
	{
		barPair.second._BarData->BarId = static_cast<uint8_t>(_count);
		newBarList.emplace(_count, std::move(barPair.second));
		++_count;
	}
	_patternData->barList = std::move(newBarList);
}

void Pattern::reAssignSequentialIdToSteps()
{
	uint16_t _count = 0;

	for (auto& barPair : _patternData->barList)
	{
		std::multimap<uint16_t, Step> newStepList;

		for (auto& stepPair : barPair.second._BarData->stepList)
		{
			stepPair.second._stepData->stepId = _count;
			newStepList.emplace(_count, std::move(stepPair.second));
			++_count;
		}
		barPair.second._BarData->stepList = std::move(newStepList);
	}
}

//Single bar copy
//Destination bar will be overwritten
//If Destination beyond current last bar, multiple new bars will be created, till destBarId is reached.
bool Pattern::CopyBar (uint16_t srcBarId, uint16_t destBarId)
{
	std::vector<StepData> StepDataList;

	//over-write existing destination bar
	if (destBarId < _patternData->numBars)
	{
		auto barSrcIter = _patternData->barList.find (srcBarId);
		auto barDestIter = _patternData->barList.find (destBarId);

		//Overwrite destination bar with src bar contents
		if ( (barSrcIter != _patternData->barList.end()) && (barDestIter != _patternData->barList.end()))
		{
			auto stepIterSrc = barSrcIter->second._BarData->stepList.begin ();
			auto stepIterDest = barDestIter->second._BarData->stepList.begin ();

			barDestIter->second._BarData->BarId = barSrcIter->second._BarData->BarId;
			barDestIter->second._BarData->barRepeatCount = barSrcIter->second._BarData->barRepeatCount;
			barDestIter->second._BarData->barTransposeDefeat = barSrcIter->second._BarData->barTransposeDefeat;
			barDestIter->second._BarData->gBarSyncOn = barSrcIter->second._BarData->gBarSyncOn;

			auto srcStepEnd = barSrcIter->second._BarData->stepList.end();
			auto destStepEnd = barDestIter->second._BarData->stepList.end();
			for ( ; (stepIterSrc != srcStepEnd) && (stepIterDest != destStepEnd); ++stepIterSrc, ++stepIterDest)
			{
				stepIterDest->second._stepData->auxList    = stepIterSrc->second._stepData->auxList;
				stepIterDest->second._stepData->enable = stepIterSrc->second._stepData->enable;
				stepIterDest->second._stepData->nodeCount  = stepIterSrc->second._stepData->nodeCount;
				stepIterDest->second._stepData->nodeList   = stepIterSrc->second._stepData->nodeList;
				stepIterDest->second._stepData->skipStatus = stepIterSrc->second._stepData->skipStatus;
				stepIterDest->second._stepData->stepId     = stepIterSrc->second._stepData->stepId;
				stepIterDest->second._stepData->transposeDefeatStatus = stepIterSrc->second._stepData->transposeDefeatStatus;
			}

			reAssignSequentialIdToBars ();
			reAssignSequentialIdToSteps ();
		}
	}//create new bars and append at end
	else
	{
		//Limit to 16 bars max
		if (destBarId >= MAX_NUM_OF_BARS_IN_PATTERN)
		{
			destBarId = MAX_NUM_OF_BARS_IN_PATTERN - 1;
		}

		int numOfNewBarsToAppend = destBarId - (_patternData->numBars - 1);

		//get the source bar
		auto srcBarIter = _patternData->barList.find (srcBarId);

		if (srcBarIter != _patternData->barList.end())
		{
			auto &tmpBar = srcBarIter->second;

			for (int count = 0; count < numOfNewBarsToAppend; ++count)
			{
				_patternData->numBars++;
				_patternData->barList.emplace (_patternData->numBars, tmpBar);
			}

			reAssignSequentialIdToBars();
			reAssignSequentialIdToSteps();
		}
		else
		{
			DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR : Copy bar unable to locate src bar");
		}
	}

	return true;
}

std::list<StepData> Pattern::CopyClientStepDataToStepData (std::list<ClientPatternStepData> clientPatternStepData)
{
	NodeData nodeListData;
	StepData stepData;
	std::list<StepData> returnStepDataList;
	returnStepDataList = clientPatternStepData;
	return returnStepDataList;
}
bool Pattern::InsertStep (uint16_t BarId, uint8_t StepCount, uint8_t InsertAt, std::list<ClientPatternStepData> ToStepDataList)
{
	std::list<StepData>  CopystepDataList;
	std::list<StepData> ReturnStepDataList;
	uint16_t barIdToAdd = BarId;

	uint8_t stepCount = (StepCount ? StepCount : _NumOfStepsPerBar);
	uint8_t insertAt = (InsertAt ? InsertAt : 1);

	if (!ToStepDataList.empty ())
		CopystepDataList = CopyClientStepDataToStepData (ToStepDataList);
	else
		CopystepDataList = CreateEmptyStepdata (stepCount, insertAt);

	auto barIt = _patternData->barList.find (barIdToAdd);

	if (barIt != _patternData->barList.end())
	{
		ReturnStepDataList = AddUpdateBarSteps (barIt->second, insertAt, CopystepDataList);

		if (!ReturnStepDataList.empty ())//excess steps to be moved to next Bar
		{
			auto barItNext = _patternData->barList.find (barIdToAdd + 1);
			uint8_t size = _NumOfStepsPerBar;
			if (ReturnStepDataList.size () > _NumOfStepsPerBar)
			{
				size = (uint8_t)ReturnStepDataList.size (); // Create for requested size or Max Bar size
			}
			if (barItNext == _patternData->barList.end ())
			{
				//update data and create new Bar
				CopystepDataList = CreateEmptyStepdata (size, 0);
				auto stepListIt = CopystepDataList.begin ();
				for (auto stepIt = ReturnStepDataList.begin (); stepIt != ReturnStepDataList.end (); stepIt)
				{
					*stepListIt = *stepIt;  // Copy available old data
					stepListIt->nodeList = stepIt->nodeList;
					stepListIt++;
				}
				++(_patternData->numBars);
				_patternData->barList.emplace (_patternData->numBars, Bar (this, _patternData->numBars, barIt->second._BarData->barTransposeDefeat, barIt->second._BarData->barRepeatCount, barIt->second._BarData->gBarSyncOn, barIt->second._BarData->direction, CopystepDataList));
			}
			else
			{
				// add remain in next bar
				insertAt = 1;
				barIdToAdd = barItNext->second._BarData->BarId;
				CopystepDataList = ReturnStepDataList;
			}
		}
	}
	else
	{
		DBG (String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR : Cannot locate bar");
	}
	return true;
}

std::list<StepData> Pattern::AddUpdateBarSteps (Bar Bar, uint8_t InsertAt, std::list<StepData>  stepDataList)
{
	return(Bar.AddStep (Bar._BarData->BarId, InsertAt, _NumOfStepsPerBar, stepDataList));
}

bool Pattern::UpdateUsedByList (bool isFillPattern, std::string SongName, std::string SceneName, std::string TrackName)
{
#if defined DISABLE_USED_BY_LIST
	auto it = std::find_if (_patternData->usedByList.begin (), _patternData->usedByList.end (), [&] (const UsedByData usedByData)
		{
			if ( (usedByData.isFillPattern == isFillPattern) &&
				 (usedByData.songName == SongName) &&
				 (usedByData.sceneName == SceneName) &&
				 (usedByData.trackName == TrackName))
				return (true);
			else
				return (false);
		}
	);

	if (it == _patternData->usedByList.end ())
	{
		UsedByData usedByData;
		usedByData.isFillPattern = isFillPattern;
		usedByData.songName = SongName;
		usedByData.sceneName = SceneName;
		usedByData.trackName = TrackName;
		_patternData->usedByList.push_back (usedByData);
		_patternData->UsedByCount++;
		return true;
	}
	//savePatternUsedByList (); // todo: check if it required
	return false;
#else
	return true;
#endif//DISABLE_USED_BY_LIST
}
bool Pattern::RemoveFromUsedByList (bool isFillPattern, std::string SongName, std::string SceneName, std::string TrackName)
{
#if defined DISABLE_USED_BY_LIST
	auto it = std::find_if (_patternData->usedByList.begin (), _patternData->usedByList.end (), [&](const UsedByData usedByData)
		{
			if ((usedByData.isFillPattern == isFillPattern) &&
				(usedByData.songName == SongName) &&
				(usedByData.sceneName == SceneName) &&
				(usedByData.trackName == TrackName))
				return (true);
			else
				return (false);
		});

	if (it != _patternData->usedByList.end ())
	{
		_patternData->usedByList.erase (it);
		_patternData->UsedByCount--;
	}
#endif//DISABLE_USED_BY_LIST
	return true;
}

void Pattern::setTimeBase (TimeBase val)
{
	_patternData->timeBase = val;
}


void Pattern::setName (std::string pName)
{
	name = pName;
}

//----- TODO clean after play manager
void Pattern::setTotalSteps (uint8_t val)
{
	//_patternData->stepCount = val;
}

void Pattern::setPlayStep (uint8_t val)
{
	val++; //TODO index 0 ?

	uint8_t playStepBarId = val / MAX_STEPS_IN_PATTERN_BAR;

	auto barIter = _patternData->barList.find (playStepBarId);

	if (barIter != _patternData->barList.end ())
	{
		auto it = barIter->second._BarData->stepList.find (val);
		if (it != barIter->second._BarData->stepList.end())
		{
				playStep = &(it->second);
				playStepId = val;
		}
		else
		{
			DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "ERR : Unable to set play step " + String (val));
		}

	}
	else
	{
		DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "ERR : Unable to locate play bar");
	}
}

void Pattern::setEditStep (uint8_t val)
{
	uint8_t editStepBarId = val / MAX_STEPS_IN_PATTERN_BAR;

	auto barIter = _patternData->barList.find (editStepBarId);

	if (barIter != _patternData->barList.end())
	{
		auto it = barIter->second._BarData->stepList.find (val);
		if (it != barIter->second._BarData->stepList.end())
		{
			editStep = &(it->second);
			editStepId = val;
		}
		else
		{
			DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "ERR : Unable to set edit step " + String(val));
		}
	}
	else
	{
		DBG (String (__FUNCTION__) + "::" + String (__LINE__) + "::" + "ERR : Unable to locate edit bar");
	}
}

TimeBase Pattern::getTimeBase (void) const
{
	return _patternData->timeBase;
}

std::vector <PatternDirection> Pattern::getPlayDirection (void) const
{
	std::vector <PatternDirection> barDirectionList;

	for (auto& bar : _patternData->barList)
	{
		barDirectionList.push_back(bar.second._BarData->direction);
	}
	return barDirectionList;
}

uint8_t Pattern::getTotalBars (void) const
{
	return _patternData->numBars;
}

std::string Pattern::getName (void) const
{
	return _patternData->patternName;
}

uint8_t Pattern::getEditStepId (void) const
{
	return editStepId;
}

uint8_t Pattern::getPlayStepId (void) const
{
	return playStepId;
}

int16_t Pattern::getTotalSteps (void) const
{
	return (getTotalBars() * MAX_STEPS_IN_PATTERN_BAR);;
}

int16_t Pattern::getLastStepId (void) const
{
	return _patternData->patternLastStepId;
}

int32_t Pattern::getId (void) const
{
	return _patternData->id;
}


void Pattern::setId (int32_t id)
{
	_patternData->id = id;
}

bool Pattern::getPatternBarLoopStatus (void)
{
	return _patternData->_barLoopOn;
}

int16_t Pattern::getPatternBarLoopEndBarId (void)
{
	return _patternData->_barLoopEndId;
}

int16_t Pattern::getPatternBarLoopStartBarId (void)
{
	return _patternData->_barLoopStartId;
}

void Pattern::savePatternUsedByList (void)
{
#if defined DISABLE_USED_BY_LIST
	PatternData patternData;
	_patternManager->engine.fileHandler->GetpatternDataHeader (_patternData->patternName, &patternData);

	patternData.UsedByCount = _patternData->UsedByCount;
	patternData.usedByList = _patternData->usedByList;

	_patternManager->engine.fileHandler->updatePatternInfo (_patternData->patternName, patternData);
#endif//DISABLE_USED_BY_LIST
}

std::string Pattern::PatternGetDispName(void)
{
	return _patternData->patternDispName;
}

/** Remove all nodes in the pattern
 */
void Pattern::clearPattern (void)
{
	for (auto &bar : _patternData->barList)
	{
		for (auto &step : bar.second._BarData->stepList)
		{
			step.second._stepData->nodeList.clear();
			step.second._stepData->auxList.clear();
		}
	}

	//update sequence events
	_patternManager->engine.sequenceManager->handlePatternClear(_patternData->patternName);
}
