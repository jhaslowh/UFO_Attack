#pragma once
#include "Camera2D.h"
#include "FileHelper.h"
#include "GameAtlas.h"
#include "GLColors.h"
#include "GLHandler.h"
#include "Ground.h"
#include "Handlers.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "LevelProperties.h"
#include "NPCHandler.h"
#include "NPCSoldier.h"
#include "Player.h"
#include "ProjectileHandler.h"
#include "SceneryHandler.h"
#include "Sky.h"
#include "TextureAtlas.h"
#include "Tree.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Level
{
	Player* player;
	Ground* ground;
	GameAtlas gameAtlas;
	SceneryHandler* sceneryHandler;
	NPCHandler* npcHandler;
	ProjectileHandler* projHandler;
	Camera2D camera;
	LevelProperties levelProps;
	Sky sky;

	// States 
	bool loaded;
	bool victory;

public:
	Handlers handlers;

	Level();
	~Level();

	// initialize level
	void init(float screen_width, float screen_height, SaveData* savedata);

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

	// Draw level 
	void drawUI(GLHandler* mgl, UIAtlas* mAtlas);

<<<<<<< HEAD
	void loadLevelData();
	//Reads in the data from the file
=======
	// Returns current victory state
	bool getVictory();
>>>>>>> 0af97f7658e28190643faefd440dcbf1e3ee8c93
};

