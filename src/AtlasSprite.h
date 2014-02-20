#pragma once
#include "GLHandler.h"
#include "TextureAtlas.h"

class AtlasSprite
{
private:
	// Drawing variables 
	int id;
	float locX;
	float locY;
	float rotation;
	float scale;
	float originX;
	float originY;
	
public:
	AtlasSprite();
	~AtlasSprite();

	// Set the position of the sprite 
	void setPosition(float,float);
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	// Set the rotation of the sprite 
	void setRotation(float);
	float getRotation();
	// Set the scale of the sprite 
	void setScale(float);
	float getScale();
	// Set the origin of the sprite 
	void setOrigin(float,float);
	// Set ID
	void setID(int value);
	int getID();

	// Draw the sprite 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);
	// Draw the sprite at offset 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas, float offx, float offy);
};

