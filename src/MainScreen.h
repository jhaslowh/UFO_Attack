#pragma once
#include "UIScreen.h"
#include "UIAtlas.h"
#include "UIButton.h"

class MainScreen : public UIScreen
{
	UIButton* buttonLevelSelect;
	UIButton* buttonStore;
	UIButton* buttonSettings;
	UIButton* buttonQuit;
	UIButton* buttonText;

public:
	MainScreen();
	~MainScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height);

	// Load screen
	virtual void load(TextureAtlas* mAtlas);

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Hide the entire screen.
	// Any UI elements will need to be put into this function,
    // if they should be hidden when the screen is hidden.
	virtual void hide();

	// Show the entire screen.
	// All UI elements in the hide screen method should have show 
	// calls here. 
	virtual void show();
};

