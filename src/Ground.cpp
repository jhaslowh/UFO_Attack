#include "Ground.h"


Ground::Ground(int type){
	points = NULL;
	indicies = NULL;
	verts = NULL;
	cords = NULL;
	pointCount = 0;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	groundDepth = 600.0f;
	textureID = 0;
	grass.setScale(.5f);
	grassLength = 55.0f * grass.getScale();
	textureScale = 80.0f;
	groundType = type;
}
Ground::~Ground(){
	while (points != NULL){
		itr = points;
		points = points->next;
		delete itr;
	}
	delete[] indicies;
	delete[] verts;
	delete[] cords;
}

// This will have no effect if called after load is called
void Ground::setType(int type){
	groundType = type;
}

int Ground::getType()
{
	return groundType;
}

// Load texture
void Ground::load(){
	if (groundType == GROUND_DIRT){
		textureID = loadPNG("images/dirt.png");
		grass.setup(64.0f,32.0f,"images/grass.png");
		grass.setColor(0.0f,1.0f,0.0f);
		grass.setOrigin(5.0f,22.0f);
	}
	else if (groundType == GROUND_CEMENT){
		textureID = loadPNG("images/cement.png");
		grass.setup(64.0f,32.0f,"images/cementTop.png");
		grass.setColor(1.0f,1.0f,1.0f);
		grass.setOrigin(5.0f,22.0f);
	}
}

// Unload ground
void Ground::unload(){
	grass.unload();
	if (textureID != 0)
		glDeleteTextures(1, &textureID);
}

// Add new point into the array 
void Ground::add(Point* p){
	if (points == NULL){
		points = p;
		pointCount++;
		fixArrays();
		return;
	}

	itr = points;
	while(itr != NULL){
		// If at end of list, must add point
		if (itr->next == NULL){
			itr->next = p;
			p->prev = itr;
			pointCount++;
			fixArrays();
			return;
		}

		// Check if the sent point is between the next two
		if (p->getX() >= itr->getX() && p->getX() <= itr->next->getX()){
			p->next = itr->next;
			p->prev = itr;
			itr->next->prev = p;
			itr->next = p;
			pointCount++;
			fixArrays();
			return;
		}

		itr = itr->next;
	}

	std::cout << "Ground::add(Point* p) Error: could not add point\n";
}
// Remove point by address 
void Ground::remove(Point* p){
	if (points == p)
	{
		// Save head
		itr = points;
		// Set head as heads next
		points = points->next;
		points->prev = NULL;
		// Make saved head next as null so it does not delete chain
		itr->next = NULL;
		// Delete saved head 
		delete itr;
		
		pointCount--;
		fixArrays();
		return;
	}

	itr = points;
	while (itr != NULL){
		if (itr == p){
			itr->prev->next = itr->next;
			if (itr->next != NULL)
				itr->next->prev = itr->prev;
			itr->next = NULL;
			itr->prev = NULL;
			delete itr;
			
			pointCount--;
			fixArrays();
			return;
		}

		itr = itr->next;
	}

	std::cout << "Ground::remove(Point* p) Error: sent address could not be found\n";
}

// Get the ground points
Point* Ground::getPoints(){
	return points;
}
// Get a single point
Point* Ground::getPoint(int index){
	if (index < 0 || index >= pointCount)
		std::cout << "Ground::getPoint(int index), Index outside bounds\n";

	if (points == NULL)
		std::cout << "Ground::getPoint(int index), Points list is empty\n";

	itr = points;
	int i = 0;
	while (itr != NULL){
		if (i == index)
			return itr;

		itr = itr->next;
		i++;
	}

	std::cout << "Ground::getPoint(int index), Error\n";
	return NULL;
}

// Fix the vertexes for the sent point
void Ground::fixVertsForPoint(Point* p){
	int i = 0;
	itr = points;
	while (itr != NULL){
		if (itr == p){
			verts[(i * 4)] = itr->getX();
			verts[(i * 4) + 1] = itr->getY();
			verts[(i * 4) + 2] = itr->getX();
			verts[(i * 4) + 3] = itr->getY() + groundDepth;
			cords[(i * 4)]     = verts[(i * 4)] / textureScale;
			cords[(i * 4) + 1] = verts[(i * 4) + 1] / textureScale;
			cords[(i * 4) + 2] = verts[(i * 4) + 2] / textureScale;
			cords[(i * 4) + 3] = verts[(i * 4) + 3] / textureScale;
			return;
		}

		itr = itr->next;
		i++;
	}

	std::cout << "Ground::fixVertsForPoint(Point* p), Error: point address could not be found\n";
}

