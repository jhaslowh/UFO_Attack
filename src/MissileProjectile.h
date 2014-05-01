#pragma once
#include "Projectile.h"
#include <iostream>

class MissileProjectile: public Projectile
{
public:
	MissileProjectile();
	MissileProjectile(float CurrentX, float CurrentY, int speed, 
		bool doesExplode, float directionx, float directiony);
	virtual ~MissileProjectile();

	virtual void updateProjectile(float deltaTime);
	virtual void updateNegligableProjectile(float deltaTime);
};