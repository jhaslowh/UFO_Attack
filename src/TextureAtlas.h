#pragma once
#include <iostream>
#include <glew.h>
#include <string>
#include "GLHandler.h"

class TextureAtlas
{
protected:
	// Drawing variables 
	GLushort indicies[6];
	GLfloat* verts;
	GLfloat* cords;
	GLuint textureID;

	int indiceOffset;

	// Used for fast binding
	int fastBindIndex;

public:
	TextureAtlas();
	virtual ~TextureAtlas();

	// Unload texture if has one 
	void unload();

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

	// Set up the texture so it does not have to 
	// be bound again until it has been unbound.
	// Index must be greater than 1. 
	// But is restricted to the number of gltextures allowed.
	void setupFastBind(GLHandler* mgl, int index);
	// Bind the texture using the fast method
	void bindTextureFast(GLHandler* mgl);

	// Draw functions 
	// Buffers and texture muse be bound before calling 
	// these functions or they will not work correctly. 
	void draw(GLHandler* mgl, int item, float x, float y);
	void draw(GLHandler* mgl, int item, float x, float y, float scale);
	void draw(GLHandler* mgl, int item, float x, float y, float scale, float rotation);
	void draw(GLHandler* mgl, int item, float x, float y, float scale, float rotation, float origin_x, float origin_y);
	void drawScale2(GLHandler* mgl, int item, float x, float y, float scalex, float scaley);
	void drawScale2(GLHandler* mgl, int item, float x, float y, float scalex, float scaley, float rotation);
	void drawScale2(GLHandler* mgl, int item, float x, float y, float scalex, float scaley, float rotation, float origin_x, float origin_y);
};

