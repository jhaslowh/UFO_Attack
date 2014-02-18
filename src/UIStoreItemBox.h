#pragma once
#include "UITransitionObject.h"
#include "UIBox.h"

class UIStoreItemBox : public UITransitionObject
{
	UIBox* bBG;

public:
	UIStoreItemBox();
	virtual ~UIStoreItemBox();
	
	// Call if object has child objects that need to be set up
	virtual void init(float screen_width, float screen_height);
	// Call if object has child objects that need to be loaded
	virtual void load(TextureAtlas* mAtlas);

	// Update the object
	virtual void update(float deltaTime);
	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Instantly hide the object
	virtual void setHidden();
	// Instantly show the object 
	virtual void setShown();
};

