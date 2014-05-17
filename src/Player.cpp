#include "Player.h"


Player::Player(SaveData* savedata){
	// Location And Sizing 
	locX = 0.0f;
	locY = 0.0f;
	nextX = 0.0f;
	nextY = 0.0f;
	direcX = 0.0f;
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
	animalAbductCount = 0;
	humanAbductCount = 0;
	invincible = false;
	
	// Interact button 
	interact = false;

	// Animation values 
	lookingRight = true;
	runFrameCount = 12;
	runFrame = 0;
	runFrameTime = .02f;
	cRunFrameTime = 0;

	animationState = PLAYERS_RUN;
	idleFrame = 8;
	jumpFrame = 9;
	
	// Arm
	armRotation = 0.0f;
	armOriginX = 25.0f;
	armOriginY = 25.0f;

	// Collision Values 
	collRec.setLocation(10.0f,5.0f);
	collRec.setSize(30.0f,45.0f);
	waistHeight = 35.0f;
	depthForDepthCheck = 20.0f;

	// Hud Scales
	hudHealthScale = 0.0f;
	hudHealthMaxScale = 1.0f;
	hudArmorScale = 0.0f;
	hudArmorMaxScale = 1.5f;
	hudShieldScale = 0.0f;
	hudShieldMaxScale = 1.6f;
	hudShieldScaleY = 2.0f;

	// Hud Locations 
	hudArmorLocX = 0.0f;
	hudArmorLocY = 0.0f;
	hudShieldLocX = 0.0f;
	hudShieldLocY = 0.0f;
	hudHealthLocX = 0.0f;
	hudHealthLocY = 0.0f;

	// Score values 
	scoreTextSize = 21.0f;
	scoreTextOffsetX = 22.0f;
	scoreTextOffsetY = 3.0f;
	locScoreAnimalX = 180.0f;
	locScoreAnimalY = 5.0f;
	locScoreHumanX = 240.0f;
	locScoreHumanY = 5.0f;

	// Energy values 
	hudEnergyScale = 1.0f;
	hudEnergyMaxScale = 1.0f;
	hudEnergyLocX = 0.0f;
	hudEnergyLocY = 0.0f;

	// Enemies Left
	elText = "Enemies Left";
	elTextSize = 20.0f;
	elTextX = 0.0f;
	elTextY = 3.0f;
	elBarX = 0;
	elBarY = 8.0f + elTextSize;
	elScale = 1.0f;

	// Hud Colors
	hudHealthColor[0] = 1.0f;
	hudHealthColor[1] = 0.27f;
	hudHealthColor[2] = 0.27f;
	hudHealthColor[3] = 1.0f;

	hudShieldColor[0] = 0.27f;
	hudShieldColor[1] = 0.89f;
	hudShieldColor[2] = 1.0f;
	hudShieldColor[3] = 1.0f;

	hudArmorColor[0] = 1.0f;
	hudArmorColor[1] = 0.84f;
	hudArmorColor[2] = 0.27f;
	hudArmorColor[3] = 1.0f;

	hudBlack[0] = 0.0f;
	hudBlack[1] = 0.0f;
	hudBlack[2] = 0.0f;
	hudBlack[3] = 0.5f;

	hudEnergyColor[0] = 0.0f;
	hudEnergyColor[1] = 1.0f;
	hudEnergyColor[2] = 0.0f;
	hudEnergyColor[3] = 1.0f;
	
	camera = NULL;
	cameraEdge = 300.0f;
	cameraEdgeTop = 140.0f;
	ufo = NULL;

	// Hit recently
	hitTime = .05f;
	chitTime = 0.0f;

	// Arm offsets 
	armOffsetsR[0] = 24;	armOffsetsR[1] = 25;
	armOffsetsR[2] = 24;	armOffsetsR[3] = 27;
	armOffsetsR[4] = 24;	armOffsetsR[5] = 25;
	armOffsetsR[6] = 24;	armOffsetsR[7] = 23;
	armOffsetsR[8] = 24;	armOffsetsR[9] = 22;
	armOffsetsR[10] = 24;	armOffsetsR[11] = 22;
	armOffsetsR[12] = 24;	armOffsetsR[13] = 25;
	armOffsetsR[14] = 24;	armOffsetsR[15] = 27;
	armOffsetsR[16] = 24;	armOffsetsR[17] = 25;
	armOffsetsR[18] = 24;	armOffsetsR[19] = 23;
	armOffsetsR[20] = 24;	armOffsetsR[21] = 22;
	armOffsetsR[22] = 24;	armOffsetsR[23] = 23;

	// Load weapon based off savedata
	usingWeapon1 = true;
	weapon1 = NULL;
	weapon2 = NULL;
	if (savedata != NULL){
		// Load player weapon 1 from savedata 
		if (savedata->getPlayerWeapon1() == StoreItems::SID_PLAYER_WEAPON_LASER)
			weapon1 = (Weapon*)new PlayerLaserGun();
		else if (savedata->getPlayerWeapon1() == StoreItems::SID_PLAYER_WEAPON_SHOTGUN)
			weapon1 = (Weapon*)new PlayerShotgun();
		else if (savedata->getPlayerWeapon1() == StoreItems::SID_PLAYER_WEAPON_SMG)
			weapon1 = (Weapon*)new PlayerSMG();

		// Load player weapon 2 from savedata 
		if (savedata->getPlayerWeapon2() == StoreItems::SID_PLAYER_WEAPON_LASER)
			weapon2 = (Weapon*)new PlayerLaserGun();
		else if (savedata->getPlayerWeapon2() == StoreItems::SID_PLAYER_WEAPON_SHOTGUN)
			weapon2 = (Weapon*)new PlayerShotgun();
		else if (savedata->getPlayerWeapon2() == StoreItems::SID_PLAYER_WEAPON_SMG)
			weapon2 = (Weapon*)new PlayerSMG();
	}
}
Player::~Player(){
	delete ufo;
	ufo = NULL;
	delete weapon1;
	weapon1 = NULL;
	delete weapon2;
	weapon2 = NULL;
}

