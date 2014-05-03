#include "NPCTankBarrel.h"


NPCTankBarrel::NPCTankBarrel() : Weapon()
{
	weaponSoundId = SE_NPC_TANK_FIRE;
	imageid = GI_TANK_BARREL;
	originX = 0.0f; 
	originY = 3.5f;

	// Weapon properties 
	typeId = GI_TANK_BARREL;
	clipCapacity = 10;
	clip = clipCapacity;
	spread = 0.05f; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 1.0f;
	timeBetweenShots = 1.0f;
	firetype = FIRETYPE_SINGLE;
	barrelOffset[0] = 65.0f;
	barrelOffset[1] = 0.0f;
	damage = 40.0f;
	isPlayerWeapon = false;
	usesAmmo = false;
	minAngle = -35;
	maxAngle = 35;

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

NPCTankBarrel::~NPCTankBarrel()
{

}
