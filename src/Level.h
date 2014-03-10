#pragma once
#include "GLColors.h"
#include "GLHandler.h"
#include "FileHelper.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "TextureAtlas.h"
#include "Player.h"
#include "Ground.h"
#include "Handlers.h"
#include "GameAtlas.h"
#include "SceneryHandler.h"
#include "Tree.h"
#include "Camera2D.h"
#include "LevelProperties.h"
#include "ProjectileHandler.h"
#include "Sky.h"

class Level
{
	Player* player;
	Ground* ground;
	GameAtlas gameAtlas;
	SceneryHandler* sceneryHandler;
	ProjectileHandler* projHandler;
	Camera2D camera;
	LevelProperties levelProps;
	Sky sky;

	// States 
	bool loaded;

public:
	Handlers handlers;

	Level();
	~Level();

	// initialize level
	void init(float screen_width, float screen_height);

	// Load level (use for textures)
	void load(GLHandler* mgl);

	// Unload level
	void unload();

	// Update level state
	void update(float deltaTime);

	// Update the terrain list
	void updateTerrain(float newX, float newY);

	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw level 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Draw level 
	void drawUI(GLHandler* mgl, UIAtlas* mAtlas);
};

