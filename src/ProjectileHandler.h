#pragma once
#include "Projectile.h"
#include <list>

class ProjectileHandler
{
private:
	std::list<Projectile*> projectiles;
	int UIDIterator;

public:
	ProjectileHandler();
	~ProjectileHandler();
	//Constructor and Deconstructor

	void addNewProjectile(Projectile* newProjectile);
	void updateProjectiles();
	void removeProjectile(Projectile* removeProjectile);
	//main methods to interact with projectiles

	void cleanUp();
	//Handles clean up of the list
};