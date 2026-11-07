/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
 * This file is part of IGNITE.
 *
 * IGNITE is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * IGNITE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with IGNITE. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <juce_core/juce_core.h>
#include "../../../Firmware/Application/Model/ModelParams.h"

using namespace juce;
using namespace Ignite;
namespace mt
{
	class IgniteSong;
	class IgniteScene;
	class IgniteSceneRow;
	class IgnitePattern;
	class IgniteTrack;
	class IgniteStep;
	class IgniteConnectivity;
	class IgniteWiFiRow;

	class Ignite
	{
	public:
		Ignite();

		enum class ptype
		{
			MONO,
			POLY,
		};

		enum class operatioMode
		{
			IDLE_MODE,
			PLAY_MODE,
			RECORD_MODE,
			PLAY_REC_MODE,
			PAUSE_MODE,
			AUDITION_MODE,
		};

		enum class direction
		{
			FORWARD,
			REVERSE_A,
			REVERSE_B,
			ALTERNATE,
			PENDULUM,
			RANDOM,
			BROWNIAN,
			EITHERWAY,
		};

		enum class timebase
		{
			ONE,
			TWO,
			TWO_T,
			FOUR,
			FOUR_T,
			EIGHT,
			EIGHT_T,
			SIXTEEN,
			SIXTEEN_T,
			THIRTYTWO,
			THIRTYTWO_T,
			SIXTYFOUR,
			SIXTYFOUR_T,
			PRH,
		};

		struct selectedNode {
			int step;
			int note;
			int value;

			bool operator==(const selectedNode& other) const
			{
				return note == other.note && step == other.step && value == other.value;
			}
		};

		struct customScaleData
		{
			int id;
			String name;
			int serialNum;
			int8 note1_value;
			int8 note2_value;
			int8 note3_value;
			int8 note4_value;
			int8 note5_value;
			int8 note6_value;
			int8 note7_value;
			int8 note8_value;
			int8 note9_value;
			int8 note10_value;
			int8 note11_value;
			int8 note12_value;
		};

		struct instrumentsData
		{
			int id;
			String name;
			String DispName;
			int serialNum;
			bool isIntSoundEnabled;
			int midiPortIndex;
			int midiChannelIndex;
			bool multiState;
			bool xposeState;
			int edtrkThruIndex;
			bool polySpreadIndex;
			bool ftsState;
			int8_t pgmChange;
			int8_t cc0State;
			int8_t cc32State;
			bool noteNums;
			bool pgm;
			int defNoteIndex;
			int programIndex;
		};

		struct patternData
		{
			int id;
			ClientPatternData enginePatternData;
			bool patternDataCreated = false;
			int barIndex;
			int stepIndex;
			int nodeIndex;
			int current_pattern_bank;
		};

		struct trackData
		{
			int id;
			juce::String name;
			int serialNum;
			juce::String pattern;
			juce::String fillPattern;
			juce::String instrument;
			juce::String outputInstrument;
			bool trackState;
			bool soloMode;
			bool recordState;
			uint8_t scene_index;
			patternData* pattern_data;
		};

		struct sceneData
		{
			int id;
			juce::String name;
			int serialNum;
			int8_t gbar;
			int16_t length;
			int8_t songadv;
			int8_t ftsRootNoteIndex;
			int8_t ftsScaleIndex;
			int8_t xpose;
			int8_t muteHoldIndex;
			int8_t xfts;
			float tempo;
			uint8_t swing;
			int song_index;
			int num_of_track_banks;
			int current_track;
			int current_track_bank;
			int activeTracks;
			bool trackDataLoded = true;
			std::vector<trackData> track_data;
			int current_scene_bank;
		};

		struct songData
		{
			int id;
			juce::String name;
			int current_scene;
			int next;
			int num_scenes;
			int serialNum;
			float tempo;
			uint8_t swing;
			int num_of_tracks;
			bool sceneCreated;
			int selectedSong;
			int selectedScene;
			int loopSceenStart;
			int loopSceenEnd;
			uint8_t sceneAdvanceMode;
			bool isFillMode;
			bool songLoaded = false;
			std::vector<sceneData> scene_data;
			juce::OwnedArray<IgniteSceneRow>* list;
			int current_song_bank;
		};

