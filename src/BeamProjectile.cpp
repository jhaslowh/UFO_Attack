#include "BeamProjectile.h"

BeamProjectile::BeamProjectile() : Projectile()
{
	projectileType = PROJT_BEAM;
	speed = 600;
	mass = 0;
	size = 0;
	negligence = true;
}

BeamProjectile::BeamProjectile(float CurrentX, float CurrentY, int speed, bool doesExplode, float directionx, float directiony) : Projectile()
{
	projectileType = PROJT_BEAM;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	speed = speed;
	xVector = speed*directionx;
	yVector = speed*directiony;
	mass = 0;
	size = 0;
	negligence = true;
	alive = true;
	this->doesExplode = doesExplode;
}

BeamProjectile::~BeamProjectile()
{

}