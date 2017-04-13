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
    setSize (400, 300);
    
    btnStart.setButtonText("Start");
    btnSendOnlySpectrum.setButtonText("Audio & Spectrum");
    addAndMakeVisible(&btnStart);
    addAndMakeVisible(&btnSendOnlySpectrum);
    addAndMakeVisible(&txtTackNumber);
    btnStart.addListener(this);
    btnSendOnlySpectrum.addListener(this);
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
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void StreamTrackAudioProcessorEditor::resized()
{
    btnStart.setBounds(10, 250, 200, 30);
    txtTackNumber.setBounds(10, 150, 200, 30);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void StreamTrackAudioProcessorEditor::buttonClicked ( Button* button)
{
    
    if (btnStart.getButtonText().equalsIgnoreCase("Start")) {
        btnStart.setButtonText("Stop");
        if (txtTackNumber.getTextValue().toString().isNotEmpty()) {
            processor.setTrackNum(txtTackNumber.getTextValue().toString());
        }
        processor.setActive(true);
    
    } else {
        btnStart.setButtonText("Start");
        processor.setActive(false);
    }
}
