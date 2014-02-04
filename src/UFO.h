#pragma once
#include "Handlers.h"
#include "GLHandler.h"
#include "PlayerAtlas.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "Camera2D.h"
#include "LevelProperties.h"

class UFO
{
	// Locations
	float locX, locY;
	float nextX, nextY;
	float originX, originY;

	// Collision properties 
	Point vertA;
	Point vertB;
	float minDistFromGround;  // Minimum distance UFO must be from ground 

	// Physics and movement
	float direcX, direcY;
	float speed;

	// Shields and armor 
	float armor;				// Ships current armor
	float maxArmor;				// Max armor that ship can have 
	float shield;				// Ships current shield amount 
	float maxShield;			// Max shield capacity for the ship
	float shieldChargeRate;		// How fast the ship shield charges 
	// How long it takes from the last time ship took damage to when it recharges
	float timeTillCharge;		
	float cTimeTillCharge;

public:
	UFO();
	~UFO();

	// Set location of the player 
	void setLocation(float x, float y);
	float getX();
	float getY();
	void setMaxArmor(float value);
	float getMaxArmor();
	void setArmor(float value);
	float getArmor();
	void setMaxShield(float value);
	float getMaxShield();
	void setShield(float value);
	float getShield();

	// Init 
	void init();
	
	// Load images
	void load();

	// Update UFO
	void update(float deltaTime, Handlers* handlers);

	// Check collision 
	void checkCollision(Handlers* handlers);

	// Resolve collisions
	void resolveCollision(Handlers* handlers);

	// Update ufo input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw UFO
	void draw(GLHandler* mgl, PlayerAtlas* mGame);

	// Apply damage to the ship 
	void applyDamage(float damage);

	// Refil armor to capacity
	void replinishArmor();

	// Returns true if ufo is alive 
	bool alive();
};

