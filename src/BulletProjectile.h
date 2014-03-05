#pragma once
#include "Projectile.h"

class BulletProjectile: public Projectile
{
public:
	BulletProjectile();
	BulletProjectile(float CurrentX, float CurrentY, int speed, bool doesExplode, float directionx, float directiony);
	BulletProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread);
	BulletProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation);
	~BulletProjectile();
};