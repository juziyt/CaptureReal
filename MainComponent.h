/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  21 Sep 2012 12:11:41pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_2983595F__
#define __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_2983595F__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioRecorder.h"
#include "LiveStreaming.h"
#include "AudioFileSource.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public Component,
                       public ButtonListener, public Timer
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void visibilityChanged();

    void timerCallback();

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioDeviceManager deviceManager;
    ScopedPointer<AudioRecorder> recorder;
    ScopedPointer<LiveStreaming> streaming;
    //[/UserVariables]
    
    //==============================================================================
//    Label* helloWorldLabel;
    Path internalPath1;
    
    ScopedPointer<Label> title;
    ScopedPointer<Label> thresholdLabel;
    ScopedPointer<Label> thresholdValueLabel;
    ScopedPointer<Label> chordValueLabel;
    ScopedPointer<Label> sensitivityLabel;
    
    ScopedPointer<TextButton> quitButton;
    ScopedPointer<TextButton> streamButton;
    ScopedPointer<TextButton> loadfileButton;
    ScopedPointer<TextButton> thresholdup;
    ScopedPointer<TextButton> thresholddown;
    ScopedPointer<TextButton> chordtypeButton;
    
    ScopedPointer<Label> chordLabel;
    
    
    File currentFile;
    ScopedPointer<AudioFileSource> player;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif   // __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_2983595F__
