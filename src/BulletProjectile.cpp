#include "BulletProjectile.h"

BulletProjectile::BulletProjectile()
{
	projectileType = PROJT_BULLET;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	spread = 40;
	speed = 200;
	mass = 1;
	size = .5;
	negligence = true;
	alive = false;
	doesExplode = false;
	isColliding = false;
}

BulletProjectile::BulletProjectile(float CurrentX, float CurrentY, int speed, bool doesExplode, float directionx, float directiony)
{
	projectileType = PROJT_NSMO;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	spread = 0;
	xVector = speed*directionx;
	yVector = speed*directiony;
	mass = 1;
	size = .5;
	negligence = false;
	alive = true;
	isColliding = false;
	this->doesExplode = doesExplode;
}

BulletProjectile::BulletProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread)
{
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	spread = Spread;
	float angle = atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 1;
	size = .5;
	negligence = true;
	alive = true;
	isColliding = false;
}

BulletProjectile::BulletProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation)
{
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = 200;
	spread = 40;
	float angle = atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 1;
	size = .5;
	negligence = true;
	alive = true;
	isColliding = false;
}

BulletProjectile::~BulletProjectile()
{

}