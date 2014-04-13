#pragma once
#include <iostream>
#include <fstream>

#include "Sprite.h"
#include "Handlers.h"
#include "SceneryHandler.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "Collision.h"
#include "UIAtlas.h"
#include "UIButton.h"
#include "UITerminal.h"
#include "Camera2D.h"
#include "LevelProperties.h"
#include "Tree.h"
#include "Sign.h"
#include "HayBale.h"
#include "AtlasSprite.h"
#include "Crate.h"
#include "Fence.h"
#include "LongCrate.h"
#include "TallCrate.h"
#include "GLColors.h"
#include "NPC.h"
#include "NPCHandler.h"
#include "LevelIO.h"

// Level editor states
#define LES_NONE 0
#define LES_MOVE_POINT 1
#define LES_ADD_POINT 2
#define LES_REMOVE_POINT 3
#define LES_SCENERY 4
#define LES_REMOVE_SCENERY 5
#define LES_LB_LEFT 6
#define LES_LB_RIGHT 7

class LevelEditor
{
	// -------------------- //
	// Ground Point Editing //
	// -------------------- //
	// Sprite to draw selected ground point
	AtlasSprite pointSprite;
	GLfloat pointColor[4];
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
	// Reference to selected scenery object 
	SceneryObject* scObj;
	
	// ---------------------- //
	// Level Editor Moving    //
	// ---------------------  //
	// Sprites for level bounds 
	AtlasSprite levelLeft;
	AtlasSprite levelRight;
	// Distance to select bound
	float boundDistance;

	// ------ //
	// States //
	// ------ //
	// Editor Toggle 
	bool enabled;
	// Current state 
	int state;
	// Current string of level editor state 
	std::string stateString;
	// Moving camera 
	bool movingCamera;
	
	// ------ //
	//   UI   //
	// ------ //
	// Buttons
	UIButton* bMove;
	UIButton* bAdd;
	UIButton* bRemove;
	UIButton* bRemoveS;

	float screenWidth;
	float screenHeight;

	// ---------- //
	// Mouse info 
	// ---------- // 

	// Locations 
	float levelX, levelY;
	Point levelLoc;
	std::string mouseLoc;
	Point lastMouse;

	// Mouse offset for selecting objects 
	float mouseOffsetX; 
	float mouseOffsetY;

	// Zooming
	float zoomPerScroll;

	// ---------------- // 
	//    Handlers      // 
	// ---------------- // 
	Camera2D* camera;
	SceneryHandler* sceneryHandler;
	LevelProperties* levelProps;
	Ground* ground;
	Handlers* handlers;
	NPCHandler* npcHandler;

public:
	LevelEditor();
	~LevelEditor();

	// Set handlers for editor 
	void setHandlers(Handlers* handlers);

	// Check if turned on
	bool Enabled();

	// Setup basic structures 
	void init(float screen_width, float screen_height);

	// Load editor 
	void load(TextureAtlas* mAtlas);

	// Update editor state 
	void update(float deltaTime, Handlers* handlers);

	// Update editor input
	void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers);

	// Draw editor 
	void draw(GLHandler* mgl, UIAtlas* mUI);

	// Parse a command give
	bool parseCommand(UITerminal* terminal, std::string command, std::string args);

	// Show editor elements
	void show();

	// Hide editor elements
	void hide();
};

