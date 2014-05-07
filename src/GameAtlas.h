#pragma once
#include <string>
#include "TextureAtlas.h"
#include "VertCordGenerator.h"
#include "FileHelper.h"

// Game item id's
#define GI_TREE1 0
#define GI_SIGN 1
#define GI_HAY 2
#define GI_CRATE 3
#define GI_FENCE 4
#define GI_SKY 5
#define GI_SKY_GLOW 6
#define GI_PROJ 7
#define GI_PROJ_GLOW 8 
#define GI_NPC_SOLDIER_F1 9
#define GI_NPC_SOLDIER_F2 10
#define GI_NPC_SOLDIER_F3 11
#define GI_NPC_SOLDIER_M1 12
#define GI_NPC_SOLDIER_M2 13
#define GI_NPC_SOLDIER_M3 14
#define GI_NPC_SOLDIER_ARM 15
#define GI_NPC_HEALTH_BAR_OUTLINE 16
#define GI_NPC_HEALTH_BAR 17
#define GI_NPC_SMG 18
#define GI_NPC_SMG_FLASH 19
#define GI_NPC_SNIPER 20
#define GI_NPC_STINGER 21
#define GI_CRATE_LONG 22
#define GI_NPC_COW_1 23
#define GI_NPC_COW_2 24
#define GI_MISSILE 25
#define GI_BASIC_EXPL_1 26
#define GI_BASIC_EXPL_2 27
#define GI_BASIC_EXPL_3 28
#define GI_BASIC_EXPL_4 29
#define GI_SPHERE 30
#define GI_SMOKE1 31
#define GI_SMOKE2 32
#define GI_SMOKE3 33
#define GI_SMOKE4 34
#define GI_SMOKE5 35
#define GI_NPC_HSOLDIER1 36
#define GI_NPC_HSOLDIER2 37
#define GI_NPC_HSOLDIER3 38
#define GI_NPC_HSOLDIER_ARM 39
#define GI_TANK 40
#define GI_TANK_BARREL 41 
#define GI_SPLAT1 42
#define GI_SPLAT2 43
#define GI_SPLAT3 44
#define GI_HOUSE_BLUE 45
#define GI_HOUSE_BROWN 46
#define GI_BARN 47
#define GI_TURRET_BASE 48
#define GI_SAM 49
#define GI_MACHINE_GUN 50

// Civilians 
#define GI_CIVI_MALE1_1 51
#define GI_CIVI_MALE1_2 52
#define GI_CIVI_MALE1_3 53
#define GI_CIVI_MALE1a_1 54
#define GI_CIVI_MALE1a_2 55
#define GI_CIVI_MALE1a_3 56

#define GI_CIVI_MALE2_1 57
#define GI_CIVI_MALE2_2 58
#define GI_CIVI_MALE2_3 59
#define GI_CIVI_MALE2a_1 60
#define GI_CIVI_MALE2a_2 61
#define GI_CIVI_MALE2a_3 62

#define GI_CIVI_FEMALE1_1 63
#define GI_CIVI_FEMALE1_2 64
#define GI_CIVI_FEMALE1_3 65
#define GI_CIVI_FEMALE1a_1 66
#define GI_CIVI_FEMALE1a_2 67
#define GI_CIVI_FEMALE1a_3 68

#define GI_CIVI_FEMALE2_1 69
#define GI_CIVI_FEMALE2_2 70
#define GI_CIVI_FEMALE2_3 71
#define GI_CIVI_FEMALE2a_1 72
#define GI_CIVI_FEMALE2a_2 73
#define GI_CIVI_FEMALE2a_3 74

#define GI_BARRACKS 75

class GameAtlas : public TextureAtlas
{
public:
	GameAtlas();
	virtual ~GameAtlas();

	// Set up the structure of this atlas.
	// Must be done in load method to work with texture. 
	void load();
};

