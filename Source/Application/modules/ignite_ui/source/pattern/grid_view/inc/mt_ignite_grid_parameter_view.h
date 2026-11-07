#pragma once
namespace ui
{
	class mt_ignite_app_joystick;
	class ParameterView : public Component

	{
	public:
		ParameterView(GridData* gData, NoteManagement& noteManagement);

		void setMinimizeHeight(int mHeight) { minimizeHeight = mHeight; }
		int getMinimizeHeight() { return minimizeHeight; }
		int getRecommendedtHeight();
		void updateOffsetLength();

	private:
		std::map<juce::String, mt::Ignite::nodeDataIndex> s_mapStringToParamValueIndex =
		{
			{ "Velocity",       mt::Ignite::nodeDataIndex::VELO },
			{ "Len:Steps",  mt::Ignite::nodeDataIndex::STEP_LEN_IN_STEP},
			{ "Len:Tick",   mt::Ignite::nodeDataIndex::STEP_LEN_IN_TICK},
			{ "Offset",          mt::Ignite::nodeDataIndex::DELAY},
		};
		std::map<juce::String, int> s_mapStringToParamMaxType =
		{
			{ "Velocity",       maxVelocity},
			{ "Len:Steps",  maxStepLength},
			{ "Len:Tick",   MaxOffsetVar},
			{ "Offset",     MaxLengthVar},
		};

		bool minimized = false;
		int minimizeHeight;
		GridData* gridData;
		NoteManagement& noteMgmt;
		mt::Ignite::patternData* patternData = nullptr;
		int MaxOffsetVar = 0;
		int MaxLengthVar = 0;

		int getStepId(int stepIndex);
		var getParamFromEngine(mt::Ignite::nodeDataIndex param, int step_index, int nodeId);
		bool isNotePreset(int stepNum, int noteNum);
		virtual void mouseDrag(const MouseEvent& event) override;
		virtual void paint(Graphics& g);

	};

	class ParameterViewControl : public juce::Component
		, public juce::Button::Listener
	{
	public:
		explicit ParameterViewControl(ParameterView& pV);
		virtual void resized();
		int getRecommendedHeight() { return gridParameterControlHeight; }
		void getAssets();

		virtual void buttonClicked(Button* button);
		CommonButton plusBtn{ "" };
		CommonButton minusBtn{ "" };
		CommonButton ZoomPrctg{ "0%" };

		void refreshGridctrl();
		void setZoomLable(int value) { ZoomPrctg.setButtonText(String(value) + " % "); }
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		int currentNoteShowing = 0;
	private:
		SIGNALS :
		sig::Signal <int> controlParamGridChanged;
		sig::Signal<bool> leftNudgeChanged;
		sig::Signal<bool> rightNudgeChanged;
		mt_ignite_app_joystick* joystick = nullptr;

		enum e_paramValueType {
			eMIN,
			eVelocity,
			eLengthSteps,
			eLengthTick,
			eDelay,
			eMAX
		};

		std::map<juce::String, e_paramValueType> s_mapStringToParamValueType =
		{
			{ "Velocity",       eVelocity },
			{ "Len:Steps",  eLengthSteps },
			{ "Len:Tick",   eLengthTick},
			{ "Offset",          eDelay},

		};
		CommonImageButton veloBtn{ "VELO","btn-param-velocity-default.png","btn-param-velocity-active.png","btn-param-velocity-default-hover.png" };
		CommonImageButton lenStepBtn{ "LENSTEP","btn-param-lenstep-default.png","btn-param-lenstep-active.png","btn-param-lenstep-default-hover.png" };
		CommonImageButton lenTickBtn{ "LENTICK","btn-param-lentick-default.png","btn-param-lentick-active.png","btn-param-lentick-default-hover.png" };
		CommonImageButton delayBtn{ "DELAY","btn-param-offset-default.png","btn-param-offset-active.png","btn-param-offset-default-hover.png" };
		
		Image scrollOptionDefault, scrollOptionHover, zoomPlusDefault, zoomPlusHover, zoomMinusDefault, zoomMinusHover, scrollLeftDefault,
			scrollLeftHover, scrollRghtDefault, scrollRghtHover;

		CommonLabel zoomPer{ "0" };
		virtual void paint(Graphics& g);

		ui::CommonButton leftNudgeButton{ TRANS("") };
		ui::CommonButton nudgeText;
		ui::CommonButton rightNudgeButton{ TRANS("") };
		ParameterView& parameterView;
		bool expanded = false;
		StepSequencerControl& stepControlView{ StepSequencer::getStepSequencerInstance()->getStepSequencerControl() };
		FlexBox controlFlex;
		FlexBox paramBox1;
		FlexBox box;

		void setButtonState(int btn_index);
	};
}

