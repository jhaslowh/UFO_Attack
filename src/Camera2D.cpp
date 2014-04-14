#include "Camera2D.h"


Camera2D::Camera2D()
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

Camera2D::~Camera2D(){}

// Set up camera
void Camera2D::init(float screen_width, float screen_height){
	originX = screen_width / 2.0f;
	originY = screen_height / 2.0f;
}

// Set camera location
void Camera2D::setLocation(float x, float y){
	// Invert locations so that transforms work correctly 
	locX = -x;
	locY = -y;
	targetX = -x;
	targetY = -y;
}
float Camera2D::getX(){ return -locX;}
float Camera2D::getY(){ return -locY;}
// Set target location
void Camera2D::setTarget(float x, float y){
	// Invert locations so that transforms work correctly 
	targetX = -x;
	targetY = -y;

	// Fix directions 
	float angle = (float)atan2(targetY - locY,targetX - locX);
	direcY = sin(angle);
	direcX = cos(angle);
}
float Camera2D::getTargetX(){return -targetX;}
float Camera2D::getTargetY(){return -targetY;}
// Set camera rotation
void Camera2D::setRotation(float r){
	rotation = r;
}
// Set camera zoom
void Camera2D::setZoom(float z){
	// Bind zoom above 0
	if (z < 0.0f)
		z = 0.0f;
	zoom = z;
}
// Get camera zoom 
float Camera2D::getZoom(){return zoom;}

// Convert mouse x to level x
float Camera2D::toLevelX(float mouseX){
	// Apply negation of matrix transforms 
	return ((mouseX - originX) / zoom) - locX;
}
// Convert mouse y to level y
float Camera2D::toLevelY(float mouseY){
	// Apply negation of matrix transforms 
	return ((mouseY - originY) / zoom) - locY;
}
// Convert level x to screen x
float Camera2D::toScreenX(float levelX){
	// Apply matrix transforms in reverse order 
	return ((levelX + locX) * zoom) + originX;
}
// Convert level x to screen y
float Camera2D::toScreenY(float levelY){
	// Apply matrix transforms in reverse order 
	return ((levelY + locY) * zoom) + originY;
}

// update camera state 
void Camera2D::update(float deltaTime){
	targetDistance = dist(locX, locY, targetX, targetY);
	if (targetDistance > 1000.0f)
	{
		additionalSpeed = targetDistance / 1000.0f;
	}
	else
		additionalSpeed = 1.0f;

	// Move camera to target 
	if (locX < targetX){
		locX += deltaTime * direcX * fixSpeed * additionalSpeed;

		if (locX > targetX){
			locX = targetX;
			direcX = 0.0f;
		}
	}
	else if (locX > targetX){
		locX += deltaTime * direcX * fixSpeed * additionalSpeed;

		if (locX < targetX){
			locX = targetX;
			direcX = 0.0f;
		}
	}

	if (locY < targetY){
		locY += deltaTime * direcY * fixSpeed * additionalSpeed;

		if (locY > targetY){
			locY = targetY;
			direcY = 0.0f;
		}
	}
	else if (locY > targetY){
		locY += deltaTime * direcY * fixSpeed * additionalSpeed;

		if (locY < targetY){
			locY = targetY;
			direcX = 0.0f;
		}
	}

}

// Convert camera to a matrix 
glm::mat4 Camera2D::getMatrix(){
	// Starting matrix 
	glm::mat4 mMatrix;

	// I beleive the translation is actually the origin in this case. 

	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(originX, originY, 0.0f));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(zoom));
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(locX, locY, 0.0f));

	return mMatrix;
}