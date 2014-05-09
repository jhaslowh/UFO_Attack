#include "PauseScreen.h"


PauseScreen::PauseScreen() : UIScreen(){
	bResume = NULL;
	bQuit = NULL;
	lTitle = NULL;
	controls = NULL;
	controlsBack = NULL;
	showControls = false;
}
PauseScreen::~PauseScreen()
{
	delete bResume;
	bResume = NULL;
	delete bQuit;
	bQuit = NULL;
	delete lTitle;
	lTitle = NULL;
	delete controls;
	controls = NULL;
	delete controlsBack;
	controlsBack = NULL;
}

// Initialize screen
void PauseScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	bgOverlay.setSize(screen_width, screen_height);

	bResume = new UIButton((screen_width/2.0f)-50.0f,(screen_height *.5f),100.0f,35.0f, std::string("Resume"));
	bResume->setupHide(HT_VERTICAL,bResume->getY()+100.0f,.2f,true);
	bResume->setHidden();

	controls = new UIButton((screen_width/2.0f)-50.0f,(screen_height *.5f)+45.05f,100.0f,35.0f, std::string("Controls"));
	controls->setupHide(HT_VERTICAL,controls->getY()+100.0f,.2f,true);
	controls->setHidden();

	bQuit = new UIButton((screen_width/2.0f)-50.0f,(screen_height *.5f)+90.0f,100.0f,35.0f, std::string("MainMenu"));
	bQuit->setupHide(HT_VERTICAL,bQuit->getY()+100.0f,.2f,true);
	bQuit->setHidden();

	controlsBack = new UIButton((screen_width/2.0f)-50.0f,(screen_height *.5f)+200.05f,100.0f,35.0f, std::string("Back"));
	controlsBack->setupHide(HT_VERTICAL,controlsBack->getY()+100.0f,.2f,true);
	controlsBack->setHidden();

	lTitle = new UILabel(std::string("Paused"));
	lTitle->setTextSize(40.0f);
	lTitle->setColor(.9f,.9f,.9f);
	lTitle->setLocation(screen_width, (screen_height*.5f)-50.0f);
	lTitle->setupHide(HT_VERTICAL,lTitle->getY()+100.0f,.2f,true);
	lTitle->setHidden();

	contrlImage.setPosition((screen_width*.5f)-300.0f,(screen_height *.5f)-200.05f);
}

// Load screen
void PauseScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	lTitle->setX(
		(lTitle->getX()/2.0f) - 
		(mUI->mTextRender->measureString(lTitle->getText(), lTitle->getTextSize())/2.0f));
	bResume->centerText(mUI->mTextRender);
	bQuit->centerText(mUI->mTextRender);
	controls->centerText(mUI->mTextRender);
	controlsBack->centerText(mUI->mTextRender);

	contrlImage.setup(600.0f, 400.0f, "images/controls.png");
}


// Unload screen textures
// THIS MUST BE CALLED IF YOU LOAD STUFF.
void PauseScreen::unload(){
	UIScreen::unload();

	contrlImage.unload();
}

// Update the state of the screen
void PauseScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	bResume->update(deltaTime);
	bQuit->update(deltaTime);
	lTitle->update(deltaTime);
	controls->update(deltaTime);
	controlsBack->update(deltaTime);
}

// Update input to the screen 
void PauseScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	if (showControls){
		controlsBack->updateInput(mKeyH, mMouseH);
		if (controlsBack->wasClicked()){
			soundHandler->playSoundEffect(SE_BUTTON_PRESS);
			controls->show();
			bResume->show();
			bQuit->show();
			controlsBack->hide();
			showControls = false;
		}
	}
	else {
		bResume->updateInput(mKeyH, mMouseH);
		bQuit->updateInput(mKeyH, mMouseH);
		controls->updateInput(mKeyH, mMouseH);

		if (controls->wasClicked()){
			soundHandler->playSoundEffect(SE_BUTTON_PRESS);
			controls->hide();
			bResume->hide();
			bQuit->hide();
			controlsBack->show();
			showControls = true;
		}
		if (bResume->wasClicked()){
			soundHandler->playSoundEffect(SE_BUTTON_PRESS);
			transitionCode = CLOSE_SCREEN;
		}
		if (bQuit->wasClicked()){
			soundHandler->playSoundEffect(SE_BUTTON_PRESS);
			transitionCode = SCREEN_MAIN;
		}
	}
}

// Draw the screen
void PauseScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);
	
	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);
	
	mgl->setFlatColor(0.0f,0.0f,0.0f,lTitle->getOpacity()*.5f);
	mUI->drawScale2(mgl,UII_REC,bgOverlay.getX(),bgOverlay.getY(), bgOverlay.getWidth(),bgOverlay.getHeight());
	if (!showControls)
		lTitle->draw(mgl, mUI);
	bResume->draw(mgl, mUI);
	bQuit->draw(mgl, mUI);
	controls->draw(mgl, mUI);
	controlsBack->draw(mgl, mUI);

	if (showControls)
		contrlImage.draw(*mgl);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void PauseScreen::hide(){
	UIScreen::hide();
	bResume->hide();
	bQuit->hide();
	lTitle->hide();
	controls->hide();
	transitionCode = NO_TRANSITION;
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void PauseScreen::show(){
	UIScreen::show();
	bResume->show();
	bQuit->show();
	lTitle->show();
	controls->show();
}