// Get the number of ground points
int Ground::getPointCount(){
	return pointCount;
}

// Get bottom most point value
float Ground::getBottomMost(){
	if (points == NULL)
		return 0;

	float value = points->getY();
	itr = points->next;
	while (itr != NULL){
		if (itr->getY() > value)
			value = itr->getY();
		itr = itr->next;
	}

	return value;
}

// Get top mose point value
float Ground::getTopMost(){
	if (points == NULL)
		return 0;

	float value = points->getY();
	itr = points->next;
	while (itr != NULL){
		if (itr->getY() < value)
			value = itr->getY();
		itr = itr->next;
	}

	return value;
}


// Draw ground light layer
void Ground::drawLight(GLHandler* mgl){
	if (pointCount > 1){
		/// Matrix transform ///
		// Starting matrix 
		glm::mat4 mMatrix;
		mgl->setModelMatrix(mMatrix);

		/// Set shader flat color ///
		mgl->setFlatColor(mgl->lightClearColor);

		/// Set up vertex and coord buffers ///
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
 
		mgl->toggleTextures(false);

		// Draw the sent indicies 
		glDrawElements(GL_TRIANGLES, indicieCount, GL_UNSIGNED_SHORT, indicies);

		// Disable arrays
		glDisableVertexAttribArray(mgl->mPositionHandle);
		glDisableVertexAttribArray(mgl->mTextCordHandle);

		mgl->toggleTextures(true);
	}
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

	itr = points;
	if (itr != NULL){
		while (itr->next != NULL)
		{
			// Get the length of the grass segment
			len = dist(*itr, *(itr->next));
			// Set rotation for grass segment 
			grass.setRotation(angle(*itr, *(itr->next)));

			// Do not draw grass on steep hills
			if (grass.getRotation() < 70.0f && grass.getRotation() > -70.0f){
				// Set starting location 
				grass.setPosition(itr->getX(), itr->getY());

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

			itr = itr->next;
		}
	}

	// ----------------- // 
	// Draw dirt         //
	// ----------------- // 

	if (pointCount > 1){
		/// Matrix transform ///
		// Starting matrix 
		glm::mat4 mMatrix;
		mgl->setModelMatrix(mMatrix);

		/// Set shader flat color ///
		mgl->setFlatColor(color);

		/// Set up vertex and coord buffers ///
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

			/// Bind Texture ///
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
}

// Call to fix the vertex, index, and cord arrays 
void Ground::fixArrays(){
	if (pointCount < 2) return;

	delete[] indicies;
	delete[] verts;
	delete[] cords;
	
	// 6 Indicies for every 2 ground points 
	indicieCount = (pointCount-1) * 6;
	indicies = new GLushort[indicieCount];
	verts = new GLfloat[pointCount*4];
	cords = new GLfloat[pointCount*4];

	for (int i = 0; i < indicieCount; i++){
		indicies[i]	= 0;
	}

	// This is alittle crazy, but we are creatings a polygon strip. 
	for (int i = 0; i < pointCount - 1; i++){
		indicies[(i * 6)]	  = (GLushort)(i * 2);
		indicies[(i * 6) + 1] = (GLushort)((i * 2) + 1);
		indicies[(i * 6) + 2] = (GLushort)((i + 1) * 2);
		indicies[(i * 6) + 3] = (GLushort)((i * 2) + 1);
		indicies[(i * 6) + 4] = (GLushort)((i * 2) + 3);
		indicies[(i * 6) + 5] = (GLushort)((i + 1) * 2);
	}

	itr = points;
	for (int i = 0; i < pointCount; i++){
		verts[(i * 4)] = itr->getX();
		verts[(i * 4) + 1] = itr->getY();
		verts[(i * 4) + 2] = itr->getX();
		verts[(i * 4) + 3] = itr->getY() + groundDepth;

		// Since we have GL_REPEAT set in the textures, we can 
		// use the vertex numbers as texture cords to get the 
		// texture to repeat across the whole polygon. 
		cords[(i * 4)]     = verts[(i * 4)] / textureScale;
		cords[(i * 4) + 1] = verts[(i * 4) + 1] / textureScale;
		cords[(i * 4) + 2] = verts[(i * 4) + 2] / textureScale;
		cords[(i * 4) + 3] = verts[(i * 4) + 3] / textureScale;

		itr = itr->next;
	}
}