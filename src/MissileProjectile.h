#pragma once
#include "Projectile.h"
#include <iostream>

class MissileProjectile: public Projectile
{
public:
	//using Projectile::updateProjectile;
	//using Projectile::updateNegligableProjectile;

	MissileProjectile();
	MissileProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread);
	MissileProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation);
	~MissileProjectile();

	void updateProjectile(float deltaTime);
	void updateNegligableProjectile(float deltaTime);
};