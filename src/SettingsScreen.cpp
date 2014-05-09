#include "SettingsScreen.h"


SettingsScreen::SettingsScreen(Settings* s, SaveData* sd) : UIScreen(){
	cbResolutions = NULL;
	buttonApply = NULL;
	cTutorial = NULL;
	lTutorial = NULL;

	settings = s;
	savedata = sd;
	hideOnClose = true;
}
SettingsScreen::~SettingsScreen()
{
	delete labelTitle;
	delete cFullscreen;
	delete cTutorial;
	delete buttonBack;
	delete buttonApply;
	delete vMasterVol;
	delete vMusicVol;
	delete vSfxVol;
	delete cbResolutions;

	delete lFullscreen;
	delete lTutorial;
	delete lMasterVolume;
	delete lMusicVol;
	delete lSfxVol;

	delete bBG;
}

// Initialize screen
void SettingsScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	labelTitle = new UILabel(std::string("Settings"));
	labelTitle->setLocation(screen_width, screen_height);
	labelTitle->setColor(.9f,.9f,.9f);
	labelTitle->setTextSize(60.0f);

	float menuX = screen_width *.5f;
	float menuY = screen_height *.4f;

	lFullscreen = new UILabel(std::string("Fullscreen"));
	lFullscreen->setLocation(menuX,menuY + 5.0f);
	lFullscreen->setColor(.9f,.9f,.9f);
	lFullscreen->setTextSize(16.0f);

	lTutorial = new UILabel(std::string("Show Tutorial"));
	lTutorial->setLocation(menuX,menuY + 35.0f);
	lTutorial->setColor(.9f,.9f,.9f);
	lTutorial->setTextSize(16.0f);
	
	lMasterVolume = new UILabel(std::string("Master Volume"));
	lMasterVolume->setLocation(menuX,menuY + 60.0f);
	lMasterVolume->setColor(.9f,.9f,.9f);
	lMasterVolume->setTextSize(16.0f);

	lMusicVol = new UILabel(std::string("Music Volume"));
	lMusicVol->setLocation(menuX,menuY + 85.0f);
	lMusicVol->setColor(.9f,.9f,.9f);
	lMusicVol->setTextSize(16.0f);

	lSfxVol = new UILabel(std::string("SFX Volume"));
	lSfxVol->setLocation(menuX,menuY + 110.0f);
	lSfxVol->setColor(.9f,.9f,.9f);
	lSfxVol->setTextSize(16.0f);

	cbResolutions = new UIComboBox(menuX - 100.0f,menuY + 130.0f);
	cbResolutions->init(screen_width, screen_height);
	cbResolutions->setupHide(HT_HOROZONTAL,cbResolutions->getX()+100.0f,hideTime,true);
	cbResolutions->setHidden();
	cbResolutions->addItem("640 x 480");
	cbResolutions->addItem("720 x 480");
	cbResolutions->addItem("720 x 576");
	cbResolutions->addItem("800 x 600");
	cbResolutions->addItem("1024 x 768");
	cbResolutions->addItem("1152 x 864");
	cbResolutions->addItem("1280 x 720");
	cbResolutions->addItem("1280 x 768");
	cbResolutions->addItem("1280 x 800");
	cbResolutions->addItem("1280 x 960");
	cbResolutions->addItem("1280 x 1024");
	cbResolutions->addItem("1360 x 765");
	cbResolutions->addItem("1360 x 768");
	cbResolutions->addItem("1366 x 768");
	cbResolutions->addItem("1400 x 1050");
	cbResolutions->addItem("1440 x 900");
	cbResolutions->addItem("1600 x 900");
	cbResolutions->addItem("1600 x 1024");
	cbResolutions->addItem("1600 x 1200");
	cbResolutions->addItem("1680 x 1050");
	cbResolutions->setMaxItemsToDisplay(8);

	cFullscreen = new UICheckbox(menuX - 4.0f,menuY,24.0f,24.0f,std::string(""));
	cFullscreen->setTextColor(.8f,.8f,.8f);
	cFullscreen->setupHide(HT_HOROZONTAL,cFullscreen->getX()+100.0f,hideTime,true);
	cFullscreen->setHidden();

	cTutorial = new UICheckbox(menuX - 4.0f,menuY + 30.0f,24.0f,24.0f,std::string(""));
	cTutorial->setTextColor(.8f,.8f,.8f);
	cTutorial->setupHide(HT_HOROZONTAL,cTutorial->getX()+100.0f,hideTime,true);
	cTutorial->setHidden();

	vMasterVol = new UIValueSlider();
	vMasterVol->setLocation(menuX,menuY + 60.0f);
	vMasterVol->setupHide(HT_HOROZONTAL,vMasterVol->getX()+100.0f,hideTime,true);
	vMasterVol->setHidden();

	vMusicVol = new UIValueSlider();
	vMusicVol->setLocation(menuX,menuY + 85.0f);
	vMusicVol->setupHide(HT_HOROZONTAL,vMusicVol->getX()+100.0f,hideTime,true);
	vMusicVol->setHidden();

	vSfxVol = new UIValueSlider();
	vSfxVol->setLocation(menuX,menuY + 110.0f);
	vSfxVol->setupHide(HT_HOROZONTAL,vSfxVol->getX()+100.0f,hideTime,true);
	vSfxVol->setHidden();

	buttonBack = new UIButton(menuX + 5.0f,
		menuY + 165.0f,100.0f,35.0f, std::string("Back"));
	buttonBack->setupHide(HT_VERTICAL,buttonBack->getY()+100.0f,hideTime,true);
	buttonBack->setHidden();

	buttonApply = new UIButton(menuX - 105.0f,
		menuY + 165.0f,100.0f,35.0f, std::string("Apply"));
	buttonApply->setupHide(HT_VERTICAL,buttonApply->getY()+100.0f,hideTime,true);
	buttonApply->setTooltip(std::string("Only needed for immediate\nresolution change"), 0.2f);
	buttonApply->setHidden();

	bBG = new UIBox(screen_width / 2.0f - 125.0f, menuY-5.0f,250.0f,165.0f);
	bBG->setupHide(HT_VERTICAL, bBG->getY() + 10.0f, hideTime, true);
	bBG->setHidden();
	bBG->setAlpha(.7f);

	// Load settings 
	cFullscreen->setChecked(settings->getFullscreen());
	cTutorial->setChecked(savedata->getShowTut());
	vMasterVol->setValue(settings->getMasterVol());
	vMusicVol->setValue(settings->getMusicVol());
	vSfxVol->setValue(settings->getSfxVol());

	// Set resolution 
	std::string res = "";
	res += toString((double)settings->getScreenWidth()) + " x " + toString((double)settings->getScreenHeight());
	int index = cbResolutions->findIndex(res);
	if (index != -1)
		cbResolutions->setSelectedItem(index);
}

