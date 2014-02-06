#pragma once
#include "SceneryObject.h"
#include "Handlers.h"

class SceneryHandler
{
	// Head object for class
	SceneryObject* head;
	// Iterator object, dont need to save it,
	// but will make out code faster. 
	SceneryObject* itr;

public:
	SceneryHandler();
	~SceneryHandler();

	// Get number of scenery objects 
	int getSize();

	// Get head objective 
	SceneryObject* getHead();
	void setHead(SceneryObject* obj);

	// Add an scenery object to the list 
	void add(SceneryObject* obj);

	// Update objects
	void update(float deltaTime, Handlers* handlers);

	// Update objects input 
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw object lights 
	void drawLight(GLHandler* mgl, GameAtlas* mGame);

	// Draw objects
	void draw(GLHandler* mgl, GameAtlas* mGame);

	// Draw object ui elements 
	void drawUI(GLHandler* mgl, UIAtlas* mUI);
};

