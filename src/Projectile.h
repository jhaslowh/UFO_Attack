#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include "GLHandler.h"
#include "GameAtlas.h"
#include "Handlers.h"
#include "Point.h"
#include "LevelProperties.h"
#include "Camera2D.h"

//Projectile Types Include
//Type 1 = Bullet
//Type 2 = Missle
//Type 3 = Non-Standard Moving Object (cows/rocks/cars/people)
//Type 4 = Beam

#define PROJT_BULLET 1
#define PROJT_MISSILE 2
#define PROJT_NSMO 3
#define PROJT_BEAM 4
#define PROJT_TEST 5

// Collision type definitions
#define P_PLAYER_COLL 1
#define P_GROUND_COLL 2
#define P_ENEMY_COLL 3 

// Fired by ___
// PFB = Projectile fired by
#define PFB_PLAYER 1
#define PFB_ENEMY 2

class Projectile
{
protected:
	glm::vec4 velocityVectors;
	short projectileType;
	float previousX;
	float previousY;
	float currentX;
	float currentY;
	float xVector; //The vectors are a function of velocity in the direction of launch towards clicked location
	float yVector;
	int spread;
	int speed;
	int mass; //Mass is the weight of the object
	int size; //Size is relative, no need to calculate area just use different ints to determine whether it is small/medium/large and so on
	bool negligence;
	int UID;//Unique identifer number
	float damage;
	int firedBy;

	// --------------------
	// Drawing properties 
	// --------------------

	int imageId;
	int imageGlowId;
	float offsetX, offsetY;
	float glowOffsetX, glowOffsetY;
	// Used to determine if projectile should be drawn 
	bool drawProj;
	float rotation;
	GLfloat drawColor[4];

	// -----------
	// States 
	// -----------
	bool alive;
	bool doesExplode;
	bool isColliding;
	// Set to true to kill the projectile on impact 
	bool diesOnImpact;

public:
	Projectile();
	Projectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode, int Spread);
	Projectile(short ProjectileType, float CurrentX, float CurrentY, float xLocation, float yLocation);
	virtual ~Projectile();
	//Constructor and deconstructor

	//Clone all the properties from the sent projectiles into this one
	void clone(Projectile* p);

	//Clears all data points
	void reset();

	void resetProjectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float xLocation, float yLocation, int speed, bool doesExplode);
	
	//Base update methods, to be inherited and edited within each projectile
	//For different projectiles, if you ask how you want them to behave I can write their update methods
	//IE: arc'ed projectile, beam, fast moving, light, heavy
	virtual void updateProjectile(float deltaTime, Handlers* handlers);
	virtual void updateNegligableProjectile(float deltaTime);
	virtual void determineNegligance();

	// Draw projectile to screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Draw projectile light to screen
	virtual void drawLight(GLHandler* mgl, TextureAtlas* mAtlas);

	// Called when projectile collides with something
	virtual void collide(Point* p, Handlers* handlers, int collType);

	short getProjectileType();
	float getCurrentX();
	float getCurrentY();
	float getPrevX();
	float getPrevY();
	bool getNegligence();
	int getUID();
	bool getAlive();
	float getDamage();
	int getFiredBy();
	//Getter methods, 

	void setUID(int newUID);
	void setAlive(bool value);
	void setImageId(int value);
	void setImageGlowId(int value);
	void setOffset(float x, float y);
	void setGlowOffset(float x, float y);
	void setDamage(float value);
	void setFiredBy(int value);
	void setExplodes(bool value);
	void setDrawColor(GLfloat* color);
	//Setter methods 

private:

	// Setup basic values for all variables 
	void initValues();
};