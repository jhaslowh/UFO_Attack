#pragma once
#include "NPC.h"
#include "LevelProperties.h"
#include "SceneryHandler.h"
#include "Collision.h"
#include "ExplHandler.h"

class NPCBasicCollision : public NPC
{
protected: 

	// --------------------
	// Collision Properties 
	// --------------------
	// Collision lines, used for check collision 
	// with the ground. 
	Point vertA;      // Vertical checking line point one and two
	Point vertB;      // 
	Point horA;       // Horozontal checking line point one and two
	Point horB;       // 
	float waistHeight;
	Point vertBotA;   // Below body vertical checking line point one and two
	Point vertBotB;   // 
	float depthForDepthCheck;
	// Collision Rectangles used for collision detection.
	Rec collRecX;		// Collision rec with just new x
	Rec collRecY;		// Collision rec with just new y
	Rec collRecXY;		// Collision rec with both new x and y

	// -------
	// Physics
	// -------
	bool inAir;
	float nextX, nextY;
    float yo;				// Original y location at begining of jump 
	float airT;				// Time that player has been in the air for 
	float minAirtForInAir;	// Min time to count airT as being in air

public:
	NPCBasicCollision();
	virtual ~NPCBasicCollision();
	
	// Update movement of the NPC 
	// This method should set the movement values for the npc.
	// Note: nextY is controled by gravity in the next method
	virtual void updateMovement(float deltaTime, Handlers* handlers);

	// Update collision of NPC 
	// This method should check if the npc is being abducted, if it is
	// it should ignore the movement from the update movement method and 
	// if it isnt, it should resolve the movement and collisions. 
	virtual void updateCollision(float deltaTime, Handlers* handlers);

	// Update game state of the npc object
	// Do any non movement or collision detection updates
	// (weapons and the like) 
	virtual void update(float deltaTime, Handlers* handlers);

	// Draw any light this object has 
	virtual void drawLight(GLHandler* mgl, GameAtlas* mGame);

	// Draw object to the screen
	virtual void draw(GLHandler* mgl, GameAtlas* mGame);

	// ------------------------ 
	// Collision Method Calls
	// ------------------------

	// Called when the NPC runs into a wall
	virtual void hitWall();

	// Called when the NPC runs into the floor 
	virtual void hitFloor();

	// Called when the NPC runs into the ceiling
	virtual void hitCeiling();

private:

	// Set the given collision rectangle to the given location
	void setCollRec(Rec* r, float x, float y);
};

