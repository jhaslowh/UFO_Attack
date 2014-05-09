#pragma once
#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Script.h"
#include "Handlers.h"

class ScriptHandler
{
protected:
	std::vector<Script*> scriptList;
	bool isActive;
	Handlers* theHandles;
	int numberOfScripts;
public:
	ScriptHandler();
	ScriptHandler(Handlers* myHandlers, std::string scriptFile);
	virtual ~ScriptHandler();

	void updateScripts(float deltaTime);
	void wasDeathOrAbduction(int whichOne);
	bool getIsActive();
};