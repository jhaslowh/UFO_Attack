#include "IntroLoadScreen.h"

IntroLoadScreen::IntroLoadScreen() : UIScreen(){
	waitTime = 1.0f;
	mColor[0] = .1f;
	mColor[1] = .1f;
	mColor[2] = .1f;
	mColor[3] = 1.0f;
}
IntroLoadScreen::~IntroLoadScreen(){}

// Update the state of the screen
void IntroLoadScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	if (waitTime > 0){
		waitTime -= deltaTime;
		if (waitTime <= 0){
			transitionCode = SCREEN_MAIN;
			waitTime = 0;
		}
	}
}

// Draw the screen
void IntroLoadScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);
	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);

	mgl->setFlatColor(mColor);
	mUI->mTextRender->drawText(*mgl, std::string("Loading ..."),10.0f,10.0f,0.0f,40.0f);
}
