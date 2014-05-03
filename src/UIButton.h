#pragma once
#include <string>
#include "UITransitionObject.h"
#include "GLColors.h"
#include "Rec.h"

#define UIB_TEXT_SIZE 20.0f
#define UIB_TT_TEXT_SIZE 14.0f

class UIButton : public UITransitionObject
{
protected: 
	// Test offset 
	float text_x, text_y;
	// States
	bool clicked, hovered, down;
	// Text 
	std::string label;
	// Images
	int imageID;
	int imageIDClick;
	int imageIDHover;
	
	GLfloat textColor[4];

	// Shadow variables
	GLfloat shadowColor[4];
	bool drawShadow;
	float shadowOffX, shadowOffY;

	// Tooltip
	bool showTooltip;
	float toolTipX, toolTipY;
	float toolTipW, toolTipH;
	std::string toolTipText;
	float ttShowTime;
	float cttShowTime;

public:
	UIButton();
	UIButton(float x, float y, float w, float h, std::string l);
	virtual ~UIButton();

	// Getters and Setters 
	void setLabel(std::string l);
	std::string getLabel();

	void setImageId(int value);
	void setImageIdClick(int value);
	void setImageIdHover(int value);

	// Update button 
	virtual void update(float deltaTime);
	// Update button input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Update focus input 
	// Return false to remove focus. 
	virtual bool updateInputFocus(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the button to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);
	
	// Draw the object focus elements to the screen
	// UIAtles must be bound first.
	virtual void drawFocus(GLHandler* mgl, UIAtlas* mAtlas);

	// Check if the button was clicked 
	bool wasClicked();
	// Center label text 
	void centerText(TextRender* mTR);

	// Set the tool tip for this button 
	void setTooltip(std::string text, float time);

	// Remove the tool tip from the button
	void removeToolTip();
};

