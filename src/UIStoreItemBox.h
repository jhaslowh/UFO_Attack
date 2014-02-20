#pragma once
#include "UITransitionObject.h"
#include "UIBox.h"
#include "UILabel.h"
#include "StoreItems.h"
#include "AtlasSprite.h"
#include "GLColors.h"

class UIStoreItemBox : public UITransitionObject
{
	UIBox* bBG;				// Background box containing elements
	UILabel* lName;			// Label for object name
	UILabel* lPriceA;		// Label for object price animal
	UILabel* lPriceH;		// Label for object price human
	UILabel* lPurchase;		// Label for object purchase state 
	AtlasSprite mCSAnimal;  // Animal currency sprite
	AtlasSprite mCSHuman;	// Human currency sprite 

	// States
	bool clicked, hovered, down;

	bool purchased;			// Bool that is true if purchesed
	int index;				// Item index number

public:
	UIStoreItemBox();
	virtual ~UIStoreItemBox();

	// Set store item by index 
	void setItem(int i);
	// Tell this item that it is purchased 
	void setPurchased(bool value);
	// Get index for item
	int getIndex();
	
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
	// Check if the box was clicked 
	bool wasClicked();
};

