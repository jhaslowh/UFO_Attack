#pragma once
#include "Projectile.h"

class NSMOProjectile: public Projectile
{
public:
	NSMOProjectile();
	NSMOProjectile(float CurrentX, float CurrentY, int speed, 
		bool doesExplode, float directionx, float directiony);
	virtual  ~NSMOProjectile();

	virtual void updateProjectile(float deltaTime);
	virtual void updateNegligableProjectile(float deltaTime);
};