#include "NPCStingerSoldier.h"


NPCStingerSoldier::NPCStingerSoldier(float x, float y) : NPCBasicCollision()
{
	// Basic NPC Properties
	stype = "stinger";
	spawnX = locX = x;
	spawnY = yo = locY = y;
	width = 50.0f;
	height = 50.0f;
	originX = 25.0f;
	originY = 50.0f;
	rotation = 0.0f;
	scale = 1.0f;
	if (rand() % 100 > 50)
		imageID = GI_NPC_SOLDIER_M1;
	else 
		imageID = GI_NPC_SOLDIER_F1;
	next = NULL;
	alive = true;

	// Movement properties
	direcX = 1.0f;
	speed = 100.0f;
	minDistanceTFlop = 100.0f;
	maxDistanceTFlop = 300.0f;
	distanceTillFlop = 200.0f;
	currentDistance = 0.0f;

	// Collision Values
	bounds.reset(0.0f,0.0f,50.0f,50.0f);
	waistHeight = 35.0f;
	depthForDepthCheck = 20.0f;

	// Animation 
	frames = 3;
	cframe = 0;
	frameRate = .1f;
	cframeTime = 0.0f;

	// Arm 
	armOffsetX = 23.0f;
	armOffsetY = 25.0f;
	armOriginX = 2.5f;
	armOriginY = 3.0f;
	armRotation = 30.0f;

	// Weapon properties 
	weapon = (Weapon*)new NPCStinger();
	weaponRange = 600.0f;
	playerInRange = false;
	caquireTime = 0.0f;
	aquireTime = 1.0f;
}

NPCStingerSoldier::~NPCStingerSoldier(){}

// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPCStingerSoldier::updateMovement(float deltaTime, Handlers* handlers){
	NPCBasicCollision::updateMovement(deltaTime, handlers);

	if (alive && !beingAbducted){
		// Walk if not shooting 
		if (!playerInRange){
			nextX = locX + (speed * direcX * deltaTime);

			// Flop soldier
			currentDistance += speed * deltaTime;
			if (currentDistance > distanceTillFlop){
				distanceTillFlop = minDistanceTFlop + 
					(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
				currentDistance = 0.0f;
				direcX = -direcX;
			}

			// Update walk frames 
			cframeTime += deltaTime;
			if (cframeTime > frameRate){
				cframeTime = 0.0f;
				cframe++;
				if (cframe >= frames)
					cframe = 0;
			}
		}
		else 
			// Set current frame to 0 if not shooting so NPC
			// doesn't walk in place. 
			cframe = 0;
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCStingerSoldier::update(float deltaTime, Handlers* handlers){
	NPCBasicCollision::update(deltaTime, handlers);

	if (alive){
		// Allways update weapon
		if (direcX > 0)
			weapon->update(deltaTime, 
				locX - originX + armOffsetX, 
				locY - originY + armOffsetY);
		else 
			weapon->update(deltaTime, 
				locX - originX + (width - armOffsetX), 
				locY - originY + armOffsetY);

		if (!beingAbducted){
			// Update weapon
			Player* player = (Player*)handlers->player;
			UFO* ufo = player->ufo;

			// Try and attack player 
			if (dist(locX, locY, ufo->getCenterX(), ufo->getCenterY()) < weaponRange &&
				((ufo->getX() > locX && direcX > 0.0f) || 
				(ufo->getX() < locX && direcX < 0.0f) )){

				// Aquire Target 
				playerInRange = true;
				caquireTime += deltaTime;

				// Fire when target aquired 
				if (caquireTime >= aquireTime){
					// Try to fire at player 
					weapon->npcFire(ufo->getCenterX(), ufo->getCenterY(), handlers);
				}
				else {
					// These need to be called, otherwise the weapon will glitch
					// while the npc is aquiring target. 
					weapon->setRotation(0.0f);
					weapon->setFacingDirec(direcX > 0.0f);
					weapon->setRotationByTarget(ufo->getCenterX(), ufo->getCenterY());
				}
			}
			else {
				// Reset gun if can't find target
				weapon->setRotation(0.0f);
				weapon->setFacingDirec(direcX > 0.0f);
				playerInRange = false;
				caquireTime = 0.0f;
			}

			armRotation = weapon->getRotation();
		}
	}
}

// Draw object to the screen
void NPCStingerSoldier::draw(GLHandler* mgl, GameAtlas* mGame){
	NPCBasicCollision::draw(mgl, mGame);
	
	if (alive && mdraw){
		if (direcX > 0){
			// Draw body 
			mGame->draw(mgl, imageID+cframe,locX,locY,scale, rotation, originX, originY);
			// Draw weapon 
			weapon->draw(mgl, mGame);
			// Draw arm 
			mGame->draw(mgl, GI_NPC_SOLDIER_ARM,
				locX-originX+armOffsetX,
				locY-originY+armOffsetY,
				1.0f,armRotation,armOriginX,armOriginY);
		}
		else {
			glCullFace(GL_FRONT);
			// Draw body 
			mGame->drawScale2(mgl, imageID+cframe,locX,locY,-scale,scale, rotation, originX, originY);
			glCullFace(GL_BACK);

			// Draw weapon 
			weapon->draw(mgl, mGame);

			// Draw arm 
			glCullFace(GL_FRONT);
			mGame->drawScale2(mgl, GI_NPC_SOLDIER_ARM,
				locX-originX+(width-armOffsetX),
				locY-originY+armOffsetY,
				-1.0f,1.0f,armRotation,armOriginX,armOriginY);
			glCullFace(GL_BACK);
		}

	}
}


// Called when the NPC runs into a wall
void NPCStingerSoldier::hitWall(){
	NPCBasicCollision::hitWall();

	direcX = -direcX;
	distanceTillFlop = minDistanceTFlop + 
			(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
		currentDistance = 0.0f;
}

// Called when npc dies 
void NPCStingerSoldier::onDeath(Handlers* handlers){
	NPC::onDeath(handlers);

	Particle* p = ((ParticleHandler*)handlers->partHandler)->add(
		GI_SPLAT1,	// Image
		locX,locY-(height*.5f),	// Location
		20.0f,25.0f,// Origin
		0.0f,0.0f,	// Direction
		0.0f,		// Speed
		0.1f,		// Life
		0.0f,		// Rotation speed
		0.0f);		// Scale speed 

	if (p != NULL){
		p->setAnimates(true);
		p->setFrames(3);
		p->setFrameTime(.05f);
		p->setRotation(((rand()%100)/100.0f)*360.0f);
	}
}