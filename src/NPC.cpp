#include "NPC.h"

NPC::NPC()
{	
	spawnX = locX = 0.0f;
	spawnY = locY = 0.0f;
	width = 0.0f;
	height = 0.0f;
	originX = 0.0f;
	originY = 0.0f;
	rotation = 0.0f;
	scale = 1.0f;
	imageID = 0;
	next = NULL;
	
	canBeAbducted = true;
	beingAbducted = false;
	alive = true;
	mdraw = false;
	justDied = false;
	justAbduct = false;
	health = healthMax = 100.0f;
	type = NPC_HUMAN;
	cAbductSpeed = 0.0f;
	abductRate = 1.0f;
}

NPC::~NPC()
{
	delete next;
}

// Set the location of the npc 
void NPC::setLocation(float x, float y){
	locX = x;
	locY = y;
	fixCollRec();
}
float NPC::getX(){return locX;}
float NPC::getY(){return locY;}
float NPC::getSpawnX(){return spawnX;}
float NPC::getSpawnY(){return spawnY;}

std::string NPC::getSType()
{
	return stype;
}
// Returns the type of npc as a string

// Set the width and height of the npc
void NPC::setSize(float w, float h){
	width = w;
	height = h;
}
float NPC::getWidth(){return width;}
float NPC::getHeight(){return height;}
// Set the origin point of the npc
void NPC::setOrigin(float x, float y){
	originX = x;
	originY = y;
}
// Set the rotation of the npc
void NPC::setRotation(float r){
	rotation = r;
}
float NPC::getRotation(){return rotation;}
// Set the scale of the npc
void NPC::setScale(float s){
	scale = s;
}
float NPC::getScale(){return scale;}
// Set the image id to draw for this npc
void NPC::setImageID(int id){
	imageID = id;
}
int NPC::getImageID(){return imageID;}
bool NPC::getAlive(){return alive;}
bool NPC::getDraw(){return mdraw;}
bool NPC::getJustDied(){
	if (justDied){
		justDied = false;
		return true;
	}
	return false;
}
bool NPC::getJustAbduct(){
	if (justAbduct){
		justAbduct = false;
		return true;
	}
	return false;
}

// Returns npc collision rec
Rec* NPC::getCollisionRec(){return &collisionRec;}

// Fix collision rec location 
void NPC::fixCollRec(){
	collisionRec.setLocation(locX - originX + bounds.getX(), locY - originY + bounds.getX());
	collisionRec.setSize(bounds.getWidth(), bounds.getHeight());
}

// Update movement of the NPC 
// This method should set the movement values for the npc.
void NPC::updateMovement(float deltaTime, Handlers* handlers){
	// Nothing to do
}

// Update collision of NPC 
// This method should check if the npc is being abducted, if it is
// it should ignore the movement from the update movement method and 
// if it isnt, it should resolve the movement and collisions. 
void NPC::updateCollision(float deltaTime, Handlers* handlers){
	
	if (alive){
		fixCollRec();

		// Check if NPC is on screen toggle draw 
		if (checkRecRec(&collisionRec, &((LevelProperties*)handlers->levelProps)->screenRec))
			mdraw = true;
		else mdraw = false;


		// Update Abduction 
		if (canBeAbducted){
			// Check if ufo is being abducted 
			UFO* ufo = (UFO*)((Player*)handlers->player)->ufo;
			Player* player = (Player*)handlers->player;
			if (player->isInUFO() && ufo->isRayOn()  && checkRecRec(&collisionRec, ufo->getAbductArea())){
				if (!beingAbducted){
					beingAbducted = true;
					cAbductSpeed = ABDUCT_START_SPEED;
				}
			}
			else 
				beingAbducted = false;

			// Move to ship if being abducted 
			if (beingAbducted){
				// Get angle to ship 
				float mTheta = (float)atan2((double)(ufo->getY() - locY), (double)(ufo->getX() - locX));

				// Convert angle to direction 
				float direcX = cos(mTheta) * abductRate;
				float direcY = sin(mTheta) * abductRate;

				// Accelerate 
				cAbductSpeed += deltaTime * ABDUCT_ACCEL;
				if (cAbductSpeed > ABDUCT_MAX_SPEED)
					cAbductSpeed = ABDUCT_MAX_SPEED;

				// Move to ship 
				locX += deltaTime * direcX * cAbductSpeed;
				locY += deltaTime * direcY * cAbductSpeed;

				// Check if touching ship
				if (checkRecRec(&collisionRec, ufo->getUFOArea())){
					onAbduct(handlers);

					alive = false;

					// Increment points 
					if (type == NPC_ANIMAL)
						player->incrAnimalCount(1);
					else if (type == NPC_HUMAN)
						player->incrHumanCount(1);
				}
			}
		}
	}
}

// Update game state of the npc object
// Do any non movement or collision detection updates
// (weapons and the like) 
void NPC::update(float deltaTime, Handlers* handlers){
	// Nothing to do
}

// Draw any light this object has 
void NPC::drawLight(GLHandler* mgl, GameAtlas* mGame){
	// Nothing to do
}

// Draw object to the screen
void NPC::draw(GLHandler* mgl, GameAtlas* mGame){
	// Draw health bar
	if (alive && mdraw){
		mGame->draw(mgl, GI_NPC_HEALTH_BAR_OUTLINE, locX - 20.0f, locY - height- 10.0f);
		mGame->drawScale2(mgl, GI_NPC_HEALTH_BAR,locX - 19.0f, locY - height - 9.0f, health / healthMax, 1.0f);
	}
}

// Damage the npc by sent damage amout.
// Will set npc to !alive if too much damage taken
void NPC::damage(float amount, Handlers* handlers){
	health -= amount;
	if (health <= 0.0f){
		alive = false;
		onDeath(handlers);
	}
}

// Called when npc dies 
void NPC::onDeath(Handlers* handlers){
	//((ScriptHandler*)(handlers->scriptHandler))->wasDeathOrAbduction(1);
	justDied = true;
}

// Called when npc is abducted
void NPC::onAbduct(Handlers* handlers){
	//((ScriptHandler*)(handlers->scriptHandler))->wasDeathOrAbduction(2);
	((SoundHandler*)handlers->soundHandler)->playSoundEffect(SE_ABDUCT_SUCCESS);
	justAbduct = true;
}