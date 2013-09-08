
#include "AudioFileSource.h"

AudioFileSource::AudioFileSource(AudioDeviceManager& deviceManager_):deviceManager(deviceManager_), playingThread("file audio IO")
{
    AudioDeviceManager::AudioDeviceSetup config;
    deviceManager.getAudioDeviceSetup(config);
    config.bufferSize = 512;
    
    deviceManager.setAudioDeviceSetup(config, true);
    
    formatManager.registerBasicFormats();
    audioSourcePlayer.setSource(&transportSource);
    deviceManager.addAudioCallback(this);
    playingThread.startThread();
    
    bufferReady = false;
    bufferIndex = 0;
    
    q = new CaptureReal(RECORDSIZE);

}

AudioFileSource::~AudioFileSource()
{
    deviceManager.removeAudioCallback(this);
    transportSource.setSource(0);
    deleteAndZero(fileSource);
    audioSourcePlayer.setSource(0);
    
    delete q;
}

void AudioFileSource::setFile(File audioFile)
{
    AudioFormatReader* tempReader = formatManager.createReaderFor(audioFile);
    fileSource = new AudioFormatReaderSource(tempReader,true);
    transportSource.setSource(fileSource,32768,&playingThread,tempReader->sampleRate);
    transportSource.start();
}

void AudioFileSource::audioDeviceIOCallback(const float** inputChannelData,
                                            int totalNumInputChannels,
                                            float** outputChannelData,
                                            int totalNumOutputChannels,
                                            int numSamples)
{
     //pass the output to the player
    
    if (bufferReady == true)
    {
        pitchTracking(calculateBuffer.getSampleData(0));
        bufferReady = false;
    }
    
    if (bufferReady == false)
    {
        sampleBuffer.copyFrom(0, 0, outputChannelData[0], numSamples);
        tempBuffer.copyFrom(0, 0, calculateBuffer, 0, numSamples, RECORDSIZE - numSamples);
        calculateBuffer.clear();
        tempBuffer.copyFrom(0, RECORDSIZE - numSamples, sampleBuffer, 0, 0, numSamples);
        calculateBuffer.copyFrom(0, 0, tempBuffer, 0, 0, RECORDSIZE);
        tempBuffer.clear();
        bufferReady = true;
        sampleBuffer.clear();
    }
    
    audioSourcePlayer.audioDeviceIOCallback (inputChannelData, totalNumInputChannels, outputChannelData, totalNumOutputChannels, numSamples);  
    
}

void AudioFileSource::pitchTracking(float* data)
{
    float* d = new float[RECORDSIZE];
    for( int i=0; i<RECORDSIZE; i++)
        d[i] = data[i]*32768;
    
    q->pitcher(d);
    
    delete d;
        
}

void AudioFileSource::audioDeviceAboutToStart(AudioIODevice* device)
{
    audioSourcePlayer.audioDeviceAboutToStart (device);
}

void AudioFileSource::audioDeviceStopped()
{
    audioSourcePlayer.audioDeviceStopped();
}
