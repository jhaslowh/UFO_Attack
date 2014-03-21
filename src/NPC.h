#pragma once
#include "Rec.h"
#include "Handlers.h"
#include "GLHandler.h"
#include "GameAtlas.h"

#define GRAVITY 980.0f

class NPC
{
protected:

	float locX, locY;
	float width, height;
	float originX, originY;
	float rotation;
	float scale;
	int imageID;
	Rec bounds;				// Bounds used when making collision rec
	Rec collisionRec;		// Collision rec to check collisions with 

	// States 
	bool canBeObducted;
	bool beingAbducted;
	bool alive;

	float health;

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

	// Update movement of the NPC 
	// This method should set the movement values for the npc.
	virtual void updateMovement(float deltaTime, Handlers* handlers);

	// Update collision of NPC 
	// This method should check if the npc is being abducted, if it is
	// it should ignore the movement from the update movement method and 
	// if it isnt, it should resolve the movement and collisions. 
	virtual void updateCollision(float deltaTime, Handlers* handlers);

	// Update game state of the npc object
	// Do any non movement or non collision detection updates
	// (weapons and the like) 
	virtual void update(float deltaTime, Handlers* handlers);

	// Draw any light this object has 
	virtual void drawLight(GLHandler* mgl, GameAtlas* mGame);

	// Draw object to the screen
	virtual void draw(GLHandler* mgl, GameAtlas* mGame);
};

