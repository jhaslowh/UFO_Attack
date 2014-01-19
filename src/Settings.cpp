#include "Settings.h"

Settings::Settings()
{
	screen_width = 1280;
	screen_height = 720;
	fullscreen = false;
}

// Getters and setters
int Settings::getScreenWidth(){return screen_width;}
void Settings::setScreenWidth(int width){screen_width = width;}
int Settings::getScreenHeight(){return screen_height;}
void Settings::setScreenHeight(int height){screen_height = height;}
bool Settings::getFullscreen(){return fullscreen;}
void Settings::setFullscreen(bool value){fullscreen = value;}