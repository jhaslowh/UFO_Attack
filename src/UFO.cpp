#include "UFO.h"


UFO::UFO(){
	locX = 0.0f;
	locY = 0.0f;
	originX = 50.0f;
	originY = 50.0f;
	speed = 375.0f;
	minDistFromGround = 200.0f;
	width = 100.0f;
	height = 50.0f;
	lookingRight = true;

	partRate = .1f;
	cpartRate = 0.0f;

	armor = 100.0f;
	maxArmor = 100.0f;
	shield = 100.0f;
	maxShield = 100.0f;
	shieldChargeRate = 100.0f; // Charge per second 
	timeTillCharge = 5.0f;
	cTimeTillCharge = 0.0f;
	invincible = false;

	rayOn = false;
	rayCircleHeight = 37.0f;
	rayMoveSpeed = 100.0f;
	rayWidth = 248.0f;
	rayHeight = 300.0f;
	rayCircleCount = 14;
	rayOffsetMax = (rayHeight - rayCircleHeight) / (float)rayCircleCount;
	rayOffset = rayOffsetMax;
	rayScaleMin = 0.5f;
	rayScaleMax = 1.0f;

	// Energy
	energy = 100.0f;
	energyMax = 100.0f;
	eCharge = 34.0f; // Charge rate
	eDrain = 20.0f; // Drain rate 
	timeTilCharge = 4.0f;
	ctimeTilCharge = timeTilCharge;
	
	// Hit recently
	hitTime = .05f;
	chitTime = 0.0f;

	// Load weapon based off savedata
	usingWeapon1 = true;
	uweapon1 = NULL;
	uweapon2 = NULL;
}
UFO::~UFO(){
	delete uweapon1;
	uweapon1 = NULL;
	delete uweapon2;
	uweapon2 = NULL;
}

// Set location of the player
void UFO::setLocation(float x, float y){
	locX = x;
	locY = y;
}
float UFO::getX(){return locX;}
float UFO::getY(){return locY;}
// Returns center x coord of ufo
float UFO::getCenterX(){return locX;}
// Returns center y coord of ufo
float UFO::getCenterY(){return locY - (height * .5f);}
void UFO::setMaxArmor(float value){maxArmor = value;}
float UFO::getMaxArmor(){return maxArmor;}
void UFO::setArmor(float value){armor = value;}
float UFO::getArmor(){return armor;}
void UFO::setMaxShield(float value){maxShield = value;}
float UFO::getMaxShield(){return maxShield;}
void UFO::setShield(float value){shield = value;}
float UFO::getShield(){return shield;}
void UFO::setInvincible(bool value){invincible = value;}
void UFO::setRayOn(bool value){rayOn = value;}

// Check if abduction ray is turned on 
bool UFO::isRayOn(){return rayOn;}
// Get the area for collision detection with ship
Rec* UFO::getUFOArea(){return &collisionArea;}
// Get the area for collision detection with abduction ray
Rec* UFO::getAbductArea(){return &abductRayArea;}

// Returns the percent of current energy 
float UFO::getEnergyPercent(){return energy/energyMax;}

// Init 
void UFO::init(SaveData* savedata){
	if (savedata != NULL){
		// Load player weapon 1 from savedata 
		if (savedata->getUFOWeapon1() == StoreItems::SID_UFO_WEAPON_MISSILE)
			uweapon1 = (Weapon*)new UFORocket();
		else if (savedata->getUFOWeapon1() == StoreItems::SID_UFO_WEAPON_MACHINE_GUN)
			uweapon1 = (Weapon*)new UFOMachineGun(); 
		else if (savedata->getUFOWeapon1() == StoreItems::SID_UFO_WEAPON_COWTAPOLT)
			uweapon1 = (Weapon*)new UFOCowtapult(); // TODO change this to cowtapolt

		// Load player weapon 2 from savedata 
		if (savedata->getUFOWeapon2() == StoreItems::SID_UFO_WEAPON_MISSILE)
			uweapon2 = (Weapon*)new UFORocket();
		else if (savedata->getUFOWeapon2() == StoreItems::SID_UFO_WEAPON_MACHINE_GUN)
			uweapon2 = (Weapon*)new UFOMachineGun(); 
		else if (savedata->getUFOWeapon2() == StoreItems::SID_UFO_WEAPON_COWTAPOLT)
			uweapon2 = (Weapon*)new UFOCowtapult(); // TODO change this to cowtapolt
	}
}
	
