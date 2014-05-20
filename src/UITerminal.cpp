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
	maxTextLength = 100;
	useFunction = false;
	iteratorLoc = 0;

	iteratorAlpha = 1.0f;
	iteratorBlinkSpeed = 1.5f;
	blinkFade = true;

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

	for (int i = 0; i < T_LINE_COUNT; i++)
		lines[i] = tline;
}

UITerminal::~UITerminal(){
	for (int i = 0; i < 4; i++)
		delete[] tColors[i];
	delete[] tColors;
}

// Set max characters for the terminal 
void UITerminal::setMaxTextLength(unsigned int l){maxTextLength = l;}
// Get the total number of characters 
int UITerminal::getMaxTextLength(){return maxTextLength;}

// Get the command string
std::string UITerminal::getCommandString(){
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
void UITerminal::setCommandFunc(void func(std::string)){
	useFunction = true;
	commandFunc = func;
}

// Add a line to the terminal 
void UITerminal::addLine(std::string line){
	addLine(line, TL_NORMAL);
}

// Add a line to the terminal 
// Type must be one of the following:
// TL_NORMAL, TL_ERROR, TL_WARNING, TL_SUCCESS
void UITerminal::addLine(std::string line, int type){
	// Make new line structure 
	TLine tLine;
	tLine.text = line;
	tLine.type = type;

	// Move lines back in history 
	for (int i = T_LINE_COUNT-1; i > 0; i--){
		lines[i] = lines[i - 1];
	}

	// Add line to list 
	lines[0] = tLine;
}

// Clear terminal
void UITerminal::clear(){
	for (int i = 0; i < T_LINE_COUNT; i++){
		lines[i].text = "";
	}
}

// Update terminal
void UITerminal::update(float deltaTime){
	UITransitionObject::update(deltaTime);

	// Fade out iterator 
	if (blinkFade){
		iteratorAlpha -= deltaTime * iteratorBlinkSpeed;
		if (iteratorAlpha <= 0.0f){
			blinkFade = !blinkFade;
			iteratorAlpha = 0.0f;
		}
	}
	// Fade in iterator 
	else {
		iteratorAlpha += deltaTime * iteratorBlinkSpeed;
		if (iteratorAlpha >= 1.0f){
			blinkFade = !blinkFade;
			iteratorAlpha = 1.0f;
		}
	}
}

// Update input 
void UITerminal::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UITransitionObject::updateInput(mKeyH, mMouseH);

	// Check for up arrow and add last command
	if (mKeyH->keyPressed(KEY_UP)){
		line = lines[0].text;
		iteratorLoc = line.length();
	}

	// Add text to the line 
	std::string next = mKeyH->getPressedKey();
	if (next.length() > 0){
		// Set iterator to visible 
		iteratorAlpha = 1.0f;
		blinkFade = true;

		// Add text to end of line if iterator is at the end
		if (iteratorLoc == line.length()){
			line += next;
			iteratorLoc++;
		}
		// Add text to the middle of line if iterator is inside line 
		else {
			line = 
				line.substr(0, iteratorLoc) + 
				next + 
				line.substr(iteratorLoc, line.length());
			iteratorLoc++;
		}
	}


	// Make sure line is not too long
	if (line.length() > maxTextLength){
		line = line.substr(0, maxTextLength);
		iteratorLoc = maxTextLength;
	}

	// Check for backspace 
	if (mKeyH->keyPressedHold(KEY_BACKSPACE)){
		if (iteratorLoc > 0){
			// Subtract text at end if iterator is at end of line
			if (iteratorLoc == line.length()){
				line = line.substr(0, line.length() - 1);
				iteratorLoc--;
			}
			// Subtract text in the middle of line if iterator is inside line 
			else {
				line = 
					line.substr(0, iteratorLoc-1) + 
					line.substr(iteratorLoc, line.length());
				iteratorLoc--;
			}
		}
	}

	// Check for enter 
	if (mKeyH->keyPressed(KEY_ENTER)){
		iteratorLoc = 0;
		commandIssued = true;
		commandString = line;
		line.clear();

		// Call command function if set 
		if (useFunction){
			commandIssued = false;
			commandFunc(commandString);
		}
	}

	// Check if user is trying to move iterator 
	if (mKeyH->keyPressedHold(KEY_LEFT)){
		iteratorLoc--;
		if (iteratorLoc < 0)
			iteratorLoc = 0;
	}
	if (mKeyH->keyPressedHold(KEY_RIGHT)){
		iteratorLoc++;
		if (iteratorLoc > (int)line.length())
			iteratorLoc = (int)line.length();
	}
}

// Draw the object to the screen
// UIAtles must be bound first.
void UITerminal::draw(GLHandler* mgl, UIAtlas* mAtlas){

	// Draw background
	mgl->setFlatColor(flatColor, flatColor[3] * mOpacity);
	mAtlas->drawScale2(mgl, UII_REC, loc_x, loc_y, width, textSize + 10.0f);
	
	// Draw current lines
	mgl->setFlatColor(tColors[0], tColors[0][3] * mOpacity);
	mAtlas->mTextRender->drawText(*mgl, line, loc_x + textOffX, loc_y + textOffY, 0, textSize);
	// Draw itterator	
	if (iteratorAlpha > 0.5f)	
		mgl->setFlatColor(tColors[0], 1.0f);
	else 
		mgl->setFlatColor(tColors[0], 0.0f);
	mAtlas->drawScale2(mgl, UII_REC, loc_x + textOffX + 
		mAtlas->mTextRender->measureString(line.substr(0,iteratorLoc), textSize), 
		loc_y + textOffY, 2.0f, textSize);

	// Draw history lines 
	if (shown()){
		for (int i = 0; i < T_LINE_COUNT; i++){
			mgl->setFlatColor(tColors[lines[i].type], tColors[lines[i].type][3] * mOpacity);
			mAtlas->mTextRender->drawText(*mgl, lines[i].text, 
				loc_x + textOffX, loc_y - (textSize * (i+1)), 0, textSize);
		}
	}
}

// Parse a line for command and args 
// If no command found, command will be left alone.
// If no args found, args will be left alone. 
void UITerminal::getCommandAndArgs(std::string* line, std::string* command, std::string* args){
	int firstSpace = line->find(std::string(" "));

	// Command has no sub commands
	if (firstSpace == -1){
		*command = *line;
		*args = "";
	}
	// Command is followed by one space 
	else if (firstSpace == line->length() - 1){
		*command = line->substr(0, line->length() - 1);
		*args = "";
	}
	// Command has sub commands 
	else {
		// Grab command 
		*command = line->substr(0, firstSpace);
		// Grab arguments 
		*args = line->substr(firstSpace+1, line->length());
	}
}
