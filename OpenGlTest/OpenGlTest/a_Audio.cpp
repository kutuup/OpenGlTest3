#include "a_Audio.h"
#include <iostream>
//#include "SDL.h"

using namespace std;
struct AudioData
{
	Uint8* position;
	Uint32 length;
};

void audioCallback(void* userData, Uint8* stream, int streamLength)
{
	AudioData* audio = (AudioData*)userData;
	if (audio->length == 0)
	{
		return;
	}
	Uint32 length = (Uint32)streamLength;
	length = (length > audio->length ? audio->length : length);
	SDL_memcpy(stream, audio->position, length);
	audio->position += length;
	audio->length -= length;
}

void a_Audio::Play()
{
//	SDL_Delay(100);
}

a_Audio::a_Audio()
{

	

		SDL_Init(SDL_INIT_AUDIO);
		SDL_AudioSpec wavSpec;
		Uint8* wavStart;
		Uint32 wavLength;
		char* filePath = "AUD\\sample.wav";
		if (SDL_LoadWAV(filePath, &wavSpec, &wavStart, &wavLength) == NULL)
		{
			cerr << "Error: file could not be loaded as an audio file." << endl;
		}
		AudioData audio;
		audio.position = wavStart;
		audio.length = wavLength;
		wavSpec.callback = audioCallback;
		wavSpec.userdata = &audio;
		SDL_AudioDeviceID audioDevice;
		audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
		if (audioDevice == 0)
		{
			cerr << "Error: " << SDL_GetError() << endl;

		}
		SDL_PauseAudioDevice(audioDevice, 0);

		SDL_CloseAudioDevice(audioDevice);
		SDL_FreeWAV(wavStart);
		SDL_Quit();

	
}


a_Audio::~a_Audio()
{
}
