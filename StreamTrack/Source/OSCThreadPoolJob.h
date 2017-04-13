/*
  ==============================================================================

    OSCThreadPoolJob.h
    Created: 6 Apr 2017 4:56:38pm
    Author:  Avrosh Kumar

  ==============================================================================
*/

#ifndef OSCTHREADPOOLJOB_H_INCLUDED
#define OSCTHREADPOOLJOB_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FFTLight.h"

class OSCThreadPoolJob : public ThreadPoolJob {
public:
    OSCThreadPoolJob(int,int, OSCSender*);
    ~OSCThreadPoolJob();
    
    JobStatus runJob() override;
    void init(AudioSampleBuffer &data, int numChannels, int blockSize);
    
    bool bActive;
    String trackNum;

    
private:
//    StreamTrackAudioProcessor& processor;
    OSCSender *oscSender;
    static FFTLight *pFft;
    float ** ppAudio;
//    float ** ppSpectrum;
//    uint8 ** ppAudio8bit;
//    float ** ppSpectrum8bit;
    
    int maxNumChannels;
    int maxBlockSize;
    
    MemoryBlock audio;
    MemoryBlock spectrum;
   
    int numChannels;
    int blockSize;
    
    void resetMemoryBlocks();
};


#endif  // OSCTHREADPOOLJOB_H_INCLUDED
