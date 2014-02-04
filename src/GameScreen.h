#pragma once
#include "UIScreen.h"
#include "PauseScreen.h"
#include "Level.h"
#include "LevelEditor.h"

class GameScreen : public UIScreen
{
	// States 
	bool paused, gameover;

	// Screen size for reference 
	float screenWidth, screenHeight;

	Level* level;
	PauseScreen* pauseScreen;
	LevelEditor levelEditor;

public:
	GameScreen();
	virtual ~GameScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height);

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
	virtual bool parseCommand(UITerminal* terminal, string command, string args);
};

