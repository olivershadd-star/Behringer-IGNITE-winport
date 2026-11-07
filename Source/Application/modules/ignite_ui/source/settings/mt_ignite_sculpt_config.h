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
	class IgniteSculptConfig :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
		enum class sculptMode {
			SCULPT_REL,
			SCULPT_ABS,
			RANDOM_REL,
			RANDOM_ABS,
			INVALID,
		};
		enum SCULPTCONFIG_FOCUS
		{
			SCULPTCONFIG_DETAIL,
			SCULPTCONFIG_OPTION,
		};

		enum sculptOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OPT_PATSTEP,
			OPT_PATBAR,
			OPT_PATGRID,
			OP_FOCUS_MAX = OPT_PATGRID
		};

#define Sculpt_MENU_VIEW 12
#define SCULPT_OPT_VIEW  6
		enum SculptMenuViewItemID
		{
			NO_FOCUS = 0,
			SCULPT_REL,
			SCULPT_ABS,
			RANDOM_REL,
			RANDOM_ABS,
			SCULPT_ALL_PARAM,
			SCULPT_VELO_PARAM,
			/*SCULPT_LEN_ST_PARAM,
			SCULPT_LEN_TK_PARAM,*/
			SCULPT_NOTE_PARAM,
			SCULPT_VELO,
			/*SCULPT_LEN_ST,
			SCULPT_LEN_TK,*/
			SCULPT_DELAY,
			RANDOM_VELO,
			/*RANDOM_LEN_ST,
			RANDOM_LEN_TK,*/
			RANDOM_DELAY,
			FOCUS_MAX = RANDOM_DELAY
		};
		uint8_t SculptMenuView[Sculpt_MENU_VIEW] = { NO_FOCUS, SCULPT_REL, SCULPT_ABS, RANDOM_REL, RANDOM_ABS, SCULPT_ALL_PARAM, SCULPT_VELO_PARAM, /*SCULPT_LEN_ST_PARAM,
			SCULPT_LEN_TK_PARAM,*/ SCULPT_NOTE_PARAM, SCULPT_VELO, /*SCULPT_LEN_ST, SCULPT_LEN_TK,*/ SCULPT_DELAY, RANDOM_VELO, /*RANDOM_LEN_ST, RANDOM_LEN_TK,*/ RANDOM_DELAY };
		int KeyFocusedItem = SculptMenuViewItemID::NO_FOCUS;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();

		uint8_t optionHandlerFocus = SCULPTCONFIG_DETAIL;
		uint8_t sculptOptionsMenuView[SCULPT_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OPT_PATSTEP,OPT_PATBAR,OPT_PATGRID,OP_FOCUS_MAX };
		int optFocusedItem = OPT_UNDO;

		bool sculptConfigDataUpdated = false;
		IgniteControlOptions* sculptOptCtl = nullptr;

		IgniteSculptConfig();
		~IgniteSculptConfig() override;
		void loadDataFromEngine();
		sculptMode getSculptMode();
		uint8_t getSculptParamConfig();
		void loadSculptParams();
		void updateData(sculptMode mode);
		void setSculptMode(sculptMode mode);
		void enableControlButton(IgniteControlOptions::eKey key, bool state)
		{
			sculptOptCtl->enableKey(key, state);
		}
		static IgniteSculptConfig* GetAppSculptInstance()
		{
			static IgniteSculptConfig* GetAppSculptObj;
			if (NULL == GetAppSculptObj)
			{
				GetAppSculptObj = new IgniteSculptConfig();
			}

			return GetAppSculptObj;
		}

	private:
		CommonLabel modeLable{ "Sculpt Mode" };
		CommonLabel valueLable{ "Parameter Values for Sculpt Relative Mode" };
		CommonLabel veloLable{ "Velocity" };
		//CommonLabel lenStepLable{ "Length (Step)" };
		//CommonLabel lenTickLable{ "Length (Tick)" };
		CommonLabel noteLable{ "Note" };
		CommonLabel paramLable{ "Params:" };

		juce::FlexBox ctlBox1;
		juce::FlexBox ctlBox2;
		juce::FlexBox valueBoxTitle;
		juce::FlexBox paramBox;

		CommonImageButton sculptRelBtn{ "Sculpt Relative","btn-relative-245x50-default.png","btn-relative-245x50-active.png","btn-relative-245x50-default-hover.png" };
		CommonImageButton sculptAbsBtn{ "Sculpt Absolute","btn-absolute-245x50-default.png","btn-absolute-245x50-active.png","btn-absolute-245x50-default-hover.png" };
		CommonImageButton randomRelBtn{ "Random Relative","btn-random-relative-245x50-default.png","btn-random-relative-245x50-active.png","btn-random-relative-245x50-default-hover.png" };
		CommonImageButton randomAbsBtn{ "Random Absolute","btn-random-absolute-245x50-default.png","btn-random-absolute-245x50-active.png","btn-random-absolute-245x50-default-hover.png" };

		CommonImageButton paramAllBtn{ "All","toggle-all-160x44-default.png","toggle-all-160x44-active.png","toggle-all-160x44-default-hover.png" };
		CommonImageButton paramVeloBtn{ "Velocity","toggle-velocity-160x44-default.png","toggle-velocity-160x44-active.png","toggle-velocity-160x44-default-hover.png" };
		//CommonImageButton paramLenStepBtn{ "Len-Step","toggle-lenstep-160x44-default.png","toggle-lenstep-160x44-active.png","toggle-lenstep-160x44-default-hover.png" };
		//CommonImageButton paramLenTickBtn{ "Len-Tick","toggle-lentick-160x44-default.png","toggle-lentick-160x44-active.png","toggle-lentick-160x44-default-hover.png" };
		CommonImageButton paramNoteBtn{ "Note","toggle-note-160x44-default.png","toggle-note-160x44-active.png","toggle-note-160x44-default-hover.png" };


		CommonNumber veloStartValue{ "Velocity", 0, 127, 0 };
		//CommonNumber lenStepStartValue{ "Length(Step)", 0, 95, 0 };
		//CommonNumber lenTickStartValue{ "Length(Tick)", 0, 31, 0 };
		CommonNumber noteStartValue{ "Note", 0, 127, 0 };

		CommonNumber veloEndValue{ "Velocity Range: End", 0, 127, 127 };
		//CommonNumber lenStepEndValue{ "Length(Step): End", 0, 95, 0 };
		//CommonNumber lenTickEndValue{ "Length(Tick): End", 0, 31, 0 };
		CommonNumber noteEndValue{ "Note Range: End", 0, 127, 127 };

		uint8_t sculpt_params = 0;
		CommonPopUp* popupPtr = nullptr;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void setParamValueTitle(bool isValueRange);
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void setSculptParams(SculptParameterSelect param, bool state);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteSculptConfig)
	};
};
