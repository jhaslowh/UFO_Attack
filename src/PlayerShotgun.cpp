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
	spread = .2f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 6;
	reloadTime = 0.8f;
	timeBetweenShots = 0.01f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 36;
	barrelOffset[1] = -4;
	damage = 25.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.5;

	// Setup projectile 
	projTemp.speed = 700.0f;
	projTemp.imageId = GI_PROJ;
	projTemp.imageOrigin[0] = 5.0f;
	projTemp.imageOrigin[1] = 2.0f;
	projTemp.glowImageId = GI_PROJ_GLOW;
	projTemp.glowImageOrigin[0] = 7.5f; 
	projTemp.glowImageOrigin[1] = 2.0f; 
	projTemp.explodes = false;
}

PlayerShotgun::~PlayerShotgun(){}
