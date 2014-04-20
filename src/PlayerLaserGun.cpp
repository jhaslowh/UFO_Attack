#include "PlayerLaserGun.h"


PlayerLaserGun::PlayerLaserGun() : Weapon()
{
	imageid = PI_GUN_LASER;
	originX = -2.0f; 
	originY = 3.0f;

	// Weapon properties 
	typeId = PI_GUN_LASER;
	clipCapacity = 15;
	clip = clipCapacity;
	spread = 0; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 0.2f;
	timeBetweenShots = 0.1f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 22;
	barrelOffset[1] = -4;
	damage = 15.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_LASER_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.1f;

	// Setup projectile 
	projTemp.speed = 700.0f;
	projTemp.imageId = GI_PROJ;
	projTemp.imageOrigin[0] = 5.0f;
	projTemp.imageOrigin[1] = 2.0f;
	projTemp.glowImageId = GI_PROJ_GLOW;
	projTemp.glowImageOrigin[0] = 7.5f; 
	projTemp.glowImageOrigin[1] = 2.0f; 
	projTemp.setColor(1.0f, 0.0f, 0.0f, 1.0f);
	projTemp.explodes = false;
}

PlayerLaserGun::~PlayerLaserGun(){}
