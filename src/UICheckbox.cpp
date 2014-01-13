#include "UICheckbox.h"

UICheckbox::UICheckbox(){
	loc_x = 0;
	loc_y = 0;
	width = 0;
	height = 0;
	label = "none";
	checked = false;
	hovered = false;

	flatColor[0] = 1.0f;
	flatColor[1] = 1.0f;
	flatColor[2] = 1.0f;
	flatColor[3] = 1.0f;
	textColor[0] = 0.2f;
	textColor[1] = 0.2f;
	textColor[2] = 0.2f;
	textColor[3] = 1.0f;
}
UICheckbox::UICheckbox(float x, float y, float w, float h, char* l){
	loc_x = x;
	loc_y = y;
	width = w;
	height = h;
	label = l;
	checked = false;
	hovered = false;

	text_x = w + 10;
	text_y = (h/2.0f) - 
		(UIC_TEXT_SIZE/2.0f)+ 
		((UIC_TEXT_SIZE/TR_FONT_SIZE) * TR_FONT_BOTTOM_SPACE);

	flatColor[0] = 1.0f;
	flatColor[1] = 1.0f;
	flatColor[2] = 1.0f;
	flatColor[3] = 1.0f;
	textColor[0] = 0.2f;
	textColor[1] = 0.2f;
	textColor[2] = 0.2f;
	textColor[3] = 1.0f;
}
UICheckbox::~UICheckbox(){}

// Getters and Setters 
void UICheckbox::setLocation(float x, float y){loc_x = x; loc_y = y;}
float UICheckbox::getX(){return loc_x;}
float UICheckbox::getY(){return loc_y;}
void UICheckbox::setSize(float w, float h){width = w; height = h;}
float UICheckbox::getWidth(){return width;}
float UICheckbox::getHeight(){return height;}
void UICheckbox::setLabel(char* l){label = l;}
char* UICheckbox::getLabel(){return label;}

// Update the button 
void UICheckbox::update(float deltaTime){
	// Nothing to do 
}

// Update button input 
void UICheckbox::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Check if button is hovered
	if (contains(mMouseH->getX(), mMouseH->getY()))
		hovered = true;
	else 
		hovered = false;

	// Check if button is clicked
	if (hovered && !mMouseH->isLeftDown() && mMouseH->wasLeftDown())
		checked = !checked;
}

// Draw the button to the screen
// UIAtles must be bound first.
void UICheckbox::draw(GLHandler* mgl, UIAtlas* mAtlas){
	mgl->setFlatColor(flatColor);
	if (checked)
		mAtlas->draw(mgl, UII_CHECKBOX_CHECKED, loc_x, loc_y);
	else 
		mAtlas->draw(mgl, UII_CHECKBOX_NORMAL, loc_x, loc_y);

	mgl->setFlatColor(textColor);
	mAtlas->mTextRender->drawText(*mgl, label, 
		loc_x + text_x, loc_y + text_y, 0, UIC_TEXT_SIZE);
}

// Check if the button was clicked 
bool UICheckbox::Checked(){
	return checked;
}

// Check if the sent location is inside the button 
bool UICheckbox::contains(float x, float y){
	if (x > loc_x && x < loc_x + width &&
			y > loc_y && y < loc_y + height)
		return true;
	return false;
}