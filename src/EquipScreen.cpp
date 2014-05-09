#include "EquipScreen.h"

using namespace StoreItems;

EquipScreen::EquipScreen(SaveData* data) : UIScreen()
{
	saveData = data;
	lTitle = NULL;
	bBack = NULL;
	scrollbar = NULL;
	ebPlayer1 = NULL;
	ebPlayer2 = NULL;
	ebUFO1 = NULL;
	ebUFO2 = NULL;
	player1 = NULL;
	player2 = NULL;
	ufo1 = NULL;
	ufo2 = NULL;
	hideOnClose = true;
	selectedType = PLAYER_WEAPON_1;
	weaponList = NULL;
	itemsToShow = 1;
	weaponListCount = 0;
}

EquipScreen::~EquipScreen()
{
	delete lTitle;
	delete bBack;
	delete scrollbar; 
	delete ebPlayer1;
	delete ebPlayer2;
	delete ebUFO1;
	delete ebUFO2;
	delete player1;
	delete player2;
	delete ufo1;
	delete ufo2;
	delete[] weaponList;
}

// Initialize screen
void EquipScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	// Menu location to easily move menu
	float menuX = screen_width * .5f;
	float menuY = screen_height * .5f;
	float spacing = 10.0f;

	// Create main title for the screen 
	lTitle = new UILabel("Equipment");
	lTitle->setTextSize(50.0f);
	lTitle->setLocation(
		menuX - 300.0f,
		menuY - lTitle->getTextSize() - 120.0f);
	lTitle->setupHide(HT_HOROZONTAL, lTitle->getX() - 200.0f, hideTime, true);
	lTitle->setColor(COLOR_UI_LABEL[0],COLOR_UI_LABEL[1],COLOR_UI_LABEL[2]);
	lTitle->setHidden();

	// Setup dividers
	topDivider.reset(menuX - 320.0f, menuY - 120.0f, 410.0f, 1.0f);
	sideDivider.reset(menuX + 100.0f, menuY - 90.0f, 1.0f, 200.0f);

	// Setup scrollbar
	scrollbar = new UIScrollbar(SCROLLBAR_VERT, 10.0f, 200.0f);
	scrollbar->setLocation(menuX + 320.0f, menuY - 90.0f);
	scrollbar->setColor(0.1f,0.1f,0.1f);
	scrollbar->setupHide(HT_HOROZONTAL, scrollbar->getX() + 200.0f, hideTime, true);
	scrollbar->setHidden();
	scrollbar->setValue(0.0f);
	scrollbar->setMax(100.0f);
	scrollbar->setSliderSize(70.0f);

	// -----------------------------
	// Setup selected equipment 
	// -----------------------------
	// Player Weapon 1
	ebPlayer1 = new UIEquipBox();
	ebPlayer1->init(screen_width, screen_height);
	ebPlayer1->setLocation(
		menuX - ((ebPlayer1->getWidth() * 1.5f) + (spacing * 2.0f)), 
		menuY - (ebPlayer1->getHeight()));
	ebPlayer1->setupHide(HT_VERTICAL, ebPlayer1->getY() + 100.0f, hideTime, true);
	ebPlayer1->setHidden();
	ebPlayer1->setItem(saveData->getPlayerWeapon1());
	player1 = new UILabel("Player Weapon 1");
	player1->setTextSize(14.0f);
	player1->setLocation(ebPlayer1->getX(), menuY - (ebPlayer1->getHeight()) - 15.0f);
	player1->setupHide(HT_VERTICAL, player1->getY() + 100.0f, hideTime, true);
	player1->setColor(COLOR_UI_LABEL[0],COLOR_UI_LABEL[1],COLOR_UI_LABEL[2]);
	player1->setHidden();

	// Player Weapon 2
	ebPlayer2 = new UIEquipBox();
	ebPlayer2->init(screen_width, screen_height);
	ebPlayer2->setLocation(
		menuX - ((ebPlayer2->getWidth() * .5f) + spacing), 
		menuY - (ebPlayer2->getHeight()));
	ebPlayer2->setupHide(HT_VERTICAL, ebPlayer2->getY() + 100.0f, hideTime, true);
	ebPlayer2->setHidden();
	ebPlayer2->setItem(saveData->getPlayerWeapon2());
	player2 = new UILabel("Player Weapon 2");
	player2->setTextSize(14.0f);
	player2->setLocation(ebPlayer2->getX(), menuY - (ebPlayer2->getHeight()) - 15.0f);
	player2->setupHide(HT_VERTICAL, player2->getY() + 100.0f, hideTime, true);
	player2->setColor(COLOR_UI_LABEL[0],COLOR_UI_LABEL[1],COLOR_UI_LABEL[2]);
	player2->setHidden();

	// UFO Weapon 1
	ebUFO1 = new UIEquipBox();
	ebUFO1->init(screen_width, screen_height);
	ebUFO1->setLocation(
		menuX - ((ebUFO1->getWidth() * 1.5f) + (spacing * 2.0f)), 
		menuY + (spacing*2.0f));
	ebUFO1->setupHide(HT_VERTICAL, ebUFO1->getY() + 100.0f, hideTime, true);
	ebUFO1->setHidden();
	ebUFO1->setItem(saveData->getUFOWeapon1());
	ufo1 = new UILabel("UFO Weapon 1");
	ufo1->setTextSize(14.0f);
	ufo1->setLocation(ebUFO1->getX(), menuY + 5.0f);
	ufo1->setupHide(HT_VERTICAL, ufo1->getY() + 100.0f, hideTime, true);
	ufo1->setColor(COLOR_UI_LABEL[0],COLOR_UI_LABEL[1],COLOR_UI_LABEL[2]);
	ufo1->setHidden();

	// UFO Weapon 2
	ebUFO2 = new UIEquipBox();
	ebUFO2->init(screen_width, screen_height);
	ebUFO2->setLocation(
		menuX - ((ebUFO2->getWidth() * .5f) + spacing), 
		menuY + (spacing*2.0f));
	ebUFO2->setupHide(HT_VERTICAL, ebUFO2->getY() + 100.0f, hideTime, true);
	ebUFO2->setHidden();
	ebUFO2->setItem(saveData->getUFOWeapon2());
	ufo2 = new UILabel("UFO Weapon 2");
	ufo2->setTextSize(14.0f);
	ufo2->setLocation(ebUFO2->getX(), menuY + 5.0f);
	ufo2->setupHide(HT_VERTICAL, ufo2->getY() + 100.0f, hideTime, true);
	ufo2->setColor(COLOR_UI_LABEL[0],COLOR_UI_LABEL[1],COLOR_UI_LABEL[2]);
	ufo2->setHidden();

	// -----------------------------
	// Setup selection
	// -----------------------------

	selectionRec.setSize(206.0f, 96.0f);
	weaponListLocX = menuX + 110.0f;
	weaponListLocY = menuY - (ebPlayer1->getHeight());

	// -----------------------------
	// Setup back button 
	bBack = new UIButton(
		menuX - (150.0f + (spacing*1.5f)), menuY + (ebPlayer1->getHeight() + (spacing * 3.0f)), 
		100.0f, 35.0f,"Back");
	bBack->setupHide(HT_VERTICAL, bBack->getY() + 100.0f, hideTime, true);
	bBack->setHidden();

	// Fix the display 
	fixWeaponList();
}

