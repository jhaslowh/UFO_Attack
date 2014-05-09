#pragma once
#include "Handlers.h"
#include "GLHandler.h"
#include "PlayerAtlas.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "Camera2D.h"
#include "LevelProperties.h"
#include "ProjectileHandler.h"
#include "ExplHandler.h"
#include "UFORocket.h"
#include "UFOMachineGun.h"
#include "PlayerLaserGun.h"
#include "ParticleHandler.h"
#include "UFOCowtapult.h"
#include "SoundHandler.h"

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

	// Particles
	float partRate;
	float cpartRate;

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
	bool invincible;

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

	// Energy
	float energy;
	float energyMax;
	float eCharge; // Charge rate
	float eDrain; // Drain rate 
	float timeTilCharge;
	float ctimeTilCharge;

	// Hit recently
	float hitTime;
	float chitTime;

	// -------------
	// Weapon
	// -------------
	bool usingWeapon1;
	Weapon* uweapon1;
	Weapon* uweapon2;

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
	void setInvincible(bool value);
	void setRayOn(bool value);

	// Check if abduction ray is turned on 
	bool isRayOn();
	// Get the area for collision detection with ship
	Rec* getUFOArea();
	// Get the area for collision detection with abduction ray
	Rec* getAbductArea();

	// Returns the percent of current energy 
	float getEnergyPercent();

	// Init 
	void init(SaveData* savedata);
	
	// Load images
	void load();

	// Update UFO
	void update(float deltaTime, Handlers* handlers);

	// Update UFO when player is on foot
	void updateOnFoot(float deltaTime, Handlers* handlers);

	// Check collision 
	void checkCollision(Handlers* handlers);

	// Resolve collisions
	void resolveCollision(float deltaTime, Handlers* handlers);

	// Update ufo input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

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
	
	// Get ammo string for current weapon
	std::string getAmmoString();
};

