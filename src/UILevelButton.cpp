#include "UILevelButton.h"


UILevelButton::UILevelButton() : UITransitionObject()
{
	clicked = false;
	hovered = false;
	down = false;

	shadowColor[0] = 0.0f;
	shadowColor[1] = 0.0f;
	shadowColor[2] = 0.0f;
	shadowColor[3] = 0.4f;
	drawShadow = true;
	shadowOffX = 4.0f;
	shadowOffY = 4.0f;

	imageHover = UII_BUTTON_NORMAL;
	imageNormal = UII_BUTTON_CLICK;
	diffIcon = UII_DIFFICULTY1;
	diffOffsetX = diffOffsetY = 0;

	difficulty = 0;
	completed = false;
	locked = false;

	// Labels 
	title = "";
	titleLocX = titleLocY = 0.0f;
	titleTextSize = 14.0f;
	desc = "";
	descLocX = descLocY = 0.0f;
	descTextSize = 12.0f;

	setHideType(HT_VERTICAL);
	setHideLocByDistance(100.0f);
}

UILevelButton::UILevelButton(float x, float y, float w, float h) : UITransitionObject()
{
	loc_x = x;
	loc_y = y;
	width = w;
	height = h;

	clicked = false;
	hovered = false;
	down = false;

	shadowColor[0] = 0.0f;
	shadowColor[1] = 0.0f;
	shadowColor[2] = 0.0f;
	shadowColor[3] = 0.4f;
	drawShadow = true;
	shadowOffX = 4.0f;
	shadowOffY = 4.0f;

	imageHover = UII_LS_TARGET_DARK;
	imageNormal = UII_LS_TARGET_LIGHT;
	diffIcon = UII_DIFFICULTY1;
	diffOffsetX = diffOffsetY = 0;

	difficulty = 0;
	completed = false;
	locked = false;
	
	// Labels 
	title = "";
	titleLocX = titleLocY = 0.0f;
	titleTextSize = 14.0f;
	desc = "";
	descLocX = descLocY = 0.0f;
	descTextSize = 12.0f;

	setHideType(HT_VERTICAL);
	setHideLocByDistance(100.0f);
}

UILevelButton::~UILevelButton()
{

}

// Update Button
void UILevelButton::update(float deltaTime){
	UITransitionObject::update(deltaTime);
}

// Getters and setters 
void UILevelButton::setDifficulty(int diff){
	difficulty = diff;

	if (diff == 0){
		diffIcon = UII_DIFFICULTY1;
	}
	else if (diff == 1){
		diffIcon = UII_DIFFICULTY2;
	}
	else if (diff == 2){
		diffIcon = UII_DIFFICULTY3;
	}
}
int UILevelButton::getDifficulty(){return difficulty;}
void UILevelButton::setCompleted(bool c){
	completed = c;
	if (c){
		imageHover = UII_LS_TARGET_DARK_CHECK;
		imageNormal = UII_LS_TARGET_LIGHT_CHECK;
	}
	else if (!c){
		imageHover = UII_LS_TARGET_DARK;
		imageNormal = UII_LS_TARGET_LIGHT;
	}

}
bool UILevelButton::getCompleted(){return completed;}
void UILevelButton::setLocked(bool l){
	locked = l;
	if(l){
		flatColor[0] = .2f;
		flatColor[1] = .2f;
		flatColor[2] = .2f;
		flatColor[3] = 1.0f;
	}
	else if (!l){
		flatColor[0] = 1.0f;
		flatColor[1] = 1.0f;
		flatColor[2] = 1.0f;
		flatColor[3] = 1.0f;
	}
}
bool UILevelButton::getLocked(){return locked;}

void UILevelButton::setTitle(std::string t){title = t;}
std::string UILevelButton::getTitle(){return title;}
void UILevelButton::setDesc(std::string d){desc = d;}
std::string UILevelButton::getDesc(){return desc;}

// Center title text and fix location of title and description 
// Note: call the after the title and scale have been set 
void UILevelButton::fixTextLoc(TextRender* mTR){
	float offset = mTR->measureString(title, titleTextSize) /2.0f;
	titleLocX = (width/2.0f) - offset;
	titleLocY = -titleTextSize;

	descLocX = width * 1.2f;
	descLocY = 0.0f;
}

// Update button input 
void UILevelButton::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	if (shown() && !locked){
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
void UILevelButton::draw(GLHandler* mgl, UIAtlas* mAtlas){
	if (flatColor[3] != 0.0f){
		
		if (hovered){
			// Draw shadow 
			if (drawShadow){
				mgl->setFlatColor(shadowColor, shadowColor[3] * flatColor[3] * mOpacity);
				mAtlas->draw(mgl, imageHover, loc_x + shadowOffX, loc_y + shadowOffY,scale);
			}
			// Draw image 
			mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
			mAtlas->draw(mgl, imageHover, loc_x, loc_y,scale);

			// Draw description
			mgl->setFlatColor(COLOR_UI_DARKBLUE, COLOR_UI_DARKBLUE[3] * mOpacity);
			mAtlas->mTextRender->drawText(*mgl, desc, loc_x + descLocX, loc_y + descLocY, 0.0f, descTextSize);
		}
		else {
			// Draw shadow 
			if (drawShadow){
				mgl->setFlatColor(shadowColor, shadowColor[3] * flatColor[3] * mOpacity);
				mAtlas->draw(mgl, imageNormal, loc_x + shadowOffX, loc_y + shadowOffY,scale);
			}
			// Draw image 
			mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
			mAtlas->draw(mgl, imageNormal, loc_x, loc_y,scale);
		}

		// Draw diff  
		mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
		mAtlas->draw(mgl, diffIcon, loc_x + diffOffsetX, loc_y + diffOffsetY,scale);

		// Draw title 
		mgl->setFlatColor(COLOR_UI_DARKBLUE, COLOR_UI_DARKBLUE[3] * mOpacity);
		mAtlas->mTextRender->drawText(*mgl, title, loc_x + titleLocX, loc_y + titleLocY, 0.0f, titleTextSize);
	}
}

// Check if the button was clicked 
bool UILevelButton::wasClicked(){
	if (clicked) {
		clicked = false;
		return true;
	}
	return false;
}

