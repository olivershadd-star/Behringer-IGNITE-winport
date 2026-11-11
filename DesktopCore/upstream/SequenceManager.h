#pragma once
#include <stdint.h>
#include <string>
#include <mutex>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <random>
#include <algorithm>
#include <atomic>
#include <vector>
#include <tuple>
#include <utility>

#include "Firmware/Application/Model/ModelParams.h"
#include "common_defs/source/EngineDataStruct.h"
#include "IgniteEngine.h"

namespace Ignite
{
	// Define type aliases to simplify map declarations
	using MidiEventVector = std::vector<MidiEvent>;
	using OffsetMidiEventMap = std::map<int16_t, MidiEventVector>;
	using StepOffsetMidiEventMap = std::map<int16_t, OffsetMidiEventMap>;


	struct EventInstance
	{
		PatternEventType type;

		MidiEventType cmd; //populate for Command events only

		uint8_t data1;
		uint8_t data2;

		TickOffset_t offset;       // Offset relative to the start of the step (in ticks)

		TickLength_t length;       // For note events only - Total length in ticks (steps * ticksPerStep + lenInTicks) // max 95 * 192 + 192 = 18432

		EventInstance()
			: type(PatternEventType::note), cmd(MidiEventType::invalid), data1(0), data2(0), offset(0), length(0) {}

		EventInstance(PatternEventType type, MidiEventType cmd, uint8_t data1, uint8_t data2, TickOffset_t offset, TickLength_t length)
			: type(type), cmd(cmd), data1(data1), data2(data2), offset(offset), length(length) {}

		EventInstance(const EventInstance& other)
			: type(other.type), cmd(other.cmd), data1(other.data1), data2(other.data2), offset(other.offset), length(other.length) {}
	};

	struct StepInstance
	{
		std::map<int16_t, std::vector <EventInstance>> tickEventListMap;//tick, event
		bool tie;         // Indicates if the note is tied to the next
		bool stepOn;    // Indicates if the step is muted
		int16_t stepId;

		StepInstance()
			: tickEventListMap(), tie(false), stepOn(false), stepId(-1) {}

		StepInstance(std::map<int16_t, std::vector <EventInstance>> tickEventListMap, bool tie, bool stepOn, int16_t id)
			: tickEventListMap(tickEventListMap), tie(tie), stepOn(stepOn), stepId(id) {}

		StepInstance(const StepInstance& other)
			: tickEventListMap(other.tickEventListMap), tie(other.tie), stepOn(other.stepOn), stepId(other.stepId) {}
	};


	struct SequenceOrder
	{
		std::map<int8_t, std::vector <int16_t>> main;//bar id, step ids
		std::map<int8_t, std::vector <int16_t>> clone;//bar id, step ids

		std::map<int8_t, std::vector <int16_t>> linearMain;//bar id, step ids
		std::map<int8_t, std::vector <int16_t>> linearClone;//bar id, step ids

		SequenceOrder()
			: main(), clone(), linearMain(), linearClone() {}

		SequenceOrder(std::map<int8_t, std::vector <int16_t>> main, std::map<int8_t, std::vector <int16_t>> clone,
			std::map<int8_t, std::vector <int16_t>> linearMain, std::map<int8_t, std::vector <int16_t>> linearClone) :
			main(main), clone(clone), linearMain(linearMain), linearClone(linearClone) {}

		SequenceOrder(const SequenceOrder& other)
			: main(other.main), clone(other.clone), linearMain(other.linearMain), linearClone(other.linearClone) {}
	};

	struct SequenceEvents
	{
		std::map <int8_t, StepOffsetMidiEventMap > main;//barid, step id, offset, events
		std::map <int8_t, StepOffsetMidiEventMap > clone;//barid, step id, offset, events

		std::map <int8_t, StepOffsetMidiEventMap > linearMain;//barid, step id, offset, events
		std::map <int8_t, StepOffsetMidiEventMap > linearClone;//barid, step id, offset, events

		SequenceEvents()
			: main(), clone(), linearMain(), linearClone() {}

