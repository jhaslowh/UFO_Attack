#pragma once
#include "UITransitionObject.h"

// Structure for lines of the terminal 
struct TLine {
  int type;
  std::string text;
} ;

// Terminal line types 
#define TL_NORMAL 0
#define TL_ERROR 1
#define TL_WARNING 2
#define TL_SUCCESS 3

#define T_LINE_COUNT 20

class UITerminal : public UITransitionObject
{
	
	// Text variables 
	bool commandIssued;			// Will be true when user presses enter
	std::string commandString;		// String command to be read
	std::string line;				// Current typed line
	unsigned int maxTextLength;	// Max length
	int iteratorLoc;

	// Text rendering 
	float textSize;				// Size of drawn text
	float textOffX, textOffY;	// Offset for text inside of box
	float iteratorAlpha;		// Alpha of iterator
	float iteratorBlinkSpeed;	// Speed to blink iterator
	float blinkFade;			// Whether or not blink should fade

	// Function pointer
	void (*commandFunc)(std::string);
	bool useFunction;

	// Type colors 
	GLfloat** tColors;
	// Lines
	TLine lines[T_LINE_COUNT];

public:
	UITerminal();
	virtual ~UITerminal();

	// Set max characters for the terminal 
	void setMaxTextLength(unsigned int l);
	// Get the total number of characters 
	int getMaxTextLength();

	// Get the command string
	std::string getCommandString();
	// Check if a command was issued 
	bool CommandIssued();
	// Set function to use on commands 
	void setCommandFunc(void func(std::string));
	// Add a line to the terminal 
	void addLine(std::string line);
	// Add a line to the terminal 
	// Type must be one of the following:
	// TL_NORMAL, TL_ERROR, TL_WARNING, TL_SUCCESS
	void addLine(std::string line, int type);

	// Clear terminal
	void clear();

	// Update terminal 
	virtual void update(float deltatime);

	// Update input 
	virtual void updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH);
	// Draw the object to the screen
	// UIAtles must be bound first.
	virtual void draw(GLHandler* mgl, UIAtlas* mAtlas);

	// Parse a line for command and args 
	// If no command found, command will be left alone.
	// If no args found, args will be left alone. 
	static void getCommandAndArgs(std::string* line, std::string* command, std::string* args);
};

