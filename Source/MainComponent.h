#pragma once

#include <JuceHeader.h>
#include "PreprocessorDefinitions.h"
#include "DOrganSound.h"
#include "OrganOsc.h"
//#include "StilsonMoogFilter.h"
#include "MoogFilterII.h"
#include "PotReader.h"
#include "SmoothValue.h"
#include "LFO.h"

#ifdef RUNNING_WINDOWS
const std::string MODE = WINDOWS;
#endif

#ifdef RUNNING_RPI
const std::string MODE = RPI;
#endif

class MainComponent : public AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    Synthesiser dorgan;
    MoogFilterII moogFilter, crackleFilter;
    
    PotReader* knobs;
    AudioBuffer<float> oscAudio[4];
    SmoothValue<float> filterCutoff;
    float filterResonance;
    float masterPitchMultiplier;
    
    const MidiBuffer trash;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
