#include "TutorialSystem.h"


TutorialSystem::TutorialSystem()
{
	// Current tutorial stage 
	currentStage = TSTAGE_NONE;

	// Set to lock the level 
	lock = false;

	// This is a pause between two tut stages
	pause = false;
	pauseTime = 2.0f;
	cpauseTime = 0.0f;

	savedata = NULL;
}

TutorialSystem::~TutorialSystem()
{

}

// Get tutorial lock 
bool TutorialSystem::getLock(){
	return lock;
}

// Call this to disable tuts on load 
void TutorialSystem::setTutsShown(){
	lock = false;
	currentStage = TSTAGE_DONE;
}

// Initialize tutorial system
void TutorialSystem::init(float screen_width, float screen_height, SaveData* sd){
	savedata = sd;

	// Stay locked if tuts completed 
	if (sd->getShowTut()){
		currentStage = TSTAGE_HEALTH;
		lock = true; 

		// Create health box 
		boxes[TSTAGE_HEALTH].setText("Current UFO armor and shields.\nPlayer health and UFO energy.");
		boxes[TSTAGE_HEALTH].setSize(220.0f, 36.0f);
		boxes[TSTAGE_HEALTH].setLocation(10.0f, 80.0f);
		boxes[TSTAGE_HEALTH].turnOnTutArrow(TA_TOP_LEFT);

		// Create abduct A count box 
		boxes[TSTAGE_ABDUCT_COUNT_A].setText("Current abduction count\nfor animals.");
		boxes[TSTAGE_ABDUCT_COUNT_A].setSize(170.0f, 36.0f);
		boxes[TSTAGE_ABDUCT_COUNT_A].setLocation(180.0f, 50.0f);
		boxes[TSTAGE_ABDUCT_COUNT_A].turnOnTutArrow(TA_TOP_LEFT);

		// Create abduct  H count box 
		boxes[TSTAGE_ABDUCT_COUNT_H].setText("Current abduction count\nfor humans.");
		boxes[TSTAGE_ABDUCT_COUNT_H].setSize(170.0f, 36.0f);
		boxes[TSTAGE_ABDUCT_COUNT_H].setLocation(240.0f, 50.0f);
		boxes[TSTAGE_ABDUCT_COUNT_H].turnOnTutArrow(TA_TOP_LEFT);

		// Create enemy count box 
		boxes[TSTAGE_ENEMY_COUNT].setText("Current enemy population in level.\nGet the red meter to go below\nthe green for Victory.");
		boxes[TSTAGE_ENEMY_COUNT].setSize(232.0f, 48.0f);
		boxes[TSTAGE_ENEMY_COUNT].setLocation(screen_width*.5f-116.0f, 68.0f);
		boxes[TSTAGE_ENEMY_COUNT].turnOnTutArrow(TA_TOP_MIDDLE);

		// Create ammo box 
		boxes[TSTAGE_AMMO].setText("Current weapon ammo\nPress R to manually reload");
		boxes[TSTAGE_AMMO].setSize(190.0f, 36.0f);
		boxes[TSTAGE_AMMO].setLocation(screen_width-290.0f, 5.0f);
		boxes[TSTAGE_AMMO].turnOnTutArrow(TA_RIGHT_TOP);

		// Create movement box 
		boxes[TSTAGE_MOVE].setText("Use W A S D to move the UFO\nand the player.");
		boxes[TSTAGE_MOVE].setSize(214.0f, 35.0f);
		boxes[TSTAGE_MOVE].setLocation(screen_width*.1f, screen_height*.5f-17.0f);
		boxes[TSTAGE_MOVE].turnOnTutArrow(TA_RIGHT_TOP);

		// Create abduct ray box 
		boxes[TSTAGE_ABDUCT_RAY].setText(
			"Press E while in the UFO to\n"
			"activate the abduction ray.\n"
			"The green bar at the top left\n"
			"is the current amount of\n"
			"energy left for the ray.");
		boxes[TSTAGE_ABDUCT_RAY].setSize(200.0f, 75.0f);
		boxes[TSTAGE_ABDUCT_RAY].setLocation(screen_width*.1f, screen_height*.5f-35.0f);
		boxes[TSTAGE_ABDUCT_RAY].turnOnTutArrow(TA_RIGHT_TOP);

		// Create switch box 
		boxes[TSTAGE_SWITCHING].setText(
			"Press Q while in the UFO to\n"
			"drop out. \n"
			"Press Q while on foot and\n"
			"close to the ship to get back\n"
			"into the ship.");
		boxes[TSTAGE_SWITCHING].setSize(200.0f, 75.0f);
		boxes[TSTAGE_SWITCHING].setLocation(screen_width*.1f, screen_height*.5f-35.0f);
		boxes[TSTAGE_SWITCHING].turnOnTutArrow(TA_RIGHT_TOP);

		// Create shooting box 
		boxes[TSTAGE_SHOOTING].setText(
			"Left click anywhere on the\n"
			"screen to fire your weapon.");
		boxes[TSTAGE_SHOOTING].setSize(195.0f, 35.0f);
		boxes[TSTAGE_SHOOTING].setLocation(screen_width*.1f, screen_height*.5f-17.0f);
		boxes[TSTAGE_SHOOTING].turnOnTutArrow(TA_RIGHT_TOP);
	}
}

