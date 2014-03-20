#pragma once
#include "Rec.h"
#include "Handlers.h"
#include "GLHandler.h"
#include "GameAtlas.h"
#include "MouseHandler.h"
#include "KeyHandler.h"

class NPC
{
protected:

	float locX, locY;
	float width, height;
	float originX, originY;
	float rotation;
	float scale;
	int imageID;
	Rec* collisionRec;

public:
	NPC* next;

	NPC();
	virtual ~NPC();

	// Set the location of the npc 
	void setLocation(float x, float y);
	float getX();
	float getY();
	// Set the width and height of the npc
	void setSize(float w, float h);
	float getWidth();
	float getHeight();
	// Set the origin point of the npc
	void setOrigin(float x, float y);
	// Set the rotation of the npc
	void setRotation(float r);
	float getRotation();
	// Set the scale of the npc
	void setScale(float s);
	float getScale();
	// Set the image id to draw for this npc
	void setImageID(int id);
	int getImageID();

	// Returns npc collision rec
	virtual Rec* getCollisionRec();

	// Fix collision rec location 
	virtual void fixCollRec();

	// Update game state of the npc object
	virtual void update(float deltaTime, Handlers* handlers);

	// Draw any light this object has 
	virtual void drawLight(GLHandler* mgl, GameAtlas* mGame);

	// Draw object to the screen
	virtual void draw(GLHandler* mgl, GameAtlas* mGame);
};

