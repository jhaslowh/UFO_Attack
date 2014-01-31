#include "MainScreen.h"


MainScreen::MainScreen() : UIScreen(){}

MainScreen::~MainScreen(){
	delete buttonLevelSelect;
	delete buttonStore;
	delete buttonFreePlay;
	delete buttonSettings;
	delete buttonQuit;
	delete buttonText;
}

// Initialize screen
void MainScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	buttonLevelSelect = new UIButton(screen_width *.1f,screen_height *.4f,100.0f,35.0f, std::string("Levels"));
	buttonLevelSelect->setupHide(HT_HOROZONTAL,buttonLevelSelect->getX()-100.0f,.4f,true);
	buttonLevelSelect->setHidden();

	buttonFreePlay = new UIButton(screen_width *.1f,(screen_height *.4f) + 40.0f,100.0f,35.0f, std::string("Free Play"));
	buttonFreePlay->setupHide(HT_HOROZONTAL,buttonFreePlay->getX()-100.0f,.4f,true);
	buttonFreePlay->setHidden();

	buttonStore = new UIButton(screen_width *.1f,(screen_height *.4f) + 80.0f,100.0f,35.0f, std::string("Store"));
	buttonStore->setupHide(HT_HOROZONTAL,buttonStore->getX()-100.0f,.4f,true);
	buttonStore->setHidden();

	buttonSettings = new UIButton(screen_width *.1f,(screen_height *.4f) + 120.0f,100.0f,35.0f, std::string("Settings"));
	buttonSettings->setupHide(HT_HOROZONTAL,buttonSettings->getX()-100.0f,.4f,true);
	buttonSettings->setHidden();

	buttonQuit = new UIButton(screen_width *.1f,(screen_height *.4f) + 160.0f,100.0f,35.0f, std::string("Quit"));
	buttonQuit->setupHide(HT_HOROZONTAL,buttonQuit->getX()-100.0f,.4f,true);
	buttonQuit->setHidden();

	buttonText = new UIButton(screen_width *.1f,(screen_height *.4f) + 200.0f,100.0f,35.0f, std::string("Test"));
	buttonText->setupHide(HT_HOROZONTAL,buttonText->getX()-100.0f,.4f,true);
	buttonText->setHidden();
}

// Load screen
void MainScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonLevelSelect->centerText(mUI->mTextRender);
	buttonStore->centerText(mUI->mTextRender);
	buttonFreePlay->centerText(mUI->mTextRender);
	buttonSettings->centerText(mUI->mTextRender);
	buttonQuit->centerText(mUI->mTextRender);
	buttonText->centerText(mUI->mTextRender);
	
	show();
}

// Update the state of the screen
void MainScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	buttonLevelSelect->update(deltaTime);
	buttonStore->update(deltaTime);
	buttonFreePlay->update(deltaTime);
	buttonSettings->update(deltaTime);
	buttonQuit->update(deltaTime);
	buttonText->update(deltaTime);
}

// Update input to the screen 
void MainScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	buttonLevelSelect->updateInput(mKeyH, mMouseH);
	buttonStore->updateInput(mKeyH, mMouseH);
	buttonSettings->updateInput(mKeyH, mMouseH);
	buttonFreePlay->updateInput(mKeyH, mMouseH);
	buttonQuit->updateInput(mKeyH, mMouseH);
	buttonText->updateInput(mKeyH, mMouseH);

	if (buttonText->wasClicked())
		transitionCode = SCREEN_TEST;
	if (buttonQuit->wasClicked())
		transitionCode = SCREEN_QUIT;
	if (buttonSettings->wasClicked())
		transitionCode = SCREEN_SETTINGS;
	if (buttonFreePlay->wasClicked())
		transitionCode = SCREEN_FREE_PLAY;

	// TODO this should be level select, but will be 
	// this until level select is implemented.
	if (buttonLevelSelect->wasClicked())
		transitionCode = SCREEN_GAME; 
}

// Draw the screen
void MainScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);

	buttonLevelSelect->draw(mgl, mUI);
	buttonStore->draw(mgl, mUI);
	buttonFreePlay->draw(mgl, mUI);
	buttonSettings->draw(mgl, mUI);
	buttonQuit->draw(mgl, mUI);
	buttonText->draw(mgl, mUI);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void MainScreen::hide(){
	buttonLevelSelect->hide();
	buttonStore->hide();
	buttonFreePlay->hide();
	buttonSettings->hide();
	buttonQuit->hide();
	buttonText->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void MainScreen::show(){
	buttonLevelSelect->show();
	buttonStore->show();
	buttonSettings->show();
	buttonFreePlay->show();
	buttonQuit->show();
	buttonText->show();
}