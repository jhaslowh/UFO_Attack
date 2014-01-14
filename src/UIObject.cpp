#include "UIObject.h"

UIObject::UIObject(){}
UIObject::~UIObject(){}

// Getters and Setters 
void UIObject::setLocation(float x, float y){loc_x = x; loc_y = y;}
float UIObject::getX(){return loc_x;}
float UIObject::getY(){return loc_y;}
void UIObject::setSize(float w, float h){width = w; height = h;}
float UIObject::getWidth(){return width;}
float UIObject::getHeight(){return height;}

// Update the button 
void UIObject::update(float deltaTime){
	// Nothing to do
}

// Update input 
void UIObject::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Nothing to do
}

// Draw the object to the screen
// UIAtles must be bound first.
void UIObject::draw(GLHandler* mgl, UIAtlas* mAtlas){
	// Nothing to do
}

// Check if the sent location is inside the objc
bool UIObject::contains(float x, float y){
	if (x > loc_x && x < loc_x + width &&
			y > loc_y && y < loc_y + height)
		return true;
	return false;
}