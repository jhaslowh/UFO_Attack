#include "UIScreen.h"

UIScreen::UIScreen(){
	loaded = false;
	unloaded = true;
	transitionCode = NO_TRANSITION;
	hideOnClose = false;
	cHideTime = 0.0f;
	hideTime = .28f;
	uio_focus = NULL;
}
UIScreen::~UIScreen(){}

// Set screen hide on close 
void UIScreen::setHideOnClose(bool value){hideOnClose = value;}

// Get screen hide on close 
bool UIScreen::getHideOnClose(){return hideOnClose;}

// Set hide time
void UIScreen::setHideTime(float value){hideTime = value;}

// Get the current screen transition request code 
int UIScreen::getTransitionCode(){return transitionCode;}
// Set transition value 
void UIScreen::setTransitionValue(int value){transitionCode = value;}

// Initialize screen
void UIScreen::init(float screen_width, float screen_height, void* sh){
	soundHandler = (SoundHandler*)sh;
}

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

// Update focus input to screen
bool UIScreen::updateInputFocus(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Update focus object 
	if (uio_focus != NULL){
		if (!uio_focus->updateInputFocus(mKeyH, mMouseH))
			uio_focus = NULL;
		return true;
	}
	return false;
}

// Draw the screen
void UIScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	if (!loaded)// && transitionCode == NO_TRANSITION)
		load(mAtlas);
}

// Draw the screen focus 
void UIScreen::drawFocus(GLHandler* mgl, TextureAtlas* mAtlas){
	if (uio_focus != NULL)
		uio_focus->drawFocus(mgl, (UIAtlas*)mAtlas);
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
			transitionCode = SCREEN_GAME_RESUME;
			return true;
		}

		// Go to new game
		if (args == "newgame"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_GAME_NEW;
			return true;
		}

		// Go to level select
		if (args == "levelselect"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_LEVEL_SELECT;
			return true;
		}

		// Go to credits screen
		if (args == "credits"){
			terminal->addLine(command + " " + args, TL_SUCCESS);
			transitionCode = SCREEN_CREDITS;
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