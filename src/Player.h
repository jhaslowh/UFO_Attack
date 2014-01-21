#pragma once
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "GLHandler.h"
#include "Point.h"
#include "Collision.h"
#include "Sprite.h"
#include "Ground.h"

#define GRAVITY 980.0f

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

	float jumpt;	 // Time left in jump
	float jumpTime;  // Total time a jump takes 
    float yo;        // Original y location at begining of jump 
	float airT;      // Time that player has been in the air for 
	float minAirtForInAir; // Min time to count airT as being in air
  
	// States 
	bool alive;
    bool jumping;
	bool inAir;

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

	
	// Physics Helpers

	// Stop player if they are jumping
	void stopJump();

	// Call when the player hits the ground 
	void hitGround();

	// Call when the player hits a wall
	void hitWall();

	// Call when the player hits the ceiling 
	void hitCeiling();
};

