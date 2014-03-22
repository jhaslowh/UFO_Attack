#include "LevelProperties.h"


LevelProperties::LevelProperties()
{
	levelLeft = 0.0f;
	levelRight = 0.0f;
	levelTop = 0.0f;
	levelBottom = 0.0f;
	playerSpawnX = 0.0f;
	playerSpawnY = 0.0f;
	light[0] = .5f;
	light[1] = .5f;
	light[2] = .5f;
	screenWidth = 0.0f;
	screenHeight = 0.0f;
}

LevelProperties::~LevelProperties(){}

void LevelProperties::setLevelLeft(float left){levelLeft = left;}
float LevelProperties::getLevelLeft(){return levelLeft;}
void LevelProperties::setLevelRight(float right){levelRight = right;}
float LevelProperties::getLevelRight(){return levelRight;}
void LevelProperties::setLevelTop(float top){levelTop = top;}
float LevelProperties::getLevelTop(){return levelTop;}
void LevelProperties::setLevelBottom(float bottom){levelBottom = bottom;}
float LevelProperties::getLevelBottom(){return levelBottom;}

// Set player spawn location 
void LevelProperties::setPlayerSpawn(float x, float y){
	playerSpawnX = x;
	playerSpawnY = y;
}
float LevelProperties::getPlayerSpawnX(){
	return playerSpawnX;
}
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

// Getters and setters for screen sizes 
void LevelProperties::setScreenWidth(float w){screenWidth = w;}
float LevelProperties::getScreenWidth(){return screenWidth;}
void LevelProperties::setScreenHeight(float h){screenHeight = h;}
float LevelProperties::getScreenHeight(){return screenHeight;}

