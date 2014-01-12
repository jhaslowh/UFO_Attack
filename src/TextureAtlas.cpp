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