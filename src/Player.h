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
#include "SceneryHandler.h"
#include "SceneryObject.h"

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
	// Camera 
	float cameraOffsetY;

	// --------------------
	// Collision Properties 
	// --------------------
	// Collision lines, used for check collision 
	// with the ground. 
	Point vertA;      // Vertical checking line point one and two
	Point vertB;      // 
	Point horA;       // Horozontal checking line point one and two
	Point horB;       // 
	float waistHeight;
	Point vertBotA;   // Below body vertical checking line point one and two
	Point vertBotB;   // 
	float depthForDepthCheck;
	// Collision Rectangle, this holds the basic properties of the collision 
	// rectangle for the player. Should not be used for collision. Copy
	// these properties into another rectangle before checking. 
	Rec collRec;		
	// Collision Rectangles used for collision detection.
	Rec collRecX;		// Collision rec with just new x
	Rec collRecY;		// Collision rec with just new y
	Rec collRecXY;		// Collision rec with both new x and y

	// -------
	// Physics
	// -------
	float nextX, nextY;
	float movementSpeed;
	float direcX;

	float jumpt;	 // Time left in jump
	float jumpTime;  // Total time a jump takes 
    float yo;        // Original y location at begining of jump 
	float airT;      // Time that player has been in the air for 
	float minAirtForInAir; // Min time to count airT as being in air
  
	// ------
	// States 
	// ------
    bool jumping;
	bool inAir;
	bool inUFO;

	// ------
	// Health
	// ------ 
	float health;
	float maxHealth;

	// ---------------------
	// Texture and animation 
	// ---------------------
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
	// Set max health
	void setMaxHealth(float value);
	// Get max health
	float getMaxHealth();
	// Set health
	void setHealth(float value);
	// Get health
	float getHealth();

	// Functions 

	// initialize player
	void init(float screen_width, float screen_height);

	// Load player (use for textures)
	void load(GLHandler* mgl);

	// Unload textures
	void unload();

	// Update level state
	void update(float deltaTime, Handlers* handlers);

	// Check collisions 
	void checkCollision(Handlers* handlers);

	// Resolve any collisions found 
	void resolveCollision(Handlers* handlers);
	
	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw player
	void draw(GLHandler* mgl);

	// Draw player hud
	void drawHud(GLHandler* mgl);

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

	// Set health back to max health
	void replinishHealth();

	// Check if player is alive 
	bool alive();

	// Apply damage to health
	void applyDamage(float damage);

private:

	// Set the given collision rectangle to the given location
	void setCollRec(Rec* r, float x, float y);
};

