/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StreamTrackAudioProcessorEditor::StreamTrackAudioProcessorEditor (StreamTrackAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (350, 200);
    
    btnStart.setButtonText("Start");
    btnSendOnlySpectrum.setButtonText("Audio & Spectrum");
    
    addAndMakeVisible(&btnStart);
    addAndMakeVisible(&btnSendOnlySpectrum);
    addAndMakeVisible(&txtTrackNumber);
    addAndMakeVisible(&txtPort);
    addAndMakeVisible(&txtHost);
    
    btnStart.addListener(this);
    btnSendOnlySpectrum.addListener(this);
    
    txtPort.setText(std::to_string(processor.getPort()));
    txtHost.setText(processor.getHost());
}

StreamTrackAudioProcessorEditor::~StreamTrackAudioProcessorEditor()
{
}

//==============================================================================
void StreamTrackAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
    g.drawText("Track #", 10, 10, 60, 30, Justification::centredLeft);
    g.drawText("Port", 10, 50, 30, 30, Justification::centredLeft);
    g.drawText("Host", 110, 50, 30, 30, Justification::centredLeft);
}

void StreamTrackAudioProcessorEditor::resized()
{
    txtTrackNumber.setBounds(70, 10, 60, 30);
    txtPort.setBounds(40, 50, 60, 30);
    txtHost.setBounds(150, 50, 90, 30);
    btnStart.setBounds(10, 90, 200, 30);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void StreamTrackAudioProcessorEditor::buttonClicked ( Button* button)
{
    
    if (btnStart.getButtonText().equalsIgnoreCase("Start")) {
        btnStart.setButtonText("Stop");
        if (txtTrackNumber.getTextValue().toString().isNotEmpty()) {
            processor.setTrackNum((txtTrackNumber.getTextValue().toString().getIntValue()));
        }
        processor.setActive(true);
//        processor.setPort(std::stoi(txtPort.getTextValue().toString()));
        processor.setHost(txtHost.getTextValue().toString());
        
    } else {
        btnStart.setButtonText("Start");
        processor.setActive(false);
    }
}
