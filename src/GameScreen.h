#pragma once
#include "UIScreen.h"
#include "PauseScreen.h"
#include "Level.h"
#include "LevelEditor.h"
#include "SaveData.h"
#include "GLColors.h"
#include "Sky.h"

class GameScreen : public UIScreen
{
	// Player save data
	SaveData* savedata;

	// States properties
	bool paused;
	
	// Gameovers
	bool gameover;
	float gameoverTime;
	float cGameoverTime;
	float gameOverX, gameOverY;

	// Victory 
	bool victory;
	float victoryTime;
	float cVictoryTime;
	float victoryX, victoryY;

	// Screen size for reference 
	float screenWidth, screenHeight;

	Level* level;
	PauseScreen* pauseScreen;
	LevelEditor levelEditor;
	std::string levelFile;

public:
	GameScreen(SaveData* sd);
	//GameScreen(SaveData* sd, string levelLoad);
	virtual ~GameScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height, void* sh);

	// Load screen
	// Note: If textures need to be loaded, they must
	// be loaded in this method or they will not work. 
	virtual void load(TextureAtlas* mAtlas);

	// Unload screen textures
	// THIS MUST BE CALLED IF YOU LOAD STUFF.
	virtual void unload();

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Parse a command give
	virtual bool parseCommand(UITerminal* terminal, std::string command, std::string args);
};

