#include "ParticleHandler.h"


ParticleHandler::ParticleHandler()
{
	size = 700;
	parts = new Particle[size];
}

ParticleHandler::~ParticleHandler()
{
	delete[] parts;
	parts = NULL;
}

// Returns the particle list
Particle* ParticleHandler::getList(){
	return parts;
}

// Return size
int ParticleHandler::getSize(){
	return size;
}

// Add new particle to list of particle 
Particle* ParticleHandler::add(int image, float x, float y, float originX, float originY, 
	float direcX, float direcY, float speed, float lifeTime){
	return add(image,x,y,originX,originY,direcX,direcY,speed,lifeTime,0.0f,0.0f);
}

// Add new particle to list of particle 
Particle* ParticleHandler::add(int image, float x, float y, float originX, float originY, 
	float direcX, float direcY, float speed, float lifeTime, float rotationSpeed, float scaleSpeed){
	
	// Return if particle is not on screen 
	if (!screenRec->contains(x,y)) return NULL;
		
	for (int i = 0; i < size; i++){
		if (!parts[i].getValid()){
			parts[i].reset();
			parts[i].setImageId(image);
			parts[i].setLoc(x,y);
			parts[i].setOrigin(originX, originY);
			parts[i].setDirec(direcX, direcY);
			parts[i].setSpeed(speed);
			parts[i].setLifeTime(lifeTime);
			parts[i].setRotSpeed(rotationSpeed);
			parts[i].setScaleSpeed(scaleSpeed);
			return &parts[i];
		}
	}
	return NULL;
}

// Add by clone
Particle* ParticleHandler::add(Particle* p){
	for (int i = 0; i < size; i++){
		if (!parts[i].getValid()){
			parts[i].clone(p);
			parts[i].setValid(true);
			return &parts[i];
		}
	}
	return NULL;
}

// Update current particle states 
void ParticleHandler::update(float deltaTime){
	for (int i = 0; i < size; i++)
		parts[i].update(deltaTime);
}

// Draw all particles 
void ParticleHandler::draw(GLHandler* mgl, GameAtlas* mAtlas){
	for (int i = 0; i < size; i++)
		parts[i].draw(mgl,mAtlas);
}
