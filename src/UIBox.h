#pragma once
#include "UITransitionObject.h"

class UIBox : public UITransitionObject
{
	float cornerWidth;

public:
	UIBox(float x, float y, float w, float h);
	virtual ~UIBox();

	// Draw box 
	virtual void draw(GLHandler* mgl, UIAtlas* mUI); 

	// Draw box at offset 
	virtual void draw(GLHandler* mgl, UIAtlas* mUI, float offx, float offy); 
};

