#include "Weapon.h"


Weapon::Weapon(void)
{
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

	// Muzzle flash
	muzzleImageId = -1;
	muzzleOffset[0] = 0;
	muzzleOffset[1] = 0;
	muzzleOrigin[0] = 0;
	muzzleOrigin[1] = 0;
	flashTime = 0;
	cFlashTime = 0;

	// Math values 
	mTheta = 0.0f;
}


Weapon::~Weapon(){}

// Call to get rotation
float Weapon::getRotation(){
	return rotation;
}

// Set the facing direction for the weapon
void Weapon::setFacingDirec(bool value){lookingRight = value;}
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

		// Set muzzle location 
		muzzleOffset[0] = locX + (cos(mTheta) * barrelOffset[0]);
		muzzleOffset[1] = locY - barrelOffset[1] + (sin(mTheta) * barrelOffset[0]);
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
	// Input should be handled by child class in this format

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
		rotation += 180.0f;

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
			mAtlas->draw(mgl, muzzleImageId, muzzleOffset[0], muzzleOffset[1], 1.0f, rotation, muzzleOrigin[0], muzzleOrigin[1]);
	}
	else{
		glCullFace(GL_FRONT);
		mAtlas->drawScale2(mgl, imageid, locX, locY, -1.0f, 1.0f, rotation, originX, originY);
		// Draw muzzle flash 
		if (cFlashTime > 0)
			mAtlas->drawScale2(mgl, muzzleImageId, muzzleOffset[0], muzzleOffset[1],-1.0f, 1.0f, rotation, muzzleOrigin[0], muzzleOrigin[1]);
		glCullFace(GL_BACK);
	}
}

// Fire the weapon
void Weapon::fire(float targetx, float targety, Handlers* handlers){
	// Fire shots 
	for (int i = 0; i < bulletsPerShot; i++){
		// Calculate weapon location 
		weaponLocX = locX;
		weaponLocY = locY - barrelOffset[1];

		// Get angle between weapon loc and target
		mTheta = (float)atan2((double)(targety - locY), (double)(targetx - locX));

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
		Projectile* p = new BulletProjectile(x, y, (int)projTemp.speed, true, direcX, direcY);
		p->setImageId(projTemp.imageId);
		p->setImageGlowId(projTemp.glowImageId);
		p->setOffset(projTemp.imageOrigin[0], projTemp.imageOrigin[1]);
		p->setGlowOffset(projTemp.glowImageOrigin[0], projTemp.glowImageOrigin[1]);
		p->setExplodes(projTemp.explodes);
		p->setDamage(damage/(float)bulletsPerShot);

		if (isPlayerWeapon)
			p->setFiredBy(PFB_PLAYER);
		else 
			p->setFiredBy(PFB_ENEMY);

		((ProjectileHandler*)handlers->projHandler)->addNewProjectile((Projectile*)(p));
	}

	// Subtract shot from clip
	if (usesAmmo) clip--;
	// Add shot time
	cTimeBetweenShots = timeBetweenShots;
	// Add muzzle time
	cFlashTime = flashTime;
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