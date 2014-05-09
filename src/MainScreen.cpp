#include "MainScreen.h"

MainScreen::MainScreen(bool showResume) : UIScreen(){
	buttonResume = NULL;
	hideOnClose = true;
	this->showResume = showResume;
}

MainScreen::~MainScreen(){
	delete buttonLevelSelect;
	delete buttonStore;
	delete buttonEquip;
	delete buttonSettings;
	delete buttonQuit;
	delete buttonResume;
}

// Initialize screen
void MainScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	buttonLevelSelect = new UIButton(screen_width *.5f - 103.0f,screen_height *.5f,100.0f,35.0f, std::string("Levels"));
	buttonLevelSelect->setupHide(HT_VERTICAL,buttonLevelSelect->getY()+100.0f,hideTime,true);
	buttonLevelSelect->setHidden();

	buttonEquip = new UIButton(screen_width *.5f + 3.0f,screen_height *.5f,100.0f,35.0f, std::string("Equip"));
	buttonEquip->setupHide(HT_VERTICAL,buttonEquip->getY()+120.0f,hideTime,true);
	buttonEquip->setHidden();

	buttonStore = new UIButton(screen_width *.5f - 103.0f,(screen_height *.5f) + 40.0f,100.0f,35.0f, std::string("Store"));
	buttonStore->setupHide(HT_VERTICAL,buttonStore->getY()+160.0f,hideTime,true);
	buttonStore->setHidden();

	buttonSettings = new UIButton(screen_width *.5f + 3.0f,(screen_height *.5f) + 40.0f,100.0f,35.0f, std::string("Settings"));
	buttonSettings->setupHide(HT_VERTICAL,buttonSettings->getY()+190.0f,hideTime,true);
	buttonSettings->setHidden();

	if (showResume)
	{
		buttonResume = new UIButton(screen_width *.5f - 103.0f,(screen_height *.5f) + 80.0f,100.0f,35.0f, std::string("Resume"));
		buttonResume->setupHide(HT_VERTICAL,buttonResume->getY()+280.0f,hideTime,true);
		buttonResume->setHidden();

		buttonQuit = new UIButton(screen_width *.5f + 3.0f,(screen_height *.5f) + 80.0f,100.0f,35.0f, std::string("Quit"));
		buttonQuit->setupHide(HT_VERTICAL,buttonQuit->getY()+200.0f,hideTime,true);
		buttonQuit->setHidden();
	}
	else {
		buttonQuit = new UIButton(screen_width *.5f - 50.0f,(screen_height *.5f) + 80.0f,100.0f,35.0f, std::string("Quit"));
		buttonQuit->setupHide(HT_VERTICAL,buttonQuit->getY()+200.0f,hideTime,true);
		buttonQuit->setHidden();
	}

	// Scale main menu logo if screen is small 
	float lscale = 1.0f;
	if (screen_height < 600.0f)
		lscale = screen_height / 600.0f;

	logo.setPosition(screen_width * .5f, screen_height * .5f - 22.0f);
	logo.setOrigin(256.0f, 256.0f);
	logo.setAlpha(0.0f);
	logo.setScale(lscale);
	soundHandler = (SoundHandler*)sh;
}

// Load screen
void MainScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonLevelSelect->centerText(mUI->mTextRender);
	buttonStore->centerText(mUI->mTextRender);
	buttonEquip->centerText(mUI->mTextRender);
	buttonSettings->centerText(mUI->mTextRender);
	if (buttonResume != NULL) 
		buttonResume->centerText(mUI->mTextRender);
	buttonQuit->centerText(mUI->mTextRender);

	logo.setup(512.0f, 256.0f, "images/logo.png");
	
	show();
}

// Update the state of the screen
void MainScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	buttonLevelSelect->update(deltaTime);
	buttonStore->update(deltaTime);
	buttonEquip->update(deltaTime);
	buttonSettings->update(deltaTime);
	buttonQuit->update(deltaTime);
	if (buttonResume != NULL) 
		buttonResume->update(deltaTime);
	
	logo.setAlpha(buttonQuit->getOpacity());
}

// Update input to the screen 
void MainScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	buttonLevelSelect->updateInput(mKeyH, mMouseH);
	buttonStore->updateInput(mKeyH, mMouseH);
	buttonSettings->updateInput(mKeyH, mMouseH);
	buttonEquip->updateInput(mKeyH, mMouseH);
	buttonQuit->updateInput(mKeyH, mMouseH);
	if (buttonResume != NULL)
		buttonResume->updateInput(mKeyH, mMouseH);

	// Close game
	if (buttonQuit->wasClicked()){
		transitionCode = SCREEN_QUIT;
		hide();
	}
	// Go to settings screen
	if (buttonSettings->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_SETTINGS;
		hide();
	}
	// Go to free play screen
	if (buttonEquip->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_EQUIP;
		hide();
	}
	// Go to store 
	if (buttonStore->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_STORE;
		hide();
	}

	// Open Level Select Screen
	if (buttonLevelSelect->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_LEVEL_SELECT; 
		hide();
	}

	// Resume game if resume clicked 
	if (buttonResume != NULL && buttonResume->wasClicked()) {
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_GAME_RESUME;
		hide();
	}
}

// Draw the screen
void MainScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	logo.draw(*mgl);

	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);

	buttonLevelSelect->draw(mgl, mUI);
	buttonStore->draw(mgl, mUI);
	buttonEquip->draw(mgl, mUI);
	buttonSettings->draw(mgl, mUI);
	buttonQuit->draw(mgl, mUI);
	if (buttonResume != NULL)
		buttonResume->draw(mgl, mUI);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void MainScreen::hide(){
	UIScreen::hide();

	buttonLevelSelect->hide();
	buttonStore->hide();
	buttonEquip->hide();
	buttonSettings->hide();
	buttonQuit->hide();
	if (buttonResume != NULL)
		buttonResume->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void MainScreen::show(){
	UIScreen::show();

	buttonLevelSelect->show();
	buttonStore->show();
	buttonSettings->show();
	buttonEquip->show();
	buttonQuit->show();
	if (buttonResume != NULL)
		buttonResume->show();
}

