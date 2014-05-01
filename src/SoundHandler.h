#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL/SDL.h>

#include "settings.h"
#include <SDL/SDL_mixer.h>


//Music
#define SE_MENU_MUSIC 11000

//Sound Effects
#define SE_PLAYER_LASER_SOUND 10000
#define SE_NPC_SMG_SOUND 10001
class SoundHandler
{
public:
	SoundHandler(Settings * settingsHandler);
	~SoundHandler(void);
	Mix_Music *menuMusic;
	Mix_Chunk *blasterSound;
	Mix_Chunk *npcSMGSound;
	void playMusic(int musicID);
	void playSoundEffect(int soundID);
private:
	void loadMusic();
	void loadSound();

};