// Load images
void UFO::load(){

}

// Update UFO
void UFO::update(float deltaTime, Handlers* handlers){
	// Update location 
	nextX = locX;
	nextY = locY;

	nextX += direcX * deltaTime * speed;
	nextY += direcY * deltaTime * speed;

	// Update shield 
	if (cTimeTillCharge > 0.0f){
		cTimeTillCharge -= deltaTime;
		if (cTimeTillCharge < 0.0f)
			cTimeTillCharge = 0.0f;
	}
	else {
		shield += shieldChargeRate * deltaTime;
		if (shield >= maxShield)
			shield = maxShield;
	}

	// Create particles 
	cpartRate += deltaTime;
	if (cpartRate >= partRate){
		cpartRate = 0.0f;
		// This will get a random angle that is +-45 degrees from strait down
		float angle = (((rand() % 1000)/1000.0f) * 1.57f) + .785f;
		((ParticleHandler*)handlers->partHandler)->add(
			GI_SPHERE,	// Image
			locX,locY-(height*.5f),	// Location
			15.0f,15.0f,// Origin
			cos(angle),sin(angle),	// Direction
			75.0f,		// Speed
			1.0f,		// Life
			0.0f,		// Rotation speed
			-1.0f);		// Scale speed 
	}

	// Update abduct ray
	rayOffset -= deltaTime * rayMoveSpeed;
	if (rayOffset <= 0.0f)
		rayOffset = rayOffsetMax;
	
	// Update energy charge time 
	ctimeTilCharge += deltaTime;
	if (ctimeTilCharge >= timeTilCharge){
		ctimeTilCharge = timeTilCharge;
	}

	// Update energy amount
	if (energy != energyMax && ctimeTilCharge >= timeTilCharge){
		energy += eCharge * deltaTime;
		if (energy > energyMax){
			energy = energyMax;
		}
	}

	// Draw energy if ray is on 
	if (rayOn){
		energy -= eDrain * deltaTime;
		ctimeTilCharge = 0.0f;
		if (energy <= 0.0f){
			((SoundHandler*)handlers->soundHandler)->stopMusic();
			rayOn = false;
			energy = 0.0f;

		}
	}
	
	// Update hit time
	if (chitTime > 0.0f){
		chitTime -= deltaTime;
		if (chitTime < 0.0f)
			chitTime = 0.0f;
	}
}

// Update UFO when player is on foot
void UFO::updateOnFoot(float deltaTime, Handlers* handlers){
	// Update hit time
	if (chitTime > 0.0f){
		chitTime -= deltaTime;
		if (chitTime < 0.0f)
			chitTime = 0.0f;
	}
}

