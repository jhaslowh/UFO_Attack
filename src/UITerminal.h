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

	// Function pointer
	void (*commandFunc)(string);
	bool useFunction;

public:
	UITerminal();
	virtual ~UITerminal();

	// Set max characters for the terminal 
	void setMaxTextLength(int l);
	// Get the total number of characters 
	int getMaxTextLength();

	// Get the command string
	string getCommandString();
	// Check if a command was issued 
	bool CommandIssued();
	// Set function to use on commands 
	void setCommandFunc(void func(string));

	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);
};

