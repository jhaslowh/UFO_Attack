#include "LevelSelectScreen.h"

using namespace std;

LevelSelectScreen::LevelSelectScreen() : UIScreen(){
	hideOnClose = true;
	numberOfLevels = 0;
	for (int i = 0; i < numberOfLevels && i < 20; i++)
		buttonLevels[i] = NULL;
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

	loadLevelList();

	logo.setPosition(screen_width * .5f, screen_height * .5f);
	logo.setOrigin(512.0f, 256.0f);
	logo.setAlpha(0.0f);
}

// Load screen
void LevelSelectScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonMainMenu->centerText(mUI->mTextRender);

	logo.setup(1024.0f, 512.0f, "images/us_map_white.png");
	
	show();
}

// Update the state of the screen
void LevelSelectScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	buttonMainMenu->update(deltaTime);
	for(int i=0;i<numberOfLevels;i++)
		buttonLevels[i]->update(deltaTime);

	logo.setAlpha(buttonMainMenu->getOpacity());
}

// Update input to the screen 
void LevelSelectScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	buttonMainMenu->updateInput(mKeyH, mMouseH);

	// Close game
	if (buttonMainMenu->wasClicked()){
		transitionCode = SCREEN_MAIN;
		hide();
	}

	// Update level button input 
	for(int i=0;i<numberOfLevels;i++)
	{
		buttonLevels[i]->updateInput(mKeyH, mMouseH);
		if(buttonLevels[i]->wasClicked())
		{
			transitionCode = SCREEN_GAME_NEW;
			std::string fileLocation = ".\\Levels\\temp.txt";
			std::ofstream outfile (fileLocation);
			outfile << levelsList[i] <<std::endl;
			outfile.close();
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

	logo.draw(*mgl);

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

void LevelSelectScreen::loadLevelList(){
	string line;
	ifstream myfile (".\\Levels\\MasterLevelFile.txt");
	if (myfile.is_open())
	{
		cout << "Loading level list..\n";
		getline(myfile, line);
		numberOfLevels = atoi(line.c_str());
		for(int i=0;i<numberOfLevels && i<20;i++)
		{
			getline(myfile, line);
			size_t pos = 0;
			string storage[3];
			std::string delimiter = ";";
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
			buttonLevels[i] = new UIButton(
				// Start at center, move to top left of background. Move to button location, 
				// then minus half of width and height to center button on location. 
				((screen_width * .5f) - 512.0f) + ((float)atoi(storage[1].c_str()) - 25.0f),
				((screen_height * .5f) - 256.0f) + ((float)atoi(storage[2].c_str()) - 25.0f),50.0f,50.0f, "");//, storage[0]);
			buttonLevels[i]->setupHide(HT_VERTICAL,buttonLevels[i]->getY()+10.0f,hideTime,true);
			buttonLevels[i]->setImageId(UII_LS_TARGET_DARK);
			buttonLevels[i]->setImageIdHover(UII_LS_TARGET_LIGHT);
			buttonLevels[i]->setImageIdClick(UII_LS_TARGET_LIGHT);
			buttonLevels[i]->setHidden();
			//levelsList[i].push_back((storage[0].c_str()));
			levelsList[i] = storage[0];
		}
		myfile.close();
		cout << "Done loading level list.\n";
	}
	else
	{
		cout << "Unable to open master level list file.\n";
	}
}

