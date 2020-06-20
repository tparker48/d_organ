#include "MainComponent.h"

#define WINFILE_LO "C:\\Users\\Tom\\Desktop\\synthProject\\TownHallOrgan_SP\\TownHallOrgan_SP\\Samples\\PRE1\\P_11_Pre1_F0_RR1.wav"
#define RPIFILE_LO "~/Desktop/d_organ/organ samples/1/P_11_Pre1_F0_RR1.wav"
#define RPIFILE_HI "~/Desktop/d_organ/organ samples/1/K_107_Pre1_F4_RR1.wav"

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

    AudioFormatReader* reader = formatManager.createReaderFor(File(RPIFILE_LO));
    audioLo.setSize(1, windowSizeLo, false, true, false);
    reader->read(&audioLo, 0, windowSizeLo, startSampleLo, true, true);
    delete reader;
    float baseFreq = 87.307;
    dorgan.addVoice(new OrganOsc(&audioLo, baseFreq, 0, knobs));
    
    int startSampleHi = 195046;
    int endSampleHi = 576658;
    int windowSizeHi = endSampleHi - startSampleHi + 1;

    reader = formatManager.createReaderFor(File(RPIFILE_HI));
    audioHi.setSize(1, windowSizeHi, false, true, false);
    reader->read(&audioHi, 0, windowSizeHi, startSampleHi, true, true);
    delete reader;
    baseFreq = 1396.913;
    dorgan.addVoice(new OrganOsc(&audioHi, baseFreq, 1, knobs));
    dorgan.addVoice(new OrganOsc(&audioHi, baseFreq, 2, knobs));
    
    dorgan.clearSounds();
    dorgan.addSound(new DOrganSound());
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    dorgan.setCurrentPlaybackSampleRate(sampleRate);
    std::cout << sampleRate << std::endl;
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    dorgan.renderNextBlock(*(bufferToFill.buffer), trash, bufferToFill.startSample, bufferToFill.numSamples);
    filter.setCoefficients(IIRCoefficients::makeLowPass(44100, 100.0 + knobs->readNormalized(0,3)*2500.0));
    filter.processSamples(bufferToFill.buffer->getWritePointer(0,0),bufferToFill.numSamples);
}

MainComponent::~MainComponent() 
{
    knobs->stop();
    shutdownAudio();
}

void MainComponent::releaseResources() {}
void MainComponent::paint(Graphics& g) {}
void MainComponent::resized() {}
