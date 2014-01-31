#pragma once
#include <glew.h>
#include <SOIL/SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SDL/SDL_rwops.h"
#include "Settings.h"
using namespace std;

// Load a texture into opengl 
int loadPNG(std::string file);

// Load the settings into sent object
void loadSettings(Settings* s);

// Save the settings into settings file 
void saveSettings(Settings* s);

// Convert int to string
string toString(int value);

// Convert double to string
string toString(double value);

// Convert string to int
int toInt(string s);

// Return setting from file 
string getSetting(string fileString, string setting);
