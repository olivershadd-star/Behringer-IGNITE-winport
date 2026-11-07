#include "SequenceManager.h"
using namespace Ignite;

SequenceManager::SequenceManager(IParamChangeListener* listener, IgniteEngine& model) : engine(model)
{
	engine.updateModuleReadyStatus((moduleId_t)ModuleName::moduleSequenceManager, true);
}

void SequenceManager::init(void)
{
	this->engine.patternManager->addStepListener(this->engine.sequenceManager);
	this->engine.patternManager->addBarListener(this->engine.sequenceManager);
	this->engine.patternManager->addPatternListener(this->engine.sequenceManager);

}

void SequenceManager::initSequence(void)
{
	updateEventMapForActiveSong();
}

SequenceManager::~SequenceManager() {}
void SequenceManager::setParamList(moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist, bool isPlayMode) {}
std::vector<IgniteParamList> SequenceManager::getParamList(moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist) { std::vector<IgniteParamList> ret; return ret; }
void SequenceManager::SetCommandParam(moduleId_t moduleSrc, paramId_t param, bool isPlayMode) {}
void SequenceManager::getParam(moduleId_t moduleSrc, paramId_t param) {}

//STEP LEVEL
void SequenceManager::handleStepSkipChange(bool skip, PatternBarStepInfo stepAncestory)
{
	updateSequence(PatternChangeParameter::stepSkipState, skip, stepAncestory.patternName);
}
void SequenceManager::handleStepTieChange(bool tie, PatternBarStepInfo stepAncestory)
{
	updateSequence(PatternChangeParameter::stepTieState, tie, stepAncestory.patternName);
}
void SequenceManager::handleStepTransposeDefeatChange(bool transposeDefeat, PatternBarStepInfo stepAncestory)
{
	updateSequence(PatternChangeParameter::stepTransposeDefeatState, transposeDefeat, stepAncestory.patternName);
}
void SequenceManager::handleStepGateChange(bool stepGate, PatternBarStepInfo stepAncestory)
{
	updateSequence(PatternChangeParameter::stepOnState, stepGate, stepAncestory.patternName);
}

void SequenceManager::handleStepNoteChange(PatternBarStepInfo stepAncestory)
{
	updateSequence(PatternChangeParameter::addRemoveNote, 0, stepAncestory.patternName);
}

void SequenceManager::handleStepAuxChange(PatternBarStepInfo stepAncestory)
{
	updateSequence(PatternChangeParameter::addRemoveAux, 0, stepAncestory.patternName);
}

void SequenceManager::handleRecordChange(PatternBarStepInfo stepAncestory)
{
	updateSequence(PatternChangeParameter::addRecordEvents, 0, stepAncestory.patternName);
}
void SequenceManager::handlePatternClear (std::string patternName)
{
	updateSequence(PatternChangeParameter::addRecordEvents, 0, patternName);
}

//BAR LEVEL
void SequenceManager::handleBarRepeatChange(PatternBarInfo barAncestory)
{
	updateInfo(PatternChangeParameter::barRepeatCount, &barAncestory, barAncestory.patternName);
}

void SequenceManager::handleBarGbarSyncChange(PatternBarInfo barAncestory)
{
	updateInfo(PatternChangeParameter::barGbarSyncState, &barAncestory, barAncestory.patternName);
}

void SequenceManager::handleBarTransposeDefeatChange(bool transposeDefeat, PatternBarInfo barAncestory)
{
}

void SequenceManager::handleBarStepCountChange(uint8_t count, PatternBarInfo barAncestory)
{
	updateSequence(PatternChangeParameter::barStepCount, count, barAncestory.patternName);
}

//PATTERN LEVEL
void SequenceManager::handleBarCountChange(uint8_t count, std::string patternName)
{
	updateSequence(PatternChangeParameter::numBars, count, patternName);
}

void SequenceManager::handleDirectionChange(PatternDirection direction, std::string patternName)
{
	updateSequence(PatternChangeParameter::direction, static_cast<uint16_t>(direction), patternName);
}

void SequenceManager::handleLastStepChange(uint16_t stepId, std::string patternName)
{
	updateSequence(PatternChangeParameter::patternLastStep, stepId, patternName);
}

void SequenceManager::handleFirstStepChange(uint16_t stepId, std::string patternName)
{
	updateSequence(PatternChangeParameter::firstStep, stepId, patternName);
}

void SequenceManager::handleTimeBaseChange(TimeBase tb, std::string patternName)
{
	updateInfo(PatternChangeParameter::timeBase, &tb, patternName);
}

void SequenceManager::handleBarLoopChange(bool state, std::string patternName)
{
	updateInfo(PatternChangeParameter::barLoopStatus, &state, patternName);
}

void SequenceManager::handleBarLoopStartChange(uint8_t barId, std::string patternName)
{
	updateInfo(PatternChangeParameter::barLoopStart, &barId, patternName);
}

void SequenceManager::handleBarLoopEndChange(uint8_t barId, std::string patternName)
{
	updateInfo(PatternChangeParameter::barLoopEnd, &barId, patternName);
}

/*
* Get events at an offset, within a step.
*/
std::vector<MidiEvent> SequenceManager::getStepEventsAtOffset(std::string patternName, int8_t barId, uint16_t stepId, int16_t offset)
{
	std::vector<MidiEvent> ret;
	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		if (seq->second.updateInProgress.load(std::memory_order_acquire))
		{
			auto barIter = seq->second.events.clone.find(barId);
			if (barIter != seq->second.events.clone.end())
			{
				auto stepIter = barIter->second.find(stepId);
				if (stepIter != barIter->second.end())
				{
					auto eventIter = stepIter->second.find(offset);
					if (eventIter != stepIter->second.end())
					{
						ret = eventIter->second;
					}
				}
			}
		}
		else
		{
			auto barIter = seq->second.events.main.find(barId);
			if (barIter != seq->second.events.main.end())
			{
				auto stepIter = barIter->second.find(stepId);
				if (stepIter != barIter->second.end())
				{
					auto eventIter = stepIter->second.find(offset);
					if (eventIter != stepIter->second.end())
					{
						ret = eventIter->second;
					}
				}
			}
		}
	}

	return ret;
}

