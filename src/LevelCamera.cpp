#include "LevelCamera.h"


LevelCamera::LevelCamera()
{
	locX = 0.0f;
	locY = 0.0f;
	rotation = 0.0f;
	zoom = 1.0f;
	originX = 0.0f;
	originY = 0.0f;
}

LevelCamera::~LevelCamera(){}

// Set up camera
void LevelCamera::init(float screen_width, float screen_height){
	originX = screen_width / 2.0f;
	originY = screen_height / 2.0f;
}

// Set camera location
void LevelCamera::setLocation(float x, float y){
	// Invert locations so that transforms work correctly 
	locX = -x;
	locY = -y;
}
// Set camera rotation
void LevelCamera::setRotation(float r){
	rotation = r;
}
// Set camera zoom
void LevelCamera::setZoom(float z){
	zoom = z;
}

// Convert mouse x to level x
float LevelCamera::toLevelX(float mouseX){
	return (mouseX - originX) - locX;
}
// Convert mouse y to level y
float LevelCamera::toLevelY(float mouseY){
	return (mouseY - originY) - locY;
}
// Convert level x to screen x
float LevelCamera::toScreenX(float levelX){
	return levelX + locX + originX;
}
// Convert level x to screen y
float LevelCamera::toScreenY(float levelY){
	return levelY + locY + originY;
}

// Convert camera to a matrix 
glm::mat4 LevelCamera::getMatrix(){
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(locX, locY, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(zoom));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(originX, originY, 0.0f));

	return mMatrix;
}