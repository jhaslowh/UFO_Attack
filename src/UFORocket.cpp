#include "UFORocket.h"


UFORocket::UFORocket() : Weapon()
{
	imageid = PI_UFO_ROCKET;
	originX = 0.0f; 
	originY = 9.0f;

	// Weapon properties 
	typeId = PI_UFO_ROCKET;
	clipCapacity = 4;
	clip = clipCapacity;
	spread = 0.2f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 1.0f;
	timeBetweenShots = 1.0f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 43.0f;
	barrelOffset[1] = 0.0f;
	damage = 0.0f;
	isPlayerWeapon = true;
	usesAmmo = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.15f;

	// Setup projectile 
	projTemp.speed = 1000.0f;
	projTemp.imageId = GI_MISSILE;
	projTemp.imageOrigin[0] = 10.0f;
	projTemp.imageOrigin[1] = 5.5f;
	projTemp.glowImageId = GI_MISSILE;
	projTemp.glowImageOrigin[0] = 10.0f; 
	projTemp.glowImageOrigin[1] = 5.5f; 
	projTemp.setColor(1.0f, 1.0f, 1.0f, 1.0f);
	projTemp.explodes = true;
	projTemp.explosion.setAsBasic();
	projTemp.smokeTrail = true;
}

UFORocket::~UFORocket(){
}
