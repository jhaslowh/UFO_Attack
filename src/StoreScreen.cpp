#include "StoreScreen.h"
using namespace StoreItems;

StoreScreen::StoreScreen(SaveData* sd) : UIScreen()
{
	savedata = sd;
	hideOnClose = true;
	lTitle = NULL;
	bDesc = NULL;
	bBack = NULL;
	bBuy = NULL;
	mStoreBoxes = NULL;
	scrollbar = NULL;
	lPlayerAnimalMoney = NULL;
	lPlayerHumanMoney = NULL;
	setupSprite = false;

	selectedItem = 0;
	lSelName = NULL;
	lSelDesc = NULL;
	lSelHumanPrice = NULL;
	lSelAnimalPrice = NULL;
}

StoreScreen::~StoreScreen()
{
	delete lTitle;
	delete bDesc;
	delete bBack;
	delete bBuy;
	delete[] mStoreBoxes;
	delete scrollbar;
	delete lSelName;
	delete lSelDesc;
	delete lSelHumanPrice;
	delete lSelAnimalPrice;
	delete lPlayerAnimalMoney;
	delete lPlayerHumanMoney;
}

// Initialize screen
void StoreScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	// Menu location to easily move menu
	float menuX = screen_width * .55f;
	float menuY = screen_height * .3f;

	lTitle = new UILabel("Store");
	lTitle->setTextSize(60.0f);
	lTitle->setLocation(
		menuX - 300.0f,
		menuY - lTitle->getTextSize() - 25.0f);
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
	bBuy->setupHide(HT_VERTICAL, bBuy->getY() + 100.0f, hideTime /2.0f, true);
	bBuy->setHidden();

	// Set player currency stuff
	lPlayerAnimalMoney = new UILabel(toString(savedata->getAnimalAbductCount()));
	lPlayerAnimalMoney->setTextSize(17.0f);
	lPlayerAnimalMoney->setLocation(menuX - 270.0f, menuY - 20.0f);
	lPlayerAnimalMoney->setupHide(HT_HOROZONTAL, lPlayerAnimalMoney->getX() - 100.0f, hideTime, true);
	lPlayerAnimalMoney->setColor(.9f,.9f,.9f);
	lPlayerAnimalMoney->setHidden(); 

	lPlayerHumanMoney = new UILabel(toString(savedata->getHumanAbductCount()));
	lPlayerHumanMoney->setTextSize(17.0f);
	lPlayerHumanMoney->setLocation(menuX - 200.0f, menuY - 20.0f);
	lPlayerHumanMoney->setupHide(HT_HOROZONTAL, lPlayerHumanMoney->getX() - 100.0f, hideTime, true);
	lPlayerHumanMoney->setColor(.9f,.9f,.9f);
	lPlayerHumanMoney->setHidden(); 

	mCSAnimalPlayer.setID(UII_CURRENCY_ANIMAL);
	mCSAnimalPlayer.setPosition(-22.0f, -4.0f);
	mCSHumanPlayer.setID(UII_CURRENCY_HUMAN);
	mCSHumanPlayer.setPosition(-22.0f, -4.0f);

	// Set store items

	mStoreBoxes = new UIStoreItemBox[STORE_ITEM_COUNT];
	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].init(screen_width, screen_height);
		mStoreBoxes[i].setLocation(menuX + 5.0f, menuY + (i * (mStoreBoxes[i].getHeight() + 5.0f)));
		mStoreBoxes[i].setupHide(HT_HOROZONTAL, mStoreBoxes[i].getX() + (rand() % 300 + 100), hideTime, true);
		mStoreBoxes[i].setHidden();
		mStoreBoxes[i].setItem(i);

		if (savedata->isItemPurchased(i))
			mStoreBoxes[i].setPurchased(true);
	}

	// Set sprite properties 
	siImage.setPosition(5.0f,32.0f);

	// Set locations
	storeItemHeight = (mStoreBoxes[0].getHeight() + 5.0f);
	storeItemsTop = menuY;
	storeItemsBottom = menuY + (float)(4.5 * storeItemHeight);
	storeItemsMin = menuY - ((STORE_ITEM_COUNT-5) * storeItemHeight);
	storeItemsLoc = storeItemsTop;

	scrollbar = new UIScrollbar(SCROLLBAR_VERT, 10.0f, storeItemHeight * 5.0f);
	scrollbar->setLocation(menuX + 150.0f, menuY);
	scrollbar->setColor(0.1f,0.1f,0.1f);
	scrollbar->setupHide(HT_HOROZONTAL, scrollbar->getX() + 200.0f, hideTime, true);
	scrollbar->setHidden();
	scrollbar->setValue(0.0f);
	scrollbar->setMax(storeItemsTop - storeItemsMin);
	scrollbar->setSliderSize((5.0f / STORE_ITEM_COUNT) * (storeItemHeight * 5.0f));

	// Set selected item elements 
	// Selected item names 
	lSelName = new UILabel("sel name");
	lSelName->setTextSize(25.0f);
	lSelName->setLocation(menuX - 294.0f, menuY + 6.0f);
	lSelName->setupHide(HT_VERTICAL, lSelName->getY() + 100.0f, hideTime, true);
	lSelName->setColor(.9f,.9f,.9f);
	lSelName->setHidden(); 

	// Selected item description 
	lSelDesc = new UILabel("sel desc");
	lSelDesc->setTextSize(20.0f);
	lSelDesc->setLocation(menuX - 294.0f, menuY + 134.0f);
	lSelDesc->setupHide(HT_VERTICAL, lSelDesc->getY() + 100.0f, hideTime, true);
	lSelDesc->setColor(.9f,.9f,.9f);
	lSelDesc->setHidden(); 

	// Set description prices 
	lSelAnimalPrice = new UILabel("1");
	lSelAnimalPrice->setTextSize(17.0f);
	lSelAnimalPrice->setLocation(menuX - 270.0f, menuY + 280.0f);
	lSelAnimalPrice->setupHide(HT_VERTICAL, lSelAnimalPrice->getY() + 100.0f, hideTime, true);
	lSelAnimalPrice->setColor(.9f,.9f,.9f);
	lSelAnimalPrice->setHidden(); 

	lSelHumanPrice = new UILabel("00");
	lSelHumanPrice->setTextSize(17.0f);
	lSelHumanPrice->setLocation(menuX - 200.0f,menuY + 280.0f);
	lSelHumanPrice->setupHide(HT_VERTICAL, lSelHumanPrice->getY() + 100.0f, hideTime, true);
	lSelHumanPrice->setColor(.9f,.9f,.9f);
	lSelHumanPrice->setHidden(); 

	lPurchsed = new UILabel("Purchased");
	lPurchsed->setTextSize(17.0f);
	lPurchsed->setLocation(menuX - 292.0f, menuY + 280.0f);
	lPurchsed->setupHide(HT_VERTICAL, lPurchsed->getY() + 100.0f, hideTime, true);
	lPurchsed->setColor(.45f,.95f,.23f);
	lPurchsed->setHidden(); 

	// Set description currency 
	mCSAnimalSelect.setID(UII_CURRENCY_ANIMAL);
	mCSHumanSelect.setID(UII_CURRENCY_HUMAN);
	mCSAnimalSelect.setPosition(-22.0f, -4.0f);
	mCSHumanSelect.setPosition(-22.0f, -4.0f);
	
	setSelectedItem(0);
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

	// Load first store item image 
	siImage.setup(290, 100, (StoreItems::sItems.at(0)).getImage());
	
	show();
}


