#pragma once
#include "TextureAtlas.h"
#include "FileHelper.h"
#include "VertCordGenerator.h"

// Palyer ID's
#define PLAYER_RUN_FRAME0 0
#define PLAYER_RUN_FRAME1 1
#define PLAYER_RUN_FRAME2 2
#define PLAYER_RUN_FRAME3 3
#define PLAYER_RUN_FRAME4 4
#define PLAYER_RUN_FRAME5 5
#define PLAYER_RUN_FRAME6 6
#define PLAYER_RUN_FRAME7 7
#define PLAYER_RUN_FRAME8 8
#define PLAYER_RUN_FRAME9 9
#define PLAYER_RUN_FRAME10 10
#define PLAYER_RUN_FRAME11 11
#define UFO_FRAME 12
#define PI_HEALTH_BAR 13

class PlayerAtlas : public TextureAtlas
{
public:
	PlayerAtlas();
	virtual ~PlayerAtlas();

	// Set up the stucture of this atlas 
	void load();
};

