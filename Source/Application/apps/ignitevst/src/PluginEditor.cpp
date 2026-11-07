/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace Ignite;
using namespace Ignite::Midi;
std::unique_ptr<IListener> _PUiInterface;
std::unique_ptr<IDevice> _PUiVirtualEngine;
extern IDevice* EngineInit(void);

void UiEngineInterfaceInit(void)
{
	//Engine init, Interface init and linking interface end points
	if (_PUiVirtualEngine == nullptr || _PUiInterface == nullptr)
	{
		_PUiVirtualEngine = (std::unique_ptr<IDevice>) EngineInit();
		_PUiInterface = std::make_unique<UiInterface>(_PUiVirtualEngine.get());
	}
}

//==============================================================================
PluginProjectAudioProcessorEditor::PluginProjectAudioProcessorEditor(PluginProjectAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	UiEngineInterfaceInit();
	home = ui::AppHome::GetAppHomeInstance();
	addAndMakeVisible(home);
	setSize(1024, 600);
}

PluginProjectAudioProcessorEditor::~PluginProjectAudioProcessorEditor()
{
}

//==============================================================================
void PluginProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.setColour(juce::Colours::white);
	g.fillRect(getLocalBounds());
}

void PluginProjectAudioProcessorEditor::resized()
{
	home->setBounds(1, 1, 1024, 600);
}


