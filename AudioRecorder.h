
#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class AudioRecorder : public AudioIODeviceCallback
{
public :
    AudioRecorder(AudioDeviceManager& deviceManager);
    ~AudioRecorder();

    // method from recorder
    void startRecording(const File& file);
    void stop();
    bool isRecording() const;
    // general method
    void audioDeviceIOCallback(const float** inputChannelData,
							   int totalNumInputChannels,
							   float** outputChannelData,
							   int totalNumOutputChannels,
							   int numSamples);
	
	void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();

private:
    //variable from recording
    TimeSliceThread backgroundThread; // the thread that will write our audio data to disk
    ScopedPointer<AudioFormatWriter::ThreadedWriter> threadedWriter; // the FIFO used to buffer the incoming data
    double sampleRate;
    
    CriticalSection writerLock;
    AudioFormatWriter::ThreadedWriter* volatile activeWriter;
    //AudioDeviceManager audioDeviceManager;
	AudioDeviceManager& deviceManager;    
};