		typedef struct track_values
		{
			int trackValueType;
			int  trackValueSelected;
			float minValue;
			float maxValue;
			float initValue;
			float currentValue;
			int8 lsbValue;
			int8 msbValue;
			bool internalsound;
			int slot;
			String name;
		}TrackValues;

		typedef struct statusBarParams
		{
			bool isSongCreated = false;
			bool isSceneCreated = false;
			bool isPatternCreated = false;
			int8_t songadv = 0;
			uint8_t swing = 0;
			uint8_t timeBase = 0;
			int songIndex = 0;
			int editSceneIndex = 1;
			int nextSceneIndex = 0;
			int sceneLength = 1;
			int currentTrack = 0;
			int editPattern = 0;
			uint8_t numberOfBars = 0;
			int16_t numberOfSteps = 0;
			int activeBarId = 0;
			int activeStepId = 0;
			float tempo = 0.0;
		}StatusParams;

		enum class wifiSigStrength
		{
			STRONG_SIGNAL,
			WEEK_SIGNAL,
			WEEKER_SIGNAL,
		};

		struct wifiData
		{
			int id;
			juce::String name;
			bool wifiConnected = false;
			wifiSigStrength signalStrength;
			bool isSecure = true;
			juce::OwnedArray<IgniteWiFiRow>* list;
		};

		struct WiFiNetwork
		{
			std::string ssid;
			bool security;   
			int signalStrength;
		};

		struct wifiProperties
		{
			std::string macAddress;
			std::string ipAddress;
			std::string subnetMask;
			std::string gateway;
		};

		enum class customScaleDataIndex
		{
			FTS_ID,
			FTS_NAME,
			FTS_NUM,
			FTS1_VALUE,
			FTS2_VALUE,
			FTS3_VALUE,
			FTS4_VALUE,
			FTS5_VALUE,
			FTS6_VALUE,
			FTS7_VALUE,
			FTS8_VALUE,
			FTS9_VALUE,
			FTS10_VALUE,
			FTS11_VALUE,
			FTS12_VALUE,
		};

		enum class instrumentsDataIndex
		{
			INSTR_ID,
			INSTR_NAME,
			INSTR_DISP_NAME,
			SERIAL_NUM,
			INTERNAL_SOUND,
			INSTR_PORT,
			INSTR_CHANNEL,
			INSTR_MULTI,
			INSTR_XPOSE,
			INSTR_EDTRK,
			INSTR_POLY,
			INSTR_FTS,
			INSTR_PGM_CHANGE,
			INSTR_CC0,
			INSTR_CC32,
			INSTR_NOTENUM,
			INSTR_PGM,
			INSTR_DEFNOTE,
			PROGRAM_INDEX,
		};

		enum class TrackValueDataIndex
		{
			Active_Knob = 26,

			MidiCCNum = 27,
			MidiCCName = 28,
			MidiCCValue = 29,
			MidiCCInitValue = 30,
			MidiCCMinValue = 31,
			MidiCCMaxValue = 32,
			AddTrackValueCmd = 33,

			SeqMidiPgmNum = 0,
			SeqQuantPercent = 1,
			SeqVelocityPercent = 4,
			SeqVelocityRef = 5,
			SeqLengthPercent = 6,
			SeqNotePercent = 2,
			SeqNoteRef = 3,
			SeqTransposeSemiTone = 8,
			SeqTransposeOctave = 9,
			SeqFtsScale = 13,
			SeqFtsRootNote = 12,
			SeqReichValue = 14,
			SeqMidiPgmBankLsb = 34,
			SeqTVMidiPgmBankMsb = 35,
			TVType = 36,
			INSTRUMENT=37,
			EffectState,
			ALL,
		};

		enum class nodeDataIndex
		{
			ID,
			NOTE_NUM,
			VELO,
			STEP_LEN_IN_STEP,
			STEP_LEN_IN_TICK,
			DELAY,
		};

		enum stepEventDataIndex
		{
			EVENT_STATUS,
			EVENT_NAME,
			EVENT_TYPE,
			EVENT_VALUE,
			EVENT_OFFSET,
		};

		enum stepDataIndex
		{
			BAR_ID,
			STEP_ID,
			NODE_COUNT,
			GATE_STATUS,
			SKIP_STATUS,
			TRANSPOSE_DEFEAT_STATUS,
			TIE_STATUS,
		};

