#pragma once
#include "Projectile.h"

class BeamProjectile: public Projectile
{
public:
	BeamProjectile();
	BeamProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread);
	BeamProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation);
	~BeamProjectile();


};