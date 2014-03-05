#include "NSMOProjectile.h"

NSMOProjectile::NSMOProjectile()
{
	projectileType = PROJT_NSMO;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	spread = 60;
	speed = 100;
	mass = 1;
	size = 1;
	negligence = false;
	alive = false;
	doesExplode = false;
	isColliding = false;
}

NSMOProjectile::NSMOProjectile(float CurrentX, float CurrentY, int Mass, int Size, int speed, bool doesExplode, float directionx, float directiony)
{
	projectileType = PROJT_NSMO;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	spread = 0;
	xVector = speed*directionx;
	yVector = speed*directiony;
	mass = Mass;
	size = Size;
	negligence = false;
	alive = true;
	isColliding = false;
	this->doesExplode = doesExplode;
}


NSMOProjectile::NSMOProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread)
{
	projectileType = PROJT_NSMO;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	spread = Spread;
	float angle = atan2((double)(yLocation + (rand() % spread) - CurrentY),
		(double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = Mass;
	size = Size;
	negligence = false;
	alive = true;
	isColliding = false;
	this->doesExplode = doesExplode;
}

NSMOProjectile::NSMOProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation)
{
	projectileType = PROJT_NSMO;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = 100;
	spread = 60;
	float angle = atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 1;
	size = 1;
	negligence = false;
	alive = true;
	isColliding = false;
}

NSMOProjectile::~NSMOProjectile()
{

}

void NSMOProjectile::updateProjectile(float deltaTime)
{
	//std::cout << "updating";
	previousY = currentY;
	previousX = currentX;
	yVector+=3*size*deltaTime;
	xVector-=1*size*deltaTime;
	//There should be a very large section for collision based interactions
	//Stuff like rolling on the ground and bouncing
	currentX+=xVector*deltaTime;
	currentY+=yVector*deltaTime;
}

//This method does not need to be overloaded for different projectiles, it is the same for every unphysiced projectile
void NSMOProjectile::updateNegligableProjectile(float deltaTime)
{
	previousY = currentY;
	previousX = currentX;
	yVector+=3*size*deltaTime;
	xVector-=1*size*deltaTime;
	currentX+=xVector*deltaTime;
	currentY+=yVector*deltaTime;

}