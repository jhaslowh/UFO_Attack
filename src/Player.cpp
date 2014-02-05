#include "Player.h"


Player::Player(){
	// Location And Sizing 
	locX = 0.0f;
	locY = 0.0f;
	originX = 25.0f;
	originY = 50.0f;
	width = 50.0f;
	height = 50.0f;

	// Physics 
	movementSpeed = 400.0f;
	jumpt = 0.0f;
	jumpTime = .35f;
	yo = 0.0f;
	airT = 0.0f;
	minAirtForInAir = .02f;

	// States 
    jumping = false;
	inAir = false;
	inUFO = true;

	// Health 
	health = 100.0f;
	maxHealth = 100.0f;

	// Animation values 
	lookingRight = true;
	runFrameCount = 12;
	runFrame = 0;
	runFrameTime = .02f;
	cRunFrameTime = 0;

	animationState = PLAYERS_RUN;
	idleFrame = PLAYER_RUN_FRAME8;
	jumpFrame = PLAYER_RUN_FRAME9;

	// Collision Values 
	collRec.setLocation(0.0f,0.0f);
	collRec.setSize(50.0f,50.0f);
	waistHeight = 35.0f;
	depthForDepthCheck = 20.0f;

	
	cameraOffsetY = 0.0f;
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
// Set max health
void Player::setMaxHealth(float value){maxHealth = value;}
// Get max health
float Player::getMaxHealth(){ return maxHealth;}
// Set health
void Player::setHealth(float value){health = value;}
// Get health
float Player::getHealth(){return health;}

// initialize level
void Player::init(float screen_width, float screen_height){
	ufo->init();

	cameraOffsetY = screen_height * .25f;
}

// Load level (use for textures)
void Player::load(){
	playerAtlas.load();

	ufo->load();
}

// Unload textures
void Player::unload(){
	playerAtlas.unload();
}

// Update level state
void Player::update(float deltaTime, Handlers* handlers){
	if (alive()){
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


			// Update Run Animation
			cRunFrameTime += deltaTime;
			if (cRunFrameTime >= runFrameTime){
				cRunFrameTime = 0.0f;
				runFrame++;
				if (runFrame >= runFrameCount)
					runFrame = 0;
			}
		}
	}
}

// Check collisions 
void Player::checkCollision(Handlers* handlers){
	if (alive()){
		if (inUFO){
			ufo->checkCollision(handlers);
		}
		else {
			// Point used during collision detection 
			Point p;
			Point* itr;

			// ----------------------------------------
			// Check player collision with level bounds
			// ----------------------------------------

			// Nasty code block....

			if (nextX - (collRec.getWidth()/2.0f) < ((LevelProperties*)(handlers->levelProps))->getLevelLeft())
				nextX = ((LevelProperties*)(handlers->levelProps))->getLevelLeft() + (collRec.getWidth()/2.0f);
			if (nextX + (collRec.getWidth()/2.0f) > ((LevelProperties*)(handlers->levelProps))->getLevelRight())
				nextX = ((LevelProperties*)(handlers->levelProps))->getLevelRight() - (collRec.getWidth()/2.0f);

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
			horA.setLocation(nextX - (collRec.getWidth()/2.0f), nextY - waistHeight);
			horB.setLocation(nextX + (collRec.getWidth()/2.0f), nextY - waistHeight);

			// Steep hill check:
			// This check stops the player from walking up steep surfaces 
			itr = handlers->ground->getPoints();
			while (itr->next != NULL){
				if (checkSegSeg(horA, horB, *itr, *(itr->next), &p)){
					nextX = locX;
					hitWall();
					break;
				}
				itr = itr->next;
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
				itr = handlers->ground->getPoints();
				while (itr->next != NULL){
					if (checkSegSeg(vertA, vertB, *itr, *(itr->next), &p)){
						nextX = p.getX();
						nextY = p.getY();
						hitGround();
						break;
					}
					itr = itr->next;
				}
			}

			// Setup below body vertical line segment
			vertBotA.setLocation(nextX, nextY);
			vertBotB.setLocation(nextX, nextY + depthForDepthCheck);

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
				itr = handlers->ground->getPoints();
				while (itr->next != NULL){
					if (checkSegSeg(vertBotA, vertBotB, *itr, *(itr->next), &p)){
						nextX = p.getX();
						nextY = p.getY();
						hitGround();
						break;
					}
					itr = itr->next;
				}
			}

			// -----------------------------------
			// Check player collision with scenery
			// -----------------------------------
			// Fix collision rectangles for next steps
			setCollRec(&collRecX, nextX, locY);
			setCollRec(&collRecY, locX, nextY);
			setCollRec(&collRecXY, nextX, nextY);

			// Variables for use with collision
			SceneryObject* sitr = ((SceneryHandler*)handlers->sceneryHandler)->getHead();
			bool cornerFound = false;
			bool xpass = true;
			bool ypass = true;

			// Check collision with all scenery 
			while (sitr != NULL){
				// If scenery object collides 
				if (sitr->getCollides()){
					// Check x collision 
					if (xpass){
						if (checkRecRec(&collRecX, sitr->getCollisionRec())){
							// Tell scenery object of the collision
							sitr->onCollide();

							// Stop player if object is physical
							if (sitr->getStopPlayer()) 
								xpass = false;
						}
					}
			
					// Check y collision
					if (ypass){
						if (checkRecRec(&collRecY, sitr->getCollisionRec())){
							// Tell scenery object of the collision
							sitr->onCollide();

							// Stop player if object is physical
							if (sitr->getStopPlayer()) {
								// Makes it so player does not bounce off ground
								locY = sitr->getCollisionRec()->top() - 1.0f;
								hitGround();
								ypass = false;
							}
						}
					}
			
					// Double check 
					// This will stop player from getting stuck in corners 
					if (xpass && ypass){
						if (checkRecRec(&collRecXY, sitr->getCollisionRec())){
							// Tell scenery object of the collision
							sitr->onCollide();

							// Stop player if object is physical
							if (sitr->getStopPlayer()) 
								cornerFound = true;
						}
					}
				}

				sitr = sitr->getNext();
			}
		
			// Corner check 
			if (cornerFound  && xpass && ypass){
				hitGround();
				ypass = false;
				xpass = false;
			}

			// Fix position if collision found 
			if (!xpass)
				nextX = locX;
			if (!ypass)
				nextY = locY;

			// ---------------------------------------------
			// Check player collision with enemy projectiles  
			// ---------------------------------------------
			// Fix collision rectangles for next steps
			setCollRec(&collRecX, nextX, locY);
			setCollRec(&collRecY, locX, nextY);
			setCollRec(&collRecXY, nextX, nextY);

			// TODO 
		}
	}
}

