#pragma once
#include "Explosion.h"

class ExplHandler
{
	// Current size of list
	int size;
	// Last active element in list 
	int lastActive;

	// List of explosions 
	Explosion* expls;

public:
	ExplHandler();
	~ExplHandler();

	// Return size
	int getSize();

	// Returns last active 
	int getLastActive();

	// Returns the double linked list of the explosions
	Explosion* getExpls();

	// Add new explosion to hander
	// This method will clone the sent pointer. So 
	// do not send it pointers that you do not delete. 
	void add(Explosion* e);

	// Update explosion object states 
	void update(float deltaTime);

	// Draw explosion objects 
	void draw(GLHandler* mgl, GameAtlas* mAtlas);
};

