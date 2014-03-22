#pragma once
class LevelProperties
{
	float levelLeft;
	float levelRight;
	float levelTop;			
	float levelBottom;		
	float playerSpawnX;
	float playerSpawnY;
	float screenWidth;
	float screenHeight;

public:
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
};

