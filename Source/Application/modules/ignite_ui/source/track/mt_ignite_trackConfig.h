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
	class AppDnp;
	class TrackMixer;

	class IgniteTrackConfig :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define TRACK_MENU_VIEW 3
#define TRACK_OPT_VIEW 4
		enum TrackMenuViewItemID
		{
			NO_FOCUS = 0,
			AUTO_SAVE, //Row 1
			TRACK_MIXER,
			FOCUS_MAX = TRACK_MIXER
		};
		enum TRACKCONFIG_FOCUS
		{
			TRACKCONFIG_DETAIL,
			TRACKCONFIG_OPTION,
		};

		enum TrackOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OPT_SCENELIST,
			OP_FOCUS_MAX = OPT_SCENELIST
		};

		uint8_t option_handler_focus = TRACKCONFIG_DETAIL;
		uint8_t OptionsView[TRACK_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OPT_SCENELIST,OP_FOCUS_MAX };
		int OptFocusedItem = OPT_UNDO;
		uint8_t TrackMenuView[TRACK_MENU_VIEW] = { NO_FOCUS, AUTO_SAVE, TRACK_MIXER };
		int KeyFocusedItem = TrackMenuViewItemID::NO_FOCUS;
		bool trackConfigDataUpdated = false;
		IgniteControlOptions* trackOptCtl = nullptr;

		IgniteTrackConfig();
		~IgniteTrackConfig() override;
		bool isAutoSaveEnabled() { return autoSaveTrack; }
		void enableControlButton(IgniteControlOptions::eKey key, bool state);
		void updateData();
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void mouseUp(const MouseEvent& event) override;

		static IgniteTrackConfig* GetAppTrackConfigInstance()
		{
			static IgniteTrackConfig* GetAppTrackConfigObj;
			if (NULL == GetAppTrackConfigObj)
			{
				GetAppTrackConfigObj = new IgniteTrackConfig();
			}

			return GetAppTrackConfigObj;
		}

	private:
		TrackMixer* mixerComp = nullptr;
		CommonImageButton autoSaveBtn{ "Auto Save:off","toggle-autosave-default.png","toggle-autosave-active.png","toggle-autosave-default-hover.png"};
		CommonImageButton trackMixer{ "Tracks Instrument Mixer","btn-track-inst-mixer-default.png","btn-track-inst-mixer-default.png","btn-track-inst-mixer-hover.png"};
		
		bool autoSaveTrack = false;
		CommonPopUp* popupPtr = nullptr;
		bool isAutosave = false;

		juce::FlexBox trackMenuBox1;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTrackConfig)
	};
};
