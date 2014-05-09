#include "Weapon.h"

Weapon::Weapon()
{
	weaponSoundId = 0;

	imageid = -1;
	locX = 0.0f;
	locY = 0.0f;
	originX = 0.0f; 
	originY = 0.0f;
	rotation = 0.0f;

	// Weapon properties 
	lookingRight = true;
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
	damage = 0.0f;
	isPlayerWeapon = false;
	usesAmmo = true;
	minAngle = -90;
	maxAngle = 90;
	proj = NULL;

	// Muzzle flash
	muzzleImageId = -1;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 0;
	flashTime = 0;
	cFlashTime = 0;

	// Math values 
	mTheta = 0.0f;
}
Weapon::~Weapon(){
	delete proj;
	proj = NULL;
}

// Returns current weapon rotation
float Weapon::getRotation(){
	return rotation;
}
// Set the current weapon rotation
void Weapon::setRotation(float value){
	rotation = value;
}

// Set the facing direction for the weapon
// Set to true if looking right. 
void Weapon::setFacingDirec(bool value){
	lookingRight = value;
}
// Get the facing direction of the weapon
bool Weapon::getFacingDirecton(){return lookingRight;}

// Set and get for player weapon 
void Weapon::setIsPlayerWeapon(bool value){isPlayerWeapon = value;}
bool Weapon::getIsPlayerWeapon(){return isPlayerWeapon;}

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
// Note: if this is an NPC weapon, do not call this method
void Weapon::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	// Get target shot location
	float targetX = ((Camera2D*)handlers->camera)->toLevelX(mMouseH->getX());
	float targetY = ((Camera2D*)handlers->camera)->toLevelY(mMouseH->getY());

	// Set shooting direction 
	if (targetX > locX )
		lookingRight = true;
	if (targetX < locX)
		lookingRight = false;

	// Set rotation 
	//   Parent class that calls this (UFO or Player should grab the 
	//   rotation if it is needed. (Player needs to rotate arm)
	// Get angle 
	mTheta = (float)atan2((double)(targetY - locY), (double)(targetX - locX));
	// Set rotation
	rotation = (float)(mTheta * (180.0f / 3.14159f));

	// Clamp rotation
	if (rotation < -90.0f)
		rotation += 180.0f;
	if (rotation > 90.0f)
		rotation -= 180.0f;

	// Check if rotation is valid and restrict angle
	if (lookingRight){
		if (rotation < minAngle)
			rotation = minAngle;
		else if (rotation > maxAngle)
			rotation = maxAngle;
	}
	else {
		if (rotation > -minAngle)
			rotation = -minAngle;
		else if (rotation < -maxAngle)
			rotation = -maxAngle;
	}

	// Check for fire shot 
	if (canFire() && 
		((firetype == FIRETYPE_SINGLE && mMouseH->isLeftDown() && !mMouseH->wasLeftDown()) ||
			(firetype == FIRETYPE_RAPID && mMouseH->isLeftDown()))){
		fire(targetX, targetY, handlers);
	}

	if (mKeyH->keyPressed(KEY_R))
		reload();
}

// Draw weapon to screen
void Weapon::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	// Draw weapon 
	if (lookingRight){
		mAtlas->draw(mgl, imageid, locX, locY, 1.0f, rotation, originX, originY);
		// Draw muzzle flash 
		if (cFlashTime > 0)
			mAtlas->draw(mgl, muzzleImageId, locX, locY, 1.0f, rotation, 
			muzzleOrigin[0] - barrelOffset[0], muzzleOrigin[1] + barrelOffset[1]);
	}
	else{
		glCullFace(GL_FRONT);
		mAtlas->drawScale2(mgl, imageid, locX, locY, -1.0f, 1.0f, rotation, originX, originY);
		// Draw muzzle flash 
		if (cFlashTime > 0)
			mAtlas->drawScale2(mgl, muzzleImageId, locX, locY,-1.0f, 1.0f, rotation, 
			muzzleOrigin[0] - barrelOffset[0], muzzleOrigin[1] + barrelOffset[1]);
		glCullFace(GL_BACK);
	}
}

// Use with the npc to fire at a requested target
// Will not fire if not allowed to (out of ammo etc.)
// NOTE: If you do not restrict fire radius in the calling method
// this method will fire in any direction. 
void Weapon::npcFire(float targetx, float targety, Handlers* handlers){
	// Set shooting direction 
	if (targetx > locX )
		lookingRight = true;
	if (targetx < locX)
		lookingRight = false;

	// Set the rotation because the class that calls this might 
	// need it even if it does not fire successfully. 
	// Get angle 
	mTheta = (float)atan2((double)(targety - locY), (double)(targetx - locX));
	// Set rotation
	rotation = (float)(mTheta * (180.0f / 3.14159f));

	// Clamp rotation
	if (rotation < -90.0f)
		rotation += 180.0f;
	if (rotation > 90.0f)
		rotation -= 180.0f;
	
	// Check if rotation is valid and restrict angle
	if (lookingRight){
		if (rotation < minAngle){
			//rotation = minAngle;
			rotation = 0.0f;
			return;
		}
		else if (rotation > maxAngle){
			//rotation = maxAngle;
			rotation = 0.0f;
			return;
		}
	}
	else {
		if (rotation > -minAngle){
			//rotation = -minAngle;
			rotation = 0.0f;
			return;
		}
		else if (rotation < -maxAngle){
			//rotation = -maxAngle;
			rotation = 0.0f;
			return;
		}
	}

	// Check for fire shot 
	if (canFire()){
		fire(targetx, targety, handlers);
	}
}

