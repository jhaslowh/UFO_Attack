#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include "Collision.h"

class Camera2D
{
	float locX, locY;			// Location of our camera 
	float targetX, targetY;		// Target location for the camera 
	float direcX, direcY;		// Fix direction
	float fixSpeed;				// Speed to fix camera to target 
	float rotation;				// Camera rotation 
	float zoom;					// Camera zoom 
	float originX, originY;		// Camera origin

	float targetDistance;		// Distance location is from target
	float additionalSpeed;		// Additional speed if point is too far

public:
	Camera2D();
	~Camera2D();

	// Set up camera
	void init(float screen_width, float screen_height);

	// Set camera location
	void setLocation(float x, float y);
	float getX();
	float getY();
	// Set target location
	void setTarget(float x, float y);
	float getTargetX();
	float getTargetY();
	// Set camera rotation
	void setRotation(float r);
	// Set camera zoom
	void setZoom(float z);
	// Get camera zoom 
	float getZoom();

	// Convert mouse x to level x
	// NOTE: Does not account for rotation. 
	float toLevelX(float mouseX);
	// Convert mouse y to level y
	// NOTE: Does not account for rotation. 
	float toLevelY(float mouseY);
	// Convert level x to screen x
	// NOTE: Does not account for rotation. 
	float toScreenX(float levelX);
	// Convert level x to screen y
	// NOTE: Does not account for rotation. 
	float toScreenY(float levelY);

	// update camera state 
	void update(float deltaTime);

	// Convert camera to a matrix 
	glm::mat4 getMatrix();
};

