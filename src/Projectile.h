#pragma once
#include "GLHandler.h"
#include "TextureAtlas.h"
#include "GameAtlas.h"

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

class Projectile
{
private:
	short projectileType;
	float previousX;
	float previousY;
	float currentX;
	float currentY;
	float xVector; //The vectors are a function of velocity in the direction of launch towards clicked location
	float yVector;
	int mass; //Mass is the weight of the object
	int size; //Size is relative, no need to calculate area just use different ints to determine whether it is small/medium/large and so on
	bool negligence;
	int UID;//unique identifer number
public:
	Projectile();
	Projectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float XVector, float YVector);
	~Projectile();
	//constructor and deconstructor
	
	//base update methods, to be inherited and edited within each projectile
	//For different projectiles, if you ask how you want them to behave I can write their update methods
	//ie: arc'ed projectile, beam, fast moving, light, heavy
	void updateProjectile(float deltaTime);
	void updateNegligableProjectile();
	void determineNegligance();

	// Draw projectile to screen
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	short getProjectileType();
	float getCurrentX();
	float getCurrentY();
	bool getNegligence();
	int getUID();
	//getter methods, 

	void setUID(int newUID);
	
};