// Unload screen textures
// THIS MUST BE CALLED IF YOU LOAD STUFF.
void StoreScreen::unload(){
	UIScreen::unload();

	siImage.unload();
}

// Update the state of the screen
void StoreScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	lTitle->update(deltaTime);
	bDesc->update(deltaTime);
	bBack->update(deltaTime);
	bBuy->update(deltaTime);
	scrollbar->update(deltaTime);
	lSelName->update(deltaTime);
	lSelDesc->update(deltaTime);
	lSelHumanPrice->update(deltaTime);
	lSelAnimalPrice->update(deltaTime);
	lPlayerAnimalMoney->update(deltaTime);
	lPlayerHumanMoney->update(deltaTime);
	lPurchsed->update(deltaTime);

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].update(deltaTime);

		// Fade store boxes 
		if (mStoreBoxes[i].getY() < storeItemsTop)
			mStoreBoxes[i].setAlpha(1 - ((storeItemsTop - mStoreBoxes[i].getY())/storeItemHeight));
		else if (mStoreBoxes[i].getY() > storeItemsBottom)
			mStoreBoxes[i].setAlpha(1 - ((mStoreBoxes[i].getY() - storeItemsBottom)/storeItemHeight));
		else 
			mStoreBoxes[i].setAlpha(1.0f);
	}
}

