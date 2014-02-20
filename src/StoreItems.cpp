#include "StoreItems.h"

//========================================//
//
// This file contains all the information 
// for the store items of the game. 
//
//========================================//

namespace StoreItems{

	// Total number of store items 
	const int STORE_ITEM_COUNT = 6;

	// Total number of ufo upgrades
	const int STORE_UFO_UPGRADE_COUNT = 2;

	// Total number of ufo weapons 
	const int STORE_UFO_WEAPON_COUNT = 4;

	// Index numbers for store items 
	const int SID_UFO_ARMOR_1 = 0;		// First ufo armor upgrade
	const int SID_UFO_ARMOR_2 = 1;		// Second ufo armor upgrade 
	const int SID_UFO_WEAPON_LASER = 2;	// UFO laser weapon 
	const int SID_UFO_WEAPON_MACHINE_GUN = 3;	// UFO machine gun 
	const int SID_UFO_WEAPON_MISSILE = 4;		// UFO missile launcher 
	const int SID_UFO_WEAPON_BOMB = 5;			// UFO bombs

	// Indexes of ufo upgrades
	const int STORE_UFO_UPGRADE_INDEXES[] = {
		SID_UFO_ARMOR_1,
		SID_UFO_ARMOR_2
	};

	// Indexes of ufo weapons
	const int STORE_UFO_WEAPON_INDEXES[] = {
		SID_UFO_WEAPON_LASER,
		SID_UFO_WEAPON_MACHINE_GUN, 
		SID_UFO_WEAPON_MISSILE,
		SID_UFO_WEAPON_BOMB
	};

	// Store Item names 
	const std::string SI_NAMES[] = {
		"UFO Armor 1", 
		"UFO Armor 2", 
		"UFO Laser",
		"UFO Machine Gun",
		"UFO Missiles",
		"UFO Bombs"
	};

	// Store Item discriptions 
	const std::string SI_DESCRIPTIONS[] = {
		"Temp Description",					// Description for UFO Armor 1
		"Temp Description",					// Description for UFO Armor 2
		"Temp Description",					// Description for UFO Laser
		"Temp Description",					// Description for UFO Machine Gun
		"Temp Description",					// Description for UFO Missiles
		"Temp Description"					// Description for UFO Bombs
	};

	
	// Store Item animal price
	const int STORE_ANIMAL_COST[] = {
		0,								// Cost for UFO Armor 1
		0,								// Cost for UFO Armor 2
		0,								// Cost for UFO Laser
		0,								// Cost for UFO Machine Gun
		0,								// Cost for UFO Missiles
		0								// Cost for UFO Bombs
	};

	// Store Item human cost
	const int STORE_HUMAN_COST[] = {
		0,								// Cost for UFO Armor 1
		0,								// Cost for UFO Armor 2
		0,								// Cost for UFO Laser
		0,								// Cost for UFO Machine Gun
		0,								// Cost for UFO Missiles
		0								// Cost for UFO Bombs
	};


	// -----------------------------------------------//
	//
	// The following methods can be used to retreive 
	// custom arrays of store information. 
	//
	// -----------------------------------------------//

	// Returns a string array of all ufo upgrade names 
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoUpgradeNames(){
		std::string* s = new std::string[STORE_UFO_UPGRADE_COUNT];
		for (int i = 0; i < STORE_UFO_UPGRADE_COUNT; i++){
			s[i] = SI_NAMES[STORE_UFO_UPGRADE_INDEXES[i]];
		}
		return s;
	}

	// Returns a string array of all ufo weapon names 
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoWeaponNames(){
		std::string* s = new std::string[STORE_UFO_WEAPON_COUNT];
		for (int i = 0; i < STORE_UFO_WEAPON_COUNT; i++){
			s[i] = SI_NAMES[STORE_UFO_WEAPON_INDEXES[i]];
		}
		return s;
	}

	// Returns a string array of all ufo upgrade descriptions
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoUpgradeDescriptions(){
		std::string* s = new std::string[STORE_UFO_UPGRADE_COUNT];
		for (int i = 0; i < STORE_UFO_UPGRADE_COUNT; i++){
			s[i] = SI_DESCRIPTIONS[STORE_UFO_UPGRADE_INDEXES[i]];
		}
		return s;
	}

	// Returns a string array of all ufo weapon descriptions 
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoWeaponDescriptions(){
		std::string* s = new std::string[STORE_UFO_WEAPON_COUNT];
		for (int i = 0; i < STORE_UFO_WEAPON_COUNT; i++){
			s[i] = SI_DESCRIPTIONS[STORE_UFO_WEAPON_INDEXES[i]];
		}
		return s;
	}
}