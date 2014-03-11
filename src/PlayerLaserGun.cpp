#include "PlayerLaserGun.h"


PlayerLaserGun::PlayerLaserGun() : Weapon()
{
	imageid = PI_GUN_LASER;
	originX = -2.0f; 
	originY = 3.0f;

	// Weapon properties 
	typeId = PI_GUN_LASER;
	clipCapacity = 15;
	clip = 15;
	spread = 0; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 0.2;
	timeBetweenShots = 0.1f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 22;
	barrelOffset[1] = -4;
	damage = 1.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_LASER_MUZ;
	muzzleOffset[0] = 0;
	muzzleOffset[1] = 0;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.1;
}

PlayerLaserGun::~PlayerLaserGun(){}
