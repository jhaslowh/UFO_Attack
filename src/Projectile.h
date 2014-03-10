#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include "GLHandler.h"
#include "GameAtlas.h"
#include "Handlers.h"
#include "Point.h"

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
	bool alive;
	bool doesExplode;
	bool isColliding;

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
	void updateProjectile(float deltaTime);
	void updateNegligableProjectile(float deltaTime);
	void determineNegligance();

	// Draw projectile to screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

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
	//Getter methods, 

	void setUID(int newUID);
	void setAlive(bool value);
	//Setter methods 
	
};