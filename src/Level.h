#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Camera2D.h"
#include "FileHelper.h"
#include "LevelIO.h"
#include "GameAtlas.h"
#include "GLColors.h"
#include "GLHandler.h"
#include "Ground.h"
#include "Handlers.h"
#include "KeyHandler.h"
#include "ProjectileHandler.h"
#include "ParticleHandler.h"
#include "SceneryHandler.h"
#include "ExplHandler.h"
#include "MouseHandler.h"
#include "NPCHandler.h"
#include "LevelProperties.h"
#include "Player.h"
#include "Sky.h"
#include "TextureAtlas.h"
#include "TutorialSystem.h"
#include "ScriptHandler.h"

class Level
{
	Player* player;
	Ground* ground;
	GameAtlas gameAtlas;
	SceneryHandler* sceneryHandler;
	NPCHandler* npcHandler;
	ProjectileHandler* projHandler;
	ParticleHandler* partHandler;
	Camera2D camera;
	LevelProperties levelProps;
	ExplHandler* explHandler;
	ScriptHandler* scriptHandler;
	TutorialSystem tutSys;
	Sky sky;

	// States 
	bool loaded;
	bool victory;

public:
	Handlers handlers;

	Level();
	~Level();

	// initialize level
	void init(float screen_width, float screen_height, SaveData* savedata, void* soundHandler);

	// Load level (use for textures)
	void load(GLHandler* mgl);

	// Unload level
	void unload();

	// Update level state
	void update(float deltaTime);

	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw level 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Draw level ui
	// Note: this will not use the level's Camera views
	void drawUI(GLHandler* mgl, UIAtlas* mAtlas);

	void loadLevelData(std::string levelFile);
	//Reads in the data from the file

	// Returns current victory state
	bool getVictory();

	// Call to skip tutorial
	void skipTut();
};

