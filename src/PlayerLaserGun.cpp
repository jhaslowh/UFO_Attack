#include "PlayerLaserGun.h"


PlayerLaserGun::PlayerLaserGun() : Weapon()
{
	weaponSoundId = SE_PLAYER_LASER_SOUND;
	imageid = PI_GUN_LASER;
	originX = -2.0f; 
	originY = 3.0f;

	// Weapon properties 
	typeId = PI_GUN_LASER;
	clipCapacity = 15;
	clip = clipCapacity;
	spread = 0.025f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 0.2f;
	timeBetweenShots = 0.1f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 22;
	barrelOffset[1] = -4;
	damage = 15.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_LASER_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.1f;

	// Setup projectile 
	proj = new Projectile();
	proj->setSpeed(700);
	proj->setImageId(GI_PROJ);
	proj->setOffset(5.0f,2.0f);
	proj->setImageGlowId(GI_PROJ_GLOW);
	proj->setGlowOffset(7.5f,2.0f);
	proj->setDrawColor(1.0f, 0.0f, 0.0f, 1.0f);
	proj->setExplodes(false);
}

PlayerLaserGun::~PlayerLaserGun(){}
