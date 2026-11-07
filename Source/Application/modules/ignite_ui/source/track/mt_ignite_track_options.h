/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY
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
using namespace ignite_Constants;
namespace ui
{
	class IgniteTrack;
	class IgniteTrackValues;
	class AppTrackOpt : public juce::Component,
		public juce::Button::Listener,
		public CommonLabel::Listener,
		public juce::ModalComponentManager
	{
	public:
		AppTrackOpt(IgniteTrack* ptr);
		~AppTrackOpt() override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		virtual void labelTextChanged(Label* labelThatHasChanged) override;
		void refreshData();
		void handleInstrumentDefinition(bool isInput, int index);
		void handlePattern(int index);
		void handleFillPattern(int index);
		void addToPatternList(String pattern_name);
		void addToFillList(String pattern_name);
		void updatePatternBox(std::list<std::string> patternNameList);
		void updateInstrumentBox(std::vector<IgniteParamList>);
		void updateFillPatternBox(std::list<std::string> patternNameList);
		void updateLableText(mt::Ignite::trackDataIndex item_id, bool state);
		int getPatternIndex(String PatternName);
		bool isAssingedPatternValid(String pattern_name);
		bool isAssingedFillPatternValid(String fillpattern_name);
		bool isAssingedInstrumentValid(String instr_name);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool PannelKeyAction(bool Focus, paramId_t param, uint32_t KeyValue);
		void updateTrackEditIndication();
		bool PannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);

		static AppTrackOpt* GetAppTrackOptionsInstance(IgniteTrack* ptr)
		{
			static AppTrackOpt* instanceAppTrackOpt;
			if (NULL == instanceAppTrackOpt)
			{
				instanceAppTrackOpt = new AppTrackOpt(ptr);
			}
			return instanceAppTrackOpt;
		}

	private:
#define TRACK_OPTIONS_VIEW 4
		enum TrackOptionsViewItemID
		{
			NO_FOCUS = 0,
			TRACK_INSTRUMENT,
			TRACK_PATTERN,
			TRACK_UNDO,
			FOCUS_MAX = TRACK_UNDO
		};
		uint8_t OptionsView[TRACK_OPTIONS_VIEW] = { NO_FOCUS, TRACK_INSTRUMENT, TRACK_PATTERN, TRACK_UNDO };
		int KeyFocusedItem = TrackOptionsViewItemID::NO_FOCUS;
		bool track_option_handler_enabled = false;

		IgniteTrack* _pTrack = nullptr;
		IgniteTrackValues* trackValueptr = nullptr;
		CommonWarningPopUp* warnPopupPtr = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;
		IgniteScene* scenePtr = nullptr;

		CommonButton trackValueBtn{ "Track FX" };
		CommonToggleButton soloMode{ "SOLO : Disabled" };
		CommonToggleButton trackMuteBtn{ "Track : Disabled" };
		CommonToggleButton trackRecBtn{ "Record : Disabled" };
		CommonKey header{ "Track Name" };
		CommonImageButton back{ " Back ", "back-default.png","back-active.png","back-default-hover.png"};

		juce::FlexBox paramBox1;
		juce::FlexBox paramBox2;
		juce::FlexBox paramBox3;

		CommonListBox instrumentOutBox{ "Output Instrument", 1, true };
		CommonListBox instrumentInBox{ "Input Instrument", 1, true };
		std::vector<juce::String> instrumentList{ "Add New Instrument" };
		std::vector<juce::String> instrumentFSNameList{ "Add New Instrument" };//Store Instrument FS name list

		CommonListBox patternBox{ "Pattern", 1, true };
		std::vector<juce::String> patternList{ "Add New Pattern" }; //Store Pattern Disp name list
		std::vector<juce::String> patternFSNameList{ "Add New Pattern" }; //Store Pattern FS name list

		CommonListBox pFillBox{ "Fill Pattern", 1, true };
		std::vector<juce::String> pFillList{ "No Pattern" };

		CommonListBox pTrackValuesBox{ "Track Instrument Values", 1 };
		std::vector<juce::String> pTrackValuesList{ "Add Track Instrument Values" };

		int id = 0, pid = 0, pfid = 0;
		int FocusedIndex = -1;
		bool isTrackSelected;
		bool isThereExistingTrack;
		bool trackSelected;
		int getIndexs(mt::Ignite::trackDataIndex index, String name);
		void setTrackBtnState(bool state);
		void setTrackSoloBtnState(bool state);
		void setTrackRecBtnState(bool state);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppTrackOpt)
	};
};
