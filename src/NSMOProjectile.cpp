#include "NSMOProjectile.h"

NSMOProjectile::NSMOProjectile() : Projectile()
{
	projectileType = PROJT_NSMO;
	speed = 100;
	mass = 1;
	size = 1;
}

NSMOProjectile::NSMOProjectile(float CurrentX, float CurrentY, int speed, bool doesExplode, float directionx, float directiony) : Projectile()
{
	projectileType = PROJT_NSMO;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = speed;
	xVector = speed*directionx;
	yVector = speed*directiony;
	mass = 1;
	size = 1;
	negligence = false;
	alive = true;
	this->doesExplode = doesExplode;
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
