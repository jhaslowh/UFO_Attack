#include "CreditsScreen.h"

CreditsScreen::CreditsScreen() : UIScreen()
{
	bBack = NULL;
	creditsBoxes = NULL;
}

CreditsScreen::~CreditsScreen()
{
	delete bBack;
	delete[] creditsBoxes;
}

// Initialize screen
void CreditsScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	bBack = new UIButton(
		5.0f,
		screen_height - 40.0f,100.0f,35.0f, std::string("MainMenu"));
	bBack->setupHide(HT_HOROZONTAL,bBack->getX()-100.0f,hideTime,true);
	bBack->setHidden();

	creditsCount = 2;
	creditsBoxes = new UICreditsBox[creditsCount];
	creditsBoxes[0].setup("Created by", "Jonathan Haslow-Hall\nAndrew Geyster\nJames Dressel");
	creditsBoxes[0].setLocation(screen_width / 2.0f, screen_height);
	creditsBoxes[1].setup("Character Designs by", "Chris Dike\nLucy Niedbala");
	creditsBoxes[1].setLocation(screen_width / 2.0f, screen_height + 30.0f + creditsBoxes[0].getHeight());
}

// Load screen
void CreditsScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	bBack->centerText(mUI->mTextRender);

	show();
}

// Update the state of the screen
void CreditsScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	bBack->update(deltaTime);
}

// Update input to the screen 
void CreditsScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	bBack->updateInput(mKeyH, mMouseH);
	if (bBack->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_MAIN;
	}
}

// Draw the screen
void CreditsScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	bBack->draw(mgl, (UIAtlas*)mAtlas);

	for (int i = 0; i < creditsCount; i++)
		creditsBoxes[i].draw(mgl,(UIAtlas*)mAtlas,0.0f,-500.0f);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void CreditsScreen::hide(){
	UIScreen::hide();

	bBack->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void CreditsScreen::show(){
	UIScreen::show();

	bBack->show();
}
