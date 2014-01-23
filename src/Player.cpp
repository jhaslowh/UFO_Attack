#include "Player.h"


Player::Player(){
	// Size
	width = 40.0f;
	height = 50.0f;

	// Location 
	locX = 0.0f;
	locY = 0.0f;

	// Drawing 
	originX = 20.0f;
	originY = 50.0f;

	// Physics 
	movementSpeed = 400.0f;
	jumpt = 0.0f;
	jumpTime = .35f;
	yo = 0.0f;
	airT = 0.0f;
	minAirtForInAir = .02f;

	// States 
	alive = true;
    jumping = false;
	inAir = false;
	inUFO = true;

	ufo = new UFO();
}
Player::~Player(){
	delete ufo;
}

// Getters and setters
void Player::setLocation(float x, float y){
	locX = x;
	locY = y;
}
float Player::getX(){return locX;}
float Player::getY(){return locY;}

// initialize level
void Player::init(){
	ufo->init();
}

// Load level (use for textures)
void Player::load(){
	sprite.setup(width, height, string("player.png"));
	sprite.setOrigin(originX, originY);

	ufo->load();
}

// Update level state
void Player::update(float deltaTime, Handlers* handlers){
	// If in ufo, update ufo state
	if (inUFO){
		ufo->update(deltaTime, handlers);
	}
	// Update player state if not in ufo 
	else {
		nextX = locX;
		nextY = locY;

		// Update Movement
		nextX += direcX * deltaTime * movementSpeed;

		// Gravity 
		if (!jumping){
			// Update time in air and apply gravity 
			airT += deltaTime;
			nextY = yo + (.5f * GRAVITY * (airT * airT));

			// Check if in air
			if (airT > minAirtForInAir)
				inAir = true;
		}
		// Jumping
		else {
			// This equation must be used to get a smooth jump curve
			nextY = yo 							// Starting loc 
				- (.5f * GRAVITY * (jumpTime * jumpTime)) // Add max jump
				+ (.5f * GRAVITY * (jumpt * jumpt));		// Minus curve value 
			jumpt -= deltaTime;
        
			if (jumpt < 0){
				stopJump();
			}
		}
	}
}

// Check collisions 
void Player::checkCollision(Handlers* handlers){
	if (inUFO){
		ufo->checkCollision(handlers);
	}
	else {
		// Point used during collision detection 
		Point p;

		// ----------------------------------
		// Check player collision with ground 
		// ----------------------------------
	
		// These three checks have to be done in separate loops or 
		// they will mess up eachother. Since the ground line 
		// segments are checked in order, there will usually 
		// be a ground collision before there is also a hill one. And
		// if the hill comes after the wall check, the hill 
		// collision will not be detected. 
	
		// Setup horozontal line segment 
		horA.setLocation(nextX - (width/2.0f), nextY - 32.0f);
		horB.setLocation(nextX + (width/2.0f), nextY - 32.0f);

		// Steep hill check:
		// This check stops the player from walking up steep surfaces 
		for (int i = 0; i < handlers->ground->getPointCount()-1; i++){
			if (checkSegSeg(horA, horB, handlers->ground->getPoint(i), handlers->ground->getPoint(i+1), &p)){
				nextX = locX;
				hitWall();
				break;
			}
		}
	
		// Setup vertical line segment 
		vertA.setLocation(nextX, nextY);
		vertB.setLocation(nextX, nextY - height);

		// Normal ground check: 
		// This check stops the player from falling through the ground
		// 
		// We first must make sure the player is not jumping or the 
		// player will be stuck to the ground. 
		if (!jumping){
			for (int i = 0; i < handlers->ground->getPointCount()-1; i++){
				if (checkSegSeg(vertA, vertB, handlers->ground->getPoint(i), handlers->ground->getPoint(i+1), &p)){
					nextX = p.getX();
					nextY = p.getY();
					hitGround();
					break;
				}
			}
		}

		// Setup below body vertical line segment
		vertBotA.setLocation(nextX, nextY);
		vertBotB.setLocation(nextX, nextY + 20.0f);

		// Hill bounce check: 
		// This check stops the player from bouncing when moving down 
		// a hill. 
		// 
		// We first check the airT, because if we do not, this will
		// stap the player to the ground when falling from  a jump.
		//
		// We also must make sure the player is not jumping or the 
		// player will be stuck to the ground. And make sure inAir
		// is false so that player will not be snapped to the ground
		// when landing from a shallow jump. 
		if (airT < minAirtForInAir && !jumping && !inAir){
			for (int i = 0; i < handlers->ground->getPointCount()-1; i++){
				if (checkSegSeg(vertBotA, vertBotB, handlers->ground->getPoint(i), handlers->ground->getPoint(i+1), &p)){
					nextX = p.getX();
					nextY = p.getY();
					hitGround();
					break;
				}
			}
		}

		// -----------------------------------
		// Check player collision with scenery
		// -----------------------------------

		// TODO 

		// ---------------------------------------------
		// Check player collision with enemy projectiles  
		// ---------------------------------------------

		// TODO 
	}
}

// Resolve any collisions found 
void Player::resolveCollision(){
	if (inUFO){
		ufo->resolveCollision();
	}
	else {
		locX = nextX;
		locY = nextY;

		sprite.setPosition(locX, locY);
	}
}

// Update input
void Player::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Update ufo input
	if (inUFO){
		ufo->updateInput(mKeyH, mMouseH);
	}
	// Update player input 
	else {
		// Check if player is trying to move
		if (mKeyH->keyDown(KEY_A))
			direcX = -1.0f;
		else if (mKeyH->keyDown(KEY_D))
			direcX = 1.0f;
		else 
			direcX = 0.0f;

		// Check if player is trying to jump 
		if (mKeyH->keyDown(KEY_W) && !jumping && !inAir){
			// Set up physics 
			jumpt = jumpTime;
			airT = 0;
			yo = locY;
          
			// Set states 
			jumping = true;
			inAir = true;
		}
	}

	// Switch from ufo to on foot 
	if (mKeyH->keyPressed(KEY_Q)){
		inUFO = !inUFO;

		if (!inUFO)
			dropFromShip();
	}
}

// Draw level 
void Player::draw(GLHandler* mgl, GameAtlas* mGame){
	ufo->draw(mgl, mGame);
	
	if (!inUFO)
		sprite.draw(*mgl);
}

// Stop player if they are jumping
void Player::stopJump(){
	airT = 0;
	yo = locY;
	jumping = false;
}

// Call when the player hits the ground 
void Player::hitGround(){
	airT = 0;
	yo = nextY;
	inAir = false;
	jumping = false;
}

// Call when the player hits a wall
void Player::hitWall(){

}

// Call when the player hits the ceiling 
void Player::hitCeiling(){
	airT = 0;
	yo = nextY;
	inAir = false; 
	jumping = false;
}

// Called when the player is dropped from the ship
void Player::dropFromShip(){
	locX = ufo->getX();
	locY = ufo->getY() + height;
	nextX = locX;
    nextY = locY;
	airT = 0;
	yo = nextY;
	inAir = true; 
	jumping = false;
}