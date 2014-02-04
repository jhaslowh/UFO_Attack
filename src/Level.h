#pragma once
#include "GLHandler.h"
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

class Level
{
	Player* player;
	Ground* ground;
	GameAtlas gameAtlas;
	SceneryHandler* sceneryHandler;
	Camera2D camera;
	LevelProperties levelProps;

	// States 
	bool loaded;

public:
	Handlers handlers;

	Level();
	~Level();

	// Grab Terrain List
	// Can also use level->handlers->ground;
	Ground* getGround();

	// Grab Current Player Object
	// Can also use level->handlers->player
	Player* getPlayer();

	// Grab levelproperties object
	// Can also use level->handlers->levelProps
	LevelProperties* getProperties();

	// initialize level
	void init(float screen_width, float screen_height);

	// Load level (use for textures)
	void load();

	// Update level state
	void update(float deltaTime);

	// Update the terrain list
	void updateTerrain(float newX, float newY);

	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw level 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);
};

