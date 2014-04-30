#include "UIComboBox.h"


UIComboBox::UIComboBox(float x, float y) : UITransitionObject(){
	// Set parent properties
	loc_x = x;
	loc_y = y;
	width = 200;
	height = 20;
	flatColor[0] = .175f;
	flatColor[1] = .175f;
	flatColor[2] = .175f;
	flatColor[3] = 1.0f;

	// Set properties 
	expandBox.reset(0,width-height,height,height);
	listBox.reset(0,height, width,0);
	expandButton = NULL;
	scrollbar = NULL;
	itemCount = 0;
	selectedItem = 0;
	mouseItem = -1;
	itemsToDisplay = 0;
	items = NULL;
	showScrollBar = false;
	showList = false;
	itemSelected = false;
	scrollOffset = 0;
	maxItemsToDisplay = 4;

	// Text and graphics 
	textColor[0] = .6f;
	textColor[1] = .6f;
	textColor[2] = .6f;
	textColor[3] = 1.0f;
	listTextColor[0] = .2f;
	listTextColor[1] = .2f;
	listTextColor[2] = .2f;
	listTextColor[3] = 1.0f;
	highlightColor[0] = .457f;
	highlightColor[1] = .652f;
	highlightColor[2] = .816f;
	highlightColor[3] = 1.0f;
	mouseHoverColor[0] = .445f;
	mouseHoverColor[1] = .74f;
	mouseHoverColor[2] = 1.0f;
	mouseHoverColor[3] = 1.0f;
	listBGColor[0] = .32f;
	listBGColor[1] = .32f;
	listBGColor[2] = .32f;
	listBGColor[3] = 1.0f;
	textOffset[0] = 4.0f;
	textOffset[1] = 3.0f;
	textSize = 16.0f;
}

UIComboBox::~UIComboBox(){
	delete scrollbar;
	delete expandButton;
	delete[] items;
}

// Set combobox items 
void UIComboBox::setItems(std::string* v, unsigned size){
	// Delete old array
	delete items;
	// Set sent array as item array
	items = v;
	// Fix size 
	itemCount = size;
	// Fix display properties 
	fixDisplayCount(); 
}

// Add item to the list 
void UIComboBox::addItem(std::string value){
	// Create new array of bigger size 
	std::string* newItems = items;
	items = new std::string[itemCount+1];
	// Move elements back into arrray
	for (int i = 0; i < itemCount; i++)
		items[i] = newItems[i];
	// Delete old array 
	delete[] newItems;
	// Add sent item to array 
	items[itemCount] = value;
	// Increase item count 
	itemCount++;
	// Fix display properties 
	fixDisplayCount();
}

// Return selected item
std::string UIComboBox::getSelectedItem(){
	if (selectedItem > -1 && selectedItem < itemCount)
		return items[selectedItem];
	return "none";
}

// Return selected index
int UIComboBox::getSelectedIndex(){
	return selectedItem;
}

// Set max items to display
void UIComboBox::setMaxItemsToDisplay(int value){
	if (value >= 1){
		maxItemsToDisplay = value;
		fixDisplayCount();
	}
}

// Check if an item was selected
bool UIComboBox::wasItemSelected(){
	if (itemSelected){
		itemSelected = false;
		return true;
	}
	return false;
}

// Set the selected item
void UIComboBox::setSelectedItem(int value){selectedItem = value;}

// Call if object has child objects that need to be set up
void UIComboBox::init(float screen_width, float screen_height){
	UIObject::init(screen_width, screen_height);

	expandButton = new UIButton(loc_x + width - height,
		loc_y,height, height, std::string("Expand"));

	scrollbar = new UIScrollbar(SCROLLBAR_VERT, 15.0f, itemsToDisplay * height);
	scrollbar->setLocation(loc_x + width - 15.0f, loc_y + height);
	scrollbar->setColor(0.1f,0.1f,0.1f);
	scrollbar->setValue(0.0f);
}

// Update the button 
void UIComboBox::update(float deltaTime){
	UITransitionObject::update(deltaTime);

	// Update scrollbar
	scrollbar->update(deltaTime);
}

// Update input 
void UIComboBox::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIObject::updateInput(mKeyH, mMouseH);

	// If list is not shown 
	if (!showList){
		// Check if expand button was clicked 
		expandButton->updateInput(mKeyH, mMouseH);
		// If button was clicked, request focus and show list 
		if (expandButton->wasClicked()){
			showList = true;
			reqFocus = true;
		}
	}
}

