/*
* Copyright (C) Musictribe Innovation India Pvt. Ltd
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
	class TrackMixer :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
		bool trackMixerDataUpdated = false;
		IgniteControlOptions* trackMixerOptCtl = nullptr;
#define TRACK_MIXER_ITEMS 5
#define TRACK_MIXER_OPT_ITEMS 3
#define TRACK_MIXER_PAN_MAX 128
		enum TRACKMIXER_FOCUS
		{
			TRACKMIXER_PARAM,
			TRACKMIXER_OPTIONS,
			TRACKMIXER_TRACKS
		};
		enum TrackMixerViewItemID
		{
			NO_FOCUS = 0,
			VOLUME_PARAM,
			PAN_PARAM,
			LEFT_NUDGE,
			RIGHT_NUDGE,
			FOCUS_MAX = RIGHT_NUDGE
		};
		enum TrackMixerOptionsViewItemID
		{
			OPT_NO_FOCUS = 0,
			OPT_UNDO,
			OPT_TRACKVIEW,
			OPT_FOCUS_MAX = OPT_TRACKVIEW
		};
		uint8_t TrackMixerViewItems[TRACK_MIXER_ITEMS] = { NO_FOCUS, VOLUME_PARAM, PAN_PARAM, LEFT_NUDGE, RIGHT_NUDGE };
		uint8_t OptionsView[TRACK_MIXER_OPT_ITEMS] = { OPT_NO_FOCUS,OPT_UNDO,OPT_TRACKVIEW };
		int KeyFocusedItem = TrackMixerViewItemID::NO_FOCUS;
		int OptFocusedItem = OPT_UNDO;
		uint8_t option_handler_enabled = TRACKMIXER_PARAM;

		TrackMixer();
		~TrackMixer() override;
		static TrackMixer* GetTrackMixerInstance()
		{
			static TrackMixer* GetTMInstance;
			if (NULL == GetTMInstance)
			{
				GetTMInstance = new TrackMixer();
			}

			return GetTMInstance;
		}
		void paint(juce::Graphics& g) override;
		virtual void resized() override;
		juce::Rectangle<float> getLevelButtonRect(int index);
		juce::Rectangle<float> getStepButtonRect(int index);
		virtual void mouseDrag(const MouseEvent& event) override;
		virtual void mouseUp(const MouseEvent& event) override;
		virtual void mouseDown(const MouseEvent& event) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void updateLableText(mt::Ignite::ptDataIndex item_id, bool state);
		var getParamValues(int index);
		TrackMixerControl& getTrackMixerControl() { return trackMixerControl; };
		void refreshTrackMixerUI();
		int trackBankIndex = 0;
		juce::String getActiveParamControl() { return sparamListValue; }
		void setActiveParamControl(juce::String param) { sparamListValue = param; }
		void setThreshold(int8_t value) { param_threshold = value - 1; }
		uint8_t getThreshold() { return param_threshold; }
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		bool PannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendOptionsKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		bool TrackKeyHandler(paramId_t param, uint32_t KeyValue);
		void getTrackMixerBankAndUpdate(bool direction);
		void getSelectedTrackMixerBankAndUpdate(int trackMixerBank);

	private:
		void cleanup();
		void updateTrackData();
		void calculateButtonWidth();
		void enableDisableButton(juce::Point<float> position);
		void setParamToEngine(juce::String param, int index, int8_t data);
		int8_t getParamFromEngine(juce::String param, int index);
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void setTrackMixerValues(paramId_t param, int index);
		int isEditing();
		bool setSelectedTrackMixerValue(paramId_t param, uint32_t KeyValue, int index);

	private:

		std::map<juce::String, mt::Ignite::nodeDataIndex> s_mapStringToParamValueType =
		{
			{ "Volume",       mt::Ignite::nodeDataIndex::VELO },
			{ "Pan",  mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP},
		};

		std::map<juce::String, int> s_mapStringToParamMaxType =
		{
			{ "Volume",       maxVelocity},
			{ "Pan",  TRACK_MIXER_PAN_MAX},
		};

		TrackMixerControl trackMixerControl;
		StepPresets stepPreset;
		juce::String sparamListValue = "Volume";

		juce::Rectangle<float> stepRect;
		juce::Rectangle<float> levelRect;
		float buttonWidth = 0;
		int rangeLow = 0;
		int rangeHigh = 0;
		int lastIndex = -1;
		int currentNote = 0;
		int currentBar = 1;
		int startIndex = 0;
		uint8_t param_threshold = 127;
		std::vector<bool> selectedIndex{ false };
		int selected_track = -1;
		bool selectedTrackInTrackMixer[64]{ false };
		CommonPopUp* popupPtr = nullptr;

		bool* getTrackMixerTrackState() { return selectedTrackInTrackMixer; }
		void resetTrackMixerTrackState()
		{
			for (auto i = 0; i < 64; i++)
				selectedTrackInTrackMixer[i] = false;
		}
	};
}