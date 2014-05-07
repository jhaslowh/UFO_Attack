#pragma once
#include "UIScreen.h"
#include "UIButton.h"
#include "UILabel.h"
#include "Rec.h"
#include "Sprite.h"

class PauseScreen : public UIScreen
{
	UILabel* lTitle;
	UIButton* bResume;
	UIButton* bQuit;
	UIButton* controls;
	UIButton* controlsBack;
	bool showControls;
	Sprite contrlImage;
	Rec bgOverlay;

public:
	PauseScreen();
	virtual ~PauseScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height, void* sh);

	// Load screen
	virtual void load(TextureAtlas* mAtlas);

	// Unload screen textures
	// THIS MUST BE CALLED IF YOU LOAD STUFF.
	virtual void unload();

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