// update tutorial system state
void TutorialSystem::update(float deltaTime, Handlers* handlers){

	// TODO show enemy tuts 

	// Update pause 
	if (pause){
		cpauseTime += deltaTime;
		if (cpauseTime >= pauseTime){
			cpauseTime = 0.0f;
			pause = false;
		}
	}
}

// Update input to the screen 
void TutorialSystem::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH, Handlers* handlers){
	
	// TODO show enemy tuts 

	// Return if finished 
	if (currentStage == TSTAGE_DONE || currentStage == TSTAGE_NONE || pause)
		return;

	// Update input states 
	switch (currentStage){
	case TSTAGE_HEALTH:
		if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
			currentStage = TSTAGE_ABDUCT_COUNT_A;
		break;
	case TSTAGE_ABDUCT_COUNT_A:
		if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
			currentStage = TSTAGE_ABDUCT_COUNT_H;
		break;
	case TSTAGE_ABDUCT_COUNT_H:
		if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
			currentStage = TSTAGE_ENEMY_COUNT;
		break;
	case TSTAGE_ENEMY_COUNT:
		if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
			currentStage = TSTAGE_AMMO;
		break;
	case TSTAGE_AMMO:
		if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
			currentStage = TSTAGE_MOVE;
			lock = false;
		}
		break;
	case TSTAGE_MOVE:
		if (mKeyH->keyDown(KEY_W) || mKeyH->keyDown(KEY_A) ||
			mKeyH->keyDown(KEY_S) || mKeyH->keyDown(KEY_D)){
			currentStage = TSTAGE_ABDUCT_RAY;
			pause = true;
		}
	case TSTAGE_ABDUCT_RAY:
		if (mKeyH->keyDown(KEY_E) && ((Player*)handlers->player)->isInUFO()){
			currentStage = TSTAGE_SWITCHING;
			pause = true;
		}
		break;
	case TSTAGE_SWITCHING:
		if (mKeyH->keyDown(KEY_Q)){
			currentStage = TSTAGE_SHOOTING;
			pause = true;
		}
		break;
	case TSTAGE_SHOOTING:
		if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
			currentStage = TSTAGE_DONE;
			savedata->setShowTut(false);
		}
		break;
	default:
		break;
	}
}

// Draw the screen
void TutorialSystem::draw(GLHandler* mgl, UIAtlas* mAtlas){
	// Return if finished 
	if (currentStage == TSTAGE_DONE || currentStage == TSTAGE_NONE || pause)
		return;

	boxes[currentStage].draw(mgl, mAtlas);
}
