#include "UIObject.h"

UIObject::UIObject(){	
	loc_x = 0;
	loc_y = 0;
	width = 0;
	height = 0;
	flatColor[0] = 1.0f;
	flatColor[1] = 1.0f;
	flatColor[2] = 1.0f;
	flatColor[3] = 1.0f;
}
UIObject::~UIObject(){}

// Getters and Setters 
void UIObject::setLocation(float x, float y){loc_x = x; loc_y = y;}
float UIObject::getX(){return loc_x;}
void UIObject::setX(float x){loc_x = x;}
float UIObject::getY(){return loc_y;}
void UIObject::setY(float y){loc_y = y;}
void UIObject::setSize(float w, float h){width = w; height = h;}
float UIObject::getWidth(){return width;}
float UIObject::getHeight(){return height;}
void UIObject::setColor(float r, float g, float b){
	flatColor[0] = r;
	flatColor[1] = g;
	flatColor[2] = b;
}
GLfloat* UIObject::getColor(){return flatColor;}

// Call if object has child objects that need to be set up
void UIObject::init(float screen_width, float screen_height){
	// Nothing to do
}
// Call if object has child objects that need to be loaded
void UIObject::load(TextureAtlas* mAtlas){
	// Nothing to do
}

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

// Draw the object to the screen at sent offset.
// UIAtles must be bound first.
void UIObject::draw(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy){
	// Nothing to do
}

// Check if the sent location is inside the objc
bool UIObject::contains(float x, float y){
	if (x > loc_x && x < loc_x + width &&
			y > loc_y && y < loc_y + height)
		return true;
	return false;
}