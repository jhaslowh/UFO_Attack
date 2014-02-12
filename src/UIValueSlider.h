#pragma once
#include "UITransitionObject.h"

class UIValueSlider : public UITransitionObject
{
	// Down value 
	bool down, hovered;
	// Slider location
	float sliderLoc;
	// Value for slider
	float value;
	// Slider minimum
	float minValue;
	// Slider maximum;
	float maxValue;
	// Slider width and height (width and height of square)
	// This is smaller than the actual image 
	float sliderWidth, sliderHeight;
	// Slider origin (Origin of entire image)
	float sliderOriginX, sliderOriginY;
	// Mouse offset 
	float mouseOffx;
	// Background color
	GLfloat backColor[4];

public:
	UIValueSlider();
	virtual ~UIValueSlider();

	// Get slider value 
	float getValue();
	// Set slider value
	void setValue(float value);
	// Set min value
	void setMinValue(float value);
	// Set max value
	void setMaxValue(float value);

	// Update slider 
	virtual void update(float deltaTime);
	// Update slider input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the slider to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Check if location is inside slier 
	bool sliderContains(float x, float y);

private:

	// Clamp slider if out of range 
	void clampSlider();
};

