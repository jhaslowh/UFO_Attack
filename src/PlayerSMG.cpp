#include "PlayerSMG.h"


PlayerSMG::PlayerSMG()
{
	imageid = PI_GUN_SMG;
	originX = 2.0f; 
	originY = 7.0f;

	// Weapon properties 
	typeId = PI_GUN_SMG;
	clipCapacity = 45;
	clip = clipCapacity;
	spread = .04; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 1;
	reloadTime = 0.8;
	timeBetweenShots = 0.07f;
	firetype = FIRETYPE_RAPID;
	barrelOffset[0] = 30;
	barrelOffset[1] = -1;
	damage = 1.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.05;
}

PlayerSMG::~PlayerSMG()
{

}
