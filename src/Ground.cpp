#include "Ground.h"


Ground::Ground(){
	points = NULL;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
}
Ground::Ground(int count){
	points = new Point[count];
	pointCount = count;
	indicies = new GLushort[count];
	for (int i = 0; i < count; i++)
		indicies[i] = i;
	verts = new GLfloat[count*2];

	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
}
Ground::~Ground(){
	if (points != NULL)
		delete(points);
	if (indicies != NULL)
		delete(indicies);
	if (verts != NULL)
		delete(verts);
}

// Set a specific point
void Ground::setPoint(const int index, Point p){
	if (index >= pointCount) return;

	points[index].setX(p.getX());
	points[index].setY(p.getY());

	// Set vertexes 
	if (verts != NULL){
		verts[(index * 2)] = p.getX();
		verts[(index * 2) + 1] = p.getY();
	}
}
// Set the ground points 
void Ground::setPoints(Point* p){
	if (points != NULL)
		delete(points);
	points = p;
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
 
	mgl->toggleTextures(false);

	// Draw the sent indicies 
	glDrawElements(GL_LINE_STRIP, pointCount, GL_UNSIGNED_SHORT, indicies);

	// Disable arrays
	glDisableVertexAttribArray(mgl->mPositionHandle);
	glDisableVertexAttribArray(mgl->mTextCordHandle);
}