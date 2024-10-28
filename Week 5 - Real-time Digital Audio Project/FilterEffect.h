#pragma once
#include "AudioEffect.h"
class FilterEffect : public AudioEffect
{
public:

	void Process(float* buffer, int numFrames, int numChannels);

	float LowPassFilter(float input);

private:

	float prev = 0;
};

