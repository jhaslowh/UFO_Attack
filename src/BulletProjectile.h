#pragma once
#include "Projectile.h"

class BulletProjectile: public Projectile
{
public:
	BulletProjectile();
	BulletProjectile(float CurrentX, float CurrentY, int speed, 
		bool doesExplode, float directionx, float directiony);
	virtual ~BulletProjectile();
};