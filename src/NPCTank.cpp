#include "NPCTank.h"

NPCTank::NPCTank(float x, float y) : NPCBasicCollision()
{
	// Basic NPC Properties
	stype = "tank";
	spawnX = locX = x;
	spawnY = yo = locY = y;
	width = 124.0f;
	height = 50.0f;
	originX = 62.0f;
	originY = 50.0f;
	rotation = 0.0f;
	scale = 1.0f;
	imageID = GI_TANK;
	next = NULL;
	alive = true;
	health = 240.0f;
	healthMax = 240.0f;
	canBeAbducted = false;

	// Movement properties
	direcX = 1.0f;
	speed = 50.0f;
	minDistanceTFlop = 150.0f;
	maxDistanceTFlop = 400.0f;
	distanceTillFlop = 200.0f;
	currentDistance = 0.0f;

	// Pause before flop 
	pauseToFlop = false;
	pauseTime = .75f;
	cpauseTime = 0.0f;

	// Collision Values
	bounds.reset(0.0f,0.0f,124.0f,50.0f);
	waistHeight = 35.0f;
	depthForDepthCheck = 20.0f;

	// Weapon properties 
	weapon = (Weapon*)new NPCTankBarrel();
	weapon->setIsPlayerWeapon(false);
	weaponRange = 600.0f;
	barrelX = 80.0f;
	barrelY = 20.0f;
}

NPCTank::~NPCTank()
{

}


// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPCTank::updateMovement(float deltaTime, Handlers* handlers){
	NPCBasicCollision::updateMovement(deltaTime, handlers);
	if (alive && !beingAbducted){

		// This is a pause at end of current walk 
		if (pauseToFlop){
			cpauseTime += deltaTime;
			if (cpauseTime >= pauseTime){
				pauseToFlop = false;
				cpauseTime = 0.0f;
				
				direcX = -direcX;

				// Fix weapon 
				weapon->setRotation(0.0f);
				weapon->setFacingDirec(direcX > 0.0f);
			}
		}
		else {
			// Update location 
			nextX = locX + (speed * direcX * deltaTime);

			// Flop tank
			currentDistance += speed * deltaTime;
			if (currentDistance > distanceTillFlop){
				distanceTillFlop = minDistanceTFlop + 
					(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
				currentDistance = 0.0f;
				pauseToFlop = true;
			}
		}
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCTank::update(float deltaTime, Handlers* handlers){
	NPCBasicCollision::update(deltaTime, handlers);

	if (alive){
		// Allways update weapon
		if (direcX > 0)
			weapon->update(deltaTime, 
				locX - originX + barrelX, 
				locY - originY + barrelY);
		else 
			weapon->update(deltaTime, 
				locX - originX + (width - barrelX), 
				locY - originY + barrelY);

		if (!beingAbducted){
			// ------------------------------
			// Update weapon
			// ------------------------------
			Player* player = (Player*)handlers->player;
		

			// Current barrel x location 
			float currentBarrelX = 0.0f;
			if (direcX > 0.0f)
				currentBarrelX = locX - originX + barrelX;
			else 
				currentBarrelX = locX - originX + (width - barrelX);

			// Try and attack player 
			if (player->isInUFO() && 
				dist(locX, locY, player->ufo->getCenterX(), player->ufo->getCenterY()) < weaponRange){
				// Try to fire at ufo
				if ((player->ufo->getX() > currentBarrelX && direcX > 0.0f) || 
					(player->ufo->getX() < currentBarrelX && direcX < 0.0f) ){
					weapon->npcFire(player->ufo->getCenterX(), player->ufo->getCenterY(), handlers);
				}
			}
			else if (!player->isInUFO() && 
				dist(locX, locY, player->getCenterX(), player->getCenterY()) < weaponRange){
				// Try to fire at player 
				if ((player->getX() > currentBarrelX && direcX > 0.0f) || 
					(player->getX() < currentBarrelX && direcX < 0.0f) ){
					weapon->npcFire(player->getCenterX(), player->getCenterY(), handlers);
				}
			}
			else {
				// Reset gun if can't find target
				weapon->setRotation(0.0f);
				weapon->setFacingDirec(direcX > 0.0f);
			}
		}
	}
}

// Draw object to the screen
void NPCTank::draw(GLHandler* mgl, GameAtlas* mGame){
	NPCBasicCollision::draw(mgl, mGame);
	
	if (alive && mdraw){
		if (direcX > 0){
			// Draw body 
			mGame->draw(mgl, imageID,locX,locY,scale, rotation, originX, originY);
			// Draw weapon 
			weapon->draw(mgl, mGame);
		}
		else {
			glCullFace(GL_FRONT);
			// Draw body 
			mGame->drawScale2(mgl, imageID,locX,locY,-scale,scale, rotation, originX, originY);
			glCullFace(GL_BACK);

			// Draw weapon 
			weapon->draw(mgl, mGame);
		}
	}
}


// Called when the NPC runs into a wall
void NPCTank::hitWall(){
	NPCBasicCollision::hitWall();

	direcX = -direcX;
	distanceTillFlop = minDistanceTFlop + 
			(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
		currentDistance = 0.0f;
}

// Damage the npc by sent damage amout.
// Will set npc to !alive if too much damage taken
void NPCTank::damage(float amount, Handlers* handlers){
	NPC::damage(amount, handlers);

	// Create explosion on death 
	if (!alive){
		Explosion e;
		e.setAsBasic();
		e.setLocation(locX, locY);
		((ExplHandler*)handlers->explHander)->add(&e);
	}
}
