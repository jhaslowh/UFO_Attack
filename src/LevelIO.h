#pragma once
#include "Handlers.h"
#include "LevelProperties.h"
#include "Player.h"
#include "SceneryHandler.h"
#include "NPCHandler.h"
#include "Sign.h"
#include "Tree.h"
#include "Fence.h"
#include "Crate.h"
#include "LongCrate.h"
#include "TallCrate.h"
#include "HayBale.h"
#include "NPCSoldier.h"
#include "NPCSniperSoldier.h"

// Save the sent level to the sent file
// Note: Just use file name, no extension or directory
void saveLevel(Handlers* handlers, std::string file, bool addToMaster);

// Load the level from the sent file into the sent level pointer
// Note: Just use file name, no extension or directory
void loadLevel(Handlers* handlers, std::string file);
