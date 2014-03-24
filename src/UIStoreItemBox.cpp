#include "UIStoreItemBox.h"


UIStoreItemBox::UIStoreItemBox()
{
	width = 140.0f;
	height = 60.0f;
	bBG = NULL;
	purchased = false;
	index = -1;
	lName = NULL;
	lPriceA = NULL;
	lPriceH = NULL;
	lPurchase = NULL;
	clicked = false;
	hovered = false;
	down = false;
}

UIStoreItemBox::~UIStoreItemBox()
{
	delete bBG;
	delete lName;
	delete lPriceA;
	delete lPriceH;
	delete lPurchase;
}

// Set store item by index 
void UIStoreItemBox::setItem(int i){
	index = i;

	StoreItem* si = &(StoreItems::sItems.at(i));

	lName->setText(si->getName());
	lPriceA->setText(toString(si->getAnimalPrice()));
	lPriceH->setText(toString(si->getHumanPrice()));
}

// Tell this item that it is purchased 
void UIStoreItemBox::setPurchased(bool value){
	purchased = value;
}
// Get index for item
int UIStoreItemBox::getIndex(){return index;}

// Call if object has child objects that need to be set up
void UIStoreItemBox::init(float screen_width, float screen_height){
	UIObject::init(screen_width, screen_height);
	
	bBG = new UIBox(0,0,width, height);
	
	lName = new UILabel("name");
	lName->setTextSize(14.0f);
	lName->setLocation(5.0f,5.0f);
	lName->setColor(.9f,.9f,.9f);

	lPurchase = new UILabel("Purchased");
	lPurchase->setTextSize(14.0f);
	lPurchase->setLocation(5.0f,24.0f);
	lPurchase->setColor(.45f,.95f,.23f);
	
	mCSAnimal.setID(UII_CURRENCY_ANIMAL);
	mCSAnimal.setPosition(5.0f, 22.0f);
	mCSAnimal.setScale(.75f);

	lPriceA = new UILabel("0");
	lPriceA->setTextSize(14.0f);
	lPriceA->setLocation(22.0f,24.0f);
	lPriceA->setColor(.9f,.9f,.9f);
	
	mCSHuman.setID(UII_CURRENCY_HUMAN);
	mCSHuman.setPosition(5.0f, 42.0f);
	mCSHuman.setScale(.75f);

	lPriceH = new UILabel("0");
	lPriceH->setTextSize(14.0f);
	lPriceH->setLocation(22.0f, 44.0f);
	lPriceH->setColor(.9f,.9f,.9f);

}
// Call if object has child objects that need to be loaded
void UIStoreItemBox::load(TextureAtlas* mAtlas){
	UIObject::load(mAtlas);

}

// Update the object
void UIStoreItemBox::update(float deltaTime){
	UITransitionObject::update(deltaTime);

	bBG->setAlpha(flatColor[3] * mOpacity);
	lName->setAlpha(flatColor[3] * mOpacity);
	lPriceA->setAlpha(flatColor[3] * mOpacity);
	lPriceH->setAlpha(flatColor[3] * mOpacity);
	lPurchase->setAlpha(flatColor[3] * mOpacity);
}

// Update input 
void UIStoreItemBox::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UITransitionObject::updateInput(mKeyH, mMouseH);
	if (shown() && flatColor[3] > .5f){
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
void UIStoreItemBox::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UITransitionObject::draw(mgl, mAtlas);

	bBG->draw(mgl, (UIAtlas*)mAtlas, loc_x, loc_y);
	lName->draw(mgl, (UIAtlas*)mAtlas, loc_x, loc_y);

	if (purchased)
		lPurchase->draw(mgl, (UIAtlas*)mAtlas, loc_x, loc_y);
	else {
		lPriceA->draw(mgl, (UIAtlas*)mAtlas, loc_x, loc_y);
		lPriceH->draw(mgl, (UIAtlas*)mAtlas, loc_x, loc_y);

		mgl->setFlatColor(COLOR_WHITE, bBG->getAlpha());
		mCSAnimal.draw(mgl, mAtlas, loc_x, loc_y);
		mCSHuman.draw(mgl, mAtlas, loc_x, loc_y);
	}
}

// Instantly hide the object
void UIStoreItemBox::setHidden(){
	UITransitionObject::setHidden();
	
	bBG->setAlpha(flatColor[3] * mOpacity);
	lName->setAlpha(flatColor[3] * mOpacity);
	lPriceA->setAlpha(flatColor[3] * mOpacity);
	lPriceH->setAlpha(flatColor[3] * mOpacity);
	lPurchase->setAlpha(flatColor[3] * mOpacity);
}

// Instantly show the object 
void UIStoreItemBox::setShown(){
	UITransitionObject::setShown();
	
	bBG->setAlpha(flatColor[3] * mOpacity);
	lName->setAlpha(flatColor[3] * mOpacity);
	lPriceA->setAlpha(flatColor[3] * mOpacity);
	lPriceH->setAlpha(flatColor[3] * mOpacity);
	lPurchase->setAlpha(flatColor[3] * mOpacity);
}

// Check if the button was clicked 
bool UIStoreItemBox::wasClicked(){
	if (clicked) {
		clicked = false;
		return true;
	}
	return false;
}