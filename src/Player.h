#pragma once
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "GLHandler.h"
#include "Point.h"
#include "Collision.h"
#include "Sprite.h"
#include "Handlers.h"
#include "UFO.h"
#include "GameAtlas.h"
#include "Camera2D.h"
#include "PlayerAtlas.h"

#define GRAVITY 980.0f

// Player animation states
#define PLAYERS_RUN 0
#define PLAYERS_IDLE 1
#define PLAYERS_AIR 2

class Player
{
	// Basic properties 
	float locX, locY;
	float originX, originY;

	// Collision Properties 
	// Collision lines, used for check collision 
	// with the ground. 
	Point vertA;      // Vertical checking line point one and two
	Point vertB;      // 
	Point horA;       // Horozontal checking line point one and two
	Point horB;       // 
	Point vertBotA;   // Below body vertical checking line point one and two
	Point vertBotB;   // 
	// Collision Rectangle, this holds the basic properties of the collision 
	// rectangle for the player. Should not be used for collision. Copy
	// these properties into another rectangle before checking. 
	Rec collRec;		
	// Collision Rectangles used for collision detection.
	Rec collRecX;		// Collision rec with just new x
	Rec collRecY;		// Collision rec with just new y
	Rec collRecXY;		// Collision rec with both new x and y

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
	bool inUFO;

	// Camera 
	float cameraOffsetY;

	// Texture and animation 
	PlayerAtlas playerAtlas; // Atlas used to draw images
	float width, height;
	bool lookingRight;		// Will be true if the player is facing right
	int animationState;		// Animation states 
	// Running frame properties
	int runFrameCount;		// Total number of run frames		
	int runFrame;			// Current run frame
	float runFrameTime;		// Time per run frame
	float cRunFrameTime;	// Current run frame time 
	// Other frames 
	int idleFrame;
	int jumpFrame;

public:

	UFO* ufo;

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

	// Update level state
	void update(float deltaTime, Handlers* handlers);

	// Check collisions 
	void checkCollision(Handlers* handlers);

	// Resolve any collisions found 
	void resolveCollision(Handlers* handlers);
	
	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw level 
	void draw(GLHandler* mgl, GameAtlas* mGame);

	
	// Physics Helpers

	// Stop player if they are jumping
	void stopJump();

	// Call when the player hits the ground 
	void hitGround();

	// Call when the player hits a wall
	void hitWall();

	// Call when the player hits the ceiling 
	void hitCeiling();

	// Called when the player is dropped from the ship
	void dropFromShip();

private:

	// Set the given collision rectangle to the given location
	void setCollRec(Rec* r, float x, float y);
};

