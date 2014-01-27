#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class LevelCamera
{
	float locX, locY;			// Location of our camera 
	float targetX, targetY;		// Target location for the camera 
	float direcX, direcY;		// Fix direction
	float fixSpeed;				// Speed to fix camera to target 
	float rotation;				// Camera rotation 
	float zoom;					// Camera zoom 
	float originX, originY;		// Camera origin

public:
	LevelCamera();
	~LevelCamera();

	// Set up camera
	void init(float screen_width, float screen_height);

	// Set camera location
	void setLocation(float x, float y);
	float getX();
	float getY();
	// Set target location
	void setTarget(float x, float y);
	// Set camera rotation
	void setRotation(float r);
	// Set camera zoom
	void setZoom(float z);

	// Convert mouse x to level x
	float toLevelX(float mouseX);
	// Convert mouse y to level y
	float toLevelY(float mouseY);
	// Convert level x to screen x
	float toScreenX(float levelX);
	// Convert level x to screen y
	float toScreenY(float levelY);

	// update camera state 
	void update(float deltaTime);

	// Convert camera to a matrix 
	glm::mat4 getMatrix();
};