		enum class barDataIndex
		{
			ID,
			NUM_STEPS,
			TRANSPOSE_DEFEAT_STATUS,
			BAR_REPEAT,
			GBAR_SYNC,
			DIR_INDEX,
		};

		enum class ptDataIndex
		{
			BARNUM,
			DIR_INDEX,
			TIMEBASE,
			LASTSTEP,
			NAME,
			ID,
			BAR_ID,
			STEP_ID,
			NODE_ID,
			BAR_LOOP_ON,
			BAR_LOOP_START,
			BAR_LOOP_END

		};

		enum  class trackDataIndex
		{
			TRACK_ID,
			TRACK_NAME,
			TRACK_SERIALNUM,
			TRACK_PATTERN,
			TRACK_PFILL,
			TRACK_INSTR,
			TRACK_STATE,
			TRACK_SOLO_MODE,
			TRACK_REC_STATE,
			TRACK_OUT_INSTR,
		};

		enum  class sceneDataIndex
		{
			SCENE_ID,
			SCENE_NAME,
			GBAR,
			LENGHT,
			SONGADV,
			FTSROOTNOTE,
			FTSSCALE,
			XPOSE,
			MUTEHOLD,
			XFTS,
			SCENE_TEMPO,
			SCENE_SWING,
			SONG_INDEX,
			NUM_TRACK_BANK_INDEX,
			CURRENT_TRACK,
			CURRENT_TRACK_BANK,
			TRACKS_ACTIVE,
			TRACK_DATA_REVALIDATE,
		};

		enum class songsDataIndex
		{
			SONG_ID,
			SONG_NAME,
			CURRENT_SCENE,
			NEXT_SCENE,
			NUM_SCENES,
			SONG_SR_NUM,
			TEMPO,
			SWING,
			NUM_TRACKS_INDEX,
			SCENE_CREATED,
			SELECTED_SONG,
			SELECTED_SCENE,
			LOOP_SCENE_START,
			LOOP_SCENE_END,
			SCENE_ADVANCE_MODE,
			FILLMODE,
		};

		enum trackValueType
		{
			MIDICC = 1,
			TRACKCTLVALUE = 2
		};
		/// Constants.
		typedef enum {
			DefaultView = 0,
			CustomView
		}DailogViewType;

		enum class tabs
		{
			MENU = 0,
			SONG = 1,
			SCENE = 2,
			TRACK = 3,
			PATTERN = 4,
			POWER_OFF = 5,
			BRAY = 6,
			INTSOUND = 7,
			KEY_LAST = 8,
			USB_STOP = 9,
		};

		// insert position
		const static inline std::vector<juce::String> songInsertPosition{ "At the End", "Next to Active Song" };
		const static inline std::vector<juce::String> sceneInsertPosition{ "At the End", "Next to Active Scene" };
		const static inline std::vector<juce::String> patternInsertPosition{ "At the End", "Next to Active Pattern" };

		/* AUX EVENT LIST */
		const static inline  std::vector<juce::String> eventList{ "POLY PRESSURE", "MIDI CC", "PGM CHANGE", " CHANNEL PRESSURE", "PITCH BEND" };

		// MIDI & CV ports
		// Any change in order here, needs to reflect in enum midiDataIOPorts
		static inline  std::vector<juce::String> portList{ "MIDI-1", "MIDI-2", "MIDI-3", "MIDI-4", "MIDI-5",
			"CV1", "CV2", "CV3", "CV4", "CV5", "CV6", "CV7", "CV8",
			"USB:MIDI1", "USB:MIDI2", "USB:MIDI3", "USB:MIDI4", "USB:MIDI5", "USB:MIDI6"};

		// MIDI ports
		static inline  std::vector<juce::String> midiPortList{ "MIDI-1", "MIDI-2", "MIDI-3", "MIDI-4", "MIDI-5",
		"USB:MIDI1", "USB:MIDI2", "USB:MIDI3", "USB:MIDI4", "USB:MIDI5", "USB:MIDI6" };

		// USB MIDI ports
		static inline  std::vector<juce::String> midiUsbPortList{ "USB:MIDI1", "USB:MIDI2", "USB:MIDI3", "USB:MIDI4", "USB:MIDI5", "USB:MIDI6" };

		// Root Notes.
		const static inline std::vector<juce::String> rootNoteNamesSharps = {
			"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
		};

