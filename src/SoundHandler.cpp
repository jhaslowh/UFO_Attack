#include "SoundHandler.h"
#include "Settings.h" // gives access to settings

SoundHandler::SoundHandler(Settings * settingsHandlerPointer)
{
	
	if(SDL_Init(SDL_INIT_AUDIO)<0){
		// errors
		printf("Error initializing audio. SDL Error info %s\n", SDL_GetError());
	} else {
		printf("Attempt to setup sound\n");

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) <0){
			//TODO error
			printf( "Error initializing SDL_mixer. Error info %s\n", Mix_GetError() );
		}
	}

	menuMusic = Mix_LoadMUS("audio/splash_screen.wav");
	if( menuMusic == NULL ){
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	if (settingsHandlerPointer->getMasterVol() * settingsHandlerPointer->getMusicVol() > 0.0f){
		Mix_PlayMusic(menuMusic, 1 );
	}
}

SoundHandler::~SoundHandler(void)
{
	//TODO cleanup SDL for graceful exit
}
