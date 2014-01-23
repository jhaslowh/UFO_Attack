#pragma once
#include "Sprite.h"
#include "Ground.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Collision.h"
#include "UIAtlas.h"

class LevelEditor
{
	// Sprite to draw selected ground point
	Sprite pointSprite;
	// Speed to shrink and grow sprite 
	float shrinkSpeed;
	// Selected ground point index
	int pointIndex;
	// Point under mouse loc 
	int hightlightIndex;
	// Distance to select point
	float maxPointDistance;

	// Editor Toggle 
	bool enabled;

	std::string mouseLoc;

public:
	LevelEditor();
	~LevelEditor();

	// Load editor 
	void load();

	// Update editor state 
	void update(float deltaTime, Ground* ground);

	// Update editor input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Ground* ground);

	// Draw editor 
	void draw(GLHandler* mgl, UIAtlas* mUI);
};

