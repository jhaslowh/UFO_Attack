#include "LevelCamera.h"


LevelCamera::LevelCamera()
{
	locX = 0.0f;
	locY = 0.0f;
	targetX = 0.0f;
	targetY = 0.0f;
	rotation = 0.0f;
	zoom = 1.0f;
	originX = 0.0f;
	originY = 0.0f;
	fixSpeed = 500.0f;
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
	targetX = -x;
	targetY = -y;
}
// Set target location
void LevelCamera::setTarget(float x, float y){
	// Invert locations so that transforms work correctly 
	targetX = -x;
	targetY = -y;

	// Fix directions 
	float angle = (float)atan2(targetY - locY,targetX - locX);
	direcY = sin(angle);
	direcX = cos(angle);
}
float LevelCamera::getX(){ return -locX;}
float LevelCamera::getY(){ return -locY;}
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


// update camera state 
void LevelCamera::update(float deltaTime){
	// Move camera to target 
	if (locX < targetX){
		locX += deltaTime * direcX * fixSpeed;

		if (locX > targetX){
			locX = targetX;
			direcX = 0.0f;
		}
	}
	else if (locX > targetX){
		locX += deltaTime * direcX * fixSpeed;

		if (locX < targetX){
			locX = targetX;
			direcX = 0.0f;
		}
	}

	if (locY < targetY){
		locY += deltaTime * direcY * fixSpeed;

		if (locY > targetY){
			locY = targetY;
			direcY = 0.0f;
		}
	}
	else if (locY > targetY){
		locY += deltaTime * direcY * fixSpeed;

		if (locY < targetY){
			locY = targetY;
			direcX = 0.0f;
		}
	}

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