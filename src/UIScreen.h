#pragma once
#include <string>
#include <iostream>
#include "GLHandler.h"
#include "TextRender.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "TextureAtlas.h"

#define NO_TRANSITION -1
#define SCREEN_LOAD 0
#define SCREEN_MAIN 1
#define SCREEN_STORE 2
#define SCREEN_SETTINGS 3
#define SCREEN_GAME 4
#define SCREEN_LEVEL_SELECT 5
#define SCREEN_QUIT 6
#define SCREEN_TEST 7
#define CLOSE_SCREEN 8

class UIScreen
{
protected:
	bool loaded;
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

