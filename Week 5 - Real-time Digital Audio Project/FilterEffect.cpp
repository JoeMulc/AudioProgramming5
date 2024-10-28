#include "FilterEffect.h"

void FilterEffect::Process(float* buffer, int numFrames, int numChannels)
{
	for (int i = 0; i < numFrames * numChannels; i++) 
	{
		switch (filter)
		{
		case (Filters::LowPass):
			buffer[i] = LowPassFilter(buffer[i]);
			//std::cout << "Low" << std::endl;
			break;
		case (Filters::HighPass):
			buffer[i] = buffer[i] - LowPassFilter(buffer[i]);
			//std::cout << "High" << std::endl;
			break;
		case (Filters::BandPass):
			buffer[i] = LowPassFilter(buffer[i] - LowPassFilter(buffer[i]));
			//std::cout << "Band" << std::endl;
			break;
		case (Filters::SteepLowPass):
			buffer[i] = LowPassFilter(LowPassFilter(buffer[i]));
			//std::cout << "Steep" << std::endl;
		default:
			break;
		}
		
	}
}

float FilterEffect::LowPassFilter(float input)
{
	float output;

	output = prev + ((input - prev) * coeff);

	prev = output;

	return output;
}