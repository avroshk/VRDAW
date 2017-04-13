/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OSCThreadPoolJob.h"


//==============================================================================
/**
*/
class StreamTrackAudioProcessorEditor  : public AudioProcessorEditor, public::TextButton::Listener
{
public:
    StreamTrackAudioProcessorEditor (StreamTrackAudioProcessor&);
    ~StreamTrackAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //UI events
    void buttonClicked (Button *button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    StreamTrackAudioProcessor& processor;
    
    TextButton btnStart;
    TextEditor txtTackNumber;
    ToggleButton btnSendOnlySpectrum;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StreamTrackAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
