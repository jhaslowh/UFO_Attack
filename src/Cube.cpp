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

	// Vertexes  

	// Front Face
	verts[0] = -0.5f; verts[1] = 0.5f;  verts[2] = 0.5f;   // Vertex 1
	verts[3] = -0.5f; verts[4] = -0.5f; verts[5] = 0.5f;   // Vertex 2
	verts[6] = 0.5f;  verts[7] = -0.5f; verts[8] = 0.5f;   // Vertex 3
	verts[9] = 0.5f;  verts[10] = 0.5f; verts[11] = 0.5f;  // Vertex 4

	// Back Face
	verts[12] = 0.5f;  verts[13] = 0.5f;  verts[14] = -0.5f;  // Vertex 5
	verts[15] = 0.5f;  verts[16] = -0.5f; verts[17] = -0.5f;  // Vertex 6
	verts[18] = -0.5f; verts[19] = -0.5f; verts[20] = -0.5f;  // Vertex 7
	verts[21] = -0.5f; verts[22] = 0.5f;  verts[23] = -0.5f;  // Vertex 8

	// Top Face
	verts[24] = -0.5f; verts[25] = 0.5f; verts[26] = -0.5f; // Vertex 9
	verts[27] = -0.5f; verts[28] = 0.5f; verts[29] = 0.5f;  // Vertex 10
	verts[30] = 0.5f;  verts[31] = 0.5f; verts[32] = 0.5f;  // Vertex 11
	verts[33] = 0.5f;  verts[34] = 0.5f; verts[35] = -0.5f; // Vertex 12

	// Bottom Face
	verts[36] = -0.5f; verts[37] = -0.5f; verts[38] = 0.5f;  // Vertex 13
	verts[39] = -0.5f; verts[40] = -0.5f; verts[41] = -0.5f; // Vertex 14
	verts[42] = 0.5f;  verts[43] = -0.5f; verts[44] = -0.5f; // Vertex 15
	verts[45] = 0.5f;  verts[46] = -0.5f; verts[47] = 0.5f;  // Vertex 16

	// Left Face
	verts[48] = 0.5f; verts[49] = 0.5f;  verts[50] = 0.5f;  // Vertex 17
	verts[51] = 0.5f; verts[52] = -0.5f; verts[53] = 0.5f;  // Vertex 18
	verts[54] = 0.5f; verts[55] = -0.5f; verts[56] = -0.5f; // Vertex 19
	verts[57] = 0.5f; verts[58] = 0.5f;  verts[59] = -0.5f; // Vertex 20

	// Right Face
	verts[60] = -0.5f; verts[61] = 0.5f;  verts[62] = -0.5f; // Vertex 21
	verts[63] = -0.5f; verts[64] = -0.5f; verts[65] = -0.5f; // Vertex 22
	verts[66] = -0.5f; verts[67] = -0.5f; verts[68] = 0.5f;  // Vertex 23
	verts[69] = -0.5f; verts[70] = 0.5f;  verts[71] = 0.5f;  // Vertex 24

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

	// Back Face 
	indicies[12] = 8;
	indicies[13] = 9;
	indicies[14] = 10;
	indicies[15] = 10;
	indicies[16] = 11;
	indicies[17] = 8;
	
	// Bottom Face 
	indicies[18] = 12;
	indicies[19] = 13;
	indicies[20] = 14;
	indicies[21] = 14;
	indicies[22] = 15;
	indicies[23] = 12;

	// Left Face 
	indicies[24] = 16;
	indicies[25] = 17;
	indicies[26] = 18;
	indicies[27] = 18;
	indicies[28] = 19;
	indicies[29] = 16;

	// Right Face 
	indicies[30] = 20;
	indicies[31] = 21;
	indicies[32] = 22;
	indicies[33] = 22;
	indicies[34] = 23;
	indicies[35] = 20;

}

Cube::~Cube(void){}

// Setup the cubes texture 
void Cube::setTexture(std::string file){
	textureID = loadPNG(file);

	cords[0] = 0.0f; cords[1] = 0.0f;
	cords[2] = 0.0f; cords[3] = 1.0f;
	cords[4] = 1.0f; cords[5] = 1.0f;
	cords[6] = 1.0f; cords[7] = 0.0f;

	cords[8] = 0.0f; cords[9] = 0.0f;
	cords[10] = 0.0f; cords[11] = 1.0f;
	cords[12] = 1.0f; cords[13] = 1.0f;
	cords[14] = 1.0f; cords[15] = 0.0f;

	cords[16] = 0.0f; cords[17] = 0.0f;
	cords[18] = 0.0f; cords[19] = 1.0f;
	cords[20] = 1.0f; cords[21] = 1.0f;
	cords[22] = 1.0f; cords[23] = 0.0f;

	cords[24] = 0.0f; cords[25] = 0.0f;
	cords[26] = 0.0f; cords[27] = 1.0f;
	cords[28] = 1.0f; cords[29] = 1.0f;
	cords[30] = 1.0f; cords[31] = 0.0f;

	cords[32] = 0.0f; cords[33] = 0.0f;
	cords[34] = 0.0f; cords[35] = 1.0f;
	cords[36] = 1.0f; cords[37] = 1.0f;
	cords[38] = 1.0f; cords[39] = 0.0f;

	cords[40] = 0.0f; cords[41] = 0.0f;
	cords[42] = 0.0f; cords[43] = 1.0f;
	cords[44] = 1.0f; cords[45] = 1.0f;
	cords[46] = 1.0f; cords[47] = 0.0f;
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
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indicies);

	// Disable vertexes 
	glDisableVertexAttribArray(mgl.mPositionHandle);
	glDisableVertexAttribArray(mgl.mTextCordHandle);
}
