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

	loadMusic();
	loadSound();
	
	if( menuMusic == NULL ){
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}


	
}

void SoundHandler::loadMusic(void){
	//Until performance issues crop up we load all of the sound files at once. 
	menuMusic = Mix_LoadMUS("audio/splash_screen.wav");

}

void SoundHandler::playMusic(int musicID){
	switch(musicID){
		case SE_MENU_MUSIC:
			Mix_PlayMusic(menuMusic, 1 );
			break;
	}
}

void SoundHandler::loadSound(void){
	blasterSound = Mix_LoadWAV("audio/blaster_sound.wav");
}


//example playSoundEffect(SE_BLASTER_SOUND);
void SoundHandler::playSoundEffect(int soundID){
	switch(soundID){
		case SE_BLASTER_SOUND:
			Mix_PlayChannel(-1, blasterSound, 0);
			break;
	}
}

SoundHandler::~SoundHandler(void)
{
	//TODO cleanup SDL for graceful exit
}
