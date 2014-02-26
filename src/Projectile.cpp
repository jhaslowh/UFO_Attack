#include "Projectile.h"

//Projectile Types Include
//Type 1 = Bullet
//Type 2 = Missle
//Type 3 = Non-Standard Moving Object (cows/rocks/cars/people)
//Type 4 = Beam

Projectile::Projectile()
{
	projectileType = 0;
	previousX = 0.0f;
	previousY = 0.0f;
	currentX = 0.0f;
	currentY = 0.0f;
	xVector = 0.0f;
	yVector = 0.0f;
	mass = 0;
	size = 0;
	negligence = false;
	UID = -1;
}

Projectile::Projectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float XVector, float YVector)
{
	projectileType = ProjectileType;
	previousX = CurrentX;
	previousY = CurrentY;
	currentX = CurrentX;
	currentY = CurrentY;
	xVector = XVector;
	yVector = YVector;
	mass = Mass;
	size = Size;
	negligence = false;
	UID = -1;
}

Projectile::~Projectile()
{

}

//UpdateProjectile does the heavier stuff for projectiles with complicated movement, and will handle collision detection
//This will act as a default in case a projectile doesn't have its own updateProjectile method
void Projectile::updateProjectile(float deltaTime)
{
	previousY = currentY;
	previousX = currentX;
	yVector-=((xVector + yVector)*mass)*-3;
	xVector-=((xVector + yVector)*size)*-1;
	//There should be a very large section for collision based interactions
	//Stuff like rolling on the ground and bouncing
	currentX+=xVector;
	currentY+=yVector;
}

//This method does not need to be overloaded for different projectiles, it is the same for every unphysiced projectile
void Projectile::updateNegligableProjectile()
{
	previousY = currentY;
	previousX = currentX;
	currentX+=xVector;
	currentY+=yVector;
}

//This will need to have some cases for each different kind of projectile, but there are some basic reasons to be negligable here
void Projectile::determineNegligance()
{
	if(projectileType == 4)
		negligence = true; //A beam typed weapon would not be affected by gravity or wind resistance
	else if(((xVector+yVector)*mass) >= 500)
		negligence = true; //This is an extreme example of a case at which a projectile has enough inertia that it will take its course before noticable change to its trajectory
	else if(size < 1 && (xVector+yVector) >= 200)
		negligence = true; //A sufficiently small projectile that is moving fast enough will not be affected by wind resistance and can most likely fulfill its course before gravity has any noticable effect
	//Need to figure out all the collision stuff, but here should be
	//if(projectile == Colliding)
	//  negligence = false;
}


// Draw projectile to screen
void Projectile::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	// Uncomment to draw 
	mAtlas->draw(mgl, GI_CRATE, currentX, currentY, 1.0f, 0.0f, 0.0f, 0.0f);

	// You will want to change this to 
	//mAtlas->draw(mgl, [Item index to draw], currentX, currentY, 1.0f, [rotation], [origin x], [origin y]);
}

short Projectile::getProjectileType()
{
	return projectileType;
}
float Projectile::getCurrentX()
{
	return currentX;
}
float Projectile::getCurrentY()
{
	return currentY;
}
bool Projectile::getNegligence()
{
	return negligence;
}
int Projectile::getUID()
{
	return UID;
}

void Projectile::setUID(int newUID)
{
	UID = newUID;
}