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
	GameAtlas* gameAtlas;
	SceneryHandler* sceneryHandler;
	Camera2D camera;
	LevelProperties levelProps;

public:
	Handlers handlers;

	Level();
	~Level();

	// initialize level
	void init(float screen_width, float screen_height);

	// Load level (use for textures)
	void load();

	// Update level state
	void update(float deltaTime);

	// Update the terrain list
	void updateTerrain(float newX, float newY);

	// Grab Terrain List
	Ground* getGround();

	// Grab Current Player Object
	Player* getPlayer();

	// Grab levelproperties object
	LevelProperties* getProperties();

	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw level 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);
};

