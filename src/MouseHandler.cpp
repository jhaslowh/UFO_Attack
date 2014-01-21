#include "MouseHandler.h"

MouseHandler::MouseHandler(){
	left_down = false;
	right_down = false;
	last_left_down = false;
	last_right_down = false;
}
MouseHandler::~MouseHandler(){}


// Get the mouse location 
Point MouseHandler::getLoc(){ return loc;}

// Get the x location 
float MouseHandler::getX(){return loc.getX();}

// Get the y location 
float MouseHandler::getY(){return loc.getY();}

// Check button states 
bool MouseHandler::isLeftDown(){return left_down;}
bool MouseHandler::wasLeftDown(){return last_left_down;}
bool MouseHandler::isRightDown(){return right_down;}
bool MouseHandler::wasRightDown(){return last_right_down;}

// Call to update the mouse state
void MouseHandler::updateState(SDL_Event windowEvent){
	switch( windowEvent.type ){
        /* Mouse events */
        case SDL_MOUSEMOTION:
			loc.setX((float)windowEvent.motion.x);
			loc.setY((float)windowEvent.motion.y);
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