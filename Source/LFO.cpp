#include "LFO.h"

LFO::LFO(int updateInterval, float sampleRate)
{
	twoPi = 2.0f * MathConstants<float>::pi;
	this->sampleRate = sampleRate;
	this->updateInterval = updateInterval;

	delta = 0.0f;
	deltaPerUpdate = 0.0f;
	theta = 0.0f;
}

void LFO::setFrequency(float hz)
{
	if (hz < 0.0f) return;

	float cyclesPerSample = hz / sampleRate;
	delta = cyclesPerSample * twoPi;
	deltaPerUpdate = delta * updateInterval;
}

void LFO::setUpdateInterval(int updateInterval)
{
	if (updateInterval < 1) return;

	this->updateInterval = updateInterval;
	deltaPerUpdate = delta * updateInterval;
}

float LFO::getValue()
{
	theta += deltaPerUpdate;
	if (theta >= twoPi) theta -= twoPi;
	return wave(theta);
}

SinLFO::SinLFO(int updateInterval, float sampleRate)
	:LFO(updateInterval, sampleRate)
{}

float SinLFO::wave(float angleInRadians)
{
	return sin(angleInRadians);
}

SquareLFO::SquareLFO(int updateInterval, float sampleRate)
	:LFO(updateInterval, sampleRate)
{}

float SquareLFO::wave(float angleInRadians)
{
	if (sin(angleInRadians) >= 0.0f) return 1.0f;
	else return -1.0f;
}

SampleHoldLFO::SampleHoldLFO(int updateInterval, float sampleRate)
	:LFO(updateInterval, sampleRate)
{
	holdValue = 0.0f;
	numberGenerator.setSeedRandomly();
}

float SampleHoldLFO::wave(float angleInRadians)
{
	// when theta >= 2PI it resets, so when a decrease occurs we know a cycle has completed
	if (angleInRadians < lastTheta)
	{
		holdValue = 2.0f * numberGenerator.nextFloat() - 1.0f;
	}

	lastTheta = angleInRadians;
	return holdValue;
}



SinSampleHoldLFO::SinSampleHoldLFO(int updateInterval, float sampleRate)
    :LFO(updateInterval,sampleRate)
{
    holdValue = 0.0f;
	numberGenerator.setSeedRandomly();
	mix = 0.5f;
}


void SinSampleHoldLFO::setMix(float ratio)
{
    mix = ratio;
}


float SinSampleHoldLFO::wave(float angleInRadians)
{
    // when theta >= 2PI it resets, so when a decrease occurs we know a cycle has completed
	if (angleInRadians < lastTheta)
	{
		holdValue = 2.0f * numberGenerator.nextFloat() - 1.0f;
	}
	lastTheta = angleInRadians;

	return (mix)*holdValue+(1.0f-mix)*sin(angleInRadians);
}