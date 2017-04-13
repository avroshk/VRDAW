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

OSCThreadPoolJob::OSCThreadPoolJob(int maxNumChannels, int maxBlockSize): ThreadPoolJob("OSC ThreadPool JOB") {
    this->maxNumChannels = maxNumChannels;
    this->maxBlockSize = maxBlockSize;
    ppAudio = new float*[maxNumChannels];
//    ppSpectrum = new float*[maxNumChannels];
//    ppAudio8bit = new uint8*[maxNumChannels];
    
    pFft->init(maxBlockSize);
    bActive = false;
    trackNum = "0";
    
    for (int i=0; i< maxNumChannels;i++) {
        ppAudio[i] = new float[maxBlockSize];
//        ppSpectrum[i] = new float[pFft->getFFTLength()];
//        ppAudio8bit[i] = new uint8[maxBlockSize];
    }
}

void OSCThreadPoolJob::init(AudioSampleBuffer &data, int numChannels, int blockSize) {
    this->numChannels = numChannels;
    this->blockSize = blockSize;
    if (bActive) {
        if (numChannels <= maxNumChannels) {
            for (int i=0; i< maxNumChannels;i++) {
                if (blockSize <= maxBlockSize) {
                    memcpy(ppAudio[i], data.getWritePointer(i),sizeof(float)*blockSize);
                }
            }
        }
//        for (int i=0; i<numChannels; i++) {
//            audio.insert(data.getWritePointer(i)+i*blockSize, blockSize*sizeof(float), blockSize*i);
//        }
    }
}

void OSCThreadPoolJob::resetMemoryBlocks() {
    audio.reset();
    spectrum.reset();
}

OSCThreadPoolJob::~OSCThreadPoolJob() {
    resetMemoryBlocks();
    for (int i=0; i<maxNumChannels; i++) {
        delete [] ppAudio[i];
//        delete [] ppAudio8bit[i];
//        delete [] ppSpectrum[i];
    }
    delete [] ppAudio;
//    delete [] ppAudio8bit;
//    delete [] ppSpectrum;
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
            
            //bit-crush
//            for (int j=0; j<blockSize;j++) {
//                ppAudio8bit[i][j] = (uint8)(ppAudio[i][j]*1000000);
//            }
//            
//            audio.insert(ppAudio8bit[i], blockSize*sizeof(uint8), blockSize*i);
//            
//            ppSpectrum[i] = pFft->getSpectrum(ppAudio[i]);
//            
//            //bit-crush spectrum
//            for (int j=0; j<pFft->getFFTLength();j++) {
//                ppAudio8bit[i][j] = (uint8)(ppSpectrum[i][j]*1000);
//            }
//            
//            spectrum.insert(ppAudio8bit[i], pFft->getFFTLength()*sizeof(uint8), pFft->getFFTLength()*i);
//            
            audio.insert(ppAudio[i], blockSize*sizeof(float), blockSize*i);
            spectrum.insert(pFft->getSpectrum(ppAudio[i]), pFft->getFFTLength()*sizeof(float), pFft->getFFTLength()*i);
        }
        
        StreamTrackAudioProcessor::oscSender->send("/live/track/"+trackNum+"/audio", numChannels, blockSize, audio);
        StreamTrackAudioProcessor::oscSender->send("/live/track/"+trackNum+"/spectrum", numChannels, pFft->getFFTLength(), spectrum);
        resetMemoryBlocks();
    }
    
    return jobHasFinished;
}
