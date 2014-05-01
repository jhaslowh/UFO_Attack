#include "BulletProjectile.h"

BulletProjectile::BulletProjectile() : Projectile()
{
	projectileType = PROJT_BULLET;
	speed = 200;
	mass = 1;
	size = 1;
}

BulletProjectile::BulletProjectile(float CurrentX, float CurrentY, int speed, bool doesExplode, float directionx, float directiony) : Projectile()
{
	projectileType = PROJT_BULLET;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	xVector = speed*directionx;
	yVector = speed*directiony;
	mass = 1;
	size = 1;
	alive = true;
	this->doesExplode = doesExplode;
}

BulletProjectile::~BulletProjectile()
{

}
