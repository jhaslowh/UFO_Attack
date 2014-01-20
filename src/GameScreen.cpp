#include "GameScreen.h"


GameScreen::GameScreen(void)
{
	paused = false;
	gameover = false;
}

GameScreen::~GameScreen(void)
{
	delete(level);
	delete(pauseScreen);
}

// Initialize screen
void GameScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);
	level = new Level();

	pauseScreen = new PauseScreen();
	pauseScreen->init(screen_width, screen_height);
	
}

// Load screen
// Note: If textures need to be loaded, they must
// be loaded in this method or they will not work. 
void GameScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

}

// Update the state of the screen
void GameScreen::update(float deltaTime){
	UIScreen::update(deltaTime);
	
	pauseScreen->update(deltaTime);

	if (!paused){

	}
}

// Update input to the screen 
void GameScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	if (paused){
		pauseScreen->updateInput(mKeyH, mMouseH);

		// Check for quit
		if (pauseScreen->getTransitionCode() == SCREEN_MAIN)
			transitionCode = SCREEN_MAIN;

		// Check for pause/unpause
		if (pauseScreen->getTransitionCode() == CLOSE_SCREEN ||
			mKeyH->keyPressed(KEY_P) || mKeyH->keyPressed(KEY_ESCAPE)){
			paused = false;
			pauseScreen->hide();
		}
	}
	else{
		// Check for pause/unpause
		if (mKeyH->keyPressed(KEY_P) || mKeyH->keyPressed(KEY_ESCAPE)){
			paused = true;
			pauseScreen->show();
		}
	}
}

// Draw the screen
void GameScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	pauseScreen->draw(mgl, mAtlas);
}
