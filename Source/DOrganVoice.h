#pragma once
#include <JuceHeader.h>
#include <cmath>
#include "DOrganSound.h"
#include "PotReader.h"

class DOrganVoice : public SynthesiserVoice
{
public:
    
    DOrganVoice(PotReader* knobs)
    {
        theta = 0.0f;
        frequency = 440.0f;
        
        twoPi = 2.0f * MathConstants<float>::pi;
        secondsPerSample = 1.0f / 44100.0f;
        delta = frequency * secondsPerSample * twoPi;

        this->knobs = knobs;
    }

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
        for (int sample = startSample; sample < numSamples; sample++)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, sample, std::sin(theta));
                
            }
            updateDelta();
        }
    }
    
    void updateDelta()
    {
        theta += delta;
        if(theta >= twoPi)
        {
            theta -= twoPi;
        }
    }
    
    // required instantiations, but not useful for this application
    bool canPlaySound(SynthesiserSound* sound) { return dynamic_cast<DOrganSound*>(sound) != nullptr;}
    void startNote(int, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {}
    void stopNote(float velocity, bool allowTailOff) {}
    void pitchWheelMoved(int newPitchWheelValue) {}
    void controllerMoved(int controllerNumber, int newControllerValue) {}

private:
    float frequency;
    float theta, delta;
    float twoPi, secondsPerSample;

    PotReader* knobs;
};