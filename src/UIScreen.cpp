#include "UIScreen.h"

UIScreen::UIScreen(){
	loaded = false;
}
UIScreen::~UIScreen(){}

// Initialize screen
void UIScreen::init(){
	// Nothing to do
}

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
