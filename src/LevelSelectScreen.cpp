#include "LevelSelectScreen.h"

using namespace std;

LevelSelectScreen::LevelSelectScreen() : UIScreen(){
	hideOnClose = true;
	numberOfLevels = 0;
	//std::vector<std::string> levelsList(20);
}

LevelSelectScreen::~LevelSelectScreen(){
	delete buttonMainMenu;
	//delete buttonLevels;
}

// Initialize screen
void LevelSelectScreen::init(float screen_width, float screen_height, void* sh){
	UIScreen::init(screen_width, screen_height, sh);

	buttonMainMenu = new UIButton(100,screen_height -100,100.0f,35.0f, std::string("Main Menu"));
	buttonMainMenu->setupHide(HT_VERTICAL,buttonMainMenu->getY()+100.0f,hideTime,true);
	buttonMainMenu->setHidden();

	loadLevelList();

	logo.setPosition(0.0f, 0.0f);//(screen_width * .5f, screen_height * .5f - 150.0f);
	logo.setOrigin(0.0f, 0.0f);
	logo.setAlpha(0.0f);
	cout << "initialized";
}

// Load screen
void LevelSelectScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);
	UIAtlas* mUI = (UIAtlas*)mAtlas;
	buttonMainMenu->centerText(mUI->mTextRender);

	logo.setup(1280.0f, 720.0f, "images/unitedStatesMap.png");
	
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
	for(int i=0;i<numberOfLevels;i++)
		buttonLevels[i]->updateInput(mKeyH, mMouseH);

	// Close game
	if (buttonMainMenu->wasClicked()){
		transitionCode = SCREEN_MAIN;
		hide();
	}

	for(int i=0;i<numberOfLevels;i++)
	{
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
	//cout << "drawing";
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
		cout << "if it crashes after this but before next messege than someone formatted something wrong.";
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
			cout << storage[1] << " \n";
			cout << storage[2] << " \n";
			buttonLevels[i] = new UIButton(screen_width * .5f + (float)atoi(storage[1].c_str()),screen_height * .5f + (float)atoi(storage[2].c_str()),100.0f,35.0f, storage[0]);
			buttonLevels[i]->setupHide(HT_VERTICAL,buttonLevels[i]->getY()+100.0f,hideTime,true);
			buttonLevels[i]->setHidden();
			//levelsList[i].push_back((storage[0].c_str()));
			levelsList[i] = storage[0];
		}
		myfile.close();
		cout << "howdy ho\n.";
	}
	else
	{
		cout << "Unable to open file, file not found.";
	}
}