/*
* Get events at all offsets, within a step.
*/
OffsetMidiEventMap SequenceManager::getStepEvents(std::string patternName, int8_t barId, uint16_t stepId)
{
	OffsetMidiEventMap ret;
	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		if (seq->second.updateInProgress.load(std::memory_order_acquire))
		{
			auto barIter = seq->second.events.clone.find(barId);
			if (barIter != seq->second.events.clone.end())
			{
				auto stepIter = barIter->second.find(stepId);
				if (stepIter != barIter->second.end())
				{
					ret = stepIter->second;
				}
			}
		}
		else
		{
			auto barIter = seq->second.events.main.find(barId);
			if (barIter != seq->second.events.main.end())
			{
				auto stepIter = barIter->second.find(stepId);
				if (stepIter != barIter->second.end())
				{
					ret = stepIter->second;
				}
			}
		}
	}
	return ret;
}

/* This function returns the ascending steps order, ignoring thr current pattern direction.
 * This order is used in record
 */
std::vector<MidiEvent> SequenceManager::getLinearStepEventsAtOffset(std::string patternName, int8_t barId, uint16_t stepId, int16_t offset)
{
	std::vector<MidiEvent> ret;
	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		if (seq->second.updateInProgress.load(std::memory_order_acquire))
		{
			//if main is updating create a copy of clone
			auto barIter = seq->second.events.linearClone.find(barId);
			if (barIter != seq->second.events.linearClone.end())
			{
				auto stepIter = barIter->second.find(stepId);
				if (stepIter != barIter->second.end())
				{
					auto eventIter = stepIter->second.find(offset);
					if (eventIter != stepIter->second.end())
					{
						ret = eventIter->second;
					}
				}
			}
		}
		else
		{
			//if main is NOT updating create a copy of main
			auto barIter = seq->second.events.linearMain.find(barId);
			if (barIter != seq->second.events.linearMain.end())
			{
				auto stepIter = barIter->second.find(stepId);
				if (stepIter != barIter->second.end())
				{
					auto eventIter = stepIter->second.find(offset);
					if (eventIter != stepIter->second.end())
					{
						ret = eventIter->second;
					}
				}
			}
		}
	}

	return ret;
}


std::map <int8_t, StepOffsetMidiEventMap > SequenceManager::updateEventMap(std::map<int8_t, std::vector <int16_t>> barStepSeqMap, std::string patternName)
{
	std::map <int8_t, std::map <int16_t, StepInstance>> barStepsEventsMap;
	std::map <int8_t, StepOffsetMidiEventMap > eventMap;

	auto pattern = engine.patternManager->GetPattern(patternName);

	if ((pattern != nullptr) && (pattern->_patternData != nullptr))
	{
		//Iterate through the bars in the sequence
		for (auto& barStepSeqPair : barStepSeqMap)
		{
			auto barId = barStepSeqPair.first;
			//Fetch bar from pattern
			auto patternBarIter = pattern->_patternData->barList.find(barId);
			if (patternBarIter != pattern->_patternData->barList.end())
			{
				if (patternBarIter->second._BarData != nullptr)
				{
					auto patternBarData = patternBarIter->second._BarData;
					std::map <int16_t, StepInstance> stepEventListMap;//stepId, stepData

					//iterate through Step-Ids, in the sequence
					auto& stepIdSequence = barStepSeqPair.second;
					for (auto stepId : stepIdSequence)
					{
						//Fetch step data from pattern
						auto patternStepIter = patternBarData->stepList.find(stepId);
						if (patternStepIter != patternBarData->stepList.end())
						{
							// Get a copy of step from pattern.
							// 1. Avoid race condition(Pattern write/ read can happen concurrently),
							// 2. It will be modified by move semantics here
							// Enables pattern to be updated simultaneously, while play is happening
							// Pattern module to ensure multi-thread protection

							if (patternStepIter->second._stepData != nullptr)
							{
								auto patternStepDataCopy = patternStepIter->second._stepData;

								std::map<TickOffset_t, std::vector <EventInstance>> offsetEventsMap;

								for (auto& auxEvent : patternStepDataCopy->auxList)
								{
									if (auxEvent.enabled)
									{
										offsetEventsMap[auxEvent.offset].push_back(AuxToEvent(std::move(auxEvent)));
									}
								}

								for (auto& noteEvent : patternStepDataCopy->nodeList)
								{
									uint8_t nodecount = MAX_POLYPHONIC_NOTES;//TODO - limit may need to be used when play ?
									for (auto& nodeData : noteEvent.second)
									{
										offsetEventsMap[nodeData.second.offset].push_back(NoteToEvent(std::move(nodeData.second), pattern));
										--nodecount;
										if (nodecount <= 0)
											break;
									}
								}

								StepInstance stepInstance{ std::move(offsetEventsMap), patternStepDataCopy->tieStatus, patternStepDataCopy->enable, stepId };

								stepEventListMap.emplace(stepId, std::move(stepInstance));

							}//if(stepData != nullptr)

						}//if (patternStepIter != patternBarData->stepList.end())

					}//step loop - step sequence

					barStepsEventsMap.emplace(barId, std::move(stepEventListMap));

				}//if (barIter->second._BarData != nullptr)

			}//if (patternBarIter != pattern->_patternData->barList.end())

		}//bar loop - pattern bar

		eventMap = createEventMap(barStepsEventsMap, pattern);
	}

	return eventMap;
}

