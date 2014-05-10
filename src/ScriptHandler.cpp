#include "ScriptHandler.h"
using namespace std;

ScriptHandler::ScriptHandler()
{
	isActive = false;
	numberOfScripts = 0;
}

ScriptHandler::ScriptHandler(Handlers* myHandlers, std::string scriptFile)
{
	isActive = false;
	numberOfScripts = 0;
	theHandles = myHandlers;
	//cout << "Script File: " << scriptFile << std::endl;
	std::string file = ".\\Levels\\";
	file.append(scriptFile);
	file.append("script.txt");
	//cout << "Script File: " << scriptFile << std::endl;
	ifstream myfile(file.c_str());
	if(myfile.is_open())
	{
		//cout << "Opened script file" << std::endl;
		std::string line;
		getline(myfile, line);
		numberOfScripts = (int)atoi(line.c_str());
		for(int i=0;i<numberOfScripts;i++)
		{
			getline(myfile, line);
			scriptList.push_back(new Script(theHandles, line));
			//cout << "I: " << i << std::endl;
		}
	}
	else
		cout << "Could not open script file " << std::endl;
}

ScriptHandler::~ScriptHandler()
{
	
}

void ScriptHandler::updateScripts(float deltaTime)
{
	for(int i=0;i<numberOfScripts;i++)
	{
		if(scriptList[i]->getIsActive())
		{
			scriptList[i]->updateScript(deltaTime);
			if(scriptList[i]->isScriptDone())
				scriptList[i]->executeScript();
		}
	}
}

void ScriptHandler::wasDeathOrAbduction(int whichOne)
{
	if(whichOne==1)
	{
		for(int i=0;i<numberOfScripts;i++)
		{
			if(scriptList[i]->getIsActive())
				scriptList[i]->npcDeath();
		}
	}
	else if(whichOne==2)
	{
		for(int i=0;i<numberOfScripts;i++)
		{
			if(scriptList[i]->getIsActive())
				scriptList[i]->npcAbduction();
		}
	}
}

bool ScriptHandler::getIsActive()
{
	return isActive;
}
