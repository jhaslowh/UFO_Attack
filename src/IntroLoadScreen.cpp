#include "IntroLoadScreen.h"

IntroLoadScreen::IntroLoadScreen() : UIScreen(){
	waitTime = 2.0f;
}
IntroLoadScreen::~IntroLoadScreen(){}


// Initialize screen
void IntroLoadScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	DGSplash.setPosition(screen_width * .5f, screen_height * .5f);
	DGSplash.setOrigin(256.0f, 128.0f);
}

// Load Screen
void IntroLoadScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	DGSplash.setup(512.0f,256.0f,std::string("images/DGSplash.png"));
}

// Update the state of the screen
void IntroLoadScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	if (waitTime > 0){
		waitTime -= deltaTime;
		if (waitTime <= 0){
			transitionCode = SCREEN_MAIN;
			waitTime = 0.0f;
		}
	}
	
}

// Draw the screen
void IntroLoadScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	// Setup world matrix to orthographic 
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	DGSplash.draw(*mgl);
}
