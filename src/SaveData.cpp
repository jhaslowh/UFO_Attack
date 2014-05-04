#include "SaveData.h"


SaveData::SaveData()
{
	purchasedItems = new bool[StoreItems::STORE_ITEM_COUNT];
	for (int i = 0; i < StoreItems::STORE_ITEM_COUNT; i++)
		purchasedItems[i] = false;
	purchasedItems[StoreItems::SID_PLAYER_WEAPON_LASER] = true;
	humanAbductCount = 0;
	animalAbductCount = 0;
	playerWeapon1 = 0;
	playerWeapon2 = -1;
	ufoWeapon1 = -1;
	ufoWeapon2 = -1;
	levelToLoad = "none";
	levelCount = 0;
	showTut = true;
}

SaveData::~SaveData()
{
	delete purchasedItems;
}

// Set the specificed item as purchased 
void SaveData::itemPurchsed(int index){
	purchasedItems[index] = true;
}
// Get the state of an item 
bool SaveData::isItemPurchased(int index){
	return purchasedItems[index];
}

// Set human abduct count 
void SaveData::setHumanAbductCount(int value){humanAbductCount = value;}
// Get human abduct count 
int SaveData::getHumanAbductCount(){return humanAbductCount;}
	
// Set Animal abduct count 
void SaveData::setAnimalAbductCount(int value){animalAbductCount = value;}
// Get Animal abduct count 
int SaveData::getAnimalAbductCount(){return animalAbductCount;}
	
// Set show tut 
void SaveData::setShowTut(bool value){showTut = value;}
// Get show tut
bool SaveData::getShowTut(){return showTut;}

// Player starting weapons
void SaveData::setPlayerWeapon1(int value){playerWeapon1 = value;}
int SaveData::getPlayerWeapon1(){return playerWeapon1;}
void SaveData::setPlayerWeapon2(int value){playerWeapon2 = value;}
int SaveData::getPlayerWeapon2(){return playerWeapon2;}

// Ufo starting weapons
void SaveData::setUFOWeapon1(int value){ufoWeapon1 = value;}
int SaveData::getUFOWeapon1(){return ufoWeapon1;}
void SaveData::setUFOWeapon2(int value){ufoWeapon2 = value;}
int SaveData::getUFOWeapon2(){return ufoWeapon2;}

// Change the abduction count of animals by the sent amout
void SaveData::incrAnimalCount(int value){animalAbductCount += value;}

// Change the abduction count of humans by the sent amout
void SaveData::incrHumanCount(int value){humanAbductCount += value;}

// Add level to list
void SaveData::addLevel(std::string name){
	if (!levelCompleted(name))
		levels.push_back(name);
}

// Check if level is in list
bool SaveData::levelCompleted(std::string name){
	for (std::list<std::string>::iterator it = levels.begin(); it != levels.end(); it++)
		if ((*it).compare(name) == 0)
			return true;
	return false;
}

// Clear level completed list
void SaveData::clearLevelList(){levels.clear();}

// Return string of all unlocked levels
std::string SaveData::levelsToString(){
	std::string levelString;
	for (std::list<std::string>::iterator it = levels.begin(); it != levels.end(); it++)
		levelString += " " + *it;
	return levelString;
}

// Check if all levels completed 
bool SaveData::allLevelsCompleted(){
	return levelCount == levels.size();
}

// Unlock all weapons
void SaveData::unlockAllWeapons(){
	for (int i = 0; i < StoreItems::STORE_ITEM_COUNT; i++)
		purchasedItems[i] = true;
}
