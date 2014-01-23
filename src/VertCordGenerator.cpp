#include "VertCordGenerator.h"


// Construct a new generator 
VertCordGenerator::VertCordGenerator()
{
	vsize = 20;
	csize = 20;
	ccount = 0;
	vcount = 0;
	sheet_width = 512;
	sheet_height = 512;
	sheet_scale = 1.0f;
	vindex = -1;
	cindex = -1;
	
	verts = new GLfloat[vsize]; //(GLfloat*)malloc(sizeof(GLfloat) * vsize);
	cords = new GLfloat[csize];

	for (int i = 0; i < vsize; i++)
		verts[i] = 0.0f;
	for (int i = 0; i < csize; i++)
		cords[i] = 0.0f;
}

VertCordGenerator::VertCordGenerator(float width, float height)
{
	vsize = 20;
	csize = 20;
	ccount = 0;
	vcount = 0;
	sheet_width = width;
	sheet_height = height;
	sheet_scale = 1.0f;
	vindex = -1;
	cindex = -1;
	
	verts = new GLfloat[vsize]; //(GLfloat*)malloc(sizeof(GLfloat) * vsize);
	cords = new GLfloat[csize];
	
	for (int i = 0; i < vsize; i++)
		verts[i] = 0.0f;
	for (int i = 0; i < csize; i++)
		cords[i] = 0.0f;
}

// Free resources 
VertCordGenerator::~VertCordGenerator(){
	delete[] verts;
	delete[] cords;
}

// Set the width and height of the texture sheet
void VertCordGenerator::setWidthHeight(const float w,const float h){
	sheet_width = w; sheet_height = h;
}

// Set this if the texture is scaled when loaded 
void VertCordGenerator::setScale(const float s){
	sheet_scale = s;
}

// Add a frame to the generator. 
// Use the original sheet coordinates if the sheet was scaled. 
void VertCordGenerator::addFrame(float x, float y, float width, float height){
	// Resize coords if sheet was scaled 
	x *= sheet_scale;
	y *= sheet_scale;
	width *= sheet_scale;
	height *= sheet_scale;
		
	// Check array size 
	if (ccount + 8 > csize)
		resizeCoords(csize + 100);
	ccount += 8;

	// Add new coords 
	cords[++cindex] = x / sheet_width; cords[++cindex] = y / sheet_height;
	cords[++cindex] = x / sheet_width; cords[++cindex] = (y + height) / sheet_height;
	cords[++cindex] = (x + width) / sheet_width; cords[++cindex] = (y + height) / sheet_height;
	cords[++cindex] = (x + width) / sheet_width; cords[++cindex] = y / sheet_height;

		
	// Check array size 
	if (vcount + 8 > vsize)
		resizeVerts(vsize + 100);
	vcount += 8;

	// Add new vertexes 
	verts[++vindex] = 0.0f; verts[++vindex] = 0.0f;
	verts[++vindex] = 0.0f; verts[++vindex] = height;
	verts[++vindex] = width; verts[++vindex] = height;
	verts[++vindex] = width; verts[++vindex] = 0.0f;
}

// Get the coord array.
// This will return an array shrunk to fit the actual
// number of elements in the array. 
GLfloat* VertCordGenerator::getCoords(){
	GLfloat* ncords = new GLfloat[ccount];
	for (int i = 0; i < ccount; i++)
		ncords[i] = cords[i];
	return ncords;
}

// Get the vertex array 
// This will return an array shrunk to fit the actual
// number of elements in the array. 
GLfloat* VertCordGenerator::getVertices(){
	GLfloat* nverts = new GLfloat[vcount];
	for (int i = 0; i < vcount; i++)
		nverts[i] = verts[i];
	return nverts;
}

// Resize the vert array
void VertCordGenerator::resizeVerts(int nsize){
	// Set new size 
	vsize = nsize;

	// Check if their is loss of data
	if (nsize < vcount) vcount = nsize;
	
	// Put data into new array 
	GLfloat* nverts = new GLfloat[nsize];
	for (int i = 0; i < vcount; i++)
		nverts[i] = verts[i];

	// Swap pointers
	delete[] verts;
	verts = nverts;
}

// Resize the coord array 
void VertCordGenerator::resizeCoords(int nsize){
	// Set new size
	csize = nsize;

	// Check if their is loss of data
	if (nsize < ccount) ccount = nsize;
	
	// Put data into new array 
	GLfloat* ncords = new GLfloat[nsize];
	for (int i = 0; i < ccount; i++)
		ncords[i] = cords[i];

	// Swap pointers
	delete[] cords;
	cords = ncords;
}