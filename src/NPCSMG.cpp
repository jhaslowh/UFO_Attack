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
	barrelOffset[1] = 2.4f;
	damage = 4.0f;
	isPlayerWeapon = false;

	// Muzzle flash
	muzzleImageId = GI_NPC_SMG_FLASH;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 3;
	flashTime = 0.15f;

	// Setup projectile 
	projTemp.speed = 700.0f;
	projTemp.imageId = GI_PROJ;
	projTemp.imageOrigin[0] = 5.0f;
	projTemp.imageOrigin[1] = 2.0f;
	projTemp.glowImageId = GI_PROJ_GLOW;
	projTemp.glowImageOrigin[0] = 7.5f; 
	projTemp.glowImageOrigin[1] = 2.0f; 
	projTemp.setColor(1.0f, .95f, .21f, 1.0f);
	projTemp.explodes = false;
}


NPCSMG::~NPCSMG()
{

}
