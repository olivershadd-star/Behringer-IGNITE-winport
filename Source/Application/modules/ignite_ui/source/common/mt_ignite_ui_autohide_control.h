#pragma once

namespace ui
{

	class IgniteTrackValues;
	class CommonAutoHideSlider: public juce::Component, private Timer , public common_rotaryslider::Listener
	{
		
		CommonAutoHideSlider();
		~CommonAutoHideSlider();

		commonrotary slider[8];
		juce::FlexBox sliderContainerBox;
		juce::FlexBox sliderContainerBox1;
		void paint(juce::Graphics& g) override;
		void resized() override;
		int timems = 3000;
		bool soundStatus = true;
		
	public:
		static CommonAutoHideSlider* GetHideSliderInstance()
		{
			static CommonAutoHideSlider* GetInstance;
			if (NULL == GetInstance)
			{
				GetInstance = new CommonAutoHideSlider();
			}

			return GetInstance;
		}
		void SetVisible(bool state);
		void timerCallback() override;
		IgniteTrackValues* TrackValuePtr = nullptr;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void onRotaryValueChange(common_rotaryslider*, double Value) override;
		bool isRotarysVisible() { return isVisible; };
		void restartTimer() {
			stopTimer();
			startTimer(timems);
			isVisible = true;
		};
		void setAlternativeFunc();
		void mouseDown(const MouseEvent&) override;
		bool valueType[8];
		bool isVisible = false;
		juce::Image   image;
		bool altstate = false;
		float Vcutoff = 0;
		int8_t isFromFp = -1;
		mt::Ignite::TrackValues activeknobdata;
		juce::Label _uiDimComp;
		
	};


};
