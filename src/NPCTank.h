#pragma once
#include "NPCBasicCollision.h"
#include "NPCTankBarrel.h"

class NPCTank : public NPCBasicCollision
{
	// Movement
	float direcX;
	float speed;
	float distanceTillFlop;
	float minDistanceTFlop;
	float maxDistanceTFlop;
	float currentDistance;

	// Pause before flop 
	bool pauseToFlop;
	float pauseTime;
	float cpauseTime;

	// Weapon Properties 
	Weapon* weapon;
	float barrelX, barrelY;
	float weaponRange;

public:
	NPCTank(float x, float y);
	virtual ~NPCTank();
	
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
};

