#include "DelayEffect.h"

DelayEffect::DelayEffect()
{

}

void DelayEffect::Process(float* buffer, int numFrames, int numChannels)
{
	for (int i = 0; i < numFrames * numChannels; i++)
	{
		ringBuffer[j] = buffer[i];

		if (j = ringBuffer.size())
		{
			j = 0;
		}
		else
		{
			j = j + 1;
		}
	}
}

void DelayEffect::setSamplerate(float val)
{
	sampleRate = val;

	ringBuffer = std::vector<float>(maxDelayTime * sampleRate);
}