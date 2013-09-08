//
//  AudioRecorder.cpp
//  CaptureReal
//
//  Created by Minwei Gu on 6/5/13.
//
//

#include "AudioRecorder.h"

AudioRecorder::AudioRecorder(AudioDeviceManager& deviceManager_): deviceManager(deviceManager_), backgroundThread("Audio Recorder"), sampleRate(0), activeWriter(0)
{
    deviceManager.addAudioCallback(this);
    backgroundThread.startThread();
    
}

AudioRecorder::~AudioRecorder()
{
    stop();
    deviceManager.removeAudioCallback(this);
}

void AudioRecorder::startRecording(const File& file)
{
    stop();
    if (sampleRate > 0)
    {
        // Create an OutputStream to write to our destination file...
        file.deleteFile();
        ScopedPointer<FileOutputStream> fileStream (file.createOutputStream());        
        if (fileStream != 0)
        {
            // Now create a WAV writer object that writes to our output stream...
            WavAudioFormat wavFormat;
            AudioFormatWriter* writer = wavFormat.createWriterFor (fileStream, sampleRate, 1, 16, StringPairArray(), 0);            
            if (writer != 0)
            {
                fileStream.release(); // (passes responsibility for deleting the stream to the writer object that is now using it)
                
                // Now we'll create one of these helper objects which will act as a FIFO buffer, and will
                // write the data to disk on our background thread.
                threadedWriter = new AudioFormatWriter::ThreadedWriter (writer, backgroundThread, 32768);
                
                // And now, swap over our active writer pointer so that the audio callback will start using it..
                const ScopedLock sl (writerLock);
                activeWriter = threadedWriter;
            }
        }
    }
}

void AudioRecorder::stop()
{
    {
        const ScopedLock sl (writerLock);
        activeWriter = 0;
    }
    
    // Now we can delete the writer object. It's done in this order because the deletion could
    // take a little time while remaining data gets flushed to disk, so it's best to avoid blocking
    // the audio callback while this happens.
    threadedWriter = 0;
}

bool AudioRecorder::isRecording() const
{
    return activeWriter !=0;
}

// general setting about audio device start here
void AudioRecorder::audioDeviceAboutToStart(AudioIODevice* device)
{
    sampleRate = device->getCurrentSampleRate();
}

void AudioRecorder::audioDeviceStopped()
{
    sampleRate=0;
}

void AudioRecorder::audioDeviceIOCallback (const float** inputChannelData, int totalNumInputChannels,
                            float** outputChannelData, int numOutputChannels,
                            int numSamples)
{
    const ScopedLock sl (writerLock);
    if (activeWriter != 0)
        activeWriter->write (inputChannelData, numSamples);
    // We need to clear the output buffers, in case they're full of junk..
    for (int i = 0; i < numOutputChannels; ++i)
        if (outputChannelData[i] != 0)
            zeromem (outputChannelData[i], sizeof (float) * numSamples);
}
