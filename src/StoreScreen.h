#pragma once
#include "UIScreen.h"
#include "UILabel.h"
#include "UIBox.h"
#include "UIButton.h"
#include "UIStoreItemBox.h"
#include "StoreItems.h"
#include "UIScrollbar.h"

class StoreScreen : public UIScreen
{
	UILabel* lTitle;
	UIBox* bDesc;
	UIButton* bBack;
	UIScrollbar* scrollbar;

	UIStoreItemBox* mStoreBoxes;
	float storeItemsMin, storeItemsMax;
	float storeItemsLoc;

public:
	StoreScreen();
	virtual ~StoreScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height);

	// Load screen
	virtual void load(TextureAtlas* mAtlas);

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Hide the entire screen.
	// Any UI elements will need to be put into this function,
    // if they should be hidden when the screen is hidden.
	virtual void hide();

	// Show the entire screen.
	// All UI elements in the hide screen method should have show 
	// calls here. 
	virtual void show();
};

