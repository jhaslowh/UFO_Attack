#include "LevelSelectScreen.h"

using namespace std;

LevelSelectScreen::LevelSelectScreen(SaveData* s) : UIScreen(){
	hideOnClose = true;
	numberOfLevels = 0;
	for (int i = 0; i < numberOfLevels && i < 20; i++)
		buttonLevels[i] = NULL;
	sd = s;
}

LevelSelectScreen::~LevelSelectScreen(){
	delete buttonMainMenu;
	for (int i = 0; i < numberOfLevels && i < 20; i++)
		delete buttonLevels[i];
}

// Initialize screen
void LevelSelectScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	this->screen_width = screen_width;
	this->screen_height = screen_height;

	buttonMainMenu = new UIButton(10.0f,screen_height -45.0f,100.0f,35.0f, std::string("MainMenu"));
	buttonMainMenu->setupHide(HT_HOROZONTAL,buttonMainMenu->getX()-100.0f,hideTime,true);
	buttonMainMenu->setHidden();

	// Setup map
	float scalex = 1.0f;
	float scaley = 1.0f;
	if (screen_width < 1024.0f)
		scalex = screen_width / 1024.0f;
	if (screen_height < 512.0f)
		scaley = screen_height / 512.0f;

	if (scaley < scalex)
		scalex = scaley;

	map.setPosition(screen_width * .5f, screen_height * .5f);
	map.setOrigin(512.0f, 256.0f);
	map.setAlpha(0.0f);
	map.setScale(scalex);

	// Load the levels and create buttons
	// Must be done after map is created 
	loadLevelList();
}

// Load screen
void LevelSelectScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonMainMenu->centerText(mUI->mTextRender);

	map.setup(1024.0f, 512.0f, "images/us_map_white.png");
	
	// Fix level button text
	for (int i = 0; i < numberOfLevels; i++){
		buttonLevels[i]->fixTextLoc(mUI->mTextRender);
	}

	show();
}


// Unload screen textures
// THIS MUST BE CALLED IF YOU LOAD STUFF.
void LevelSelectScreen::unload(){
	UIScreen::unload();

	map.unload();
}

// Update the state of the screen
void LevelSelectScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	buttonMainMenu->update(deltaTime);
	for(int i=0;i<numberOfLevels;i++)
		buttonLevels[i]->update(deltaTime);

	map.setAlpha(buttonMainMenu->getOpacity());
}

// Update input to the screen 
void LevelSelectScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	buttonMainMenu->updateInput(mKeyH, mMouseH);

	// Close game
	if (buttonMainMenu->wasClicked()){
		soundHandler->playSoundEffect(SE_BUTTON_PRESS);
		transitionCode = SCREEN_MAIN;
		hide();
	}

	// Update level button input 
	for(int i=0;i<numberOfLevels;i++)
	{
		buttonLevels[i]->updateInput(mKeyH, mMouseH);
		if(buttonLevels[i]->wasClicked())
		{
			soundHandler->playSoundEffect(SE_BUTTON_PRESS);
			transitionCode = SCREEN_GAME_NEW;
			sd->levelToLoad = levelsList[i];
			hide();
		}
	}


}

// Draw the screen
void LevelSelectScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;

	// Setup world matrix
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	map.draw(*mgl);

	// Bind bufferes
	mUI->bindBuffers(mgl);
	mUI->bindTexture(mgl);

	buttonMainMenu->draw(mgl, mUI);
	for(int i=0;i<numberOfLevels;i++)
		buttonLevels[i]->draw(mgl, mUI);
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void LevelSelectScreen::hide(){
	UIScreen::hide();

	buttonMainMenu->hide();
	for(int i=0;i<numberOfLevels;i++)
		buttonLevels[i]->hide();
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void LevelSelectScreen::show(){
	UIScreen::show();

	buttonMainMenu->show();
	for(int i=0;i<numberOfLevels;i++)
		buttonLevels[i]->show();
}

// Parse a command give
bool LevelSelectScreen::parseCommand(UITerminal* terminal, string command, string args){
	if (UIScreen::parseCommand(terminal, command, args))
		return true;

	// Check for reset commmand
	if (command == "unlockall"){
		
		for(int i=0;i<numberOfLevels;i++)
			buttonLevels[i]->setLocked(false);

		terminal->addLine(command, TL_SUCCESS);

		return true;
	}

	return false;
}

void LevelSelectScreen::loadLevelList(){
	float mapScale = map.getScale();
	string line;
	ifstream completionFile ("./Levels/MasterLevelFile.txt");
	int numberOfCompletedLevels = 0;
	if(completionFile.is_open())
	{
		getline(completionFile, line);
		numberOfLevels = atoi(line.c_str());
		for(int i=0;i<numberOfLevels;i++)
		{
			getline(completionFile, line);
			size_t pos = 0;
			string storage[5];
			std::string delimiter = ".";
			int counter = 0;
			while ((pos = line.find(delimiter)) != std::string::npos) 
			{
				storage[counter] = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				counter++;
			}			
			storage[counter] = line;
			if (sd->levelCompleted(storage[0]))
				numberOfCompletedLevels++;
		}
	}
	completionFile.close();
	ifstream myfile ("./Levels/MasterLevelFile.txt");
	if (myfile.is_open())
	{
		//cout << "Loading level list..\n";
		getline(myfile, line);
		numberOfLevels = atoi(line.c_str());
		// Tell savedata how many levels there are
		sd->levelCount = numberOfLevels;
		for(int i=0;i<numberOfLevels && i<20;i++)
		{
			getline(myfile, line);
			size_t pos = 0;
			string storage[5];
			std::string delimiter = ".";
			int counter = 0;
			while ((pos = line.find(delimiter)) != std::string::npos) 
			{
				storage[counter] = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				counter++;
			}			
			storage[counter] = line;
			//cout << storage[1] << " \n";
			//cout << storage[2] << " \n";
			buttonLevels[i] = new UILevelButton(
				// Start at center, move to top left of background. Move to button location, 
				// then minus half of width and height to center button on location. 
				((screen_width * .5f) - (512.0f*mapScale)) + (((float)atoi(storage[1].c_str()) - 25.0f)*mapScale),
				((screen_height * .5f) - (256.0f*mapScale)) + (((float)atoi(storage[2].c_str()) - 25.0f)*mapScale),
				50.0f * mapScale,
				50.0f * mapScale);
			buttonLevels[i]->setupHide(HT_VERTICAL,buttonLevels[i]->getY()+10.0f,hideTime,true);
			
			// Set level to check mark if completed 
			if (sd->levelCompleted(storage[0]))
				buttonLevels[i]->setCompleted(true);
			//cout << "levelcount: " << numberOfCompletedLevels << std::endl;
			//cout << "level required: " << storage[4] << std::endl;
			if(numberOfCompletedLevels<atoi(storage[4].c_str()))
			{
				buttonLevels[i]->setLocked(true);
			}
			// Uncomment this to lock a level
			//buttonLevels[i]->setLocked(true);
			buttonLevels[i]->setDifficulty(atoi(storage[3].c_str()));
			//cout << "Loading Level " << i << " difficulty: " << storage[3];
			buttonLevels[i]->setHidden();
			buttonLevels[i]->setScale(map.getScale());
			buttonLevels[i]->setTitle(storage[0]);
			//buttonLevels[i]->setDesc("Temp Description\nLine two");

			// Add level name to list 
			levelsList[i] = storage[0];
		}
		myfile.close();
		//cout << "Done loading level list.\n";
	}
	else
	{
		cout << "Unable to open master level list file.\n";
	}
}

