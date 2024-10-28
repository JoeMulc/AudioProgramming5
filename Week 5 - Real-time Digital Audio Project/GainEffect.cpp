#include "GainEffect.h"

void GainEffect::Process(float* buffer, int numFrames, int numChannels)
{
	for (int i = 0; i < numFrames * numChannels; i++) {
		buffer[i] *= 2.0;
	}
}