		const static inline std::vector<juce::String> rootNoteNamesFlats = {
		"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"
		};
		//Pattern Directions
		const static inline std::vector<juce::String> directions{ "Forward", "Reverse A", "Reverse B", "Alternate", "Pendulum", "Random", "Brownian", "Eitherway", "Bar Level"};

		//Pattern Timebase
		const static inline std::vector<juce::String>  tbvalues{ "1", "2", "2T", "4", "4T", "8", "8T", "16", "16T", "32", "32T" };

		// Midi Notes.
		const static inline std::vector<juce::String> midiNoteNamesSharps = {
			"C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0",
			"C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
			"C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
			"C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
			"C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
			"C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
			"C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
			"C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7",
			"C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8", "A8", "A#8", "B8",
			"C9", "C#9", "D9", "D#9", "E9", "F9", "F#9", "G9", "G#9", "A9", "A#9", "B9",
			"C10", "C#10", "D10", "D#10", "E10", "F10", "F#10", "G10", "---"
		};

		const static inline std::vector<juce::String> midiNoteNamesFlats = {
		 "C0", "Db0", "D0", "Eb0", "E0", "F0", "Gb0", "G0", "Ab0", "A0", "Bb0", "B0",
		 "C1", "Db1", "D1", "Eb1", "E1", "F1", "Gb1", "G1", "Ab1", "A1", "Bb1", "B1",
		 "C2", "Db2", "D2", "Eb2", "E2", "F2", "Gb2", "G2", "Ab2", "A2", "Bb2", "B2",
		 "C3", "Db3", "D3", "Eb3", "E3", "F3", "Gb3", "G3", "Ab3", "A3", "Bb3", "B3",
		 "C4", "Db4", "D4", "Eb4", "E4", "F4", "Gb4", "G4", "Ab4", "A4", "Bb4", "B4",
		 "C5", "Db5", "D5", "Eb5", "E5", "F5", "Gb5", "G5", "Ab5", "A5", "Bb5", "B5",
		 "C6", "Db6", "D6", "Eb6", "E6", "F6", "Gb6", "G6", "Ab6", "A6", "Bb6", "B6",
		 "C7", "Db7", "D7", "Eb7", "E7", "F7", "Gb7", "G7", "Ab7", "A7", "Bb7", "B7",
		 "C8", "Db8", "D8", "Eb8", "E8", "F8", "Gb8", "G8", "Ab8", "A8", "Bb8", "B8",
		 "C9", "Db9", "D9", "Eb9", "E9", "F9", "Gb9", "G9", "Ab9", "A9", "Bb9", "B9",
		 "C10", "Db10", "D10", "Eb10", "E10", "F10", "Gb10", "G10", "---"
		};

