#pragma once
#include "Handlers.h"
#include "GLHandler.h"
#include "GameAtlas.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "LevelCamera.h"

class UFO
{
	// Locations
	float locX, locY;
	float nextX, nextY;
	float originX, originY;

	// Collision properties 
	Point vertA;
	Point vertB;
	float minDistFromGround;  // Minimum distance UFO must be from ground 

	// Physics and movement
	float direcX, direcY;
	float speed;

public:
	UFO();
	~UFO();

	// Set location of the player 
	void setLocation(float x, float y);
	float getX();
	float getY();

	// Init 
	void init();
	
	// Load images
	void load();

	// Update UFO
	void update(float deltaTime, Handlers* handlers);

	// Check collision 
	void checkCollision(Handlers* handlers);

	// Resolve collisions
	void resolveCollision(Handlers* handlers);

	// Update ufo input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw UFO
	void draw(GLHandler* mgl, GameAtlas* mGame);
};

