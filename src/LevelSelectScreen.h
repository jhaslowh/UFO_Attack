#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include "UIScreen.h"
#include "UIAtlas.h"
#include "UIButton.h"
#include "Sprite.h"
#include <string>
#include <vector>

class LevelSelectScreen: public UIScreen
{
	UIButton* buttonMainMenu;
	UIButton* buttonLevels[20];
	//std::vector<std::string> levelsList;
	std::string levelsList[20];
	int numberOfLevels;
	Sprite logo;
	float screen_width, screen_height;

public:
	LevelSelectScreen();
	virtual ~LevelSelectScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height, void* sh);

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

	void loadLevelList();
	//loads the list of levels from the master level file
};