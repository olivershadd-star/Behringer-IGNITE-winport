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

using namespace ignite_Constants;
namespace ui
{
	class AppOptions;
	class IgniteRecordModale;
	class IgniteMiscSettings;
	class IgniteControlOptions : public juce::Component,
		public ui::CommonToggleButton::Listener
	{

	public:
		enum eKey {
			PLAY,
			STOP,
			SAVE,
			COPY,
			UNDO,
			LOOP,
			MOVE,
			REC,
			DEL,
			FILLMODE,
			CONFIG,
			MOVEUP,
			MOVEDOWN,
			MOVETOP,
			MOVEBTM,
			AUTOSAVE,
			SONGLIST,
			SCENELIST,
			TRACKVIEW,
			PATSTEP,
			PATBAR,
			PATGRID,
			REVERSE,
			MIDI_GLOBAL,
			MIDI_SONG,
			CV_GLOBAL,
			CV_SONG,
			MIDI_SONG_CONFIG,
			CVIO_SONG_CONFIG,
			SONG_SETTING_GLOBAL,
			SONG_SETTING_ACTIVE,
			PATTERN,
			INST,
			TRACK_CTL,
			ALT_FN,
			SAVEALLON,
			SAVEALLOFF,
			AUTOSAVEON,
			AUTOSAVEOFF,
			ALL
		};
		IgniteControlOptions();
		~IgniteControlOptions() override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void enableKey(eKey option, bool state);
		void playKeyBlinkCtrl(bool state) { state ? playButton.setAlpha(1.0f) : playButton.setAlpha(0.3f);}
		void recordKeyBlinkCtrl(bool state) { state ? recButton.setAlpha(1.0f) : recButton.setAlpha(0.3f); }
		mt::Ignite::operatioMode getOperationMode() { return opMode; };
		void setOperationMode(mt::Ignite::operatioMode mode) { opMode = mode; }
		void setPlayButtonMode() { (bool)opMode ? playButton.setToggleState(false, sendNotification) : playButton.setToggleState(true, sendNotification); }
		void setRecButtonMode(bool state) { state ? recButton.setToggleState(true, dontSendNotification) : recButton.setToggleState(false, sendNotification); }
		void onCtrlOptnClick(eKey option);
		void handleCommandMessage(int id);
		//Image getSnapShot();
		void updatePlayBtnState();
		void updateRecBtnState();
		void sendSaveAllNotification();
		void sendDeleteforAllListners();


		static IgniteControlOptions* GetAppOptInstance()
		{
			static IgniteControlOptions* GetInstance;
			if (NULL == GetInstance)
			{
				GetInstance = new IgniteControlOptions();
			}

			return GetInstance;
		}

		class Listener
		{
		public:
			virtual ~Listener() = default;
			virtual void onOptCtlButtonClicked(eKey option) = 0;
		};
		void addOptCtlListener(Listener* listener);
		void removeOptCtlListener(Listener* listener);
		bool PannelKeyHandler(eKey, bool, paramId_t param, uint32_t KeyValue);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool SaveStatusChanged(eKey option,bool state);
		void setSafeStopStatus(bool status) { isSafeStopEnabled = status; };
		bool isEditing = false;
		bool isSaveallEnabled = false;
		bool isAutoSaveEnabled = false;
		bool isSavePopUpOn = false;
		bool isDeletePopUpOn = false;
		bool isSafeStopEnabled = false;
		uint8_t safeStopCount = 0;
	private:
		juce::FlexBox ctlBox;
		juce::FlexBox ctrBox1;
		juce::ListenerList<Listener> listeners;
		ui::CommonToggleButton revButton{ };
		ui::CommonImageButton playButton{"", "btn-play-default.png", "btn-pause-active.png", "btn-play-default-hover.png" };
		ui::CommonToggleButton stopButton{ };
		ui::CommonImageButton recButton{"", "btn-record-default.png", "btn-record-active.png", "btn-record-default-hover.png"};
		ui::CommonToggleButton saveButton{ };
		ui::CommonToggleButton delButton{  };
		mt::Ignite::operatioMode opMode = mt::Ignite::operatioMode::IDLE_MODE;
		AppOptions* optionsPtr = nullptr;
		IgniteRecordModale* RecordPtr = nullptr;
		CommonPopUp* popupPtr = nullptr;
		IgniteMiscSettings* MiscPtr = nullptr;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteControlOptions)
	};
};
