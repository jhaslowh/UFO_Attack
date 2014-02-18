#include "UIStoreItemBox.h"


UIStoreItemBox::UIStoreItemBox()
{
	width = 140.0f;
	height = 60.0f;
	bBG = NULL;
}

UIStoreItemBox::~UIStoreItemBox()
{
	delete bBG;
}

// Call if object has child objects that need to be set up
void UIStoreItemBox::init(float screen_width, float screen_height){
	UIObject::init(screen_width, screen_height);
	
	bBG = new UIBox(0,0,width, height);
}
// Call if object has child objects that need to be loaded
void UIStoreItemBox::load(TextureAtlas* mAtlas){
	UIObject::load(mAtlas);

}

// Update the object
void UIStoreItemBox::update(float deltaTime){
	UITransitionObject::update(deltaTime);

	bBG->setAlpha(flatColor[3]);
}

// Update input 
void UIStoreItemBox::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UITransitionObject::updateInput(mKeyH, mMouseH);

}

// Draw the object to the screen
// UIAtles must be bound first.
void UIStoreItemBox::draw(GLHandler* mgl, UIAtlas* mAtlas){
	UITransitionObject::draw(mgl, mAtlas);

	bBG->draw(mgl, (UIAtlas*)mAtlas, loc_x, loc_y);
}

// Instantly hide the object
void UIStoreItemBox::setHidden(){
	UITransitionObject::setHidden();

	bBG->setAlpha(0.0f);
}

// Instantly show the object 
void UIStoreItemBox::setShown(){
	UITransitionObject::setShown();

	bBG->setAlpha(1.0f);
}