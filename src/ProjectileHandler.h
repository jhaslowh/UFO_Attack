#pragma once
#include <list>
#include "Projectile.h"

class ProjectileHandler
{
private:
	std::list<Projectile*> projectiles;
	int UIDIterator;

	std::list<Projectile*>::iterator addIndex;

public:
	ProjectileHandler();
	~ProjectileHandler();
	//Constructor and Deconstructor

	void addNewProjectile(Projectile* newProjectile);
	void updateProjectiles(float deltaTime);
	void removeProjectile(Projectile* removeProjectile);
	//main methods to interact with projectiles

	// Draw all projectiles 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	void cleanUp();
	//Handles clean up of the list
};