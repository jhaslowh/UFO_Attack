#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL/SDL.h>

#include "settings.h"
#include <SDL/SDL_mixer.h>


//The music that will be played



class SoundHandler
{
public:
	SoundHandler(Settings * settingsHandler);
	~SoundHandler(void);
	Mix_Music *menuMusic;
};

