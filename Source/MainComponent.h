#pragma once

#include <JuceHeader.h>
#include "DOrganSound.h"
#include "OrganOsc.h"
#include "PotReader.h"

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
    AudioBuffer<float> audioLo,audioHi;
    
    IIRFilter filter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
