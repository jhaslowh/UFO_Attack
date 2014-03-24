#pragma once
#include "UIBox.h"
#include "UILabel.h"
#include "UITransitionObject.h"
#include "Sprite.h"

class UIEquipBox : public UITransitionObject
{
	UIBox* bBG;		// Background box containing elements
	UILabel* label;	// Label for the box 
	// States
	bool clicked, hovered, down;

	int item;		// Index of item 

	bool resetSprite;
	Sprite imageSprite;

public:
	UIEquipBox();
	virtual ~UIEquipBox();

	// Set item index
	void setItem(int index);
	// Get item index
	int getItem();

	// Call if object has child objects that need to be set up
	virtual void init(float screen_width, float screen_height);
	// Call if object has child objects that need to be unloaded
	virtual void unload();

	// Update the object
	virtual void update(float deltaTime);
	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Call to draw image sprite 
	void drawSprite(GLHandler* mgl);
	
	// Instantly hide the object
	virtual void setHidden();
	// Instantly show the object 
	virtual void setShown();

	// Check if the box was clicked 
	bool wasClicked();
};