EventInstance SequenceManager::AuxToEvent(const Aux& aux)
{
	return EventInstance(PatternEventType::command, static_cast<MidiEventType>(aux.type), aux.data1, aux.data2, aux.offset, 0);
}

EventInstance SequenceManager::NoteToEvent(const NodeData& node, Pattern *pattern)
{
	return EventInstance(PatternEventType::note, MidiEventType::invalid, node.note, node.velocity, node.offset, static_cast<int16_t>(node.lenInSteps * pattern->getTicksPerStep() + node.lenInTicks));
}

#if 0
int16_t getTicksToEndOfBar(int16_t currentStepPos, int8_t currentOffset, int16_t stepsInBar)
{
	return (TICKS_PER_STEP - currentOffset + 1) + ((stepsInBar - currentStepPos + 1) * TICKS_PER_STEP);
}
#endif

std::map <int8_t, StepOffsetMidiEventMap > SequenceManager::createEventMap(const std::map <int8_t, std::map <int16_t, StepInstance>>& barStepEvents, Pattern* pattern)
{
	std::map <int8_t, StepOffsetMidiEventMap > ret; //bar, <step, offset, event>
	int16_t currentStepIndex = 0;

	// Iterate through each bar
	for (auto& barStepEventPair : barStepEvents)
	{
		auto& stepEventMap = barStepEventPair.second;

		// Iterate through each step.
		for (const auto& stepEventPair : stepEventMap)
		{
			const StepInstance& stepData = stepEventPair.second;

			for (const auto& tickEventListPair : stepData.tickEventListMap)
			{
				for (auto& event : tickEventListPair.second)
				{
					if (stepData.stepOn)
					{
						if (event.type == PatternEventType::command)
						{
							ret[barStepEventPair.first][stepEventPair.first][event.offset].push_back({ event.cmd, event.data1, event.data2 });
						}
						else if (event.type == PatternEventType::note)
						{
							//All notes of the step are swinged
							//Add any filters, if required, here
#if 0
							if ((swing != 0) && (currentStepIndex % 2))
							{
								event.offset = mapSwingToOffset(swing, event.offset);
							}
#endif
							ret[barStepEventPair.first][stepEventPair.first][event.offset].push_back({ MidiEventType::noteOn, event.data1, event.data2 });

							// Initial calculation for the note-off event tick
							NoteOffLocation noteOffPoint = findNoteOffLocation(barStepEvents, barStepEventPair.first, stepData.stepId, event.offset, event.length, pattern);

							// Adjust for tie by checking the first note of the next step
							if (stepData.tie)
							{
								NoteOnLocation tmp = findNextNoteOn(barStepEvents, barStepEventPair.first, stepData.stepId, pattern);
								noteOffPoint = findNoteOffLocation(barStepEvents, tmp.barId, tmp.stepId, tmp.offset, 1, pattern);
							}

							if (noteOffPoint.found)
							{
								ret[noteOffPoint.barId][noteOffPoint.stepId][noteOffPoint.offset].push_back({ MidiEventType::noteOff, event.data1, event.data2 });
							}
							else
							{
								//if length is too long or note off location could not be located
								// add note off at end of bar or end of seq
							}
						}
						else
						{
							DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR Unsupported event");
						}
					}//step mute check
				}//iterate event list
			}//iterate through ticks (0- 31)
			++currentStepIndex;
		}//step iterate
	}//bar iterate

	return ret;
}

/*
 *Swing is added to every second note of the step
 *If note already has an offset greater than 15 (possible with record)
 *Swing + Offset is limited to step boundary, so that note stays within the current step
 */
TickOffset_t SequenceManager::mapSwingToOffset(int8_t swing, TickOffset_t offsetWithinStep, Pattern *pattern)
{
	TickOffset_t swingedOffset = swing + offsetWithinStep;
	TickLength_t maxTicksPerStep = pattern->getTicksPerStep();

	if (swingedOffset >= maxTicksPerStep)
	{
		swingedOffset = maxTicksPerStep - 1;
	}

	return swingedOffset;
}

NoteOffLocation SequenceManager::findNoteOffLocation(const std::map<int8_t, std::map<int16_t, StepInstance>>& barStepEvents, int8_t barId, int16_t stepId, int16_t offset, int16_t len, Pattern* pattern)
{
	NoteOffLocation ret{ false, -1, - 1, -1};//found, bar, step, offset

	int16_t stepCount = 0;

	int16_t steps = 0;
	TickLength_t ticks = 0;

	TickLength_t maxTicksPerStep = pattern->getTicksPerStep();

	std::tie(steps, ticks) = convertToStepAndTicks(len, maxTicksPerStep);

	// Iterate over bars
	for (const auto& bar : barStepEvents)
	{
		if (bar.first < barId) continue;

		// Iterate over steps within a bar
		for (const auto& stepEvents : bar.second)
		{
			if (stepEvents.first < stepId) continue;

			// reach the note off step first, then check the offset+ticks
			if (stepCount < steps)
			{
				++stepCount;
				continue;
			}
			else
			{
				//withen step - location found
				if ( (offset + ticks) < maxTicksPerStep)
				{
					ret.found = true;
					ret.barId = bar.first;
					ret.stepId = stepEvents.first;
					ret.offset = offset + ticks;

					return ret;
				}

				// location is in the next step
				// remove ticks which are part of current step, in next step consider the overflow part of ticks
				// set offset 0,
				// it will satisfy the above if, in the next iteration
				ticks = (offset + ticks) - maxTicksPerStep;
				offset = 0;
			}
		}
	}
	return ret;
}

