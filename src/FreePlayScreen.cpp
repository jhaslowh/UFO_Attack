#include "FreePlayScreen.h"
using namespace std;

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
void FreePlayScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	level = new Level();
	level->init(screen_width, screen_height, NULL, NULL);

	pauseScreen = new PauseScreen();
	pauseScreen->init(screen_width, screen_height, sh);

	levelEditor.init(screen_width, screen_height);
}

// Load screen
// Note: If textures need to be loaded, they must
// be loaded in this method or they will not work. 
void FreePlayScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	//level->load(); // You dont need to call this, it is done internally by level.draw()

	levelEditor.load(mAtlas);
}

// Unload screen textures
// THIS MUST BE CALLED IF YOU LOAD STUFF.
void FreePlayScreen::unload(){
	if (unloaded) return;
	UIScreen::unload();

	level->unload();
}

// Update the state of the screen
void FreePlayScreen::update(float deltaTime){
	UIScreen::update(deltaTime);
	
	pauseScreen->update(deltaTime);

	if (!paused){
		levelEditor.update(deltaTime, &(level->handlers));
		updateTerrain(&(level->handlers));

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
	
	UIScreen::draw(mgl, mAtlas);

	mgl->setProjectionMatrix(mgl->orthoMatrix);

	level->draw(mgl, mAtlas);
	
	mAtlas->bindBuffers(mgl);
	mAtlas->bindTexture(mgl);

	level->drawUI(mgl, (UIAtlas*)mAtlas);
	levelEditor.draw(mgl, (UIAtlas*)mAtlas);
	pauseScreen->draw(mgl, mAtlas);
}

void FreePlayScreen::updateTerrain(Handlers* handlers)
{
	//cout<<"Entered Update Terrain.\n";
	Ground* tempGround = (Ground*)(handlers->ground);
	Player* tempPlayer = (Player*)(handlers->player);
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
				randomYHolder += (float)(((rand() % 400)-200));
			}
			else
			{
				randomYHolder += (float)(((rand() % 50) - 25));
			}
			generatorCounter++;
			tempGround->add(new Point(randomXHolder, randomYHolder));
		}

		// Fix level boundaries 
		((LevelProperties*)(level->handlers.levelProps))->setLevelRight(tempGround->getPoint(tempGround->getPointCount()-1)->getX());
		//((LevelProperties*)(level->handlers.levelProps))->setLevelLeft(((Camera2D*)level->handlers.camera)->toLevelX(0));

		// Fix ufo location 
		// TODO make sure ufo is not less than level left 		

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

// Parse a command give
bool FreePlayScreen::parseCommand(UITerminal* terminal, string command, string args){
	if (UIScreen::parseCommand(terminal, command, args))
		return true;

	// Update level editor commands if enabled 
	if (levelEditor.parseCommand(terminal, command, args))
		return true;

	// If you find a command and use it, return true.
	//
	// Also if you want to split args into sub command and sub arg, 
	// you can do the following.
	//
	// string subCommand("none");
	// string subArgs("none");
	//
	// UITerminal::getCommandAndArgs(&args, &subCommand, &subArgs);
	// 
	// If getCommandAndArgs() finds a subCommand, it will no longer be 
	// equal to none. And same for sub args. 
	return false;
}

