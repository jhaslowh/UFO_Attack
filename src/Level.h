#pragma once
#include "GLHandler.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "TextureAtlas.h"
#include "Player.h"
#include "Ground.h"
#include "Handlers.h"
#include "GameAtlas.h"

class Level
{
	Player* player;
	Ground* ground;
	Handlers handlers;
	GameAtlas* gameAtlas;

public:
	Level();
	~Level();

	// Get reference to ground 
	Ground* getGround();

	// initialize level
	void init(float screen_width, float screen_height);

	// Load level (use for textures)
	void load(TextureAtlas* mAtlas);

	// Update level state
	void update(float deltaTime);

	// Update input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);

	// Draw level 
	void draw(GLHandler* mgl, TextureAtlas* mAtlas);
};