// Load screen
void EquipScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);
	
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	bBack->centerText(mUI->mTextRender);

	ebPlayer1->load(mAtlas);
	ebPlayer2->load(mAtlas);
	ebUFO1->load(mAtlas);
	ebUFO2->load(mAtlas);

	show();
}

// Update the state of the screen
void EquipScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	lTitle->update(deltaTime);
	bBack->update(deltaTime);
	ebPlayer1->update(deltaTime);
	ebPlayer2->update(deltaTime);
	player1->update(deltaTime);
	player2->update(deltaTime);
	ebUFO1->update(deltaTime);
	ebUFO2->update(deltaTime);
	ufo1->update(deltaTime);
	ufo2->update(deltaTime);
	scrollbar->update(deltaTime);

	// Update weapon list
	if (weaponList != NULL){
		for (int i = 0; i < weaponListCount; i++){
			//weaponList[i].setAlpha(bBack->getOpacity());
			weaponList[i].update(deltaTime);
		}
	}

	// Fix selection 
	if (selectedType == PLAYER_WEAPON_1){
		selectionRec.setLocation(ebPlayer1->getX() - 3.0f, ebPlayer1->getY() - 3.0f);
	}
	else if (selectedType == PLAYER_WEAPON_2){
		selectionRec.setLocation(ebPlayer2->getX() - 3.0f, ebPlayer2->getY() - 3.0f);
	}
	else if (selectedType == UFO_WEAPON_1){
		selectionRec.setLocation(ebUFO1->getX() - 3.0f, ebUFO1->getY() - 3.0f);
	}
	else if (selectedType == UFO_WEAPON_2){
		selectionRec.setLocation(ebUFO2->getX() - 3.0f, ebUFO2->getY() - 3.0f);
	}
}

