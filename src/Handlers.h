#pragma once
#include <stdlib.h>
#include "Ground.h"

class Handlers
{
public:

	// Handlers for each handler we  need in the game.
	// These should be changed from void* to their 
	// actual types when implemented;
	void* enemyHandler;
	void* projHandler;
	void* sceneryHandler;
	Ground* ground;

	Handlers();
	~Handlers();
};

