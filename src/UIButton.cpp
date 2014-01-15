#include "UIButton.h"


UIButton::UIButton() : UITransitionObject()
{
	label = "none";
	clicked = false;
	hovered = false;
	down = false;
	
	textColor[0] = 0.2f;
	textColor[1] = 0.2f;
	textColor[2] = 0.2f;
	textColor[3] = 1.0f;

	setHideType(HT_VERTICAL);
	setHideLocByDistance(100.0f);
}

UIButton::UIButton(float x, float y, float w, float h, char* l) : UITransitionObject()
{
	loc_x = x;
	loc_y = y;
	width = w;
	height = h;
	label = l;
	clicked = false;
	hovered = false;
	down = false;

	textColor[0] = 0.2f;
	textColor[1] = 0.2f;
	textColor[2] = 0.2f;
	textColor[3] = 1.0f;

	setHideType(HT_VERTICAL);
	setHideLocByDistance(100.0f);
}
UIButton::~UIButton(){}

void UIButton::setLabel(char* l){label = l;}
char* UIButton::getLabel(){return label;}

// Update Button
void UIButton::update(float deltaTime){
	UITransitionObject::update(deltaTime);
	if (mFadeOut) textColor[3] = flatColor[3];
}

// Update button input 
void UIButton::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	if (shown()){
		// Check if button is hovered
		if (contains(mMouseH->getX(), mMouseH->getY()))
			hovered = true;
		else {
			hovered = false;
			down = false;
		}

		// Check to see if mouse is pressing button 
		if (hovered && mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
			down = true;

		// Check if button is clicked
		if (hovered && down && !mMouseH->isLeftDown()){
			clicked = true;
			down = false;
		}
	}
}

// Draw the button to the screen
// UIAtles must be bound first.
void UIButton::draw(GLHandler* mgl, UIAtlas* mAtlas){
	if (flatColor[3] != 0.0f){
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
}

// Check if the button was clicked 
bool UIButton::wasClicked(){
	if (clicked) {
		clicked = false;
		return true;
	}
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

