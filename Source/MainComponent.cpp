#include "MainComponent.h"

#define WINFILE "C:\\Users\\Tom\\Desktop\\synthProject\\TownHallOrgan_SP\\TownHallOrgan_SP\\Samples\\PRE1\\P_11_Pre1_F0_RR1.wav"
#define RPIFILE "~/Desktop/d_organ/organ samples/1/P_11_Pre1_F0_RR1.wav"

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

    knobs = new PotReader();
    knobs->start();

    dorgan.clearVoices();

    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    int startSampleLo = 205702;
    int endSampleLo = 608161;
    int windowSizeLo = endSampleLo - startSampleLo + 1;

    AudioFormatReader* reader = formatManager.createReaderFor(File(WINFILE));
    audio.setSize(1, windowSizeLo, false, true, false);
    reader->read(&audio, 0, windowSizeLo, startSampleLo, true, true);
    delete reader;
    float baseFreq = 87.307;
    dorgan.addVoice(new OrganOsc(&audio, baseFreq, 0, knobs));

    dorgan.clearSounds();
    dorgan.addSound(new DOrganSound());
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    dorgan.setCurrentPlaybackSampleRate(sampleRate);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    dorgan.renderNextBlock(*(bufferToFill.buffer), trash, bufferToFill.startSample, bufferToFill.numSamples);
}

MainComponent::~MainComponent() 
{
    knobs->stop();
    shutdownAudio();
}

void MainComponent::releaseResources() {}
void MainComponent::paint(Graphics& g) {}
void MainComponent::resized() {}