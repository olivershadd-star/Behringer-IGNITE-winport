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
	class IgniteGateConfig;
	class IgniteCvConfig;
	class IgniteControlOptions;

	class IgniteCvio :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define CVIO_VIEW 3
#define CVIO_OPT  5
		enum CVIOItemID
		{
			NO_FOCUS = 0,
			CV_PORT,
			GATE_PORT,
			NEXT_VIEW,
			FOCUS_MAX = NEXT_VIEW
		};
		enum CVIOCONFIG_FOCUS
		{
			CVIO_DETAIL,
			CVIO_OPTION
		};

		enum MIDIOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OP_UNDO,
			OP_DEFULT,
			OP_ACTIVE_SONG,
			OP_FOCUS_MAX = OP_ACTIVE_SONG
		};

		uint8_t option_handler_focus = CVIO_DETAIL;
		uint8_t OptionsView[CVIO_OPT] = { OP_NO_FOCUS,OP_UNDO,OP_DEFULT,OP_ACTIVE_SONG,OP_FOCUS_MAX };
		int OptFocusedItem = OP_UNDO;

		uint8_t CVIO_Config[CVIO_VIEW] = { NO_FOCUS, CV_PORT, GATE_PORT };
		int KeyFocusedItem = CVIOItemID::NO_FOCUS;
		bool cvioConfigDataUpdated = false;

		IgniteCvio();
		~IgniteCvio() override;
		void  refreshUI();
		void enableControlButton(IgniteControlOptions::eKey key, bool state);
		void setActivePort(uint8_t port) { active_port = port; }
		uint8_t getActivePort() { return active_port; }
		void setDefaultOutputPort();
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		CommonImageButton cvbtn{ "CV Output Port","btn-cvoutput-default.png","btn-cvoutput-active.png","btn-cvoutput-default-hover.png" };
		CommonImageButton gatebtn{ "Gate Output Port","btn-gateport-default.png","btn-gateport-active.png","btn-gateport-default-hover.png" };


		static IgniteCvio* GetAppCvioInstance()
		{
			static IgniteCvio* GetAppCvioObj;
			if (NULL == GetAppCvioObj)
			{
				GetAppCvioObj = new IgniteCvio();
			}

			return GetAppCvioObj;
		}

	private:
		IgniteCvConfig* cvObject;
		IgniteGateConfig* gateObject;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void saveCvConfigSettings(int8_t SaveLocation);
		uint8_t active_port = 0;
		bool isAutosave = false;
		IgniteControlOptions* cvioOptCtl = nullptr;
		CommonPopUp* popupPtr = nullptr;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCvio)
	};

	class IgniteCvConfigContainer : public  juce::Component
	{
	private:
		juce::Array<juce::Component*> compList;
		int containerOffset;

	public:
		IgniteCvConfigContainer();
		~IgniteCvConfigContainer() override;
		void resized() override;
		void setOffset(int offset);
		void addChildComp(juce::Component* pComp);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCvConfigContainer)
	};


	class IgniteCvConfig :
		public juce::Component,
		public juce::Button::Listener, public common_rotaryslider::Listener, public CommonViewport::Listener
	{
#define NO_OF_ENVOLOPE_SLIDER 5
#define CV_LEFT_FOCUSE 9
#define CV_CHANNEL_FOCUSE 10
#define CVLAW_CHANNEL_FOCUSE 9
#define CVGATE_FOCUSE 12
#define CVCCLIST_FOCUSE 13
#define CVSLIDE_FOCUSE 14
#define SLIDETIME_FOCUSE 15
#define CVNOTERANGESTART_FOCUSE 10
#define CV_RIGHT_FOCUSE 17
#define CVNOTERANGEEND_FOCUSE 11
#define CVNOTESELECTION_FOCUSE 12
#define CVOUTPUT_FOCUSE 13

		enum EnvlopType
		{
			ATTACK,
			DECAY,
			SUSTAIN,
			RELEASE,
			AMOUNT,
			VELOCITY
		};

		enum MoveDirection
		{
			MOVE_LEFT,
			MOVE_RIGHT,
		};

	public:
#define CV_CONFIG_VIEW 14
		enum  CVConfigItemID
		{
			NO_FOCUS = 0,
			CV_PORT1,
			CV_PORT2,
			CV_PORT3,
			CV_PORT4,
			CV_PORT5,
			CV_PORT6,
			CV_PORT7,
			CV_PORT8,
			//CV_LEFT,
			//CV_CHANNEL,
			CV_LAW,
			//CV_GATE,
			//CV_CC,
			//CV_SLIDE,
			//CV_TIME,
			CV_NOTE_START,
			//CV_RIGHT,
			CV_NOTE_END,
			CV_NOTE_SELECTION,
			CV_OUTPUT,
			FOCUS_MAX = CV_OUTPUT
		};

		uint8_t CV_Config[CV_CONFIG_VIEW] = { NO_FOCUS,CV_PORT1, CV_PORT2,CV_PORT3,CV_PORT4,CV_PORT5,CV_PORT6,CV_PORT7,CV_PORT8,/* CV_LEFT, CV_CHANNEL,*/ CV_LAW, /*CV_GATE,*/
			/*CV_CC , CV_SLIDE , CV_TIME,*/ CV_NOTE_START,/* CV_RIGHT,*/ CV_NOTE_END, CV_NOTE_SELECTION, CV_OUTPUT };
		int KeyFocusedItem = CVConfigItemID::CV_PORT1;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();
		int current_slider = 0;
		IgniteCvConfig();
		~IgniteCvConfig() override;
		void updateAccidentals(bool state);
		void updateCvData();
		void updateCvOutputPort();
		void showEnvolopSliders(bool state);
		void getAssets();
		static IgniteCvConfig* GetAppCvInstance()
		{
			static IgniteCvConfig* GetAppCvObj;
			if (NULL == GetAppCvObj)
			{
				GetAppCvObj = new IgniteCvConfig();
			}

			return GetAppCvObj;
		}

	private:
		CommonNameLabel cvConfigLable{ "CV Output Port: " };
		CommonButton cvPort1{ "1" };
		CommonButton cvPort2{ "2" };
		CommonButton cvPort3{ "3" };
		CommonButton cvPort4{ "4" };
		CommonButton cvPort5{ "5" };
		CommonButton cvPort6{ "6" };
		CommonButton cvPort7{ "7" };
		CommonButton cvPort8{ "8" };
		//CommonNumber cvChannel{ "Channel", 0, 15, 0, 1 };
		//CommonImageButton moveLeft{ "Move Left","cvio-caret-left-default.png","cvio-caret-left-hover.png","cvio-caret-left-hover.png" };
		//CommonImageButton moveRight{ "Move Right","cvio-caret-right-default.png","cvio-caret-right-hover.png","cvio-caret-right-hover.png" };

		CommonNumber cvNote{ "Note %", 0, 100, 0, 1 };
		//CommonListBox cvCCList{ "CC",  {mt::Ignite::midiccVal}, 0, 4 };
		CommonListBox cvNoteRangeStart{ "Note Range Start", {mt::Ignite::midiNoteNamesSharps}, 0, 4 };
		CommonListBox cvNoteRangeEnd{ "Note Range End", {mt::Ignite::midiNoteNamesSharps}, 127, 4 };

		CommonNumber cvVelocity{ "Velocity %", 0, 100, 0, 1 };
		CommonNumber cvCCCtrl{ "Control %", 0, 100, 0, 1 };
		CommonNumber cvPitchBend{ "Pitch Bend", -8192, 8191, 0 };
		//CommonNumber slideTime{ "Time", 0, 127, 0 };

		CommonListBox cvLaw{ "Law", {"V/Oct", "Hz/V","Envelope"}, 0, 1 };
		//CommonListBox cvSlide{ "Slide Mode", {"Off", "Liner", "Exponential"}, 0, 1 };
		//CommonListBox cvGate{ "Gate", {"Normal", "Re-Trigger"}, 0, 1 };
		CommonListBox CVNoteSelection{ "Note Priority",{"Lowest","Highest", "Last" },0,1 };
		CommonNumber cvOutput{ "Output Volts", 5, 10, 5 };

		commonrotary slider[NO_OF_ENVOLOPE_SLIDER];

		juce::FlexBox cvConfigPort;
		juce::FlexBox cvConfgBox1;
		juce::FlexBox cvConfgBox2;
		juce::FlexBox rotarySlider;
		IgniteCvConfigContainer Container;
		CommonViewport viewport;
		Image imageGateportBg, imageDefault, imageDefaultHover, imageActive, imageActiveHover;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void updateValuesRange();
		void setCvPortButtonToggleState(int portNumber);
		void updateCvUI(uint8_t selectedPort);
		void updateSliderData(EnvlopType index, int8_t data, bool play_mode);
		int8_t getSiderData(EnvlopType index);
		void onRotaryValueChange(common_rotaryslider*, double Value) override;
		void onRotaryDragEnd(common_rotaryslider*, double Value) override;
		int getKnobIndex(String knob);
		void updateOnViewPositionChange(CommonViewport* pViewport);
		void moveViewPortHorizontaly(int direction);
		void updateCvNoteEnd(int baseNote);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCvConfig)
	};

	class IgniteGateConfig :
		public juce::Component,
		public juce::Button::Listener
	{
	public:
#define GATE_CONFIG_VIEW 12
		enum GateConfigItemID
		{
			NO_FOCUS = 0,
			GATE_PORT1,
			GATE_PORT2,
			GATE_PORT3,
			GATE_PORT4,
			GATE_PORT5,
			GATE_PORT6,
			GATE_PORT7,
			GATE_PORT8,
			//GATE_CHANNEL,
			GATE_MODE,
			GATE_TYPE,
			GATE_OUTPUT,
			FOCUS_MAX = GATE_OUTPUT
		};

		uint8_t Gate_Config[GATE_CONFIG_VIEW] = { NO_FOCUS, GATE_PORT1,	GATE_PORT2,GATE_PORT3,GATE_PORT4,GATE_PORT5,GATE_PORT6,	GATE_PORT7,	GATE_PORT8,	/*GATE_CHANNEL,*/ GATE_MODE, GATE_TYPE, GATE_OUTPUT };
		int KeyFocusedItem = GateConfigItemID::GATE_PORT1;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		int isEditing();

		IgniteGateConfig();
		~IgniteGateConfig() override;
		void updateGateData();
		void updateGateOutputPort();
		void getAssets();
		static IgniteGateConfig* GetAppGateInstance()
		{
			static IgniteGateConfig* GetAppGateObj;
			if (NULL == GetAppGateObj)
			{
				GetAppGateObj = new IgniteGateConfig();
			}

			return GetAppGateObj;
		}

	private:
		CommonNameLabel GateConfigLable{ "Gate Port: " };
		CommonButton gatePort1{ "1" };
		CommonButton gatePort2{ "2" };
		CommonButton gatePort3{ "3" };
		CommonButton gatePort4{ "4" };
		CommonButton gatePort5{ "5" };
		CommonButton gatePort6{ "6" };
		CommonButton gatePort7{ "7" };
		CommonButton gatePort8{ "8" };
		//CommonNumber gateChannel{ "Channel", 0, 15, 0 };

		CommonListBox gateType{ "Type", {"V-Trig Output", "Invert Output"}, 0, 1 };
		CommonListBox gateOutput{ "Output Volts", {"5V", "10V"}, 0, 1 };
		CommonListBox gateMode{ "Mode", {"Normal", "Re-Trigger"}, 0, 1 };

		juce::FlexBox gateConfigPort;
		juce::FlexBox gateConfgBox;
		Image imageGateportBg, imageDefault, imageDefaultHover, imageGateDefault, imageGateDefaultHover, imageGateActive, imageGateActiveHover;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void setGatePortButtonToggleState(int portNumber);
		void updateGateUI(uint8_t selectedPort);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteGateConfig)
	};
};