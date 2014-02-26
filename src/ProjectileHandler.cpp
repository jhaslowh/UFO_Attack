#include "ProjectileHandler.h"
//almost did ifndef/endif out of habit

ProjectileHandler::ProjectileHandler()
{
	projectiles = std::list<Projectile*>();
	UIDIterator = 0;
}
ProjectileHandler::~ProjectileHandler()
{
	cleanUp();
}
//Constructor and Deconstructor

//Pass in a constructor Projectile to be contained by the list
void ProjectileHandler::addNewProjectile(Projectile* newProjectile)
{
	// List expands when you add to it, setting its size is uneeded 

	/*if(projectiles.size()==projectiles.max_size())
	{
		projectiles.resize(projectiles.size()+5);
		newProjectile->setUID(UIDIterator);
		projectiles.push_back(newProjectile);
		UIDIterator++;
	}
	else
	{*/
		newProjectile->setUID(UIDIterator);
		projectiles.push_back(newProjectile);
		UIDIterator++;
	//}
}

void ProjectileHandler::updateProjectiles(float deltaTime)
{
	for(std::list<Projectile*>::iterator myIterator = projectiles.begin(); myIterator != projectiles.end(); myIterator++)
	{
		// Null check 
		if (*myIterator != NULL){
			if((*myIterator)->getNegligence())
				(*myIterator)->updateNegligableProjectile();
			else
				(*myIterator)->updateProjectile(deltaTime);
		}
	}
}

void ProjectileHandler::removeProjectile(Projectile* removeProjectile)
{
	for(std::list<Projectile*>::iterator myIterator = projectiles.begin(); myIterator != projectiles.end(); myIterator++)
	{
		if(*myIterator != NULL && *myIterator == removeProjectile && (*myIterator)->getUID() ==removeProjectile->getUID())
			projectiles.erase(myIterator);
	}
}

// Draw all projectiles 
void ProjectileHandler::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	for(std::list<Projectile*>::iterator myIterator = projectiles.begin(); myIterator != projectiles.end(); myIterator++)
	{
		if(*myIterator != NULL)
			(*myIterator)->draw(mgl, mAtlas);
	}
}

void ProjectileHandler::cleanUp()
{
	projectiles.clear();
}