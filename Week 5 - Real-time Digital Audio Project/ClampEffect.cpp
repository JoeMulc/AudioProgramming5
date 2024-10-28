#include "ClampEffect.h"

void ClampEffect::Process(float* buffer, int numFrames, int numChannels)
{
	for (int i = 0; i < numFrames * numChannels; i++) 
	{
				buffer[i] = tanh(buffer[i]);
	}

}
