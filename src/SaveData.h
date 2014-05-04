#pragma once
#include <list>
#include "StoreItems.h"

class SaveData
{

	// Bool of all purchased items 
	bool* purchasedItems;
	// Number of abducted humans 
	int humanAbductCount;
	// Number of abducted animals
	int animalAbductCount;
	// Show tutorial 
	bool showTut;

	// Starting weapons
	int playerWeapon1;
	int playerWeapon2;
	int ufoWeapon1;
	int ufoWeapon2;

	// Completed levels
	std::list<std::string> levels;

public:
	// Used to tell the game screen what to load
	std::string levelToLoad;
	// Used to check how many levels there are. 
	// Shouldn't be saved, just set each time the list of levels
	// is loaded for reference. 
	int levelCount;

	SaveData();
	~SaveData();

	// Set the specificed item as purchased 
	void itemPurchsed(int index);
	// Get the state of an item 
	bool isItemPurchased(int index);

	// Set human abduct count 
	void setHumanAbductCount(int value);
	// Get human abduct count 
	int getHumanAbductCount();
	
	// Set Animal abduct count 
	void setAnimalAbductCount(int value);
	// Get Animal abduct count 
	int getAnimalAbductCount();

	// Set show tut 
	void setShowTut(bool value);
	// Get show tut
	bool getShowTut();
	
	// Player starting weapons
	void setPlayerWeapon1(int value);
	int getPlayerWeapon1();
	void setPlayerWeapon2(int value);
	int getPlayerWeapon2();

	// Ufo starting weapons
	void setUFOWeapon1(int value);
	int getUFOWeapon1();
	void setUFOWeapon2(int value);
	int getUFOWeapon2();

	// Change the abduction count of animals by the sent amout
	void incrAnimalCount(int value);
	// Change the abduction count of humans by the sent amout
	void incrHumanCount(int value);

	// Add level to list
	void addLevel(std::string name);
	// Check if level is in list
	bool levelCompleted(std::string name);
	// Clear level completed list
	void clearLevelList();
	// Return string of all unlocked levels
	std::string levelsToString();

	// Check if all levels completed 
	bool allLevelsCompleted();

	// Unlock all weapons
	void unlockAllWeapons();
};

