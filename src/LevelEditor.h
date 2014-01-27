#pragma once
#include "Sprite.h"
#include "Handlers.h"
#include "SceneryHandler.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Collision.h"
#include "UIAtlas.h"
#include "UIButton.h"
#include "UITerminal.h"
#include "LevelCamera.h"

// Level editor states
#define LES_NONE 0
#define LES_MOVE_POINT 1
#define LES_ADD_POINT 2
#define LES_REMOVE_POINT 3
#define LES_SCENERY 4
#define LES_REMOVE_SCENERY 5
#define LES_MOVE_CAMERA 6

class LevelEditor
{
	// -------------------- //
	// Ground Point Editing //
	// -------------------- //
	// Sprite to draw selected ground point
	Sprite pointSprite;
	// Speed to shrink and grow sprite 
	float shrinkSpeed;
	// Selected ground point 
	Point* selectedPoint;
	// Point under mouse loc 
	bool pointHighlighted;
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
	
	// ------ //
	// States //
	// ------ //
	// Editor Toggle 
	bool enabled;
	// Current state 
	int state;
	
	// Buttons
	UIButton* bMove;
	UIButton* bAdd;
	UIButton* bRemove;
	UIButton* bRemoveS;
	UITerminal* tTerminal;

	string mouseLoc;
	string stateString;

	// Level location
	float levelX, levelY;
	Point levelLoc;

	// Mouse locations 
	Point lastMouse;

public:
	LevelEditor();
	~LevelEditor();

	// Check if turned on
	bool Enabled();

	// Setup basic structures 
	void init(float screen_width, float screen_height);

	// Load editor 
	void load(TextureAtlas* mAtlas);

	// Update editor state 
	void update(float deltaTime, Ground* ground);

	// Update editor input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw editor 
	void draw(GLHandler* mgl, UIAtlas* mUI);

	// Show editor elements
	void show();

	// Hide editor elements
	void hide();
};

