#pragma once
#include "Projectile.h"

class NSMOProjectile: public Projectile
{
public:
	//using Projectile::updateProjectile;
	//using Projectile::updateNegligableProjectile;

	NSMOProjectile();
	NSMOProjectile(float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread);
	NSMOProjectile(float CurrentX, float CurrentY, float xLocation, float yLocation);
	~NSMOProjectile();

	void updateProjectile(float deltaTime);
	void updateNegligableProjectile(float deltaTime);
};