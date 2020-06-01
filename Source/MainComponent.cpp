#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(1, 1);

    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
        && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request(RuntimePermissions::recordAudio,
            [&](bool granted) { if (granted)  setAudioChannels(2, 2); });
    }
    else
    {
        setAudioChannels(0, 1);
    }

    dorgan.clearVoices();
    dorgan.addVoice(new DOrganVoice(0));
    dorgan.addVoice(new DOrganVoice(1));
    dorgan.addVoice(new DOrganVoice(2));
    dorgan.addVoice(new DOrganVoice(3));

    dorgan.clearSounds();
    dorgan.addSound(new DOrganSound());
    
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    dorgan.setCurrentPlaybackSampleRate(sampleRate);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    //dorgan.noteOn(1, 1, 0.0);
    dorgan.renderNextBlock(*(bufferToFill.buffer), trash, bufferToFill.startSample, bufferToFill.numSamples);
}

MainComponent::~MainComponent() {shutdownAudio();}
void MainComponent::releaseResources() {}
void MainComponent::paint(Graphics& g) {}
void MainComponent::resized() {}
