#include "StoreScreen.h"
using namespace StoreItems;

StoreScreen::StoreScreen() : UIScreen()
{
	hideOnClose = true;
	lTitle = NULL;
	bDesc = NULL;
	bBack = NULL;
	bBuy = NULL;
	mStoreBoxes = NULL;
	scrollbar = NULL;
}

StoreScreen::~StoreScreen()
{
	delete lTitle;
	delete bDesc;
	delete bBack;
	delete bBuy;
	delete[] mStoreBoxes;
	delete scrollbar;
}

// Initialize screen
void StoreScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	// Menu location to easily move menu
	float menuX = screen_width * .55f;
	float menuY = screen_height * .3f;

	lTitle = new UILabel("Store");
	lTitle->setTextSize(60.0f);
	lTitle->setLocation(
		menuX - 300.0f,
		menuY - lTitle->getTextSize());
	lTitle->setupHide(HT_HOROZONTAL, lTitle->getX() - 200.0f, hideTime, true);
	lTitle->setColor(.9f,.9f,.9f);
	lTitle->setHidden();

	bDesc = new UIBox(menuX - 300.0f,menuY, 300.0f,300.0f);
	bDesc->setupHide(HT_VERTICAL, bDesc->getY() + 100, hideTime, true);
	bDesc->setHidden();

	bBack = new UIButton(menuX - 300.0f, menuY + 310.0f, 100.0f, 35.0f,"Back");
	bBack->setupHide(HT_VERTICAL, bBack->getY() + 100.0f, hideTime, true);
	bBack->setHidden();

	bBuy = new UIButton(menuX - 105.0f, menuY + 310.0f, 100.0f, 35.0f,"Buy");
	bBuy->setupHide(HT_VERTICAL, bBuy->getY() + 100.0f, hideTime, true);
	bBuy->setHidden();

	// Set store items

	mStoreBoxes = new UIStoreItemBox[STORE_ITEM_COUNT];
	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].init(screen_width, screen_height);
		mStoreBoxes[i].setLocation(menuX + 5.0f, menuY + (i * (mStoreBoxes[i].getHeight() + 5.0f)));
		mStoreBoxes[i].setupHide(HT_HOROZONTAL, mStoreBoxes[i].getX() + (rand() % 300 + 100), hideTime, true);
		mStoreBoxes[i].setHidden();
	}

	// Set locations
	storeItemsMin = menuY;
	storeItemsMax = menuY - ((STORE_ITEM_COUNT-3) * (mStoreBoxes[0].getHeight() + 5.0f));
	storeItemsLoc = storeItemsMin;

	scrollbar = new UIScrollbar(SCROLLBAR_VERT, 10.0f, 350.0f);
	scrollbar->setLocation(menuX + 150.0f, menuY);
	scrollbar->setColor(0.1f,0.1f,0.1f);
	scrollbar->setupHide(HT_HOROZONTAL, scrollbar->getX() + 200.0f, hideTime, true);
	scrollbar->setHidden();
	scrollbar->setValue(0.0f);
	scrollbar->setMax(storeItemsMin - storeItemsMax);
	scrollbar->setSliderSize(100.0f);
}

// Load screen
void StoreScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);
	
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	bBack->centerText(mUI->mTextRender);
	bBuy->centerText(mUI->mTextRender);

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].load(mAtlas);
	}

	show();
}

// Update the state of the screen
void StoreScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	lTitle->update(deltaTime);
	bDesc->update(deltaTime);
	bBack->update(deltaTime);
	bBuy->update(deltaTime);
	scrollbar->update(deltaTime);

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].update(deltaTime);
	}
}

// Update input to the screen 
void StoreScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	bBack->updateInput(mKeyH, mMouseH);
	bBuy->updateInput(mKeyH, mMouseH);

	if (bBack->wasClicked()){
		transitionCode = SCREEN_MAIN;
		hide();
	}

	// Update Store Item scroll bar
	scrollbar->updateInput(mKeyH, mMouseH);
	scrollbar->updateMouseScroll(mMouseH);
	storeItemsLoc = storeItemsMin - scrollbar->getValue();

	// Update store item input and location 
	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].setY(storeItemsLoc + (i * (mStoreBoxes[i].getHeight() + 5.0f)));
		mStoreBoxes[i].updateInput(mKeyH, mMouseH);
	}
}


// Draw the screen
void StoreScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);
	
	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Bind bufferes
	mAtlas->bindBuffers(mgl);
	mAtlas->bindTexture(mgl);

	lTitle->draw(mgl, (UIAtlas*)mAtlas);
	bDesc->draw(mgl, (UIAtlas*)mAtlas);
	bBack->draw(mgl, (UIAtlas*)mAtlas);
	bBuy->draw(mgl, (UIAtlas*)mAtlas);
	scrollbar->draw(mgl, (UIAtlas*)mAtlas);

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].draw(mgl, (UIAtlas*)mAtlas);
	}
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void StoreScreen::hide(){
	UIScreen::hide();

	lTitle->hide();
	bDesc->hide();
	bBack->hide();
	bBuy->hide();
	scrollbar->hide();

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].hide();
	}
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void StoreScreen::show(){
	UIScreen::show();

	lTitle->show();
	bDesc->show();
	bBack->show();
	bBuy->show();
	scrollbar->show();

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].show();
	}
}
