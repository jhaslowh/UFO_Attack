#include "UFOMachineGun.h"


UFOMachineGun::UFOMachineGun()
{
	weaponSoundId = SE_UFO_ROCKET_LAUNCH_SOUND;
	imageid = PI_UFO_MACHINE_GUN;
	originX = 0.0f; 
	originY = 5.0f;

	// Weapon properties 
	typeId = PI_UFO_MACHINE_GUN;
	clipCapacity = 100;
	clip = clipCapacity;
	spread = 0.23f; // In radians
	verticalDisplacement = 10;
	horizontalDisplacement = 10;
	bulletsPerShot = 1;
	reloadTime = 1.0f;
	timeBetweenShots = .02f;
	firetype = FIRETYPE_RAPID;
	barrelOffset[0] = 42.0f;
	barrelOffset[1] = 0.0f;
	damage = 4.0f;
	isPlayerWeapon = true;
	usesAmmo = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.15f;

	// Setup projectile 
	proj = new Projectile();
	proj->setSpeed(700);
	proj->setImageId(GI_PROJ);
	proj->setOffset(5.0f,2.0f);
	proj->setImageGlowId(GI_PROJ_GLOW);
	proj->setGlowOffset(7.5f,2.0f);
	proj->setDrawColor(.4f, .4f, .4f, 1.0f);
	proj->setExplodes(false);
}

UFOMachineGun::~UFOMachineGun()
{

}
