#pragma once
class Settings
{
	int screen_width;
	int screen_height;
	bool fullscreen;
	float masterVol;
	float musicVol;
	float sfxVol;

public:

	Settings();

	// Getters and setters
	int getScreenWidth();
	void setScreenWidth(int width);
	int getScreenHeight();
	void setScreenHeight(int height);
	bool getFullscreen();
	void setFullscreen(bool value);
	float getMasterVol();
	void setMasterVol(float value);
	float getMusicVol();
	void setMusicVol(float value);
	float getSfxVol();
	void setSfxVol(float value);

	// Get this value when setting the volume for the game
	float getMusicPlaybackVol();
	// Get this value when setting the volume for the game
	float getSfxPlaybackVol();

};

#include <SDL/SDL_mixer.h>
