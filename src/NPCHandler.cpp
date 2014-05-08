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
	NPC* itr = head;
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
	
	NPC* itr = head;
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

// Add new object to list by name.
// Returns true if name is matched. 
bool NPCHandler::addByName(std::string name, float x, float y){
	if (name.compare("soldier") == 0){
		add(new NPCSoldier(x,y));
		return true;
	}
	else if (name.compare("sniper") == 0){
		add(new NPCSniperSoldier(x,y));
		return true;
	}
	else if (name.compare("cow") == 0){
		add(new NPCcow(x,y));
		return true;
	}
	else if (name.compare("stinger") == 0){
		add(new NPCStingerSoldier(x,y));
		return true;
	}
	else if (name.compare("hsoldier") == 0){
		add(new NPCHeavySoldier(x,y));
		return true;
	}
	else if (name.compare("tank") == 0){
		add(new NPCTank(x,y));
		return true;
	}
	else if (name.compare("turret") == 0){
		add(new NPCTurret(x,y));
		return true;
	}
	else if (name.compare("sam") == 0){
		add(new NPCSamSite(x,y));
		return true;
	}
	else if (name.compare("civilian") == 0){
		add(new NPCCivilian(x,y));
		return true;
	}
	return false;
}

// Remove object from handler
void NPCHandler::remove(NPC* obj){
	// Check it obj is head
	if (obj == head){
		NPC* itr = head;
		head = head->next;
		delete itr;
	}

	// Setup for list
	NPC* itr = head;
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
int NPCHandler::update(float deltaTime, Handlers* handlers){
	uitr = head;
	int count = 0;
	while (uitr != NULL){
		if (uitr->getAlive()) count++;
		uitr->updateMovement(deltaTime, handlers);
		uitr->updateCollision(deltaTime, handlers);
		uitr->update(deltaTime, handlers);
		uitr = uitr->next;
	}
	return count;
}

// Draw object lights 
void NPCHandler::drawLight(GLHandler* mgl, GameAtlas* mGame){
	ditr = head;
	while (ditr != NULL){
		ditr->drawLight(mgl, mGame);
		ditr = ditr->next;
	}
}

// Draw objects
void NPCHandler::draw(GLHandler* mgl, GameAtlas* mGame){
	ditr = head;

	while (ditr != NULL){
		ditr->draw(mgl, mGame);
		ditr = ditr->next;
	}
}

int NPCHandler::getAliveCount()
{
	int i=0;
	while (uitr != NULL){
		if (uitr->getAlive()) i++;
	}
	return i;
}

