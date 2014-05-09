#pragma once
#include "Rec.h"
#include "Handlers.h"
#include "GLHandler.h"
#include "GameAtlas.h"
#include "Collision.h"
#include "Player.h"
#include "UFO.h"

#define GRAVITY 980.0f

// NPC types
#define NPC_ANIMAL 1
#define NPC_HUMAN 2

// Global abduction properties
#define ABDUCT_START_SPEED 200.0f
#define ABDUCT_MAX_SPEED 300.0f
#define ABDUCT_ACCEL 50.0f

class NPC
{
protected:

	float locX, locY;
	float spawnX, spawnY;
	float width, height;
	float originX, originY;
	float rotation;
	float scale;
	int imageID;
	Rec bounds;				// Bounds used when making collision rec
	Rec collisionRec;		// Collision rec to check collisions with 

	// States 
	bool canBeAbducted;
	bool beingAbducted;
	bool alive;
	bool mdraw; // Toggle whether the npc will draw this iteration 
	bool justDied;
	bool justAbduct;

	float health;
	float healthMax;
	int type;
	std::string stype;

	// Abduction properties
	float cAbductSpeed;
	// Change this to slow down or speed up abductions
	float abductRate;		

public:
	NPC* next;

	NPC();
	virtual ~NPC();

	// Set the location of the npc 
	void setLocation(float x, float y);
	float getX();
	float getY();
	float getSpawnX();
	float getSpawnY();
	std::string getSType();
	// get the npc type as a string
	// Set the width and height of the npc
	void setSize(float w, float h);
	float getWidth();
	float getHeight();
	// Set the origin point of the npc
	void setOrigin(float x, float y);
	// Set the rotation of the npc
	void setRotation(float r);
	float getRotation();
	// Set the scale of the npc
	void setScale(float s);
	float getScale();
	// Set the image id to draw for this npc
	void setImageID(int id);
	int getImageID();
	bool getAlive();
	bool getDraw();
	bool getJustDied();
	bool getJustAbduct();

	// Returns npc collision rec
	virtual Rec* getCollisionRec();

	// Fix collision rec location 
	virtual void fixCollRec();

	// Update movement of the NPC 
	// This method should set the movement values for the npc.
	virtual void updateMovement(float deltaTime, Handlers* handlers);

	// Update collision of NPC 
	// This method should check if the npc is being abducted, if it is
	// it should ignore the movement from the update movement method and 
	// if it isnt, it should resolve the movement and collisions. 
	virtual void updateCollision(float deltaTime, Handlers* handlers);

	// Update game state of the npc object
	// Do any non movement or non collision detection updates
	// (weapons and the like) 
	virtual void update(float deltaTime, Handlers* handlers);

	// Draw any light this object has 
	virtual void drawLight(GLHandler* mgl, GameAtlas* mGame);

	// Draw object to the screen
	virtual void draw(GLHandler* mgl, GameAtlas* mGame);

	// Damage the npc by sent damage amout.
	// Will set npc to !alive if too much damage taken
	virtual void damage(float amount, Handlers* handlers);

	// Called when npc dies 
	virtual void onDeath(Handlers* handlers);

	// Called when npc is abducted
	virtual void onAbduct(Handlers* handlers);
};

