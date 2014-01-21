#include "Player.h"


Player::Player(){
	width = 40.0f;
	height = 50.0f;

	locX = 0.0f;
	locY = 0.0f;

	originX = 20.0f;
	originY = 50.0f;

	movementSpeed = 400.0f;
}
Player::~Player(){}

// Getters and setters
void Player::setLocation(float x, float y){
	locX = x;
	locY = y;
}
float Player::getX(){return locX;}
float Player::getY(){return locY;}

// initialize level
void Player::init(float screen_width, float screen_height){
	locX = screen_width * .5f;
	locY = screen_height *.1f;
}

// Load level (use for textures)
void Player::load(){
	sprite.setup(width, height, string("player.png"));
	sprite.setOrigin(originX, originY);
}

// Update input
void Player::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	if (mKeyH->keyDown(KEY_A))
		direcX = -1.0f;
	else if (mKeyH->keyDown(KEY_D))
		direcX = 1.0f;
	else 
		direcX = 0.0f;

	if (mMouseH->isLeftDown())
		cout << "Mouse: " << mMouseH->getX() << ", " << mMouseH->getY() << "\n";
}

// Update level state
void Player::update(float deltaTime){
	nextX = locX;
	nextY = locY;

	nextX += direcX * deltaTime * movementSpeed;
	nextY += deltaTime * 200.0f;
}

// Check collisions 
void Player::checkCollision(Ground* ground){
	// Fix player collision variables 
	vertA.setLocation(nextX, nextY);
	vertB.setLocation(nextX, nextY - height);
	horA.setLocation(nextX - (width/2.0f), nextY - 20.0f);
	horB.setLocation(nextX + (width/2.0f), nextY - 20.0f);

	// Point used during collision detection 
	Point p;

	// ----------------------------------
	// Check player collision with ground 
	// ----------------------------------
	
	// These two checks have to be done in separate loops or 
	// they will mess up eachother. Since the ground line 
	// segments are found in order, there will usually 
	// be a ground collision when there is a hill one. And
	// if the hill comes after, the collision will not detect it. 

	// Steep hill check 
	for (int i = 0; i < ground->getPointCount()-1; i++){
		if (checkSegSeg(horA, horB, ground->getPoint(i), ground->getPoint(i+1), &p)){
			nextX = locX;
			nextY = locY;
			return;
		}
	}

	// Normal ground check 
	for (int i = 0; i < ground->getPointCount()-1; i++){
		if (checkSegSeg(vertA, vertB, ground->getPoint(i), ground->getPoint(i+1), &p)){
			nextX = p.getX();
			nextY = p.getY();
			return;
		}
	}
}

// Resolve any collisions found 
void Player::resolveCollision(){
	locX = nextX;
	locY = nextY;

	sprite.setPosition(locX, locY);
}

// Draw level 
void Player::draw(GLHandler* mgl){
	sprite.draw(*mgl);
}
