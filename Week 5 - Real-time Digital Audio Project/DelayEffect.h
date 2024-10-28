#pragma once
#include "AudioEffect.h"
class DelayEffect : public AudioEffect
{
public:
	DelayEffect();
	void Process(float* buffer, int numFrames, int numChannels);
	void setSamplerate(float val) ;
	
private:
	float sampleRate;
	std::vector<float> ringBuffer;
	int j = 0;
	int readposition;
};

