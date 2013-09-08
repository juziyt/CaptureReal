
#ifndef __OnsetReal__AudioInputSource__
#define __OnsetReal__AudioInputSource__

#include <iostream>
#include "JuceHeader.h"
#include "CaptureReal.h"

#define RECORDSIZE 13458

class AudioFileSource : public AudioIODeviceCallback
{
public:
    AudioFileSource(AudioDeviceManager& deviceManager);
    ~AudioFileSource();
    void audioDeviceIOCallback(const float** inputChannelData,
							   int totalNumInputChannels,
							   float** outputChannelData,
							   int totalNumOutputChannels,
							   int numSamples);
    void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();
    void setFile(File audioFile);
    
    void pitchTracking(float* dataInput);
    
    CaptureReal* q;

private:
    
    AudioDeviceManager& deviceManager;                          // global device manager
    AudioSourcePlayer audioSourcePlayer;
    AudioFormatReaderSource* fileSource;
    AudioTransportSource transportSource;
    AudioFormatManager formatManager;
    TimeSliceThread playingThread;
    
    AudioSampleBuffer sampleBuffer = AudioSampleBuffer(1,RECORDSIZE); //the buffer is for store;
    AudioSampleBuffer calculateBuffer = AudioSampleBuffer(1,RECORDSIZE); //the buffer is throwing to the pitchtail
    AudioSampleBuffer tempBuffer = AudioSampleBuffer(1,RECORDSIZE); // this buffer is for sliding buffer window
    bool bufferReady;
    int bufferIndex;
};
#endif /* defined(__OnsetReal__FileInputSource__) */