// Update input to the screen 
void EquipScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	bBack->updateInput(mKeyH, mMouseH);
	ebPlayer1->updateInput(mKeyH, mMouseH);
	ebPlayer2->updateInput(mKeyH, mMouseH);
	ebUFO1->updateInput(mKeyH, mMouseH);
	ebUFO2->updateInput(mKeyH, mMouseH);

	// Check for weapon box clicks 
	if (ebPlayer1->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		selectedType = PLAYER_WEAPON_1;
		fixWeaponList();
	}
	if (ebPlayer2->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		selectedType = PLAYER_WEAPON_2;
		fixWeaponList();
	}
	if (ebUFO1->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		selectedType = UFO_WEAPON_1;
		fixWeaponList();
	}
	if (ebUFO2->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		selectedType = UFO_WEAPON_2;
		fixWeaponList();
	}
	
	
	float value = weaponListLocY;
	if (weaponListCount > itemsToShow){
		// Update Store Item scroll bar
		scrollbar->updateInput(mKeyH, mMouseH);
		scrollbar->updateMouseScroll(mMouseH);

		value -= scrollbar->getValue();
	}

	// Update weapon list input 
	if (weaponList != NULL){
		for (int i = 0; i < weaponListCount; i++){
			weaponList[i].setY(value + (i * (weaponList[i].getHeight() + 5.0f)));
			weaponList[i].updateInput(mKeyH, mMouseH);

			// Check input 
			if (weaponList[i].wasClicked()){
				if (selectedType == PLAYER_WEAPON_1){
					soundHandler->playSoundEffect(SE_BUTTON_PRESS);
					ebPlayer1->setItem(weaponList[i].getItem());
					saveData->setPlayerWeapon1(weaponList[i].getItem());
				}
				else if (selectedType == PLAYER_WEAPON_2){
					soundHandler->playSoundEffect(SE_BUTTON_PRESS);
					ebPlayer2->setItem(weaponList[i].getItem());
					saveData->setPlayerWeapon2(weaponList[i].getItem());
				}
				else if (selectedType == UFO_WEAPON_1){
					soundHandler->playSoundEffect(SE_BUTTON_PRESS);
					ebUFO1->setItem(weaponList[i].getItem());
					saveData->setUFOWeapon1(weaponList[i].getItem());
				}
				else if (selectedType == UFO_WEAPON_2){
					soundHandler->playSoundEffect(SE_BUTTON_PRESS);
					ebUFO2->setItem(weaponList[i].getItem());
					saveData->setUFOWeapon2(weaponList[i].getItem());
				}

				fixWeaponList();
			}
		}
	}

	// Quit to main menu if back was clicked 
	if (bBack->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		saveSaveData(saveData);
		transitionCode = SCREEN_MAIN;
		hide();
	}
}

