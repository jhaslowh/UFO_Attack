#pragma once
class LevelProperties
{
	float levelLeft;
	float levelRight;
	float playerSpawnX;
	float playerSpawnY;
	float light[3];
	float screenWidth;
	float screenHeight;

public:
	LevelProperties();
	~LevelProperties();

	// Set the left bounds of the level
	void setLevelLeft(float left);
	// Get the left bounds of the level
	float getLevelLeft();

	// Set the right boudns of the level
	void setLevelRight(float right);
	// Get the right bounds of the level 
	float getLevelRight();

	// Set player spawn location 
	void setPlayerSpawn(float x, float y);
	// Get player spawn x
	float getPlayerSpawnX();
	// Get player spawn y
	float getPlayerSpawnY();

	// Set the level light
	void setLight(float r, float g, float b);
	// Get level light
	// Length is 3. 
	float* getLight();

	// Getters and setters for screen sizes 
	void setScreenWidth(float w);
	float getScreenWidth();
	void setScreenHeight(float h);
	float getScreenHeight();
};

