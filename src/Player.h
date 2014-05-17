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
#include "Weapon.h"
#include "PlayerLaserGun.h"
#include "PlayerShotgun.h"
#include "PlayerSMG.h"
#include "SaveData.h"
#include "StoreItems.h"
#include "GLColors.h"
#include "ProjectileHandler.h"
#include "SoundHandler.h"

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
	Rec cameraRec;
	float cameraEdge, cameraEdgeTop;
	Camera2D* camera;


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

	// --------------------
	// Gameplay properties
	// --------------------
	float health;
	float maxHealth;
	int animalAbductCount;
	int humanAbductCount;
	bool invincible;

	// --------------------
	// Interact button 
	// --------------------
	bool interact;

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
	int currentFrame;

	// Arm
	float armRotation;			// Rotation for arm 
	float armOffsetsR[24];
	float armOriginX, armOriginY;

	// ----------
	//    Hud 
	// ----------
	// Health
	float hudHealthScale;
	float hudHealthMaxScale;
	float hudHealthLocX;
	float hudHealthLocY;
	// Armor
	float hudArmorScale;
	float hudArmorMaxScale;
	float hudArmorLocX;
	float hudArmorLocY;
	// Shield
	float hudShieldScale;
	float hudShieldMaxScale;
	float hudShieldScaleY;
	float hudShieldLocX;
	float hudShieldLocY;
	// Score
	float scoreTextSize;
	float scoreTextOffsetX, scoreTextOffsetY;
	float locScoreAnimalX, locScoreAnimalY;
	float locScoreHumanX, locScoreHumanY;
	// Enemies left
	std::string elText;
	float elTextSize;
	float elTextX, elTextY;
	float elBarX, elBarY;
	float elScale;
	// Energy 
	float hudEnergyScale;
	float hudEnergyMaxScale;
	float hudEnergyLocX;
	float hudEnergyLocY;
	// Ammo
	float ammoLocX, ammoLocY;
	float ammoOffsetX, ammoOffsetY;

	// Colors
	GLfloat hudHealthColor[4];
	GLfloat hudShieldColor[4];
	GLfloat hudArmorColor[4];
	GLfloat hudBlack[4];
	GLfloat hudEnergyColor[4];

	// Hit recently
	float hitTime;
	float chitTime;

	// -------------
	// Weapon
	// -------------
	Weapon* weapon1;
	Weapon* weapon2;
	bool usingWeapon1;

public:

	UFO* ufo;

	Player(SaveData* savedata);
	~Player();

	// Getters and setters
	void setLocation(float x, float y);
	float getX();
	float getY();
	// Get x center loc
	float getCenterX();
	// Get y center loc
	float getCenterY();
	// Set max health
	void setMaxHealth(float value);
	// Get max health
	float getMaxHealth();
	// Set health
	void setHealth(float value);
	// Get health
	float getHealth();
	// Set player arm rotation
	void setArmRotation(float value);
	void incrAnimalCount(int value);
	void incrHumanCount(int value);
	int getAnimalCount();
	int getHumanCount();
	// Set enemy left bar size
	void setEnemyBarScale(float value);
	bool getInteract();
	Rec* getCollRec();

	// Functions 

	// initialize player
	void init(float screen_width, float screen_height, SaveData* savedata);

	// Load player (use for textures)
	void load(GLHandler* mgl);

	// Unload textures
	void unload();

	// Update level state
	void update(float deltaTime, Handlers* handlers);

	// Check collisions 
	void checkCollision(Handlers* handlers);

	// Resolve any collisions found. 
	// And do other nessesary updates that have to happen after movement checks.
	void update2(float deltaTime, Handlers* handlers);
	
	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw player
	void draw(GLHandler* mgl);

	// Draw player hud
	void drawHud(GLHandler* mgl);

	// Draw player objects that need the UIAtlas
	void drawUI(GLHandler* mgl, UIAtlas* mUI);

	// Draw player light
	void drawLight(GLHandler* mgl);

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

	// Check if the player is currently in the ufo
	bool isInUFO();

	// Make it so the player no longer takes damage
	void makeInvincible();

	// Make it so the player will take damage 
	void makeMortal();

	// Get ammo string for current weapon
	std::string getAmmoString();

private:

	// Set the given collision rectangle to the given location
	void setCollRec(Rec* r, float x, float y);
};

