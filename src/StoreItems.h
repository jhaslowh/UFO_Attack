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

	// Total number of ufo weapons 
	extern const int STORE_UFO_WEAPON_COUNT;

	// Total number of player weapons 
	extern const int STORE_PLAYER_WEAPON_COUNT;

	// Index numbers for store items 
	extern const int SID_PLAYER_WEAPON_LASER;
	extern const int SID_PLAYER_WEAPON_SHOTGUN;
	extern const int SID_PLAYER_WEAPON_SMG;
	extern const int SID_UFO_WEAPON_MACHINE_GUN;	// UFO machine gun 
	extern const int SID_UFO_WEAPON_MISSILE;		// UFO missile launcher 
	extern const int SID_UFO_WEAPON_COWTAPOLT;

	// Indexes of ufo weapons
	extern const int STORE_UFO_WEAPON_INDEXES[];

	// Indexes of player weapons
	extern const int STORE_PLAYER_WEAPON_INDEXES[];

	// Call to create store items vector 
	void setupStoreItems();
}
