#include "NPCBasicCollision.h"


NPCBasicCollision::NPCBasicCollision() : NPC()
{
	// Physics 
	inAir = false;
	yo = 0.0f;
	airT = 0.0f;
	minAirtForInAir = .02f;

	// Collision Values 
	waistHeight = 35.0f;
	depthForDepthCheck = 20.0f;
}

NPCBasicCollision::~NPCBasicCollision()
{

}

// Update movement of the NPC 
// This method should set the movement values for the npc.
// Note: nextY is controled by gravity in the next method
void NPCBasicCollision::updateMovement(float deltaTime, Handlers* handlers){
	NPC::updateMovement(deltaTime, handlers);
}

// Update collision of NPC 
// This method should check if the npc is being abducted, if it is
// it should ignore the movement from the update movement method and 
// if it isnt, it should resolve the movement and collisions. 
void NPCBasicCollision::updateCollision(float deltaTime, Handlers* handlers){
	NPC::updateCollision(deltaTime, handlers);

	if (alive && !beingAbducted){
		// -----------
		// Gravity 
		// -----------
		// Update time in air and apply gravity 
		airT += deltaTime;
		nextY = yo + (.5f * GRAVITY * (airT * airT));

		// Check if in air
		if (airT > minAirtForInAir)
			inAir = true;

		// Point used during collision detection 
		Point p;
		Point* itr;

		// ----------------------------------------
		// Check player collision with level bounds
		// ----------------------------------------

		// Nasty code block....

		if (nextX - (width/2.0f) < ((LevelProperties*)(handlers->levelProps))->getLevelLeft()){
			nextX = ((LevelProperties*)(handlers->levelProps))->getLevelLeft() + (width/2.0f);
			hitWall();
		}
		else if (nextX + (width/2.0f) > ((LevelProperties*)(handlers->levelProps))->getLevelRight()){
			nextX = ((LevelProperties*)(handlers->levelProps))->getLevelRight() - (width/2.0f);
			hitWall();
		}

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
		horA.setLocation(nextX - (width/2.0f), nextY - waistHeight);
		horB.setLocation(nextX + (width/2.0f), nextY - waistHeight);

		// Steep hill check:
		// This check stops the player from walking up steep surfaces 
		itr = handlers->ground->getPoints();
		while (itr->next != NULL){
			// Check if npc is close to point
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
		itr = handlers->ground->getPoints();
		while (itr->next != NULL){
			// Check if npc is close to point
			if ((*itr).getX() <= nextX && (*(itr->next)).getX() >= nextX){
				if (checkSegSeg(vertA, vertB, *itr, *(itr->next), &p)){
					nextX = p.getX();
					nextY = p.getY();
					hitFloor();
					break;
				}
			}
			itr = itr->next;
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
		if (airT < minAirtForInAir && !inAir){
			itr = handlers->ground->getPoints();
			while (itr->next != NULL){
				// Check if npc is close to point
				if ((*itr).getX() <= nextX && (*(itr->next)).getX() >= nextX){
					if (checkSegSeg(vertBotA, vertBotB, *itr, *(itr->next), &p)){
						nextX = p.getX();
						nextY = p.getY();
						hitFloor();
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
						if (sitr->getStopPlayer()) {
							xpass = false;
							hitWall();
						}
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

								hitFloor();
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
			hitFloor();
			ypass = false;
			xpass = false;
		}

		// Fix position if collision found 
		if (!xpass)
			nextX = locX;
		if (!ypass)
			nextY = locY;
			
		// ---------------------------------------------
		// Check NPC collision with player projectiles  
		// ---------------------------------------------
		// Fix collision rectangles for next steps
		setCollRec(&collRecXY, nextX, nextY);

		Projectile** projs = ((ProjectileHandler*)handlers->projHandler)->getProjList();
		Point projp;

		// Check all projectiles for collision 
		for (int i = 0; i <= ((ProjectileHandler*)handlers->projHandler)->getLastActive(); i++){
			// Null check / Alive check / shot by player 
			if (projs[i]  != NULL && projs[i] ->getAlive() && projs[i] ->getFiredBy() == PFB_PLAYER){	
				// Quick distance check 
				if (dist(nextX, nextY,projs[i] ->getCurrentX(), projs[i] ->getCurrentY()) <100){ 
					// Check for collision 
					if (checkRecSeg(&collRecXY, 
						projs[i] ->getCurrentX(), projs[i] ->getCurrentY(), 
						projs[i] ->getPrevX(), projs[i] ->getPrevY(), &projp)){

						// Tell projectile we had a player collision 
						projs[i] ->collide(&projp, handlers, P_ENEMY_COLL);

						// Apply projectile damage to npc
						damage(projs[i]->getDamage(), handlers);
					}
				}
			}
		}

		// ---------------------------------------------
		// Check ufo collision with player explosions  
		// ---------------------------------------------
		// Fix collision rectangles for next steps
		setCollRec(&collRecXY, nextX, nextY);
		Explosion* expls = ((ExplHandler*)handlers->explHander)->getExpls();

		for (int i = 0; i <= ((ExplHandler*)handlers->explHander)->getLastActive(); i++){
			if (expls[i].isValid()){
				if (expls[i].firedByPlayer() && expls[i].inRadius(&collRecXY)){
					damage(expls[i].getDamage(), handlers);
				}
			}
		}

		// ------------------------------------------

		locX = nextX;
		locY = nextY;
	}
	else {
		// Reset states if being abducted
		nextX = locX;
		nextY = yo = locY;
		airT = 0.0f;
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCBasicCollision::update(float deltaTime, Handlers* handlers){
	NPC::update(deltaTime, handlers);
	// Nothing to do
}

// Draw any light this object has 
void NPCBasicCollision::drawLight(GLHandler* mgl, GameAtlas* mGame){
	NPC::drawLight(mgl, mGame);
	// Nothing to do
}

// Draw object to the screen
void NPCBasicCollision::draw(GLHandler* mgl, GameAtlas* mGame){
	NPC::draw(mgl, mGame);
	// Nothing to do
}

// Called when the NPC runs into a wall
void NPCBasicCollision::hitWall(){

}

// Called when the NPC runs into the floor 
void NPCBasicCollision::hitFloor(){
	airT = 0;
	yo = locY;
	inAir = false;
}

// Called when the NPC runs into the ceiling
void NPCBasicCollision::hitCeiling(){
	airT = 0;
	yo = locY;
	inAir = true; 
}

// Set the given collision rectangle to the given location
void NPCBasicCollision::setCollRec(Rec* r, float x, float y){
	r->setX(x - originX + bounds.getX());
	r->setY(y - originY + bounds.getY());
	r->setWidth(bounds.getWidth());
	r->setHeight(bounds.getHeight());
}
