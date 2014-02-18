#pragma once
#include <string>

//======================================================//
//
// This file contains all the information 
// for the store items of the game. 
//
//======================================================//

namespace StoreItems{

	// Total number of store items 
	extern const int STORE_ITEM_COUNT;

	// Total number of ufo upgrades
	extern const int STORE_UFO_UPGRADE_COUNT;

	// Total number of ufo weapons 
	extern const int STORE_UFO_WEAPON_COUNT;

	// Index numbers for store items 
	extern const int SID_UFO_ARMOR_1;		// First ufo armor upgrade
	extern const int SID_UFO_ARMOR_2;		// Second ufo armor upgrade 
	extern const int SID_UFO_WEAPON_LASER;	// UFO laser weapon 
	extern const int SID_UFO_WEAPON_MACHINE_GUN;	// UFO machine gun 
	extern const int SID_UFO_WEAPON_MISSILE;		// UFO missile launcher 
	extern const int SID_UFO_WEAPON_BOMB;			// UFO bombs

	// Indexes of ufo upgrades
	extern const int STORE_UFO_UPGRADE_INDEXES[];

	// Indexes of ufo weapons
	extern const int STORE_UFO_WEAPON_INDEXES[];

	// Store Item names 
	extern const std::string SI_NAMES[];

	// Store Item discriptions 
	extern const std::string SI_DESCRIPTIONS[];

	// Store Item animal price
	extern const int STORE_ANIMAL_COST[];

	// Store Item human cost
	extern const int STORE_HUMAN_COST[];

	// -----------------------------------------------//
	//
	// The following methods can be used to retreive 
	// custom arrays of store information. 
	//
	// -----------------------------------------------//

	// Returns a string array of all ufo upgrade names 
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoUpgradeNames();

	// Returns a string array of all ufo weapon names 
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoWeaponNames();

	// Returns a string array of all ufo upgrade descriptions
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoUpgradeDescriptions();

	// Returns a string array of all ufo weapon descriptions 
	// Note: The returned pointer must be deleted with delete[]
	std::string* getUfoWeaponDescriptions();

}
