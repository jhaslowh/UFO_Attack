#include "NPCSMG.h"

NPCSMG::NPCSMG() :Weapon()
{	
	weaponSoundId = SE_NPC_SMG_SOUND;
	imageid = GI_NPC_SMG;
	originX = -5.0f; 
	originY = 8.0f;

	// Weapon properties 
	typeId = GI_NPC_SMG;
	clipCapacity = 45;
	clip = clipCapacity;
	spread = .03f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 1;
	reloadTime = 0.8f;
	timeBetweenShots = 0.1f;
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
	proj = new Projectile();
	proj->setSpeed(700);
	proj->setImageId(GI_PROJ);
	proj->setOffset(5.0f,2.0f);
	proj->setImageGlowId(GI_PROJ_GLOW);
	proj->setGlowOffset(7.5f,2.0f);
	proj->setDrawColor(1.0f, .95f, .21f, 1.0f);
	proj->setExplodes(false);
}
NPCSMG::~NPCSMG(){}