// Getters and setters
void Player::setLocation(float x, float y){
	locX = x;
	locY = y;
}
float Player::getX(){return locX;}
float Player::getY(){return locY;}
// Get x center loc
float Player::getCenterX(){return locX - originX + (width/2.0f);}
// Get y center loc
float Player::getCenterY(){return locY - originY + (height/2.0f);}
// Set max health
void Player::setMaxHealth(float value){maxHealth = value;}
// Get max health
float Player::getMaxHealth(){ return maxHealth;}
// Set health
void Player::setHealth(float value){health = value;}
// Get health
float Player::getHealth(){return health;}
// Set player arm rotation
void Player::setArmRotation(float value){armRotation = value;}

void Player::incrAnimalCount(int value){animalAbductCount += value; }
void Player::incrHumanCount(int value){humanAbductCount += value;}
int Player::getAnimalCount(){return animalAbductCount;}
int Player::getHumanCount(){return humanAbductCount;}
// Set enemy left bar size
void Player::setEnemyBarScale(float value){elScale = value;}
bool Player::getInteract(){return interact;}
Rec* Player::getCollRec(){return &collRecXY;}

// initialize level
void Player::init(float screen_width, float screen_height, SaveData* savedata){
	ufo = new UFO();
	ufo->init(savedata);

	// Set hud locations
	hudArmorLocX = 10.0f;
	hudArmorLocY = 10.0f;
	hudShieldLocX = 5.0f;
	hudShieldLocY = 5.0f;
	hudHealthLocX = 5.0f;
	hudHealthLocY = 30.0f;
	hudEnergyLocX = 5.0f;
	hudEnergyLocY = 45.0f;

	cameraRec.reset(cameraEdge, cameraEdgeTop, 
		screen_width - (cameraEdge*2.0f), screen_height - (cameraEdgeTop*2.0f));
	
	elBarX = (screen_width / 2.0f) - 50.0f;

	ammoLocX = screen_width - 25.0f;
	ammoLocY = 5.0f;
	ammoOffsetX = -5.0f;
	ammoOffsetY = 4.0f;

	if (screen_width < 600.0f){
		cameraEdge = screen_width * .3f;
	}
}