// Update focus input 
// Return false to remove focus. 
bool UIComboBox::updateInputFocus(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIObject::updateInputFocus(mKeyH, mMouseH);

	// Check if listbox contains 
	if (listBox.contains(mMouseH->getX(), mMouseH->getY(), loc_x, loc_y) && 
		!scrollbar->contains(mMouseH->getX(), mMouseH->getY())){
		
		// Get y value inside listbox 
		float v = mMouseH->getY() - (loc_y + height);
		mouseItem = (int)(v / height) + scrollOffset;

		if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
			selectedItem = mouseItem;
			itemSelected = true;
			showList = false;
			return false;
		}
	}

	// Update scroll bar input
	if (showScrollBar){
		scrollbar->updateInput(mKeyH, mMouseH);
		scrollbar->updateMouseScroll(mMouseH);
		scrollOffset = (int)scrollbar->getValue();
	}

	// Check if expand button was clicked 
	expandButton->updateInput(mKeyH, mMouseH);
	// If button was clicked, lose focus and hide list 
	if (expandButton->wasClicked()){
		showList = false;
		return false;
	}

	// Lose focus if clicked outside of combobox 
	if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown() &&
		!contains(mMouseH->getX(), mMouseH->getY()) &&
		!listBox.contains(mMouseH->getX(), mMouseH->getY(), loc_x, loc_y)){
		showList = false;
		return false;
	}

	// Keep focus otherwise 
	return true;
}

// Draw the object to the screen
// UIAtles must be bound first.
void UIComboBox::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UITransitionObject::draw(mgl, mAtlas);

	// Draw main background 
	mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
	mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y,width, height);

	// Draw selected item 
	if (selectedItem >= 0 && selectedItem < itemCount){
		mgl->setFlatColor(textColor);
		mAtlas->mTextRender->drawText(*mgl, items[selectedItem], loc_x + textOffset[0],
			loc_y + textOffset[1], 0.0f, textSize);
	}

	// Draw list arrow 
	if (!showList){
		mgl->setFlatColor(COLOR_WHITE);
		mAtlas->draw(mgl, UII_COMBOBOX_ARROW, loc_x + width - 20.0f, loc_y);
	}
}


// Draw the object to the screen at sent offset.
// UIAtles must be bound first.
void UIComboBox::draw(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy){
	UIObject::draw(mgl, mAtlas, offx, offy);

	// TODO 
}


// Draw the object focus elements to the screen
// UIAtles must be bound first.
void UIComboBox::drawFocus(GLHandler* mgl, UIAtlas* mAtlas){
	UIObject::drawFocus(mgl, mAtlas);
	
	// Draw listbox background 
	mgl->setFlatColor(listBGColor, listBGColor[3] * mOpacity);
	mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y + listBox.getY(),
		listBox.getWidth(), listBox.getHeight());
	
	// Draw other items 
	for (int i = 0; i < itemsToDisplay; i++){
		if (i + scrollOffset == selectedItem){
			mgl->setFlatColor(highlightColor, highlightColor[3] * mOpacity);
			mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y + (height * (i+1)), width, height);
		}
		if (i + scrollOffset == mouseItem){
			mgl->setFlatColor(mouseHoverColor, mouseHoverColor[3] * mOpacity);
			mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y + (height * (i+1)), width, height);
		}

		mgl->setFlatColor(listTextColor, listTextColor[3] * mOpacity);
		mAtlas->mTextRender->drawText(*mgl, items[i + scrollOffset], 
			loc_x + textOffset[0],
			loc_y + textOffset[1] + (height * (i+1)), 0.0f, textSize);
	}

	// Draw scroll bar 
	if (showScrollBar)
		scrollbar->draw(mgl, mAtlas);

	// Draw arrow 
	mgl->setFlatColor(COLOR_WHITE);
	mAtlas->draw(mgl, UII_COMBOBOX_ARROW, loc_x + width, loc_y + 20.0f,1.0f, 180.0f);
}


// Draw the object focus elements to the screen at sent offset.
// UIAtles must be bound first.
void UIComboBox::drawFocus(GLHandler* mgl, UIAtlas* mAtlas, float offx, float offy){
	UIObject::drawFocus(mgl, mAtlas, offx, offy);

	// TODO 
}

// Check if the sent item is in the combobox 
int UIComboBox::findIndex(std::string item){
	for (int i = 0; i < itemCount; i++){
		if (item == items[i])
			return i;
	}
	return -1;
}

// Fix item to display count
void UIComboBox::fixDisplayCount(){
	if (itemCount > maxItemsToDisplay){
		itemsToDisplay = maxItemsToDisplay;
		showScrollBar = true;
	}
	else {
		itemsToDisplay = itemCount;
		showScrollBar = false;
	}

	// Fix scrollbar
	if (showScrollBar){
		scrollbar->setSize(15.0f, itemsToDisplay * height);
		scrollbar->setMax((itemCount - itemsToDisplay) + .5f);
		scrollbar->setSliderSize((4.0f / (float)itemCount) * (itemsToDisplay * height));
	}

	// Fix list box height 
	listBox.setHeight(itemsToDisplay * height);
}
