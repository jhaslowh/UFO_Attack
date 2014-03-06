#include "LevelProperties.h"


LevelProperties::LevelProperties()
{
	levelLeft = 0.0f;
	levelRight = 0.0f;
	playerSpawnX = 0.0f;
	playerSpawnY = 0.0f;
	light[0] = .5f;
	light[1] = .5f;
	light[2] = .5f;
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

// Set player spawn location 
void LevelProperties::setPlayerSpawn(float x, float y){
	playerSpawnX = x;
	playerSpawnY = y;
}
// Get player spawn x
float LevelProperties::getPlayerSpawnX(){
	return playerSpawnX;
}
// Get player spawn y
float LevelProperties::getPlayerSpawnY(){
	return playerSpawnY;
}
// Set the level light
void LevelProperties::setLight(float r, float g, float b){
	light[0] = r;
	light[1] = g;
	light[2] = b;
}
// Get level light
// Length is 3. 
float* LevelProperties::getLight(){return &light[0];}