// Load level (use for textures)
void Player::load(GLHandler* mgl){
	playerAtlas.load();
	playerAtlas.setupFastBind(mgl,3);

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
			ufo->updateOnFoot(deltaTime, handlers);

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

				// Update current walk frame
				// Walking forward
				if ((lookingRight && nextX > locX) || (!lookingRight && nextX < locX)){
					runFrame++;
					if (runFrame >= runFrameCount)
						runFrame = 0;
				}
				// Walking backward
				else {
					runFrame--;
					if (runFrame < 0)
						runFrame = runFrameCount-1;
				}
			}

			// Update hit time
			if (chitTime > 0.0f){
				chitTime -= deltaTime;
				if (chitTime < 0.0f)
					chitTime = 0.0f;
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
			ufo->checkCollision(handlers);

			// Point used during collision detection 
			Point p;
			Point* itr;

			// ----------------------------------------
			// Check player collision with level bounds
			// ----------------------------------------

			// Nasty code block....

			if (nextX - (collRec.getWidth()/2.0f) < ((LevelProperties*)(handlers->levelProps))->getLevelLeft())
				nextX = ((LevelProperties*)(handlers->levelProps))->getLevelLeft() + (collRec.getWidth()/2.0f);
			else if (nextX + (collRec.getWidth()/2.0f) > ((LevelProperties*)(handlers->levelProps))->getLevelRight())
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
				// Check if player is close to point
				if ((*itr).getX() - 50 <= nextX && (*(itr->next)).getX() + 50 >= nextX){
					if (checkSegSeg(horA, horB, *itr, *(itr->next), &p)){
						nextX = locX;
						hitWall();
						break;
					}
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
					// Check if player is close to point
					if ((*itr).getX() <= nextX && (*(itr->next)).getX() >= nextX){
						if (checkSegSeg(vertA, vertB, *itr, *(itr->next), &p)){
							nextX = p.getX();
							nextY = p.getY();
							hitGround();
							break;
						}
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
					// Check if player is close to point
					if ((*itr).getX() <= nextX && (*(itr->next)).getX() >= nextX){
						if (checkSegSeg(vertBotA, vertBotB, *itr, *(itr->next), &p)){
							nextX = p.getX();
							nextY = p.getY();
							hitGround();
							break;
						}
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

								// Check if player is hitting ceiling or ground 
								if (nextY > locY){
									// Makes it so player does not bounce off ground.
									// Also make sure the object is below the player
									if (sitr->getCollisionRec()->top() > locY)
										locY = sitr->getCollisionRec()->top() - .2f;

									hitGround();
								}
								else 
									hitCeiling();

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
			setCollRec(&collRecXY, nextX, nextY);

			Projectile** projs = ((ProjectileHandler*)handlers->projHandler)->getProjList();
			Point projp;

			for (int i = 0; i <= ((ProjectileHandler*)handlers->projHandler)->getLastActive(); i++){
				// Null check / Alive check / shot by player 
				if (projs[i] != NULL && projs[i]->getAlive() && projs[i]->getFiredBy() == PFB_ENEMY){
					// Quick distance check 
					if (dist(nextX, nextY,projs[i]->getCurrentX(), projs[i]->getCurrentY()) <100){ 
						// Check for collision 
						if (checkRecSeg(&collRecXY, 
							projs[i]->getCurrentX(), projs[i]->getCurrentY(), 
							projs[i]->getPrevX(), projs[i]->getPrevY(), &projp)){

							// Tell projectile we had a player collision 
							projs[i]->collide(&projp, handlers, P_PLAYER_COLL);

							// Apply projectile damage to player
							if(!invincible){
								applyDamage(projs[i]->getDamage());
								((SoundHandler*)handlers->soundHandler)->playSoundEffect(SE_PLAYER_DAMAGED);
							}							
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
					if (expls[i].firedByEnemy() && expls[i].inRadius(&collRecXY)){
						if(!invincible){
							applyDamage(expls[i].getDamage());
						}
					}
				}
			}
		}
	}
}

// Resolve any collisions found 
void Player::update2(float deltaTime, Handlers* handlers){
	if (alive()){
		// Set camera reference if null 
		if (camera ==NULL)
			camera = (Camera2D*)(handlers->camera);

		if (inUFO){
			ufo->resolveCollision(deltaTime, handlers);

			// Set camera location 
			if (camera->toScreenX(ufo->getX()) < cameraRec.getX())
				camera->setTarget(ufo->getX() + (cameraRec.getWidth() * .5f), camera->getTargetY());
			if (camera->toScreenX(ufo->getX()) > cameraRec.getX() + cameraRec.getWidth())
				camera->setTarget(ufo->getX() - (cameraRec.getWidth() * .5f), camera->getTargetY());
			if (camera->toScreenY(ufo->getY()) < cameraRec.getY())
				camera->setTarget(camera->getTargetX(), ufo->getY() + (cameraRec.getHeight() * .5f));
			if (camera->toScreenY(ufo->getY()) > cameraRec.getHeight())
				camera->setTarget(camera->getTargetX(), ufo->getY() - 
				((cameraRec.getHeight() * .5f) - cameraRec.getY()));
		}
		else {
			ufo->resolveCollision(deltaTime, handlers);

			locX = nextX;
			locY = nextY;

			// Set camera location 
			if (camera->toScreenX(locX) < cameraRec.getX())
				camera->setTarget(locX + (cameraRec.getWidth() * .5f), camera->getTargetY());
			if (camera->toScreenX(locX) > cameraRec.getX() + cameraRec.getWidth())
				camera->setTarget(locX - (cameraRec.getWidth() * .5f), camera->getTargetY());
			if (camera->toScreenY(locY) < cameraRec.getY())
				camera->setTarget(camera->getTargetX(), locY + (cameraRec.getHeight() * .5f));
			if (camera->toScreenY(locY) > cameraRec.getY() + cameraRec.getHeight())
				camera->setTarget(camera->getTargetX(), locY - (cameraRec.getHeight() * .5f));

			// Set player animation state 
			if (inAir)
				animationState = PLAYERS_AIR;
			else if (direcX != 0.0f)
				animationState = PLAYERS_RUN;
			else 
				animationState = PLAYERS_IDLE;

			// Update weapons
			if (usingWeapon1 && weapon1 != NULL){
				// Update weapon 
				if (lookingRight){
					 weapon1->update(deltaTime, 
					  locX - originX + armOffsetsR[currentFrame*2],
						locY - originY + armOffsetsR[currentFrame*2 + 1]);
				}
				else {
					 weapon1->update(deltaTime, 
					  locX - originX + (width - armOffsetsR[currentFrame*2]),
						locY - originY + armOffsetsR[currentFrame*2 + 1]);
				}

				// Set facing direction from weapon 
				lookingRight = weapon1->getFacingDirecton();

				// Get weapon angle 
				armRotation = weapon1->getRotation();
			}
			else if (!usingWeapon1 && weapon2 != NULL){
				// Update weapon 
				if (lookingRight){
					 weapon2->update(deltaTime, 
					  locX - originX + armOffsetsR[currentFrame*2],
						locY - originY + armOffsetsR[currentFrame*2 + 1]);
				}
				else {
					 weapon2->update(deltaTime, 
					  locX - originX + (width - armOffsetsR[currentFrame*2]),
						locY - originY + armOffsetsR[currentFrame*2 + 1]);
				}

				// Set facing direction from weapon 
				lookingRight = weapon2->getFacingDirecton();

				// Get weapon angle 
				armRotation = weapon2->getRotation();
			}

			// Fix collision rec for other checks 
			setCollRec(&collRecXY, locX, locY);
		}
	}

	// Fix hud sizes 
	hudHealthScale = (health / maxHealth) * hudHealthMaxScale;
	hudArmorScale = (ufo->getArmor() / ufo->getMaxArmor()) * hudArmorMaxScale;
	hudShieldScale = (ufo->getShield() / ufo->getMaxShield()) * hudShieldMaxScale;
	hudEnergyScale = ufo->getEnergyPercent() * hudEnergyMaxScale;

	// Get current frame 
	if (animationState == PLAYERS_RUN)
		currentFrame = runFrame;
	else if (animationState == PLAYERS_IDLE)
		currentFrame = idleFrame;
	else if (animationState == PLAYERS_AIR)
		currentFrame = jumpFrame;
}

// Update input
void Player::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	SoundHandler* soundHand = (SoundHandler*)handlers->soundHandler;
	
	if (alive()){
		// Update ufo input
		if (inUFO){
			ufo->updateInput(mKeyH, mMouseH, handlers);
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
			if (mKeyH->keyPressed(KEY_SPACE) && !jumping && !inAir){
				// Set up physics 
				jumpt = jumpTime;
				airT = 0;
				yo = locY;
          
				// Set states 
				jumping = true;
				inAir = true;
			}

			// Check interact key
			interact = false;
			if (mKeyH->keyPressed(KEY_E))
				interact = true;

			// Switch weapons 
			if (weapon1 != NULL && weapon2 != NULL && mKeyH->keyPressed(KEY_F))
				usingWeapon1 = !usingWeapon1;

			// Update player weapon
			if (usingWeapon1 && weapon1 != NULL)
				weapon1->updateInput(mKeyH, mMouseH, handlers);
			else if (!usingWeapon1 && weapon2 != NULL)
				weapon2->updateInput(mKeyH, mMouseH, handlers);
		}

		// Switch from ufo to on foot 
		if (mKeyH->keyReleased(KEY_Q)){
			if (inUFO || (!inUFO && abs(locX - ufo->getCenterX()) < 100.0f)){
				
				if(inUFO){
					soundHand->playSoundEffect(SE_EXIT_UFO);
					soundHand->stopMusic();//stop beam sound
					dropFromShip();
					ufo->setRayOn(false);
				} else {
					soundHand->playSoundEffect(SE_ENTER_UFO);
				}

				inUFO = !inUFO;
			}
			else {
				soundHand->playSoundEffect(SE_UFO_ERROR);
			}
		}
	}
}

// Draw level 
void Player::draw(GLHandler* mgl){
	playerAtlas.bindBuffers(mgl);
	playerAtlas.bindTextureFast(mgl);

	ufo->draw(mgl, &playerAtlas, inUFO);
	
	if (!inUFO){
		// Draw player
		// Set damage color
		if (chitTime > 0.0f)
			mgl->setFlatColor(1.0f, 0.0f, 0.0f, 1.0f);
		if (lookingRight)
			playerAtlas.draw(mgl, PLAYER_RUN_FRAME0 + currentFrame,
				locX,locY,1.0f,0.0f,originX,originY);
		else {
			glCullFace(GL_FRONT);
			playerAtlas.drawScale2(mgl, PLAYER_RUN_FRAME0 + currentFrame,
				locX,locY,-1.0f,1.0f,0.0f,originX,originY);
			glCullFace(GL_BACK);
		}
		mgl->setFlatColor(1.0f, 1.0f, 1.0f, 1.0f);

		// Draw weapon
		if (usingWeapon1 && weapon1)
			weapon1->draw(mgl, &playerAtlas);
		else if (!usingWeapon1 && weapon2)
			weapon2->draw(mgl, &playerAtlas);
		
		// Set damage color
		if (chitTime > 0.0f)
			mgl->setFlatColor(1.0f, 0.0f, 0.0f, 1.0f);
		// Draw player arm 
		if (lookingRight){
			playerAtlas.draw(mgl, PI_PLAYER_ARM,
				locX-originX+armOffsetsR[currentFrame*2],
				locY-originY+armOffsetsR[currentFrame*2 + 1],
				1.0f,armRotation,armOriginX,armOriginY);
		}
		else {
			glCullFace(GL_FRONT);
			playerAtlas.drawScale2(mgl, PI_PLAYER_ARM,
				locX-originX+(width-armOffsetsR[currentFrame*2]),
				locY-originY+armOffsetsR[currentFrame*2 + 1],
				-1.0f,1.0f,armRotation,armOriginX,armOriginY);
			glCullFace(GL_BACK);
		}
		mgl->setFlatColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

// Draw player hud
void Player::drawHud(GLHandler* mgl){
	playerAtlas.bindTexture(mgl);
	playerAtlas.bindBuffers(mgl);

	// Drawbackdrops
	mgl->setFlatColor(hudBlack);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudHealthLocX, hudHealthLocY, hudHealthMaxScale, 1.0f);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudShieldLocX, hudShieldLocY, hudShieldMaxScale, hudShieldScaleY);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudArmorLocX, hudArmorLocY, hudArmorMaxScale, 1.0f);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudEnergyLocX, hudEnergyLocY, hudEnergyMaxScale, 1.0f);

	// Draw health 
	mgl->setFlatColor(hudHealthColor);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudHealthLocX, hudHealthLocY, hudHealthScale, 1.0f);
	// Draw shield
	mgl->setFlatColor(hudShieldColor);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudShieldLocX, hudShieldLocY, hudShieldScale, hudShieldScaleY);
	// Draw armor 
	mgl->setFlatColor(hudArmorColor);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudArmorLocX, hudArmorLocY, hudArmorScale, 1.0f);
	// Draw energy 
	mgl->setFlatColor(hudEnergyColor);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, hudEnergyLocX, hudEnergyLocY, hudEnergyScale, 1.0f);

	// Draw enemy left bar
	mgl->setFlatColor(hudBlack);
	playerAtlas.draw(mgl, PI_HEALTH_BAR, elBarX, elBarY);
	mgl->setFlatColor(hudHealthColor);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, elBarX, elBarY, elScale, 1.0f);
	mgl->setFlatColor(.09f, 1.0f, .05f, .75f);
	playerAtlas.drawScale2(mgl, PI_HEALTH_BAR, elBarX, elBarY, .1f, 1.0f);
}

