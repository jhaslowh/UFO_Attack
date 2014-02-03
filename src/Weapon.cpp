#include "Weapon.h"


Weapon::Weapon(void)
{
	locX = 0.0f;
	locY = 0.0f;
	originX = 0.0f; 
	originY = 0.0f;
	rotation = 0.0f;

	// Weapon properties 
	typeId = 0;
	clipCapacity = 0;
	clip = 0;
	spread = 0; // In radians
	verticalDisplacement = 0;
	horizontalDisplacement = 0;
	bulletsPerShot = 1;
	reloadTime = 0;
	cReloadTime = 0;
	timeBetweenShots = 0.0f;
	cTimeBetweenShots = 0.0f;
	firetype = 0;
	barrelOffset[0] = 0;
	barrelOffset[0] = 1;

	// Muzzle flash
	muzzleOffset[0] = 0;
	muzzleOffset[1] = 0;
	flashTime = 0;
	cFlashTime = 0;
}


Weapon::~Weapon(){}

// Call to get rotation
float Weapon::getRotation(){
	return rotation;
}

// Update weapon state
// x: the x location in the world for the weapon
// y: the y location in the world for the weapon
void Weapon::update(float deltaTime, float x, float y){
	// Set weapon location 
	locX = x;
	locY = y;

	// Reload gun if empty 
	if (clip == 0){
		cReloadTime += deltaTime;
		if (cReloadTime >= reloadTime){
			clip = clipCapacity;
			cReloadTime = 0.0f;
		}
	}

	// Update muzzle flash time 
	if (cFlashTime != 0.0f){
		cFlashTime -= deltaTime;
		if (cFlashTime < .0f)
			cFlashTime = 0.0f;
	}

	// Update time between shots 
	if (cTimeBetweenShots > 0.0f){
		cTimeBetweenShots -= deltaTime;
		if (cTimeBetweenShots < 0.0f){
			cTimeBetweenShots = 0.0f;
		}
	}

}

// Update weapon input
void Weapon::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	// Input should be handled by child class in this format

	// 1. Get target shot location
	// 2. Check if it is a valid angle (player cannot shoot backwards)
	// - if true
	// -- 1. Set rotation 
	//       Parent class that calls this (UFO or Player should grab the 
	//       rotation if it is needed. (Player needs to rotate arm)
	// -- 2. Check if can fire (not reloading, not in middle of shot, has ammo)
	//    - if true
	//    -- 1. Fire shot

	if (mKeyH->keyPressed(KEY_R))
		reload();
}

// Draw weapon to screen
void Weapon::draw(GLHandler* mgl){
	// Handle in child class
}

// Fire the weapon
void Weapon::fire(float targetx, float targety, Handlers* handlers){
	// Fire shots 
	for (int i = 0; i < bulletsPerShot; i++){
		// TODO 

		// 1. Create a new projectile
		// 2. Calculate weapon location 
		// -- WeaponLocx = locX;
		// -- WeaponLocy = locY - barrelOffset[1];
		// 3. Get angle between weaponLoc and target
		// 4. Apply spread to angle.
		// -- this is + or - Random(0, spread) 
		// 5. Convert angle to direction 
		// -- direc[0] = cos(angle)
		// -- direc[1] = sin(angle)
		// -- (Give direc to projectile as it needs it to move)
		// 6. Determin Displacement 
		// -- dispX = Random(0, horDispacement)
		// -- dispY = Random(0, vertDisplacement)
		// 7. Set the projectiles location as 
		// -- x = weaponLocx + (direc[0] * (barrelOffset[0] + dispX);
		// -- y = weaponLocy + (direc[1] * (barrelOffset[0] + dispX);
		// -- x += direc[0] * dispY;
		// -- y += direc[1] * dispY;
		// -- (Set these as the projetiles location)
		// 8. Add projectile to list in handlers 
	}

	// Subtract shot from clip
	clip--;
	// Add shot time
	cTimeBetweenShots = timeBetweenShots;
	// Add muzzle time
	cFlashTime = flashTime;

	// Setup realod 
	if (clip == 0)
		reload();
}

// Check if the gun is reloading 
bool Weapon::reloading(){
	return cReloadTime > 0.0f;
}

// Reload the gun 
void Weapon::reload(){
	if (!reloading() && clip != clipCapacity){
		cReloadTime = reloadTime;
		cTimeBetweenShots = 0.0f;
		clip = 0;
	}
}

// Check if can fire
bool Weapon::canFire(){
	return clip != 0 && cTimeBetweenShots <= 0;
}