		//Last steps:  max number of Bars x Max number of steps = 16x16 =256  TODO: support for steps based in number of bars
		const static inline std::vector<juce::String>  lastSteps{ "1 : 1", "1 : 2", "1 : 3", "1: 4", "1 : 5", "1 : 6", "1 : 7", "1 : 8", "1 : 9", "1 : 10", "1 : 11", "1 : 12", "1 : 13", "1 : 14", "1 : 15", "1 : 16",
		"2 : 1", "2 : 2", "2 : 3", "2 : 4", "2 : 5", "2 : 6", "2 : 7", "2 : 8", "2 : 9", "2 : 10", "2 : 11", "2 : 12", "2 : 13", "2 : 14", "2 : 15", "2 : 16",
		"3 : 1", "3 : 2", "3 : 3", "3 : 4", "3 : 5", "3 : 6", "3 : 7", "3 : 8", "3 : 9", "3 : 10", "3 : 11", "3 : 12", "3 : 13", "3 : 14", "3 : 15", "3 : 16",
		"4 : 1", "4 : 2", "4 : 3", "4 : 4", "4 : 5", "4 : 6", "4 : 7", "4 : 8", "4 : 9", "4 : 10", "4 : 11", "4 : 12", "4 : 13", "4 : 14", "4 : 15", "4 : 16",
		"5 : 1", "5 : 2", "5 : 3", "5 : 4", "5 : 5", "5 : 6", "5 : 7", "5 : 8", "5 : 9", "5 : 10", "5 : 11", "5 : 12", "5 : 13", "5 : 14", "5 : 15", "5 : 16",
		"6 : 1", "6 : 2", "6 : 3", "6 : 4", "6 : 5", "6 : 6", "6 : 7", "6 : 8", "6 : 9", "6 : 10", "6 : 11", "6 : 12", "6 : 13", "6 : 14", "6 : 15", "6 : 16",
		"7 : 1", "7 : 2", "7 : 3", "7 : 4", "7 : 5", "7 : 6", "7 : 7", "7 : 8", "7 : 9", "7 : 10", "7 : 11", "7 : 12", "7 : 13", "7 : 14", "7 : 15", "7 : 16",
		"8 : 1", "8 : 2", "8 : 3", "8 : 4", "8 : 5", "8 : 6", "8 : 7", "8 : 8", "8 : 9", "8 : 10", "8 : 11", "8 : 12", "8 : 13", "8 : 14", "8 : 15", "8 : 16",
		"9 : 1", "9 : 2", "9 : 3", "9 : 4", "9 : 5", "9 : 6", "9 : 7", "9 : 8", "9 : 9", "9 : 10", "9 : 11", "9 : 12", "8 : 13", "9 : 14", "9 : 15", "9 : 16",
		"10 : 1", "10 : 2", "10 : 3", "10 : 4", "10 : 5", "10 : 6", "10 : 7", "10 : 8", "10 : 9", "10 : 10", "10 : 11", "10 : 12", "10 : 13", "10 : 14", "10 : 15", "10 : 16",
		"11 : 1", "11 : 2", "11 : 3", "11 : 4", "11 : 5", "11 : 6", "11 : 7", "11 : 8", "11 : 9", "11 : 10", "11 : 11", "11 : 12", "11 : 13", "11 : 14", "11 : 15", "11 : 16",
		"12 : 1", "12 : 2", "12 : 3", "12 : 4", "12 : 5", "12 : 6", "12 : 7", "12 : 8", "12 : 9", "12 : 10", "12 : 11", "12 : 12", "12 : 13", "12 : 14", "12 : 15", "12 : 16",
		"13 : 1", "13 : 2", "13 : 3", "13 : 4", "13 : 5", "13 : 6", "13 : 7", "13 : 8", "13 : 9", "13 : 10", "13 : 11", "13 : 12", "13 : 13", "13 : 14", "13 : 15", "13 : 16",
		"14 : 1", "14 : 2", "14 : 3", "14 : 4", "14 : 5", "14 : 6", "14 : 7", "14 : 8", "14 : 9", "14 : 10", "14 : 11", "14 : 12", "14 : 13", "14 : 14", "14 : 15", "14 : 16",
		"15 : 1", "15 : 2", "15 : 3", "15 : 4", "15 : 5", "15 : 6", "15 : 7", "15 : 8", "15 : 9", "15 : 10", "15 : 11", "15 : 12", "15 : 13", "15 : 14", "15 : 15", "15 : 16",
		"16 : 1", "16 : 2", "16 : 3", "16 : 4", "16 : 5", "16 : 6", "16 : 7", "16 : 8", "16 : 9", "16 : 10", "16 : 11", "16 : 12", "16 : 13", "16 : 14", "16 : 15", "16 : 16"
		};

		const static inline std::vector<juce::String> midiccVal{ "cc #0", "cc #1", "cc #2", "cc #3", "cc #4", "cc #5", "cc #6", "cc #7", "cc #8", "cc #9","cc #10",
										"cc #11", "cc #12", "cc #13", "cc #14", "cc #15", "cc #16", "cc #17", "cc #18", "cc #19","cc #20",
										"cc #21", "cc #22", "cc #23", "cc #24", "cc #25", "cc #26", "cc #27", "cc #28", "cc #29","cc #30",
										"cc #31", "cc #32", "cc #33", "cc #34", "cc #35", "cc #36", "cc #37", "cc #38", "cc #39","cc #40",
										"cc #41", "cc #42", "cc #43", "cc #44", "cc #45", "cc #46", "cc #47", "cc #48", "cc #49","cc #50",
										"cc #51", "cc #52", "cc #53", "cc #54", "cc #55", "cc #56", "cc #57", "cc #58", "cc #59","cc #60",
										"cc #61", "cc #62", "cc #63", "cc #64", "cc #65", "cc #66", "cc #67", "cc #68", "cc #69","cc #70",
										"cc #71", "cc #72", "cc #73", "cc #74", "cc #75", "cc #76", "cc #77", "cc #78", "cc #79","cc #80",
										"cc #81", "cc #82", "cc #83", "cc #84", "cc #85", "cc #86", "cc #87", "cc #88", "cc #89","cc #90",
										"cc #91", "cc #92", "cc #93", "cc #94", "cc #95", "cc #96", "cc #97", "cc #98", "cc #99","cc #100",
										"cc #101", "cc #102", "cc #103", "cc #104", "cc #105", "cc #106", "cc #107", "cc #108", "cc #109","cc #110",
										"cc #111", "cc #112", "cc #113", "cc #114", "cc #115", "cc #116", "cc #117", "cc #118", "cc #119","cc #120",
										"cc #121", "cc #122", "cc #123", "cc #124", "cc #125", "cc #126", "cc #127", "" };

