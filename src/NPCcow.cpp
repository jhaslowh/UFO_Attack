#include "NPCcow.h"
#include <iostream>
using namespace std;

NPCcow::NPCcow(float x, float y) : NPCBasicCollision()
{
	// Basic NPC Properties
	stype = "cow";
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
	speed = 10.0f;
	afraidSpeed = 3 * speed; // TODO this is clunky

	// Collision Values
	bounds.reset(0.0f,0.0f,50.0f,50.0f);
	waistHeight = 35.0f;
	depthForDepthCheck = 20.0f;

	// Animation 
	frames = 3;
	cframe = 0;
	frameRate = .1f;
	cframeTime = 0.0f;

	afraid = false;


}


NPCcow::~NPCcow(void)
{
}


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
	
	if(health<healthMax){//TODO ideally this should be placed somewhere it only runs once, such as where the code to reduce NPC health. }
		afraid = true;
	}


	if (alive){
		if (!beingAbducted){
			// Update frames
			// Update weapon
			Player* player = (Player*)handlers->player;



			//direction to the playerss
			float direction = 0;
			bool playerIsToLeft = isPlayerToLeft(player);


			

			if(playerIsToLeft){
				cout << "to the left" << endl;
			}else{
				cout << "to the right " << endl;
			}

			if(afraid){
				//affraid, run away from player
				if(playerIsToLeft){
					goRight();
				} else {
					goLeft();
				}
			} else {
				//not afraid, go to player
				if(playerIsToLeft){
					goLeft();
				} else {
					goRight();
				}

			}



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
	
	if (alive){
		if (direcX > 0){
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

