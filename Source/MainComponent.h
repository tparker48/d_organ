#pragma once

#include <JuceHeader.h>
#include "DOrganSound.h"
#include "OrganOsc.h"
#include "StilsonMoogFilter.h"
//#include "MoogFilterII.h"
#include "PotReader.h"
#include "PreprocessorDefinitions.h"

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
    const MidiBuffer trash;

    PotReader* knobs;
    AudioBuffer<float> oscAudio[4];
    
    StilsonMoogFilter moogFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
