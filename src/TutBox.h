#pragma once
#include <string>
#include "GLColors.h"
#include "GLHandler.h"
#include "UIAtlas.h"

#define TUT_BOX_TEXT_SIZE 14.0f

// Tut arrow locs 
#define TA_TOP_LEFT 0
#define TA_TOP_MIDDLE 1
#define TA_RIGHT_TOP 2

class TutBox
{
	// Text to display
	std::string text;
	// Location of box
	float locX, locY;
	// Size of box 
	float width, height;

	// Tut arrow 
	bool showArrow;
	float arrowRotation;
	float arrowOffsetX, arrowOffsetY;

public:
	TutBox();
	TutBox(std::string t);
	TutBox(std::string t, float w, float h);
	~TutBox();

	void setText(std::string s);
	std::string getText();
	void setLocation(float x, float y);
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setSize(float w, float h);
	void setWidth(float w);
	float getWidth();
	void setHeight(float h);
	float getHeight();

	// Draw ui box 
	void draw(GLHandler* mgl, UIAtlas* mUI);

	// Turn on the tut arrow and put it at the sent loc
	// loc = TA_TOP_LEFT, TA_TOP_MIDDLE, TA_RIGHT_TOP 
	// NOTE: Call this after size and location set 
	void turnOnTutArrow(int loc);

	// Turn off arrow
	void turnOffTutArrow();
};

