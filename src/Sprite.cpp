#include "Sprite.h"

Sprite::Sprite(){}
Sprite::~Sprite(){}

void Sprite::set(float x,float y,float w,float h,char* file)
{
	// Set indicies
	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;
	indicies[3] = 2;
	indicies[4] = 3;
	indicies[5] = 0;

	// Vertexes 
	verts[0] = x; verts[1] = y;
	verts[2] = x; verts[3] = y + h;
	verts[4] = x + w; verts[5] = y + h;
	verts[6] = x + w; verts[7] = y;

	// Texture Coords
	cords[0] = 0.0f; cords[1] = 0.0f;
	cords[2] = 0.0f; cords[3] = 1.0f;
	cords[4] = 1.0f; cords[5] = 1.0f;
	cords[6] = 1.0f; cords[7] = 0.0f;

	// Load texture
	textureID = FileHelper::loadPNG(file);
}

// Draw the sprite to the screen
void Sprite::draw(GLHandler mgl){

	glEnableVertexAttribArray(mgl.mPositionHandle);
	// Describe our vertices array to OpenGL (it can't guess its format automatically) 
	glVertexAttribPointer(
		mgl.mPositionHandle, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		verts  // pointer to the C array
	);
 
    // Bind textures 
    glEnableVertexAttribArray(mgl.mTextCordHandle);
    glVertexAttribPointer(
        mgl.mTextCordHandle, 
		2,                 // number of elements per coord, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		cords			  // pointer to the C array
	);

	// Set the active texture unit to texture unit 0.
    glActiveTexture(GL_TEXTURE0);
    // Bind the texture to this unit.
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
    glUniform1i(mgl.mTextureHandle, 0);

	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);

	// Disable vertexes 
	glDisableVertexAttribArray(mgl.mPositionHandle);
	glDisableVertexAttribArray(mgl.mTextCordHandle);
}
