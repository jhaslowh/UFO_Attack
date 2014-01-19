#pragma once
class Settings
{
	int screen_width;
	int screen_height;
	bool fullscreen;

public:
	Settings();

	// Getters and setters
	int getScreenWidth();
	void setScreenWidth(int width);
	int getScreenHeight();
	void setScreenHeight(int height);
	bool getFullscreen();
	void setFullscreen(bool value);
};

