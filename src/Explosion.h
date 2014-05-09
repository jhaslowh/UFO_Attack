#pragma once
#include "GLHandler.h"
#include "GameAtlas.h"
#include "Collision.h"

#define PLAYER_EXP 0
#define ENEMY_EXP 1

class Explosion
{
protected:

	// --- Drawing 
	// Image id to draw 
	int imageID;
	float locX, locY;
	float originX, originY;
	float rotation;

	// --- Exploding
	// Damage of explosion 
	float damage;
	// Explosion range 
	float range;
	// Explosion time
	float explTime;			// Time explosion is active for
	float cexplTime;		// Current explosion time 

	// --- Animation
	bool animates;
	int frames;
	int cframe;
	float frameTime;
	float cframeTime;

	// --- States/Types
	bool valid;
	int type;

public:
	Explosion();

	// Clone this explosion off the sent one 
	void cloneE(Explosion* e);

	// ------------------------
	// Getters and Setters 
	// ------------------------

	// Returns explosion damage
	float getDamage();

	// Set exp location 
	void setLocation(float x, float y);

	// Set exp type
	void setType(int t);

	// Returns explosion type 
	int getType();

	// Returns true if fired by player
	bool firedByPlayer();
	
	// Returns true if fired by enemy 
	bool firedByEnemy();
	
	// ------------------------
	// Member functions 
	// ------------------------

	// Update explosion state
	void update(float deltaTime);

	// Draw Explosion 
	void draw(GLHandler* mgl, GameAtlas* mAtlas);

	// Draw Explosion Light
	void drawLight(GLHandler* mgl, GameAtlas* mAtlas);

	// Check if explosion is valid
	bool isValid();

	// Check if explosion is active
	bool active(); 

	// Check if rec is in range
	bool inRadius(Rec* r);


	// --------------------------------

	// Set as a basic explosion
	void setAsBasic();

	void setAsSplat();
};

