#pragma once
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "GLHandler.h"
#include "UIAtlas.h"

#define UIB_TEXT_SIZE 20.0f

class UIButton
{
	// Location settings 
	float loc_x,loc_y,width,height;
	float text_x, text_y;
	bool clicked, hovered, down;
	char* label;
	
	GLfloat flatColor[4];
	GLfloat textColor[4];

public:
	UIButton();
	UIButton(float x, float y, float w, float h, char* l);
	~UIButton();

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
	bool wasClicked();
	// Check if the sent location is inside the button 
	bool contains(float x, float y);
	// Center label text 
	void centerText(TextRender* mTR);
};

