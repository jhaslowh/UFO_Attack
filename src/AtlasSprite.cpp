#include "AtlasSprite.h"


AtlasSprite::AtlasSprite()
{
	id = 0;
	locX = 0.0f;
	locY = 0.0f;
	rotation = 0.0f;
	scale = 1.0f;
	originX = 0.0f;
	originY = 0.0f;
}

AtlasSprite::~AtlasSprite(){}

// Set the position of the sprite 
void AtlasSprite::setPosition(float x,float y){locX = x; locY = y;}
void AtlasSprite::setX(float x){locX = x;}
void AtlasSprite::setY(float y){locY = y;}
float AtlasSprite::getX(){return locX;}
float AtlasSprite::getY(){return locY;}
// Set the rotation of the sprite 
void AtlasSprite::setRotation(float r){rotation =r;}
float AtlasSprite::getRotation(){return rotation;}
// Set the scale of the sprite 
void AtlasSprite::setScale(float s){scale = s;}
float AtlasSprite::getScale(){return scale;}
// Set the origin of the sprite 
void AtlasSprite::setOrigin(float x,float y){originX = x; originY = y;}
// Set ID
void AtlasSprite::setID(int value){id = value;}
int AtlasSprite::getID(){return id;}

// Draw the sprite 
void AtlasSprite::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	mAtlas->draw(mgl,id, locX,locY,scale,rotation,originX,originY);
}
// Draw the sprite at offset 
void AtlasSprite::draw(GLHandler* mgl, TextureAtlas* mAtlas, float offx, float offy){
	mAtlas->draw(mgl,id, offx+locX,offy+locY,scale,rotation,originX,originY);
}