		const static inline std::vector<juce::String> auditionPresetList{ "Off", "Acoustic Grand", "Bright Acoustic", "Electric Grand", "Honky - tonk",
				"Electric Piano 1", "Electric 2", "Harpsichord", "Clavi", "Celesta", "Glockenspiel", "Music Box", "Vibraphone", "Marimba",
				"Xylophone", "Tubular Bells", "Dulcimer", "Drawbar Organ", "Percussive Organ", "Rock Organ", "Church Organ",
				"Reed Organ", "Accordion", "Harmonica", "Tango Accordion", "Acoustic Guitar \n (nylon)",
				"Acoustic Guitar \n (steel)", "Electric Guitar \n (jazz)", "Electric Guitar \n (clean)",
				"Electric Guitar \n (muted)", "Overdriven Guitar", "Distortion Guitar", "Guitar harmonics",
				"Acoustic Bass", "Electric Bass \n (finger)", "Electric Bass \n (pick)", "Fretless Bass",
				"Slap Bass 1", "Slap Bass 2", "Synth Bass 1", "Synth Bass 2", "Violin", "Viola",
				"Cello", "Contrabass", "Tremolo Strings", "Pizzicato Strings", "Orchestral Harp",
				"Timpani", "String Ensemble 1", "String Ensemble 2", "SynthStrings 1", "SynthStrings 2",
				"Choir Aahs", "Voice Oohs", "Synth Voice", "Orchestra Hit","Trumpet", "Trombone",
				"Tuba", "Muted Trumpet", "French Horn", "Brass Section", "SynthBrass 1", "SynthBrass 2",
				"Soprano Sax", "Alto Sax", "Tenor Sax", "Baritone Sax", "Oboe", "English Horn",
				"Bassoon", "Clarinet", "Piccolo", "Flute", "Recorder", "Pan Flute", "Blown Bottle",
				"Shakuhachi", "Whistle", "Ocarina", "Lead 1 \n (square)", "Lead 2 \n (sawtooth)", "Lead 3 \n (calliope)",
				"Lead 4 \n (chiff)", "Lead 5 \n (charang)", "Lead 6 \n (voice)", "Lead 7 \n (fifths)", "Lead 8 \n (bass + lead)",
				"Pad 1 \n (new age)", "Pad 2 \n (warm)", "Pad 3 \n (polysynth)", "Pad 4 \n (choir)", "Pad 5 \n (bowed)",
				"Pad 6 \n (metallic)", "Pad 7 \n (halo)", "Pad 8 \n (sweep)", "FX 1 \n (rain)", "FX 2 \n (soundtrack)",
				"FX 3 \n (crystal)", "FX 4 \n (atmosphere)", "FX 5 \n (brightness)", "FX 6 \n (goblins)", "FX 7 \n (echoes)",
				"FX 8 \n (sci-fi)", "Sitar", "Banjo", "Shamisen", "Koto", "Kalimba", "Bag pipe", "Fiddle",
				"Shanai", "Tinkle Bell", "Agogo", "Steel Drums", "Woodblock", "Taiko Drum", "Melodic Tom",
				"Synth Drum", "Reverse Cymbal", "Guitar Fret Noise", "Breath Noise", "Seashore", "Bird Tweet",
				"Telephone Ring", "Helicopter", "Applause", "Gunshot", "Standard", "Room", "Power", "Electronic", "TR 808", "Jazz", "Brush", "Orchestra", "SFX", "CM64/32" };