std::tuple<int16_t, TickLength_t> SequenceManager::convertToStepAndTicks(TickLength_t lengthInTicks, TickLength_t maxTicksPerStep)
{
	int16_t steps = lengthInTicks / maxTicksPerStep;

	TickLength_t ticks = lengthInTicks % maxTicksPerStep;

	return { steps, ticks };
}

// Function to find the next "note on" event's location.
// Search on steps after the current step
NoteOnLocation SequenceManager::findNextNoteOn(const std::map<int8_t, std::map<int16_t, StepInstance>>& barStepEvents, int8_t barId, int16_t stepId, Pattern *pattern)
{
	NoteOnLocation ret{ false, -1, -1, -1 };//found, bar, step, offset
	int16_t lowestOffset = pattern->getTicksPerStep();;

	// Iterate over bars
	for (const auto& bar : barStepEvents)
	{
		if (bar.first < barId) continue;

		// Iterate over steps within a bar
		for (const auto& step : bar.second)
		{
			if (step.first <= stepId) continue;

			const StepInstance& stepInstance = step.second;

			if (stepInstance.stepOn)
			{
				// Iterate over events within the step
				for (const auto& tickEventListPair : stepInstance.tickEventListMap)
				{
					for (const EventInstance& event : tickEventListPair.second)
					{
						// Check for 'note' type event
						if (event.type == PatternEventType::note )
						{
							//Add comment why we need 2 checks < max_ticks and == 0
							//And why not break after finding first occuurance, it is a ordered map now, so offset should be in sequence
							if (event.offset < lowestOffset)
							{
								lowestOffset = event.offset;

								ret.found = true;
								ret.barId = bar.first;
								ret.stepId = step.first;
								ret.offset = event.offset;
							}

							if (event.offset == 0) break;
						}
					}
				}
			}
		}
	}
	return ret; // Return false
}

int16_t SequenceManager::getFirstStepOfBar(int8_t barId, std::string patternName)
{
	int16_t stepId = -1;

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		auto barStepSeqPair = seq->second.order.main.find(barId);
		if (barStepSeqPair != seq->second.order.main.end())
		{
			if (barStepSeqPair->second.size() > 0)
			{
				stepId = barStepSeqPair->second[0];
			}
		}
	}
	return stepId;
}

int16_t SequenceManager::getLinearFirstStepOfBar(int8_t barId, std::string patternName)
{
	int16_t stepId = -1;

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		auto barStepSeqPair = seq->second.order.linearMain.find(barId);
		if (barStepSeqPair != seq->second.order.linearMain.end())
		{
			if (barStepSeqPair->second.size() > 0)
			{
				stepId = barStepSeqPair->second[0];
			}
		}
	}
	return stepId;
}

/* Gets the step at requested index,  returns bar id, step id, and total steps within the bar.
* if bar is not found return -1, -1, -1
*/
std::tuple<int8_t, int16_t, int16_t> SequenceManager::getNextStepOfBar(int8_t barId, int16_t stepIndex, std::string patternName)
{
	//DBG("INP : BarId : " + String(barId) + " : StepIndex : " + String(stepIndex));
	std::tuple<int8_t, int16_t, int16_t> retBarIdStepIdStepCount = std::make_tuple(static_cast<int8_t>(-1), static_cast<int16_t>(-1), static_cast<int16_t>(-1));

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		if (barId == -1)//starting condition
		{
			//get the first valid bar and step, of the sequence
			for (auto barStepSeqMapIter = seq->second.order.main.begin(); barStepSeqMapIter != seq->second.order.main.end(); ++barStepSeqMapIter)
			{
				if (barStepSeqMapIter->second.size() > 0)
				{
					std::get<0>(retBarIdStepIdStepCount) = barStepSeqMapIter->first;// barId
					std::get<1>(retBarIdStepIdStepCount) = *(barStepSeqMapIter->second.begin());//stepId
					std::get<2>(retBarIdStepIdStepCount) = static_cast<int16_t>(barStepSeqMapIter->second.size());
					break;
				}
			}
		}
		else
		{
			//New bar start
			if (stepIndex == -1)
			{
				auto barStepSeqPair = seq->second.order.main.find(barId);
				if (barStepSeqPair != seq->second.order.main.end())
				{
					std::get<0>(retBarIdStepIdStepCount) = barStepSeqPair->first;

					if (barStepSeqPair->second.size() > 0)
					{
						//get the first step
						std::get<1>(retBarIdStepIdStepCount) = *(barStepSeqPair->second.begin());//stepId
						std::get<2>(retBarIdStepIdStepCount) = static_cast<int16_t>(barStepSeqPair->second.size());
					}
				}
			}
			else
			{
				auto barStepSeqPair = seq->second.order.main.find(barId);
				if (barStepSeqPair != seq->second.order.main.end())
				{
					std::get<0>(retBarIdStepIdStepCount) = barStepSeqPair->first;

					if (barStepSeqPair->second.size() > 0)
					{
						//get the next step
						if (stepIndex < barStepSeqPair->second.size())
						{
							std::get<1>(retBarIdStepIdStepCount) = barStepSeqPair->second[stepIndex];//stepId
							std::get<2>(retBarIdStepIdStepCount) = static_cast<int16_t>(barStepSeqPair->second.size());
						}
					}
				}
			}
		}//else if (barId == -1)//starting condition
	}

	//DBG("OUT : BarId : " + String(std::get<0>(retBarIdStepIdStepCount)) + " : StepId: " + String(std::get<1>(retBarIdStepIdStepCount)) + " : Step Count : " + String(std::get<2>(retBarIdStepIdStepCount)));
	return retBarIdStepIdStepCount;
}