		SequenceEvents(std::map <int8_t, StepOffsetMidiEventMap > main, std::map <int8_t, StepOffsetMidiEventMap > clone,
			std::map <int8_t, StepOffsetMidiEventMap > linearMain, std::map <int8_t, StepOffsetMidiEventMap > linearClone) :
			main(main), clone(clone), linearMain(linearMain), linearClone(linearClone) {}

		SequenceEvents(const SequenceEvents& other) :
			main(other.main), clone(other.clone), linearMain(other.linearMain), linearClone(other.linearClone) {}
	};

	// Pattern data in the form of step sequence and event list
	// Changes are calculated & updated whenever pattern params change. (Saves lot of time in playback thread)
	// Write threads always act on the actual(use refrence/pointer  of) data structure
	// Read threads should take a copy of the data
	// All write threads should obtain mutex lock before making changes to order and/or events data
	struct SequenceData
	{
		std::atomic_bool updateInProgress{ false };
		SequenceOrder order;
		SequenceEvents events;
		std::mutex seqUpdateMutex;
		int16_t totalUnskippedSteps;
		PatternInfo patternInfo;

		SequenceData(SequenceOrder order, SequenceEvents events, int16_t totalUnskippedSteps) :
			order(order), events(events), totalUnskippedSteps(totalUnskippedSteps) {}
		SequenceData(SequenceOrder order, SequenceEvents events, int16_t totalUnskippedSteps, PatternInfo patternInfo) :
			order(order), events(events), totalUnskippedSteps(totalUnskippedSteps), patternInfo(patternInfo) {}
	};

	struct NoteOnLocation
	{
		bool found;
		int8_t barId;
		int16_t stepId;
		int16_t offset;

		NoteOnLocation() : found(false), barId(-1), stepId(-1), offset(-1) {}

		NoteOnLocation(bool f, int8_t bId, int16_t sId, int16_t off)
			: found(f), barId(bId), stepId(sId), offset(off) {}
	};

	struct NoteOffLocation
	{
		bool found;
		int8_t barId;
		int16_t stepId;
		int16_t offset;

		NoteOffLocation() : found(false), barId(-1), stepId(-1), offset(-1) {}

		NoteOffLocation(bool f, int8_t bId, int16_t sId, int16_t off)
			: found(f), barId(bId), stepId(sId), offset(off) {}
	};




	class SequenceManager : public Module, public StepChangeListener, public BarChangeListener, public PatternChangeListener
	{
	public:
		SequenceManager(IParamChangeListener* listener, IgniteEngine& model);
		~SequenceManager();

	private:
		NoteOnLocation findNextNoteOn(const std::map<int8_t, std::map<int16_t, StepInstance>>& barStepEvents, int8_t barId, int16_t stepId, Pattern *pattern);
		std::map <int8_t, StepOffsetMidiEventMap > createEventMap(const std::map <int8_t, std::map <int16_t, StepInstance>>& barStepEvents, Pattern* pattern);
		std::map <int8_t, StepOffsetMidiEventMap > updateEventMap(std::map<int8_t, std::vector <int16_t>> barStepSeqMap, std::string patternName);
		void updateInfo(PatternChangeParameter param, void* info, std::string patternName);

		std::pair<std::map<int8_t, std::vector<int16_t>>, int16_t> generateStepSequence(std::vector <std::vector <int16_t>>& skippedStepsPerBar, std::vector <int16_t>& stepsPerBar, std::vector <PatternDirection> directions);
		EventInstance NoteToEvent(const NodeData& node, Pattern *pattern);
		EventInstance AuxToEvent(const Aux& aux);
		std::vector<int16_t> applyDirection(std::vector<int16_t>&& currentSequence, PatternDirection direction);


		TickOffset_t mapSwingToOffset(int8_t swing, TickOffset_t offsetWithinStep, Pattern* pattern);
		std::tuple<int16_t, TickLength_t> convertToStepAndTicks(TickLength_t lengthInTicks, TickLength_t maxTicksPerStep);
		NoteOffLocation findNoteOffLocation(const std::map<int8_t, std::map<int16_t, StepInstance>>& barStepEvents, int8_t barId, int16_t stepId, int16_t offset, int16_t len, Pattern* pattern);
		void updateEventMapForActiveSong(void);
		void initSequence(std::string patternName, PatternInfo info, int16_t unSkippedSteps);

