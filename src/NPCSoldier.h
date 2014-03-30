#pragma once
#include "NPCBasicCollision.h"

class NPCSoldier : public NPCBasicCollision
{
	// Movement
	float direcX;
	float speed;

	// Animation 
	int frames;
	int cframe;
	float frameRate;
	float cframeTime;
	
	// Arm 
	float armOffsetX, armOffsetY;
	float armOriginX, armOriginY;
	float armRotation;

	// Weapon Properties 
	Weapon* weapon;

public:
	NPCSoldier(float x, float y);
	virtual ~NPCSoldier();

	// Update movement of the NPC 
	// This method should set the movement values for the npc.
	virtual void updateMovement(float deltaTime, Handlers* handlers);

	// Update game state of the npc object
	// Do any non movement or collision detection updates
	// (weapons and the like) 
	virtual void update(float deltaTime, Handlers* handlers);

	// Draw object to the screen
	virtual void draw(GLHandler* mgl, GameAtlas* mGame);
	
	// Called when the NPC runs into a wall
	virtual void hitWall();
};

