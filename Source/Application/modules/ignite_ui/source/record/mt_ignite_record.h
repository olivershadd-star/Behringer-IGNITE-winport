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

	class IgniteRecord :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define RECORD_MENU_VIEW 10
#define RECORD_OPT_VIEW 3
#define RECORD_ROW_ITEMS 3
		enum RecordMenuViewItemID
		{
			NO_FOCUS = 0,
			QUANTIZATION, //Row 1
			//MTHRU,
			//FTS,
			//AUTO_ADD_BARS, //Row 2
			BAR_OVERWRITE,
			NUMBER_OF_BARS,
			NOTE_EVENTS, //Row 3
			CC_EVENTS,
			AFT_TOUCH_EVENT,
			PITCH_BEND_EVENT, //Row 4
			POLY_P_EVENT,
			PROGRAM_CHANGE_EVENT,
			FOCUS_MAX = PROGRAM_CHANGE_EVENT
		};
		enum RECCONFIG_FOCUS
		{
			RECCONFIG_DETAIL,
			RECCONFIG_OPTION,
		};

		enum RecOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OP_FOCUS_MAX = OPT_UNDO
		};

		uint8_t option_handler_focus = RECCONFIG_DETAIL;
		uint8_t OptionsView[RECORD_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OP_FOCUS_MAX };
		int OptFocusedItem = OPT_UNDO;
		uint8_t RecordMenuView[RECORD_MENU_VIEW] = { NO_FOCUS, QUANTIZATION, /*MTHRU, FTS, AUTO_ADD_BARS,*/ BAR_OVERWRITE, NUMBER_OF_BARS, NOTE_EVENTS, CC_EVENTS, AFT_TOUCH_EVENT, PITCH_BEND_EVENT, POLY_P_EVENT, PROGRAM_CHANGE_EVENT };
		int KeyFocusedItem = RecordMenuViewItemID::NO_FOCUS;

		bool recordConfigDataUpdated = false;
		IgniteControlOptions* recordOptCtl = nullptr;

		IgniteRecord();
		~IgniteRecord() override;
		void updateData();
		int isEditing();
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void getAssets();
		static IgniteRecord* GetAppRecordInstance()
		{
			static IgniteRecord* GetAppRecordObj;
			if (NULL == GetAppRecordObj)
			{
				GetAppRecordObj = new IgniteRecord();
			}

			return GetAppRecordObj;
		}

	private:
		CommonImageButton quantBtn{ "Quantization:Off","toggle-quantization-default.png","toggle-quantization-active.png","toggle-quantization-default-hover.png"};
		//CommonImageButton mthruBtn{ "Mthru:Off","toggle-mthru-default.png","toggle-mthru-active.png","toggle-mthru-default-hover.png"};
		//CommonImageButton ftsBtn{ "FTS:Off","toggle-fts-default.png","toggle-fts-active.png","toggle-fts-default-hover.png" };
		//CommonImageButton autoAddBarBtn{ "Auto Add Bars:Off","toggle-addautobars-default.png","toggle-addautobars-active.png","toggle-addautobars-default-hover.png"};
		CommonImageButton barOverwriteBtn{ "Bar OverWrite:Off","toggle-barovewrite-default.png","toggle-barovewrite-active.png","toggle-barovewrite-default-hover.png"};
		CommonNumber maxBars{ "Number of Bars", 1, 16, 1 };
		CommonNameLabel eventFilterLable{ "Event Filters:" };
		CommonImageButton noteEvtBtn{ "NOTE EVENTS:Off","toggle-noteevents-default.png","toggle-noteevents-active.png","toggle-noteevents-default-hover.png" };
		CommonImageButton ctrlEvtBtn{ "MIDI CC EVENTS:Off","toggle-midicc-default.png","toggle-midicc-active.png","toggle-midicc-default-hover.png" };
		CommonImageButton aftEvtBtn{ "AFT TOUCH EVENT:Off","toggle-afttouch-default.png","toggle-afttouch-active.png","toggle-afttouch-default-hover.png"};
		CommonImageButton bendEvtBtn{ "PITCH BEND EVENT:Off","toggle-pitchblend-default.png","toggle-pitchblend-active.png","toggle-pitchblend-default-hover.png" };
		CommonImageButton polypEvtBtn{ "POLY-P EVENT:Off","toggle-polyp-default.png","toggle-polyp-active.png","toggle-polyp-default-hover.png"};
		CommonImageButton prgmEvtBtn{ "PROGRAM CHANGE EVENT:Off","toggle-pce-default.png","toggle-pce-active.png","toggle-pce-default-hover.png" };
		juce::FlexBox recordBox1;
		juce::FlexBox recordBox2;
		Image imageDefault, imagehover, imageDisabled;
		juce::FlexBox filterBox1;
		juce::FlexBox filterBox2;
		juce::FlexBox filterBox3;
		CommonPopUp* popupPtr = nullptr;
		bool isAutosave = false;

		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void setEventFilterValue(uint16_t value, bool state);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteRecord)
	};
};
