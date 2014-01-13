#include "UIButton.h"


UIButton::UIButton()
{
	loc_x = 0;
	loc_y = 0;
	width = 0;
	height = 0;
	label = "none";
	clicked = false;
	hovered = false;
	down = false;
	
	flatColor[0] = 1.0f;
	flatColor[1] = 1.0f;
	flatColor[2] = 1.0f;
	flatColor[3] = 1.0f;
	textColor[0] = 0.2f;
	textColor[1] = 0.2f;
	textColor[2] = 0.2f;
	textColor[3] = 1.0f;
}

UIButton::UIButton(float x, float y, float w, float h, char* l){
	loc_x = x;
	loc_y = y;
	width = w;
	height = h;
	label = l;
	clicked = false;
	hovered = false;
	down = false;

	flatColor[0] = 1.0f;
	flatColor[1] = 1.0f;
	flatColor[2] = 1.0f;
	flatColor[3] = 1.0f;
	textColor[0] = 0.2f;
	textColor[1] = 0.2f;
	textColor[2] = 0.2f;
	textColor[3] = 1.0f;
}
UIButton::~UIButton(){}

// Getters and Setters 
void UIButton::setLocation(float x, float y){loc_x = x; loc_y = y;}
float UIButton::getX(){return loc_x;}
float UIButton::getY(){return loc_y;}
void UIButton::setSize(float w, float h){width = w; height = h;}
float UIButton::getWidth(){return width;}
float UIButton::getHeight(){return height;}
void UIButton::setLabel(char* l){label = l;}
char* UIButton::getLabel(){return label;}

// Update the button 
void UIButton::update(float deltaTime){
	// Nothing to do 
}

// Update button input 
void UIButton::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	// Check if button is hovered
	if (contains(mMouseH->getX(), mMouseH->getY()))
		hovered = true;
	else 
		hovered = false;

	// Check to see if mouse is pressing button 
	if (hovered && mMouseH->isLeftDown())
		down = true;
	else 
		down = false;

	// Check if button is clicked
	if (hovered && !mMouseH->isLeftDown() && mMouseH->wasLeftDown())
		clicked = true;
}

// Draw the button to the screen
// UIAtles must be bound first.
void UIButton::draw(GLHandler* mgl, UIAtlas* mAtlas){
	mgl->setFlatColor(flatColor);
	if (down)
		mAtlas->draw(mgl, UII_BUTTON_CLICK, loc_x, loc_y);
	else if (hovered)
		mAtlas->draw(mgl, UII_BUTTON_HOVER, loc_x, loc_y);
	else 
		mAtlas->draw(mgl, UII_BUTTON_NORMAL, loc_x, loc_y);

	mgl->setFlatColor(textColor);
	mAtlas->mTextRender->drawText(*mgl, label, 
		loc_x + text_x, loc_y + text_y, 0, UIB_TEXT_SIZE);
}

// Check if the button was clicked 
bool UIButton::wasClicked(){
	if (clicked) {
		clicked = false;
		return true;
	}
	return false;
}

// Check if the sent location is inside the button 
bool UIButton::contains(float x, float y){
	if (x > loc_x && x < loc_x + width &&
			y > loc_y && y < loc_y + height)
		return true;
	return false;
}

// Center label text 
void UIButton::centerText(TextRender* mTR){
	float offset = mTR->measureString(label, UIB_TEXT_SIZE) /2.0f;
	text_x = (width/2.0f) - offset;
	text_y = 
		((height/2.0f) - (UIB_TEXT_SIZE/2.0f)) +	// Position to center of text
		((UIB_TEXT_SIZE/TR_FONT_SIZE) * TR_FONT_BOTTOM_SPACE); // Remove bottom white space 
}

