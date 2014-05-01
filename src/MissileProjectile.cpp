#include "MissileProjectile.h"
using namespace std;

MissileProjectile::MissileProjectile() : Projectile()
{
	projectileType = PROJT_MISSILE;
	speed = 500;
	mass = 40;
	size = 5;
}

MissileProjectile::MissileProjectile(float CurrentX, float CurrentY, int speed, bool doesExplode, float directionx, float directiony) : Projectile()
{
	projectileType = PROJT_MISSILE;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = speed;
	xVector = speed*directionx;
	yVector = speed*directiony;
	mass = 40;
	size = 5;//.5;
	negligence = false;
	alive = true;
	this->doesExplode = doesExplode;
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

