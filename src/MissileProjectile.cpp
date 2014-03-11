#include "MissileProjectile.h"
using namespace std;

MissileProjectile::MissileProjectile()
{
	projectileType = PROJT_MISSILE;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	spread = 80;
	speed = 500;
	mass = 40;
	size = 5;
	negligence = false;
	alive = false;
	doesExplode = false;
	isColliding = false;
}

MissileProjectile::MissileProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread)
{
	projectileType = PROJT_MISSILE;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	spread = Spread;
	float angle = (float)atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 40;
	size = 5;
	negligence = false;
	alive = true;
	isColliding = false;
}

MissileProjectile::MissileProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation)
{
	projectileType = PROJT_MISSILE;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = 500;
	spread = 80;
	float angle = (float)atan2((double)(yLocation + (rand() % spread) - CurrentY), (double)(xLocation + (rand() % spread) - CurrentX));
	xVector = speed*(cos(angle));
	yVector = speed*(sin(angle));
	mass = 40;
	size = 5;
	negligence = false;
	alive = true;
	isColliding = false;
	cout << "false";
}

MissileProjectile::~MissileProjectile()
{

}

void MissileProjectile::updateProjectile(float deltaTime)
{
	//cout << "update";
	previousY = currentY;
	previousX = currentX;
	yVector+=10*size;
	xVector-=5*size;
	currentX+=xVector*deltaTime;
	currentY+=yVector*deltaTime;
}

void MissileProjectile::updateNegligableProjectile(float deltaTime)
{
	//cout << "neg";
	previousY = currentY;
	previousX = currentX;
	yVector+=10*size;
	xVector-=5*size;
	currentX+=xVector*deltaTime;
	currentY+=yVector*deltaTime;
}