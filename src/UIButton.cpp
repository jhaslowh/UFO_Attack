#include "UIButton.h"

UIButton::UIButton() : UITransitionObject()
{
	label = std::string("none");
	clicked = false;
	hovered = false;
	down = false;
	
	textColor[0] = 0.2f;
	textColor[1] = 0.2f;
	textColor[2] = 0.2f;
	textColor[3] = 1.0f;

	shadowColor[0] = 0.0f;
	shadowColor[1] = 0.0f;
	shadowColor[2] = 0.0f;
	shadowColor[3] = 0.4f;
	drawShadow = true;
	shadowOffX = 4.0f;
	shadowOffY = 4.0f;

	imageID = UII_BUTTON_NORMAL;
	imageIDClick = UII_BUTTON_CLICK;
	imageIDHover = UII_BUTTON_HOVER;

	setHideType(HT_VERTICAL);
	setHideLocByDistance(100.0f);

	showTooltip = false;
	toolTipX = toolTipY = 0.0f;
	toolTipW = toolTipH = 0.0f;
	toolTipText = "";
	ttShowTime = 0.0f;
	cttShowTime = 0.0f;
}

UIButton::UIButton(float x, float y, float w, float h, std::string l) : UITransitionObject()
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
	
	shadowColor[0] = 0.0f;
	shadowColor[1] = 0.0f;
	shadowColor[2] = 0.0f;
	shadowColor[3] = 0.4f;
	drawShadow = true;
	shadowOffX = 4.0f;
	shadowOffY = 4.0f;

	imageID = UII_BUTTON_NORMAL;
	imageIDClick = UII_BUTTON_CLICK;
	imageIDHover = UII_BUTTON_HOVER;

	setHideType(HT_VERTICAL);
	setHideLocByDistance(100.0f);

	showTooltip = false;
	toolTipX = toolTipY = 0.0f;
	toolTipW = toolTipH = 0.0f;
	toolTipText = "";
	ttShowTime = 0.0f;
	cttShowTime = 0.0f;
}
UIButton::~UIButton(){}

void UIButton::setLabel(std::string l){
	label = l;
}
std::string UIButton::getLabel(){return label;}

void UIButton::setImageId(int value){imageID = value;}
void UIButton::setImageIdClick(int value){imageIDClick = value;}
void UIButton::setImageIdHover(int value){imageIDHover = value;}

// Update Button
void UIButton::update(float deltaTime){
	UITransitionObject::update(deltaTime);

	// Update tool tip time 
	if (hovered)
		cttShowTime += deltaTime;
	else 
		cttShowTime = 0.0f;
}

// Update button input 
void UIButton::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	if (shown()){
		// Check if button is hovered
		if (contains(mMouseH->getX(), mMouseH->getY())){
			hovered = true;
			if (showTooltip) reqFocus = true;
		}
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

// Update focus input 
// Return false to remove focus. 
bool UIButton::updateInputFocus(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIObject::updateInputFocus(mKeyH, mMouseH);

	updateInput(mKeyH, mMouseH);

	if (hovered){
		toolTipX = mMouseH->getX() + 20.0f;
		toolTipY = mMouseH->getY();

		return true;
	}

	return false;
}
	

// Draw the button to the screen
// UIAtles must be bound first.
void UIButton::draw(GLHandler* mgl, UIAtlas* mAtlas){
	if (flatColor[3] != 0.0f){
		if (down){
			// Draw shadow 
			if (drawShadow){
				mgl->setFlatColor(shadowColor, shadowColor[3] * flatColor[3] * mOpacity);
				mAtlas->draw(mgl, imageIDClick, loc_x + shadowOffX, loc_y + shadowOffY,scale);
			}
			// Draw image 
			mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
			mAtlas->draw(mgl, imageIDClick, loc_x, loc_y,scale);
		}
		else if (hovered){
			// Draw shadow 
			if (drawShadow){
				mgl->setFlatColor(shadowColor, shadowColor[3] * flatColor[3] * mOpacity);
				mAtlas->draw(mgl, imageIDHover, loc_x + shadowOffX, loc_y + shadowOffY,scale);
			}
			// Draw image 
			mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
			mAtlas->draw(mgl, imageIDHover, loc_x, loc_y,scale);
		}
		else {
			// Draw shadow 
			if (drawShadow){
				mgl->setFlatColor(shadowColor, shadowColor[3] * flatColor[3] * mOpacity);
				mAtlas->draw(mgl, imageID, loc_x + shadowOffX, loc_y + shadowOffY,scale);
			}
			// Draw image 
			mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
			mAtlas->draw(mgl, imageID, loc_x, loc_y,scale);
		}

		mgl->setFlatColor(textColor, textColor[3] * mOpacity);
		mAtlas->mTextRender->drawText(*mgl, label, 
			loc_x + text_x, loc_y + text_y, 0, UIB_TEXT_SIZE * scale);
	}
}

// Draw the object focus elements to the screen
// UIAtles must be bound first.
void UIButton::drawFocus(GLHandler* mgl, UIAtlas* mAtlas){
	UIObject::drawFocus(mgl, mAtlas);

	// Fix sizes if 0 
	if (toolTipW <= 0.0f){
		toolTipW = mAtlas->mTextRender->measureString(toolTipText, UIB_TT_TEXT_SIZE) + 8.0f;
		toolTipH = (UIB_TT_TEXT_SIZE * 2.0f) + 8.0f;
	}

	if (cttShowTime >= ttShowTime){
		// Draw tool tip background
		mgl->setFlatColor(COLOR_BLACK_10);
		mAtlas->drawScale2(mgl, UII_REC, toolTipX, toolTipY, toolTipW, toolTipH);
		mgl->setFlatColor(COLOR_BLACK_50);
		mAtlas->drawScale2(mgl, UII_REC, toolTipX-4.0f, toolTipY-4.0f, toolTipW, toolTipH);
		mgl->setFlatColor(COLOR_UI_LABEL);
		mAtlas->mTextRender->drawText(*mgl, toolTipText, toolTipX, toolTipY, 0.0f, UIB_TT_TEXT_SIZE);
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

// Set the tool tip for this button 
void UIButton::setTooltip(std::string text, float time){
	toolTipText = text;
	showTooltip = true;
	ttShowTime = time;
}

// Remove the tool tip from the button
void UIButton::removeToolTip(){
	showTooltip = false;
	toolTipX = toolTipY = 0.0f;
	toolTipW = toolTipH = 0.0f;
	toolTipText = "";
	ttShowTime = 0.0f;
	cttShowTime = 0.0f;
}
