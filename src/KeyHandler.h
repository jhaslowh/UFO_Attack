#pragma once
#include <SDL/SDL.h>
#include <string>

#define KEY_SPACE 0
#define KEY_0 1
#define KEY_1 2
#define KEY_2 3
#define KEY_3 4
#define KEY_4 5
#define KEY_5 6
#define KEY_6 7
#define KEY_7 8
#define KEY_8 9
#define KEY_9 10
#define KEY_A 11
#define KEY_B 12
#define KEY_C 13
#define KEY_D 14
#define KEY_E 15
#define KEY_F 16
#define KEY_G 17
#define KEY_H 18
#define KEY_I 19
#define KEY_J 20
#define KEY_K 21
#define KEY_L 22
#define KEY_M 23
#define KEY_N 24
#define KEY_O 25
#define KEY_P 26
#define KEY_Q 27
#define KEY_R 28
#define KEY_S 29
#define KEY_T 30
#define KEY_U 31
#define KEY_V 32
#define KEY_W 33
#define KEY_X 34
#define KEY_Y 35
#define KEY_Z 36
#define KEY_UP 37
#define KEY_DOWN 38
#define KEY_RIGHT 39
#define KEY_LEFT 40
#define KEY_ESCAPE 41
// These next two should be the same, just using
// both names for convenience. 
#define KEY_RETURN 42
#define KEY_ENTER 42 
#define KEY_BACKSPACE 43
#define KEY_SHIFT 44
#define KEY_TILDE 45
#define KEY_BACKQUOTE 45
#define KEY_PERIOD 46

// Total Number of keys 
#define KEY_COUNT 47

class KeyHandler
{
	// List of keys 
	bool keys[KEY_COUNT];
	bool keysNext[KEY_COUNT];
	bool keysOld[KEY_COUNT];
	float keyDownTime[KEY_COUNT];
	// Time to wait till key is repeated.
	float timeForRepeat;		
	// Time to start multiply repeats at 
	float timeForMultiRepeat;   

public:
	KeyHandler();
	~KeyHandler();

	// Update keys 
	void update(float deltaTime);

	// Update the keystates 
	void updateState(SDL_Event windowEvent);

	// Check to see if a key is down
	bool keyDown(int key);

	// Check to see if a key is up
	bool keyUp(int key);

	// Check to see if a key was released
	// (was down and just released)
	bool keyReleased(int key);

	// Check to see if a key was pressed
	// (was up and just pressed)
	bool keyPressed(int key);

	// Check to see if a key was pressed
	// (was up and just pressed) or has been 
	// held for a set amout of time 
	bool keyPressedHold(int key);

	// Get the string of the pressed key
	std::string getPressedKey();

private:
	// Get the key index from sent scancode 
// For list of scancodes's, please see 
// http://wiki.libsdl.org/SDL_Scancode
	int keyIndex(int scancode);
};

