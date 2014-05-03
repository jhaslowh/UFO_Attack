#include "PlayerSMG.h"


PlayerSMG::PlayerSMG()
{
	imageid = PI_GUN_SMG;
	originX = 2.0f; 
	originY = 7.0f;

	// Weapon properties 
	typeId = PI_GUN_SMG;
	clipCapacity = 45;
	clip = clipCapacity;
	spread = .28f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 15;
	bulletsPerShot = 1;
	reloadTime = 0.8f;
	timeBetweenShots = 0.07f;
	firetype = FIRETYPE_RAPID;
	barrelOffset[0] = 30;
	barrelOffset[1] = -2;
	damage = 10.0f;
	isPlayerWeapon = true;

	// Muzzle flash
	muzzleImageId = PI_GUN_SHOTGUN_MUZ;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 6;
	flashTime = 0.05f;

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

PlayerSMG::~PlayerSMG(){}
