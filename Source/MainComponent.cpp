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

    knobs = new PotReader();
    knobs->start(MODE == WINDOWS);

    dorgan.clearVoices();

    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    AudioFormatReader* reader;

    std::string root;
    if (MODE == RPI) root = RPI_PATH;
    else if (MODE == WINDOWS)
    {
        root = WIN_PATH;
    }
    
    std::string path[4] = { root + OSC1, root + OSC2, root + OSC3, root + OSC4 };

    int startSample[4] = {191179, 187455, 189156, 188332};
    int endSample[4] = {564427, 551954, 559243, 552831};
    int windowSize;

    float baseFreq[4] = { 34.65f, 233.08f, 185.0f, 493.88f };
    
    for (int i = 0; i < 4; i++)
    {
        // Compute length of audio, initialize the sample buffer
        windowSize = endSample[i] - startSample[i];
        oscAudio[i].setSize(1, windowSize, false, true, false);

        // Read the wav file and fill the sample buffer
        reader = formatManager.createReaderFor(File( path[i] ));
        reader->read(&(oscAudio[i]), 0, windowSize, startSample[i], true, true);
        delete reader;

        // Instantiate the oscillator voice
        dorgan.addVoice(new OrganOsc(&oscAudio[i], baseFreq[i], i, knobs));
    }

    dorgan.clearSounds();
    dorgan.addSound(new DOrganSound());
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    dorgan.setCurrentPlaybackSampleRate(sampleRate);
    moogFilter.init((float)sampleRate);
    crackleFilter.init((float)sampleRate);
    crackleFilter.set(20000.0f, 0.0f);
    filterCutoff.init(0.0f, 0.3f);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    dorgan.renderNextBlock(*(bufferToFill.buffer), trash, bufferToFill.startSample, bufferToFill.numSamples);

    
    float resonance = (knobs->readNormalized(1, 5));
    filterCutoff.setValue(300.0f + knobs->readLogarithmic(1, 4) * 20000.0f);

    moogFilter.set(filterCutoff.getValue(), resonance);
    moogFilter.processBlock(bufferToFill, LOWPASS);
    crackleFilter.processBlock(bufferToFill, LOWPASS);
}

MainComponent::~MainComponent() 
{
    knobs->stop();
    shutdownAudio();
}

void MainComponent::releaseResources() {}
void MainComponent::paint(Graphics& g) {}
void MainComponent::resized() {}
