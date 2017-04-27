/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StreamTrackAudioProcessor::StreamTrackAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        trackNumParam(nullptr),
        portParam(nullptr),
        ip1Param(nullptr),
        ip2Param(nullptr),
        ip3Param(nullptr),
        ip4Param(nullptr),
        blockMulParam(nullptr),
        hopMulParam(nullptr),
        oscPool(),
        oscSender(nullptr)

#endif
{
    port = 7000;
    ip1 = 127; ip2 = 0; ip3 = 0; ip4 = 1;
    host = (String)ip1+"."+(String)ip2+"."+(String)ip3+"."+(String)ip4;
    blockMul = 4;
    hopMul = 1;

    addParameter (trackNumParam  = new AudioParameterInt ("tracknum",  "Track Number", 0, 15, 2));
    addParameter (portParam  = new AudioParameterInt ("port",  "Port", 7000, 7999, port));
    addParameter (blockMulParam  = new AudioParameterInt ("blockmul",  "Block = 2048 * ?", 1, 4, blockMul));
    addParameter (hopMulParam  = new AudioParameterInt ("hopmul",  "Hop = 2048 * ?", 1, 4, hopMul));
    addParameter (ip1Param  = new AudioParameterInt ("ip1",  "ip1", 0, 255, ip1));
    addParameter (ip2Param  = new AudioParameterInt ("ip2",  "ip2", 0, 255, ip2));
    addParameter (ip3Param  = new AudioParameterInt ("ip3",  "ip3", 0, 255, ip3));
    addParameter (ip4Param  = new AudioParameterInt ("ip4",  "ip4", 0, 255, ip4));

    initPlugin();
}

StreamTrackAudioProcessor::~StreamTrackAudioProcessor()
{
    resetPlugin();
}

void StreamTrackAudioProcessor::resetPlugin() {
    oscSender->disconnect();
    delete oscPoolJob;
    delete oscSender;
}


void StreamTrackAudioProcessor::initPlugin() {
    
    if (oscSender != nullptr) {
        setActive(false);
        resetPlugin();
    }
    
    oscSender = new OSCSender();
    
    oscSender->connect(host, port);
    hostBufferSize = 2048;
    windowSize = hostBufferSize*blockMul;
    processBufferSize = 0;
    currentHop = 0;
    maxChannelsSupported = 2;
    oscPoolJob = new OSCThreadPoolJob(2,windowSize,oscSender);
    
    //Activate OSC Sender
    setActive(true);
}

//==============================================================================
const String StreamTrackAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StreamTrackAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StreamTrackAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double StreamTrackAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StreamTrackAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StreamTrackAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StreamTrackAudioProcessor::setCurrentProgram (int index)
{
}

const String StreamTrackAudioProcessor::getProgramName (int index)
{
    return String();
}

void StreamTrackAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StreamTrackAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    pfWindow = new float*[maxChannelsSupported];
    for (int i=0; i< maxChannelsSupported;i++) {
        pfWindow[i] = new float[windowSize];
        memset(pfWindow[i],0.0f,windowSize);
    }
}

void StreamTrackAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    for (int i=0; i<maxChannelsSupported; i++) {
        delete [] pfWindow[i];
        
    }
    delete [] pfWindow;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StreamTrackAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StreamTrackAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (port != *portParam) {
        setActive(false);
        port = *portParam;
        initPlugin();
    }
    
    if (ip1 != *ip1Param || ip2 != *ip2Param || ip2 != *ip2Param || ip2 != *ip2Param) {
        setActive(false);
        port = *portParam;
        initPlugin();
    }
    
    if (blockMul != *blockMulParam) {
        setActive(false);
        blockMul = *blockMulParam;
        initPlugin();
    }
    
    if (hopMul != *hopMulParam) {
        setActive(false);
        hopMul = *hopMulParam;
        initPlugin();
    }
    
    if (bActive) {
        // This is the place where you'd normally do the guts of your plugin's
        // audio processing...
    
        //put
        for (int channel = 0; channel < totalNumInputChannels; ++channel) {
             memcpy(pfWindow[channel]+(blockMul-hopMul)*getBlockSize(), buffer.getWritePointer (channel),sizeof(float)*getBlockSize());
        }
        
        //send
        oscPoolJob->init(pfWindow, totalNumInputChannels, windowSize, *trackNumParam);
        oscPool.addJob(oscPoolJob, false);
        
        
        //move
        for (int channel = 0; channel < totalNumInputChannels; ++channel) {
            memcpy(pfWindow[channel], pfWindow[channel]+hopMul*getBlockSize(),sizeof(float)*(blockMul-hopMul)*getBlockSize());
        }
       
        
//        if (processBufferSize > 0 && (processBufferSize % windowSize == 0)) {
//            oscPoolJob->init(pfWindow, totalNumInputChannels, windowSize, *trackNumParam);
//            oscPool.addJob(oscPoolJob, false);
//            processBufferSize = 0;
//        } else {
//            for (int channel = 0; channel < totalNumInputChannels; ++channel) {
//                memcpy(pfWindow[channel]+processBufferSize, buffer.getWritePointer (channel),sizeof(float)*getBlockSize());
//            }
//            processBufferSize += getBlockSize();
//        }
    }
    
    
}

//==============================================================================
bool StreamTrackAudioProcessor::hasEditor() const
{
    return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StreamTrackAudioProcessor::createEditor()
{
    return nullptr;
//    return new StreamTrackAudioProcessorEditor (*this);
}

//==============================================================================
void StreamTrackAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StreamTrackAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StreamTrackAudioProcessor();
}

void StreamTrackAudioProcessor::setActive(bool active) {
    bActive = active;
}


OSCSender* StreamTrackAudioProcessor::getOSCSender() {
    return oscSender;
}
