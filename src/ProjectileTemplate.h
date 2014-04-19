#pragma once
#include "glew.h"
#include "Explosion.h"

class ProjectileTemplate
{
public:
	float speed;
	int imageId;
	float imageOrigin[2];
	int glowImageId;
	float glowImageOrigin[2]; 
	GLfloat drawColor[4];
	bool explodes;
	Explosion* explosion;

	ProjectileTemplate();
	~ProjectileTemplate();

	// Set the color for the template
	void setColor(float r, float g, float b, float a);
};

