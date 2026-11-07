/*
* Copyright (c) - 2022 - MUSIC Tribe, MY.
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

namespace ui
{

#define MAX_TRACK_VALUE 8
#define CHORUS_DEPTH "Depth"
#define CHORUS_RATE  "Rate"
#define REVERB_DRY  "Dry"
#define REVERB_WIDTH "Width"
#define FILTER_CUTOFF "Freq"
#define FILTER_MODE "Mode"
#define EQ_GAIN "Gain"
#define EQ_FREQ "Freq"
#define VOLUME_MASTER "Master"
#define VOLUME_ALT "Track"

	class TrackValueSelection;

	class IgniteTrackValues :
		public juce::Component,
		public CommonButton::Listener,
		public common_rotaryslider::Listener
	{
	public:
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		int isEditing();
		void setSliderEditCtl(bool state);

		typedef struct
		{
			String instrumentIndex;
			Array<ui::commonrotary*> sliderPtr;
			Array<mt::Ignite::TrackValues*> trackValueArray;
		}TrackValuesStruct;

		static IgniteTrackValues* GetAppTrackValueInstance()
		{
			static IgniteTrackValues* instanceAppTrackValue;
			if (NULL == instanceAppTrackValue)
			{
				instanceAppTrackValue = new IgniteTrackValues();
			}
			return instanceAppTrackValue;
		}

		bool isModelOpened = false;
		int8_t activeKnob = 0;
		mt::Ignite::TrackValues activeKnobdata;

		IgniteTrackValues();
		~IgniteTrackValues() override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		virtual void buttonClicked(juce::Button* buttonThatWasClicked) override;
		bool isUpdateRotaryData = true;
		void updateTrackValueScreen();
		void getDataHolder();
		void onRotaryValueChange(common_rotaryslider*, double Value) override;
		void onTitleChange(common_rotaryslider*, String s) override;
		void onDoubleClicked(common_rotaryslider*) override;
		void onbuttonClicked(common_rotaryslider*, bool value) override;
		void setTrackValueData(mt::Ignite::TrackValueDataIndex item_id, int data);
		void setTrackValueData(mt::Ignite::TrackValueDataIndex item_id, float data);
		void setTrackValueData(mt::Ignite::TrackValueDataIndex item_id, std::string data);
		void setDefaultKnobTitle();
		void setAltFnStatus(bool state) { altFunEnabled = state; }
		void setInstSoundStatus(bool s);
		void setAlternativeFunc();
		void setKnobIndex();
		bool getInstSoundStatus() { return soundStatus; };
		int getKnobIndex(String knob);
		void getdatafromEngine(int knob);
		void updateSlider(mt::Ignite::TrackValues* p);
		bool getFxAltState() { return altFunEnabled; };
		mt::Ignite::TrackValues getactiveknobdata() { return  activeKnobdata; };

		std::vector<juce::String> intSoundDefaultknobLable = { "RELEASE", "CUTOFF", "RESONANCE","VOLUME", "REVERB", "CHORUS", "EQ HIGH", "EQ LOW" };
		std::vector<juce::String> extSoundDefaultknobLable = { "CC #72", "CC #20", "CC #71","CC #7", "CC #91", "CC #93", "CC #21", "CC #22" };
		std::vector<juce::String> notecList = { "C0", "C1", "C2","C3", "C4", "C5", "C6", "C7","C8","C9","C10" };
		std::vector<juce::String> fts_sList = { "all","maj", "aeo","har", "mel", "blu","pen", "mix", "lyd", "bl2", "aug", "arb",
												"bal", "hng", "ori", "rga", "chi", "hn2", "jap","jp2", "per", "dim", "who", "u01", "u02", "u03", "u04", "u05", "u06", "u07", "u08" };
	private:
		TrackValuesStruct* currentDataHolder;
		CommonLabel header{ "Track FX" };
		CommonImageButton back{ " Back ", "back-default.png","back-active.png","back-disabled.png" };
		TrackValueSelection* valueSelectionPtr = nullptr;

		juce::FlexBox headerBox;
		juce::FlexBox sliderContainerBox1;
		juce::FlexBox sliderContainerBox;
		juce::FlexBox trackMainEnvlopBox;
		commonrotary slider[8];
		CommonAutoHideSlider* hideSlider;
		bool soundStatus = true;
		int current_slider = 0;
		bool altFunEnabled = false;
		int8_t isFromFp = -1;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTrackValues)
	};

	class TrackValueSelection : public juce::Component,
		public CommonButton::Listener
	{
	public:

#define TRACK_VALUE_SEL_VIEW 9
		enum TrackValuesSelViewItemID
		{
			NO_FOCUS = 0,
			MIDI_CC,
			PGM_CHANGE,
			CC_BOX,
			INIT_VALUE,
			MAX_VALUE,
			APPLY,
			CANCEL,
			RESET,
			FOCUS_MAX = RESET
		};
		uint8_t OptionsView[TRACK_VALUE_SEL_VIEW] = { NO_FOCUS, MIDI_CC, PGM_CHANGE, CC_BOX, INIT_VALUE, MAX_VALUE, APPLY, CANCEL, RESET };
		int KeyFocusedItem = TrackValuesSelViewItemID::NO_FOCUS;

#define TRACK_VALUE_PGMSEL_VIEW 8
		enum TrackValuesPgmSelViewItemID
		{
			PGMNO_FOCUS = 0,
			PGMMIDI_CC,
			PGMPGM_CHANGE,
			LSB,
			MSB,
			PGMAPPLY,
			PGMCANCEL,
			PGMRESET,
			PGMFOCUS_MAX = PGMRESET
		};
		uint8_t pgmOptionsView[TRACK_VALUE_PGMSEL_VIEW] = { PGMNO_FOCUS, PGMMIDI_CC, PGMPGM_CHANGE, LSB, MSB, PGMAPPLY, PGMCANCEL, PGMRESET };
		int pgmKeyFocusedItem = TrackValuesPgmSelViewItemID::PGMNO_FOCUS;

		TrackValueSelection();
		~TrackValueSelection() override;

		static TrackValueSelection* GetAppTrackValueSelectionInstance()
		{
			static TrackValueSelection* instanceAppTrackValueSelection;
			if (NULL == instanceAppTrackValueSelection)
			{
				instanceAppTrackValueSelection = new TrackValueSelection();
			}
			return instanceAppTrackValueSelection;
		}

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void updateAccidentals(bool state);
		IgniteTrackValues::TrackValuesStruct* trackValuePtr = nullptr;
		void updateRotaryData(mt::Ignite::TrackValues);
		std::vector<juce::String> knobValues = { "A", "B", "C","D", "E", "F", "G", "H" };
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue, int knob);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();
		bool CCFPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);
		bool pgmPannelKeyHandler(paramId_t param, uint32_t KeyValue, int knob);
		void pgmPannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isPgmEditing();
		void clearPrevTrackValuFocus();

	private:
		int valueUpdateIndex;
		juce::FlexBox ctlBox;
		juce::FlexBox valueSelectionBox1;
		juce::FlexBox valueSelectionBox2;
		juce::FlexBox valueSelectionBox;
		mt::Ignite::TrackValues presentTrackValues;
		int ValueType;
		CommonLabel  initLable{ "Initial Value " };
		CommonLabel  maxLable{ "Max Value " };
		CommonLabel  BlsbLable{ "Bank LSB " };
		CommonLabel  BmsbLable{ "Bank MSB " };

		CommonLabel  knobLabel{ "Knob: " };

		CommonListBox valueBox{ "", 1 };
		CommonListBox knobBox{ "", 3 };
		CommonListBox midiBox{ "", 3 };
		CommonListBox trackControlValue{ "", 2 };

		IgniteTrackValues* valuePtr;
		juce::Viewport view;
		juce::Component container;
		Array<CommonToggleButton*> options;
		CommonNumber minValue{ "MIN VALUE",minMidi,maxMidi,minMidi,false,1 };
		CommonNumber initValue{ "INIT VALUE",minMidi,maxMidi,minMidi,false,1 };
		CommonNumber maxValue{ "MAX VALUE",minMidi,maxMidi,maxMidi,false,1 };
		CommonNumber bankLSB{ "Bank LSB",minMidi,maxMidi,minMidi,false,1 };
		CommonNumber bankMSB{ "Bank MSB",minMidi,maxMidi,minMidi,false,1 };
		CommonImageButton Midicc{ "Midicc","btn-midicc-default.png","btn-midicc-active.png","btn-midicc-default-hover.png" };
		CommonImageButton PgmCtr{ "PgmCtr","btn-progchange-default.png","btn-progchange-active.png","btn-progchange-default-hover.png" };
		CommonImageButton ctlApply{ "ctlApply","btn-apply-174x44-default-hover.png","btn-apply-174x44-default-hover.png","btn-apply-174x44-default.png" };
		CommonImageButton ctlCancel{ "ctlCancel","btn-cancel-174x44-default-hover.png","btn-cancel-174x44-default-hover.png","btn-cancel-174x44-default.png" };
		CommonImageButton ctlclear{ "ctlclear","btn-clearvalue-174x44-default-hover.png","btn-clearvalue-174x44-default-hover.png","btn-clearvalue-174x44-default.png" };
		std::vector<juce::String> valueList{ "NONE","MIDI CC","Program Change" };
		std::vector<juce::String> MidiCcValues{ "cc #0","cc #1", "cc #2", "cc #3", "cc #4", "cc #5", "cc #6", "cc #7", "cc #8", "cc #9","cc #10",
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
												"cc #121", "cc #122", "cc #123", "cc #124", "cc #125", "cc #126", "cc #127" };

		std::vector<juce::String> trackControlValues = { "pgm","quant % ", "note % ", "noteC","velo%", "veloC", "leng%", "tbase", "xpos", "octave", "knob1",
														"knob2", "fts-R", "fts-S", "reich","NONE" };
		int8 selection_state{ -1 };
		int currentFocus{ -1 };
		CommonWarningPopUp* warnPopupPtr = nullptr;
		IgniteControlOptions* optPtr = nullptr;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackValueSelection)
	};
};