std::tuple<int8_t, int16_t, int16_t> SequenceManager::getLinearNextStepOfBar(int8_t barId, int16_t stepIndex, std::string patternName)
{
	std::tuple<int8_t, int16_t, int16_t> retBarIdStepIdStepCount = std::make_tuple(static_cast<int8_t>(-1), static_cast<int16_t>(-1), static_cast<int16_t>(-1));

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		if (barId == -1) //starting condition
		{
			//get the first valid bar and step, of the sequence
			for (auto barStepSeqMapIter = seq->second.order.main.begin(); barStepSeqMapIter != seq->second.order.main.end(); ++barStepSeqMapIter)
			{
				if (barStepSeqMapIter->second.size() > 0)
				{
					std::get<0>(retBarIdStepIdStepCount) = barStepSeqMapIter->first;// barId
					std::get<1>(retBarIdStepIdStepCount) = *(barStepSeqMapIter->second.begin());//stepId
					std::get<2>(retBarIdStepIdStepCount) = static_cast<int16_t>(barStepSeqMapIter->second.size());
					break;
				}
			}
		}
		else
		{
			auto barStepSeqPair = seq->second.order.linearMain.find(barId);
			if (barStepSeqPair != seq->second.order.linearMain.end())
			{
				std::get<0>(retBarIdStepIdStepCount) = barStepSeqPair->first;

				if (barStepSeqPair->second.size() > 0)
				{
					//get the next step
					if (stepIndex < barStepSeqPair->second.size())
					{
						std::get<1>(retBarIdStepIdStepCount) = barStepSeqPair->second[stepIndex];//stepId
					}
					std::get<2>(retBarIdStepIdStepCount) = static_cast<int16_t>(barStepSeqPair->second.size());
				}
			}
		}//else if ((barId == -1) || (stepId == -1))//starting condition
	}

	return retBarIdStepIdStepCount;
}

TimeBase SequenceManager::getPatternTimeBase(std::string patternName)
{
	TimeBase tb = TimeBase::Base_4;

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		tb = seq->second.patternInfo.tb;
	}

	return tb;
}

PatternInfo SequenceManager::getUpdatedInfo(std::string patternName)
{
	PatternInfo info;

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		info = seq->second.patternInfo;
	}

	return info;
}

void SequenceManager::updateInfo(PatternChangeParameter param, void* info, std::string patternName)
{
	auto pattern = engine.patternManager->GetPattern(patternName);

	if (pattern != nullptr)
	{
		auto seq = patternSequenceMap.find(patternName);
		if (seq != patternSequenceMap.end())
		{
			PatternInfo& patternInfo = seq->second.patternInfo;

			switch (param)
			{
				case PatternChangeParameter::timeBase:
					patternInfo.tb = *(reinterpret_cast<TimeBase*>(info));
				break;

				case PatternChangeParameter::barLoopStatus://PATTERN
					std::get <0>(patternInfo.barloop) = *(reinterpret_cast<bool*>(info));
					break;

				case PatternChangeParameter::barLoopStart://PATTERN
					std::get <1>(patternInfo.barloop).startBarId = *(reinterpret_cast<int8_t*>(info));
					break;

				case PatternChangeParameter::barLoopEnd://PATTERN
					std::get <1>(patternInfo.barloop).endBarId = *(reinterpret_cast<int8_t*>(info));
					break;

				case PatternChangeParameter::barRepeatCount://BAR
				{
					auto barInfo = *(reinterpret_cast<PatternBarInfo*>(info));

					auto bar = patternInfo.barInfoList.find(barInfo.barId);
					if (bar != patternInfo.barInfoList.end())
					{
						bar->second.repeatCount = barInfo.repeatCount;
					}
					break;
				}

				case PatternChangeParameter::barGbarSyncState://BAR
				{
					auto barInfo = *(reinterpret_cast<PatternBarInfo*>(info));

					auto bar = patternInfo.barInfoList.find(barInfo.barId);
					if (bar != patternInfo.barInfoList.end())
					{
						bar->second.gBarSyncState = barInfo.gBarSyncState;
					}
					break;
				}

				case PatternChangeParameter::numBars://BAR
				{
					auto barInfo = *(reinterpret_cast<PatternBarInfo*>(info));
					auto bar = patternInfo.barInfoList.find(barInfo.barId);
					if (bar == patternInfo.barInfoList.end())
					{
						patternInfo.barInfoList.emplace(barInfo.barId, barInfo);
					}
					break;
				}

				default:
					assert(0);
					break;
			}//switch

		}//if (seq != patternSequenceMap.end())

	}//if (pattern != nullptr)
}

