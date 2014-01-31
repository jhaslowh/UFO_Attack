#include "FreePlayScreen.h"

FreePlayScreen::FreePlayScreen() : UIScreen()
{
	pauseScreen = NULL;
	level = NULL;
	timer = 0;
	paused = false;
	gameover = false;
}

FreePlayScreen::~FreePlayScreen()
{
	delete level;
	delete pauseScreen;
}

// Initialize screen
void FreePlayScreen::init(float screen_width, float screen_height){
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
void FreePlayScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	level->load();
	levelEditor.load(mAtlas);
}

// Update the state of the screen
void FreePlayScreen::update(float deltaTime){
	UIScreen::update(deltaTime);
	
	pauseScreen->update(deltaTime);

	if (!paused){
		levelEditor.update(deltaTime, &(level->handlers));
		if (!levelEditor.Enabled())
			level->update(deltaTime);
	}

}

// Update input to the screen 
void FreePlayScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
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
void FreePlayScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	this->updateTerrain();
	UIScreen::draw(mgl, mAtlas);

	mgl->setProjectionMatrix(mgl->orthoMatrix);

	level->draw(mgl, mAtlas);
	levelEditor.draw(mgl, (UIAtlas*)mAtlas);
	pauseScreen->draw(mgl, mAtlas);
}

void FreePlayScreen::updateTerrain()
{
	//cout<<"Entered Update Terrain.\n";
	Ground* tempGround = level->getGround();
	Player* tempPlayer = level->getPlayer();
	//cout<< "Player" << tempPlayer->getX();
	Camera2D* tempCamera = new Camera2D();
	//cout<< "Terrain - 5" << tempGround->getPoint(tempGround->getPointCount()-5)->getX();
	//if(tempCamera->toScreenX(tempPlayer->getX()) >= tempGround->getPoint(tempGround->getPointCount()-5)->getX())
	if(timer == 30)
	{
		timer = 0;
		//cout<<"Need to generator new Terrain.\n";
		int generatorCounter = 0;
		float randomXHolder = tempGround->getPoint(tempGround->getPointCount()-1)->getX();
		float randomYHolder = tempGround->getPoint(tempGround->getPointCount()-1)->getY();
		while(generatorCounter <= 10)
		{
			randomXHolder += (float)((rand() % 75));
			if(rand() % 10 == 1)
			{
				randomYHolder += (float)(((rand() % 100)-50));
			}
			else
			{
				randomYHolder += (float)(((rand() % 20) - 10));
			}
			generatorCounter++;
			level->updateTerrain(randomXHolder, randomYHolder);
		}
		level->getProperties()->setLevelRight(tempGround->getPoint(tempGround->getPointCount()-1)->getX());
		/*for(int i=0;i<tempGround->getPointCount();i++)
		{
			if(tempGround->getPoint(i)->getX() <= tempCamera->toScreenX(tempPlayer->getX()))
			{
				level->getGround()->remove(i);
			}
		}*/
	}
	else
	{
	//	do nothing;
		timer++;
	}
}

