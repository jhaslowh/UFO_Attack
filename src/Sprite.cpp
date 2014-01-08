#include "Sprite.h"

Sprite::Sprite(){
	pos_x = 0.0f;
	pos_y = 0.0f;
	rotation = 0.0f;
	scale = 1.0f;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	origin_x = 0;
	origin_y = 0;
}
Sprite::~Sprite(){}

// Setup the sprites verticies, coords, and texture 
void Sprite::setup(float w,float h,char* file)
{
	// Set indicies
	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;
	indicies[3] = 2;
	indicies[4] = 3;
	indicies[5] = 0;

	// Vertexes 
	verts[0] = 0; verts[1] = 0;
	verts[2] = 0; verts[3] = h;
	verts[4] = w; verts[5] = h;
	verts[6] = w; verts[7] = 0;

	// Texture Coords
	cords[0] = 0.0f; cords[1] = 0.0f;
	cords[2] = 0.0f; cords[3] = 1.0f;
	cords[4] = 1.0f; cords[5] = 1.0f;
	cords[6] = 1.0f; cords[7] = 0.0f;

	// Load texture
	textureID = FileHelper::loadPNG(file);
}

// Set position of the sprite 
void Sprite::setPosition(float x, float y){
	pos_x = x; pos_y = y;
}

// Set the rotation of the sprite 
void Sprite::setRotation(float degrees){
	rotation = degrees;
}

// Set the scale of the sprite 
void Sprite::setScale(float value){
	scale = value;
}

// Set the origin of the sprite 
void Sprite::setOrigin(float x,float y){
	origin_x = x;
	origin_y = y;
}

// Set the RGB color 
void Sprite::setColor(const float r,const float g,const float b){
	color[0] = r; color[1] = g; color[2] = b;
}

// Set the RGBA color
void Sprite::setColor(const float r,const float g,const float b,const float a){
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
}

// Set the alpha value 
void Sprite::setAlpha(const float a){
	color[3] = a;
}

// Draw the sprite to the screen
void Sprite::draw(GLHandler mgl){
	/** Matrix transform **/
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(pos_x, pos_y, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-origin_x, -origin_y, 0.0f));
	// Send the rotation matrix to the shader 
	mgl.setModelMatrix(mMatrix);

	/** Set shader flat color **/
	mgl.setFlatColor(color);

	/* Set up vertex and coord buffers **/
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

	/** Bind Texture **/
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
