#pragma once
#include <glew.h>
#include "GLHandler.h"

class TextureAtlas
{
protected:
	// Drawing variables 
	GLushort indicies[6];
	GLfloat* verts;
	GLfloat* cords;
	GLint textureID;

	int indiceOffset;

public:
	TextureAtlas();
	~TextureAtlas();

	// Set the vertex list 
    void setVerts(GLfloat* v);
	// Set the cord list 
	void setCords(GLfloat* c);
	// Set the texture sheet id
	void setTexture(GLint value);
	// Set the offset of the index values 
	void setIndiceOffset(int value);

	// Call to bind the vertex and cord buffers
	void bindBuffers(GLHandler* mgl);
	// Call to bind the texture 
	void bindTexture(GLHandler* mgl);
	// Set the indicies for the atlas 
	void setIndicies(int index);

	// Draw functions 
	// Buffers and texture muse be bound before calling 
	// these functions or they will not work correctly. 
	void draw(GLHandler* mgl, int item, float x, float y);
	void draw(GLHandler* mgl, int item, float x, float y, float scale);
	void draw(GLHandler* mgl, int item, float x, float y, float scale, float rotation);
	void draw(GLHandler* mgl, int item, float x, float y, float scale, float rotation, float origin_x, float origin_y);
};

