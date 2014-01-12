#pragma once
#include "GLHandler.h"
#include "TextRender.h"
#include "KeyHandler.h"

class UIScreen
{
public:
	UIScreen();
	virtual ~UIScreen();

	// Initialize screen
	virtual void init();

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextRender* mTR);
};