void SequenceManager::updateSequence(PatternChangeParameter param, uint16_t val, std::string patternName)
{
	auto pattern = engine.patternManager->GetPattern(patternName);

	if (pattern != nullptr)
	{
		auto seq = patternSequenceMap.find(patternName);
		if (seq != patternSequenceMap.end())
		{
			SequenceOrder& sequenceOrder = seq->second.order;
			SequenceEvents& sequenceEvents = seq->second.events;
			int16_t& totalUnskippedSteps = seq->second.totalUnskippedSteps;
			std::atomic_bool& updateInProgress = seq->second.updateInProgress;
			std::mutex& seqUpdateMutex = seq->second.seqUpdateMutex;

			// This is the write thread (modified order or events)
			//
			// Any read thread will check the updateInProgress flag and use clone(old) data. So it will not block.
			// Read threads are high priority, as they are used while playing
			//
			// All read threads are required/desiged to use a copy of the data structure, rather than ref/pointer
			//
			// Both sequence order and eventMap are tighly coupled
			// Read threads should never use order from main and eventMap from Clone or vice versa
			//
			// Don't let multiple calls to this function, from diff threads, modify at the same time
			std::unique_lock<std::mutex> lock(seqUpdateMutex);//mutex is scope based, auto released, when it is out of scope

			sequenceOrder.clone = sequenceOrder.main;
			sequenceOrder.linearClone = sequenceOrder.linearMain;
			sequenceEvents.clone = sequenceEvents.main;

			// Main data is going to change from this point
			updateInProgress.store(true, std::memory_order_release);

			if (pattern->_patternData == nullptr)
			{
				DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR Seq not updated, pat data null " + patternName);
				return;
			}

			auto barDirections = pattern->getPlayDirection();//this will be a vector of bar directions
			//auto numBars = pattern->getTotalBars();
			auto patternLastStep = pattern->getLastStepId();
			//auto patternBarLoopOn = pattern->getPatternBarLoopStatus();
			//auto patternBarLoopStart = pattern->getPatternBarLoopStartBarId();
			//auto patternBarLoopEnd = pattern->getPatternBarLoopEndBarId();

			std::vector<std::vector<int16_t>> skippedStepsPerBar;
			std::vector<int16_t> stepsPerBar;
			//int totalProcessedSteps = 0;
			bool patternLastStepReached = false;

			for (const auto& bar : pattern->_patternData->barList)
			{
				if (bar.second._BarData == nullptr)
				{
					DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR Seq not updated, bar data null " + patternName);
					return;
				}
				std::vector <int16_t> skippedSteps;
				int stepCountPerBar = 16;// take from pattern, if considered as user input, in future
				int16_t stepCounter = 0;

				for (const auto& step : bar.second._BarData->stepList)
				{
					++stepCounter;
					if (stepCounter > stepCountPerBar)
					{
						break;
					}
					if (step.second.getStepId() >= patternLastStep)
					{
						patternLastStepReached = true;
						break;
					}
					if (step.second.getStepSkip() == true)
					{
						skippedSteps.push_back(step.second.getStepId());
					}
				}//step loop
				skippedStepsPerBar.push_back(skippedSteps);
				stepsPerBar.push_back(stepCounter);

				skippedSteps.clear();
				//stepCountPerBar = 0;

				if (patternLastStepReached)
				{
					break;
				}
			}//bar loop


			switch (param)
			{
			//Update info
			case PatternChangeParameter::numBars://PATTTERN
			{
				for (const auto& bar : pattern->_patternData->barList)
				{
					PatternBarInfo tmp;
					tmp.patternName = patternName;
					tmp.barId = bar.second._BarData->BarId;
					tmp.repeatCount = bar.second._BarData->barRepeatCount;
					tmp.gBarSyncState = bar.second._BarData->gBarSyncOn;

					updateInfo(PatternChangeParameter::numBars, &tmp, patternName);
				}
			}
			//FALL-THROUGH
			//Both order and event map update
			case PatternChangeParameter::initPattern://special case - song loading time
			case PatternChangeParameter::direction://PATTERN
			case PatternChangeParameter::patternLastStep://PATTERN
			case PatternChangeParameter::firstStep://PATTERN
			case PatternChangeParameter::barStepCount://BAR
			case PatternChangeParameter::stepSkipState://BAR
			{
				std::tie(sequenceOrder.main, totalUnskippedSteps) = generateStepSequence(skippedStepsPerBar, stepsPerBar, barDirections);;
				sequenceEvents.main = updateEventMap(sequenceOrder.main, patternName);

				//This is specifically used for record purpose
				//Currently we will maintain
				// 1. skipped steps
				// 2. last step
				// Based on user feed back, we can choose (change here) to ignore the above 2 and use the complete pattern
				std::vector<PatternDirection> allFowarddirections(stepsPerBar.size(), PatternDirection::forward);
				std::tie(sequenceOrder.linearMain, totalUnskippedSteps) = generateStepSequence(skippedStepsPerBar, stepsPerBar, allFowarddirections);
				sequenceEvents.linearMain = updateEventMap(sequenceOrder.linearMain, patternName);
				break;
			}


			case PatternChangeParameter::addRecordEvents://special case - record time
			{
				std::tie(sequenceOrder.main, totalUnskippedSteps) = generateStepSequence(skippedStepsPerBar, stepsPerBar, barDirections);
				sequenceEvents.main = updateEventMap(sequenceOrder.main, patternName);

				//This is specifically used for record purpose
				//Currently we will maintain
				// 1. skipped steps
				// 2. last step
				// Based on user feed back, we can choose (change here) to ignore the above 2 and use the complete pattern
				std::vector<PatternDirection> allFowarddirections(stepsPerBar.size(), PatternDirection::forward);
				std::tie(sequenceOrder.linearMain, totalUnskippedSteps) = generateStepSequence(skippedStepsPerBar, stepsPerBar, allFowarddirections);
				sequenceEvents.linearMain = updateEventMap(sequenceOrder.linearMain, patternName);
				break;
			}

				//Only event map update, order remains same
			case PatternChangeParameter::stepTieState://BAR, event list
			case PatternChangeParameter::stepOnState://STEP, event list
			case PatternChangeParameter::nodeOffset://NODE, event list
			case PatternChangeParameter::nodeLength://NODE, event list
			case PatternChangeParameter::addRemoveNote://STEP
			case PatternChangeParameter::addRemoveAux://STEP
				sequenceEvents.main = updateEventMap(sequenceOrder.main, patternName);

				sequenceEvents.linearMain = updateEventMap(sequenceOrder.linearMain, patternName);
				break;

				// There are changes in the playing order, but will be handled at play time
				// Will be very memory intensive when multiple loops and repeats are handled here.
				// Update the info, will use it during run time
			case PatternChangeParameter::barLoopStatus://PATTERN
			case PatternChangeParameter::barLoopStart://PATTERN
			case PatternChangeParameter::barLoopEnd://PATTERN
			case PatternChangeParameter::barRepeatCount://BAR
			case PatternChangeParameter::barGbarSyncState://BAR
			case PatternChangeParameter::timeBase://PATTERN
				break;

				//No changes in order or event-map - NOP
			case PatternChangeParameter::barTransposeDefeat://BAR
			case PatternChangeParameter::barTranspose://BAR
			case PatternChangeParameter::stepTransposeDefeatState://STEP
				break;

			default:
				DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "WARN Unknown pattern param type");
				break;

			}//switch PatternChangeParameter

			// Both order and event has been updated at this point
			// Update flag so that any new read thread, will start using the main(new) data
			updateInProgress.store(false, std::memory_order_release);

			// Release mutex, so that any waiting write threads(if any), can update the sequence
			//lock.unlock();//scope based mutex, auto released
		} /* seq != patternSequenceMap.end() */
	} /* pattern != nullptr*/
}

