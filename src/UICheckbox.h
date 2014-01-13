#pragma once
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "GLHandler.h"
#include "UIAtlas.h"

#define UIC_TEXT_SIZE 20.0f

class UICheckbox
{
	// Location settings 
	float loc_x,loc_y,width,height;
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
	void setLocation(float x, float y);
	float getX();
	float getY();
	void setSize(float w, float h);
	float getWidth();
	float getHeight();
	void setLabel(char* l);
	char* getLabel();

	// Update the button 
	void update(float deltaTime);
	// Update button input 
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the button to the screen
	// UIAtles must be bound first.
	void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Check if the button was clicked 
	bool Checked();
	// Check if the sent location is inside the button 
	bool contains(float x, float y);
};

