#pragma once
#define GLEW_STATIC
#include <glew.h>
#include "FileHelper.h"
#include "GLHandler.h"

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

	void set(float, float, float, float, char*);

	// Call to draw the sprite 
	void draw(GLHandler);
};

