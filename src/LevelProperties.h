#pragma once
class LevelProperties
{
	float levelLeft;
	float levelRight;

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
};

