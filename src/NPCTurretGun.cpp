#include "NPCTurretGun.h"


NPCTurretGun::NPCTurretGun()
{
	weaponSoundId = SE_NPC_SMG_SOUND;
	imageid = GI_MACHINE_GUN;
	originX = 6.0f; 
	originY = 16.0f;

	// Weapon properties 
	typeId = GI_MACHINE_GUN;
	clipCapacity = 10;
	clip = clipCapacity;
	spread = .04f; // In radians
	verticalDisplacement = 5;
	horizontalDisplacement = 15;
	bulletsPerShot = 2;
	reloadTime = 0.8f;
	timeBetweenShots = 0.1f;
	firetype = FIRETYPE_RAPID;
	barrelOffset[0] = 35.0f;
	barrelOffset[1] = 0.0f;
	damage = 4.0f;
	usesAmmo = false;
	isPlayerWeapon = false;

	// Muzzle flash
	muzzleImageId = GI_NPC_SMG_FLASH;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 3.0f;
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

NPCTurretGun::~NPCTurretGun()
{

}