// Fire the weapon
void Weapon::fire(float targetx, float targety, Handlers* handlers){
	// Sound
	SoundHandler * sh = (SoundHandler*)handlers->soundHandler;
	sh->playSoundEffect(weaponSoundId);
	// Fire shots 
	for (int i = 0; i < bulletsPerShot; i++){
		// Calculate weapon location 
		weaponLocX = locX;
		weaponLocY = locY - barrelOffset[1];

		// Get angle between weapon loc and target
		mTheta = (float)atan2((double)(targety - locY), (double)(targetx - locX));

		// Clamp theta 
		if (lookingRight){
			if (mTheta < minAngle * DEG_TO_RAD)
				mTheta = minAngle * DEG_TO_RAD;
			else if (mTheta > maxAngle * DEG_TO_RAD)
				mTheta = maxAngle * DEG_TO_RAD;
		}
		else {
			if (mTheta < 0.0f && mTheta > ((-180.0f-minAngle) * DEG_TO_RAD))
				mTheta = ((-180.0f-minAngle) * DEG_TO_RAD);
			else if (mTheta > 0.0f && mTheta < (180.0f-maxAngle) * DEG_TO_RAD)
				mTheta = (180.0f-maxAngle) * DEG_TO_RAD;
		}

		// Apply spread to angle.
		spr = ((float)rand() / (float)RAND_MAX) * spread;
		if (rand() % 100 > 50)
			mTheta += spr / 2.0f;
		else 
			mTheta -= spr / 2.0f;

		// Convert angle to direction 
		direcX = cos(mTheta);
		direcY = sin(mTheta);

		// Determin Displacement 
		dispX = ((float)rand() / (float)RAND_MAX) * horizontalDisplacement;
		dispY = ((float)rand() / (float)RAND_MAX) * verticalDisplacement;

		// Set the projectiles location as 
		x = weaponLocX + (direcX * (barrelOffset[0] + dispX));
		y = weaponLocY + (direcY * (barrelOffset[0] + dispX));
		x += direcX * dispY;
		y += direcY * dispY;

		// Add projectile to list in handlers 
		if (proj != NULL){
			proj->setPosition(x,y);
			proj->setDirec(direcX, direcY);
			proj->setDamage(damage/(float)bulletsPerShot);
			if (isPlayerWeapon)
				proj->setFiredBy(PFB_PLAYER);
			else 
				proj->setFiredBy(PFB_ENEMY);
			((ProjectileHandler*)handlers->projHandler)->addNewProjectile((Projectile*)proj->clone());
		}
	}

	// Subtract shot from clip
	if (usesAmmo) clip--;
	// Add shot time
	cTimeBetweenShots = timeBetweenShots;
	// Add muzzle time
	cFlashTime = flashTime;
}

// Set the rotation of the weapon based off the sent target 
void Weapon::setRotationByTarget(float targetx, float targety){
	// Set shooting direction 
	if (targetx > locX )
		lookingRight = true;
	if (targetx < locX)
		lookingRight = false;

	// Set the rotation because the class that calls this might 
	// need it even if it does not fire successfully. 
	// Get angle 
	mTheta = (float)atan2((double)(targety - locY), (double)(targetx - locX));
	// Set rotation
	rotation = (float)(mTheta * (180.0f / 3.14159f));

	// Clamp rotation
	if (rotation < -90.0f)
		rotation += 180.0f;
	if (rotation > 90.0f)
		rotation -= 180.0f;
	
	// Check if rotation is valid and restrict angle
	if (lookingRight){
		if (rotation < minAngle)
			rotation = minAngle;
		else if (rotation > maxAngle)
			rotation = maxAngle;
	}
	else {
		if (rotation > -minAngle)
			rotation = -minAngle;
		else if (rotation < -maxAngle)
			rotation = -maxAngle;
	}
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
	return (clip != 0 || !usesAmmo) && cTimeBetweenShots <= 0;
}

// Return string for ammo count
std::string Weapon::getAmmoString(){
	std::string ammoS("");
	ammoS += toString(clip);
	ammoS += "/";
	ammoS += toString(clipCapacity);
	return ammoS;
}
