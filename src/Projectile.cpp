#include "Projectile.h"
using namespace std;

//Projectile Types Include
//Type 1 = Bullet
//Type 2 = Missle
//Type 3 = Non-Standard Moving Object (cows/rocks/cars/people)
//Type 4 = Beam

Projectile::Projectile()
{
	initValues();
}

Projectile::Projectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread)
{
	initValues();

	projectileType = ProjectileType;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	spread = Spread;
	float angle = atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = Mass;
	size = Size;
	if(projectileType == PROJT_BULLET || projectileType == PROJT_BEAM || projectileType == PROJT_TEST)
		negligence = false;
	alive = true;
}

Projectile::Projectile(short ProjectileType, float CurrentX, float CurrentY, float xLocation, float yLocation)
{
	initValues();

	projectileType = ProjectileType;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	float angle = atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 1;
	size = .5;
	if(projectileType == PROJT_BULLET || projectileType == PROJT_BEAM || projectileType == PROJT_TEST)
		negligence = false;
	alive = true;

}
//builds a default typed projectile, not to be used with projectile, only in inheritance

Projectile::~Projectile(){}

// Clone all the properties from the sent projectiles into this one
void Projectile::clone(Projectile* p){
	projectileType = p->projectileType;
	previousX = p->previousX;
	previousY = p->previousY;
	currentX = p->currentX;
	currentY = p->currentY;
	xVector = p->xVector; 
	yVector = p->yVector;
	mass = p->mass; 
	size = p->size; 
	negligence = p->negligence;
	alive = true;
	doesExplode = p->doesExplode;
	diesOnImpact = p->diesOnImpact;
	imageId = p->imageId;
	imageGlowId = p->imageGlowId;
	offsetX = p->offsetX;
	offsetY = p->offsetY;
	glowOffsetX = p->glowOffsetX;
	glowOffsetY = p->glowOffsetY;
	rotation = p->rotation;
	damage = p->damage;
	firedBy = p->firedBy;
}

void Projectile::reset()
{
	initValues();
}

//UpdateProjectile does the heavier stuff for projectiles with complicated movement, and will handle collision detection
//This will act as a default in case a projectile doesn't have its own updateProjectile method
void Projectile::updateProjectile(float deltaTime, Handlers* handlers)
{
	//cout << "updatingP/n";
	//cout << "yVector: " << yVector << " /n";
	//cout << "currentY: " << currentY << " /n";
	previousY = currentY;
	previousX = currentX;
	yVector+=1*size;
	//xVector+=.25*size;
	//There should be a very large section for collision based interactions
	//Stuff like rolling on the ground and bouncing
	currentX+=xVector*deltaTime;
	currentY+=yVector*deltaTime;
	//cout << "yVector: " << yVector << " /n";
	//cout << "currentY: " << currentY << " /n";

	// Check if projectile should be drawn 
	Camera2D* cam = (Camera2D*)handlers->camera;
	LevelProperties* levelProps = (LevelProperties*)handlers->levelProps;
	if (cam->toScreenX(currentX) > -50 && cam->toScreenX(currentX) < levelProps->getScreenWidth() + 50 &&
		cam->toScreenY(currentY) > -50 && cam->toScreenY(currentY) < levelProps->getScreenHeight() + 50)
		drawProj = true;
	else 
		drawProj = false;

	// Fix projectile rotation 
	rotation = (180.0f/3.14159f) * atan2(currentY - previousY, currentX - previousX);
}

//This method does not need to be overloaded for different projectiles, it is the same for every unphysiced projectile
void Projectile::updateNegligableProjectile(float deltaTime)
{
	//cout << "negP";
	previousY = currentY;
	previousX = currentX;
	currentX+=xVector*deltaTime;
	currentY+=yVector*deltaTime;

}

//This will need to have some cases for each different kind of projectile, but there are some basic reasons to be negligable here
void Projectile::determineNegligance()
{
	//#define PROJT_BULLET 1
	//#define PROJT_MISSILE 2
	//#define PROJT_NSMO 3
	//#define PROJT_BEAM 4
	//#define PROJT_TEST 5
	if(projectileType == PROJT_BULLET || projectileType == PROJT_BEAM || projectileType == PROJT_TEST)
	{
		//cout << "determined negligable";
		negligence = true; //A beam typed weapon would not be affected by gravity or wind resistance
	}
	else if(((xVector+yVector)*mass) >= 50000)
		negligence = true; //This is an extreme example of a case at which a projectile has enough inertia that it will take its course before noticable change to its trajectory
	else if(size < 1 && (xVector+yVector) >= 20000)
		negligence = true; //A sufficiently small projectile that is moving fast enough will not be affected by wind resistance and can most likely fulfill its course before gravity has any noticable effect
	//Need to figure out all the collision stuff, but here should be
	//if(projectile == Colliding)
	//  negligence = false;
	
}


// Draw projectile to screen
void Projectile::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	if (alive && drawProj){
		// Uncomment to draw 
		mAtlas->draw(mgl, imageId, currentX, currentY, 1.0f, rotation, offsetX, offsetY);

		// You will want to change this to 
		//mAtlas->draw(mgl, [Item index to draw], currentX, currentY, 1.0f, [rotation], [origin x], [origin y]);
	}
}

// Draw projectile light to screen
void Projectile::drawLight(GLHandler* mgl, TextureAtlas* mAtlas){
	if (alive && drawProj && imageGlowId != -1){
		mAtlas->draw(mgl, imageGlowId, currentX, currentY, 1.0f, rotation, glowOffsetX, glowOffsetY);
	}
}

// Called when projectile collides with something
// CollType 
// 1 = player collision
// 2 = ground collision
// 3 = enemy collision 
//
// p = point of collision 
void Projectile::collide(Point* p, Handlers* handlers, int collType)
{
	// Please do collide stuff here, maybe set a variable for what 
	// it collides with, player/enemy/ground, and what side it collides on.

	// Kill if dies on impact
	if (diesOnImpact)
		alive = false;
}

short Projectile::getProjectileType(){return projectileType;}
float Projectile::getCurrentX(){return currentX;}
float Projectile::getCurrentY(){return currentY;}
float Projectile::getPrevX(){return previousX;}
float Projectile::getPrevY(){return previousY;}
bool Projectile::getNegligence(){return negligence;}
int Projectile::getUID(){return UID;}
bool Projectile::getAlive(){return alive;}
float Projectile::getDamage(){return damage;}
int Projectile::getFiredBy(){return firedBy;}
void Projectile::setUID(int newUID){UID = newUID;}
void Projectile::setAlive(bool value){alive = value;}
void Projectile::setImageId(int value){imageId = value;}
void Projectile::setImageGlowId(int value){imageGlowId = value;}
void Projectile::setOffset(float x, float y){offsetX = x; offsetY = y;}
void Projectile::setGlowOffset(float x, float y){glowOffsetX = x; glowOffsetY = y;}
void Projectile::setDamage(float value){damage = value;}
void Projectile::setFiredBy(int value){firedBy = value;}

// Setup basic values for all variables 
void Projectile::initValues(){
	projectileType = PROJT_TEST;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	spread = 0;
	speed = 200;
	mass = 0;
	size = 0;
	negligence = false;
	alive = false;
	doesExplode = false;
	isColliding = false;
	diesOnImpact = true;
	drawProj = false;
	imageId = 0;
	imageGlowId = -1;
	offsetX = offsetY = glowOffsetX = glowOffsetY = 0;
	rotation = 0;
	damage = 0.0f;
	firedBy = PFB_ENEMY;
}