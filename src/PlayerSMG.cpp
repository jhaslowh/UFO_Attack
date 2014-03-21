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
	spread = .04f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 1;
	reloadTime = 0.8f;
	timeBetweenShots = 0.07f;
	firetype = FIRETYPE_RAPID;
	barrelOffset[0] = 30;
	barrelOffset[1] = -2;
	damage = 1.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.05f;

	// Setup projectile 
	projTemp.speed = 700.0f;
	projTemp.imageId = GI_PROJ_RED;
	projTemp.imageOrigin[0] = 10.0f;
	projTemp.imageOrigin[1] = 4.0f;
	projTemp.glowImageId = GI_PROJ_RED_GLOW;
	projTemp.glowImageOrigin[0] = 15.0f; 
	projTemp.glowImageOrigin[1] = 7.5f; 
	projTemp.explodes = false;
}

PlayerSMG::~PlayerSMG()
{

}
