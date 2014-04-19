#include "BasicExplosion.h"

BasicExplosion::BasicExplosion() : Explosion()
{
	// --- Drawing 
	imageID = GI_BASIC_EXPL_1;
	locX = locY = 0.0f;
	originX = originY = 30.0f;
	rotation = 0.0f;

	// --- Exploding
	damage = 10.0f;
	range = 35.0f;
	explTime = 0.25f;			
	cexplTime = 0.0f;		

	// --- Animation
	animates = true;
	frames = 4;
	cframe = 0;
	frameTime = 0.05f;
	cframeTime = 0.0f;
}

BasicExplosion::~BasicExplosion()
{

}
