#pragma once
#include "UITransitionObject.h"

// Structure for lines of the terminal 
struct TLine {
  int type;
  string text;
} ;

// Terminal line types 
#define TL_NORMAL 0
#define TL_ERROR 1
#define TL_WARNING 2
#define TL_SUCCESS 3

class UITerminal : public UITransitionObject
{
	
	// Text variables 
	bool commandIssued;		// Will be true when user presses enter
	string commandString;   // String command to be read
	string line;			// Current typed line
	int maxTextLength;		// Max length
	int iteratorLoc;

	// Text rendering 
	float textSize;			// Size of drawn text
	float textOffX, textOffY;// Offset for text inside of box 

	// Function pointer
	void (*commandFunc)(string);
	bool useFunction;

	// Type colors 
	GLfloat** tColors;
	// Lines
	TLine lines[10];

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
	// Add a line to the terminal 
	void addLine(string line);
	// Add a line to the terminal 
	// Type must be one of the following:
	// TL_NORMAL, TL_ERROR, TL_WARNING, TL_SUCCESS
	void addLine(string line, int type);

	// Clear terminal
	void clear();

	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Parse a line for command and args 
	// If no command found, command will be left alone.
	// If no args found, args will be left alone. 
	static void getCommandAndArgs(string* line, string* command, string* args);
};

