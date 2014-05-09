#pragma once
#include "Handlers.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "GLHandler.h"
#include "UIAtlas.h"
#include "TutBox.h"
#include "Player.h"
#include "SaveData.h"

#define TSTAGE_NONE -1
#define TSTAGE_HEALTH 0
#define TSTAGE_ABDUCT_COUNT_A 1
#define TSTAGE_ABDUCT_COUNT_H 2
#define TSTAGE_ENEMY_COUNT 3
#define TSTAGE_AMMO 4
#define TSTAGE_MOVE 5
#define TSTAGE_ABDUCT_RAY 6
#define TSTAGE_SWITCHING 7
#define TSTAGE_SHOOTING 8
#define TSTAGE_DONE 9

class TutorialSystem
{
	SaveData* savedata;

	// Current tutorial stage 
	int currentStage;

	// Set to lock the level 
	bool lock;

	// Tutorial boxes
	TutBox boxes[TSTAGE_DONE];

	// This is a pause between two tut stages
	bool pause;
	float pauseTime;
	float cpauseTime;

public:
	TutorialSystem();
	~TutorialSystem();

	// Get tutorial lock 
	bool getLock();

	// Call this to disable tuts on load 
	void setTutsShown();

	// Initialize tutorial system
	void init(float screen_width, float screen_height, SaveData* sd);

	// update tutorial system state
	void update(float deltaTime, Handlers* handlers);

	// Update input to the screen 
	void updateInput(KeyHandler*, MouseHandler*, Handlers* handlers);

	// Draw the screen
	void draw(GLHandler* mgl, UIAtlas* mAtlas);
};

