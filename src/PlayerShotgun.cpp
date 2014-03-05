#include "PlayerShotgun.h"


PlayerShotgun::PlayerShotgun(): Weapon()
{
	imageid = PI_GUN_LASER;
	originX = -2.0f; 
	originY = 3.0f;

	// Weapon properties 
	typeId = PI_GUN_LASER;
	clipCapacity = 15;
	clip = 15;
	spread = .2; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 5;
	reloadTime = 0.2;
	timeBetweenShots = 0.01f;
	firetype = FIRETYPE_RAPID;
	barrelOffset[0] = 22;
	barrelOffset[1] = -4;

	// Muzzle flash
	muzzleImageId = -1;
	muzzleOffset[0] = 0;
	muzzleOffset[1] = 0;
	flashTime = 0;
}

PlayerShotgun::~PlayerShotgun(){}
