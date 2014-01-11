#pragma once
#include <SDL\SDL.h>

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

#define KEY_COUNT 41

class KeyHandler
{
	// List of keys 
	bool keys[KEY_COUNT];
	
public:
	KeyHandler();
	~KeyHandler();

	// Update the keystates 
	void updateState(SDL_Event windowEvent);

	// Check to see if a key is down
	bool keyDown(int key);

private:
	// Get the key index from sent scancode 
// For list of scancodes's, please see 
// http://wiki.libsdl.org/SDL_Scancode
	int keyIndex(int scancode);
};

