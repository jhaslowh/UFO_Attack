#pragma once
#include <iostream>
#include <stdlib.h>
#include "Point.h"
#include "GLHandler.h"
#include "FileHelper.h"
#include "Collision.h"
#include "Sprite.h"

#define GROUND_DIRT 0
#define GROUND_CEMENT 1 

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
	int groundType;

	int indicieCount;
	GLushort* indicies;
	GLfloat* verts;
	GLfloat* cords;
	GLfloat color[4];
	GLuint textureID;

public:
	Ground(int type);
	~Ground();
	
	// This will have no effect if called after load is called
	void setType(int type);
	int getType();

	// Load texture
	void load();
	// Unload ground
	void unload();

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
	// Get bottom most point value
	float getBottomMost();
	// Get top mose point value
	float getTopMost();

	// Draw ground light layer
	void drawLight(GLHandler* mgl);
	// Draw ground 
	void draw(GLHandler* mgl);

private:
	// Call to fix the vertex, index, and cord arrays 
	void fixArrays();
};

