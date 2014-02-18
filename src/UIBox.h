#pragma once
#include "UITransitionObject.h"

class UIBox : public UITransitionObject
{
	float cornerWidth;
	float mAlpha;

public:
	UIBox(float x, float y, float w, float h);
	virtual ~UIBox();

	// Set box alpha
	void setAlpha(float value);

	// Draw box 
	virtual void draw(GLHandler* mgl, UIAtlas* mUI); 

	// Draw box at offset 
	virtual void draw(GLHandler* mgl, UIAtlas* mUI, float offx, float offy); 
};

