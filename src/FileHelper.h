#pragma once
#include <glew.h>
#include <SOIL/SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SDL/SDL_rwops.h"
#include "Settings.h"
#include "SaveData.h"
#include "StoreItems.h"

// Load a texture into opengl 
int loadPNG(std::string file);

// Load the settings into sent object
void loadSettings(Settings* s);

// Save the settings into settings file 
void saveSettings(Settings* s);

// Load player save data 
void loadSaveData(SaveData* sd);

// Save player save data
void saveSaveData(SaveData* sd);

// ---------------------------------------- //
//       Helper Methods                     //
// ---------------------------------------- // 

// Convert int to string
std::string toString(int value);

// Convert double to string
std::string toString(double value);

// Convert string to int
int toInt(std::string s);

// Convert string to double
double toDouble(std::string s);

// Return setting from file 
std::string getSetting(std::string fileString, std::string setting);

// Check if a file exists
bool fexists(const char *filename);

