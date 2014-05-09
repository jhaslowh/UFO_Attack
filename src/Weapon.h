#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "GLHandler.h"
#include "TextureAtlas.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Handlers.h"
#include "Camera2D.h"
#include "ProjectileHandler.h"

// Fire types for the weapon
#define FIRETYPE_SINGLE 0
#define FIRETYPE_RAPID 1

const float DEG_TO_RAD = (3.14159f/180.0f);

#include "SoundHandler.h" //used for the defines

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
	// This property has no effect on npc weapons 
	int firetype;
	// To get the barrel of the weapon, get the cords of the end of the barrel
	// relative to the sprite and subtrace the origin for it. 
	float barrelOffset[2];	
	float damage;
	bool isPlayerWeapon;
	Projectile* proj;
	bool usesAmmo;					// Set to false to give unlimited ammo
	float minAngle;
	float maxAngle;
	
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
	Weapon();
	virtual ~Weapon();

	// Returns current weapon rotation
	float getRotation();
	// Set the current weapon rotation
	void setRotation(float value);

	// Set the facing direction for the weapon
	// Set to true if looking right. 
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

	// Use with the npc to fire at a requested target
	// Will not fire if not allowed to (out of ammo etc.).
	// NOTE: If you do not restrict fire radius in the calling method
	// this method will fire in any direction. 
	virtual void npcFire(float targetx, float targety, Handlers* handlers);

	// Fire the weapon
	virtual void fire(float targetx, float targety, Handlers* handlers);

	// Set the rotation of the weapon based off the sent target 
	void setRotationByTarget(float targetx, float targety);

	// Check if the gun is reloading 
	virtual bool reloading();

	// Reload the gun 
	virtual void reload();

	// Check if can fire
	bool canFire();

	// Used to determine which sound to play when the weapon fires
	int weaponSoundId;

	// Return string for ammo count
	std::string getAmmoString();
};

