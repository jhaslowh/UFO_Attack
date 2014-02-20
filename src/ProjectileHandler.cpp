#pragma once
#include "ProjectileHandler.h"
#include <list>
//almost did ifndef/endif out of habit

ProjectileHandler::ProjectileHandler()
{
	projectiles = std::list<Projectile*>(5);
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
	if(projectiles.size()==projectiles.max_size())
	{
		projectiles.resize(projectiles.size()+5);
		newProjectile->setUID(UIDIterator);
		projectiles.push_back(newProjectile);
		UIDIterator++;
	}
	else
	{
		newProjectile->setUID(UIDIterator);
		projectiles.push_back(newProjectile);
		UIDIterator++;
	}
}

void ProjectileHandler::updateProjectiles()
{
	for(std::list<Projectile*>::iterator myIterator = projectiles.begin(); myIterator != projectiles.end(); myIterator++)
	{
		if((*myIterator)->getNegligence())
			(*myIterator)->updateNegligableProjectile();
		else
			(*myIterator)->updateProjectile();
	}
}

void ProjectileHandler::removeProjectile(Projectile* removeProjectile)
{
	for(std::list<Projectile*>::iterator myIterator = projectiles.begin(); myIterator != projectiles.end(); myIterator++)
	{
		if(*myIterator == removeProjectile && (*myIterator)->getUID() ==removeProjectile->getUID())
			projectiles.erase(myIterator);
	}
}

void ProjectileHandler::cleanUp()
{
	projectiles.clear();
}