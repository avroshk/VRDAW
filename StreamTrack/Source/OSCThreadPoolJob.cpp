/*
  ==============================================================================

    OSCThreadPoolJob.cpp
    Created: 6 Apr 2017 4:56:19pm
    Author:  Avrosh Kumar

  ==============================================================================
*/

#include "OSCThreadPoolJob.h"
#include "PluginProcessor.h"

FFTLight *OSCThreadPoolJob::pFft = new FFTLight();

OSCThreadPoolJob::OSCThreadPoolJob(int maxNumChannels, int maxBlockSize, OSCSender* o): ThreadPoolJob("OSC ThreadPool JOB") {
    this->maxNumChannels = maxNumChannels;
    this->maxBlockSize = maxBlockSize;
    this->oscSender = o;
    ppAudio = new float*[maxNumChannels];
    ppAudio8bit = new char*[maxNumChannels];
    ppSpectrum8bit = new char*[maxNumChannels];
    
    pFft->init(maxBlockSize);
    bActive = false;
    trackNum = 0;
    
    for (int i=0; i< maxNumChannels;i++) {
        ppAudio[i] = new float[maxBlockSize];
        ppAudio8bit[i] = new char[maxBlockSize];
        ppSpectrum8bit[i] = new char[pFft->getFFTLength()];
    }
}

//void OSCThreadPoolJob::init(AudioSampleBuffer &data, int numChannels, int blockSize) {
//    this->numChannels = numChannels;
//    this->blockSize = blockSize;
//    if (bActive) {
//        if (numChannels <= maxNumChannels) {
//            for (int i=0; i< maxNumChannels;i++) {
//                if (blockSize <= maxBlockSize) {
//                    memcpy(ppAudio[i], data.getWritePointer(i),sizeof(float)*blockSize);
//                }
//            }
//        }
//    }
//}

void OSCThreadPoolJob::init(float ** data, int numChannels, int blockSize) {
    this->numChannels = numChannels;
    this->blockSize = blockSize;
    if (bActive) {
        if (numChannels <= maxNumChannels) {
            for (int i=0; i< maxNumChannels;i++) {
                if (blockSize <= maxBlockSize) {
                    memcpy(ppAudio[i], data[i],sizeof(float)*blockSize);
                }
            }
        }
    }
}

void OSCThreadPoolJob::resetMemoryBlocks() {
    audio.reset();
    spectrum.reset();
}

void OSCThreadPoolJob::bitCrush(float* data, char* crushed, int blockSize) {
    
    for (int j=0; j< blockSize; j++) {
        crushed[j] = data[j]*255;
    }
    
}

OSCThreadPoolJob::~OSCThreadPoolJob() {
    resetMemoryBlocks();
    for (int i=0; i<maxNumChannels; i++) {
        delete [] ppAudio[i];
        delete [] ppAudio8bit[i];
        delete [] ppSpectrum8bit[i];
    }
    delete [] ppAudio;
    delete [] ppAudio8bit;
    delete [] ppSpectrum8bit;
}

OSCThreadPoolJob::JobStatus OSCThreadPoolJob::runJob()  {
    
    if (shouldExit()) {
        return jobNeedsRunningAgain;
    }
    
    if (bActive) {

        if (blockSize != maxBlockSize) {
            pFft->init(blockSize);
            maxBlockSize = blockSize;
        }
        
        for (int i=0; i<numChannels; i++) {
            
//            bitCrush(ppAudio[i], ppAudio8bit[i], blockSize);
//            audio.insert(ppAudio8bit[i], blockSize*sizeof(char), blockSize*i);
            
            bitCrush(pFft->getSpectrum(ppAudio[i]), ppSpectrum8bit[i], pFft->getFFTLength());
            spectrum.insert(ppSpectrum8bit[i], pFft->getFFTLength()*sizeof(char), pFft->getFFTLength()*i);
            
            
//            audio.insert(ppAudio[i], blockSize*sizeof(float), blockSize*i);
//            spectrum.insert(pFft->getSpectrum(ppAudio[i]), pFft->getFFTLength()*sizeof(float), pFft->getFFTLength()*i);
        }
        
//        oscSender->send("/live/track/"+trackNum+"/audio", numChannels, blockSize, audio);
        oscSender->send("/live/track/spectrum", trackNum, numChannels, pFft->getFFTLength(), spectrum);
        resetMemoryBlocks();
    }
    
    return jobHasFinished;
}
