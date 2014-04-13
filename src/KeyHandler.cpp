#include "KeyHandler.h"

using namespace std;

KeyHandler::KeyHandler()
{
	for (int i = 0; i < KEY_COUNT; i++){
		keys[i] = false;
		keyDownTime[i] = 0.0f;
	}
	timeForRepeat = .5f;
	timeForMultiRepeat = .45f;
}

KeyHandler::~KeyHandler(){}

// Update keys 
void KeyHandler::update(float deltaTime){
	// Swap out keys 
	for (int i = 0; i < KEY_COUNT; i++){
		keysOld[i] = keys[i];
		keys[i] = keysNext[i];
	}

	for (int i = 0; i < KEY_COUNT; i++){
		if (keys[i])
			keyDownTime[i] += deltaTime;
		else 
			keyDownTime[i] = 0.0f;
	}
}

// Update the keystates 
void KeyHandler::updateState(SDL_Event windowEvent){
	int key = 0;
	switch( windowEvent.type ){
        /* Keyboard event */
        case SDL_KEYDOWN:
			key = keyIndex((int)windowEvent.key.keysym.scancode);
			if (key >= 0)
				keysNext[key] = true;
			break;
        case SDL_KEYUP:
			key = keyIndex((int)windowEvent.key.keysym.scancode);
			if (key >= 0)
				keysNext[key] = false;
            break;
        default:
            break;
    }
}

// Check to see if a key is down
bool KeyHandler::keyDown(int key){
	return keys[key];
}

// Check to see if a key is up
bool KeyHandler::keyUp(int key){
	return !keys[key];
}

// Check to see if a key was released
// (was down and just released)
bool KeyHandler::keyReleased(int key){
	return !keys[key] && keysOld[key];
}

// Check to see if a key was pressed
// (was up and just pressed)
bool KeyHandler::keyPressed(int key){
	return keys[key] && !keysOld[key];
}

// Check to see if a key was pressed
// (was up and just pressed) or has been 
// held for a set amout of time 
bool KeyHandler::keyPressedHold(int key){
	if (keyPressed(key) || keyDownTime[key] >= timeForRepeat){
		if (keyDownTime[key] >= timeForRepeat) keyDownTime[key] = timeForMultiRepeat;
		return true;
	}
	return false;
}

// Get the string of the pressed key
string KeyHandler::getPressedKey(){
	// Numbers 
	if (keyPressedHold(KEY_0))
		return string("0");
	if (keyPressedHold(KEY_1))
		return string("1");
	if (keyPressedHold(KEY_2))
		return string("2");
	if (keyPressedHold(KEY_3))
		return string("3");
	if (keyPressedHold(KEY_4))
		return string("4");
	if (keyPressedHold(KEY_5))
		return string("5");
	if (keyPressedHold(KEY_6))
		return string("6");
	if (keyPressedHold(KEY_7))
		return string("7");
	if (keyPressedHold(KEY_8))
		return string("8");
	if (keyPressedHold(KEY_9))
		return string("9");

	// Letters 
	
	if (keyPressedHold(KEY_A)){
		if (keys[KEY_SHIFT]) return string("A");
		return string("a");
	}
	if (keyPressedHold(KEY_B)){
		if (keys[KEY_SHIFT]) return string("B");
		return string("b");
	}
	if (keyPressedHold(KEY_C)){
		if (keys[KEY_SHIFT]) return string("C");
		return string("c");
	}
	if (keyPressedHold(KEY_D)){
		if (keys[KEY_SHIFT]) return string("D");
		return string("d");
	}
	if (keyPressedHold(KEY_E)){
		if (keys[KEY_SHIFT]) return string("E");
		return string("e");
	}
	if (keyPressedHold(KEY_F)){
		if (keys[KEY_SHIFT]) return string("F");
		return string("f");
	}
	if (keyPressedHold(KEY_G)){
		if (keys[KEY_SHIFT]) return string("G");
		return string("g");
	}
	if (keyPressedHold(KEY_H)){
		if (keys[KEY_SHIFT]) return string("H");
		return string("h");
	}
	if (keyPressedHold(KEY_I)){
		if (keys[KEY_SHIFT]) return string("I");
		return string("i");
	}
	if (keyPressedHold(KEY_J)){
		if (keys[KEY_SHIFT]) return string("J");
		return string("j");
	}
	if (keyPressedHold(KEY_K)){
		if (keys[KEY_SHIFT]) return string("K");
		return string("k");
	}
	if (keyPressedHold(KEY_L)){
		if (keys[KEY_SHIFT]) return string("L");
		return string("l");
	}
	if (keyPressedHold(KEY_M)){
		if (keys[KEY_SHIFT]) return string("M");
		return string("m");
	}
	if (keyPressedHold(KEY_N)){
		if (keys[KEY_SHIFT]) return string("N");
		return string("n");
	}
	if (keyPressedHold(KEY_O)){
		if (keys[KEY_SHIFT]) return string("O");
		return string("o");
	}
	if (keyPressedHold(KEY_P)){
		if (keys[KEY_SHIFT]) return string("P");
		return string("p");
	}
	if (keyPressedHold(KEY_Q)){
		if (keys[KEY_SHIFT]) return string("Q");
		return string("q");
	}
	if (keyPressedHold(KEY_R)){
		if (keys[KEY_SHIFT]) return string("R");
		return string("r");
	}
	if (keyPressedHold(KEY_S)){
		if (keys[KEY_SHIFT]) return string("S");
		return string("s");
	}
	if (keyPressedHold(KEY_T)){
		if (keys[KEY_SHIFT]) return string("T");
		return string("t");
	}
	if (keyPressedHold(KEY_U)){
		if (keys[KEY_SHIFT]) return string("U");
		return string("u");
	}
	if (keyPressedHold(KEY_V)){
		if (keys[KEY_SHIFT]) return string("V");
		return string("v");
	}
	if (keyPressedHold(KEY_W)){
		if (keys[KEY_SHIFT]) return string("W");
		return string("w");
	}
	if (keyPressedHold(KEY_X)){
		if (keys[KEY_SHIFT]) return string("X");
		return string("x");
	}
	if (keyPressedHold(KEY_Y)){
		if (keys[KEY_SHIFT]) return string("Y");
		return string("y");
	}
	if (keyPressedHold(KEY_Z)){
		if (keys[KEY_SHIFT]) return string("Z");
		return string("z");
	}
	if (keyPressedHold(KEY_SPACE))
		return string(" ");
	if (keyPressedHold(KEY_PERIOD))
		return string(".");

	return string("");
}

