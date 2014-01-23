#pragma once
#include "SceneryObject.h"
#include "Handlers.h"

class SceneryHandler
{
	SceneryObject** objects;
	int count;

public:
	SceneryHandler();
	SceneryHandler(int size);
	~SceneryHandler();

	// Set count. Set the number of scenerey objects
	// This will delete all objects 
	void setCount(int size);

	// Get number of scenery objects 
	int getCount();

	// Set the sent index as the sent pointer
	void set(int index, SceneryObject* obj);

	// Get the scenery object list 
	SceneryObject** getObjects();

	// Update objects
	void update(float deltaTime, Handlers* handlers);

	// Draw objects
	void draw(GLHandler* mgl, GameAtlas* mGame);
};

