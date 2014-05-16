#include "NPCcow.h"
using namespace std;

NPCcow::NPCcow(float x, float y) : NPCBasicCollision()
{
	// Basic NPC Properties
	stype = "cow";
	spawnX = locX = x;
	spawnY = yo = locY = y;
	width = 50.0f;
	height = 35.0f;
	originX = 25.0f;
	originY = 34.0f;
	rotation = 0.0f;
	scale = 1.0f;
	imageID = GI_NPC_COW_1;
	next = NULL;
	alive = true;
	type = NPC_ANIMAL;

	// Cow properties
	health = healthMax = 30.0f;
	direcX = 1.0f;
	speed = 10.0f;
	afraidSpeed = 3 * speed; // TODO this is clunky

	// Collision Values
	bounds.reset(0.0f,0.0f,50.0f,35.0f);
	waistHeight = 28.0f;
	depthForDepthCheck = 20.0f;

	// Animation 
	frames = 2;
	cframe = 0;
	frameRate = .3f;
	cframeTime = 0.0f;

	afraid = false;
	abductRate = 1.3f;
}


NPCcow::~NPCcow(){}

// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPCcow::updateMovement(float deltaTime, Handlers* handlers){
	NPCBasicCollision::updateMovement(deltaTime, handlers);

	if (alive && !beingAbducted){
		nextX = locX + (speed * direcX * deltaTime);
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCcow::update(float deltaTime, Handlers* handlers){
	NPCBasicCollision::update(deltaTime, handlers);

	if (alive){
		if (!beingAbducted){
			Player* player = (Player*)handlers->player;

			// Player location 
			float px = 0;
			float py = 0;

			if (!player->isInUFO()){
				px = player->getCenterX();
				py = player->getCenterY();
			}
			else {
				px = player->ufo->getCenterX();
				py = player->ufo->getCenterY();
			}

			//direction to the playerss
			bool playerIsToLeft = isPlayerToLeft(player);
			
			if(afraid){
				//affraid, run away from player
				if(playerIsToLeft){
					goRight();
				} else {
					goLeft();
				}
			} else {
				// Only come close if not allready close 
				if (dist(locX, locY, px, locY) > 100){
					//not afraid, go to player
					if(playerIsToLeft){
						goLeft();
					} else {
						goRight();
					}
				}
			}

			// Update frames
			cframeTime += deltaTime;
			if (cframeTime > frameRate){
				cframeTime = 0.0f;
				cframe++;
				if (cframe >= frames)
					cframe = 0;
			}
		}
	}
}

// Draw object to the screen
void NPCcow::draw(GLHandler* mgl, GameAtlas* mGame){
	NPCBasicCollision::draw(mgl, mGame);
	
	if (alive && mdraw){
		if (direcX < 0){
			// Draw body 
			mGame->draw(mgl, imageID+cframe,locX,locY,scale, rotation, originX, originY);
		}
		else {
			glCullFace(GL_FRONT);
			// Draw body 
			mGame->drawScale2(mgl, imageID+cframe,locX,locY,-scale,scale, rotation, originX, originY);
			glCullFace(GL_BACK);

		}

	}
}


// Called when the NPC runs into a wall
void NPCcow::hitWall(){
	NPCBasicCollision::hitWall();

	direcX = -direcX;
}


void NPCcow::goLeft(){
	direcX = -1;
}

void NPCcow::goRight(){
	direcX = 1;
}

bool NPCcow::isPlayerToLeft(Player* player){
	if(player->isInUFO()){
		if(player->ufo->getCenterX()-locX > 0){
			return false;
		} else {
			return true;
		}
	} else {
		if(player->getCenterX()-locX > 0){
			return false;
		} else {
			return true;
		}
	}
}

// Damage the npc by sent damage amout.
// Will set npc to !alive if too much damage taken
void NPCcow::damage(float amount, Handlers* handlers){
	NPC::damage(amount, handlers);
	
	// Check if cow is afraid 
	if(health < healthMax){
		afraid = true;
	}
}

// Called when npc dies 
void NPCcow::onDeath(Handlers* handlers){
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

