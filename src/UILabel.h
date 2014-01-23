#pragma once
#include <string>
#include "UITransitionObject.h"

class UILabel : public UITransitionObject
{
	string text;
	float textSize;

public:
	UILabel(string l);
	virtual ~UILabel();

	// Getters and setters 
	string getText();
	void setText(string l);
	float getTextSize();
	void setTextSize(float size);

	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);
};

