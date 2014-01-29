#include "UFO.h"


UFO::UFO(){
	locX = 0.0f;
	locY = 0.0f;
	originX = 50.0f;
	originY = 50.0f;
	speed = 300.0f;
	minDistFromGround = 200.0f;
}
UFO::~UFO(){}

// Set location of the player
void UFO::setLocation(float x, float y){
	locX = x;
	locY = y;
}
float UFO::getX(){return locX;}
float UFO::getY(){return locY;}

// Init 
void UFO::init(){

}
	
// Load images
void UFO::load(){

}

// Update UFO
void UFO::update(float deltaTime, Handlers* handlers){
	nextX = locX;
	nextY = locY;

	nextX += direcX * deltaTime * speed;
	nextY += direcY * deltaTime * speed;
}

// Check collision 
void UFO::checkCollision(Handlers* handlers){
	// Make sure UFO cannot leave level on left or right side

	// TODO 

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
void UFO::draw(GLHandler* mgl, GameAtlas* mGame){
	mGame->draw(mgl, GI_UFO, locX,locY,1.0f,0,originX, originY);
}