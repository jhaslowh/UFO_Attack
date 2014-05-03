#include "NPCSam.h"


NPCSam::NPCSam()
{
	weaponSoundId = SE_NPC_SMG_SOUND;
	imageid = GI_SAM;
	originX = 20.0f; 
	originY = 5.0f;

	// Weapon properties 
	typeId = GI_SAM;
	clipCapacity = 1;
	clip = clipCapacity;
	spread = .02f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 0.8f;
	timeBetweenShots = 0.3f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 18.0f;
	barrelOffset[1] = 0.0f;
	damage = 10.0f;
	usesAmmo = false;
	isPlayerWeapon = false;

	// Muzzle flash
	muzzleImageId = -1;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 3.0f;
	flashTime = 0.0f;

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


NPCSam::~NPCSam(void)
{
}
