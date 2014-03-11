#pragma once
#include <string>
#include "UITransitionObject.h"
#include "Rec.h"
#include "UIScrollbar.h"
#include "UIButton.h"
#include "GLColors.h"

class UIComboBox : public UITransitionObject
{
	// -----------------
	// Collision and UI
	// -----------------
	// Rec area of box to click to expand combo box 
	Rec expandBox;			
	// Button for expand box 
	UIButton* expandButton;
	// Rec area of box to click drop down items 
	Rec listBox;
	// Scrollbar for drop down items 
	UIScrollbar* scrollbar;

	// ------------------
	// Items
	// ------------------
	// Total count of items
	int itemCount;
	// Selected item
	int selectedItem;
	// Mouse selected index 
	int mouseItem;
	// Total number of items to display on dropdown
	int itemsToDisplay;
	// List of items
	std::string* items;
	// Display Scroll Bar
	bool showScrollBar;
	// Toggle to display list below box 
	bool showList;
	// Offset for scrollbar index
	int scrollOffset;
	// Max Items to display in list
	int maxItemsToDisplay;
	// Set to true when an item is selected
	bool itemSelected;

	// ------------------
	// Text and graphics 
	// ------------------
	// Text color
	GLfloat textColor[4];
	// list text color
	GLfloat listTextColor[4];
	// Hightlight color for selected item 
	GLfloat highlightColor[4];
	// Mouse hover color
	GLfloat mouseHoverColor[4];
	// List background color
	GLfloat listBGColor[4];
	// Text offset 
	float textOffset[2];
	// Size for display text 
	float textSize;

public:
	UIComboBox(float x, float y);
	virtual ~UIComboBox();

	// Set combobox items 
	void setItems(std::string* v, unsigned size);
	// Add item to the list 
	void addItem(std::string value);
	// Return selected item
	std::string getSelectedItem();
	// Return selected index
	int getSelectedIndex();
	// Set max items to display
	void setMaxItemsToDisplay(int value);
	// Check if an item was selected
	bool wasItemSelected();
	// Set the selected item
	void setSelectedItem(int value);

	// Call if object has child objects that need to be set up
	virtual void init(float screen_width, float screen_height);

	// Update the button 
	virtual void update(float deltaTime);
	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Update focus input 
	// Return false to remove focus. 
	virtual bool updateInputFocus(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Draw the object to the screen at sent offset.
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy);

	// Draw the object focus elements to the screen
	// UIAtles must be bound first.
	virtual void drawFocus(GLHandler* mgl, UIAtlas* mAtlas);

	// Draw the object focus elements to the screen at sent offset.
	// UIAtles must be bound first.
	virtual void drawFocus(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy);

	// Check if the sent item is in the combobox 
	int findIndex(std::string item);

private:
	// Fix item to display count
	void fixDisplayCount();
};

