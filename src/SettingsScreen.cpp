#include "SettingsScreen.h"


SettingsScreen::SettingsScreen(Settings* s) : UIScreen(){
	settings = s;
	hideOnClose = true;
}
SettingsScreen::~SettingsScreen()
{
	delete labelTitle;
	delete cFullscreen;
	delete buttonBack;
	delete vMasterVol;
	delete vMusicVol;
	delete vSfxVol;

	delete lFullscreen;
	delete lMasterVolume;
	delete lMusicVol;
	delete lSfxVol;

	delete bBG;
}

// Initialize screen
void SettingsScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	labelTitle = new UILabel(std::string("Settings"));
	labelTitle->setLocation(screen_width, screen_height);
	labelTitle->setColor(.9f,.9f,.9f);
	labelTitle->setTextSize(60.0f);

	float menuX = screen_width *.5f;
	float menuY = screen_height *.4f;

	lFullscreen = new UILabel(std::string("Fullscreen"));
	lFullscreen->setLocation(menuX - 120.0f,menuY + 5.0f);
	lFullscreen->setupHide(HT_HOROZONTAL,lFullscreen->getX()-100.0f,hideTime,true);
	lFullscreen->setColor(.9f,.9f,.9f);
	lFullscreen->setTextSize(16.0f);
	lFullscreen->setHidden();
	
	lMasterVolume = new UILabel(std::string("Master Volume"));
	lMasterVolume->setLocation(menuX - 120.0f,menuY + 35.0f);
	lMasterVolume->setupHide(HT_HOROZONTAL,lMasterVolume->getX()-100.0f,hideTime,true);
	lMasterVolume->setColor(.9f,.9f,.9f);
	lMasterVolume->setTextSize(16.0f);
	lMasterVolume->setHidden();

	lMusicVol = new UILabel(std::string("Music Volume"));
	lMusicVol->setLocation(menuX - 120.0f,menuY + 60.0f);
	lMusicVol->setupHide(HT_HOROZONTAL,lMusicVol->getX()-100.0f,hideTime,true);
	lMusicVol->setColor(.9f,.9f,.9f);
	lMusicVol->setTextSize(16.0f);
	lMusicVol->setHidden();

	lSfxVol = new UILabel(std::string("SFX Volume"));
	lSfxVol->setLocation(menuX - 120.0f,menuY + 95.0f);
	lSfxVol->setupHide(HT_HOROZONTAL,lSfxVol->getX()-100.0f,hideTime,true);
	lSfxVol->setColor(.9f,.9f,.9f);
	lSfxVol->setTextSize(16.0f);
	lSfxVol->setHidden();

	cFullscreen = new UICheckbox(menuX - 4.0f,menuY,24.0f,24.0f,std::string(""));
	cFullscreen->setTextColor(.8f,.8f,.8f);
	cFullscreen->setupHide(HT_HOROZONTAL,cFullscreen->getX()+100.0f,hideTime,true);
	cFullscreen->setHidden();

	vMasterVol = new UIValueSlider();
	vMasterVol->setLocation(menuX,menuY + 35.0f);
	vMasterVol->setupHide(HT_HOROZONTAL,vMasterVol->getX()+100.0f,hideTime,true);
	vMasterVol->setHidden();

	vMusicVol = new UIValueSlider();
	vMusicVol->setLocation(menuX,menuY + 60.0f);
	vMusicVol->setupHide(HT_HOROZONTAL,vMusicVol->getX()+100.0f,hideTime,true);
	vMusicVol->setHidden();

	vSfxVol = new UIValueSlider();
	vSfxVol->setLocation(menuX,menuY + 85.0f);
	vSfxVol->setupHide(HT_HOROZONTAL,vSfxVol->getX()+100.0f,hideTime,true);
	vSfxVol->setHidden();

	buttonBack = new UIButton(menuX- 50.0f,
		menuY + 125.0f,100.0f,35.0f, std::string("Back"));
	buttonBack->setupHide(HT_VERTICAL,buttonBack->getY()+100.0f,hideTime,true);
	buttonBack->setHidden();

	bBG = new UIBox(screen_width / 2.0f - 125.0f, menuY-5.0f,250.0f,120.0f);
	bBG->setupHide(HT_VERTICAL, bBG->getY() + 10.0f, hideTime, true);
	bBG->setHidden();
	bBG->setAlpha(.7f);

	// Load settings 
	cFullscreen->setChecked(settings->getFullscreen());
	vMasterVol->setValue(settings->getMasterVol());
	vMusicVol->setValue(settings->getMusicVol());
	vSfxVol->setValue(settings->getSfxVol());
}