// Draw player objects that need the UIAtlas
void Player::drawUI(GLHandler* mgl, UIAtlas* mUI){
	// Set text location 
	if (elTextX == 0.0f){
		elTextX = 
			(mgl->getScreenWidth() / 2.0f) - 
			(mUI->mTextRender->measureString(elText, elTextSize) / 2.0f);
	}

	mgl->setFlatColor(COLOR_UI_LABEL);

	// Draw animal abduct count
	mUI->draw(mgl, UII_CURRENCY_ANIMAL, locScoreAnimalX, locScoreAnimalY);
	mUI->mTextRender->drawText(*mgl,"" + toString(animalAbductCount),
		locScoreAnimalX+scoreTextOffsetX, 
		locScoreAnimalY+scoreTextOffsetY,0.0f,scoreTextSize);

	// Draw human abduct count 
	mUI->draw(mgl, UII_CURRENCY_HUMAN, locScoreHumanX, locScoreHumanY);
	mUI->mTextRender->drawText(*mgl,"" + toString(humanAbductCount),
		locScoreHumanX+scoreTextOffsetX, 
		locScoreHumanY+scoreTextOffsetY,0.0f,scoreTextSize);

	// Draw ammo 
	mUI->draw(mgl, UII_HUD_AMMO, ammoLocX, ammoLocY);
	std::string ammoS = getAmmoString();
	mUI->mTextRender->drawText(*mgl, ammoS, 
		ammoLocX - mUI->mTextRender->measureString(ammoS, elTextSize) + ammoOffsetX, 
		ammoLocY + ammoOffsetY , 0.0f, elTextSize);

	// Draw enemy left text
	mUI->mTextRender->drawText(*mgl, elText, elTextX, elTextY, 0.0f, elTextSize);
}

