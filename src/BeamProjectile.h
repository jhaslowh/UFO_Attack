#pragma once
#include "Projectile.h"

class BeamProjectile : public Projectile
{
public:
	BeamProjectile();
	BeamProjectile(float CurrentX, float CurrentY, int speed, 
		bool doesExplode, float directionx, float directiony);
	virtual ~BeamProjectile();
};
