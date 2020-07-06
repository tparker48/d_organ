#pragma once

#include <JuceHeader.h>

class LFO
{
public:
	// updateInterval is the number of samples inbetween calls to getValue()
	// If you intend to call getValue per-sample, updateInterval = 1
	// If you intend to call getValue per-buffer, updateInterval = numSamples of the buffer
	LFO(int updateInterval,float sampleRate);
	
	void setFrequency(float hz);
	void setUpdateInterval(int updateInterval);

	// range [0..1]
	float getValue();

private:
	virtual float wave(float angleInRadians) = 0;

	int updateInterval;

	float twoPi;
	float sampleRate;
	float theta, delta, deltaPerUpdate;
};

class SampleHoldLFO : public LFO
{
public:
	SampleHoldLFO(int updateInterval, float sampleRate);

private:
	float wave(float angleInRadians);
	Random numberGenerator;
	float holdValue, lastTheta;
};

class SquareLFO : public LFO
{
public:
	SquareLFO(int updateInterval, float sampleRate);
private:
	float wave(float angleInRadians);
};

class SinLFO : public LFO
{
public:
	SinLFO(int updateInterval, float samplerate);
private:
	float wave(float angleInRadians);
};

class SinSampleHoldLFO : public LFO
{
public:
	SinSampleHoldLFO(int updateInterval, float sampleRate);
	// 0..1 range. 0 for pure sin, 1 for pure SH, anything inbetween mixes the two
	void setMix(float ratio);

private:
	float wave(float angleInRadians);
	Random numberGenerator;
	float holdValue, lastTheta;
	float mix;
};