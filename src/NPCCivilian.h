#pragma once
#include "NPCBasicCollision.h"
#include "NPCSMG.h"

class NPCCivilian : public NPCBasicCollision
{
	// Movement
	float direcX;
	float speed;
	float afraidSpeed;
	float distanceTillFlop;
	float minDistanceTFlop;
	float maxDistanceTFlop;
	float currentDistance;
	bool afraid;

	// Animation 
	int frames;
	int cframe;
	float frameRate;
	float cframeTime;
	
	// Arm 
	float armOffsetX, armOffsetY;
	float armOriginX, armOriginY;
	float armRotation;

public:
	NPCCivilian(float x, float y);
	virtual ~NPCCivilian();

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
	
	// Damage the npc by sent damage amout.
	// Will set npc to !alive if too much damage taken
	virtual void damage(float amount, Handlers* handlers);

	// Called when npc dies 
	virtual void onDeath(Handlers* handlers);
};

