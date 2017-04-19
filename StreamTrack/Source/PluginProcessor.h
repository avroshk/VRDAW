/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "OSCThreadPoolJob.h"


//==============================================================================
/**
*/
//class OSCThreadPoolJob;

class StreamTrackAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    StreamTrackAudioProcessor();
    ~StreamTrackAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //=======
    void setPort(int port);
    int getPort();
    void setHost(String host);
    String getHost();
    void setActive(bool);
    void setTrackNum(String trackNum);
    OSCSender* getOSCSender();
    
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StreamTrackAudioProcessor)

    static int port;
    static String host;
    
    ThreadPool oscPool;
    
    OSCSender *oscSender;
    OSCThreadPoolJob *oscPoolJob;
    
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
