#include "TextureAtlas.h"


TextureAtlas::TextureAtlas()
{
	verts = NULL;
	cords = NULL;
	textureID = 0;
	indiceOffset = 0;
}
TextureAtlas::~TextureAtlas(){
	delete[] verts;
	delete[] cords;
	// This line will crash unless the sprite is deleted
	// in the main thread. You cannot delete a gl object
	// in the update thread. I am also not sure if we need 
	// it. 
	//glDeleteTextures(1, &textureID);
}

// Set the vertex list 
void TextureAtlas::setVerts(GLfloat* v){
	verts = v;
}

// Set the cord list 
void TextureAtlas::setCords(GLfloat* c){
	cords = c;
}

// Set the texture sheet id
void TextureAtlas::setTexture(GLint value){
	textureID = value;
}

// Set the offset of the index values 
void TextureAtlas::setIndiceOffset(int value){
	indiceOffset = value;
}

// Call to bind the vertex and cord buffers
void TextureAtlas::bindBuffers(GLHandler* mgl){
	mgl->bindBuffers(verts, cords);
}

// Call to bind the texture 
void TextureAtlas::bindTexture(GLHandler* mgl){
	mgl->bindTexture(textureID);
}

// Set the indicies for the atlas 
void TextureAtlas::setIndicies(int index){
	indicies[0] = (GLushort)(4 * (index+indiceOffset));
	indicies[1] = (GLushort)((4 * (index+indiceOffset)) + 1);
	indicies[2] = (GLushort)((4 * (index+indiceOffset)) + 2);
	indicies[3] = (GLushort)((4 * (index+indiceOffset)) + 2);
	indicies[4] = (GLushort)((4 * (index+indiceOffset)) + 3);
	indicies[5] = (GLushort)(4 * (index+indiceOffset));
}

// Draw functions 
void TextureAtlas::draw(GLHandler* mgl, int item, float x, float y){
	
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);
	// Set the indicies based on the item
	setIndicies(item);
	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}

void TextureAtlas::draw(GLHandler* mgl, int item, float x, float y, float scale){
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);
	// Set the indicies based on the item
	setIndicies(item);
	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}

void TextureAtlas::draw(GLHandler* mgl, int item, float x, float y, float scale, 
	float rotation){
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);
	// Set the indicies based on the item
	setIndicies(item);
	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}

void TextureAtlas::draw(GLHandler* mgl, int item, float x, float y, float scale, 
	float rotation, float origin_x, float origin_y){
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-origin_x, -origin_y, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);
	// Set the indicies based on the item
	setIndicies(item);
	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}

void TextureAtlas::drawScale2(GLHandler* mgl, int item, float x, float y, float scalex, float scaley){
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scalex, scaley, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);
	// Set the indicies based on the item
	setIndicies(item);
	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}

void TextureAtlas::drawScale2(GLHandler* mgl, int item, float x, float y, float scalex, float scaley, float rotation){
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scalex, scaley, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);
	// Set the indicies based on the item
	setIndicies(item);
	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}
void TextureAtlas::drawScale2(GLHandler* mgl, int item, float x, float y, float scalex, float scaley, float rotation, float origin_x, float origin_y){
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(x, y, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scalex, scaley, 0.0f));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-origin_x, -origin_y, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);
	// Set the indicies based on the item
	setIndicies(item);
	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}
