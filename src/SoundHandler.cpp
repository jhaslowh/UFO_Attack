#include "SoundHandler.h"

// Using the standard output for printf 
#include <stdio.h>
#include <stdlib.h>
#include <vector>
// Use glew.h instead of gl.h to get all the GL prototypes declared 
#include <glew.h>
// Using the SDL library for the base windowing setup 
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_timer.h>
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
