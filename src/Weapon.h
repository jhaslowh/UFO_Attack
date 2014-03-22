#pragma once
#include "GLHandler.h"
#include "TextureAtlas.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Handlers.h"
#include "Camera2D.h"
#include "ProjectileHandler.h"
#include "ProjectileTemplate.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>


// Fire types for the weapon
#define FIRETYPE_SINGLE 0
#define FIRETYPE_RAPID 1

class Weapon
{

protected: 
	// ---------------
	// Drawing 
	// ---------------
	int imageid;					// For atlas use 
	float locX, locY;				// Location of the weapon 
	float originX, originY;			// Origin of the weapon 
	float rotation;					// Rotation of the weapon 
	
	// ---------------
	// Weapon properties 
	// ---------------
	bool lookingRight;				// Facing direction
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
	float damage;
	bool isPlayerWeapon;
	ProjectileTemplate projTemp;
	bool usesAmmo;					// Set to false to give unlimited ammo
	
	// ---------------
	// Muzzle flash
	// ---------------
	int muzzleImageId;		// For atlas use 
	float muzzleOrigin[2];
	float flashTime;
	float cFlashTime;

	// ------------------------
	// Values used during maths
	// ------------------------
	float mTheta;
	float weaponLocX, weaponLocY;
	float spr;
	float direcX, direcY;
	float dispX, dispY;
	float x, y;

public:
	Weapon(void);
	virtual ~Weapon(void);

	// Call to get rotation
	float getRotation();

	// Set the facing direction for the weapon
	void setFacingDirec(bool value);
	// Get the facing direction of the weapon
	bool getFacingDirecton();
	// Set and get for player weapon 
	void setIsPlayerWeapon(bool value);
	bool getIsPlayerWeapon();

	// Update weapon state
	// x: the x location in the world for the weapon
	// y: the y location in the world for the weapon
	virtual void update(float deltaTime, float x, float y);

	// Update weapon input
	// Note: if this is an NPC weapon, do not call this method
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw weapon to screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Fire the weapon
	virtual void fire(float targetx, float targety, Handlers* handlers);

	// Check if the gun is reloading 
	virtual bool reloading();

	// Reload the gun 
	virtual void reload();

	// Check if can fire
	bool canFire();
};

