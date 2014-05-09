#include "SoundHandler.h"
#include "Settings.h" // gives access to settings

SoundHandler::SoundHandler(Settings * settingsHandlerPointer)
{
	settings = settingsHandlerPointer;
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

	try{
//		Mix_VolumeMusic((int)(MIX_MAX_VOLUME*settings->musicVol*settings->masterVol));
//		Mix_Volume(-1, (int)(MIX_MAX_VOLUME*settings->sfxVol*settings->masterVol));
	}
	catch(int e){
		//TODO some logging needs to happen here. I think mix_volume gets called before sdl mixer is created
	}

	switch(musicID){
		case SE_MENU_MUSIC:
			Mix_PlayMusic(menuMusic, 1 );
			break;
	}
}

void SoundHandler::loadSound(void){
	blasterSound = Mix_LoadWAV("audio/blaster_sound.wav");
	npcSMGSound = Mix_LoadWAV("audio/smg_fire.wav");//TODO NEED SOUND
	npcSniperSound = Mix_LoadWAV("audio/sniper_fire.wav");
	npcRocketLaunchSound = Mix_LoadWAV("audio/rocket_launch.wav");//TODO NEED SOUND
	npcTankFireSound = Mix_LoadWAV("audio/tank_blast.wav");//TODO NEED SOUND
	ufoRocketLaunchSound = Mix_LoadWAV("audio/ufo_rocket_launch.wav");//TODO NEED SOUND
	rocketExplodeSound = Mix_LoadWAV("audio/rocket_explosion.wav");



	playerDamagedSound = Mix_LoadWAV("audio/player_hit.wav");
	ufoHitSound= Mix_LoadWAV("audio/ufo_hit.wav");
	ufoEnterSound = Mix_LoadWAV("audio/ufo_up.wav");
	ufoExitSound = Mix_LoadWAV("audio/ufo_down.wav");
	gameOverSound = Mix_LoadWAV("audio/game_over.wav");

}


//example playSoundEffect(SE_BLASTER_SOUND);
void SoundHandler::playSoundEffect(int soundID){
	try{
		
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME*settings->getMusicVol()*settings->getMasterVol()));
		Mix_Volume(-1, (int)(MIX_MAX_VOLUME*settings->getSfxVol()*settings->getMasterVol()));
	}
	catch(int e){
		//TODO some logging needs to happen here. I think mix_volume gets called before sdl mixer is created
	}

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
		case SE_PLAYER_DAMAGED:
			Mix_PlayChannel(-1, playerDamagedSound, 0);
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
