#include "ExplHandler.h"


ExplHandler::ExplHandler()
{
	// Make array 
	size = 150;
	lastActive = 0;
	expls = new Explosion*[size];
	for (int i = 0; i < size; i++){
		expls[i] = new Explosion();
	}
}

ExplHandler::~ExplHandler()
{
	if (expls == NULL) return;
	for (int i = 0; i < size; i++){
		delete expls[i];
		expls[i] = NULL;
	}
	delete[] expls;
	expls = NULL;
}

// Return size
int ExplHandler::getSize(){return size;}

// Returns last active 
int ExplHandler::getLastActive(){return lastActive;}

// Add new explosion to hander
// This method will clone the sent pointer. So 
// do not send it pointers that you do not delete. 
void ExplHandler::add(Explosion* e){
	if (e == NULL) return;

	for (int i = 0; i < size; i++){
		// If current explosion is dead, add in place
		if (!expls[i]->isValid()){
			expls[i]->clone(e);
			return;
		}

		// Check if current is null
		if (expls[i] == NULL){
			expls[i] = new Explosion();
			expls[i]->clone(e);
			return;
		}
	}
}

// Update explosion object states 
void ExplHandler::update(float deltaTime){
	// Update 
	lastActive = 0;
	for (int i = 0; i < size; i++){
		if (expls[i] != NULL && expls[i]->isValid()){
			expls[i]->update(deltaTime);
			lastActive = i;
		}
	}
}

// Draw explosion objects 
void ExplHandler::draw(GLHandler* mgl, GameAtlas* mAtlas){
	for (int i = 0; i <= lastActive; i++){
		expls[i]->draw(mgl, mAtlas);
	}
}