// Resolve any collisions found 
void Player::resolveCollision(Handlers* handlers){
	if (alive()){
		if (inUFO){
			ufo->resolveCollision(handlers);

			// Set camera location 
			((Camera2D*)(handlers->camera))->setTarget(ufo->getX(), ufo->getY() + cameraOffsetY);
		}
		else {
			locX = nextX;
			locY = nextY;

			// Set camera location 
			((Camera2D*)(handlers->camera))->setTarget(locX, locY - cameraOffsetY);

			// Set player animation state 
			if (inAir)
				animationState = PLAYERS_AIR;
			else if (direcX != 0.0f)
				animationState = PLAYERS_RUN;
			else 
				animationState = PLAYERS_IDLE;
		}
	}
}

// Update input
void Player::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	if (alive()){
		// Update ufo input
		if (inUFO){
			ufo->updateInput(mKeyH, mMouseH);
		}
		// Update player input 
		else {
			// Check if player is trying to move
			if (mKeyH->keyDown(KEY_A)){
				direcX = -1.0f;
				lookingRight = false;
			}
			else if (mKeyH->keyDown(KEY_D)){
				direcX = 1.0f;
				lookingRight = true;
			}
			else 
				direcX = 0.0f;

			// Check if player is trying to jump 
			if (mKeyH->keyDown(KEY_SPACE) && !jumping && !inAir){
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
		if (mKeyH->keyReleased(KEY_Q)){
			inUFO = !inUFO;

			if (!inUFO)
				dropFromShip();
		}
	}
}

// Draw level 
void Player::draw(GLHandler* mgl, GameAtlas* mGame){
	playerAtlas.bindTexture(mgl);
	playerAtlas.bindBuffers(mgl);

	ufo->draw(mgl, &playerAtlas);
	
	if (!inUFO){

		// Draw player
		// Player running 
		if (animationState == PLAYERS_RUN){
			if (lookingRight)
				playerAtlas.draw(mgl, PLAYER_RUN_FRAME0 + runFrame,
					locX,locY,1.0f,0.0f,originX,originY);
			else {
				glCullFace(GL_FRONT);
				playerAtlas.drawScale2(mgl, PLAYER_RUN_FRAME0 + runFrame,
					locX,locY,-1.0f,1.0f,0.0f,originX,originY);
				glCullFace(GL_BACK);
			}
		}
		// Player idle 
		else if (animationState == PLAYERS_IDLE){
			if (lookingRight)
				playerAtlas.draw(mgl, idleFrame,
					locX,locY,1.0f,0.0f,originX,originY);
			else {
				glCullFace(GL_FRONT);
				playerAtlas.drawScale2(mgl, idleFrame,
					locX,locY,-1.0f,1.0f,0.0f,originX,originY);
				glCullFace(GL_BACK);
			}
		}
		// Player jumping or falling 
		else if (animationState == PLAYERS_AIR){
			if (lookingRight)
				playerAtlas.draw(mgl, jumpFrame,
					locX,locY,1.0f,0.0f,originX,originY);
			else {
				glCullFace(GL_FRONT);
				playerAtlas.drawScale2(mgl, jumpFrame,
					locX,locY,-1.0f,1.0f,0.0f,originX,originY);
				glCullFace(GL_BACK);
			}
		}
	}
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
	// Nothing to do yet
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


// Set health back to max health
void Player::replinishHealth(){
	health = maxHealth;
}

// Check if player is alive 
bool Player::alive(){
	return health > 0.0f && ufo->alive();
}

// Apply damage to health
void Player::applyDamage(float damage){
	health -= damage;
	if (health < 0.0f)
		health = 0.0f;
}

// Set the given collision rectangle to the given location
void Player::setCollRec(Rec* r, float x, float y){
	r->copy(&collRec);

	r->setX(x - originX + r->getX());
	r->setY(y - originY + r->getY());
}