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
	Point* itr;
	int pointCount;
	float groundDepth;

	// Drawing 
	Sprite grass;
	float grassLength;
	float textureScale;

	int indicieCount;
	GLushort* indicies;
	GLfloat* verts;
	GLfloat* cords;
	GLfloat color[4];
	GLuint textureID;

public:
	Ground();
	~Ground();

	// Load texture
	void load();

	// Add new point into the array 
	void add(Point* p);
	// Remove point by address 
	void remove(Point* p);
	// Get the ground points
	Point* getPoints();
	// Get a single point
	Point* getPoint(int index);
	// Fix the vertexes for the sent point
	void fixVertsForPoint(Point* p);
	// Get the number of ground points
	int getPointCount();

	// Draw ground 
	void draw(GLHandler* mgl);


private:
	// Call to fix the vertex, index, and cord arrays 
	void fixArrays();
};

