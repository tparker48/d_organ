#pragma once

#include <JuceHeader.h>
#include "DOrganSound.h"
#include "DOrganVoice.h"

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
    int counter;
    JUCE_GPIO::MCP3008 mcp;
    const MidiBuffer trash;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
