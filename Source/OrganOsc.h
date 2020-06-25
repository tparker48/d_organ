#pragma once
#include <JuceHeader.h>
#include "DOrganSound.h"
#include "PotReader.h"
#include "StilsonMoogFilter.h"

class OrganOsc : public SynthesiserVoice
{
public:
    OrganOsc(AudioBuffer<float>* audio, float baseFreq, int oscID, PotReader* knobs);

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples);
    
    // required instantiations, but not useful for this application
    bool canPlaySound(SynthesiserSound* sound) { return dynamic_cast<DOrganSound*>(sound) != nullptr;}
    void startNote(int, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {}
    void stopNote(float velocity, bool allowTailOff) {}
    void pitchWheelMoved(int newPitchWheelValue) {}
    void controllerMoved(int controllerNumber, int newControllerValue) {}

private:
    float getFrequency();
    float getGain();
    void updateFilter();

    AudioBuffer<float>* audioBuffer, outBuffer;
    AudioSourceChannelInfo output;
    StilsonMoogFilter filter;
    PotReader* knobs;

    float baseFreq;
    float freqMin, freqRange;
    int freqMCP, gainMCP, freqPot, gainPot;
    int filterCutoffMCP, filterCutoffPot, filterResonanceMCP, filterResonancePot;
    int filterMode;
    
    int offset;
    float increment;
};