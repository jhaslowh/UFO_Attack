#pragma once
#include "Particle.h"
#include "Rec.h"

class ParticleHandler
{
	private:
	// Current size of list
	int size;

	// List of particles 
	Particle* parts;

public:
	// Screen rec reference, used to make sure new particles 
	// are on screen. Do not edit in this class. It is a reference
	// to the one in the LevelProps
	Rec* screenRec;

	ParticleHandler();
	~ParticleHandler();

	// Returns the particle list
	Particle* getList();

	// Return size
	int getSize();

	// Add new particle to list of particle 
	Particle* add(int image, float x, float y, float originX, float originY, 
		float direcX, float direcY, float speed, float lifeTime);
	// Add new particle to list of particle 
	Particle* add(int image, float x, float y, float originX, float originY, 
		float direcX, float direcY, float speed, float lifeTime, 
		float rotationSpeed, float scaleSpeed);
	// Add by clone
	Particle* add(Particle* p);
	
	// Update current particle states 
	void update(float deltaTime);

	// Draw all particles 
	void draw(GLHandler* mgl, GameAtlas* mAtlas);
};

