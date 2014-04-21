#pragma once
#include "UIScreen.h"
#include "UILabel.h"
#include "UIBox.h"
#include "UIButton.h"
#include "UIStoreItemBox.h"
#include "UIAtlas.h"
#include "StoreItems.h"
#include "UIScrollbar.h"
#include "AtlasSprite.h"
#include "GLColors.h"
#include "SaveData.h"
#include "Sprite.h"
#include "StoreItems.h"

class StoreScreen : public UIScreen
{
	SaveData* savedata;

	UILabel* lTitle;
	UIBox* bDesc;
	UIButton* bBack;
	UIButton* bBuy;
	UIScrollbar* scrollbar;
	UILabel* lPlayerAnimalMoney;
	UILabel* lPlayerHumanMoney;
	AtlasSprite mCSAnimalPlayer;
	AtlasSprite mCSHumanPlayer;

	UIStoreItemBox* mStoreBoxes;
	// (Sorry for the bad comments on these, they are hard to describe)
	float storeItemsTop;		// Top of showable store item locations
	float storeItemsBottom;		// Bottom of showable store item locations
	float storeItemsMin;		// Minimum scroll location for store item locations
	float storeItemsLoc;		// Current store item location 
	float storeItemHeight;		// The height of a single store item 

	// Selected item elements 
	int selectedItem;			// Selected store item index
	UILabel* lSelName;			// Selected store item name 
	UILabel* lSelDesc;			// Selected store item description 
	UILabel* lSelHumanPrice;	// Selected store item human price
	UILabel* lSelAnimalPrice;	// Selected store item animal price
	UILabel* lPurchsed;			// Purchased state of store item 
	AtlasSprite mCSAnimalSelect;// Animal currency symbol
	AtlasSprite mCSHumanSelect;	// Human currency symbol 

	bool setupSprite;			// Set to true to load the selected item
	Sprite siImage;				// Sprite for selected item 

public:
	StoreScreen(SaveData* sd);
	virtual ~StoreScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height, void* sh);

	// Load screen
	virtual void load(TextureAtlas* mAtlas);
	
	// Unload screen textures
	// THIS MUST BE CALLED IF YOU LOAD STUFF.
	virtual void unload();

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

	// Set the selected item for the store 
	void setSelectedItem(int i);
};

