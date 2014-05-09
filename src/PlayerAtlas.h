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
#define UFO_BEAR_FRAME 13
#define PI_HEALTH_BAR 14
#define PI_PLAYER_ARM 15
#define PI_GUN_LASER 16
#define PI_GUN_LASER_MUZ 17
#define PI_GUN_SHOTGUN 18
#define PI_GUN_SHOTGUN_MUZ 19
#define PI_GUN_SMG 20
#define PI_UFO_RAY 21
#define PI_UFO_ROCKET 22
#define PI_UFO_MACHINE_GUN 23
#define PI_UFO_COWTAPULT 24

class PlayerAtlas : public TextureAtlas
{
public:
	PlayerAtlas();
	virtual ~PlayerAtlas();

	// Set up the stucture of this atlas 
	void load();
};

