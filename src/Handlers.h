#pragma once
#include <stdlib.h>
#include "Ground.h"

class Handlers
{
public:

	// Handlers for each handler we  need in the game.
	void* npcHandler;
	void* projHandler;
	void* sceneryHandler;
	Ground* ground;
	void* camera;
	void* levelProps;
	void* player;

	Handlers();
	~Handlers();
};

