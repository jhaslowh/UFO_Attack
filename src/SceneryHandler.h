#pragma once
#include "SceneryObject.h"
#include "Handlers.h"
#include "TallCrate.h"
#include "Sign.h"
#include "LongCrate.h"
#include "HayBale.h"
#include "Fence.h"
#include "Crate.h"
#include "Tree.h"
#include "Barn.h"
#include "HouseBlue.h"
#include "HouseBrown.h"
#include "Barracks.h"

class SceneryHandler
{
	// Head object for class
	SceneryObject* head;
	
	// Iterators for update and draw
	SceneryObject* ditr;
	SceneryObject* uitr;

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

	// Add by name
	bool add(std::string name, std::string args, float x, float y);

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