std::pair<std::map<int8_t, std::vector<int16_t>>, int16_t> SequenceManager::generateStepSequence(std::vector<std::vector<int16_t>>& skippedStepsPerBar,
	std::vector<int16_t>& stepsPerBar,
	std::vector<PatternDirection> directions )
{

	std::map<int8_t, std::vector<int16_t>> sequenceByBarExcludeSkipped;
	int16_t totalUnskippedSteps = 0;
	int8_t numBars = static_cast<int8_t>(stepsPerBar.size());

	//int16_t totalSteps = std::accumulate(stepsPerBar.begin(), stepsPerBar.end(), 0);

	// Populate the map with non-skipped steps
	for (int8_t barId = 0; barId < numBars; ++barId)
	{
		std::vector<int16_t> currentBarSteps;
		currentBarSteps.reserve(stepsPerBar[barId]);

		for (int16_t count = 0; count < stepsPerBar[barId]; ++count)
		{
			int16_t stepId = barId * 16 + count;
			if (std::find(skippedStepsPerBar[barId].begin(), skippedStepsPerBar[barId].end(), stepId) == skippedStepsPerBar[barId].end())
			{
				currentBarSteps.push_back(stepId);
				++totalUnskippedSteps;
			}
		}
		sequenceByBarExcludeSkipped[barId] = std::move(currentBarSteps);
	}

	// Apply the direction transformation at the bar level or the pattern level as requested.
	
	int i = 0;
	for (auto& barSeqPair : sequenceByBarExcludeSkipped)
	{
		barSeqPair.second = applyDirection(std::move(barSeqPair.second), directions[i]);
		++i;
	}
	
	return { sequenceByBarExcludeSkipped, totalUnskippedSteps };
}

std::vector<int16_t> SequenceManager::applyDirection(std::vector<int16_t>&& currentSequence, PatternDirection direction)
{
	std::vector<int16_t> sequence;
	sequence.reserve(currentSequence.size());

	switch (direction)
	{
	case PatternDirection::forward:
		sequence = currentSequence;
		break;

	case PatternDirection::reverseA:
		// Reverse sequence but ensure the first step of the first bar is the starting point
		std::reverse(currentSequence.begin()+1, currentSequence.end());
		sequence.assign(currentSequence.begin(), currentSequence.end());
		break;

	case PatternDirection::reverseB:
		std::reverse(currentSequence.begin(), currentSequence.end());
		sequence.assign(currentSequence.begin(), currentSequence.end());
		break;

	case PatternDirection::alternate:
		sequence.reserve(currentSequence.size() * 2);
		sequence.assign(currentSequence.begin(), currentSequence.end());
		sequence.insert(sequence.end(), currentSequence.rbegin(), currentSequence.rend());
		break;

	case PatternDirection::pendulum:
		sequence.reserve(currentSequence.size() * 2);
		sequence.assign(currentSequence.begin(), currentSequence.end());
		sequence.insert(sequence.end(), currentSequence.rbegin() + 1, currentSequence.rend()-1);
		break;

	case PatternDirection::random:
	{
		auto  seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(currentSequence.begin(), currentSequence.end(), std::mt19937(static_cast<unsigned int>(seed)));
		sequence = currentSequence;
		break;
	}

	case PatternDirection::brownian:
	{
		auto  seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 rGen(static_cast<unsigned int>(seed));

		std::uniform_int_distribution<int> moveDist(-1, 1);

		int16_t currentPosition = 0;
		auto totalSteps = currentSequence.size();
		for (auto i = 0; i < totalSteps; ++i)
		{
			sequence.push_back(currentSequence[currentPosition]);
			currentPosition += static_cast<int16_t>(moveDist(rGen));
			currentPosition = std::max(static_cast<int16_t> (0), static_cast<int16_t> (std::min(currentPosition, static_cast<int16_t> (totalSteps - 1))));
		}
		break;
	}

	case PatternDirection::eitherway:
	{
		auto  seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 rGen(static_cast<unsigned int>(seed));

		// choose only 2 directons - forward (1) or backward (0)
		std::uniform_int_distribution<int> eitherWayDist(0, 1);

		int16_t currentPosition = 0;
		auto totalSteps = currentSequence.size();
		for (auto i = 0; i < totalSteps; ++i)
		{
			sequence.push_back(currentSequence[currentPosition]);
			int move = eitherWayDist(rGen);
			currentPosition += (move == 0) ? -1 : 1;
			currentPosition = std::max(static_cast<int16_t> (0), static_cast<int16_t> (std::min(currentPosition, static_cast<int16_t> (totalSteps - 1))));
		}
		break;
	}

	default:
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR Invalid direction");
		break;
	}

	return sequence;
}

