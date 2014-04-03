#include "NPCSoldier.h"


NPCSoldier::NPCSoldier(float x, float y) : NPCBasicCollision()
{
	// Basic NPC Properties 
	locX = x;
	locY = yo = y;
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

	// Soldier properties
	direcX = 1.0f;
	speed = 200.0f;

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
	weaponRange = 300.0f;
}

NPCSoldier::~NPCSoldier()
{

}

// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPCSoldier::updateMovement(float deltaTime, Handlers* handlers){
	NPCBasicCollision::updateMovement(deltaTime, handlers);

	if (alive && !beingAbducted){
		nextX = locX + (speed * direcX * deltaTime);
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCSoldier::update(float deltaTime, Handlers* handlers){
	NPCBasicCollision::update(deltaTime, handlers);

	if (alive){
		// Allways update weapon
		weapon->update(deltaTime, 
			locX - originX + armOffsetX, 
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

			// Update weapon
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
void NPCSoldier::draw(GLHandler* mgl, GameAtlas* mGame){
	NPCBasicCollision::draw(mgl, mGame);
	
	if (alive){
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
void NPCSoldier::hitWall(){
	NPCBasicCollision::hitWall();

	direcX = -direcX;
}
