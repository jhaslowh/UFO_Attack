#pragma once
//#include <iostream>
#include "NPCBasicCollision.h"

class NPCcow :	public NPCBasicCollision
{
	// Movement
	float direcX;
	float speed;
	float afraidSpeed;

	// Animation
	int frames;
	int cframe;
	float frameRate;
	float cframeTime;
	bool afraid; 

public:
	NPCcow(float x, float y);
	virtual ~NPCcow();

	virtual void updateMovement(float deltaTime, Handlers* handlers);
	virtual void update(float deltaTime, Handlers* handlers);

	virtual void draw(GLHandler* mgl, GameAtlas* mGame);

	virtual void hitWall();
	
	void goLeft();
	void goRight();
	bool isPlayerToLeft(Player* player);
	
	// Damage the npc by sent damage amout.
	// Will set npc to !alive if too much damage taken
	virtual void damage(float amount, Handlers* handlers);

	// Called when npc dies 
	virtual void onDeath(Handlers* handlers);
};