		const static inline std::vector<juce::String> presetList{ "Acoustic Grand", "Bright Acoustic", "Electric Grand", "Honky-tonk",
						"Electric Piano 1", "Electric 2", "Harpsichord", "Clavi", "Celesta", "Glockenspiel", "Music Box", "Vibraphone", "Marimba",
						"Xylophone", "Tubular Bells", "Dulcimer", "Drawbar Organ", "Percussive Organ", "Rock Organ", "Church Organ",
						"Reed Organ", "Accordion", "Harmonica", "Tango Accordion", "Acoustic Guitar \n (nylon)",
						"Acoustic Guitar \n (steel)", "Electric Guitar \n (jazz)", "Electric Guitar \n (clean)",
						"Electric Guitar \n (muted)", "Overdriven Guitar", "Distortion Guitar", "Guitar harmonics",
						"Acoustic Bass", "Electric Bass \n (finger)", "Electric Bass \n (pick)", "Fretless Bass",
						"Slap Bass 1", "Slap Bass 2", "Synth Bass 1", "Synth Bass 2", "Violin", "Viola",
						"Cello", "Contrabass", "Tremolo Strings", "Pizzicato Strings", "Orchestral Harp",
						"Timpani", "String Ensemble 1", "String Ensemble 2", "SynthStrings 1", "SynthStrings 2",
						"Choir Aahs", "Voice Oohs", "Synth Voice", "Orchestra Hit","Trumpet", "Trombone",
						"Tuba", "Muted Trumpet", "French Horn", "Brass Section", "SynthBrass 1", "SynthBrass 2",
						"Soprano Sax", "Alto Sax", "Tenor Sax", "Baritone Sax", "Oboe", "English Horn",
						"Bassoon", "Clarinet", "Piccolo", "Flute", "Recorder", "Pan Flute", "Blown Bottle",
						"Shakuhachi", "Whistle", "Ocarina", "Lead 1 \n (square)", "Lead 2 \n (sawtooth)", "Lead 3 \n (calliope)",
						"Lead 4 \n (chiff)", "Lead 5 \n (charang)", "Lead 6 \n (voice)", "Lead 7 \n (fifths)", "Lead 8 \n (bass + lead)",
						"Pad 1 \n (new age)", "Pad 2 \n (warm)", "Pad 3 \n (polysynth)", "Pad 4 \n (choir)", "Pad 5 \n (bowed)",
						"Pad 6 \n (metallic)", "Pad 7 \n (halo)", "Pad 8 \n (sweep)", "FX 1 \n (rain)", "FX 2 \n (soundtrack)",
						"FX 3 \n (crystal)", "FX 4 \n (atmosphere)", "FX 5 \n (brightness)", "FX 6 \n (goblins)", "FX 7 \n (echoes)",
						"FX 8 \n (sci-fi)", "Sitar", "Banjo", "Shamisen", "Koto", "Kalimba", "Bag pipe", "Fiddle",
						"Shanai", "Tinkle Bell", "Agogo", "Steel Drums", "Woodblock", "Taiko Drum", "Melodic Tom",
						"Synth Drum", "Reverse Cymbal", "Guitar Fret Noise", "Breath Noise", "Seashore", "Bird Tweet",
						"Telephone Ring", "Helicopter", "Applause", "Gunshot", "Standard", "Room", "Power", "Electronic", "TR 808", "Jazz", "Brush", "Orchestra", "SFX", "CM64/32" };
		// Scales.
		const static inline std::vector<juce::String> scaleNames = {
			"Major", "Natural Minor", "Harmonic Minor", "Pentatonic Major", "Pentatonic Minor", "Blues"
		};

		const static inline std::vector<std::vector<int>> scaleFormulas = {
			{ 2, 2, 1, 2, 2, 2, 1 }, // Major
			{ 2, 1, 2, 2, 1, 2, 2 }, // Natural Minor
			{ 2, 1, 2, 2, 1, 3, 1 }, // Harmonic Minor
			{ 2, 2, 3, 2, 3 }, // Pentatonic Major
			{ 3, 2, 2, 3, 2 }, // Pentatonic Minor
			{ 3, 2, 1, 1, 3, 2 } // Blues
		};

