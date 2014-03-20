#include "Sprite.h"

Sprite::Sprite(){
	locX = 0.0f;
	locY = 0.0f;
	rotation = 0.0f;
	scale = 1.0f;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	originX = 0;
	originY = 0;
	textureID = 0;
	width = 0;
	height = 0;
}
Sprite::~Sprite(){}

// Unload sprite 
void Sprite::unload(){
	if (textureID != 0)
		glDeleteTextures(1, &textureID);
}

// Setup the sprites verticies, coords, and texture 
void Sprite::setup(float w,float h)
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

	width = w;
	height = h;
}

// Setup the sprites verticies, coords, and texture 
void Sprite::setup(float w,float h, std::string file)
{
	setup(w,h);

	// Load texture
	textureID = loadPNG(file);
}

// Set position of the sprite 
void Sprite::setPosition(float x, float y){
	locX = x; locY = y;
}
void Sprite::setX(float x){locX = x;}
void Sprite::setY(float y){locY = y;}
float Sprite::getX(){return locX;}
float Sprite::getY(){return locY;}

// Set the rotation of the sprite 
void Sprite::setRotation(float degrees){
	rotation = degrees;
}
float Sprite::getRotation(){return rotation;}

// Set the scale of the sprite 
void Sprite::setScale(float value){
	scale = value;
}
float Sprite::getScale(){return scale;}

// Set the origin of the sprite 
void Sprite::setOrigin(float x,float y){
	originX = x;
	originY = y;
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
float Sprite::getAlpha(){return color[3];}

// Get the width of the sprite
float Sprite::getWidth(){return width;}
// Get the height of the sprite 
float Sprite::getHeight(){return height;}

// Call to get image id
GLuint Sprite::getImageID(){return textureID;}

// Call to clip part of the image off. 
// Can be fixed later with restore()
void Sprite::clip(float xPer, float yPer){
	// Vertexes 
	verts[0] = 0;			 verts[1] = 0;
	verts[2] = 0;			 verts[3] = height * yPer;
	verts[4] = width * xPer; verts[5] = height * yPer;
	verts[6] = width * xPer; verts[7] = 0;

	// Texture Coords
	cords[0] = 0.0f; cords[1] = 0.0f;
	cords[2] = 0.0f; cords[3] = yPer;
	cords[4] = xPer; cords[5] = yPer;
	cords[6] = xPer; cords[7] = 0.0f;
}

// Fix the image if it was cliped; 
void Sprite::restore(){
	// Vertexes 
	verts[0] = 0; verts[1] = 0;
	verts[2] = 0; verts[3] = height;
	verts[4] = width; verts[5] = height;
	verts[6] = width; verts[7] = 0;

	// Texture Coords
	cords[0] = 0.0f; cords[1] = 0.0f;
	cords[2] = 0.0f; cords[3] = 1.0f;
	cords[4] = 1.0f; cords[5] = 1.0f;
	cords[6] = 1.0f; cords[7] = 0.0f;
}

// Prebind the vertex and texture cord buffers. 
// Along with bind the texture, so you can render 
// many copies of the sprite quickly. 
void Sprite::bind(GLHandler* mgl){
	/* Set up vertex and coord buffers **/
	glEnableVertexAttribArray(mgl->mPositionHandle);
	// Describe our vertices array to OpenGL
	glVertexAttribPointer(
		mgl->mPositionHandle, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		verts  // pointer to the C array
	);
 
	if (textureID != 0){
		// Bind texture
		glEnableVertexAttribArray(mgl->mTextCordHandle);
		glVertexAttribPointer(
			mgl->mTextCordHandle, 
			2,                 // number of elements per coord, here (x,y)
			GL_FLOAT,          // the type of each element
			GL_FALSE,          // take our values as-is
			0,                 // no extra data between each position
			cords			  // pointer to the C array
		);

		/** Bind Texture **/
		mgl->toggleTextures(true);
		// Set the active texture unit to texture unit 0.
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture to this unit.
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
		glUniform1i(mgl->mTextureHandle, 0);
	}
	else 
		mgl->toggleTextures(false);
}

// Draw the sprite to the screen
void Sprite::draw(GLHandler mgl){
	/** Matrix transform **/
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(locX, locY, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-originX, -originY, 0.0f));
	// Send the rotation matrix to the shader 
	mgl.setModelMatrix(mMatrix);

	/** Set shader flat color **/
	mgl.setFlatColor(color);

	/* Set up vertex and coord buffers **/
	glEnableVertexAttribArray(mgl.mPositionHandle);
	// Describe our vertices array to OpenGL
	glVertexAttribPointer(
		mgl.mPositionHandle, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		verts  // pointer to the C array
	);
 
	if (textureID != 0){
		// Bind texture
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
		mgl.toggleTextures(true);
		// Set the active texture unit to texture unit 0.
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture to this unit.
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
		glUniform1i(mgl.mTextureHandle, 0);
	}
	else 
		mgl.toggleTextures(false);

	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);

	// Disable arrays
	glDisableVertexAttribArray(mgl.mPositionHandle);
	glDisableVertexAttribArray(mgl.mTextCordHandle);
}

// Draw the sprite to the screen at offset
void Sprite::draw(GLHandler mgl, float offx, float offy){
	/** Matrix transform **/
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(locX + offx, locY + offy, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-originX, -originY, 0.0f));
	// Send the rotation matrix to the shader 
	mgl.setModelMatrix(mMatrix);

	/** Set shader flat color **/
	mgl.setFlatColor(color);

	/* Set up vertex and coord buffers **/
	glEnableVertexAttribArray(mgl.mPositionHandle);
	// Describe our vertices array to OpenGL
	glVertexAttribPointer(
		mgl.mPositionHandle, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		verts  // pointer to the C array
	);
 
	if (textureID != 0){
		// Bind texture
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
		mgl.toggleTextures(true);
		// Set the active texture unit to texture unit 0.
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture to this unit.
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
		glUniform1i(mgl.mTextureHandle, 0);
	}
	else 
		mgl.toggleTextures(false);

	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);

	// Disable arrays
	glDisableVertexAttribArray(mgl.mPositionHandle);
	glDisableVertexAttribArray(mgl.mTextCordHandle);
}

// Use to draw copies of the sprite faster
// Must call bind() first. 
void Sprite::drawFast(GLHandler* mgl){
	/** Matrix transform **/
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(locX, locY, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-originX, -originY, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);

	/** Set shader flat color **/
	mgl->setFlatColor(color);

	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}

// Use to draw copies of the sprite faster.
// Draw at offset 
// Must call bind() first. 
void Sprite::drawFast(GLHandler* mgl, float offx, float offy){
	/** Matrix transform **/
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(locX + offx, locY + offy, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-originX, -originY, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);

	/** Set shader flat color **/
	mgl->setFlatColor(color);

	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);
}