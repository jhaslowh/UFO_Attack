#pragma once
#include "UIScreen.h"
#include "Sprite.h"
#include "Cube.h"

class TestScreen : UIScreen
{
	// Testing sprite 
	Sprite sprite;
	float rotstat;
	Cube cube;

public:
	TestScreen();
	virtual ~TestScreen();

	// Initialize screen
	virtual void init();

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextRender* mTR);
};

