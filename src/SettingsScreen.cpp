#include "SettingsScreen.h"


SettingsScreen::SettingsScreen(Settings* s) : UIScreen(){
	settings = s;
}
SettingsScreen::~SettingsScreen()
{
	delete(labelTitle);
	delete(checkboxFullscreen);
	delete(buttonBack);
}

// Initialize screen
void SettingsScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	labelTitle = new UILabel(std::string("Settings"));
	labelTitle->setLocation(20.0f,20.0f);
	labelTitle->setColor(.9f,.9f,.9f);
	labelTitle->setTextSize(60.0f);
	labelTitle->setupHide(HT_HOROZONTAL,labelTitle->getX()-100.0f,.4f,true);
	labelTitle->setHidden();

	checkboxFullscreen = new UICheckbox(screen_width *.05f,screen_height *.2f,24.0f,24.0f, std::string("Fullscreen"));
	checkboxFullscreen->setTextColor(.8f,.8f,.8f);
	checkboxFullscreen->setupHide(HT_HOROZONTAL,checkboxFullscreen->getX()-100.0f,.4f,true);
	checkboxFullscreen->setHidden();

	buttonBack = new UIButton(10.0f,screen_height -45.0f,100.0f,35.0f, std::string("Back"));
	buttonBack->setupHide(HT_HOROZONTAL,buttonBack->getX()-100.0f,.4f,true);
	buttonBack->setHidden();
}

// Load screen
void SettingsScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonBack->centerText(mUI->mTextRender);
	
	show();
}

// Update the state of the screen
void SettingsScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	labelTitle->update(deltaTime);
	checkboxFullscreen->update(deltaTime);
	buttonBack->update(deltaTime);
}

// Update input to the screen 
void SettingsScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	checkboxFullscreen->updateInput(mKeyH, mMouseH);
	buttonBack->updateInput(mKeyH, mMouseH);

	settings->setFullscreen(checkboxFullscreen->Checked());

	if (buttonBack->wasClicked()){
		transitionCode = SCREEN_MAIN;
		saveSettings(settings);
	}
}

// Draw the screen
void SettingsScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);

	labelTitle->draw(mgl, mUI);
	checkboxFullscreen->draw(mgl, mUI);
	buttonBack->draw(mgl, mUI);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void SettingsScreen::hide(){
	labelTitle->hide();
	checkboxFullscreen->hide();
	buttonBack->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void SettingsScreen::show(){
	labelTitle->show();
	checkboxFullscreen->show();
	buttonBack->show();
}