#pragma once
#include "UIObject.h"

#define UIC_TEXT_SIZE 20.0f

class UICheckbox : public UIObject
{
	// Location settings 
	float text_x, text_y;
	bool checked, hovered;
	char* label;
	
	GLfloat flatColor[4];
	GLfloat textColor[4];

public:
	UICheckbox();
	UICheckbox(float x, float y, float w, float h, char* l);
	~UICheckbox();

	// Getters and Setters 
	void setLabel(char* l);
	char* getLabel();

	// Update button input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the button to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Check if the button was clicked 
	bool Checked();
};

