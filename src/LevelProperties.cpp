#include "LevelProperties.h"


LevelProperties::LevelProperties()
{
	levelLeft = 0.0f;
	levelRight = 0.0f;
}

LevelProperties::~LevelProperties(){}

// Set the left bounds of the level
void LevelProperties::setLevelLeft(float left){levelLeft = left;}
// Get the left bounds of the level
float LevelProperties::getLevelLeft(){return levelLeft;}

// Set the right boudns of the level
void LevelProperties::setLevelRight(float right){levelRight = right;}
// Get the right bounds of the level 
float LevelProperties::getLevelRight(){return levelRight;}