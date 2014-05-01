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


class SoundHandler
{
public:
	SoundHandler(Settings * settingsHandler);
	~SoundHandler(void);
	Mix_Music *menuMusic;
	void playMusic(int musicID);
private:
	void loadMusic();
	

};

