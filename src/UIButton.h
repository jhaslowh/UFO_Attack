#pragma once
#include "UITransitionObject.h"
#include <string>

#define UIB_TEXT_SIZE 20.0f

class UIButton : public UITransitionObject
{
	// Test offset 
	float text_x, text_y;
	// States
	bool clicked, hovered, down;
	// Text 
	std::string label;
	
	GLfloat textColor[4];

	// Shadow variables
	GLfloat shadowColor[4];
	bool drawShadow;
	float shadowOffX, shadowOffY;

public:
	UIButton();
	UIButton(float x, float y, float w, float h, std::string l);
	virtual ~UIButton();

	// Getters and Setters 
	void setLabel(std::string l);
	std::string getLabel();

	// Update button 
	virtual void update(float deltaTime);
	// Update button input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the button to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Check if the button was clicked 
	bool wasClicked();
	// Center label text 
	void centerText(TextRender* mTR);
};

