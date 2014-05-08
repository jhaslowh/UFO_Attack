#include "Script.h"
using namespace std;

Script::Script()
{
	scriptType = 0;
	scriptCompareValue = 0;
	scriptCurrentValue = 0;
	isActive = false;
}

Script::Script(Handlers* myHandlers, std::string scriptString)
{
	isActive = true;
	isScriptComplete = false;
	cout << "Enter script start" << std::endl;
	myHandles = myHandlers;
	size_t pos = 0;
	std::string delimiter = ".";
	int counter = 0;
	while ((pos = scriptString.find(delimiter)) != std::string::npos) 
	{
		scriptStorage[counter] = scriptString.substr(0, pos);
		scriptString.erase(0, pos + delimiter.length());
		counter++;
	}			
	scriptStorage[counter] = scriptString;
	cout << "im here " << std::endl;
	if(scriptStorage[0]=="abductions")
	{
		cout << "hi";
		scriptType = ABDUCTION_CONTROL;
		scriptCurrentValue = 0;
	}
	else if(scriptStorage[0]=="time")
	{
		cout << "start time " << std::endl;
		scriptType = TIME_CONTROL;
		cout << "finished time control else if" << std::endl;
	}
	else if(scriptStorage[0]=="death")
	{
		cout << "death";
		scriptType = DEATH_CONTROL;
		scriptCompareValue = 0;
		scriptCurrentValue = 0;
	}
	else if(scriptStorage[0]=="distance")
	{
		cout << "distance";
		scriptCompareValue = 0;
		scriptType = DISTANCE_CONTROL;
	}
	else
		cout << "Nothing mate" << std::endl;
	cout << "Finished script make " << std::endl;
	/*for(int i=0;i<7;i++)
	{
		cout << scriptStorage[i] << " ";
	}
	cout << " " << std::endl;*/
}

Script::~Script(){

}

void Script::updateScript(float deltaTime)
{
	if(scriptType==TIME_CONTROL)
	{
		scriptCurrentValue += deltaTime;
		if(scriptCurrentValue>=(float)atoi(scriptStorage[1].c_str()))
			isScriptComplete = true;
	}
	else if(scriptType==DEATH_CONTROL)
	{
		if(scriptCompareValue==0)
		{
			scriptCompareValue = ((NPCHandler*)myHandles->npcHandler)->getAliveCount();
			cout << ((NPCHandler*)myHandles->npcHandler)->getAliveCount();
		}
		else
		{
			cout << "Script Value: " << scriptCurrentValue << std::endl;
			cout << "Compare Value: " << scriptCompareValue << std::endl;
			cout << "Goal: " << (float)atoi(scriptStorage[1].c_str()) << std::endl;
			int tempValue = ((NPCHandler*)myHandles->npcHandler)->getAliveCount();
			scriptCurrentValue += (scriptCompareValue - tempValue);
			scriptCompareValue = ((NPCHandler*)myHandles->npcHandler)->getAliveCount();
			if(scriptCurrentValue>=(float)atoi(scriptStorage[1].c_str()))
				isScriptComplete = true;
		}
	}
	else if(scriptType==DISTANCE_CONTROL)
	{
		scriptCurrentValue = ((Player*)(myHandles->player))->getX();
		if((float)atoi(scriptStorage[1].c_str())>=(scriptCurrentValue-scriptCompareValue))
			isScriptComplete = true;
	}
	else if(scriptType==ABDUCTION_CONTROL)
	{

	}
}

void Script::executeScript()
{
	if(scriptStorage[2]=="spawnScenery")
	{
		if(scriptStorage[3]=="sign")
		{
			((SceneryHandler*)(myHandles->sceneryHandler))->add("sign",scriptStorage[6],(float)atoi(scriptStorage[4].c_str()),(float)atoi(scriptStorage[5].c_str()));
		}
		else
		{
			((SceneryHandler*)(myHandles->sceneryHandler))->add(scriptStorage[3],std::string(""),(float)atoi(scriptStorage[4].c_str()),(float)atoi(scriptStorage[5].c_str()));
		}
	}
	else if(scriptStorage[2]=="spawnNPC")
	{
		((NPCHandler*)(myHandles->npcHandler))->addByName(scriptStorage[3], (float)atoi(scriptStorage[4].c_str()),(float)atoi(scriptStorage[5].c_str()));
	}
	else if(scriptStorage[2]=="damagePlayer")
	{
		((Player*)(myHandles->player))->applyDamage((float)atoi(scriptStorage[3].c_str()));
	}
	isActive = false;
}

bool Script::isScriptDone()
{
	return isScriptComplete;
}

bool Script::getIsActive()
{
	return isActive;
}