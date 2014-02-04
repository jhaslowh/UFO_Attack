#include "GameScreen.h"

GameScreen::GameScreen() : UIScreen()
{
	pauseScreen = NULL;
	level = NULL;
	paused = false;
	gameover = false;
}

GameScreen::~GameScreen()
{
	delete level;
	delete pauseScreen;
}

// Initialize screen
void GameScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	level = new Level();
	level->init(screen_width, screen_height);

	pauseScreen = new PauseScreen();
	pauseScreen->init(screen_width, screen_height);

	levelEditor.init(screen_width, screen_height);
}

// Load screen
// Note: If textures need to be loaded, they must
// be loaded in this method or they will not work. 
void GameScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	level->load();
	levelEditor.load(mAtlas);
	levelEditor.setHandlers(&level->handlers);
}

// Update the state of the screen
void GameScreen::update(float deltaTime){
	UIScreen::update(deltaTime);
	
	pauseScreen->update(deltaTime);

	if (!paused){
		levelEditor.update(deltaTime, &(level->handlers));
		if (!levelEditor.Enabled())
			level->update(deltaTime);
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
			mKeyH->keyReleased(KEY_P) || mKeyH->keyReleased(KEY_ESCAPE)){
			paused = false;
			pauseScreen->hide();
		}
	}
	else{
		// Update level editor input 
		levelEditor.updateInput(mKeyH, mMouseH, &(level->handlers));

		// Update level input if editor off
		if (!levelEditor.Enabled()){
			// Check for pause/unpause
			if (mKeyH->keyReleased(KEY_P) || mKeyH->keyReleased(KEY_ESCAPE)){
				paused = true;
				pauseScreen->show();
			}

			level->updateInput(mKeyH, mMouseH);
		}
	}
}

// Draw the screen
void GameScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	mgl->setProjectionMatrix(mgl->orthoMatrix);

	level->draw(mgl, mAtlas);
	
	mAtlas->bindBuffers(mgl);
	mAtlas->bindTexture(mgl);

	levelEditor.draw(mgl, (UIAtlas*)mAtlas);
	pauseScreen->draw(mgl, mAtlas);
}


// Parse a command give
bool GameScreen::parseCommand(UITerminal* terminal, string command, string args){
	UIScreen::parseCommand(terminal, command, args);

	// Update level editor commands if enabled 
	if (levelEditor.Enabled()){
		if (levelEditor.parseCommand(terminal, command, args))
			return true;
	}
	return false;
}

