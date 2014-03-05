#include "UIScreen.h"

UIScreen::UIScreen(){
	loaded = false;
	unloaded = true;
	transitionCode = NO_TRANSITION;
	hideOnClose = false;
	cHideTime = 0.0f;
	hideTime = .28f;
}
UIScreen::~UIScreen(){}

// Set screen hide on close 
void UIScreen::setHideOnClose(bool value){hideOnClose = value;}

// Get screen hide on close 
bool UIScreen::getHideOnClose(){return hideOnClose;}

// Set hide time
void UIScreen::setHideTime(float value){hideTime = value;}

// Initialize screen
void UIScreen::init(float screen_width, float screen_height){
	// Nothing to do
}

// Get the current screen transition request code 
int UIScreen::getTransitionCode(){return transitionCode;}

// Load screen
void UIScreen::load(TextureAtlas* mAtlas){
	loaded = true;
	unloaded = false;
}

// Unload screen textures
// THIS MUST BE CALLED IF YOU LOAD STUFF.
void UIScreen::unload(){
	unloaded = true;
	loaded = false;
}
bool UIScreen::isUnloaded(){
	return unloaded;
}

// Update the state of the screen
void UIScreen::update(float deltaTime){
	// Minus hide time if not 0
	if (cHideTime > 0.0f){
		cHideTime -= deltaTime;
		if (cHideTime < 0.0f)
			cHideTime = 0.0f;
	}
}

// Update input to the screen 
void UIScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Nothing to do
}

// Draw the screen
void UIScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	if (!loaded && transitionCode == NO_TRANSITION)
		load(mAtlas);
}

// Parse a command give
bool UIScreen::parseCommand(UITerminal* terminal, std::string command, std::string args){
	// Check screen commands 
	if (command == "screen"){
		// Hide screen
		if (args == "hide") {
			terminal->addLine("screen hide", TL_SUCCESS);
			hide();
			return true;
		}

		// Show screen
		if (args == "show"){
			terminal->addLine("screen show", TL_SUCCESS);
			show();
			return true;
		}

		// Go to main menu 
		if (args == "main"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_MAIN;
			return true;
		}

		// Go to store
		if (args == "store"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_STORE;
			return true;
		}

		// Go to settings
		if (args == "settings"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_SETTINGS;
			return true;
		}

		// Go to game
		if (args == "game"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_GAME;
			return true;
		}

		// Go to level select
		if (args == "levelselect"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_LEVEL_SELECT;
			return true;
		}

		// Go to free play
		if (args == "freeplay"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_FREE_PLAY;
			return true;
		}

		terminal->addLine("Unrecognized arguments given to command: screen", TL_WARNING);
		return true;
	}

	return false;
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void UIScreen::hide(){
	cHideTime = hideTime;
}

// Check if the screen is hidden. 
// May not be correct for all sub elements 
bool UIScreen::hidden(){
	return cHideTime <= 0.0f;
}


// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void UIScreen::show(){
	// Nothing to do
}