#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "GLHandler.h"
#include "FileHelper.h"
#include "VertCordGenerator.h"

#define TR_SPACE_LENGTH 30
#define TR_FONT_SIZE 72.0f
#define TR_FONT_BOTTOM_SPACE 5.0f
#define TR_CHARACTERS 70

class TextRender
{
	float letterWidth[TR_CHARACTERS];
	
	// Drawing variables 
	GLushort indicies[6];

public:
	TextRender();
	~TextRender();

	// Draw text to the screen with the following properties 
	void drawText(GLHandler mgl, std::string text, float x, float y, float rotation, float fontSize);

	// Measure how long the text will be on screen
	float measureString(std::string text, float size);

	// Get the index for the sent char
	int getCharIndex(char c);

	// Get the width of the sent character 
	float getLetterWidth(char c);
	
	// Setup the buffers for the font 
	void createFontBuffers(VertCordGenerator* vcg);

private:
	// Set the indexes based off a char
	void setIndicies(char c);
};

