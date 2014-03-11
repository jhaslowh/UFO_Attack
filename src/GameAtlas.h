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
#define GI_PROJ_RED 7
#define GI_PROJ_RED_GLOW 8 

class GameAtlas : public TextureAtlas
{
public:
	GameAtlas();
	virtual ~GameAtlas();

	// Set up the structure of this atlas.
	// Must be done in load method to work with texture. 
	void load();
};

