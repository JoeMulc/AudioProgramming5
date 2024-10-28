#pragma once
#include "AudioEffect.h"
class ClampEffect : public AudioEffect
{
public:
	void Process(float* buffer, int numFrames, int numChannels);
};

