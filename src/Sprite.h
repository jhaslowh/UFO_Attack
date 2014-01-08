#pragma once
#include <glew.h>
#include "FileHelper.h"
#include "GLHandler.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Sprite
{
private:
	// Drawing variables 
	GLushort indicies[6];
	GLfloat verts[8];
	GLfloat cords[8];
	GLint textureID;
	float pos_x;
	float pos_y;
	float rotation;
	float scale;
	float origin_x;
	float origin_y;
	GLfloat color[4];

public:
	Sprite();
	~Sprite();

	// Setup the sprites verticies, coords, and texture 
	void setup(float, float, char*);

	// Set the position of the sprite 
	void setPosition(float,float);
	// Set the rotation of the sprite 
	void setRotation(float);
	// Set the scale of the sprite 
	void setScale(float);
	// Set the origin of the sprite 
	void setOrigin(float,float);
	// Set the RGB color 
	void setColor(const float,const float,const float);
	// Set the RGBA color
	void setColor(const float,const float,const float,const float);
	// Set the alpha value 
	void setAlpha(const float);

	// Call to draw the sprite 
	void draw(GLHandler);
};

