#pragma once
#include <JuceHeader.h>
#include <cmath>
#include "DOrganSound.h"
#include "MCP3008.h"

class DOrganVoice : public SynthesiserVoice
{
public:
    
    DOrganVoice(int num)
    {
        this->num = num;
        frequency = (float)mcp.mcp3008_value(0, 11, 9, 10, 23);
        frequency = (float)mcp.mcp3008_value(0, 11, 9, 10, 25);
        frequency = (float)mcp.mcp3008_value(0, 11, 9, 10, 8);
        newFrequency = frequency;
        //frequency = 440.0;
        float secondsPerSample = 1.0 / 44100.0;
        delta = frequency * secondsPerSample * 2.0f * MathConstants<float>::pi;
        theta = 0.0;
        counter = 0;
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
            
            counter++;
            float secondsPerSample = 1.0 / 44100.0;
            if((counter + (200*num)) % 2000== 0){
                newFrequency = (float)mcp.mcp3008_value(num, 11, 9, 10, 23);
                newFrequency = (float)mcp.mcp3008_value(num, 11, 9, 10, 25);
                newFrequency = 100.0 + 700.0*(((float)mcp.mcp3008_value(num, 11, 9, 10, 8))/1024.0);
                counter=0;
            }
            if (std::abs(newFrequency - frequency) < 0.1)
            {
                frequency = newFrequency;
            }
            else
            {
                frequency += (newFrequency-frequency)/500.0;
            }
            delta = frequency * secondsPerSample * 2.0f * MathConstants<float>::pi;
        }
    }

    // required instantiations, but not useful for this application
    bool canPlaySound(SynthesiserSound* sound) { return dynamic_cast<DOrganSound*>(sound) != nullptr;}
    void startNote(int, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {}
    void stopNote(float velocity, bool allowTailOff) {}
    void pitchWheelMoved(int newPitchWheelValue) {}
    void controllerMoved(int controllerNumber, int newControllerValue) {}

private:
    JUCE_GPIO::MCP3008 mcp;
    int counter;
    int num;
    float frequency, newFrequency;
    float theta, delta;
};
