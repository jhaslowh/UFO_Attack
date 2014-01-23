#pragma once
#include <iostream>
#include <stdlib.h>
#include "Point.h"
#include "GLHandler.h"
#include "FileHelper.h"
#include "Collision.h"
#include "Sprite.h"

class Ground
{
	// List of ground points 
	Point* points;
	int pointCount;
	float groundDepth;

	// Drawing 
	Sprite grass;
	float grassLength;

	int indicieCount;
	GLushort* indicies;
	GLfloat* verts;
	GLfloat* cords;
	GLfloat color[4];
	GLuint textureID;

public:
	Ground();
	Ground(int count);
	~Ground();

	// Load texture
	void load();

	// Set point count
	// Do not use this to change the size of the point
	// arrays. It will erase the arrays. 
	void setPointCount(int count);
	// Set a specific point
	void setPoint(int index, Point p);
	// Get the ground points
	Point* getPoints();
	// Get a single point
	Point getPoint(int index);
	// Get the number of ground points
	int getPointCount();

	// Draw ground 
	void draw(GLHandler* mgl);
};

