#pragma once
#include "NPC.h"
class NPCHandler
{
	// Head object for class
	NPC* head;
	// Iterator object, dont need to save it,
	// but will make out code faster. 
	NPC* itr;

public:
	NPCHandler();
	~NPCHandler();

	// Get number of objects 
	int getSize();

	// Get head objective 
	NPC* getHead();
	// Set the head for the handler
	void setHead(NPC* obj);

	// Add an object to the list 
	void add(NPC* obj);

	// Remove object from handler
	void remove(NPC* obj);

	// Update objects
	void update(float deltaTime, Handlers* handlers);

	// Draw object lights 
	void drawLight(GLHandler* mgl, GameAtlas* mGame);

	// Draw objects
	void draw(GLHandler* mgl, GameAtlas* mGame);
};

