#pragma once
#include "UIObject.h"
#include "GLColors.h"

class UICreditsBox : public UIObject
{
	std::string title;
	std::string subtitle;
	float textSize;

public:
	UICreditsBox();
	UICreditsBox(std::string t, std::string subtitle);
	virtual ~UICreditsBox();

	// Call to reset up credits box 
	void setup(std::string t, std::string subtitle);
	
	float getTextHeight();

	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Draw the object to the screen at sent offset.
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy);
};

