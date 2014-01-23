#include "Ground.h"


Ground::Ground(){
	points = NULL;
	indicies = NULL;
	verts = NULL;
	cords = NULL;
	pointCount = 0;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	groundDepth = 400.0f;
	textureID = -1;
	grassLength = 55.0f;
}
Ground::Ground(int count){
	points = NULL;
	indicies = NULL;
	verts = NULL;
	cords = NULL;
	pointCount = 0;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	groundDepth = 400.0f;
	textureID = -1;
	grassLength = 55.0f;

	setPointCount(count);
}
Ground::~Ground(){
	if (points != NULL)
		delete[] points;
	if (indicies != NULL)
		delete[] indicies;
	if (verts != NULL)
		delete[] verts;
	if (cords != NULL)
		delete[] cords;
}

// Load texture
void Ground::load(){
	textureID = loadPNG("images/dirt.png");
	grass.setup(64.0f,32.0f,"images/grass.png");
	grass.setColor(0.0f,1.0f,0.0f);
	grass.setOrigin(5.0f,22.0f);
}

// Set point count
// Do not use this to change the size of the point
// arrays. It will erase the arrays. 
void Ground::setPointCount(int count){
	if (points != NULL)
		delete(points);
	if (indicies != NULL)
		delete(indicies);
	if (verts != NULL)
		delete(verts);
	if (cords != NULL)
		delete(cords);

	pointCount = count;
	points = new Point[pointCount];
	
	// 6 Indicies for every 2 ground points 
	indicieCount = (count-1) * 6;
	indicies = new GLushort[indicieCount];
	for (int i = 0; i < indicieCount; i++){
		indicies[i]	= 0;
	}

	// This is alittle crazy, but we are creatings a polygon strip. 
	for (int i = 0; i < count; i++){
		indicies[(i * 6)]	  = (GLushort)(i * 2);
		indicies[(i * 6) + 1] = (GLushort)((i * 2) + 1);
		indicies[(i * 6) + 2] = (GLushort)((i + 1) * 2);
		indicies[(i * 6) + 3] = (GLushort)((i * 2) + 1);
		indicies[(i * 6) + 4] = (GLushort)((i * 2) + 3);
		indicies[(i * 6) + 5] = (GLushort)((i + 1) * 2);
	}

	verts = new GLfloat[count*4];
	cords = new GLfloat[count*4];
}

// Set a specific point
void Ground::setPoint(const int index, Point p){
	if (pointCount == 0) {
		std::cout << "Error: Point count must be set\n";
		return;
	}
	if (index >= pointCount) {
		std::cout << "Error: Point index out of range\n";
		return;
	}

	points[index].setX(p.getX());
	points[index].setY(p.getY());

	// Set vertexes 
	if (verts != NULL && cords != NULL){
		verts[(index * 4)] = p.getX();
		verts[(index * 4) + 1] = p.getY();
		verts[(index * 4) + 2] = p.getX();
		verts[(index * 4) + 3] = p.getY() + groundDepth;

		// Since we have GL_REPEAT set in the textures, we can 
		// use the vertex numbers as texture cords to get the 
		// texture to repeat across the whole polygon. 
		cords[(index * 4)]     = verts[(index * 4)] / 100.0f;
		cords[(index * 4) + 1] = verts[(index * 4) + 1] / 100.0f;
		cords[(index * 4) + 2] = verts[(index * 4) + 2] / 100.0f;
		cords[(index * 4) + 3] = verts[(index * 4) + 3] / 100.0f;
	}
}
// Get the ground points
Point* Ground::getPoints(){
	return points;
}
// Get a single point
Point Ground::getPoint(int index){
	return points[index];
}
// Get the number of ground points
int Ground::getPointCount(){
	return pointCount;
}

// Draw ground 
void Ground::draw(GLHandler* mgl){
	// ----------------- // 
	// Draw grass        //
	// ----------------- // 

	// Variables used
	// (might need to make these part of the class 
	// to reduce creation and deletion costs)
	float len;
	float direcX;
	float direcY;

	// Bind grass to draw faster 
	grass.bind(mgl);

	for (int i = 0; i < pointCount -1; i++){
		// Get the length of the grass segment
		len = dist(points[i], points[i+1]);
		// Set rotation for grass segment 
		grass.setRotation(angle(points[i], points[i+1]));

		// Do not draw crass on steep hills
		if (grass.getRotation() < 70.0f && grass.getRotation() > -70.0f){
			// Set starting location 
			grass.setPosition(points[i].getX(), points[i].getY());

			// Set movement values 
			direcX = (float)cos((3.14159f / 180.0f) * grass.getRotation()) * grassLength;
			direcY = (float)sin((3.14159f / 180.0f) * grass.getRotation()) * grassLength;

			// Draw grass based off length 
			while (len > grassLength){
				grass.drawFast(mgl);

				grass.setPosition(grass.getX() + direcX, grass.getY() + direcY);
				len -= grassLength;
			}

			// Draw last peice of grass that is shorter than grass length
			grass.clip(len/grassLength, 1.0f);
			grass.drawFast(mgl);
			grass.restore();
		}
	}
	// ----------------- // 
	// Draw dirt         //
	// ----------------- // 

	/** Matrix transform **/
	// Starting matrix 
	glm::mat4 mMatrix;
	mgl->setModelMatrix(mMatrix);

	/** Set shader flat color **/
	mgl->setFlatColor(color);

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
 
	if (textureID != -1){
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

	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, indicieCount, GL_UNSIGNED_SHORT, indicies);

	// Disable arrays
	glDisableVertexAttribArray(mgl->mPositionHandle);
	glDisableVertexAttribArray(mgl->mTextCordHandle);
}