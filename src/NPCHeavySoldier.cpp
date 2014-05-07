#include "NPCHeavySoldier.h"


NPCHeavySoldier::NPCHeavySoldier(float x, float y) : NPCBasicCollision()
{
	// Basic NPC Properties
	stype = "hsoldier";
	spawnX = locX = x;
	spawnY = yo = locY = y;
	width = 50.0f;
	height = 50.0f;
	originX = 25.0f;
	originY = 50.0f;
	rotation = 0.0f;
	scale = 1.0f;
	imageID = GI_NPC_HSOLDIER1;
	next = NULL;
	alive = true;
	health = 200.0f;
	healthMax = 200.0f;

	// Movement properties
	direcX = 1.0f;
	speed = 140.0f;
	minDistanceTFlop = 150.0f;
	maxDistanceTFlop = 400.0f;
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
	weapon = (Weapon*)new NPCSMG();
	weapon->setIsPlayerWeapon(false);
	weaponRange = 350.0f;

	abductRate = .3f;
}


NPCHeavySoldier::~NPCHeavySoldier(void)
{

}

// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPCHeavySoldier::updateMovement(float deltaTime, Handlers* handlers){
	NPCBasicCollision::updateMovement(deltaTime, handlers);

	if (alive && !beingAbducted){
		nextX = locX + (speed * direcX * deltaTime);

		// Flop soldier
		currentDistance += speed * deltaTime;
		if (currentDistance > distanceTillFlop){
			distanceTillFlop = minDistanceTFlop + 
				(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
			currentDistance = 0.0f;
			direcX = -direcX;
		}
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCHeavySoldier::update(float deltaTime, Handlers* handlers){
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
			// Update frames 
			cframeTime += deltaTime;
			if (cframeTime > frameRate){
				cframeTime = 0.0f;
				cframe++;
				if (cframe >= frames)
					cframe = 0;
			}

			// ------------------------------
			// Update weapon
			// ------------------------------
			Player* player = (Player*)handlers->player;
		

			// Try and attack player 
			if (player->isInUFO() && 
				dist(locX, locY, player->ufo->getCenterX(), player->ufo->getCenterY()) < weaponRange){
				// Try to fire at ufo
				if ((player->ufo->getX() > locX && direcX > 0.0f) || 
					(player->ufo->getX() < locX && direcX < 0.0f) ){
					weapon->npcFire(player->ufo->getCenterX(), player->ufo->getCenterY(), handlers);
				}
			}
			else if (!player->isInUFO() && 
				dist(locX, locY, player->getCenterX(), player->getCenterY()) < weaponRange){
				// Try to fire at player 
				if ((player->getX() > locX && direcX > 0.0f) || 
					(player->getX() < locX && direcX < 0.0f) ){
					weapon->npcFire(player->getCenterX(), player->getCenterY(), handlers);
				}
			}
			else {
				// Reset gun if can't find target
				weapon->setRotation(0.0f);
				weapon->setFacingDirec(direcX > 0.0f);
			}

			armRotation = weapon->getRotation();
		}
	}
}

// Draw object to the screen
void NPCHeavySoldier::draw(GLHandler* mgl, GameAtlas* mGame){
	NPCBasicCollision::draw(mgl, mGame);
	
	if (alive && mdraw){
		if (direcX > 0){
			// Draw body 
			mGame->draw(mgl, imageID+cframe,locX,locY,scale, rotation, originX, originY);
			// Draw weapon 
			weapon->draw(mgl, mGame);
			// Draw arm 
			mGame->draw(mgl, GI_NPC_HSOLDIER_ARM,
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
			mGame->drawScale2(mgl, GI_NPC_HSOLDIER_ARM,
				locX-originX+(width-armOffsetX),
				locY-originY+armOffsetY,
				-1.0f,1.0f,armRotation,armOriginX,armOriginY);
			glCullFace(GL_BACK);
		}

	}
}


// Called when the NPC runs into a wall
void NPCHeavySoldier::hitWall(){
	NPCBasicCollision::hitWall();

	direcX = -direcX;
	distanceTillFlop = minDistanceTFlop + 
			(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
		currentDistance = 0.0f;
}

// Called when npc dies 
void NPCHeavySoldier::onDeath(Handlers* handlers){
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
