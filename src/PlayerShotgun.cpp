#include "PlayerShotgun.h"


PlayerShotgun::PlayerShotgun(): Weapon()
{
	imageid = PI_GUN_SHOTGUN;
	originX = -3.0f; 
	originY = 2.0f;

	// Weapon properties 
	typeId = PI_GUN_SHOTGUN;
	clipCapacity = 15;
	clip = clipCapacity;
	spread = .2; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 6;
	reloadTime = 0.8;
	timeBetweenShots = 0.01f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 36;
	barrelOffset[1] = -4;
	damage = 1.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.5;
}

PlayerShotgun::~PlayerShotgun(){}