/*
* Find all patterns associated with the song
* Add them in the pattern (sequence event) list of sequence manager
*/
void SequenceManager::updateEventMapForActiveSong(void)
{
	std::unordered_set<std::string> nameList;

	if (engine.songManager->activeSong != nullptr)
	{
		if (engine.songManager->activeSong->_songData != nullptr)
		{
			const auto& sceneList = engine.songManager->activeSong->_songData->sceneList;

			for (const auto& scene : sceneList)
			{
				if (scene._sceneData != nullptr)
				{
					for (const auto& track : scene._sceneData->trackList)
					{
						auto pattern = track._trackData->mainPattern;
						if (pattern != nullptr)
						{
							auto name = pattern->getName();
							auto ret = nameList.insert(name);
							if (ret.second)//a new name
							{
								int16_t unSkippedSteps = 0;
								PatternInfo patInfo;
								std::tie (patInfo, unSkippedSteps) = extractPatternInfoAndUnskippedSteps(pattern);

								initSequence(name, patInfo, unSkippedSteps);
							}
						}

						pattern = track._trackData->fillPattern;
						if (pattern != nullptr)
						{
							auto name = pattern->getName();
							auto ret = nameList.insert(name);
							if (ret.second)//a new name
							{
								int16_t unSkippedSteps = 0;
								PatternInfo patInfo;
								std::tie(patInfo, unSkippedSteps) = extractPatternInfoAndUnskippedSteps(pattern);

								initSequence(name, patInfo, unSkippedSteps);
							}
						}
					}
				}
				else
				{
					DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR Null scene data, event list not updated");
				}
			}
		}
		else
		{
			DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR Null song data, event list not updated");
		}

	}
	else
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR No active song, event list not updated");
	}
}

void SequenceManager::initSequence(std::string patternName, PatternInfo info, int16_t unSkippedSteps)
{
	std::map <int8_t, StepOffsetMidiEventMap > mainEv, cloneEv, linearMainEv, linearCloneEv;
	SequenceEvents tmpEvents{ mainEv, cloneEv, linearMainEv, linearCloneEv };

	std::map<int8_t, std::vector <int16_t>> mainOrd, cloneOrd, linearMainOrd, linearCloneOrd;
	SequenceOrder tmpOrder{ mainOrd, cloneOrd, linearMainOrd, linearCloneOrd };

	patternSequenceMap.emplace(std::piecewise_construct, std::forward_as_tuple(patternName), std::forward_as_tuple(tmpOrder, tmpEvents, unSkippedSteps, info));

	updateSequence(PatternChangeParameter::initPattern, 0, patternName);
}

void SequenceManager::updateTrackPattern (Pattern* pattern)
{
	if (pattern != nullptr)
	{
		auto name = pattern->getName();

		int16_t unSkippedSteps = 0;
		PatternInfo patInfo;
		std::tie(patInfo, unSkippedSteps) = extractPatternInfoAndUnskippedSteps(pattern);

		initSequence(name, patInfo, unSkippedSteps);
	}
	else
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERR Inavlid pattern ptr");
		return;
	}
}

std::pair <PatternInfo, int16_t>  SequenceManager::extractPatternInfoAndUnskippedSteps(Pattern* pattern)
{
	auto blState = pattern->getPatternBarLoopStatus();
	auto blStart = pattern->getPatternBarLoopStartBarId();
	auto blEnd = pattern->getPatternBarLoopEndBarId();
	auto tb = pattern->getTimeBase();

	auto name = pattern->getName();

	BarLoopRange tmpBlRange{ static_cast<int8_t>(blStart), static_cast<int8_t>(blEnd) };

	int16_t unSkippedSteps = 0;

	std::map <int8_t, PatternBarInfo> tmpBarInfoMap;
	for (auto& bar : pattern->_patternData->barList)
	{
		PatternBarInfo tmpBarInfo{ name, static_cast<int8_t>(bar.first), bar.second._BarData->barRepeatCount, bar.second._BarData->gBarSyncOn };
		tmpBarInfoMap.emplace(static_cast<int8_t>(bar.first), tmpBarInfo);

		for (auto& step : bar.second._BarData->stepList)
		{
			if (step.second.getStepSkip() == false)
			{
				++unSkippedSteps;
			}
		}
	}

	PatternInfo tmp{ name, tb, std::make_tuple(blState, tmpBlRange),  tmpBarInfoMap };

	return { tmp, unSkippedSteps };
}

int16_t SequenceManager::getStepCountForFirstBar(std::string patternName)
{
	int16_t count = 0;

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		//get the first valid bar, of the sequence
		for (auto barStepSeqMapIter = seq->second.order.main.begin(); barStepSeqMapIter != seq->second.order.main.end(); ++barStepSeqMapIter)
		{
			if (barStepSeqMapIter->second.size() > 0)
			{
				count = static_cast<int16_t>(barStepSeqMapIter->second.size());
				break;
			}
		}
	}

	return count;
}

int16_t SequenceManager::getLinearStepCountForFirstBar(std::string patternName)
{
	int16_t count = 0;

	auto seq = patternSequenceMap.find(patternName);
	if (seq != patternSequenceMap.end())
	{
		//get the first valid bar, of the sequence
		for (auto barStepSeqMapIter = seq->second.order.linearMain.begin(); barStepSeqMapIter != seq->second.order.linearMain.end(); ++barStepSeqMapIter)
		{
			if (barStepSeqMapIter->second.size() > 0)
			{
				count = static_cast<int16_t>(barStepSeqMapIter->second.size());
				break;
			}
		}
	}

	return count;
}
