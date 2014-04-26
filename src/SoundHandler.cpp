#include "SoundHandler.h"

// Using the standard output for printf 
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <SDL/SDL_mixer.h>




SoundHandler::SoundHandler(void)
{
	std::cout << "SOUND" << std::endl;
	std::cout << "SOUND" << std::endl;
}


SoundHandler::~SoundHandler(void)
{
	//TODO cleanup SDL for graceful exit
}
