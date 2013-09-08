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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent():quitButton (0)
{
    addAndMakeVisible (quitButton = new TextButton (String::empty));
    quitButton->setButtonText ("Quit");
    quitButton->addListener (this);
    
    addAndMakeVisible (title = new Label (String::empty, "Pitch Tail Demo"));
    title->setFont (Font (20.00f, Font::plain));
    title->setJustificationType (Justification::topLeft);
    title->setEditable (false, false, false);
    title->setColour (TextEditor::textColourId, Colours::black);
    title->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (sensitivityLabel = new Label (String::empty, "Chord Type"));
    sensitivityLabel->setFont(Font (16.00f, Font::plain));
    sensitivityLabel->setJustificationType (Justification::topLeft);
    sensitivityLabel->setEditable(false, false, false);
    sensitivityLabel->setColour (TextEditor::textColourId, Colours::black);
    sensitivityLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (thresholdLabel = new Label (String::empty, "Onset Threshold"));
    thresholdLabel->setFont(Font (16.00f, Font::plain));
    thresholdLabel->setJustificationType (Justification::topLeft);
    thresholdLabel->setEditable(false, false, false);
    thresholdLabel->setColour (TextEditor::textColourId, Colours::black);
    thresholdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible(streamButton = new TextButton(String::empty));
    streamButton->setButtonText("Streaming off");
    streamButton->addListener(this);
    streamButton->setColour (TextButton::buttonColourId, Colours::purple);
    streamButton->setColour (TextButton::textColourOnId, Colours::black);
    
    addAndMakeVisible(loadfileButton = new TextButton(String::empty));
    loadfileButton->setButtonText("Load Audio File");
    loadfileButton->addListener(this);
    loadfileButton->setColour (TextButton::buttonColourId, Colours::purple);
    loadfileButton->setColour (TextButton::textColourOnId, Colours::black);
    
    addAndMakeVisible(thresholdup = new TextButton(String::empty));
    thresholdup->setButtonText("increase");
    thresholdup->addListener(this);
    thresholdup->setColour (TextButton::buttonColourId, Colours::yellow);
    thresholdup->setColour (TextButton::textColourOnId, Colours::black);
    
    addAndMakeVisible(thresholddown = new TextButton(String::empty));
    thresholddown->setButtonText("decrease");
    thresholddown->addListener(this);
    thresholddown->setColour (TextButton::buttonColourId, Colours::yellow);
    thresholddown->setColour (TextButton::textColourOnId, Colours::black);
    
    addAndMakeVisible(thresholdValueLabel = new Label(String::empty, "1"));
    thresholdValueLabel->setFont (Font (15.0000f, Font::bold));
    thresholdValueLabel->setJustificationType (Justification::centred);
    thresholdValueLabel->setEditable (false, false, false);
    thresholdValueLabel->setColour (Label::textColourId, Colours::white);
    thresholdValueLabel->setColour(Label::backgroundColourId, Colours::black);
    
    addAndMakeVisible(chordtypeButton = new TextButton(String::empty));
    chordtypeButton->setButtonText("Sensitivity -- High");
    chordtypeButton->addListener(this);
    chordtypeButton->setColour (TextButton::buttonColourId, Colours::yellow);
    chordtypeButton->setColour (TextButton::textColourOnId, Colours::black);
    
    addAndMakeVisible (chordLabel = new Label (String::empty, "Chord"));
    chordLabel->setFont(Font (16.00f, Font::plain));
    chordLabel->setJustificationType (Justification::topLeft);
    chordLabel->setEditable(false, false, false);
    chordLabel->setColour (TextEditor::textColourId, Colours::black);
    chordLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(chordValueLabel = new Label(String::empty, "no chord"));
    chordValueLabel->setFont (Font (15.0000f, Font::bold));
    chordValueLabel->setJustificationType (Justification::centred);
    chordValueLabel->setEditable (false, false, false);
    chordValueLabel->setColour (Label::textColourId, Colours::white);
    chordValueLabel->setColour(Label::backgroundColourId, Colours::black);

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    deviceManager.initialise(2, /* number of input channels */
                                  2, /* number of output channels */
                                  0, /* no XML settings*/
                                  true, /* select default device on failure */
                                  String::empty, /* preferred device name */
                                  0 /* preferred setup options */);
    
//    AudioDeviceManager::AudioDeviceSetup config;
//    deviceManager.setAudioDeviceSetup(config, true);
    recorder = new AudioRecorder(deviceManager);

    startTimer(10);

    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]
    recorder=nullptr;
   
    title= nullptr;
    thresholdLabel = nullptr;
    sensitivityLabel = nullptr;
    streamButton = nullptr;
    loadfileButton = nullptr;
    chordtypeButton = nullptr;
    thresholdup = nullptr;
    thresholddown = nullptr;
    thresholdValueLabel = nullptr;
    quitButton = nullptr;
    chordLabel = nullptr;
    chordValueLabel = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::lightgrey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    quitButton->setBounds (getWidth() - 176, getHeight() - 60, 120, 32);
    streamButton->setBounds (getWidth()/4 - 100, getHeight()/3-50, 200, 32);
    loadfileButton->setBounds (getWidth()/4 - 100, getHeight()/3, 200, 32);
    title->setBounds (getWidth()/2-60, 20, 400, 200);
    thresholdLabel->setBounds(getWidth()/4 - 100, getHeight()/3+50, 200, 32);
    thresholdup->setBounds(getWidth()/4 - 100, getHeight()/3+80, 100, 32);
    thresholddown->setBounds(getWidth()/4, getHeight()/3+80, 100, 32);
    thresholdValueLabel->setBounds(getWidth()/4 - 100, getHeight()*2/3, 200, 40);
    
    sensitivityLabel->setBounds(getWidth()/2 + 50, getHeight()/3-60, 200, 32);
    chordtypeButton->setBounds(getWidth()/2 + 50, getHeight()/3, 200, 32);
    
    chordLabel->setBounds(getWidth()/2 + 50, getHeight()/2+20, 100, 32);
    chordValueLabel -> setBounds(getWidth()/2+50 , getHeight()*2/3, 150, 50);
    
    internalPath1.clear();
    internalPath1.startNewSubPath (136.0f, 80.0f);
    internalPath1.quadraticTo (176.0f, 24.0f, 328.0f, 32.0f);
    internalPath1.quadraticTo (472.0f, 40.0f, 472.0f, 104.0f);
    internalPath1.quadraticTo (472.0f, 192.0f, 232.0f, 176.0f);
    internalPath1.lineTo (184.0f, 216.0f);
    internalPath1.lineTo (200.0f, 168.0f);
    internalPath1.quadraticTo (96.0f, 136.0f, 136.0f, 80.0f);
    internalPath1.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == quitButton)
    {
        //[UserButtonCode_quitButton] -- add your button handler code here..

        JUCEApplication::quit();

        //[/UserButtonCode_quitButton]
    }
    
    if (buttonThatWasClicked == streamButton)
    {
        if (!streaming)
        {
            player = nullptr;
            streaming = new LiveStreaming(deviceManager);
            streamButton->setButtonText("Streaming on");
            streamButton->setColour(TextButton::buttonColourId, Colours::yellow);
        }
        else
        {
            streaming = nullptr;
            streamButton->setButtonText("Streaming off");
            streamButton->setColour(TextButton::buttonColourId, Colours::purple);
        }
    }
    
    if (buttonThatWasClicked == loadfileButton)
    {
        if (!streaming)
        {
            // load audio file here
            FileChooser chooser (("Choose file to open"),File::nonexistent,"*",true);
            chooser.browseForFileToOpen();
            currentFile = File(chooser.getResult());
            if (!player)
            {
                player = new AudioFileSource(deviceManager);
                player->setFile(currentFile);
                std::cout<< "load file: "<<currentFile.getFileName()<<std::endl;
            }

        }
    }
    
    if (buttonThatWasClicked == thresholdup)
    {
        if (streaming)
        {
            streaming->q->threshold += 0.2;
            if(streaming->q->threshold>30)
                streaming->q->threshold = 30;
            thresholdup->setColour(TextButton::buttonColourId, Colours::pink);
            thresholdValueLabel->setText((String)streaming->q->threshold, NotificationType::sendNotification);
        }
        else if (player)
        {
            player->q->threshold += 0.2;
            if(player->q->threshold>30)
                player->q->threshold = 30;
            thresholdup->setColour(TextButton::buttonColourId, Colours::pink);
            thresholdValueLabel->setText((String)player->q->threshold, NotificationType::sendNotification);
        }
    }
    if (buttonThatWasClicked == thresholddown)
    {
        if (streaming)
        {
            streaming->q->threshold -= 0.2;
            if(streaming->q->threshold<1)
                streaming->q->threshold = 1;
            thresholddown->setColour(TextButton::buttonColourId, Colours::blue);
            thresholdValueLabel->setText((String)streaming->q->threshold, NotificationType::sendNotification);
        }
        else if (player)
        {
            player->q->threshold -= 0.2;
            if(player->q->threshold<1)
                player->q->threshold = 1;
            thresholddown->setColour(TextButton::buttonColourId, Colours::blue);
            thresholdValueLabel->setText((String)player->q->threshold, NotificationType::sendNotification);
        }
    }

    if (buttonThatWasClicked == chordtypeButton)
    {
        if(streaming){
            if(chordtypeButton->getButtonText() == "Sensitivity -- Low"){
                streaming->q->sensitivity = 1;
                chordtypeButton->setButtonText("Sensitivity -- High");
            }
            else{
                streaming->q->sensitivity = 0;
                chordtypeButton->setButtonText("Sensitivity -- Low");
            }
        }
        else if(player){
            if(chordtypeButton->getButtonText() == "Sensitivity -- Low"){
                player->q->sensitivity = 1;
                chordtypeButton->setButtonText("Sensitivity -- High");
            }
            else{
                player->q->sensitivity = 0;
                chordtypeButton->setButtonText("Sensitivity -- Low");
            }
        }
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainComponent::visibilityChanged()
{
    recorder->stop();
//    recordButton->setButtonText("Record");
}

void MainComponent::timerCallback()
{
    if(streaming)
        chordValueLabel->setText((String)streaming->q->chordDetected, NotificationType::sendNotification);
    else if(player)
        chordValueLabel->setText((String)player->q->chordDetected, NotificationType::sendNotification);
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="600" initialHeight="300">
  <BACKGROUND backgroundColour="ffc1d0ff">
    <PATH pos="0 0 100 100" fill="solid: ffffffff" hasStroke="1" stroke="5.19999981, mitered, butt"
          strokeColour="solid: ff6f6f6f" nonZeroWinding="1">s 136 80 q 176 24 328 32 q 472 40 472 104 q 472 192 232 176 l 184 216 l 200 168 q 96 136 136 80 x</PATH>
  </BACKGROUND>
  <LABEL name="" id="be4f6f2e5725a063" memberName="helloWorldLabel" virtualName=""
         explicitFocusOrder="0" pos="152 80 296 48" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Hello World!" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="40" bold="1" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="bcf4f7b0888effe5" memberName="quitButton" virtualName=""
              explicitFocusOrder="0" pos="176R 60R 120 32" buttonText="Quit"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
