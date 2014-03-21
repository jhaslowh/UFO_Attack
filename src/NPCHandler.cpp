#include "NPCHandler.h"


NPCHandler::NPCHandler()
{
	head = NULL;
}

NPCHandler::~NPCHandler()
{
	delete head;
}

// Get number of objects 
int NPCHandler::getSize(){
	itr = head;
	int count = 0;
	while (itr != NULL){
		count++;
		itr = itr->next;
	}
	return count;
}

// Get head objective 
NPC* NPCHandler::getHead(){
	return head;
}
// Set the head for the handler
void NPCHandler::setHead(NPC* obj){
	head = obj;
}

// Add an object to the list 
void NPCHandler::add(NPC* obj){
	// Check if list is empty
	if (head == NULL){
		head = obj;
		return;
	}
	
	itr = head;
	while (itr != NULL)
	{
		if (itr->next == NULL){
			itr->next = obj;
			return;
		}
		itr = itr->next;
	}

	std::cout << "Error: could not add item to NPC linked list\n";
}

// Remove object from handler
void NPCHandler::remove(NPC* obj){
	// Check it obj is head
	if (obj == head){
		itr = head;
		head = head->next;
		delete itr;
	}

	// Setup for list
	itr = head;
	NPC* prev = NULL;

	// Go through list and find item to remove 
	while (itr != NULL)
	{
		if (itr == obj){
			// Fix previous 
			if (prev != NULL)
				prev->next = itr->next;
			// Set its next to null so that list is not deleted
			itr->next = NULL;
			// Delete pointer
			delete itr;

			return;
		}
		// Move to next spot in list 
		prev = itr;
		itr = itr->next;
	}

	std::cout << "Error: could not remove item from NPC linked list\n";
}

// Update objects
void NPCHandler::update(float deltaTime, Handlers* handlers){
	itr = head;
	while (itr != NULL){
		itr->updateMovement(deltaTime, handlers);
		itr->updateCollision(deltaTime, handlers);
		itr->update(deltaTime, handlers);
		itr = itr->next;
	}
}

// Draw object lights 
void NPCHandler::drawLight(GLHandler* mgl, GameAtlas* mGame){
	itr = head;
	while (itr != NULL){
		itr->drawLight(mgl, mGame);
		itr = itr->next;
	}
}

// Draw objects
void NPCHandler::draw(GLHandler* mgl, GameAtlas* mGame){
	itr = head;
	while (itr != NULL){
		itr->draw(mgl, mGame);
		itr = itr->next;
	}
}

