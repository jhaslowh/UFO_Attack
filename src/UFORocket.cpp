#include "UFORocket.h"


UFORocket::UFORocket() : Weapon()
{
	weaponSoundId = SE_UFO_ROCKET_LAUNCH_SOUND;
	imageid = PI_UFO_ROCKET;
	originX = 0.0f; 
	originY = 9.0f;

	// Weapon properties 
	typeId = PI_UFO_ROCKET;
	clipCapacity = 4;
	clip = clipCapacity;
	spread = 0.23f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 1.0f;
	timeBetweenShots = 1.0f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 43.0f;
	barrelOffset[1] = 0.0f;
	damage = 0.0f;
	isPlayerWeapon = true;
	usesAmmo = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
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

UFORocket::~UFORocket(){
}
