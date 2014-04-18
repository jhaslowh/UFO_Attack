#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "UIScreen.h"
#include "UIAtlas.h"
#include "UIButton.h"
#include "Sprite.h"
#include "SaveData.h"

class LevelSelectScreen: public UIScreen
{
	SaveData* sd;
	UIButton* buttonMainMenu;
	UIButton* buttonLevels[20];
	std::string levelsList[20];

	int numberOfLevels;
	float screen_width, screen_height;
	
	// Map variables 
	Sprite map;

public:
	LevelSelectScreen(SaveData* s);
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