// Get the key index from sent scancode 
// For list of scancodes's, please see 
// http://wiki.libsdl.org/SDL_Scancode
int KeyHandler::keyIndex(int scancode){
	switch (scancode){
	case SDL_SCANCODE_SPACE:
		return KEY_SPACE;
	case SDL_SCANCODE_0:
		return KEY_0;
	case SDL_SCANCODE_1:
		return KEY_1;
	case SDL_SCANCODE_2:
		return KEY_2;
		break;
	case SDL_SCANCODE_3:
		return KEY_3;
	case SDL_SCANCODE_4:
		return KEY_4;
	case SDL_SCANCODE_5:
		return KEY_5;
	case SDL_SCANCODE_6:
		return KEY_6;
	case SDL_SCANCODE_7:
		return KEY_7;
	case SDL_SCANCODE_8:
		return KEY_8;
	case SDL_SCANCODE_9:
		return KEY_9;
	case SDL_SCANCODE_A:
		return KEY_A;
	case SDL_SCANCODE_B:
		return KEY_B;
	case SDL_SCANCODE_C:
		return KEY_C;
	case SDL_SCANCODE_D:
		return KEY_D;
	case SDL_SCANCODE_E:
		return KEY_E;
	case SDL_SCANCODE_F:
		return KEY_F;
	case SDL_SCANCODE_G:
		return KEY_G;
	case SDL_SCANCODE_H:
		return KEY_H;
	case SDL_SCANCODE_I:
		return KEY_I;
	case SDL_SCANCODE_J:
		return KEY_J;
	case SDL_SCANCODE_K:
		return KEY_K;
	case SDL_SCANCODE_L:
		return KEY_L;
	case SDL_SCANCODE_M:
		return KEY_M;
	case SDL_SCANCODE_N:
		return KEY_N;
	case SDL_SCANCODE_O:
		return KEY_O;
	case SDL_SCANCODE_P:
		return KEY_P;
	case SDL_SCANCODE_Q:
		return KEY_Q;
	case SDL_SCANCODE_R:
		return KEY_R;
	case SDL_SCANCODE_S:
		return KEY_S;
	case SDL_SCANCODE_T:
		return KEY_T;
	case SDL_SCANCODE_U:
		return KEY_U;
	case SDL_SCANCODE_V:
		return KEY_V;
	case SDL_SCANCODE_W:
		return KEY_W;
	case SDL_SCANCODE_X:
		return KEY_X;
	case SDL_SCANCODE_Y:
		return KEY_Y;
	case SDL_SCANCODE_Z:
		return KEY_Z;
	case SDL_SCANCODE_UP:
		return KEY_UP;
	case SDL_SCANCODE_DOWN:
		return KEY_DOWN;
	case SDL_SCANCODE_RIGHT:
		return KEY_RIGHT;
	case SDL_SCANCODE_LEFT:
		return KEY_LEFT;
	case SDL_SCANCODE_ESCAPE:
		return KEY_ESCAPE;
	case SDL_SCANCODE_RETURN:
		return KEY_RETURN;
	case SDL_SCANCODE_BACKSPACE:
		return KEY_BACKSPACE;
	case SDL_SCANCODE_LSHIFT:
	case SDL_SCANCODE_RSHIFT:
		return KEY_SHIFT;
	case SDL_SCANCODE_GRAVE:
		return KEY_TILDE;
	case SDL_SCANCODE_PERIOD:
		return KEY_PERIOD;
	default:
		break;
	}

	return -1;
}
