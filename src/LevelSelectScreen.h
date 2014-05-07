#pragma once
//#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "UIScreen.h"
#include "UIAtlas.h"
#include "UIButton.h"
#include "UILevelButton.h"
#include "Sprite.h"
#include "SaveData.h"

class LevelSelectScreen: public UIScreen
{
	SaveData* sd;
	UIButton* buttonMainMenu;
	UILevelButton* buttonLevels[20];
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

	// Parse a command give
	virtual bool parseCommand(UITerminal* terminal, std::string command, std::string args);

	void loadLevelList();
	//loads the list of levels from the master level file
};
