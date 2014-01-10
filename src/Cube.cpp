#include "Cube.h"

Cube::Cube()
{
	pos_x = 0.0f;
	pos_y = 0.0f;
	pos_z = 0.0f;
	rot_x = 0.0f;
	rot_y = 0.0f;
	rot_z = 0.0f;
	scale = 1.0f;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	origin_x = 0;
	origin_y = 0;
	textureID = -1;

	
	// Set indicies
	// Front Face 
	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;
	indicies[3] = 2;
	indicies[4] = 3;
	indicies[5] = 0;

	// Top Face 
	indicies[6] = 4;
	indicies[7] = 5;
	indicies[8] = 6;
	indicies[9] = 6;
	indicies[10] = 7;
	indicies[11] = 4;

	// Vertexes 
	// Front face 
	verts[0] = -0.5f; verts[1] = 0.5f;  verts[2] = 0.5f;   // Vertex 1
	verts[3] = -0.5f; verts[4] = -0.5f; verts[5] = 0.5f;   // Vertex 2
	verts[6] = 0.5f;  verts[7] = -0.5f; verts[8] = 0.5f;   // Vertex 3
	verts[9] = 0.5f;  verts[10] = 0.5f; verts[11] = 0.5f;  // Vertex 4

	// Top face 
	verts[12] = -0.5f; verts[13] = 0.5f; verts[14] = -0.5f;   // Vertex 5
	verts[15] = -0.5f; verts[16] = 0.5f; verts[17] = 0.5f;   // Vertex 6
	verts[18] = 0.5f;  verts[19] = 0.5f; verts[20] = 0.5f;   // Vertex 7
	verts[21] = 0.5f;  verts[22] = 0.5f; verts[23] = -0.5f;  // Vertex 8
}

Cube::~Cube(void){}

// Setup the cubes texture 
void Cube::setTexture(char* file){
	textureID = FileHelper::loadPNG(file);
}

// Set the position of the cube 
void Cube::setPosition(float x, float y, float z){
	pos_x = x; pos_y = y; pos_z = z;
}

// Set the rotation of the cube on the x axis  
void Cube::setRotationX(float degrees){
	rot_x = degrees;
}
float Cube::getRotationX(){return rot_x;};

// Set the rotation of the cube on the z axis  
void Cube::setRotationY(float degrees){
	rot_y = degrees;
}
float Cube::getRotationY(){return rot_y;};

// Set the rotation of the cube on the z axis  
void Cube::setRotationZ(float degrees){
	rot_z = degrees;
}
float Cube::getRotationZ(){return rot_z;};

// Set the scale of the cube
void Cube::setScale(float value){
	scale = value;
}

// Set the origin of the cube 
void Cube::setOrigin(float x,float y){
	origin_x = x;
	origin_y = y;
}

// Set the RGB color 
void Cube::setColor(const float r,const float g,const float b){
	color[0] = r; color[1] = g; color[2] = b;
}

// Set the RGBA color
void Cube::setColor(const float r,const float g,const float b,const float a){
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
}

// Set the alpha value 
void Cube::setAlpha(const float a){
	color[3] = a;
}


// Call to draw the cube
void Cube::draw(GLHandler mgl){
	/** Matrix transform **/
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(pos_x, pos_y, pos_z));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rot_x, glm::vec3(1.0f, 0.0f, 0.0f));
	mMatrix = glm::rotate(mMatrix, rot_y, glm::vec3(0.0f, 1.0f, 0.0f));
	mMatrix = glm::rotate(mMatrix, rot_z, glm::vec3(0.0f, 0.0f, 1.0f));
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
	// Describe our vertices array to OpenGL 
	glVertexAttribPointer(
		mgl.mPositionHandle, // attribute
		3,                 // number of elements per vertex, here (x,y,z)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		verts  // pointer to the C array
	);
 
	if (textureID != -1){
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
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, indicies);
	
	GLfloat c[]= {0.0f,0.0f,0.0f,1.0f};
	mgl.setFlatColor(c);
	glDrawElements(GL_LINE_STRIP, 12, GL_UNSIGNED_SHORT, indicies);

	// Disable vertexes 
	glDisableVertexAttribArray(mgl.mPositionHandle);
	glDisableVertexAttribArray(mgl.mTextCordHandle);
}
