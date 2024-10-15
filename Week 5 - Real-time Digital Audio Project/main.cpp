//	main.cpp - Console application forming the basis of the CMP407 week 5 lab.

//We're using the dr_wav single-header library to load .wav files...
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

//...and we're using the sokol_audio single-header library to stream audio data
//to our soundcard.
#define SOKOL_IMPL
#include "sokol_audio.h"

#include <iostream>
#include <vector>
#include <string>

//------------------------------------------------------------------------------
///	This struct will get passed in to audioCallback().
/*!
	Use it to store any data that you want to remain persistent between calls to
	audioCallback().
 */
struct AudioData
{
	//--------------------------------------------------------------------------
	//TODO: Store any persistent variables you want access to in the audio
	//		thread here.
	//--------------------------------------------------------------------------

	std::vector<float> data;
	int playedFrames = 0;
	int numFrames = 0;
	int numChannels= 0;
};

//------------------------------------------------------------------------------
///	Our audio callback. All audio processing happens here.
/*!
	When the function returns our audio data will get passed to the soundcard.
 */
void audioCallback(float *buffer,	//A buffer of float audio samples for us to fill.
				   int numFrames,	//The number of frames in this buffer (you can think of a frame as a multi-channel sample; mono = 1 sample per frame; stereo = 2 samples per frame, etc.).
				   int numChannels,	//The number of channels this buffer represents (1: mono).
				   void *userData)	//Our AudioData struct.
{
	//Get our audio data from the passed-in userData variable.
	AudioData *data((AudioData *)userData);
	//Get the samplerate our soundcard is running at.
	const float samplerate((float)saudio_sample_rate());

	//Just in case...
	if(data)
	{
		for(int i=0;i<numFrames;++i)
		{
			//Note: This boilerplate assumes we're working with mono audio.
			//		What changes might you need to make to support stereo?

			//Clear the buffer to start with (might not be necessary, but it's
			//good practice).
			buffer[i] = 0.0f;

			//------------------------------------------------------------------
			//TODO: Write audio data into buffer here.
			//------------------------------------------------------------------
			if (data->playedFrames == data->numFrames)
			{
				data->playedFrames = 0;
			}

			buffer[i] = data->data[data->playedFrames];
			data->playedFrames++;	
		}	

	}
}

//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	//We store any data we might use in our audio callback in this struct.
	AudioData audioData;

	//--------------------------------------------------------------------------
	//TODO: For the first task, you will want to load Loop.wav here.
	//		(refer back to last week's lab for how to do this)

	//These variables will be set by the dr_wav wave file library in the
	//following function call.
	unsigned int channels;
	unsigned int samplerate;
	drwav_uint64 numFrames;

	//Load our sound file.
	float* data = drwav_open_file_and_read_pcm_frames_f32("Loop.wav",	//Sound file to load.
		&channels,	//On return, the number of channels in the file.
		&samplerate,	//On return, the file's samplerate.
		&numFrames,	//On return, the number of frames (num samples *  numchannels) in the file.
		NULL);

	if (data == nullptr)
	{
		std::cout << "Could not open sound file." << std::endl;

		return 1;
	}

	//Note: dr_wav is a C library, and returns our audio data as a raw float
	//		pointer. To make things easier for ourselves, we'll copy the data
	//		into a C++ vector (vectors are easier to resize if we want to
	//		change the length of the sound).

	std::vector<float> dataVector(data, data + (numFrames * channels));
	audioData.data = dataVector;
	audioData.numChannels = channels;
	audioData.numFrames = numFrames;

	//With that done, we can now free the dr_wav-allocated audio data.
	drwav_free(data, NULL);

	//--------------------------------------------------------------------------

	//Create a sokol_audio audio descriptor, zero its members.
	saudio_desc audioDescriptor = {};

	//Request mono audio.
	audioDescriptor.num_channels = 1;
	//Pass in our audio callback.
	audioDescriptor.stream_userdata_cb = audioCallback;
	//Pass in any user data (stored in the AudioData struct) to the audio callback.
	audioDescriptor.user_data = (void *)&audioData;
	
	//Initialise sokol_audio, and start the soundcard processing audio.
	saudio_setup(&audioDescriptor);

	//Check that we were able to initialise sokol_audio.
	if(!saudio_isvalid())
	{
		std::cout << "Could not initialise sokol_audio. Exiting." << std::endl;

		return 1;
	}
	else
		std::cout << "(type [return] to quit)" << std::endl;

	// <at this point, audio is now being processed>

	//Cheap way of blocking execution on the main thread until the user hits return.
	//(note that audio processing happens in a separate audio thread)
	std::cin.get();

	//Close the soundcard, clean up after ourselves.
	saudio_shutdown();

	return 0;
}
