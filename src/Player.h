#pragma once
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "GLHandler.h"
#include "Point.h"
#include "Collision.h"
#include "Sprite.h"
#include "Ground.h"

class Player
{
	// Basic properties 
	float locX, locY;
	float width, height;
	float originX, originY;
	Sprite sprite;

	// Collision Properties 
	// Collision lines, used for check collision 
	// with the ground. 
	Point vertA;      // Vertical checking line point one and two
	Point vertB;      // 
	Point horA;       // Horozontal checking line point one and two
	Point horB;       // 
	Point vertBotA;   // Below body vertical checking line point one and two
	Point vertBotB;   // 

	// Physics
	float nextX, nextY;
	float movementSpeed;
	float direcX;

public:
	Player();
	~Player();

	// Getters and setters
	void setLocation(float x, float y);
	float getX();
	float getY();

	// Functions 

	// initialize level
	void init(float screen_width, float screen_height);

	// Load level (use for textures)
	void load();
	
	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Update level state
	void update(float deltaTime);

	// Check collisions 
	void checkCollision(Ground* ground);

	// Resolve any collisions found 
	void resolveCollision();

	// Draw level 
	void draw(GLHandler* mgl);
};

