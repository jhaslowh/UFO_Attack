#pragma once
#include "NPC.h"
#include "Collision.h"
#include "ExplHandler.h"
#include "NPCSam.h"
class NPCSamSite: public NPC
{
	// Weapon Properties 
	Weapon* weapon;
	float weaponRange;
	float wOffsetX, wOffsetY; 

public:
	NPCSamSite(float x, float y);
	virtual ~NPCSamSite();

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

	// Called when npc dies 
	virtual void onDeath(Handlers* handlers);
};

