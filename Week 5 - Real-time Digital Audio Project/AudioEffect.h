//	AudioEffect.h - Base class for any audio effects you code in lab 6.

#pragma once
#include <iostream>
#include <vector>
#include <string>
///	Base class for any audio effects you code in lab 6.
/*!
	It's up to you to inherit from this class to create your own audio effects,
	and to determine how to hook it up to your existing audio code.
 */

enum effects {
	Gain,
	Clamp
};

enum Filters
{
	LowPass,
	HighPass,
	BandPass,
	SteepLowPass
};

class AudioEffect
{
public:
	virtual ~AudioEffect() {}

	///	Inherit this function to process the passed-in buffer of audio.
	/*!
		\param buffer		A buffer of audio data to process. The result of
							your processing should be written into this buffer.
		\param numFrames	The number of frames of audio data in buffer. You
							can use this to calculate the total size of buffer:
							buffer size = numFrames * numChannels.
		\param numChannels	The number of channels of audio data contained in
							the buffer. If you are using sokol_audio or dr_wav,
							you can assume multi-channel audio data will be
							*interleaved* in buffer.
	 */

	virtual void Process(float* buffer, int numFrames, int numChannels) = 0;


	//OLD CODE FROM WORSE IMPLEMENTATION DEMONSTRATING ZERO PLOYMORPHISM
	//void doEffect(float* buffer, int numFrames, int numChannels, effects e)
	//{
	//	switch (e)
	//	{
	//		case (effects::Gain):
	//			gain(buffer, numFrames, numChannels);
	//			break;
	//		case (effects::Clamp):
	//			clamp(buffer, numFrames, numChannels);
	//			break;
	//	}
	//}
	//
	//void gain(float* buffer, int numFrames, int numChannels)
	//{
	//	for (int i = 0; i < numFrames * numChannels; i++) {
	//		buffer[i] *= 2.0;  
	//	}
	//}
	//
	//void clamp(float* buffer, int numFrames, int numChannels)
	//{
	//	for (int i = 0; i < numFrames * numChannels; i++) {
	//		buffer[i] = tanh(buffer[i]);
	//	}
	//}

	///	Inherit this function if your effect needs to know the samplerate.
	/*!
		Not all effects need to know the samplerate, but any that rely on
		temporal calculations (e.g. delay, filters, reverbs, etc.) will need
		this information.
	 */
	virtual void setSamplerate(float val) {
	}

	void SetCoeff(float newCoeff)
	{
		coeff = newCoeff;
	}

	void SetFilter(Filters newFilter) 
	{
		filter = newFilter;
	}

protected:
	float coeff = 0.5f;
	Filters filter = Filters::LowPass;

	//delay stuff
	float maxDelayTime = 0.5;

};
