#include "Explosion.h"


Explosion::Explosion()
{
	// --- Drawing 
	imageID = 0;
	locX = locY = 0.0f;
	originX = originY = 0.0f;
	rotation = 0.0f;

	// --- Exploding
	damage = 0.0f;
	range = 0.0f;
	explTime = 0.0f;			
	cexplTime = 0.0f;		

	// --- Animation
	animates = false;
	frames = 0;
	cframe = 0;
	frameTime = 0.0f;
	cframeTime = 0.0f;

	// --- States
	valid = false;
	type = PLAYER_EXP;
	next = NULL;
}

Explosion::Explosion(Explosion* e){
	clone(e);
}

Explosion::~Explosion()
{

}

// Clone this explosion off the sent one 
void Explosion::clone(Explosion* e){
	// --- Drawing 
	imageID = e->imageID;
	locX = e->locX;
	locY = e->locY;
	originX = e->originX;
	originY = e->originY;
	rotation = e->rotation;

	// --- Exploding
	damage = e->damage;
	range = e->range;
	explTime = e->explTime;			
	cexplTime = e->cexplTime;		

	// --- Animation
	animates = e->animates;
	frames = e->frames;
	cframe = e->cframe;
	frameTime = e->frameTime;
	cframeTime = e->cframeTime;

	// --- States
	valid = true;
	type = e->type;
	next = e->next;
}
	
// Returns explosion damage
float Explosion::getDamage(){
	return damage;
}

// Set exp location 
void Explosion::setLocation(float x, float y){
	locX = x; locY = y;
}

// Set exp type
void Explosion::setType(int t){
	type = t;
}

// Returns explosion type 
int Explosion::getType(){
	return type;
}

// Returns true if fired by player
bool Explosion::firedByPlayer(){
	return type == PLAYER_EXP;
}
	
// Returns true if fired by enemy 
bool Explosion::firedByEnemy(){
	return type == ENEMY_EXP;
}

// Update explosion state
void Explosion::update(float deltaTime){
	if (valid){
		// Update animation state 
		if (animates){
			cframeTime += deltaTime;
			if (cframeTime >= frameTime){
				cframeTime = 0.0f;
				cframe++;
			}
		}

		// Update explosion time 
		cexplTime += deltaTime;

		// Check if explosion is over 
		if (cexplTime > explTime &&
			((animates && cframe >= frames) || !animates)){
			valid = false;
		}
	}
}

// Draw Explosion 
void Explosion::draw(GLHandler* mgl, GameAtlas* mAtlas){
	if (valid && ((animates && cframe < frames) || !animates)){
		mAtlas->draw(mgl,imageID + cframe, locX, locY, 1.0f, rotation, originX, originY);
	}
}

// Draw Explosion Light
void Explosion::drawLight(GLHandler* mgl, GameAtlas* mAtlas){
	// TODO 
}

// Check if explosion is valid
bool Explosion::isValid(){
	return valid;
}

// Check if explosion is active
bool Explosion::active(){
	return cexplTime < explTime;
}

// Check if position is in range
bool Explosion::inRange(float x, float y){
	return dist(x,y,locX,locY) < range;
}
