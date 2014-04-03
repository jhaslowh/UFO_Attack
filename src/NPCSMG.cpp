#include "NPCSMG.h"

NPCSMG::NPCSMG()
{	
	imageid = GI_NPC_SMG;
	originX = -5.0f; 
	originY = 8.0f;

	// Weapon properties 
	typeId = GI_NPC_SMG;
	clipCapacity = 45;
	clip = clipCapacity;
	spread = .04f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 1;
	reloadTime = 0.8f;
	timeBetweenShots = 0.07f;
	firetype = FIRETYPE_RAPID;
	barrelOffset[0] = 31;
	barrelOffset[1] = 2.4;
	damage = 4.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = GI_NPC_SMG_FLASH;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 3;
	flashTime = 0.15f;

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


NPCSMG::~NPCSMG()
{

}