		// Pads.
		const static inline std::vector<juce::String> padBankNames = {
			"A", "B", "C", "D", "E", "F", "G", "H"
		};
		const static inline std::vector<juce::String> padNames = {
			"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "A11", "A12", "A13", "A14", "A15", "A16",
			"B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10", "B11", "B12", "B13", "B14", "B15", "B16",
			"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11", "C12", "C13", "C14", "C15", "C16",
			"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "D11", "D12", "D13", "D14", "D15", "D16",
			"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10", "E11", "E12", "E13", "E14", "E15", "E16",
			"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16",
			"G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9", "G10", "G11", "G12", "G13", "G14", "G15", "G16",
			"H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "H11", "H12", "H13", "H14", "H15", "H16"
		};

		// Note Lengths.
		const static inline std::vector<juce::String> noteLengthNames = {
			"Bar", "1/2", "1/4", "1/4T", "1/8", "1/8T", "1/16", "1/16T", "1/32", "1/32T", "1/64", "1/64T"
		};

		// Pattern bar number
		const static inline std::vector<juce::String> barNumber{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16" };

		struct songSettings
		{
			bool autoSave;
			bool accidentals;
			bool soloMode;
			uint8_t fillModeState;
			uint8_t fillRelease;
		};

#define PAD1 1
#define PAD2 2
#define PAD3 3
#define PAD4 4
#define PAD5 5
#define PAD6 6
#define PAD7 7
#define PAD8 8
#define PAD9 9
#define PAD10 10
#define PAD11 11
#define PAD12 12
#define PAD13 13
#define PAD14 14
#define PAD15 15
#define PAD16 16

#define PADS_IN_BANK 16

#define NUM_ROW_FOR_SCROLL 6
		/// Type Definitions...

		enum class EventType
		{
			DrumEvents,
			MelodicEvents
		};

		enum class RandomEventType
		{
			ReplaceAll,
			ReplaceInRange,
			AppendExisting
		};

		typedef struct _track
		{
			typedef struct _noteRange
			{
				juce::String start;
				juce::String end;
			}noteRange;

			typedef struct _splitInfo
			{
				bool onlyForSelectedNotes{ false };
				int value{ 2 };
			}splitInfo;

			typedef struct _humanizeInfo
			{
				bool onlyForSelectedNotes{ false };
				bool isNoteLengthEnabled{ false };
				bool isTimeEnabled{ false };
				bool isVelocityEnabled{ false };
				int8_t eagerness{ 0 };
				uint8_t time{ 1 };
				uint8_t velocity{ 1 };
				uint8_t noteLength{ 2 };
			}humanizeInfo;

			typedef struct _patternLenInfo
			{
				bool isHoldEnabled{ false };
				uint8_t steps{ 0 };
				uint8_t ticks{ 0 };
			}patternLenInfo;

			typedef struct _pitchQuantizeInfo
			{
				bool onlyForSelectedNotes{ false };
				juce::String rootNoteValue;
				juce::String scaleValue;
				noteRange range;
			}pitchQuantizeInfo;

			typedef struct _randomEventsInfo
			{
				bool isLegatoSelected{ false };
				bool isConstrainNotesToScaleSelected{ false };
				mt::Ignite::EventType eventType{ mt::Ignite::EventType::DrumEvents };
				mt::Ignite::RandomEventType replace{ mt::Ignite::RandomEventType::ReplaceAll };
				uint8_t patternSize;
				uint8_t densityValue;
				uint8_t rhythmVariationValue;
				uint8_t polyphonyValue;
				juce::String noteLenghtValue;
				juce::String bankValue;
				juce::String rootNoteValue;
				juce::String scaleValue;
				noteRange pads;
				noteRange range;
			}randomEventsInfo;
			//
		}track;

		/// Utility functions...
		static int getRootNoteNumber(const juce::String& Root);
		static const juce::String& getRootNoteName(int Number);
		static int8_t getNoteNumber(const juce::String& Note);
		static const juce::String& getNoteName(int Number);
		static std::vector<int> getNotesInScale(const juce::String& Root, const juce::String& Scale, const juce::String& StartNote, const juce::String& EndNote);
		static int getPadBankNumber(const juce::String& PadBank);
		static const juce::String& getPadBankName(int Number);
		static int getPadNumber(const juce::String& Pad);
		static const juce::String& getPadName(int Number);
		static double getNoteLength(const juce::String& Length);

	private:
		static int findIndex(const juce::String& Note, const std::vector<juce::String>& NoteArray);
		static std::vector<int> getScaleNotesInRange(const int RootNote, const std::vector<int>& Scale, const int Start = 0, const int End = 127);
	};
}
