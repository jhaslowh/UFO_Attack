#pragma once
#include <string>
#include <iostream>
#include "GLHandler.h"
#include "TextRender.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "TextureAtlas.h"
#include "UITerminal.h"
#include "FileHelper.h"
#include "SoundHandler.h"
// These codes are for transitionCode

// Restart game code
#define RESTART_GAME -2
// Default code state
#define NO_TRANSITION -1
// Code used to tell parent screen to close 
// this screen. Parent must check for it. 
#define CLOSE_SCREEN 0
// Screen codes used by main.cpp to switch screens. 
#define SCREEN_LOAD 1
#define SCREEN_MAIN 2
#define SCREEN_MAIN_SAVE_GAME 3
#define SCREEN_STORE 4
#define SCREEN_SETTINGS 5
#define SCREEN_GAME_NEW 6
#define SCREEN_GAME_RESUME 7
#define SCREEN_LEVEL_SELECT 8
#define SCREEN_QUIT 9
#define SCREEN_EQUIP 11
#define SCREEN_CREDITS 12
#define SCREEN_FROM_FILE 13

class UIScreen
{
protected:
	bool loaded;		// True when screen has been loaded 
	bool unloaded;		// True when screen has been unloaded
	int transitionCode; // Transition Code for screen

	bool hideOnClose;	// Set to true to hide when closing 
	float cHideTime;	// Time till screen hides
	float hideTime;		// Total screen hide time

	UIObject* uio_focus; // Current focused item 
	SoundHandler * soundHandler;
public:
	UIScreen();
	virtual ~UIScreen();

	// Set screen hide on close 
	virtual void setHideOnClose(bool value);
	// Get screen hide on close 
	virtual bool getHideOnClose();
	// Set hide time
	virtual void setHideTime(float value);
	// Get the current screen transition request code 
	virtual int getTransitionCode();
	// Set transition value 
	virtual void setTransitionValue(int value);

	// Initialize screen
	virtual void init(float screen_width, float screen_height, void* soundHandler);

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

	// Update focus input to screen
	// Return true if event handled. 
	virtual bool updateInputFocus(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Draw the screen focus 
	virtual void drawFocus(GLHandler* mgl, TextureAtlas* mAtlas);

	// Parse a command give
	virtual bool parseCommand(UITerminal* terminal, std::string command, std::string args);

	// Hide the entire screen.
	// Any UI elements will need to be put into this function,
    // if they should be hidden when the screen is hidden.
	virtual void hide();

	// Check if the screen is hidden. 
	// May not be correct for all sub elements 
	virtual bool hidden();

	// Show the entire screen.
	// All UI elements in the hide screen method should have show 
	// calls here. 
	virtual void show();
};

