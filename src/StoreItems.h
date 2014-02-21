#pragma once
#include <string>
#include <vector>
#include "StoreItem.h"

//======================================================//
//
// This file contains all the information 
// for the store items of the game. 
//
//======================================================//

namespace StoreItems{

	// Vector list of all store items 
	extern std::vector<StoreItem> sItems;

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

	// Call to create store items vector 
	void setupStoreItems();
}
