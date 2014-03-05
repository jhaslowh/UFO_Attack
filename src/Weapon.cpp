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

	// Muzzle flash
	muzzleImageId = -1;
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

// Set the facing direction for the weapon
void Weapon::setFacingDirec(bool value){lookingRight = value;}
// Get the facing direction of the weapon
bool Weapon::getFacingDirecton(){return lookingRight;}

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
	float mTheta = atan2((double)(targetY - locY), (double)(targetX - locX));
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
	if (lookingRight)
		mAtlas->draw(mgl, imageid, locX, locY, 1.0f, rotation, originX, originY);
	else{
		glCullFace(GL_FRONT);
		mAtlas->drawScale2(mgl, imageid, locX, locY, -1.0f, 1.0f, rotation, originX, originY);
		glCullFace(GL_BACK);
	}

	// TODO draw flash 
}

// Fire the weapon
void Weapon::fire(float targetx, float targety, Handlers* handlers){
	// Fire shots 
	for (int i = 0; i < bulletsPerShot; i++){
		// Calculate weapon location 
		float weaponLocX = locX;
		float weaponLocY = locY - barrelOffset[1];

		/*
		// Get angle between weapon loc and target
		float mTheta = atan2((double)(targety - locY), (double)(targetx - locX));

		// Apply spread to angle.
		float spr = ((float)rand() / (float)RAND_MAX) * spread;
		if (rand() % 100 > 50)
			mTheta += spr;
		else 
			mTheta -= spr;

		// Convert angle to direction 
		float direcX = cos(mTheta);
		float direcY = sin(mTheta);

		// Determin Displacement 
		float dispX = ((float)rand() / (float)RAND_MAX) * horizontalDisplacement;
		float dispY = ((float)rand() / (float)RAND_MAX) * verticalDisplacement;

		// Set the projectiles location as 
		float x = weaponLocX + (direcX * (barrelOffset[0] + dispX));
		float y = weaponLocY + (direcY * (barrelOffset[0] + dispX));
		x += direcX * dispY;
		y += direcY * dispY;
		*/
		//direcY *= -1;

		// Add projectile to list in handlers 
		((ProjectileHandler*)handlers->projHandler)->addNewProjectile((Projectile*)(new NSMOProjectile(weaponLocX, weaponLocY, targetx, targety)));
		
	}

	// Subtract shot from clip
	clip--;
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
	return clip != 0 && cTimeBetweenShots <= 0;
}