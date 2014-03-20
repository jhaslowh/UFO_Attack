#include "ProjectileTemplate.h"


ProjectileTemplate::ProjectileTemplate()
{
	speed = 1000.0f;
	imageId = -1;
	imageOrigin[0] = 0.0f;
	imageOrigin[1] = 0.0f;
	glowImageId = -1;
	glowImageOrigin[0] = 0.0f; 
	glowImageOrigin[1] = 0.0f; 
	explodes = false;
}

ProjectileTemplate::~ProjectileTemplate(){}
