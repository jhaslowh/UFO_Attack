#pragma once
#include "UITransitionObject.h"
#include "Rec.h"

#define SCROLLBAR_HOR 0
#define SCROLLBAR_VERT 1

class UIScrollbar : public UITransitionObject
{
	// Slider values
	float minVal, maxVal;
	// Slider color 
	GLfloat sliderColor[4];
	Rec sliderArea;
	// Mouse offsets
	float mouseOffx, mouseOffy;
	// States
	bool down, hovered;

	// Scrollbar type 
	int mType;

public:
	UIScrollbar(int type, float w, float h);
	virtual ~UIScrollbar();
	
	// Set location 
	virtual void setLocation(float x, float y);
	// Set x
	virtual void setX(float);
	// Set y
	virtual void setY(float);
	// Set the slider size
	void setSliderSize(float s);
	// Set value
	void setValue(float value);
	// Get value
	float getValue();
	// Set max
	void setMax(float m);
	// Get max
	float getMax();
	// Set min 
	void setMin(float m);
	// Get min 
	float getMin();
	// Set slider color
	void setSliderColor(float r, float g, float b, float a);

	// Update the button 
	virtual void update(float deltaTime);
	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Call to update the mouse scroll wheel functions 
	// for this scrollbar globaly. 
	void updateMouseScroll(MouseHandler* mMouseH);

	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

private:
	// Clamp slider value 
	void clampSlider();
};

