#include "ExplHandler.h"


ExplHandler::ExplHandler()
{
	head = NULL;
}

ExplHandler::~ExplHandler()
{
	// Delete head list 
	Explosion* itr;
	while (head != NULL){
		itr = head->next;
		delete head;
		head = itr;
	}
}

// Add new explosion to hander
// This method will clone the sent pointer. So 
// do not send it pointers that you do not delete. 
void ExplHandler::add(Explosion* e){
	if (e == NULL) return;

	// Check if list is empty 
	if (head == NULL){
		head = new Explosion(e);
		return;
	}

	// Add explosion to list 
	Explosion* itr = head;
	Explosion* last = NULL;

	while (itr != NULL){
		// Insert into list if current is not valid 
		if (!itr->isValid()){
			itr->clone(e);
			return;
		}

		// Move to next and set last 
		if (itr->next == NULL)
			last = itr;
		itr = itr->next;
	}

	// Add to end of list if no spots found 
	last->next = new Explosion(e);
}

// Remove explosion from handler
void ExplHandler::remove(Explosion* e){
	Explosion* hold = NULL;
	
	// Check if head 
	if (head == e){
		hold = head->next;
		delete head;
		head = hold;
		return;
	}

	// Iterate through list and check for pointer 
	Explosion* itr = head;
	while (itr != NULL){
		// Delete if found 
		if (itr == e){
			hold->next = itr->next;
			delete itr;
			return;
		}

		hold = itr;
		itr = itr->next;
	}
}

// Update explosion object states 
void ExplHandler::update(float deltaTime){
	Explosion* itr = head;
	while (itr != NULL){
		itr->update(deltaTime);
		itr = itr->next;
	}
}

// Draw explosion objects 
void ExplHandler::draw(GLHandler* mgl, GameAtlas* mAtlas){
	Explosion* itr = head;
	while (itr != NULL){
		itr->draw(mgl, mAtlas);
		itr = itr->next;
	}
}