// Check collision 
void UFO::checkCollision(Handlers* handlers){
	// Make sure UFO cannot leave level on left or right side

	LevelProperties* lp = (LevelProperties*)(handlers->levelProps);

	if (nextX - 50.0f < lp->getLevelLeft())
		nextX = lp->getLevelLeft() + 50.0f;
	if (nextX + 50.0f > lp->getLevelRight())
		nextX = lp->getLevelRight() - 50.0f;

	// Keep UFO from leaving top of level

	if (nextY < lp->getLevelTop())
		nextY = lp->getLevelTop();

	// ----------------------------------
	// Check UFO collision with ground 
	// Push UFO away from ground if too close 
	// ----------------------------------
	
	// Point used during collision detection 
	Point p;
	Point* itr;

	// Setup vertical line segment 
	vertA.setLocation(nextX, nextY);
	vertB.setLocation(nextX, nextY + minDistFromGround);

	// Normal ground check: 
	itr = handlers->ground->getPoints();
	if (itr != NULL){
		while (itr->next != NULL){
			// Check if player is close to point
			if ((*itr).getX() <= nextX && (*(itr->next)).getX() >= nextX){
				if (checkSegSeg(vertA, vertB, *itr, *(itr->next), &p)){
					nextX = p.getX();
					nextY = p.getY() - minDistFromGround;
					break;
				}
			}
			itr = itr->next;
		}
	}

	// ---------------------------------------------
	// Check ufo collision with enemy projectiles  
	// ---------------------------------------------
	// Fix collision rectangle for next step
	collisionArea.setLocation(locX - originX, locY - originY);
	collisionArea.setSize(width, height);

	Projectile** projs = ((ProjectileHandler*)handlers->projHandler)->getProjList();
	Point projp;

	// Check all projectiles for collision 
	for (int i = 0; i <= ((ProjectileHandler*)handlers->projHandler)->getLastActive(); i++){
		// Null check 
		if (projs[i] != NULL && projs[i]->getAlive() && projs[i]->getFiredBy() == PFB_ENEMY){
			// Quick distance check 
			if (dist(nextX, nextY,projs[i]->getCurrentX(), projs[i]->getCurrentY()) <100){ 
				// Check for collision 
				if (checkRecSeg(&collisionArea, 
					projs[i]->getCurrentX(), projs[i]->getCurrentY(), 
					projs[i]->getPrevX(), projs[i]->getPrevY(), &projp)){

					// Tell projectile we had a player collision 
					projs[i]->collide(&projp, handlers, P_PLAYER_COLL);

					// Apply projectile damage to player
					((SoundHandler*)handlers->soundHandler)->playSoundEffect(SE_UFO_HIT);
					applyDamage(projs[i]->getDamage());
				}
			}
		}
	}

	// ---------------------------------------------
	// Check ufo collision with enemy explosions  
	// ---------------------------------------------

	Explosion* expls = ((ExplHandler*)handlers->explHander)->getExpls();

	for (int i = 0; i <= ((ExplHandler*)handlers->explHander)->getLastActive(); i++){
		if (expls[i].isValid()){
			if (expls[i].firedByEnemy() && expls[i].inRadius(&collisionArea)){
				applyDamage(expls[i].getDamage());
			}
		}
	}
}

// Resolve collisions
void UFO::resolveCollision(float deltaTime, Handlers* handlers){
	locX = nextX;
	locY = nextY;

	// Fix areas 
	collisionArea.setLocation(locX - originX, locY - originY);
	collisionArea.setSize(width, height);

	abductRayArea.setLocation(locX - (rayWidth / 2.0f), locY);
	abductRayArea.setSize(rayWidth, rayHeight);

	
	// Update weapons
	if (usingWeapon1 && uweapon1 != NULL){
		// Update weapon 
		if (lookingRight)
			uweapon1->update(deltaTime,locX,locY-(height*.5f));
		else 
			uweapon1->update(deltaTime,locX,locY-(height*.5f));

		// Set facing direction from weapon 
		lookingRight = uweapon1->getFacingDirecton();
	}
	else if (!usingWeapon1 && uweapon2 != NULL){
		// Update weapon 
		if (lookingRight)
			uweapon2->update(deltaTime, locX,locY-(height*.5f));
		else 
			uweapon2->update(deltaTime, locX,locY-(height*.5f));

		// Set facing direction from weapon 
		lookingRight = uweapon2->getFacingDirecton();
	}
}

// Update ufo input
void UFO::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	// Check Movement controls 
	if (mKeyH->keyDown(KEY_D)){
		direcX = 1.0f;
		if (uweapon1 == NULL && uweapon2 == NULL) 
			lookingRight = true;
	}
	else if (mKeyH->keyDown(KEY_A)){
		direcX = -1.0f;
		if (uweapon1 == NULL && uweapon2 == NULL)
			lookingRight = false;
	}
	else 
		direcX = 0.0f;

	if (mKeyH->keyDown(KEY_W))
		direcY = -1.0f;
	else if (mKeyH->keyDown(KEY_S))
		direcY = 1.0f;
	else 
		direcY = 0.0f;

	// Check fro abduction ray press
	if (mKeyH->keyPressed(KEY_E) && ((rayOn) || (!rayOn && energy > 0.0f))){
		rayOn = !rayOn;
		if(rayOn){
			((SoundHandler*)handlers->soundHandler)->startMusic(SE_ABDUCT);
		} else {
			((SoundHandler*)handlers->soundHandler)->stopMusic();
		}
	}
		

	// Switch weapons 
	if (uweapon1 != NULL && uweapon2 != NULL && mKeyH->keyPressed(KEY_F))
		usingWeapon1 = !usingWeapon1;

	// Update player weapon
	if (usingWeapon1 && uweapon1 != NULL)
		uweapon1->updateInput(mKeyH, mMouseH, handlers);
	else if (!usingWeapon1 && uweapon2 != NULL)
		uweapon2->updateInput(mKeyH, mMouseH, handlers);
}

