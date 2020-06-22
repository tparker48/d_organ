#include "MainComponent.h"
#include "PreprocessorDefinitions.h"

#ifdef RUNNING_WINDOWS "Windows"
const std::string MODE = WINDOWS;
#endif

#ifdef RUNNING_RPI
const std::string MODE = RPI;
#endif

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

    int startSample[4] = {186678, 187455, 189156, 188332};
    int endSample[4] = {551178, 551954, 559243, 552831};
    int windowSize;

    float baseFreq[4] = { 32.7f, 233.08f, 185.0f, 493.88f };
    
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
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    dorgan.renderNextBlock(*(bufferToFill.buffer), trash, bufferToFill.startSample, bufferToFill.numSamples);
    filter.setCoefficients(IIRCoefficients::makeLowPass(44100, 100.0 + knobs->readNormalized(1,4)*2500.0));
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
