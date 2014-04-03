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
	// Base Properties
	float locX, locY;
	float nextX, nextY;
	float originX, originY;
	float width, height;

	// Collision properties 
	Point vertA;
	Point vertB;
	float minDistFromGround;  // Minimum distance UFO must be from ground 
	Rec collisionArea;
	Rec abductRayArea;

	// Physics and movement
	float direcX, direcY;
	float speed;
	bool lookingRight;

	// Shields and armor 
	float armor;				// Ships current armor
	float maxArmor;				// Max armor that ship can have 
	float shield;				// Ships current shield amount 
	float maxShield;			// Max shield capacity for the ship
	float shieldChargeRate;		// How fast the ship shield charges 
	// How long it takes from the last time ship took damage to when it recharges
	float timeTillCharge;		
	float cTimeTillCharge;

	// Abduction Ray
	bool rayOn;
	int rayCircleCount;
	float rayMoveSpeed;
	float rayOffset;
	float rayOffsetMax;
	float rayScaleMin;
	float rayScaleMax;
	float rayWidth;
	float rayHeight;
	float rayCircleHeight;

public:
	UFO();
	~UFO();

	// Set location of the player 
	void setLocation(float x, float y);
	float getX();
	// Returns center x coord of ufo
	float getCenterX();
	// Returns center y coord of ufo
	float getCenterY();
	float getY();
	void setMaxArmor(float value);
	float getMaxArmor();
	void setArmor(float value);
	float getArmor();
	void setMaxShield(float value);
	float getMaxShield();
	void setShield(float value);
	float getShield();

	// Check if abduction ray is turned on 
	bool isRayOn();
	// Get the area for collision detection with ship
	Rec* getUFOArea();
	// Get the area for collision detection with abduction ray
	Rec* getAbductArea();

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
	void draw(GLHandler* mgl, PlayerAtlas* mAtlas, bool inUFO);

	// Draw UFO lights
	void drawLights(GLHandler* mgl, PlayerAtlas* mAtlas, bool inUFO);

	// Apply damage to the ship 
	void applyDamage(float damage);

	// Refil armor to capacity
	void replinishArmor();

	// Returns true if ufo is alive 
	bool alive();
};

