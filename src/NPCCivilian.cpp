#include "NPCCivilian.h"


NPCCivilian::NPCCivilian(float x, float y) : NPCBasicCollision()
{
	// Basic NPC Properties
	stype = "civilian";
	spawnX = locX = x;
	spawnY = yo = locY = y;
	width = 50.0f;
	height = 50.0f;
	originX = 25.0f;
	originY = 50.0f;
	rotation = 0.0f;
	scale = 1.0f;
	int r = rand() % 100;
	if (r > 75)
		imageID = GI_CIVI_MALE1_1;
	else if (r > 50)
		imageID = GI_CIVI_MALE1_1;
	else if (r > 25)
		imageID = GI_CIVI_FEMALE1_1;
	else 
		imageID = GI_CIVI_FEMALE2_1;
	next = NULL;
	alive = true;
	afraid = false;

	// Movement properties
	direcX = 1.0f;
	speed = 140.0f;
	afraidSpeed = 200.0f;
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
}


NPCCivilian::~NPCCivilian()
{

}

// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPCCivilian::updateMovement(float deltaTime, Handlers* handlers){
	NPCBasicCollision::updateMovement(deltaTime, handlers);

	if (alive && !beingAbducted){
		if (afraid)
			nextX = locX + (afraidSpeed * direcX * deltaTime);
		else 
			nextX = locX + (speed * direcX * deltaTime);

		if (!afraid){
			// Flop soldier
			currentDistance += speed * deltaTime;
			if (currentDistance > distanceTillFlop){
				distanceTillFlop = minDistanceTFlop + 
					(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
				currentDistance = 0.0f;
				direcX = -direcX;
			}
		}
		else {
			Player* player = (Player*)handlers->player;
			if (player->isInUFO()){
				if (player->ufo->getCenterX() > locX)
					direcX = -1.0f;
				else 
					direcX = 1.0f;
			}
			else {
				if (player->getCenterX() > locX)
					direcX = -1.0f;
				else 
					direcX = 1.0f;
			}
		}
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPCCivilian::update(float deltaTime, Handlers* handlers){
	NPCBasicCollision::update(deltaTime, handlers);

	if (alive){
		if (!beingAbducted){
			// Update frames 
			cframeTime += deltaTime;
			if (cframeTime > frameRate){
				cframeTime = 0.0f;
				cframe++;
				if (cframe >= frames)
					cframe = 0;
			}
		}
		else {
			afraid = true;
		}
	}
}

// Draw object to the screen
void NPCCivilian::draw(GLHandler* mgl, GameAtlas* mGame){
	NPCBasicCollision::draw(mgl, mGame);
	
	if (alive && mdraw){
		if (direcX > 0){
			// Draw body 
			if (afraid)
				mGame->draw(mgl, imageID+3+cframe,locX,locY,scale, rotation, originX, originY);
			else 
				mGame->draw(mgl, imageID+cframe,locX,locY,scale, rotation, originX, originY);
		}
		else {
			glCullFace(GL_FRONT);
			// Draw body 
			if (afraid)
				mGame->drawScale2(mgl, imageID+3+cframe,locX,locY,-scale,scale, rotation, originX, originY);
			else 
				mGame->drawScale2(mgl, imageID+cframe,locX,locY,-scale,scale, rotation, originX, originY);
			glCullFace(GL_BACK);
		}
	}
}


// Called when the NPC runs into a wall
void NPCCivilian::hitWall(){
	NPCBasicCollision::hitWall();

	direcX = -direcX;
	distanceTillFlop = minDistanceTFlop + 
			(rand() % (int)(maxDistanceTFlop - minDistanceTFlop)); 
		currentDistance = 0.0f;
}


// Damage the npc by sent damage amout.
// Will set npc to !alive if too much damage taken
void NPCCivilian::damage(float amount, Handlers* handlers){
	NPC::damage(amount, handlers);
	
	afraid = true;
}

// Called when npc dies 
void NPCCivilian::onDeath(Handlers* handlers){
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