// Load screen
void SettingsScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonBack->centerText(mUI->mTextRender);
	buttonApply->centerText(mUI->mTextRender);

	labelTitle->setLocation(
		(labelTitle->getX() * .5f) - (mUI->mTextRender->measureString(labelTitle->getText(), labelTitle->getTextSize()) * .5f),
		labelTitle->getY() * .4f - labelTitle->getTextSize() - 5.0f);
	labelTitle->setupHide(HT_VERTICAL,labelTitle->getY()-100.0f,hideTime,true);
	labelTitle->setHidden();

	// Align to right 
	lMasterVolume->setX(lMasterVolume->getX() - 5.0f - mUI->mTextRender->measureString(lMasterVolume->getText(), lMasterVolume->getTextSize()));
	lMasterVolume->setupHide(HT_HOROZONTAL,lMasterVolume->getX()-100.0f,hideTime,true);
	lMasterVolume->setHidden();
	
	lMusicVol->setX(lMusicVol->getX() - 5.0f - mUI->mTextRender->measureString(lMusicVol->getText(), lMusicVol->getTextSize()));
	lMusicVol->setupHide(HT_HOROZONTAL,lMusicVol->getX()-100.0f,hideTime,true);
	lMusicVol->setHidden();

	lSfxVol->setX(lSfxVol->getX() - 5.0f - mUI->mTextRender->measureString(lSfxVol->getText(), lSfxVol->getTextSize()));
	lSfxVol->setupHide(HT_HOROZONTAL,lSfxVol->getX()-100.0f,hideTime,true);
	lSfxVol->setHidden();

	lFullscreen->setX(lFullscreen->getX() - 5.0f - mUI->mTextRender->measureString(lFullscreen->getText(), lFullscreen->getTextSize()));
	lFullscreen->setupHide(HT_HOROZONTAL,lFullscreen->getX()-100.0f,hideTime,true);
	lFullscreen->setHidden();

	lTutorial->setX(lTutorial->getX() - 5.0f - mUI->mTextRender->measureString(lTutorial->getText(), lTutorial->getTextSize()));
	lTutorial->setupHide(HT_HOROZONTAL,lTutorial->getX()-100.0f,hideTime,true);
	lTutorial->setHidden();
	
	show();
}

