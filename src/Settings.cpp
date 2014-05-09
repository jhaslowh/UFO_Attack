#include "Settings.h"

Settings::Settings()
{
	screen_width = 1280;
	screen_height = 720;
	fullscreen = false;
	masterVol = 1.0f;
	musicVol = 1.0f;
	sfxVol = 1.0f;
}

// Getters and setters
int Settings::getScreenWidth(){return screen_width;}
void Settings::setScreenWidth(int width){screen_width = width;}
int Settings::getScreenHeight(){return screen_height;}
void Settings::setScreenHeight(int height){screen_height = height;}
bool Settings::getFullscreen(){return fullscreen;}
void Settings::setFullscreen(bool value){fullscreen = value;}

float Settings::getMasterVol(){return masterVol;}
void Settings::setMasterVol(float value){
	masterVol = value;	
}
float Settings::getMusicVol(){return musicVol;}
void Settings::setMusicVol(float value){
	musicVol = value;
}
float Settings::getSfxVol(){return sfxVol;}
void Settings::setSfxVol(float value){
	sfxVol = value;
}

// Get this value when setting the volume for the game
float Settings::getMusicPlaybackVol(){return masterVol * musicVol;}
// Get this value when setting the volume for the game
float Settings::getSfxPlaybackVol(){return masterVol * sfxVol;}