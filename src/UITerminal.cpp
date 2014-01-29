#include "UITerminal.h"


UITerminal::UITerminal() : UITransitionObject()
{
	commandIssued = false;
	textSize = 20.0f;
	flatColor[0] = .2f;
	flatColor[1] = .2f;
	flatColor[2] = .2f;
	flatColor[3] = .9f;
	textOffX = 5.0f;
	textOffY = 5.0f;
	maxTextLength = 50;
	useFunction = false;

	// Set colors 
	tColors = new GLfloat*[4];
	// Normal Color
	tColors[0] = new GLfloat[4];
	tColors[0][0] = .9f;
	tColors[0][1] = .9f;
	tColors[0][2] = .9f;
	tColors[0][3] = .8f;
	// Error Color
	tColors[1] = new GLfloat[4];
	tColors[1][0] = 1.0f;
	tColors[1][1] = .38f;
	tColors[1][2] = .28f;
	tColors[1][3] = .8f;
	// Warning Color
	tColors[2] = new GLfloat[4];
	tColors[2][0] = 1.0f;
	tColors[2][1] = .63f;
	tColors[2][2] = .24f;
	tColors[2][3] = .8f;
	// Success Color 
	tColors[3] = new GLfloat[4];
	tColors[3][0] = .47f;
	tColors[3][1] = 1.0f;
	tColors[3][2] = .47f;
	tColors[3][3] = .8f;

	// Set blank lines 
	TLine tline;
	tline.type = 0;
	tline.text = "";

	for (int i = 0; i < 10; i++)
		lines[i] = tline;
}

UITerminal::~UITerminal(){
	for (int i = 0; i < 4; i++)
		delete[] tColors[i];
	delete[] tColors;
}

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

// Add a line to the terminal 
void UITerminal::addLine(string line){
	addLine(line, TL_NORMAL);
}

// Add a line to the terminal 
// Type must be one of the following:
// TL_NORMAL, TL_ERROR, TL_WARNING, TL_SUCCESS
void UITerminal::addLine(string line, int type){
	// Make new line structure 
	TLine tLine;
	tLine.text = line;
	tLine.type = type;

	// Move lines back in history 
	for (int i = 9; i > 0; i--){
		lines[i] = lines[i - 1];
	}

	// Add line to list 
	lines[0] = tLine;
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
	if (mKeyH->keyPressedHold(KEY_BACKSPACE)){
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

	// Draw background
	mgl->setFlatColor(flatColor);
	mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y, width, textSize + 10.0f);
	
	// Draw current lines
	mgl->setFlatColor(tColors[0]);
	mAtlas->mTextRender->drawText(*mgl, line, loc_x + textOffX, loc_y + textOffY, 0, textSize);
	// Draw itterator 
	mAtlas->drawScale2(mgl, UII_REC, loc_x + textOffX + mAtlas->mTextRender->measureString(line, textSize), 
		loc_y + textOffY, 2.0f, textSize);

	// Draw history lines 
	if (shown()){
		for (int i = 0; i < 10; i++){
			mgl->setFlatColor(tColors[lines[i].type]);
			mAtlas->mTextRender->drawText(*mgl, lines[i].text, 
				loc_x + textOffX, loc_y - (textSize * (i+1)), 0, textSize);
		}
	}
}