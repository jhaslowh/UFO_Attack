#include "UIValueSlider.h"


UIValueSlider::UIValueSlider() : UITransitionObject()
{
	down = false;
	hovered = false;
	sliderLoc = 0.0f;
	value = 0.0f;
	minValue = 0.0f;
	maxValue = 1.0f;
	sliderWidth = 16.0f;
	sliderHeight = 16.0f;
	width = 100.0f + sliderWidth;
	height = sliderHeight;
	sliderOriginX = 12.0f;
	sliderOriginY = 12.0f;

	backColor[0] = .0f;
	backColor[1] = .0f;
	backColor[2] = .0f;
	backColor[3] = .4f;
}

UIValueSlider::~UIValueSlider(){}

// Get slider value 
float UIValueSlider::getValue(){
	return 
		// Start with minimum value 
		minValue + 
		// Convert sliderloc to a percentage of the slider as a whole
		(((sliderLoc - (sliderWidth/2.0f)) / 100.0f) * 
		// Multiply this to value range 
		(maxValue - minValue));
}

// Set slider value
void UIValueSlider::setValue(float value){
	float percent = (value - minValue) / (maxValue - minValue);
	sliderLoc = (sliderWidth/2.0f) + (percent * 100.0f);
}

// Set min value
void UIValueSlider::setMinValue(float value){
	minValue = value;
}

// Set max value
void UIValueSlider::setMaxValue(float value){
	maxValue = value;
}

// Update Button
void UIValueSlider::update(float deltaTime){
	UITransitionObject::update(deltaTime);

	clampSlider();
}

// Update button input 
void UIValueSlider::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIObject::updateInput(mKeyH, mMouseH);
	if (shown()){
		// Check if slider is hovered
		if (sliderContains(mMouseH->getX(), mMouseH->getY()))
			hovered = true;
		else {
			hovered = false;
		}

		// Check to see if mouse is pressing slider 
		if (hovered && mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
			down = true;
			mouseOffx = mMouseH->getX() - (sliderLoc + loc_x);
		}

		// Check movement and release 
		if (down){
			sliderLoc = mMouseH->getX() - loc_x - mouseOffx;
			clampSlider();

			if (!mMouseH->isLeftDown())
				down = false;
		}
	}
}

// Draw the button to the screen
// UIAtles must be bound first.
void UIValueSlider::draw(GLHandler* mgl, UIAtlas* mAtlas){
	if (flatColor[3] != 0.0f){
		// Draw image 
		mgl->setFlatColor(backColor[0], backColor[1], backColor[2], backColor[3] * flatColor[3] * mOpacity);
		mAtlas->drawScale2(mgl, UII_REC,loc_x ,loc_y, width, height);
		mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
		mAtlas->draw(mgl, UII_CHECKBOX_NORMAL, loc_x + sliderLoc, loc_y + 8.0f,
			1.0f,0.0f,sliderOriginX, sliderOriginY);
	}
}

// Check if location is inside slier 
bool UIValueSlider::sliderContains(float x, float y){
	if (x > loc_x + sliderLoc - (sliderWidth /2.0f) && x < loc_x + sliderLoc + (sliderWidth /2.0f) &&
		y > loc_y && y < loc_y + sliderHeight)
		return true;
	return false;
}

// Clamp slider if out of range 
void UIValueSlider::clampSlider(){
	if (sliderLoc < (sliderWidth /2.0f))
		sliderLoc = (sliderWidth /2.0f);
	if (sliderLoc > width - (sliderWidth /2.0f))
		sliderLoc = width - (sliderWidth /2.0f);
}