	public:
		void init(void);
		void initSequence(void);
		void updateSequence(PatternChangeParameter param, uint16_t val, std::string patternName);

		TimeBase getPatternTimeBase(std::string patternName);
		OffsetMidiEventMap getStepEvents(std::string patternName, int8_t barId, uint16_t stepId);
		std::vector<MidiEvent> getStepEventsAtOffset(std::string patternName, int8_t barId, uint16_t stepId, int16_t offset);
		std::vector<MidiEvent> getLinearStepEventsAtOffset(std::string patternName, int8_t barId, uint16_t stepId, int16_t offset);
		int16_t getFirstStepOfBar(int8_t barId, std::string patternName);
		int16_t getLinearFirstStepOfBar(int8_t barId, std::string patternName);
		std::tuple<int8_t, int16_t, int16_t> getNextStepOfBar(int8_t barId, int16_t stepIndex, std::string patternName);
		std::tuple<int8_t, int16_t, int16_t> getLinearNextStepOfBar(int8_t barId, int16_t stepIndex, std::string patternName);
		PatternInfo getUpdatedInfo(std::string patternName);

		virtual void setParamList(moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist, bool isPlayMode) override;
		virtual std::vector<IgniteParamList> getParamList(moduleId_t moduleSrc, std::vector<IgniteParamList>& paramlist) override;
		virtual void SetCommandParam(moduleId_t moduleSrc, paramId_t param, bool isPlayMode) override;
		virtual void getParam(moduleId_t moduleSrc, paramId_t param) override;

		//Step level changes CB
		virtual void handleStepSkipChange(bool skip, PatternBarStepInfo stepAncestory) override;
		virtual void handleStepTieChange(bool tie, PatternBarStepInfo stepAncestory) override;
		virtual void handleStepTransposeDefeatChange(bool transposeDefeat, PatternBarStepInfo stepAncestory) override;
		virtual void handleStepGateChange(bool stepGate, PatternBarStepInfo stepAncestory) override;

		virtual void handleStepNoteChange(PatternBarStepInfo stepAncestory)override;
		virtual void handleStepAuxChange(PatternBarStepInfo stepAncestory)override;

		void handleRecordChange(PatternBarStepInfo stepAncestory);

		//Bar level changes CB
		virtual void handleBarRepeatChange(PatternBarInfo barAncestory)override;
		virtual void handleBarGbarSyncChange(PatternBarInfo barAncestory)override;
		virtual void handleBarTransposeDefeatChange(bool transposeDefeat, PatternBarInfo barAncestory)override;
		virtual void handleBarStepCountChange(uint8_t count, PatternBarInfo barAncestory)override;
		//virtual void handleBarTransposeChange(uint8_t octave, PatternBarInfo barAncestory)override;

		//Pattern level changes CB
		virtual void handleBarCountChange(uint8_t count, std::string patternName)override;
		virtual void handleDirectionChange(PatternDirection direction, std::string patternName)override;
		virtual void handleLastStepChange(uint16_t stepId, std::string patternName)override;
		virtual void handleFirstStepChange(uint16_t stepId, std::string patternName)override;
		virtual void handleTimeBaseChange(TimeBase tb, std::string patternName)override;
		virtual void handleBarLoopChange(bool state, std::string patternName)override;
		virtual void handleBarLoopStartChange(uint8_t barId, std::string patternName)override;
		virtual void handleBarLoopEndChange(uint8_t barId, std::string patternName)override;

		void handlePatternClear (std::string patternName);
		void updateTrackPattern(Pattern* pattern);
		std::pair <PatternInfo, int16_t> extractPatternInfoAndUnskippedSteps(Pattern* pattern);

		int16_t getStepCountForFirstBar (std::string patternName);
		int16_t getLinearStepCountForFirstBar (std::string patternName);

		IgniteEngine& engine;
		std::unordered_map <std::string, SequenceData > patternSequenceMap;
		void SaveData() { return; };
	};
}
