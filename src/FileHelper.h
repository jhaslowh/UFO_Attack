#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <SOIL\SOIL.h>

class FileHelper
{
public:
	static int loadPNG(char* file);
};

