#pragma once
#include "GLColors.h"
#include "UIScreen.h"
#include "UILabel.h"
#include "UIButton.h"
#include "UIScrollbar.h"
#include "UIEquipBox.h"
#include "SaveData.h"
#include "FileHelper.h"

// Selection types 
#define PLAYER_WEAPON_1 0
#define PLAYER_WEAPON_2 1
#define UFO_WEAPON_1 2
#define UFO_WEAPON_2 3

class EquipScreen: public UIScreen
{
	// Reference to savedata 
	SaveData* saveData;

	// UI Objects 
	UILabel* lTitle;
	UIButton* bBack;
	UIScrollbar* scrollbar;

	// Dividers 
	Rec topDivider;
	Rec sideDivider;

	// Selection 
	Rec selectionRec;
	int selectedType;			// Which weapon type is selected
	UIEquipBox* weaponList;		// List of weapons for player to select from 
	float weaponListLocX;		// X location for the weapon list 
	float weaponListLocY;		// Starting location for list 
	int itemsToShow;			// list items to show (how many one scroll bar will cover)
	int weaponListCount;		// Count of current items on list 	

	// UI objects for for selected items 
	UIEquipBox* ebPlayer1;
	UIEquipBox* ebPlayer2;
	UIEquipBox* ebUFO1;
	UIEquipBox* ebUFO2;
	UILabel* player1;
	UILabel* player2;
	UILabel* ufo1;
	UILabel* ufo2;

public:
	EquipScreen(SaveData* data);
	virtual ~EquipScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height, void* sh);

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

	// Set the selected item for the store 
	void setSelectedItem(int i);

private:

	// Call to fix the list of weapons 
	void fixWeaponList();
};

