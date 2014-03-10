#include "Projectile.h"
using namespace std;

//Projectile Types Include
//Type 1 = Bullet
//Type 2 = Missle
//Type 3 = Non-Standard Moving Object (cows/rocks/cars/people)
//Type 4 = Beam

Projectile::Projectile()
{
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
	negligence = true;
	alive = false;
	doesExplode = false;
	isColliding = false;
}

Projectile::Projectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread)
{
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
	isColliding = false;
}

Projectile::Projectile(short ProjectileType, float CurrentX, float CurrentY, float xLocation, float yLocation)
{
	projectileType = ProjectileType;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = 200;
	float angle = atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 1;
	size = .5;
	if(projectileType == PROJT_BULLET || projectileType == PROJT_BEAM || projectileType == PROJT_TEST)
		negligence = false;
	alive = true;
	isColliding = false;

}
//builds a default typed projectile, not to be used with projectile, only in inheritance

Projectile::~Projectile()
{

}

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
}

void Projectile::reset()
{
	projectileType = 0;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	mass = 0;
	size = 0;
	negligence = false;
	alive = false;
	doesExplode = false;
}

//UpdateProjectile does the heavier stuff for projectiles with complicated movement, and will handle collision detection
//This will act as a default in case a projectile doesn't have its own updateProjectile method
void Projectile::updateProjectile(float deltaTime)
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
}

//This method does not need to be overloaded for different projectiles, it is the same for every unphysiced projectile
void Projectile::updateNegligableProjectile(float deltaTime)
{
	cout << "negP";
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
	if (alive){
		// Uncomment to draw 
		mAtlas->draw(mgl, GI_CRATE, currentX, currentY, 0.3f, 0.0f, 12.5f, 12.5f);

		// You will want to change this to 
		//mAtlas->draw(mgl, [Item index to draw], currentX, currentY, 1.0f, [rotation], [origin x], [origin y]);
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
}

short Projectile::getProjectileType()
{
	return projectileType;
}
float Projectile::getCurrentX()
{
	return currentX;
}
float Projectile::getCurrentY()
{
	return currentY;
}
float Projectile::getPrevX(){return previousX;}
float Projectile::getPrevY(){return previousY;}
float getPrevY();
bool Projectile::getNegligence()
{
	return negligence;
}
int Projectile::getUID()
{
	return UID;
}
bool Projectile::getAlive(){
	return alive;
}

void Projectile::setUID(int newUID)
{
	UID = newUID;
}
void Projectile::setAlive(bool value){
	alive = value;
}