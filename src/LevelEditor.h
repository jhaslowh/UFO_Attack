#pragma once
#include "Sprite.h"
#include "Handlers.h"
#include "SceneryHandler.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Collision.h"
#include "UIAtlas.h"

// Level editor states
#define LES_NONE 0
#define LES_POINT 1
#define LES_SCENERY 2

class LevelEditor
{
	// -------------------- //
	// Ground Point Editing //
	// -------------------- //
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

	// ---------------------- //
	// Scenery Object Editing //
	// ---------------------  //
	// Offset x and y of scenery object 
	float sceneryOffsetX;
	float sceneryOffsetY;
	// Reference to selected scenery object 
	SceneryObject* scObj;

	// Editor Toggle 
	bool enabled;
	// Current state 
	int state;

	std::string mouseLoc;

public:
	LevelEditor();
	~LevelEditor();

	// Load editor 
	void load();

	// Update editor state 
	void update(float deltaTime, Ground* ground);

	// Update editor input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw editor 
	void draw(GLHandler* mgl, UIAtlas* mUI);
};

