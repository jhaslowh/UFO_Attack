#include "NPCSamSite.h"

NPCSamSite::NPCSamSite(float x, float y) : NPC()
{
	// Basic NPC Properties
	stype = "sam";
	spawnX = locX = x;
	spawnY = locY = y;
	width = 50.0f;
	height = 31.0f;
	originX = 25.0f;
	originY = 31.0f;
	rotation = 0.0f;
	scale = 1.0f;
	imageID = GI_TURRET_BASE;
	next = NULL;
	alive = true;
	canBeAbducted = false;

	// Collision Values
	bounds.reset(0.0f,0.0f,50.0f,31.0f);

	// Weapon properties 
	weapon = (Weapon*)new NPCSam();
	weaponRange = 500.0f;
	wOffsetX = 25.0f;
	wOffsetY = 5.0f;
}

NPCSamSite::~NPCSamSite()
{

}

// Update collision of NPC 
// This method should check if the npc is being abducted, if it is
// it should ignore the movement from the update movement method and 
// if it isnt, it should resolve the movement and collisions. 
void NPCSamSite::updateCollision(float deltaTime, Handlers* handlers){
	NPC::updateCollision(deltaTime, handlers);

	if (alive && !beingAbducted){
		// Check NPC collision with player projectiles  
		// Fix collision rectangles for next steps
		fixCollRec();

		Projectile** projs = ((ProjectileHandler*)handlers->projHandler)->getProjList();
		Point projp;

		// Check all projectiles for collision 
		for (int i = 0; i <= ((ProjectileHandler*)handlers->projHandler)->getLastActive(); i++){
			// Null check / Alive check / shot by player 
			if (projs[i]  != NULL && projs[i] ->getAlive() && projs[i] ->getFiredBy() == PFB_PLAYER){	
				// Quick distance check 
				if (dist(locX, locY,projs[i] ->getCurrentX(), projs[i] ->getCurrentY()) <100){ 
					// Check for collision 
					if (checkRecSeg(&collisionRec, 
						projs[i] ->getCurrentX(), projs[i] ->getCurrentY(), 
						projs[i] ->getPrevX(), projs[i] ->getPrevY(), &projp)){

						// Tell projectile we had a player collision 
						projs[i] ->collide(&projp, handlers, P_ENEMY_COLL);
					}
				}
			}
		}

		// Check if player is trying to deactivate sam site 
		Player* player = ((Player*)handlers->player);

		if (!player->isInUFO() && player->getInteract() && 
			checkRecRec(player->getCollRec(), &collisionRec)){
			damage(100.0f, handlers);
		}
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCSamSite::update(float deltaTime, Handlers* handlers){
	NPC::update(deltaTime, handlers);
	
	if (alive){
		weapon->update(deltaTime, 
			locX - originX + wOffsetX, 
			locY - originY + wOffsetY);

		if (!beingAbducted){
			// ------------------------------
			// Update weapon
			// ------------------------------
			Player* player = (Player*)handlers->player;
		

			// Try and attack player 
			if (dist(locX, locY, player->ufo->getCenterX(), player->ufo->getCenterY()) < weaponRange){
				// Try to fire at player 
				weapon->npcFire(player->ufo->getCenterX(), player->ufo->getCenterY(), handlers);
			}
			else {
				// Reset gun if can't find target
				weapon->setRotation(0.0f);
			}
		}
	}
}

// Draw any light this object has 
void NPCSamSite::drawLight(GLHandler* mgl, GameAtlas* mGame){
	NPC::drawLight(mgl, mGame);

}

// Draw object to the screen
void NPCSamSite::draw(GLHandler* mgl, GameAtlas* mGame){
	// Dont draw health 
	// NPC::draw(mgl, mGame);
	
	if (alive && mdraw){
		// Draw body 
		mGame->draw(mgl, imageID,locX,locY,scale, rotation, originX, originY);
		// Draw weapon 
		weapon->draw(mgl, mGame);
	}
}

// Called when npc dies 
void NPCSamSite::onDeath(Handlers* handlers){
	NPC::onDeath(handlers);

	Particle* p = ((ParticleHandler*)handlers->partHandler)->add(
		GI_BASIC_EXPL_1,	// Image
		locX,locY-(height*.5f),	// Location
		30.0f,30.0f,// Origin
		0.0f,0.0f,	// Direction
		0.0f,		// Speed
		0.1f,		// Life
		0.0f,		// Rotation speed
		0.0f);		// Scale speed 

	if (p != NULL){
		p->setAnimates(true);
		p->setFrames(4);
		p->setFrameTime(.05f);
		p->setRotation(((rand()%100)/100.0f)*360.0f);
	}
}
