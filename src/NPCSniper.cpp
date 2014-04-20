#include "NPCSniper.h"


NPCSniper::NPCSniper() : Weapon()
{
	imageid = GI_NPC_SNIPER;
	originX = -5.0f; 
	originY = 8.0f;

	// Weapon properties 
	typeId = GI_NPC_SNIPER;
	clipCapacity = 10;
	clip = clipCapacity;
	spread = 0.0f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 1.0f;
	timeBetweenShots = 1.0f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 44.0f;
	barrelOffset[1] = 2.0f;
	damage = 20.0f;
	isPlayerWeapon = false;
	usesAmmo = false;
	minAngle = -40;
	maxAngle = 40;

	// Muzzle flash
	muzzleImageId = GI_NPC_SMG_FLASH;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 3;
	flashTime = 0.15f;

	// Setup projectile 
	projTemp.speed = 1500.0f;
	projTemp.imageId = GI_PROJ;
	projTemp.imageOrigin[0] = 5.0f;
	projTemp.imageOrigin[1] = 2.0f;
	projTemp.glowImageId = GI_PROJ_GLOW;
	projTemp.glowImageOrigin[0] = 7.5f; 
	projTemp.glowImageOrigin[1] = 2.0f; 
	projTemp.setColor(1.0f, .95f, .21f, 1.0f);
	projTemp.explodes = false;
}

NPCSniper::~NPCSniper(){}