// Load screen
void SettingsScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonBack->centerText(mUI->mTextRender);

	labelTitle->setLocation(
		(labelTitle->getX() * .5f) - (mUI->mTextRender->measureString(labelTitle->getText(), labelTitle->getTextSize()) * .5f),
		labelTitle->getY() * .4f - labelTitle->getTextSize() - 5.0f);
	labelTitle->setupHide(HT_VERTICAL,labelTitle->getY()-100.0f,hideTime,true);
	labelTitle->setHidden();
	
	show();
}

// Update the state of the screen
void SettingsScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	// Update ui objects 
	labelTitle->update(deltaTime);
	cFullscreen->update(deltaTime);
	buttonBack->update(deltaTime);
	vMasterVol->update(deltaTime);
	vMusicVol->update(deltaTime);
	vSfxVol->update(deltaTime);
	lFullscreen->update(deltaTime);
	lMasterVolume->update(deltaTime);
	lMusicVol->update(deltaTime);
	lSfxVol->update(deltaTime);
	bBG->update(deltaTime);
}

// Update input to the screen 
void SettingsScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	// Update fullscreen checkbox 
	cFullscreen->updateInput(mKeyH, mMouseH);
	settings->setFullscreen(cFullscreen->Checked());

	// Update volume value sliders 
	vMasterVol->updateInput(mKeyH, mMouseH);
	settings->setMasterVol(vMasterVol->getValue());
	vMusicVol->updateInput(mKeyH, mMouseH);
	settings->setMusicVol(vMusicVol->getValue());
	vSfxVol->updateInput(mKeyH, mMouseH);
	settings->setSfxVol(vSfxVol->getValue());
	
	// Update back button 
	buttonBack->updateInput(mKeyH, mMouseH);
	if (buttonBack->wasClicked()){
		transitionCode = SCREEN_MAIN;
		saveSettings(settings);
		hide();
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

	// Draw ui objects 
	bBG->draw(mgl, mUI);
	labelTitle->draw(mgl, mUI);
	cFullscreen->draw(mgl, mUI);
	buttonBack->draw(mgl, mUI);
	vMasterVol->draw(mgl, mUI);
	vMusicVol->draw(mgl, mUI);
	vSfxVol->draw(mgl, mUI);
	lFullscreen->draw(mgl, mUI);
	lMasterVolume->draw(mgl, mUI);
	lMusicVol->draw(mgl, mUI);
	lSfxVol->draw(mgl, mUI);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void SettingsScreen::hide(){
	UIScreen::hide();

	// Hide ui objects 
	labelTitle->hide();
	cFullscreen->hide();
	buttonBack->hide();
	vMasterVol->hide();
	vMusicVol->hide();
	vSfxVol->hide();
	lFullscreen->hide();
	lMasterVolume->hide();
	lMusicVol->hide();
	lSfxVol->hide();
	bBG->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void SettingsScreen::show(){
	UIScreen::show();

	// show ui objects 
	labelTitle->show();
	cFullscreen->show();
	buttonBack->show();
	vMasterVol->show();
	vMusicVol->show();
	vSfxVol->show();
	lFullscreen->show();
	lMasterVolume->show();
	lMusicVol->show();
	lSfxVol->show();
	bBG->show();
}