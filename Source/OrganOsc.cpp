#include "OrganOsc.h"

const float freqMins[] = { 17.325, 116.54, 92.5, 246.94 };
const float freqRanges[] = { 51.975, 349.62, 277.5, 740.7};

const int freqMCPs[] = { 0,0,0,0 };
const int freqPots[] = { 0,1,2,3 };
const int gainMCPs[] = { 1,1,1,1 };
const int gainPots[] = { 0,1,2,3 };

const int filterCutoffMCPs[] = { 2,2,2,2 };
const int filterCutoffPots[] = { 0,2,4,6 };
const int filterResonanceMCPs[] = { 2,2,2,2 };
const int filterResonancePots[] = { 1,3,5,7 };

const int filterModes[] = {LOWPASS, LOWPASS, BANDPASS, HIGHPASS};

OrganOsc::OrganOsc(AudioBuffer<float>* audio, float baseFreq,int oscID,PotReader* knobs, float* pitchMultiplier)
{
    audioBuffer = audio;
    this->baseFreq = baseFreq;
    this->knobs = knobs;
    this->pitchMultiplier = pitchMultiplier;

    output.buffer = &outBuffer;
    output.startSample = 0;

    freqMin = freqMins[oscID];
    freqRange = freqRanges[oscID];
    freqMCP = freqMCPs[oscID];
    freqPot = freqPots[oscID];
    gainMCP = gainMCPs[oscID];
    gainPot = gainPots[oscID];
    filterCutoffMCP = filterCutoffMCPs[oscID];
    filterCutoffPot = filterCutoffPots[oscID];
    filterResonanceMCP = filterResonanceMCPs[oscID];
    filterResonancePot = filterResonancePots[oscID];

    offset = 0;
    increment = 0.0;

    gainMax = .25;

    filterMode = filterModes[oscID];
    filter.init((float)getSampleRate());
    //filter.setSaturationAmount(0.0);
}

void OrganOsc::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    increment = getFrequency() / baseFreq;
    int sampleIndex;
    float samp;
    float gain = getGain();

    if (output.buffer->getNumSamples() < numSamples)
    {
        output.buffer->setSize(1, numSamples, false, false, true);
        output.numSamples = numSamples;
    }

    for (int sample = 0; sample < numSamples; sample++)
    {
        sampleIndex = floor(increment * sample);
        samp = gain * getInterpolatedSample(sampleIndex + offset);

        output.buffer->setSample(0, sample, samp);
    }

    updateFilter();
    filter.processBlock(output, filterMode);

    for (int sample = 0; sample < numSamples; sample++)
    {
        outputBuffer.addSample(0, sample + startSample, output.buffer->getSample(0, sample));
    }

    offset += floor(increment * numSamples);
    offset %= audioBuffer->getNumSamples();
}

float OrganOsc::getFrequency()
{
    return (freqMin + (freqRange * knobs->readNormalized(freqMCP, freqPot)))*(*pitchMultiplier);
}

float OrganOsc::getGain()
{
    return knobs->readNormalized(gainMCP, gainPot)*gainMax;
}

void OrganOsc::updateFilter()
{
    float cutoff = 350.0f + 20000.0f * knobs->readLogarithmic(filterCutoffMCP, filterCutoffPot);
    float resonance = knobs->readNormalized(filterResonanceMCP, filterResonancePot);
    filter.set(cutoff,resonance);
}

float OrganOsc::getInterpolatedSample(float index)
{
    float lo = floor(index);
    float hi = ceil(index);
    float ratio = (index - lo);

    if (lo >= audioBuffer->getNumSamples()) lo -= audioBuffer->getNumSamples();
    if (hi >= audioBuffer->getNumSamples()) hi -= audioBuffer->getNumSamples();
    
    return interpolate(audioBuffer->getSample(0, (lo)), audioBuffer->getSample(0, (hi)), ratio);
}


float OrganOsc::interpolate(float a, float b, float ratio)
{
    return ((1.0f - ratio) * a) + (ratio * b);
}
