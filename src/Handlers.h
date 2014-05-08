#pragma once
#include <stdlib.h>
#include "Ground.h"

class Handlers
{
public:

	// Handlers for each handler we  need in the game.
	void* npcHandler;
	void* projHandler;
	void* partHandler;
	void* sceneryHandler;
	void* explHander;
	Ground* ground;
	void* camera;
	void* levelProps;
	void* player;
	void* soundHandler;
	void* sky;
	void* scriptHandler;

	Handlers();
	~Handlers();
};

