#pragma once
#include "Sprite.h"
#include "Ground.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Collision.h"
#include "UIAtlas.h"

class LevelEditor
{
	Sprite pointSprite;
	int pointIndex;
	int hightlightIndex;
	float shrinkSpeed;
	float maxPointDistance;

	bool enabled;

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

