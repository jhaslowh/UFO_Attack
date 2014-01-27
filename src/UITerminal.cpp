#include "UITerminal.h"


UITerminal::UITerminal() : UITransitionObject()
{
	commandIssued = false;
	textSize = 20.0f;
	textColor[0] = .8f;
	textColor[1] = .8f;
	textColor[2] = .8f;
	textColor[3] = .8f;
	flatColor[0] = .2f;
	flatColor[1] = .2f;
	flatColor[2] = .2f;
	flatColor[3] = .9f;
	textOffX = 5.0f;
	textOffY = 5.0f;
	maxTextLength = 50;
	useFunction = false;
}

UITerminal::~UITerminal(){}

// Set max characters for the terminal 
void UITerminal::setMaxTextLength(int l){maxTextLength = l;}
// Get the total number of characters 
int UITerminal::getMaxTextLength(){return maxTextLength;}

// Get the command string
string UITerminal::getCommandString(){
	return commandString;
}

// Check if a command was issued 
bool UITerminal::CommandIssued(){
	if (commandIssued){
		commandIssued = false;
		return true;
	}
	return false;
}

// Set function to use on commands 
void UITerminal::setCommandFunc(void func(string)){
	useFunction = true;
	commandFunc = func;
}

// Update input 
void UITerminal::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UITransitionObject::updateInput(mKeyH, mMouseH);

	// Add text to the line 
	line += mKeyH->getPressedKey();

	// Make sure line is not too long
	if (line.length() > maxTextLength){
		line = line.substr(0, maxTextLength);
	}

	// Check for backspace 
	if (mKeyH->keyPressed(KEY_BACKSPACE)){
		line = line.substr(0, line.length() - 1);
	}

	// Check for enter 
	if (mKeyH->keyPressed(KEY_ENTER)){
		commandIssued = true;
		commandString = line;
		line.clear();

		// Call command function if set 
		if (useFunction){
			commandIssued = false;
			commandFunc(commandString);
		}
	}
}

// Draw the object to the screen
// UIAtles must be bound first.
void UITerminal::draw(GLHandler* mgl, UIAtlas* mAtlas){

	mgl->setFlatColor(flatColor);
	mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y, width, textSize + 10.0f);
	mgl->setFlatColor(textColor);
	mAtlas->mTextRender->drawText(*mgl, line, loc_x + textOffX, loc_y + textOffY, 0, textSize);
	mAtlas->drawScale2(mgl, UII_REC, loc_x + textOffX + mAtlas->mTextRender->measureString(line, textSize), 
		loc_y + textOffY, 2.0f, textSize);
}