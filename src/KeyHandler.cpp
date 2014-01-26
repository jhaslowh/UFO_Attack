#include "KeyHandler.h"


KeyHandler::KeyHandler()
{
	for (int i = 0; i < KEY_COUNT; i++)
		keys[i] = false;
}

KeyHandler::~KeyHandler(){}

// Update keys 
void KeyHandler::update(){
	for (int i = 0; i < KEY_COUNT; i++){
		keysOld[i] = keys[i];
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
				keys[key] = true;
			break;
        case SDL_KEYUP:
			key = keyIndex((int)windowEvent.key.keysym.scancode);
			if (key >= 0)
				keys[key] = false;
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

// Get the string of the pressed key
string KeyHandler::getPressedKey(){
	// Numbers 
	if (keys[KEY_0] && !keysOld[KEY_0])
		return string("0");
	if (keys[KEY_1] && !keysOld[KEY_1])
		return string("1");
	if (keys[KEY_2] && !keysOld[KEY_2])
		return string("2");
	if (keys[KEY_3] && !keysOld[KEY_3])
		return string("3");
	if (keys[KEY_4] && !keysOld[KEY_4])
		return string("4");
	if (keys[KEY_5] && !keysOld[KEY_5])
		return string("5");
	if (keys[KEY_6] && !keysOld[KEY_6])
		return string("6");
	if (keys[KEY_7] && !keysOld[KEY_7])
		return string("7");
	if (keys[KEY_8] && !keysOld[KEY_8])
		return string("8");
	if (keys[KEY_9] && !keysOld[KEY_9])
		return string("9");

	// Letters 
	if (keys[KEY_A] && !keysOld[KEY_A])
		return string("a");
	if (keys[KEY_B] && !keysOld[KEY_B])
		return string("b");
	if (keys[KEY_C] && !keysOld[KEY_C])
		return string("c");
	if (keys[KEY_D] && !keysOld[KEY_D])
		return string("d");
	if (keys[KEY_E] && !keysOld[KEY_E])
		return string("e");
	if (keys[KEY_F] && !keysOld[KEY_F])
		return string("f");
	if (keys[KEY_G] && !keysOld[KEY_G])
		return string("g");
	if (keys[KEY_H] && !keysOld[KEY_H])
		return string("h");
	if (keys[KEY_I] && !keysOld[KEY_I])
		return string("i");
	if (keys[KEY_J] && !keysOld[KEY_J])
		return string("j");
	if (keys[KEY_K] && !keysOld[KEY_K])
		return string("k");
	if (keys[KEY_L] && !keysOld[KEY_L])
		return string("l");
	if (keys[KEY_M] && !keysOld[KEY_M])
		return string("m");
	if (keys[KEY_N] && !keysOld[KEY_N])
		return string("n");
	if (keys[KEY_O] && !keysOld[KEY_O])
		return string("o");
	if (keys[KEY_P] && !keysOld[KEY_P])
		return string("p");
	if (keys[KEY_Q] && !keysOld[KEY_Q])
		return string("q");
	if (keys[KEY_R] && !keysOld[KEY_R])
		return string("r");
	if (keys[KEY_S] && !keysOld[KEY_S])
		return string("s");
	if (keys[KEY_T] && !keysOld[KEY_T])
		return string("t");
	if (keys[KEY_U] && !keysOld[KEY_U])
		return string("u");
	if (keys[KEY_V] && !keysOld[KEY_V])
		return string("v");
	if (keys[KEY_W] && !keysOld[KEY_W])
		return string("w");
	if (keys[KEY_X] && !keysOld[KEY_X])
		return string("x");
	if (keys[KEY_Y] && !keysOld[KEY_Y])
		return string("y");
	if (keys[KEY_Z] && !keysOld[KEY_Z])
		return string("z");
	if (keys[KEY_SPACE] && !keysOld[KEY_SPACE])
		return string(" ");

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
	default:
		break;
	}

	return -1;
}
