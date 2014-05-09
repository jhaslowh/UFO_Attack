#pragma once
#include <math.h>
#include <string>
#include <vector>
#include "Handlers.h"
#include "Player.h"
#include "NPCHandler.h"
#include "SceneryHandler.h"
#include "LevelProperties.h"

#define TIME_CONTROL 1
#define DEATH_CONTROL 2
#define DISTANCE_CONTROL 3
#define ABDUCTION_CONTROL 4

class Script
{
protected:
	short scriptType;
	float scriptCompareValue;
	float scriptCurrentValue;
	std::string scriptStorage[7];
	bool isScriptComplete;
	Handlers* myHandles;
	bool isActive;
public:
	Script();
	Script(Handlers* myHandlers, std::string scriptString);
	virtual ~Script();

	void updateScript(float deltaTime);
	void executeScript();
	void npcDeath();
	void npcAbduction();

	bool isScriptDone();
	bool getIsActive();
};