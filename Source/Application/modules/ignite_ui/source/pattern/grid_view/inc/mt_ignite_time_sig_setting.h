#pragma once
namespace ui
{

	class TimeSigSetting : public juce::Component,
		public juce::Button::Listener
	{
	public:
		TimeSigSetting(int tsNum, int tsDen, bool hasOnlyOneBar);
		~TimeSigSetting() override;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		juce::String getNumerator();
		juce::String getDenominator();

	private:
		juce::TextEditor timeSigNumerator;
		juce::TextEditor timeSigDenominator;
		juce::Label labelSlash;
		CommonButton addButton{ TRANS("Add") };
		CommonButton cancelButton{ TRANS("cancel") };
		CommonButton deleteButton{ TRANS("Delete") };
		bool hasTimeSig = false;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimeSigSetting)
	};
}

//[EndFile] You can add extra defines here...
//[/EndFile]
