#include "ProjectileHandler.h"

ProjectileHandler::ProjectileHandler()
{
	// Make array 
	size = 250;
	lastActive = 0;
	projs = new Projectile*[size];
	for (int i = 0; i < size; i++){
		projs[i] = new Projectile();
	}
}
ProjectileHandler::~ProjectileHandler()
{
	cleanUp();
}

// Returns the projectile list
Projectile** ProjectileHandler::getProjList(){return projs;}

// Return size
int ProjectileHandler::getSize(){return size;}

// Returns last active 
int ProjectileHandler::getLastActive(){return lastActive;}

//Pass in a constructor Projectile to be contained by the list
void ProjectileHandler::addNewProjectile(Projectile* newProjectile)
{
	for (int i = 0; i < size; i++){
		// Check if current is null
		if (projs[i] == NULL){
			delete projs[i];
			projs[i] = newProjectile;
			projs[i]->setAlive(true);
			return;
		}
		// If current projectile is dead, add in place
		else if (!projs[i]->getAlive()){
			delete projs[i];
			projs[i] = newProjectile;
			projs[i]->setAlive(true);
			return;
		}
	}

	// NOTE: this will not add the projectile if there is no space in the array 
}

void ProjectileHandler::updateProjectiles(float deltaTime, Handlers* handlers)
{
	// Update 
	lastActive = 0;
	for (int i = 0; i < size; i++){
		// Null and alive check 
		if (projs[i] != NULL && projs[i]->getAlive()){
			lastActive = i;
			projs[i]->determineNegligance();
			if(projs[i]->getNegligence())
				projs[i]->updateNegligableProjectile(deltaTime);
			else
				projs[i]->updateProjectile(deltaTime, handlers);
			projs[i]->checkCollision(deltaTime, handlers);
		}
	}
}

// Draw all projectiles 
void ProjectileHandler::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	for (int i = 0; i <= lastActive; i++){
		// Null and alive check 
		if (projs[i] != NULL && projs[i]->getAlive()){
			projs[i]->draw(mgl, mAtlas);
		}
	}

	// Reset flat color here instead of every time a projectile draws
	mgl->setFlatColor(1.0f,1.0f,1.0f,1.0f);
}

// Draw all projectiles lights 
void ProjectileHandler::drawLight(GLHandler* mgl, TextureAtlas* mAtlas){
	for (int i = 0; i <= lastActive; i++){
		// Null and alive check 
		if (projs[i] != NULL && projs[i]->getAlive()){
			projs[i]->drawLight(mgl, mAtlas);
		}
	}

	// Reset flat color here instead of every time a projectile draws
	mgl->setFlatColor(1.0f,1.0f,1.0f,1.0f);
}

void ProjectileHandler::cleanUp()
{
	if (projs == NULL) return;
	for (int i = 0; i < size; i++){
		delete projs[i];
		projs[i] = NULL;
	}
	delete[] projs;
	projs = NULL;
}