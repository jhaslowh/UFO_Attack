#include "SoundHandler.h"
#include "Settings.h" // gives access to settings

SoundHandler::SoundHandler(Settings * settingsHandlerPointer)
{
	soundsSetup = true;
	settings = settingsHandlerPointer;
	if(SDL_Init(SDL_INIT_AUDIO)<0){
		// errors
		printf("Error initializing audio. SDL Error info %s\n", SDL_GetError());
		soundsSetup = false;
	} else {
		printf("Attempt to setup sound\n");

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) <0){
			printf( "Error initializing SDL_mixer. Error info: %s\n", Mix_GetError() );
			soundsSetup = false;
		}
	}

	loadMusic();
	loadSound();
	
	if( menuMusic == NULL ){
		//printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	else {
		// This sound is incredible distorted and loud on the 
		// linux build. I think it might be the different audio
		// libraries. But it makes it sound like the sounds are 
		// broken. So I commented it out for now. 
		//playMusic(SE_MENU_MUSIC);
	}
}

void SoundHandler::loadMusic(void){
	//Until performance issues crop up we load all of the sound files at once. 
	menuMusic = Mix_LoadMUS("audio/splash_screen.wav");
}

void SoundHandler::playMusic(int musicID){
	if (!soundsSetup) return;

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
	abductMusic = Mix_LoadMUS("audio/abduct.wav");
	blasterSound = Mix_LoadWAV("audio/blaster_sound.wav");
	npcSMGSound = Mix_LoadWAV("audio/smg_fire.wav");//TODO NEED SOUND
	npcSniperSound = Mix_LoadWAV("audio/sniper_fire.wav");
	npcRocketLaunchSound = Mix_LoadWAV("audio/rocket_launch.wav");//TODO NEED SOUND
	npcTankFireSound = Mix_LoadWAV("audio/tank_blast.wav");//TODO NEED SOUND
	ufoRocketLaunchSound = Mix_LoadWAV("audio/ufo_rocket_launch.wav");//TODO NEED SOUND
	rocketExplodeSound = Mix_LoadWAV("audio/rocket_explosion.wav");
	abductSuccessSound = Mix_LoadWAV("audio/abduct_success.wav");
	pauseSound = Mix_LoadWAV("audio/pause.wav");
	resumeSound = Mix_LoadWAV("audio/resume.wav");

	placeholderSound = Mix_LoadWAV("audio/placeholder.wav");
	buttonSound = Mix_LoadWAV("audio/click.wav");
	playerDamagedSound = Mix_LoadWAV("audio/player_hit.wav");
	ufoHitSound= Mix_LoadWAV("audio/ufo_hit.wav");
	gameOverSound = Mix_LoadWAV("audio/game_over.wav");

	ufoEnterSound = Mix_LoadWAV("audio/ufo_up.wav");
	ufoExitSound = Mix_LoadWAV("audio/ufo_down.wav");
	ufoErrorSound = Mix_LoadWAV("audio/ufo_error.wav");

	cowtapoltSound = Mix_LoadWAV("audio/cowtapolt.wav");

}


//example playSoundEffect(SE_BLASTER_SOUND);
void SoundHandler::playSoundEffect(int soundID){
	if (!soundsSetup) return;

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
		case SE_UFO_HIT:
			Mix_PlayChannel(-1, ufoHitSound, 0);
			break;
		case SE_ENTER_UFO:
			Mix_PlayChannel(-1, ufoEnterSound, 0);
			break;
		case SE_EXIT_UFO:
			Mix_PlayChannel(-1, ufoExitSound, 0);
			break;
		case SE_UFO_ERROR:
			Mix_PlayChannel(-1, ufoErrorSound,0);
			break;
		case SE_GAME_OVER:
			Mix_PlayChannel(-1, gameOverSound, 0);
			break;
		case SE_PAUSE:
			Mix_PlayChannel(-1, pauseSound,0);
			break;
		case SE_RESUME:
			Mix_PlayChannel(-1, resumeSound, 0);
			break;
		case SE_BUTTON_PRESS:
			Mix_PlayChannel(-1, buttonSound, 0);
			break;
		case SE_ABDUCT_SUCCESS:
			Mix_PlayChannel(-1, abductSuccessSound, 0);
			break;
		case SE_COWTAPULT:
			Mix_PlayChannel(-1, cowtapoltSound, 0);
			break;
		default:
			Mix_PlayChannel(-1, placeholderSound, 0);
			break;

	}
}

void SoundHandler::startMusic(int musicID){

	switch(musicID){
		case SE_ABDUCT:
			Mix_PlayMusic(abductMusic, -1 );//loop until stopped
			break;
	}
}


void SoundHandler::stopMusic(){
	Mix_HaltMusic();
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
