#pragma once
#include "Rec.h"

class LevelProperties
{
	// These are the bounds of the level itself 
	float levelLeft;
	float levelRight;
	float levelTop;			
	float levelBottom;		

	// Player spawn location 
	float playerSpawnX;
	float playerSpawnY;

	// Screen size 
	float screenWidth;
	float screenHeight;
	int enemyCount;

public:
	// Rec of visible screen area 
	Rec screenRec;

	LevelProperties();
	~LevelProperties();

	void setLevelLeft(float left);
	float getLevelLeft();
	void setLevelRight(float right);
	float getLevelRight();
	void setLevelTop(float top);
	float getLevelTop();
	void setLevelBottom(float bottom);
	float getLevelBottom();

	// Set player spawn location 
	void setPlayerSpawn(float x, float y);
	float getPlayerSpawnX();
	float getPlayerSpawnY();

	// Getters and setters for screen sizes 
	void setScreenWidth(float w);
	float getScreenWidth();
	void setScreenHeight(float h);
	float getScreenHeight();

	// Return level enemy count
	int getEnemyCount();
	// Set level enemy count
	void setEnemyCount(int value);
};

