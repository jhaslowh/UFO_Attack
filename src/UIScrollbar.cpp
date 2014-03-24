#include "UIScrollbar.h"


UIScrollbar::UIScrollbar(int type, float w, float h)
{
	// Set type and clamp
	mType = type;
	if (mType != SCROLLBAR_HOR && mType != SCROLLBAR_VERT)
		mType = SCROLLBAR_HOR;
	// Set width and height
	width = w;
	height = h;

	// Set slider area 
	if (mType == SCROLLBAR_HOR){
		sliderArea.setLocation(loc_x + width - (width*.1f), loc_y);
		sliderArea.setSize(width * .1f, height);
	}
	else {
		sliderArea.setLocation(loc_x, loc_y + height - (height*.1f));
		sliderArea.setSize(width,height * .1f);
	}

	// Set slider color
	sliderColor[0] = 0.0f;
	sliderColor[1] = .6f;
	sliderColor[2] = 1.0f;
	sliderColor[3] = 1.0f;

	// Set defaults 
	down = false;
	hovered = false;
	minVal = 0.0f;
	maxVal = 100.0f;
}

UIScrollbar::~UIScrollbar(){}

// Set location 
void UIScrollbar::setLocation(float x, float y){
	UIObject::setLocation(x, y);

	if (mType == SCROLLBAR_HOR)
		sliderArea.setLocation(loc_x + width - (width*.1f), loc_y);
	else
		sliderArea.setLocation(loc_x, loc_y + height - (height*.1f));
}

// Set x
void UIScrollbar::setX(float x){
	UIObject::setX(x);

	if (mType == SCROLLBAR_HOR)
		sliderArea.setX(loc_x + width - (width*.1f));
	else
		sliderArea.setX(loc_x);
}

// Set y
void UIScrollbar::setY(float y){
	UIObject::setY(y);

	if (mType == SCROLLBAR_HOR)
		sliderArea.setY(loc_y);
	else
		sliderArea.setY(loc_y + height - (height*.1f));
}

// Set the slider size
void UIScrollbar::setSliderSize(float s){
	// Check which type of scrollbar this is 
	// and set its size acordingly. 
	if (mType == SCROLLBAR_HOR){
		if (s < width){
			sliderArea.setWidth(s);
			clampSlider();
		}
	}
	else {
		if (s < height){
			sliderArea.setHeight(s);
			clampSlider();
		}
	}
}
// Set value
void UIScrollbar::setValue(float value){
	if (value < minVal || value > maxVal) return;
	if (mType == SCROLLBAR_HOR){
		sliderArea.setX(
			loc_x + ((width - sliderArea.getWidth()) * (value/(maxVal - minVal))));
	}
	else {
		sliderArea.setY(
			loc_y + ((height - sliderArea.getHeight()) * (value/(maxVal - minVal))));
	}
}
// Get value
float UIScrollbar::getValue(){
	if (mType == SCROLLBAR_HOR){
		return ((sliderArea.getX() - loc_x)/(width - sliderArea.getWidth())) * (maxVal - minVal);
	}
	else {
		return ((sliderArea.getY() - loc_y)/(height - sliderArea.getHeight())) * (maxVal - minVal);
	}
}
// Set max
void UIScrollbar::setMax(float m){
	maxVal = m;
}
// Get max
float UIScrollbar::getMax(){
	return maxVal;
}
// Set min 
void UIScrollbar::setMin(float m){
	minVal = m;
}
// Get min 
float UIScrollbar::getMin(){
	return minVal;
}
// Set slider color
void UIScrollbar::setSliderColor(float r, float g, float b, float a){
	sliderColor[0] = r;
	sliderColor[1] = g;
	sliderColor[2] = b;
	sliderColor[3] = a;
}

// Update the button 
void UIScrollbar::update(float deltaTime){
	UITransitionObject::update(deltaTime);
	
	// Fix location for slider
	// this is needed so that hide and show works 
	if (mType == SCROLLBAR_HOR)
		sliderArea.setY(loc_y);
	else
		sliderArea.setX(loc_x);
}

// Update input 
void UIScrollbar::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIObject::updateInput(mKeyH, mMouseH);
	if (shown()){
		// Check if slider is hovered
		if (sliderArea.contains(mMouseH->getX(), mMouseH->getY()))
			hovered = true;
		else {
			hovered = false;
		}

		// Check to see if mouse is pressing slider 
		if (hovered && mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
			down = true;
			mouseOffx = mMouseH->getX() - sliderArea.getX();
			mouseOffy = mMouseH->getY() - sliderArea.getY();
		}

		// Check movement and release 
		if (down){
			sliderArea.setX(mMouseH->getX() - mouseOffx);
			sliderArea.setY(mMouseH->getY() - mouseOffy);
			clampSlider();

			if (!mMouseH->isLeftDown())
				down = false;
		}

		// Update wheel scrolling 
		if (contains(mMouseH->getX(), mMouseH->getY())){
			updateMouseScroll(mMouseH);
		}
	}
}

// Call to update the mouse scroll wheel functions 
// for this scrollbar globaly. 
void UIScrollbar::updateMouseScroll(MouseHandler* mMouseH){
	if (mMouseH->scrollUp()){
		if (mType == SCROLLBAR_HOR)
			sliderArea.setX(sliderArea.getX() - (width * .05f));
		else
			sliderArea.setY(sliderArea.getY() - (height * .05f));
		clampSlider();
	}
	if (mMouseH->scrollDown()){
		if (mType == SCROLLBAR_HOR)
			sliderArea.setX(sliderArea.getX() + (width * .05f));
		else
			sliderArea.setY(sliderArea.getY() + (height * .05f));
		clampSlider();
	}
}

// Draw the object to the screen
// UIAtles must be bound first.
void UIScrollbar::draw(GLHandler* mgl, UIAtlas* mAtlas){
	mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
	mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y, width, height);
	mgl->setFlatColor(sliderColor, sliderColor[3] * flatColor[3] * mOpacity);
	mAtlas->drawScale2(mgl, UII_REC, sliderArea.getX(), sliderArea.getY(), sliderArea.getWidth(), sliderArea.getHeight());
}

// Clamp slider value 
void UIScrollbar::clampSlider(){
	if (mType == SCROLLBAR_HOR){
		if (sliderArea.getX() < loc_x)
			sliderArea.setX(loc_x);
		else if (sliderArea.getX() + sliderArea.getWidth() > loc_x + width)
			sliderArea.setX(loc_x + width - sliderArea.getWidth());
	}
	else{
		if (sliderArea.getY() < loc_y)
			sliderArea.setY(loc_y);
		else if (sliderArea.getY() + sliderArea.getHeight() > loc_y + height)
			sliderArea.setY(loc_y + height - sliderArea.getHeight());
	}
}