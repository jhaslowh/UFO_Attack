#pragma once
#include "GLHandler.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Handlers.h"

// Fire types for the weapon
#define FIRETYPE_SINGLE 0
#define FIRETYPE_RAPID 1

class Weapon
{

protected: 
	// Drawing 
	float locX, locY;				// Location of the weapon 
	float originX, originY;			// Origin of the weapon 
	float rotation;					// Rotation of the weapon 

	// Weapon properties 
	int typeId;						// Weapon id, if needed 
	int clipCapacity;	
	int clip;
	float spread;					// Weapon fire spread in radians
	float verticalDisplacement;
	float horizontalDisplacement;
	int bulletsPerShot;
	float reloadTime;
	float cReloadTime;
	float timeBetweenShots;
	float cTimeBetweenShots;
	int firetype;
	// To get the barrel of the weapon, get the cords of the end of the barrel
	// relative to the sprite and subtrace the origin for it. 
	float barrelOffset[2];			

	// Muzzle flash
	float muzzleOffset[2]; // Similar to barrel offset 
	float flashTime;
	float cFlashTime;

public:
	Weapon(void);
	virtual ~Weapon(void);

	// Call to get rotation
	float getRotation();

	// Update weapon state
	// x: the x location in the world for the weapon
	// y: the y location in the world for the weapon
	virtual void update(float deltaTime, float x, float y);

	// Update weapon input
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw weapon to screen
	virtual void draw(GLHandler* mgl);

	// Fire the weapon
	virtual void fire(float targetx, float targety, Handlers* handlers);

	// Check if the gun is reloading 
	virtual bool reloading();

	// Reload the gun 
	virtual void reload();

private:

	// Check if can fire
	bool canFire();
};

