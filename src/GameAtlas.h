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
#define GI_CRATE_LONG 20

class GameAtlas : public TextureAtlas
{
public:
	GameAtlas();
	virtual ~GameAtlas();

	// Set up the structure of this atlas.
	// Must be done in load method to work with texture. 
	void load();
};