// Draw the screen
void EquipScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);
	
	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Bind bufferes
	mAtlas->bindBuffers(mgl);
	mAtlas->bindTexture(mgl);

	// Draw selection rec
	if (ebPlayer1->shown()){
		mgl->setFlatColor(COLOR_UI_BLUE);
		mAtlas->drawScale2(mgl, UII_REC, selectionRec.getX(), selectionRec.getY(), 
			selectionRec.getWidth(), selectionRec.getHeight());
	}

	// Update weapon list input 
	if (weaponList != NULL)
		for (int i = 0; i < weaponListCount; i++)
			weaponList[i].draw(mgl, (UIAtlas*)mAtlas);

	// Draw ui objects
	lTitle->draw(mgl, (UIAtlas*)mAtlas);
	bBack->draw(mgl, (UIAtlas*)mAtlas);
	if (weaponListCount > itemsToShow)
		scrollbar->draw(mgl, (UIAtlas*)mAtlas);
	ebPlayer1->draw(mgl, (UIAtlas*)mAtlas);
	ebPlayer2->draw(mgl, (UIAtlas*)mAtlas);
	player1->draw(mgl, (UIAtlas*)mAtlas);
	player2->draw(mgl, (UIAtlas*)mAtlas);
	ebUFO1->draw(mgl, (UIAtlas*)mAtlas);
	ebUFO2->draw(mgl, (UIAtlas*)mAtlas);
	ufo1->draw(mgl, (UIAtlas*)mAtlas);
	ufo2->draw(mgl, (UIAtlas*)mAtlas);

	// Draw dividers
	mgl->setFlatColor(COLOR_UI_BLUE, lTitle->getOpacity());
	mAtlas->drawScale2(mgl, UII_REC, topDivider.getX(), topDivider.getY(), topDivider.getWidth(), topDivider.getHeight());
	mAtlas->drawScale2(mgl, UII_REC, sideDivider.getX(), sideDivider.getY(), sideDivider.getWidth(), sideDivider.getHeight());

	// Draw sprites 
	ebPlayer1->drawSprite(mgl);
	ebPlayer2->drawSprite(mgl);
	ebUFO1->drawSprite(mgl);
	ebUFO2->drawSprite(mgl);
	
	// Update weapon list input 
	if (weaponList != NULL)
		for (int i = 0; i < weaponListCount; i++)
			weaponList[i].drawSprite(mgl);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void EquipScreen::hide(){
	UIScreen::hide();

	lTitle->hide();
	bBack->hide();
	ebPlayer1->hide();
	ebPlayer2->hide();
	player1->hide();
	player2->hide();
	ebUFO1->hide();
	ebUFO2->hide();
	ufo1->hide();
	ufo2->hide();
	scrollbar->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void EquipScreen::show(){
	UIScreen::show();

	lTitle->show();
	bBack->show();
	ebPlayer1->show();
	ebPlayer2->show();
	player1->show();
	player2->show();
	ebUFO1->show();
	ebUFO2->show();
	ufo1->show();
	ufo2->show();
	scrollbar->show();
}

// Call to fix the list of weapons 
void EquipScreen::fixWeaponList(){
	// Index list for weapons 
	int* indexes = NULL;

	if (selectedType == PLAYER_WEAPON_1 || selectedType == PLAYER_WEAPON_2){
		// Get weapon list count 
		weaponListCount = 0;
		for (int i = 0; i < STORE_PLAYER_WEAPON_COUNT; i++){
			if (saveData->isItemPurchased(STORE_PLAYER_WEAPON_INDEXES[i]) &&
				STORE_PLAYER_WEAPON_INDEXES[i] != ebPlayer1->getItem() &&
				STORE_PLAYER_WEAPON_INDEXES[i] != ebPlayer2->getItem()){
				weaponListCount++;
			}
		}

		// Create index list 
		indexes = new int[weaponListCount];
		int current = 0;
		for (int i = 0; i < STORE_PLAYER_WEAPON_COUNT; i++){
			if (saveData->isItemPurchased(STORE_PLAYER_WEAPON_INDEXES[i]) &&
				STORE_PLAYER_WEAPON_INDEXES[i] != ebPlayer1->getItem() &&
				STORE_PLAYER_WEAPON_INDEXES[i] != ebPlayer2->getItem()){
				indexes[current] = STORE_PLAYER_WEAPON_INDEXES[i];
				current++;
			}
		}
	}
	else if (selectedType == UFO_WEAPON_1 || selectedType == UFO_WEAPON_2){
		// Get weapon list count 
		weaponListCount = 0;
		for (int i = 0; i < STORE_UFO_WEAPON_COUNT; i++){
			if (saveData->isItemPurchased(STORE_UFO_WEAPON_INDEXES[i]) &&
				STORE_UFO_WEAPON_INDEXES[i] != ebUFO1->getItem() &&
				STORE_UFO_WEAPON_INDEXES[i] != ebUFO2->getItem()){
				weaponListCount++;
			}
		}

		// Create index list 
		indexes = new int[weaponListCount];
		int current = 0;
		for (int i = 0; i < STORE_UFO_WEAPON_COUNT; i++){
			if (saveData->isItemPurchased(STORE_UFO_WEAPON_INDEXES[i]) &&
				STORE_UFO_WEAPON_INDEXES[i] != ebUFO1->getItem() &&
				STORE_UFO_WEAPON_INDEXES[i] != ebUFO2->getItem()){
				indexes[current] = STORE_UFO_WEAPON_INDEXES[i];
				current++;
			}
		}
	}

	// Create weapon list 
	delete[] weaponList;
	weaponList = NULL;

	if (weaponListCount > 0){
		weaponList = new UIEquipBox[weaponListCount];
		for (int i = 0; i < weaponListCount; i++){
			weaponList[i].init(0.0f, 0.0f);
			weaponList[i].setLocation(weaponListLocX, 
				weaponListLocY + (i * 95.0f));
			weaponList[i].setItem(indexes[i]);
			//weaponList[i].setAlpha(0.0f);
		}

		// Fix scrollbar 
		scrollbar->setMax((weaponListCount - itemsToShow) * 95.0f);
		scrollbar->setSliderSize(((itemsToShow * 95.0f) / (weaponListCount * 95.0f)) * scrollbar->getHeight());
		scrollbar->setValue(0.0f);
	}

	// Delete index list 
	delete[] indexes;
}

