#pragma once
#include "Explosion.h"

class ExplHandler
{
	// Head explosion object 
	Explosion* head;

public:
	ExplHandler();
	~ExplHandler();

	// Add new explosion to hander
	// This method will clone the sent pointer. So 
	// do not send it pointers that you do not delete. 
	void add(Explosion* e);

	// Remove explosion from handler
	void remove(Explosion* e);

	// Update explosion object states 
	void update(float deltaTime);

	// Draw explosion objects 
	void draw(GLHandler* mgl, GameAtlas* mAtlas);
};