// Update the state of the screen
void SettingsScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	// Update ui objects 
	labelTitle->update(deltaTime);
	cFullscreen->update(deltaTime);
	cTutorial->update(deltaTime);
	buttonBack->update(deltaTime);
	buttonApply->update(deltaTime);
	vMasterVol->update(deltaTime);
	vMusicVol->update(deltaTime);
	vSfxVol->update(deltaTime);
	lFullscreen->update(deltaTime);
	lTutorial->update(deltaTime);
	lMasterVolume->update(deltaTime);
	lMusicVol->update(deltaTime);
	lSfxVol->update(deltaTime);
	bBG->update(deltaTime);
	cbResolutions->update(deltaTime);
}

// Update input to the screen 
void SettingsScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	// Update fullscreen checkbox 
	cFullscreen->updateInput(mKeyH, mMouseH);
	settings->setFullscreen(cFullscreen->Checked());
	cTutorial->updateInput(mKeyH, mMouseH);
	savedata->setShowTut(cTutorial->Checked());

	// Update volume value sliders 
	vMasterVol->updateInput(mKeyH, mMouseH);
	settings->setMasterVol(vMasterVol->getValue());
	vMusicVol->updateInput(mKeyH, mMouseH);
	settings->setMusicVol(vMusicVol->getValue());
	vSfxVol->updateInput(mKeyH, mMouseH);
	settings->setSfxVol(vSfxVol->getValue());

	// Update resoluion combo box 
	cbResolutions->updateInput(mKeyH, mMouseH);
	if (cbResolutions->requestFocus()){
		if (uio_focus != NULL) uio_focus->focusLost(); 
		uio_focus = cbResolutions;
	}

	// Check if new resolution was selected 
	if (cbResolutions->wasItemSelected()){
		parseResLine(cbResolutions->getSelectedItem());
	}
	
	// Update back button 
	buttonBack->updateInput(mKeyH, mMouseH);
	if (buttonBack->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_MAIN;
		saveSettings(settings);
		saveSaveData(savedata);
		hide();
	}

	// Update apply button 
	buttonApply->updateInput(mKeyH, mMouseH);
	if (buttonApply->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		saveSettings(settings);
		transitionCode = RESTART_GAME;
	}
	if (buttonApply->requestFocus()){
		if (uio_focus != NULL) uio_focus->focusLost(); 
		uio_focus = buttonApply;
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
	cTutorial->draw(mgl, mUI);
	buttonBack->draw(mgl, mUI);
	buttonApply->draw(mgl, mUI);
	vMasterVol->draw(mgl, mUI);
	vMusicVol->draw(mgl, mUI);
	vSfxVol->draw(mgl, mUI);
	lFullscreen->draw(mgl, mUI);
	lTutorial->draw(mgl, mUI);
	lMasterVolume->draw(mgl, mUI);
	lMusicVol->draw(mgl, mUI);
	lSfxVol->draw(mgl, mUI);
	cbResolutions->draw(mgl, mUI);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void SettingsScreen::hide(){
	UIScreen::hide();

	// Hide ui objects 
	labelTitle->hide();
	cFullscreen->hide();
	cTutorial->hide();
	buttonBack->hide();
	buttonApply->hide();
	vMasterVol->hide();
	vMusicVol->hide();
	vSfxVol->hide();
	lFullscreen->hide();
	lTutorial->hide();
	lMasterVolume->hide();
	lMusicVol->hide();
	lSfxVol->hide();
	bBG->hide();
	cbResolutions->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void SettingsScreen::show(){
	UIScreen::show();

	// show ui objects 
	labelTitle->show();
	cFullscreen->show();
	cTutorial->show();
	buttonBack->show();
	buttonApply->show();
	vMasterVol->show();
	vMusicVol->show();
	vSfxVol->show();
	lFullscreen->show();
	lTutorial->show();
	lMasterVolume->show();
	lMusicVol->show();
	lSfxVol->show();
	bBG->show();
	cbResolutions->show();
}

// Parse a resolution line 
void SettingsScreen::parseResLine(std::string line){
	// Width and heigth 
	float width, height;

	// Find width 
	int index = line.find(" ");
	if (index == -1) return;
	width = (float)toDouble(line.substr(0,index));

	// Cut off front of line 
	line = line.substr(index+1, line.length());
	line = line.substr(line.find(" ")+1, line.length());

	height = (float)toDouble(line);

	settings->setScreenWidth((int)width);
	settings->setScreenHeight((int)height);
}
