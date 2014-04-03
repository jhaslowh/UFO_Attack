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

	armor = 100.0f;
	maxArmor = 100.0f;
	shield = 100.0f;
	maxShield = 100.0f;
	shieldChargeRate = 100.0f; // Charge per second 
	timeTillCharge = 5.0f;
	cTimeTillCharge = 0.0f;

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
}
UFO::~UFO(){}

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
float UFO::getCenterY(){return locY - (height * .5);}
void UFO::setMaxArmor(float value){maxArmor = value;}
float UFO::getMaxArmor(){return maxArmor;}
void UFO::setArmor(float value){armor = value;}
float UFO::getArmor(){return armor;}
void UFO::setMaxShield(float value){maxShield = value;}
float UFO::getMaxShield(){return maxShield;}
void UFO::setShield(float value){shield = value;}
float UFO::getShield(){return shield;}

// Check if abduction ray is turned on 
bool UFO::isRayOn(){return rayOn;}
// Get the area for collision detection with ship
Rec* UFO::getUFOArea(){return &collisionArea;}
// Get the area for collision detection with abduction ray
Rec* UFO::getAbductArea(){return &abductRayArea;}

// Init 
void UFO::init(){}
	
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

	// Update abduct ray
	rayOffset -= deltaTime * rayMoveSpeed;
	if (rayOffset <= 0.0f)
		rayOffset = rayOffsetMax;
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
	while (itr->next != NULL){
		if (checkSegSeg(vertA, vertB, *itr, *(itr->next), &p)){
			nextX = p.getX();
			nextY = p.getY() - minDistFromGround;
			break;
		}
		itr = itr->next;
	}
}

// Resolve collisions
void UFO::resolveCollision(Handlers* handlers){
	locX = nextX;
	locY = nextY;

	// Fix areas 
	collisionArea.setLocation(locX - originX, locY - originY);
	collisionArea.setSize(width, height);

	abductRayArea.setLocation(locX - (rayWidth / 2.0f), locY);
	abductRayArea.setSize(rayWidth, rayHeight);
}

// Update ufo input
void UFO::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Check Movement controls 
	if (mKeyH->keyDown(KEY_D)){
		direcX = 1.0f;
		lookingRight = true;
	}
	else if (mKeyH->keyDown(KEY_A)){
		direcX = -1.0f;
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
	if (mKeyH->keyPressed(KEY_E))
		rayOn = !rayOn;
}

// Draw UFO
void UFO::draw(GLHandler* mgl, PlayerAtlas* mAtlas, bool inUFO){
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