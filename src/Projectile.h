#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include "GLHandler.h"
#include "GameAtlas.h"
#include "Handlers.h"
#include "Point.h"
#include "LevelProperties.h"
#include "Camera2D.h"
#include "Explosion.h"
#include "ExplHandler.h"
#include "Ground.h"
#include "ParticleHandler.h"
#include "SoundHandler.h"

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
	// -------------------
	// Physics
	// -------------------
	short projectileType;
	float previousX;
	float previousY;
	float currentX;
	float currentY;
	float xVector; //The vectors are a function of velocity in the direction of launch towards clicked location
	float yVector;
	int speed;
	int mass; //Mass is the weight of the object
	int size; //Size is relative, no need to calculate area just use different ints to determine whether it is small/medium/large and so on
	bool negligence;
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

	// ---------------------
	// Particles
	// ---------------------
	bool smokeTrail;
	float partTime;

	// -----------
	// States 
	// -----------
	bool alive;
	bool doesExplode;
	Explosion explosion;
	// Set to true to kill the projectile on impact 
	bool diesOnImpact;

public:
	Projectile();
	virtual ~Projectile();

	//Clone all the properties from the sent projectiles into this one
	void clone(Projectile* p);

	// Returns a clone pointer of this projectile 
	virtual void* clone();
	
	//Base update methods, to be inherited and edited within each projectile
	//For different projectiles, if you ask how you want them to behave I can write their update methods
	//IE: arc'ed projectile, beam, fast moving, light, heavy
	virtual void updateProjectile(float deltaTime, Handlers* handlers);
	virtual void updateNegligableProjectile(float deltaTime);
	virtual void determineNegligance();

	// Check projectile collision 
	virtual void checkCollision(float deltaTime, Handlers* handlers);

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
	bool getAlive();
	float getDamage();
	int getFiredBy();
	Explosion getExplosion();
	Explosion* getExplRef();
	//Getter methods, 

	void setSize(int newSize);
	void setType(short type);
	void setAlive(bool value);
	void setImageId(int value);
	void setImageGlowId(int value);
	void setPosition(float x, float y);
	void setOffset(float x, float y);
	void setGlowOffset(float x, float y);
	void setDamage(float value);
	void setFiredBy(int value);
	void setExplodes(bool value);
	void setDrawColor(GLfloat* color);
	void setDrawColor(float r, float g, float b, float a);
	void setExplosion(Explosion e);
	void setSmokeTrail(bool value);
	void setSpeed(int s);
	void setDirec(float x, float y);
	//Setter methods 

private:

	// Setup basic values for all variables 
	virtual void initValues();
};