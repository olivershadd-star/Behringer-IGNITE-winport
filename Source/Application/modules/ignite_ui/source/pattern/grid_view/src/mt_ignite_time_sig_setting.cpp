#include "../inc/mt_ignite_time_sig_setting.h"

namespace ui
{
	TimeSigSetting::TimeSigSetting(int tsNum, int tsDen, bool hasOnlyOneBar)
	{
		addAndMakeVisible(&timeSigNumerator);
		timeSigNumerator.setMultiLine(false);
		timeSigNumerator.setReturnKeyStartsNewLine(false);
		timeSigNumerator.setReadOnly(false);
		timeSigNumerator.setScrollbarsShown(true);
		timeSigNumerator.setCaretVisible(true);
		timeSigNumerator.setPopupMenuEnabled(true);
		juce::String numVal = tsNum == -1 ? "4" : juce::String(tsNum);
		timeSigNumerator.setText(numVal);
		timeSigNumerator.setBounds(xStartTimeSigNumerator, yStartTimeSigNumerator, widthTimeSigNumerator, heightTimeSigNumerator);
		timeSigNumerator.setInputRestrictions(10, "0123456789");

		addAndMakeVisible(&timeSigDenominator);
		timeSigDenominator.setMultiLine(false);
		timeSigDenominator.setReturnKeyStartsNewLine(false);
		timeSigDenominator.setReadOnly(false);
		timeSigDenominator.setScrollbarsShown(true);
		timeSigDenominator.setCaretVisible(true);
		timeSigDenominator.setPopupMenuEnabled(true);
		juce::String denVal = tsDen == -1 ? "4" : juce::String(tsDen);
		timeSigDenominator.setText(denVal);

		timeSigDenominator.setBounds(xStartTimeSigDenominator, yStartTimeSigDenominator, widthTimeSigDenominator, heightTimeSigDenominator);
		timeSigDenominator.setInputRestrictions(10, "0123456789");

		addAndMakeVisible(&labelSlash);
		labelSlash.setText("/", juce::NotificationType::dontSendNotification);
		labelSlash.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		labelSlash.setJustificationType(juce::Justification::centredLeft);
		labelSlash.setEditable(false, false, false);
		labelSlash.setColour(juce::TextEditor::textColourId, Theme::Instance().backgroundColour(5));
		labelSlash.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

		labelSlash.setBounds(xStartLabelSlash, yStartLabelSlash, widthLabelSlash, heightLabelSlash);

		addAndMakeVisible(&cancelButton);
		cancelButton.setButtonText(TRANS("cancel"));
		cancelButton.addListener(this);
		cancelButton.setBounds(xStartCancelButton, yStartCancelButton, widthCancelButton, heightCancelButton);

		addAndMakeVisible(&deleteButton);
		deleteButton.setButtonText(TRANS("Delete"));
		deleteButton.addListener(this);
		deleteButton.setBounds(xStartDeleteButton, yStartDeleteButton, widthDeleteButton, heightDeleteButton);

		addAndMakeVisible(&addButton);
		addButton.setButtonText(TRANS("Add"));
		addButton.addListener(this);
		addButton.setBounds(xStartAddButton, yStartAddButton, widthAddButton, heightAddButton);

		if (tsNum != -1 && !hasOnlyOneBar)
		{
			addButton.setButtonText(TRANS("Ok"));
		}
		else
		{
			deleteButton.setVisible(false);
		}

		setSize(240, 100);
	}

	TimeSigSetting::~TimeSigSetting()
	{        }

	void TimeSigSetting::paint(juce::Graphics& g)
	{
		g.fillAll(juce::Colour(0xff323e44));
	}

	void TimeSigSetting::resized()
	{        }

	void TimeSigSetting::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>();
		if (dw == nullptr)
			return;

		if (buttonThatWasClicked == &addButton)
		{
			dw->exitModalState(ignite_Constants::BUTTONS::APPLY);
		}
		else if (buttonThatWasClicked == &cancelButton)
		{
			dw->exitModalState(ignite_Constants::BUTTONS::CANCEL);
		}
		else if (buttonThatWasClicked == &deleteButton)
		{
			dw->exitModalState(ignite_Constants::BUTTONS::DELETE);
		}
	}
	juce::String TimeSigSetting::getNumerator()
	{
		return timeSigNumerator.getText();
	}
	juce::String TimeSigSetting::getDenominator()
	{
		return timeSigDenominator.getText();
	}
}

