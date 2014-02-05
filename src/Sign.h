#pragma once
#include <string>
#include "SceneryObject.h"
#include "Camera2D.h"

class Sign : public SceneryObject
{
	// Color for text
	GLfloat textColor[4];
	// Color for background rec
	GLfloat recColor[4];
	// Size for text
	float textSize;
	// Text offset
	float textOffX, textOffY;


	// Text to draw on sign
	std::string text;
	// Toggle text on and off
	bool drawText;

public:
	Sign();
	~Sign();

	// Set sign text
	void setText(std::string t);
	// Get sign text
	std::string getText();
	
	// Update Handlers 
	virtual void update(float deltaTime, Handlers* handlers);
	
	// Update scenery input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw object ui elements 
	virtual void drawUI(GLHandler* mgl, UIAtlas* mUI);

	// Call when the player collides with the object 
	virtual void onCollide();
};

