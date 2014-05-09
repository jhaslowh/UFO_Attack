#include "UFOCowtapult.h"


UFOCowtapult::UFOCowtapult() : Weapon()
{
	weaponSoundId = SE_COWTAPULT;
	imageid = PI_UFO_COWTAPULT;
	originX = 0.0f; 
	originY = 16.0f;

	// Weapon properties 
	typeId = PI_UFO_COWTAPULT;
	clipCapacity = 2;
	clip = clipCapacity;
	spread = 0.73f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 3;
	reloadTime = 3.0f;
	timeBetweenShots = 2.0f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 90.0f;
	barrelOffset[1] = 0.0f;
	damage = 75.0f;
	isPlayerWeapon = true;
	usesAmmo = true;

	// Setup projectile 
	proj = new Projectile();
	proj->setSpeed(500);
	proj->setSize(50);
	proj->setType(3);
	proj->setImageId(GI_NPC_COW_1);
	proj->setOffset(25.0f,15.5f);
	proj->setImageGlowId(GI_NPC_COW_1);
	proj->setGlowOffset(25.0f,15.5f);
	proj->setDrawColor(1.0f, 1.0f, 1.0f, 1.0f);
	proj->setExplodes(true);
	proj->getExplRef()->setAsSplat();
	proj->setSmokeTrail(false);
}

UFOCowtapult::~UFOCowtapult(){
}
