#pragma once
#include "NPCBasicCollision.h"
#include "NPCStinger.h"

class NPCStingerSoldier: public NPCBasicCollision
{
	// Movement
	float direcX;
	float speed;
	float distanceTillFlop;
	float minDistanceTFlop;
	float maxDistanceTFlop;
	float currentDistance;

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
	float weaponRange;
	bool playerInRange;
	float caquireTime;
	float aquireTime;

public:
	NPCStingerSoldier(float x, float y);
	virtual ~NPCStingerSoldier();

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

	// Called when npc dies 
	virtual void onDeath(Handlers* handlers);
};



