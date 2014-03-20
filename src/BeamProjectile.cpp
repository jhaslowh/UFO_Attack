#include "BeamProjectile.h"

BeamProjectile::BeamProjectile()
{
	projectileType = PROJT_BEAM;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	spread = 10;
	speed = 600;
	mass = 0;
	size = 0;
	negligence = true;
	alive = false;
	doesExplode = false;
	isColliding = false;
}

BeamProjectile::BeamProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread)
{
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	spread = Spread;
	float angle = (float)atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 0;
	size = 0;
	negligence = true;
	alive = true;
	isColliding = false;
}

BeamProjectile::BeamProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation)
{
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = 600;
	spread = 10;
	float angle = (float)atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 0;
	size = 0;
	negligence = true;
	alive = true;
	isColliding = false;
}

BeamProjectile::~BeamProjectile()
{

}