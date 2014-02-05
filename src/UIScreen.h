#pragma once
#include <string>
#include <iostream>
#include "GLHandler.h"
#include "TextRender.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "TextureAtlas.h"
#include "UITerminal.h"

// These codes are for transitionCode

// Default code state
#define NO_TRANSITION -1
// Code used to tell parent screen to close 
// this screen. Parent must check for it. 
#define CLOSE_SCREEN 0
// Screen codes used by main.cpp to switch screens. 
#define SCREEN_LOAD 1
#define SCREEN_MAIN 2
#define SCREEN_STORE 3
#define SCREEN_SETTINGS 4
#define SCREEN_GAME 5
#define SCREEN_LEVEL_SELECT 6
#define SCREEN_QUIT 7
#define SCREEN_TEST 8
#define SCREEN_FREE_PLAY 9

class UIScreen
{
protected:
	bool loaded;
	bool unloaded;
	int transitionCode;

public:
	UIScreen();
	virtual ~UIScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height);

	// Get the current screen transition request code 
	virtual int getTransitionCode();

	// Load screen
	// Note: If textures need to be loaded, they must
	// be loaded in this method or they will not work. 
	virtual void load(TextureAtlas* mAtlas);

	// Unload screen textures
	// THIS MUST BE CALLED IF YOU LOAD STUFF.
	virtual void unload();
	bool isUnloaded();

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Parse a command give
	virtual bool parseCommand(UITerminal* terminal, std::string command, std::string args);

	// Hide the entire screen.
	// Any UI elements will need to be put into this function,
    // if they should be hidden when the screen is hidden.
	virtual void hide();

	// Show the entire screen.
	// All UI elements in the hide screen method should have show 
	// calls here. 
	virtual void show();
};

