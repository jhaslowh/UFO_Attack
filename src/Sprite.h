#pragma once
#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "FileHelper.h"
#include "GLHandler.h"

class Sprite
{
private:
	// Drawing variables 
	GLushort indicies[6];
	GLfloat verts[8];
	GLfloat cords[8];
	GLuint textureID;
	float locX;
	float locY;
	float rotation;
	float scale;
	float originX;
	float originY;
	float width;
	float height;
	GLfloat color[4];

public:
	Sprite();
	~Sprite();

	// Unload sprite 
	void unload();

	// Setup the sprites verticies, coords, and texture 
	void setup(float width, float height);
	void setup(float width, float height, std::string file);

	// Set the position of the sprite 
	void setPosition(float,float);
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	// Set the rotation of the sprite 
	void setRotation(float);
	float getRotation();
	// Set the scale of the sprite 
	void setScale(float);
	float getScale();
	// Set the origin of the sprite 
	void setOrigin(float,float);
	// Set the RGB color 
	void setColor(const float,const float,const float);
	// Set the RGBA color
	void setColor(const float,const float,const float,const float);
	// Set the alpha value 
	void setAlpha(const float);
	float getAlpha();
	// Get the width of the sprite
	float getWidth();
	// Get the height of the sprite 
	float getHeight();
	// Call to get image id
	GLuint getImageID();

	// Call to clip part of the image off. 
	// Can be fixed later with restore().
	// xPer: x percentage of image to use [0-1]
	// yPer: y percentage of image to use [0-1]
	void clip(float xPer, float yPer);

	// Fix the image if it was cliped; 
	void restore();

	// Prebind the vertex and texture cord buffers. 
	// Along with bind the texture, so you can render 
	// many copies of the sprite quickly. 
	void bind(GLHandler* mgl);

	// Draw the sprite 
	void draw(GLHandler);
	// Draw the sprite at offset
	void draw(GLHandler mgl, float offx, float offy);

	// Use to draw copies of the sprite faster
	// Must call bind() first. 
	void drawFast(GLHandler* mgl);
	// Use to draw copies of the sprite faster.
	// Draw at offset 
	// Must call bind() first. 
	void drawFast(GLHandler* mgl, float offx, float offy);
};
