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
	class IgnitePattern;
	class IgniteSong;
	class IgniteScene;
	class IgniteTrack;
	class IgniteInstruments;
	class AppOptCtl : public juce::Component,
		public juce::Button::Listener
	{
	public:
		enum class pKey {
			BACK,
			SAVE,
			COPY,
			MOVE,
			DEL,
			MOVEUP,
			MOVEDOWN,
			MOVETOP,
			MOVEBTM,
		};
		std::function<void(pKey)> onButtonPressed;
		AppOptCtl(bool BACK = true, bool SAVE = true, bool DEL = true, bool COPY = true, bool MOVE = true);
		~AppOptCtl() override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void updateButtons();
		void setButtonName(pKey, String new_name);

	private:
		juce::FlexBox ctlBox;
		bool backButton, saveButton, copyButton, moveButton, delButton;

		CommonButton optionSave{ "SAVE" };
		CommonButton optionCopy{ "COPY" };
		CommonButton optionMove{ "MOVE" };
		CommonButton rowDelete{ "DELETE" };
		CommonButton optionBack{ "BACK" };

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppOptCtl)
	};

	class AppOptions : public juce::Component,
		public juce::Button::Listener
	{
	public:
		enum viewType {
			Vertical = 0,
			horizontal
		};

		CommonImageButton optionMove{"Move","btn-move-default.png","btn-move-active.png","btn-move-default-hover.png" };

		AppOptions();
		~AppOptions() {};
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void showOptions(bool state);
		void enableKey(IgniteControlOptions::eKey option, bool state);
		void setView(bool loop = true, bool copy = true, bool move = true, bool undo = true, bool fillmode = false, bool autosave = false);
		void taboptionChanges(mt::Ignite::tabs t, int subtab);
		void enableMoveoptions(mt::Ignite::tabs a, int subtab, bool state);
		void changebtnstate(IgniteControlOptions::eKey option, bool state);
		bool getBtnState(IgniteControlOptions::eKey option);
		bool PannelKeyHandler(IgniteControlOptions::eKey option, bool state, paramId_t param, uint32_t KeyValue);
		void updateAltFunBtnState() { altFunBtn.setVisible(trackCtlBtn.getToggleState()); }

		static AppOptions* GetOptionsInstance()
		{
			static AppOptions* GetInstance;
			if (NULL == GetInstance)
			{
				GetInstance = new AppOptions();
			}
			return GetInstance;
		}

	private:
		juce::FlexBox ctlBox;
		juce::FlexBox moveBox;

		CommonImageButton optionloop{ "loop" ,"btn-loop-default.png","btn-loop-active.png","btn-loop-default-hover.png" };
		CommonImageButton optionCopy{ "COPY" ,"btn-copy-default.png","btn-copy-active.png","btn-copy-default-hover.png" };
		CommonImageButton optionUndo{ "UNDO","btn-undo-default.png","btn-undo-active.png","btn-undo-default-hover.png" };
		CommonImageButton optionConfig{ "OptionConfig","btn-config-default.png","btn-config-active.png","btn-config-default-hover.png" };
		CommonImageButton movetoTop{ "MovetoTop","btn-movetotop-default.png","btn-movetotop-active.png","btn-movetotop-default-hover.png" };
		CommonImageButton movetoLast{ "MovetoLast","btn-movetobottom-default.png","btn-movetobottom-active.png","btn-movetobottom-default-hover.png" };
		CommonImageButton movetoDown{ "MovetoTop","btn-move1down-default.png","btn-move1down-active.png","btn-move1down-default-hover.png" };
		CommonImageButton movetoUp{ "MovetoLast","btn-move1up-default.png","btn-move1up-active.png","btn-move1up-default-hover.png" };
		CommonImageButton autoSave{ "AutoSave","btn-autosave-default.png","btn-autosave-active.png","btn-autosave-default-hover.png" };
		CommonImageButton SongList{ "SongList","btn-songlist-default.png","btn-songlist-active.png","btn-songlist-default-hover.png" };
		CommonImageButton SceneList{ "SceneList","btn-scenelist-default.png","btn-scenelist-default-hover.png","btn-scenelist-default-hover.png" };
		CommonImageButton TrackView{ "trackView","btn-trackview-default.png","btn-trackview-active.png","btn-trackview-default-hover.png" };
		CommonImageButton PatternStep{ "PatStep","btn-stepselection-default.png","btn-stepselection-active.png","btn-stepselection-default-hover.png" };
		CommonImageButton PatternBar{ "PatBar","btn-barselection-default.png","btn-barselection-active.png","btn-barselection-default-hover.png" };
		CommonImageButton PatternGrid{ "PatGrid","btn-gridselection-default.png","btn-gridselection-active.png","btn-gridselection-default-hover.png" };
		CommonImageButton btnInstrument{ "Inst","btn-instrument-default.png","btn-instrument-active.png","btn-instrument-default-hover.png" };
		CommonImageButton btnPattern{ "Pattern","btn-pattern-default.png","btn-pattern-active.png","btn-pattern-default-hover.png" };
		CommonImageButton midiGlobal{ "Default","btn-defaultsetting-default.png","btn-defaultsetting-active.png","btn-defaultsetting-default-hover.png" };
		CommonImageButton midiSong{ "Midi Active Song","btn-activesong-default.png","btn-activesong-active.png","btn-activesong-default-hover.png" };
		CommonImageButton songSettingGlobal{ "Song Default","btn-defaultsetting-default.png","btn-defaultsetting-active.png","btn-defaultsetting-default-hover.png"};
		CommonImageButton songSettingActive{ "Active Song","btn-activesong-default.png","btn-activesong-active.png","btn-activesong-default-hover.png" };
		CommonImageButton cvioGlobal{ "cvio Default","btn-defaultsetting-default.png","btn-defaultsetting-active.png","btn-defaultsetting-default-hover.png" };
		CommonImageButton cvioSong{ " cvio Active Song","btn-activesong-default.png","btn-activesong-active.png","btn-activesong-default-hover.png" };
		CommonImageButton songMidiConfig{ "MIDI Configuration","btn-midiconfig-default.png","btn-midiconfig-active.png","btn-midiconfig-default-hover.png" };
		CommonImageButton songCvioConfig{ "CVIO Configuration","btn-cvioconfig-default.png","btn-cvioconfig-active.png","btn-cvioconfig-default-hover.png" };
		CommonImageButton altFunBtn{ " ","btn-altfn-default.png","btn-altfn-active.png","btn-altfn-default-hover.png" };
		CommonImageButton trackCtlBtn{ " ","btn-extcc-default.png","btn-extcc-active.png","btn-extcc-default-hover.png" };

		IgnitePattern* appPatternComp = nullptr;
		IgniteSong* appSongComp = nullptr;
		IgniteScene* appSceneComp = nullptr;
		IgniteTrack* appTrackComp = nullptr;
		IgniteControlOptions* optCntPtr = nullptr;
		IgniteInstruments* appInstrComp = nullptr;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppOptions)
	};
};