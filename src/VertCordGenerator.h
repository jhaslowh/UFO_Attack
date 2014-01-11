#pragma once
#include <glew.h>
#include <stdio.h>
#include <stdlib.h>

/** 
 * This class is used to generate vertex and UV lists
 * for 2D sprites that share the same texture. 
 */
class VertCordGenerator
{
	// The current size of the arrays
	int vsize;
	int csize;
	// The count of the number of real items in the array 
	int ccount;
	int vcount;

	// Texture sizes 
	float sheet_width;
	float sheet_height;
	float sheet_scale;

	// Indexes 
	int vindex;
	int cindex;

	// Cords and verticies 
	GLfloat* verts;
	GLfloat* cords;

public:
	VertCordGenerator();
	VertCordGenerator(float width, float height);
	~VertCordGenerator();

	// Set the width and height of the texture sheet
	void setWidthHeight(const float,const float);
	// Set this if the texture is scaled when loaded 
	void setScale(const float);

	// Add a frame to the generator. 
	// Use the original sheet coordinates if the sheet was scaled. 
	void addFrame(float x, float y, float width, float height);

	// Get the coord array.
	// This will return an array shrunk to fit the actual
	// number of elements in the array. 
	GLfloat* getCoords();

	// Get the vertex array 
	// This will return an array shrunk to fit the actual
	// number of elements in the array. 
	GLfloat* getVertices();

private:

	// Resize the vert array
	void resizeVerts(int nsize);
	// Resize the coord array 
	void resizeCoords(int nsize);
};

