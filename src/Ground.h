#pragma once
#include <stdlib.h>
#include "Point.h"
#include "GLHandler.h"

class Ground
{
	// List of ground points 
	Point* points;
	int pointCount;

	// Test drawing 
	GLushort* indicies;
	GLfloat* verts;
	GLfloat color[4];

public:
	Ground();
	Ground(int count);
	~Ground();

	// Set a specific point
	void setPoint(const int index, Point p);
	// Set the ground points 
	void setPoints(Point*);
	// Get the ground points
	Point* getPoints();
	// Get a single point
	Point getPoint(int index);
	// Get the number of ground points
	int getPointCount();

	// Draw ground 
	void draw(GLHandler* mgl);
};