// Update input to the screen 
void StoreScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	bBack->updateInput(mKeyH, mMouseH);
	bBuy->updateInput(mKeyH, mMouseH);

	if (bBack->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_MAIN;
		hide();
	}

	// Update Store Item scroll bar
	scrollbar->updateInput(mKeyH, mMouseH);
	scrollbar->updateMouseScroll(mMouseH);
	storeItemsLoc = storeItemsTop - scrollbar->getValue();

	// Update store item input and location 
	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].setY(storeItemsLoc + (i * (mStoreBoxes[i].getHeight() + 5.0f)));
		mStoreBoxes[i].updateInput(mKeyH, mMouseH);

		// Check for click 
		if (mStoreBoxes[i].wasClicked()){
			soundHandler->playSoundEffect(SE_BUTTON_PRESS);
			setSelectedItem(mStoreBoxes[i].getIndex());
		}
	}

	// Check if buy clicked 
	if (bBuy->wasClicked() && !savedata->isItemPurchased(selectedItem) &&
			savedata->getAnimalAbductCount() >= (StoreItems::sItems.at(selectedItem)).getAnimalPrice() &&
			savedata->getHumanAbductCount() >= (StoreItems::sItems.at(selectedItem)).getHumanPrice()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		// Increment player currency 
		savedata->incrAnimalCount((StoreItems::sItems.at(selectedItem)).getAnimalPrice() * -1);
		savedata->incrHumanCount((StoreItems::sItems.at(selectedItem)).getHumanPrice() * -1);
		// Set item as purchased 
		savedata->itemPurchsed(selectedItem);
		// Tell store box that it was purchased
		mStoreBoxes[selectedItem].setPurchased(true);
		// Update description items 
		setSelectedItem(selectedItem);

		// Update display currency 
		lPlayerAnimalMoney->setText(toString(savedata->getAnimalAbductCount()));
		lPlayerHumanMoney->setText(toString(savedata->getHumanAbductCount()));
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
	lSelName->draw(mgl, (UIAtlas*)mAtlas);
	lSelDesc->draw(mgl, (UIAtlas*)mAtlas);
	lPlayerAnimalMoney->draw(mgl, (UIAtlas*)mAtlas);
	lPlayerHumanMoney->draw(mgl, (UIAtlas*)mAtlas);

	if (savedata->isItemPurchased(selectedItem))
		lPurchsed->draw(mgl, (UIAtlas*)mAtlas);
	else {
		lSelHumanPrice->draw(mgl, (UIAtlas*)mAtlas);
		lSelAnimalPrice->draw(mgl, (UIAtlas*)mAtlas);
		mgl->setFlatColor(COLOR_WHITE, lSelHumanPrice->getOpacity());
		mCSAnimalSelect.draw(mgl, (UIAtlas*)mAtlas,lSelHumanPrice->getX(), lSelHumanPrice->getY());
		mCSHumanSelect.draw(mgl, (UIAtlas*)mAtlas,lSelAnimalPrice->getX(), lSelAnimalPrice->getY());
	}

	mgl->setFlatColor(COLOR_WHITE, lPlayerAnimalMoney->getOpacity());
	mCSAnimalPlayer.draw(mgl, (UIAtlas*)mAtlas, lPlayerAnimalMoney->getX(), lPlayerAnimalMoney->getY());
	mCSHumanPlayer.draw(mgl, (UIAtlas*)mAtlas, lPlayerHumanMoney->getX(), lPlayerHumanMoney->getY());

	mgl->setFlatColor(COLOR_WHITE, lTitle->getOpacity());
	mCSAnimalPlayer.draw(mgl, mAtlas);
	mCSHumanPlayer.draw(mgl, mAtlas);

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].draw(mgl, (UIAtlas*)mAtlas);
	}

	if (setupSprite) 
		siImage.setup(290, 100, (StoreItems::sItems.at(selectedItem)).getImage());

	siImage.setAlpha(bDesc->getOpacity());
	siImage.draw(*mgl, bDesc->getX(), bDesc->getY());
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
	lSelName->hide();
	lSelDesc->hide();
	lSelHumanPrice->hide();
	lSelAnimalPrice->hide();
	lPlayerAnimalMoney->hide();
	lPlayerHumanMoney->hide();
	lPurchsed->hide();

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
	if (!savedata->isItemPurchased(selectedItem)) bBuy->show();
	scrollbar->show();
	lSelName->show();
	lSelDesc->show();
	lSelHumanPrice->show();
	lSelAnimalPrice->show();
	lPlayerAnimalMoney->show();
	lPlayerHumanMoney->show();
	lPurchsed->show();

	for (int i = 0; i < STORE_ITEM_COUNT; i++){
		mStoreBoxes[i].show();
	}
}


// Set the selected item for the store 
void StoreScreen::setSelectedItem(int i){
	selectedItem = i;
	setupSprite = true;

	StoreItem* si = &(StoreItems::sItems.at(i));

	lSelName->setText(si->getName());
	lSelDesc->setText(si->getDesc());
	lSelHumanPrice->setText(toString(si->getHumanPrice()));
	lSelAnimalPrice->setText(toString(si->getAnimalPrice()));

	// Hide and show button based on purchase state 
	if (savedata->isItemPurchased(selectedItem))
		bBuy->hide();
	else 
		bBuy->show();
}
