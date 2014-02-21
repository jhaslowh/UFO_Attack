#include "StoreItems.h"

//========================================//
//
// This file contains all the information 
// for the store items of the game. 
//
//========================================//

namespace StoreItems{
	
	// Vector list of all store items 
	std::vector<StoreItem> sItems;

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
	
	// Call to create store items vector 
	void setupStoreItems(){
		sItems.push_back(StoreItem(0,"UFO Armor 1","desc",0,0));
		sItems.push_back(StoreItem(1,"UFO Armor 2","desc",0,0));
		sItems.push_back(StoreItem(2,"UFO Laser","desc",0,0));
		sItems.push_back(StoreItem(3,"UFO Machine Gun","desc",0,0));
		sItems.push_back(StoreItem(4,"UFO Missiles","desc",0,0));
		sItems.push_back(StoreItem(5,"UFO Bombs","desc",0,0));
	}
}