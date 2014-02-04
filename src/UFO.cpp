#include "UFO.h"


UFO::UFO(){
	locX = 0.0f;
	locY = 0.0f;
	originX = 50.0f;
	originY = 50.0f;
	speed = 300.0f;
	minDistFromGround = 200.0f;

	armor = 100.0f;
	maxArmor = 100.0f;
	shield = 100.0f;
	maxShield = 100.0f;
	shieldChargeRate = 100.0f; // Charge per second 
	timeTillCharge = .25f;
	cTimeTillCharge = 0.0f;
}
UFO::~UFO(){}

// Set location of the player
void UFO::setLocation(float x, float y){
	locX = x;
	locY = y;
}
float UFO::getX(){return locX;}
float UFO::getY(){return locY;}
void UFO::setMaxArmor(float value){maxArmor = value;}
float UFO::getMaxArmor(){return maxArmor;}
void UFO::setArmor(float value){armor = value;}
float UFO::getArmor(){return armor;}
void UFO::setMaxShield(float value){maxShield = value;}
float UFO::getMaxShield(){return maxShield;}
void UFO::setShield(float value){shield = value;}
float UFO::getShield(){return shield;}

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
}

// Check collision 
void UFO::checkCollision(Handlers* handlers){
	// Make sure UFO cannot leave level on left or right side

	if (nextX - 50.0f < ((LevelProperties*)(handlers->levelProps))->getLevelLeft())
		nextX = ((LevelProperties*)(handlers->levelProps))->getLevelLeft() + 50.0f;
	if (nextX + 50.0f > ((LevelProperties*)(handlers->levelProps))->getLevelRight())
		nextX = ((LevelProperties*)(handlers->levelProps))->getLevelRight() - 50.0f;

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
}

// Update ufo input
void UFO::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Check Movement controls 
	if (mKeyH->keyDown(KEY_D))
		direcX = 1.0f;
	else if (mKeyH->keyDown(KEY_A))
		direcX = -1.0f;
	else 
		direcX = 0.0f;

	if (mKeyH->keyDown(KEY_W))
		direcY = -1.0f;
	else if (mKeyH->keyDown(KEY_S))
		direcY = 1.0f;
	else 
		direcY = 0.0f;
}

// Draw UFO
void UFO::draw(GLHandler* mgl, PlayerAtlas* mGame){
	mGame->draw(mgl, UFO_FRAME, locX,locY,1.0f,0,originX, originY);
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
	return armor <= 0.0f;
}