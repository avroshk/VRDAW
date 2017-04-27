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
    void initPlugin();
    void resetPlugin();
    void setPort(int port);
    int getPort();
    void setHost(String host);
    String getHost();
    void setActive(bool);
    void setTrackNum(int trackNum);
    OSCSender* getOSCSender();
    
    AudioParameterInt* trackNumParam;
    AudioParameterInt* portParam;
    AudioParameterInt* ip1Param;
    AudioParameterInt* ip2Param;
    AudioParameterInt* ip3Param;
    AudioParameterInt* ip4Param;
    AudioParameterInt* blockMulParam;
    AudioParameterInt* hopMulParam;
    
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StreamTrackAudioProcessor)

    int port, ip1, ip2, ip3, ip4, blockMul, hopMul;
    int currentHop;
    String host;
    int hostBufferSize;
    int windowSize;
    int processBufferSize;
    int maxChannelsSupported;
    float **pfWindow;
    
    bool bActive;
    
    ThreadPool oscPool;
    
    OSCSender *oscSender;
    OSCThreadPoolJob *oscPoolJob;
    
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
