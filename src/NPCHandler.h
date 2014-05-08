#pragma once
#include "NPC.h"
#include "NPCSoldier.h"
#include "NPCHeavySoldier.h"
#include "NPCSniperSoldier.h"
#include "NPCStingerSoldier.h"
#include "NPCcow.h"
#include "NPCTank.h"
#include "NPCTurret.h"
#include "NPCSamSite.h"
#include "NPCCivilian.h"

class NPCHandler
{
	// Head object for class
	NPC* head;

	// Iteraters for game methods 
	NPC* uitr;		// For update thread
	NPC* ditr;		// For draw thread 

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

	// Add new object to list by name.
	// Returns true if name is matched. 
	bool addByName(std::string name, float x, float y);

	// Remove object from handler
	void remove(NPC* obj);

	// Update objects.
	// Returns number of living npc's.
	// [0-n]
	int update(float deltaTime, Handlers* handlers);

	// Draw object lights 
	void drawLight(GLHandler* mgl, GameAtlas* mGame);

	// Draw objects
	void draw(GLHandler* mgl, GameAtlas* mGame);

	int getAliveCount();
};

