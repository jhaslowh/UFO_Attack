#pragma once
#include <list>
#include "Projectile.h"
#include "BeamProjectile.h"
#include "BulletProjectile.h"
#include "NSMOProjectile.h"
#include "MissileProjectile.h"

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

	// Returns the projectile list
	std::list<Projectile*> getProjList();

	void addNewProjectile(Projectile* newProjectile);
	void addProjectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode);
	void updateProjectiles(float deltaTime);
	void removeProjectile(Projectile* removeProjectile);
	//main methods to interact with projectiles
	//add projectile takes in same as constructor so it sets a current dead projectile to the new stats
	//add new projectile actually creates a new projectile

	// Draw all projectiles 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	void cleanUp();
	//Handles clean up of the list
};