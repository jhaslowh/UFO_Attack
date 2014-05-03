#include "NPCStinger.h"


NPCStinger::NPCStinger() : Weapon()
{
	weaponSoundId = SE_NPC_ROCKET_LAUNCH_SOUND;
	imageid = GI_NPC_STINGER;
	originX = 22.0f; 
	originY = 8.0f;

	// Weapon properties 
	typeId = GI_NPC_STINGER;
	clipCapacity = 10;
	clip = clipCapacity;
	spread = 0.0f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 1.0f;
	timeBetweenShots = 2.3f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 27.0f;
	barrelOffset[1] = 1.0f;
	damage = 0.0f;
	isPlayerWeapon = false;
	usesAmmo = false;

	// Muzzle flash
	muzzleImageId = GI_NPC_SMG_FLASH;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 3;
	flashTime = 0.15f;

	// Setup projectile 
	proj = new Projectile();
	proj->setSpeed(1000);
	proj->setImageId(GI_MISSILE);
	proj->setOffset(10.0f,5.5f);
	proj->setImageGlowId(GI_MISSILE);
	proj->setGlowOffset(10.0f,5.5f);
	proj->setDrawColor(1.0f, 1.0f, 1.0f, 1.0f);
	proj->setExplodes(true);
	proj->getExplRef()->setAsBasic();
	proj->setSmokeTrail(true);
}

NPCStinger::~NPCStinger(){}
