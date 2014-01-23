#include "PauseScreen.h"


PauseScreen::PauseScreen() : UIScreen(){
	bResume = NULL;
	bQuit = NULL;
	lTitle = NULL;
}
PauseScreen::~PauseScreen()
{
	delete bResume;
	delete bQuit;
	delete lTitle;
}

// Initialize screen
void PauseScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	bResume = new UIButton((screen_width/2.0f)-50.0f,(screen_height *.35f),100.0f,35.0f, std::string("Resume"));
	bResume->setupHide(HT_VERTICAL,bResume->getY()+100.0f,.4f,true);
	bResume->setHidden();

	bQuit = new UIButton((screen_width/2.0f)-50.0f,(screen_height *.35f)+45.0f,100.0f,35.0f, std::string("Quit"));
	bQuit->setupHide(HT_VERTICAL,bQuit->getY()+100.0f,.4f,true);
	bQuit->setHidden();

	lTitle = new UILabel(string("Paused"));
	lTitle->setTextSize(40.0f);
	lTitle->setColor(.9f,.9f,.9f);
	lTitle->setLocation(screen_width, (screen_height*.35f)-50.0f);
	lTitle->setupHide(HT_VERTICAL,lTitle->getY()+100.0f,.4f,true);
	lTitle->setHidden();
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
}

// Update the state of the screen
void PauseScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	bResume->update(deltaTime);
	bQuit->update(deltaTime);
	lTitle->update(deltaTime);
}

// Update input to the screen 
void PauseScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	bResume->updateInput(mKeyH, mMouseH);
	bQuit->updateInput(mKeyH, mMouseH);

	if (bResume->wasClicked())
		transitionCode = CLOSE_SCREEN;
	if (bQuit->wasClicked())
		transitionCode = SCREEN_MAIN;
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
	
	lTitle->draw(mgl, mUI);
	bResume->draw(mgl, mUI);
	bQuit->draw(mgl, mUI);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void PauseScreen::hide(){
	UIScreen::hide();
	bResume->hide();
	bQuit->hide();
	lTitle->hide();
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
}