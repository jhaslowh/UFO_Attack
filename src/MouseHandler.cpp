#include "MouseHandler.h"


MouseHandler::MouseHandler(){
	left_down = false;
	right_down = false;
	last_left_down = false;
	last_right_down = false;
}
MouseHandler::~MouseHandler(){}


// Get the mouse location 
float* MouseHandler::getLoc(){ return mouse_loc;}

// Get the x location 
float MouseHandler::getX(){return mouse_loc[0];}

// Get the y location 
float MouseHandler::getY(){return mouse_loc[1];}

// Check button states 
bool MouseHandler::isLeftDown(){return left_down;}
bool MouseHandler::isRightDown(){return right_down;}

// Call to update the mouse state
void MouseHandler::updateState(SDL_Event windowEvent){
	switch( windowEvent.type ){
        /* Mouse events */
        case SDL_MOUSEMOTION:
			mouse_loc[0] = (float)windowEvent.motion.x;
			mouse_loc[1] = (float)windowEvent.motion.y;
			break;
        case SDL_MOUSEBUTTONDOWN:
			if(windowEvent.button.button == SDL_BUTTON_LEFT)
				left_down = true;
			if(windowEvent.button.button == SDL_BUTTON_RIGHT)
				right_down = true;
            break;
		case SDL_MOUSEBUTTONUP:
			if(windowEvent.button.button == SDL_BUTTON_LEFT)
				left_down = false;
			if(windowEvent.button.button == SDL_BUTTON_RIGHT)
				right_down = false;
			break;
        default:
            break;
    }
}

// Call at the end of the game update 
void MouseHandler::update(){
	last_left_down = left_down;
	last_right_down = right_down;
}