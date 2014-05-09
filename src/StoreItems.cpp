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

	// Total number of ufo weapons 
	const int STORE_UFO_WEAPON_COUNT = 3;
	
	// Total number of player weapons 
	const int STORE_PLAYER_WEAPON_COUNT = 3;

	// Index numbers for store items 
	const int SID_PLAYER_WEAPON_LASER = 0;
	const int SID_PLAYER_WEAPON_SHOTGUN = 1;
	const int SID_PLAYER_WEAPON_SMG = 2;
	const int SID_UFO_WEAPON_MACHINE_GUN = 3;	// UFO machine gun 
	const int SID_UFO_WEAPON_MISSILE = 4;		// UFO missile launcher 
	const int SID_UFO_WEAPON_COWTAPOLT = 5;

	// Indexes of ufo weapons
	const int STORE_UFO_WEAPON_INDEXES[] = {
		SID_UFO_WEAPON_MACHINE_GUN, 
		SID_UFO_WEAPON_MISSILE,
		SID_UFO_WEAPON_COWTAPOLT
	};
	
	// Indexes of player weapons
	const int STORE_PLAYER_WEAPON_INDEXES[] = {
		SID_PLAYER_WEAPON_LASER,
		SID_PLAYER_WEAPON_SHOTGUN, 
		SID_PLAYER_WEAPON_SMG
	};

	// Call to create store items vector 
	void setupStoreItems(){
		sItems.push_back(StoreItem(SID_PLAYER_WEAPON_LASER,
			"Laser Gun",	"Standard issue pistol for all\nalien bears",
			0,0,"images/si/sii_laser.png"));
		sItems.push_back(StoreItem(SID_PLAYER_WEAPON_SHOTGUN,
			"Shotgun",		"Powerful ballistic weapon with\nspread for maximum \ndestruction",
			25,5,"images/si/sii_shotgun.png"));
		sItems.push_back(StoreItem(SID_PLAYER_WEAPON_SMG,
			"SMG",			"Best choice in alien small\narms fire",
			25,15,"images/si/sii_smg.png"));
		sItems.push_back(StoreItem(SID_UFO_WEAPON_MACHINE_GUN,
			"UFO Machine Gun","Rain down bullets upon \nyour enemies.",
			10,25,"images/si/sii_mini.png"));
		sItems.push_back(StoreItem(SID_UFO_WEAPON_MISSILE,
			"UFO Missiles",	"Explosive ship-mounted weapon.",
			0,40,"images/si/sii_rocket.png"));
		sItems.push_back(StoreItem(SID_UFO_WEAPON_COWTAPOLT,
			"UFO Cowtapolt",	"Launch Cows at your \nenemies",
			0,50,"images/si/sii_cow.png"));
	}
}