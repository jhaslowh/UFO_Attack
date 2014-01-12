#include "TextureAtlas.h"


TextureAtlas::TextureAtlas()
{
	textureID = -1;
}
TextureAtlas::~TextureAtlas(){
	if (verts != NULL) delete(verts);
	if (cords != NULL) delete(cords);
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
	/// Set up vertex and coord buffers 
	glEnableVertexAttribArray(mgl->mPositionHandle);
	glVertexAttribPointer(mgl->mPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, verts );

	/// Bind texture
	glEnableVertexAttribArray(mgl->mTextCordHandle);
	glVertexAttribPointer(mgl->mTextCordHandle, 2,GL_FLOAT, GL_FALSE, 0, cords);
}

// Call to bind the texture 
void TextureAtlas::bindTexture(GLHandler* mgl){
	mgl->toggleTextures(true);
	// Set the active texture unit to texture unit 0.
	glActiveTexture(GL_TEXTURE0);
	// Bind the texture to this unit.
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
	glUniform1i(mgl->mTextureHandle, 0);
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

