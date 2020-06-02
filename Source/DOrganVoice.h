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
        this->knobs = knobs;

        frequency = 440.0;
        float secondsPerSample = 1.0 / 44100.0;
        delta = frequency * secondsPerSample * 2.0f * MathConstants<float>::pi;
        theta = 0.0;
    }

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
            
        for (int sample = startSample; sample < numSamples; sample++)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, sample, std::sin(theta));
                
            }
            
            theta += delta;
            if(theta >= 2.0f * MathConstants<float>::pi)
            {
                theta -= 2.0f * MathConstants<float>::pi;
            }
 
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

    PotReader* knobs;
};
