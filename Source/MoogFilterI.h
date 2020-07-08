#pragma once
#include <JuceHeader.h>

class MoogFilterI
{
public:
	MoogFilterI();
	void init();
	void calc();
	float process(float x);
	void processBlock(const AudioSourceChannelInfo& bufferToFill);
	~MoogFilterI();
	float getCutoff();
	void setCutoff(float c);
	float getRes();
	void setRes(float r);
	void setSaturationAmount(float amount);

protected:
	float saturate(float input);

	float cutoff;
	float res;
	float fs;
	float y1, y2, y3, y4;
	float oldx;
	float oldy1, oldy2, oldy3;
	float x;
	float r;
	float p;
	float k;

	float saturationAmount;
	const float saturationLimit = 0.95;
};