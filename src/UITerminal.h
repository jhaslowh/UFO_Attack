#pragma once
#include "UITransitionObject.h"

class UITerminal : public UITransitionObject
{
	
	// Text variables 
	bool commandIssued;		// Will be true when user presses enter
	string commandString;   // String command to be read
	string line;			// Current typed line
	int maxTextLength;		// Max length

	// Text rendering 
	float textSize;			// Size of drawn text
	GLfloat textColor[4];	// Text color 
	float textOffX, textOffY;// Offset for text inside of box 

public:
	UITerminal();
	virtual ~UITerminal();

	// Get the command string
	string getCommandString();
	// Check if a command was issued 
	bool CommandIssued();

	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);
};

