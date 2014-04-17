#pragma once
#include "NPCBasicCollision.h"

class NPCcow :	public NPCBasicCollision
{
	// Movement
	float direcX;
	float speed;

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
};

