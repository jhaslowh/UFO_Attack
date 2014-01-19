#pragma once
#include "UIScreen.h"
#include "Sprite.h"
#include "Cube.h"
#include "UIAtlas.h"
#include "UIButton.h"
#include "UICheckbox.h"

class TestScreen : public UIScreen
{
	// Testing sprite 
	Sprite sprite;
	float rotstat;
	Cube cube;
	UIButton* button1;
	UIButton* button2;
	UIButton* button3;
	UICheckbox* checkbox1;
	UIButton* close;

public:
	TestScreen();
	~TestScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height);

	// Load screen
	virtual void load(TextureAtlas* mAtlas);

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl,  TextureAtlas* mAtlas);
};