// Draw UFO
void UFO::draw(GLHandler* mgl, PlayerAtlas* mAtlas, bool inUFO){
	
	// Draw weapon
	if (usingWeapon1 && uweapon1)
		uweapon1->draw(mgl, mAtlas);
	else if (!usingWeapon1 && uweapon2)
		uweapon2->draw(mgl, mAtlas);

	// Set damage color
	if (chitTime > 0.0f)
		mgl->setFlatColor(1.0f, 0.0f, 0.0f, 1.0f);
	if (lookingRight){
		if (inUFO)
			mAtlas->draw(mgl, UFO_BEAR_FRAME, locX,locY,1.0f,0,originX, originY);
		else 
			mAtlas->draw(mgl, UFO_FRAME, locX,locY,1.0f,0,originX, originY);
	}
	else {
		glCullFace(GL_FRONT);
		if (inUFO)
			mAtlas->drawScale2(mgl, UFO_BEAR_FRAME, locX,locY,-1.0f,1.0f,0,originX, originY);
		else 
			mAtlas->drawScale2(mgl, UFO_FRAME, locX,locY,-1.0f,1.0f,0,originX, originY);
		glCullFace(GL_BACK);
	}
	mgl->setFlatColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Draw UFO lights
void UFO::drawLights(GLHandler* mgl, PlayerAtlas* mAtlas, bool inUFO){
	if (inUFO){
		// Draw abduction ray 
		if (rayOn){
			float y;
			for (int i = 0; i < rayCircleCount; i++){
				// Determine y offset for each ray circle
				y = rayOffset + (i * rayOffsetMax);

				// Fade out circles on top and bottom 
				if (y < 100.0f) 
					mgl->setFlatColor(1.0f,1.0f,1.0f,y/100.0f);
				else if (y + rayCircleHeight > rayHeight - 100.0f)
					mgl->setFlatColor(1.0f,1.0f,1.0f,(rayHeight - (y + rayCircleHeight))/100.0f);
				else 
					mgl->setFlatColor(1.0f,1.0f,1.0f,1.0f);
		
				// Draw ray 
				mAtlas->draw(mgl, PI_UFO_RAY, locX, locY + y,
					rayScaleMin + ((y/rayHeight) * (rayScaleMax - rayScaleMin)),
					1.0f, rayWidth/2.0f, 0.0f);
			}
		}
	}
}

// Apply damage to the ship 
void UFO::applyDamage(float damage){
	if (invincible) return;

	chitTime = hitTime;

	// If shields are remaining, 
	if (shield > 0.0f){
		shield -= damage;
		cTimeTillCharge = timeTillCharge;
		if (shield < 0.0f)
			shield = 0.0f;
	}
	else {
		cTimeTillCharge = timeTillCharge;
		armor -= damage;
		if (armor < 0.0f)
			armor = 0.0f;
	}
}

// Refil armor to capacity
void UFO::replinishArmor(){
	armor = maxArmor;
}

// Returns true if ufo is alive 
bool UFO::alive(){
	return armor > 0.0f;
}

// Get ammo string for current weapon
std::string UFO::getAmmoString(){
	if (usingWeapon1 && uweapon1 != NULL){
		return uweapon1->getAmmoString();
	}
	else if (!usingWeapon1 && uweapon2 != NULL){
		return uweapon2->getAmmoString();
	}

	return std::string("0/0");
}
