#pragma once
#include <string>
#include "UITransitionObject.h"

class UILabel : public UITransitionObject
{
	std::string text;
	float textSize;

public:
	UILabel(std::string l);
	virtual ~UILabel();

	// Getters and setters 
	std::string getText();
	void setText(std::string l);
	float getTextSize();
	void setTextSize(float size);

	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);
};

