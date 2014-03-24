#include "UIEquipBox.h"

using namespace StoreItems;

UIEquipBox::UIEquipBox()
{
	
	width = 200.0f;
	height = 90.0f;
	bBG = NULL;
	label = NULL;
	clicked = false;
	hovered = false;
	down = false;
	item = -1;
	resetSprite = true;
}

UIEquipBox::~UIEquipBox()
{
	delete bBG;
	delete label;
}

// Set item index
void UIEquipBox::setItem(int index){
	if (index >= 0){
		item = index;
		resetSprite = true;
		label->setText(sItems.at(item).getName());
	}
}

// Get item index
int UIEquipBox::getItem(){return item;}

// Call if object has child objects that need to be set up
void UIEquipBox::init(float screen_width, float screen_height){
	UIObject::init(screen_width, screen_height);

	label = new UILabel("None");
	label->setTextSize(16.0f);
	label->setLocation(4.0f,4.0f);
	label->setColor(.9f,.9f,.9f);

	bBG = new UIBox(0.0f,0.0f,width, height);
}

// Call if object has child objects that need to be unloaded
void UIEquipBox::unload(){
	UIObject::unload();

	imageSprite.unload();
}

// Update the object
void UIEquipBox::update(float deltaTime){
	UITransitionObject::update(deltaTime);

	bBG->setAlpha(flatColor[3] * mOpacity);
	label->setAlpha(flatColor[3] * mOpacity);
	imageSprite.setAlpha(flatColor[3] * mOpacity);
}

// Update input 
void UIEquipBox::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIObject::updateInput(mKeyH, mMouseH);

	if (shown()){
		// Check if button is hovered
		if (contains(mMouseH->getX(), mMouseH->getY()))
			hovered = true;
		else {
			hovered = false;
			down = false;
		}

		// Check to see if mouse is pressing button 
		if (hovered && mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
			down = true;

		// Check if button is clicked
		if (hovered && down && !mMouseH->isLeftDown()){
			clicked = true;
			down = false;
		}
	}
}

// Draw the object to the screen
// UIAtles must be bound first.
void UIEquipBox::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UIObject::draw(mgl, mAtlas);

	bBG->draw(mgl, mAtlas, loc_x, loc_y);
	label->draw(mgl, mAtlas, loc_x, loc_y);
}

// Call to draw image sprite 
void UIEquipBox::drawSprite(GLHandler* mgl){
	if (resetSprite){
		imageSprite.unload();
		if (item >= 0)
			imageSprite.setup(290.0f, 100.0f, sItems.at(item).getImage());
		else 
			imageSprite.setup(290.0f, 100.0f, "images/si/sii_none.png");
		// Fix properties 
		imageSprite.setPosition(2.0f,18.0f);
		imageSprite.setScale(.7f);
	}

	imageSprite.draw(*mgl, loc_x, loc_y);
}


// Instantly hide the object
void UIEquipBox::setHidden(){
	UITransitionObject::setHidden();
	
	bBG->setAlpha(flatColor[3] * mOpacity);
	label->setAlpha(flatColor[3] * mOpacity);
	imageSprite.setAlpha(flatColor[3] * mOpacity);
}

// Instantly show the object 
void UIEquipBox::setShown(){
	UITransitionObject::setShown();
	
	bBG->setAlpha(flatColor[3] * mOpacity);
	label->setAlpha(flatColor[3] * mOpacity);
	imageSprite.setAlpha(flatColor[3] * mOpacity);
}

// Check if the box was clicked 
bool UIEquipBox::wasClicked(){
	if (clicked) {
		clicked = false;
		return true;
	}
	return false;
}
