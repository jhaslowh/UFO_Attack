#include "UFOCowtapult.h"


UFOCowtapult::UFOCowtapult() : Weapon()
{
	weaponSoundId = NULL; //Could use a good MOOO
	imageid = PI_UFO_COWTAPULT;
	originX = 0.0f; 
	originY = 9.0f;

	// Weapon properties 
	typeId = PI_UFO_COWTAPULT;
	clipCapacity = 1;
	clip = clipCapacity;
	spread = 0.73f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 3;
	reloadTime = 1.0f;
	timeBetweenShots = 2.0f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 43.0f;
	barrelOffset[1] = 0.0f;
	damage = 75.0f;
	isPlayerWeapon = true;
	usesAmmo = false;

	// Muzzle flash
	// Catapults don't have muzzle flash
	/*
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.15f;*/

	// Setup projectile 
	proj = new Projectile();
	proj->setSpeed(500);
	proj->setSize(50);
	proj->setType(3);
	proj->setImageId(GI_NPC_COW_1);
	proj->setOffset(10.0f,5.5f);
	proj->setImageGlowId(GI_NPC_COW_1);
	proj->setGlowOffset(10.0f,5.5f);
	proj->setDrawColor(1.0f, 1.0f, 1.0f, 1.0f);
	proj->setExplodes(true);
	proj->getExplRef()->setAsSplat();
	proj->setSmokeTrail(false);
}

UFOCowtapult::~UFOCowtapult(){
}
