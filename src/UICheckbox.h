#pragma once
#include "UITransitionObject.h"
#include <string>

#define UIC_TEXT_SIZE 16.0f

class UICheckbox : public UITransitionObject
{
	// Location settings 
	float text_x, text_y;
	bool checked, hovered;
	bool down;
	std::string label;
	
	GLfloat textColor[4];

public:
	UICheckbox();
	UICheckbox(float x, float y, float w, float h, std::string l);
	~UICheckbox();

	// Getters and Setters 
	void setLabel(std::string l);
	std::string getLabel();
	void setTextColor(float r, float g, float b);
	void setChecked(bool value);

	// Update Checkbox
	virtual void update(float deltaTime);
	// Update button input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the button to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Check if the button was clicked 
	bool Checked();
};

