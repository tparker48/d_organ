#pragma once

#include "OrganOsc.h"

const float freqMins[] = { 16.35, 116.54, 92.5, 246.94 };
const float freqRanges[] = { 49.05, 349.62, 277.5, 740.7};
const int freqMCPs[] = { 0,0,0,0 };
const int freqPots[] = { 0,1,2,3 };
const int gainMCPs[] = { 1,1,1,1 };
const int gainPots[] = { 0,1,2,3 };

OrganOsc::OrganOsc(AudioBuffer<float>* audio, float baseFreq,int oscID,PotReader* knobs)
{
    audioBuffer = audio;
    this->baseFreq = baseFreq;
    this->knobs = knobs;

    freqMin = freqMins[oscID];
    freqRange = freqRanges[oscID];
    freqMCP = freqMCPs[oscID];
    freqPot = freqPots[oscID];
    gainMCP = gainMCPs[oscID];
    gainPot = gainPots[oscID];

    offset = 0;
    increment = 0.0;
}

void OrganOsc::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    increment = getFrequency() / baseFreq;
    int sampleIndex;
    float samp;
    float gain = getGain();
    for (int sample = startSample; sample < numSamples; sample++)
    {
        sampleIndex = floor(increment * sample);
        samp = gain * audioBuffer->getSample(0, (sampleIndex + offset) % audioBuffer->getNumSamples());

        outputBuffer.addSample(0, startSample + sample, samp);
    }
    offset += floor(increment * numSamples);
    offset %= audioBuffer->getNumSamples();
}

float OrganOsc::getFrequency()
{
    return freqMin + (freqRange * knobs->readNormalized(freqMCP, freqPot));
}

float OrganOsc::getGain()
{
    return knobs->readNormalized(gainMCP, gainPot);
}