// Draw player light
void Player::drawLight(GLHandler* mgl){
	playerAtlas.bindTexture(mgl);
	playerAtlas.bindBuffers(mgl);

	ufo->drawLights(mgl, &playerAtlas, inUFO);
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
	yo = locY;
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
	yo = locY;
	inAir = true; 
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
	chitTime = hitTime;
	if(!invincible){
		health -= damage;
	}
	if (health < 0.0f)
		health = 0.0f;
}

// Check if the player is currently in the ufo
bool Player::isInUFO(){return inUFO;}


// Make it so the player no longer takes damage
void Player::makeInvincible(){
	printf("make invincible\n");
	ufo->setInvincible(true);
	invincible = true;
}

// Make it so the player will take damage 
void Player::makeMortal(){
	printf("make mortal\n");
	ufo->setInvincible(false);
	invincible = false;
}

// Get ammo string for current weapon
std::string Player::getAmmoString(){
	if (inUFO){
		return ufo->getAmmoString();
	}
	else {
		if (usingWeapon1 && weapon1 != NULL){
			return weapon1->getAmmoString();
		}
		else if (!usingWeapon1 && weapon2 != NULL){
			return weapon2->getAmmoString();
		}
	}

	return std::string("0/0");
}
	
// Set the given collision rectangle to the given location
void Player::setCollRec(Rec* r, float x, float y){
	r->copy(&collRec);

	r->setX(x - originX + r->getX());
	r->setY(y - originY + r->getY());
}
