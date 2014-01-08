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
	GLfloat color[4];

public:
	Sprite();
	~Sprite();

	// Setup the sprites verticies, coords, and texture 
	void setup(float, float, char*);

	// Set position of the sprite 
	void setPosition(float,float);

	// Call to draw the sprite 
	void draw(GLHandler);


};

