#include "UIScreen.h"

UIScreen::UIScreen(){
	loaded = false;
	transitionCode = NO_TRANSITION;
}
UIScreen::~UIScreen(){}

// Initialize screen
void UIScreen::init(float screen_width, float screen_height){
	// Nothing to do
}

// Get the current screen transition request code 
int UIScreen::getTransitionCode(){return transitionCode;}

// Load screen
void UIScreen::load(TextureAtlas* mAtlas){
	loaded = true;
}

// Update the state of the screen
void UIScreen::update(float deltaTime){
	// Nothing to do
}

// Update input to the screen 
void UIScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Nothing to do
}

// Draw the screen
void UIScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	if (!loaded)
		load(mAtlas);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void UIScreen::hide(){
	// Nothing to do
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void UIScreen::show(){
	// Nothing to do
}