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
	const int STORE_ITEM_COUNT = 9;

	// Total number of ufo upgrades
	const int STORE_UFO_UPGRADE_COUNT = 2;

	// Total number of ufo weapons 
	const int STORE_UFO_WEAPON_COUNT = 4;
	
	// Total number of player weapons 
	const int STORE_PLAYER_WEAPON_COUNT = 3;

	// Index numbers for store items 
	const int SID_PLAYER_WEAPON_LASER = 0;
	const int SID_PLAYER_WEAPON_SHOTGUN = 1;
	const int SID_PLAYER_WEAPON_SMG = 2;
	const int SID_UFO_ARMOR_1 = 3;		// First ufo armor upgrade
	const int SID_UFO_ARMOR_2 = 4;		// Second ufo armor upgrade 
	const int SID_UFO_WEAPON_LASER = 5;	// UFO laser weapon 
	const int SID_UFO_WEAPON_MACHINE_GUN = 6;	// UFO machine gun 
	const int SID_UFO_WEAPON_MISSILE = 7;		// UFO missile launcher 
	const int SID_UFO_WEAPON_BOMB = 8;			// UFO bombs

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
	
	// Indexes of player weapons
	const int STORE_PLAYER_WEAPON_INDEXES[] = {
		SID_PLAYER_WEAPON_LASER,
		SID_PLAYER_WEAPON_SHOTGUN, 
		SID_PLAYER_WEAPON_SMG
	};

	// Call to create store items vector 
	void setupStoreItems(){
		sItems.push_back(StoreItem(SID_PLAYER_WEAPON_LASER,"Laser Gun","desc",0,0,"images/si/sii_laser.png"));
		sItems.push_back(StoreItem(SID_PLAYER_WEAPON_SHOTGUN,"Shotgun","desc",0,0,"images/si/sii_shotgun.png"));
		sItems.push_back(StoreItem(SID_PLAYER_WEAPON_SMG,"SMG","desc",0,0,"images/si/sii_smg.png"));
		sItems.push_back(StoreItem(SID_UFO_ARMOR_1,"UFO Armor 1","desc",0,0,"images/si/sii_todo.png"));
		sItems.push_back(StoreItem(SID_UFO_ARMOR_2,"UFO Armor 2","desc",0,0,"images/si/sii_todo.png"));
		sItems.push_back(StoreItem(SID_UFO_WEAPON_LASER,"UFO Laser","desc",0,0,"images/si/sii_todo.png"));
		sItems.push_back(StoreItem(SID_UFO_WEAPON_MACHINE_GUN,"UFO Machine Gun","desc",0,0,"images/si/sii_todo.png"));
		sItems.push_back(StoreItem(SID_UFO_WEAPON_MISSILE,"UFO Missiles","desc",0,0,"images/si/sii_todo.png"));
		sItems.push_back(StoreItem(SID_UFO_WEAPON_BOMB,"UFO Bombs","desc",0,0,"images/si/sii_todo.png"));
	}
}