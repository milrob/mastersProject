/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_63FD855A234897E__
#define __JUCE_HEADER_63FD855A234897E__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "LoopGenerator.h"
#include "WaveformDisplay.h"
#include "essentia.h"
#include "algorithmfactory.h"
#include "pool.h"
#include "PreSynthesis.h"
#include "MATRIX.h"
//for convenience, probably bad practice though
#define VAR essentia::Real
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
 TO DO:
    Restructure program: use these separate components for the synthesis, analysis,
    and GUI

                                                                    //[/Comments]
*/
class AudioApp  : public Component,
                  public ChangeListener,
                  public ButtonListener,
                  public SliderListener,
                  public Timer,
                  public drow::AudioFilePlayer::Listener
{
public:
    //==============================================================================
    AudioApp ();
    ~AudioApp();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    enum TransportState{
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping,
        Looping,
        ShiftyLooping
    };

    float gain;
    juce::Logger* masterLogger;

    void changeState(TransportState newState);
    void changeListenerCallback(ChangeBroadcaster* src);
    void shiftyLooping();
    void printCurrentState(String s);


    void fileChanged(drow::AudioFilePlayer* player) override;
    void audioFilePlayerSettingChanged(drow::AudioFilePlayer* player, int settingCode) override;
    void timerCallback() override;
    void playerStoppedOrStarted(drow::AudioFilePlayer* player) override;

    WaveformDisplay waveform;
    //ScopedPointer<drow::PositionableWaveDisplay> posDisplay;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* sl490x_png;
    static const int sl490x_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    const int APP_WIDTH = 700, APP_HEIGHT = 750;
    AudioDeviceManager       deviceManager;
    AudioSourcePlayer        sourcePlayer;
    drow::AudioFilePlayerExt mediaPlayer;
    drow::AudioFilePlayer::Listener* listener;

    TransportState state;
    std::string AUDIO_FILENAME;
    std::vector<Loop> crudeLoops;

    Loop* currentLoop;
    MATRIX* similarity;
    juce::ScopedPointer<MATRIX> transMat;
    //MemoryInputStream stream;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> infoLabel;
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<TextButton> playButton;
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<TextButton> settingsButton;
    ScopedPointer<ToggleButton> loopButton;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Label> gainLabel;
    ScopedPointer<ToggleButton> shiftyLoopingButton;
    ScopedPointer<ImageComponent> backgroundImg;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioApp)
};

//[EndFile] You can add extra defines here...

//[/EndFile]

#endif   // __JUCE_HEADER_63FD855A234897E__
