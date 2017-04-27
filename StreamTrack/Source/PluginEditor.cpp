/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class StreamTrackAudioProcessorEditor::ParameterSlider   : public Slider,
private Timer
{
public:
    ParameterSlider (AudioProcessorParameter& p)
    : Slider (p.getName (256)), param (p)
    {
        setRange (0.0, 15.0, 1.0);
        startTimerHz (30);
        updateSliderPos();
    }
    
    void valueChanged() override
    {
        if (isMouseButtonDown())
            param.setValueNotifyingHost ((float) Slider::getValue());
        else
            param.setValue ((float) Slider::getValue());
    }
    
    void timerCallback() override       { updateSliderPos(); }
    
    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }
    
    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }
    
    void updateSliderPos()
    {
        const float newValue = param.getValue();
        
        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue);
    }
    
    AudioProcessorParameter& param;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
};

//==============================================================================
StreamTrackAudioProcessorEditor::StreamTrackAudioProcessorEditor (StreamTrackAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
//    setSize (350, 200);
    
//    btnStart.setButtonText("Start");
//    btnSendOnlySpectrum.setButtonText("Audio & Spectrum");
//    
//    addAndMakeVisible(&btnStart);
//    addAndMakeVisible(&btnSendOnlySpectrum);
//    addAndMakeVisible(&txtTrackNumber);
//    addAndMakeVisible(&txtPort);
//    addAndMakeVisible(&txtHost);
//    
//    addAndMakeVisible (trackNumberSlider = new ParameterSlider (*processor.trackNumParam));
//    addAndMakeVisible (portNumberSlider = new ParameterSlider (*processor.portParam));
//
//    trackNumberSlider->setSliderStyle (Slider::Rotary);
//    
//    btnStart.addListener(this);
//    btnSendOnlySpectrum.addListener(this);
    
//    txtPort.setText(std::to_string(processor.getPort()));
//    txtHost.setText(processor.getHost());
}

StreamTrackAudioProcessorEditor::~StreamTrackAudioProcessorEditor()
{
}

//==============================================================================
void StreamTrackAudioProcessorEditor::paint (Graphics& g)
{
//    g.fillAll (Colours::white);
//    g.setColour (Colours::black);
//    g.setFont (15.0f);
////    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
//    g.drawText("Track #", 10, 10, 60, 30, Justification::centredLeft);
//    g.drawText("Port", 10, 50, 30, 30, Justification::centredLeft);
//    g.drawText("Host", 110, 50, 30, 30, Justification::centredLeft);
}

void StreamTrackAudioProcessorEditor::resized()
{
    
//    trackNumberSlider->setBounds (70, 10, 60, 30);
    
//    txtTrackNumber.setBounds(70, 10, 60, 30);
//    txtPort.setBounds(40, 50, 60, 30);
//    txtHost.setBounds(150, 50, 90, 30);
//    btnStart.setBounds(10, 90, 200, 30);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void StreamTrackAudioProcessorEditor::buttonClicked ( Button* button)
{
    
//    if (btnStart.getButtonText().equalsIgnoreCase("Start")) {
//        btnStart.setButtonText("Stop");
//        if (txtTrackNumber.getTextValue().toString().isNotEmpty()) {
//            processor.setTrackNum((txtTrackNumber.getTextValue().toString().getIntValue()));
//        }
//        processor.setActive(true);
////        processor.setPort(std::stoi(txtPort.getTextValue().toString()));
//        processor.setHost(txtHost.getTextValue().toString());
//        
//    } else {
//        btnStart.setButtonText("Start");
//        processor.setActive(false);
//    }
}
