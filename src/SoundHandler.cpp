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
	//blasterSound = Mix_LoadWAV("audio/blaster_sound.wav");
	blasterSound = Mix_LoadWAV("audio/lightning_bolt.wav");
	npcSMGSound = Mix_LoadWAV("audio/smg_fire.wav");
	npcSniperSound = Mix_LoadWAV("audio/sniper_fire.wav");
	npcRocketLaunchSound = Mix_LoadWAV("audio/rocket_launch.wav");
	npcTankFireSound = Mix_LoadWAV("audio/tank_blast.wav");
	ufoRocketLaunchSound = Mix_LoadWAV("audio/ufo_rocket_launch.wav");
	rocketExplodeSound = Mix_LoadWAV("audio/rocket_explosion.wav");
}


//example playSoundEffect(SE_BLASTER_SOUND);
void SoundHandler::playSoundEffect(int soundID){
	switch(soundID){
		case SE_PLAYER_LASER_SOUND:
			Mix_PlayChannel(-1, blasterSound, 0);
			break;
		case SE_NPC_SMG_SOUND:
			Mix_PlayChannel(-1, npcSMGSound, 0);
			break;
		case SE_NPC_SNIPER_SOUND:
			Mix_PlayChannel(-1, npcSniperSound, 0);
			break;
		case SE_NPC_ROCKET_LAUNCH_SOUND:
			Mix_PlayChannel(-1, npcRocketLaunchSound, 0);
			break;
		case SE_NPC_TANK_FIRE:
			Mix_PlayChannel(-1, npcTankFireSound, 0);
			break;
		case SE_UFO_ROCKET_LAUNCH_SOUND:
			Mix_PlayChannel(-1, ufoRocketLaunchSound, 0);
			break;
		case SE_ROCKET_EXPLODE_SOUND:
			Mix_PlayChannel(-1, rocketExplodeSound, 0);
			break;
	}
}

SoundHandler::~SoundHandler()
{
	// Cleanup SDL for graceful exit
	Mix_FreeMusic(menuMusic);

	Mix_FreeChunk(blasterSound);
	Mix_FreeChunk(npcSMGSound);
	Mix_FreeChunk(npcSniperSound);
	Mix_FreeChunk(npcRocketLaunchSound);
	Mix_FreeChunk(npcTankFireSound);
}
