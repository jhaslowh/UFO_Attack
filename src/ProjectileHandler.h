#pragma once
#include "Projectile.h"
#include "BeamProjectile.h"
#include "BulletProjectile.h"
#include "NSMOProjectile.h"
#include "MissileProjectile.h"

class ProjectileHandler
{
private:
	// Current size of list
	int size;
	// Last active element in list 
	int lastActive;

	// List of projectiles 
	Projectile** projs;

public:
	ProjectileHandler();
	~ProjectileHandler();

	// Returns the projectile list
	Projectile** getProjList();

	// Return size
	int getSize();

	// Returns last active 
	int getLastActive();

	// Add new projectile to list of projectiles 
	void addNewProjectile(Projectile* newProjectile);
	
	// Update current projectile states 
	void updateProjectiles(float deltaTime, Handlers* handlers);

	// Draw all projectiles 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);
	// Draw all projectiles lights 
	void drawLight(GLHandler* mgl, TextureAtlas* mAtlas);

	void cleanUp();
	//Handles clean up of the list
};