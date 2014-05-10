#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "Settings.h"


//Music
#define SE_MENU_MUSIC 11000
#define SE_ABDUCT 11001

//Sound Effects
#define SE_PLACEHOLDER 11111
#define SE_PLAYER_LASER_SOUND 10000
#define SE_NPC_SMG_SOUND 10001
#define SE_NPC_SNIPER_SOUND 10002
#define SE_NPC_ROCKET_LAUNCH_SOUND 10003
#define SE_NPC_TANK_FIRE 10004
#define SE_UFO_ROCKET_LAUNCH_SOUND 10005
#define SE_ROCKET_EXPLODE_SOUND 10006

#define SE_PLAYER_DAMAGED 10007
#define SE_UFO_HIT 10008
#define SE_ENTER_UFO 10009
#define SE_EXIT_UFO 10010
#define SE_GAME_OVER 10011
#define SE_PAUSE 10012
#define SE_RESUME 10013
#define SE_UFO_UP 10014
#define SE_BUTTON_PRESS 10014 
//TODO this seams like it should cause a problem, but has not yet
#define SE_UFO_DOWN 10015
#define SE_UFO_ERROR 10016
#define SE_ABDUCT_SUCCESS 10017
#define SE_COWTAPULT 10018


class SoundHandler
{
	bool soundsSetup;

public:
	SoundHandler(Settings * settingsHandler);
	~SoundHandler(void);
	Mix_Chunk *buttonSound;
	Mix_Chunk *placeholderSound;
	Mix_Chunk *playerDamagedSound;
	Mix_Chunk *ufoHitSound;
	Mix_Chunk *ufoEnterSound;
	Mix_Chunk *ufoExitSound;
	Mix_Chunk *gameOverSound;
	Mix_Chunk *pauseSound;
	Mix_Chunk *resumeSound;
	Mix_Music *menuMusic;
	Mix_Music *abductMusic;
	Mix_Chunk *blasterSound;
	Mix_Chunk *npcSMGSound;
	Mix_Chunk *npcSniperSound;
	Mix_Chunk *npcRocketLaunchSound;
	Mix_Chunk *npcTankFireSound;
	Mix_Chunk *ufoRocketLaunchSound;
	Mix_Chunk *rocketExplodeSound;
	Mix_Chunk *ufoErrorSound;
	Mix_Chunk *abductSuccessSound;
	Mix_Chunk *cowtapoltSound;
	Settings * settings;

	void playMusic(int musicID);
	void startMusic(int musicID);
	void stopMusic();
	void playSoundEffect(int soundID);
private:
	void loadMusic();
	void loadSound();

};

